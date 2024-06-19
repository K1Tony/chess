#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qevent.h>
#include <piece.h>
#include <pawn.h>
#include <king.h>
#include <queen.h>
#include <rook.h>
#include <bishop.h>
#include <knight.h>
#include <QPair>

#include <QStandardItemModel>

#include <QPushButton>
#include <qlabel.h>
#include <QScreen>

#include <QDrag>
#include <QMimeData>
#include <qthread.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainwindow)
{
    ui->setupUi(this);


    int playing_area = this->width() * 0.7;
    square_length_ = playing_area / 8;
    ui->gameStatus->setMinimumHeight(square_length_);
    ui->whitePerformance->setMinimumHeight(square_length_);
    ui->whitePerformance->setMaximumHeight(square_length_);
    ui->blackPerformance->setMinimumHeight(square_length_);
    ui->blackPerformance->setMaximumHeight(square_length_);

    ui->whitePerformance->hide();
    ui->blackPerformance->hide();

    ui->groupBox->hide();
    ui->tableView->hide();
    ui->gameStatus->setText(ui->gameStatus->text());

    connect(ui->start, &QPushButton::clicked, this, [this] () {
        this->ui->groupBox->show();
        this->ui->tableView->show();

        this->ui->gameStatus->setMaximumHeight(this->square_length_);
        this->init();
        this->enable_buttons();
        delete this->ui->start;
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enable_buttons()
{
    ui->resign->setEnabled(true);
    ui->settings->setEnabled(true);
    ui->flip->setEnabled(true);
    ui->load->setEnabled(true);
    ui->save->setEnabled(true);
    ui->undo->setEnabled(true);
}

void MainWindow::init()
{
    // Chessboard init
    chessboard_.reset(new Chessboard(square_length_, ui->chessGrid, ui->centralwidget));
    for (int i = 0; i < 10; i++) {
        ui->chessGrid->setColumnMinimumWidth(i, square_length_);
    }
    for (int i = 0; i < 12; i++) {
        ui->chessGrid->setRowMinimumHeight(i, square_length_);
    }
    // setFixedSize(width(), square_length * 11);

    // chessboard_->color_dialog().setDark_square(MColor(255, 0, 255));

    auto view = new QHeaderView(Qt::Orientation::Vertical);
    ui->tableView->setVerticalHeader(view);

    ui->gameStatus->hide();
    ui->whitePerformance->show();
    ui->blackPerformance->show();

    connect(ui->replay, &QPushButton::clicked, this, [this] () {
        this->chessboard_->readFEN(FEN(FEN::basic_fen));
        this->move_dialog_->clear_moves();

        this->resigned_ = false;
        this->mate_.setValue(false);
        this->draw_.setValue(false);
        this->ui->gameStatus->setText(QString());
        this->ui->gameStatus->hide();

        this->white_points_.setValue(0);
        this->black_points_.setValue(0);

        this->disableNewGame();
    });

    connect(ui->resign, &QPushButton::clicked, this, [this] () {
        this->ui->gameStatus->show();
        this->enableNewGame();
        if (this->chessboard_->turn() == WHITE) {
            this->ui->gameStatus->setText("BLACK WINS BY RESIGNATION");
            this->ui->gameStatus->setStyleSheet("QLabel {background-color : black; color: white}");
        } else {
            this->ui->gameStatus->setText("WHITE WINS BY RESIGNATION");
            this->ui->gameStatus->setStyleSheet("QLabel {background-color : white; color: black}");
        }
        this->resigned_ = true;
    });

    connect(ui->flip, &QPushButton::clicked, this, [this] () {
        this->chessboard_->flip_chessboard();
    });

    connect(ui->settings, &QPushButton::clicked, this, [this] () {
        if (this->settings_widget_->isHidden())
            this->settings_widget_->show();
        else
            this->settings_widget_->hide();
    });

    connect(ui->undo, &QPushButton::clicked, this, [this] () {this->move_dialog_->undo();});

    mate_notifier_ = mate_.addNotifier([this] () {
        this->enableNewGame();
        this->ui->gameStatus->show();
        if (this->mate_.value()) {
            if (this->chessboard_->turn() == WHITE) {
                this->ui->gameStatus->setText("BLACK WINS BY CHECKMATE");
                this->ui->gameStatus->setStyleSheet("QLabel {background-color : black; color: white}");


            } else {
                this->ui->gameStatus->setText("WHITE WINS BY CHECKMATE");
                this->ui->gameStatus->setStyleSheet("QLabel {background-color : white; color: black}");
            }
        }
    });
    draw_notifier_ = draw_.addNotifier([this] () {
        this->enableNewGame();
        this->ui->gameStatus->show();
        if (this->draw_.value()) {
            this->ui->gameStatus->setText("DRAW");
            this->ui->gameStatus->setStyleSheet("QLabel {background-color : black; color: white}");
        }
    });

    white_pts_notif_ = white_points_.addNotifier([this] () {
                                        if (this->white_points_ > 0) {
                                            this->ui->whitePerformance->setText(
                                                "White points: " + QString(std::to_string(this->white_points_).c_str()));
                                        } else {
                                            this->ui->whitePerformance->setText(QString());
                                        }
    });

    black_pts_notif_ = black_points_.addNotifier([this] () {
                                        if (this->black_points_ > 0) {
                                            this->ui->blackPerformance->setText(
                                                "Black points: " + QString(std::to_string(this->black_points_).c_str()));
                                        } else {
                                            this->ui->blackPerformance->setText(QString());
                                        }
    });

    ui->tableView->setModel(move_dialog_);

    set_interactive_squares();
}

void MainWindow::closeEvent ([[maybe_unused]] QCloseEvent *event) {
    settings_widget_->close();
}

void MainWindow::enableNewGame()
{
    ui->replay->setEnabled(true);
    ui->replay->setStyleSheet("QPushButton {color: #000000}");
}

void MainWindow::disableNewGame()
{
    ui->replay->setEnabled(false);
    ui->replay->setStyleSheet("QPushButton {color: #666666}");
}

void MainWindow::set_interactive_squares()
{
    for (int rank = 1; rank <= 8; rank++) {
        for (int file = 0; file < 8; file++) {
            connect(chessboard_->at(file, rank).get(), &Square::hovered, this, [this, file, rank] () {
                if (this->promoting_ || this->resigned_){
                    this->chessboard_->at(file, rank)->setCursor(QCursor(Qt::ArrowCursor));
                    return;
                }
                std::shared_ptr<Piece> piece_at = this->chessboard_->piece_at(Position(file, rank));
                if ((piece_at.get() != nullptr && piece_at->color() == this->chessboard_->turn()) ||
                    this->chessboard_->at(Position(file, rank))->is_highlighted()) {
                    this->chessboard_->at(file, rank)->setCursor(QCursor(Qt::PointingHandCursor));
                } else {
                    this->chessboard_->at(file, rank)->setCursor(QCursor(Qt::ArrowCursor));
                }
            });

            connect(chessboard_->at(file, rank).get(), &Square::clicked, this, [this, file, rank] () {
                if (this->resigned_)
                    return;
                Position pos(file, rank);
                PieceColor turn = this->chessboard_->turn(), opposite = (PieceColor) ((this->chessboard_->turn() + 1) % 2);
                if (this->promoting_ && this->chessboard_->selected_piece()->tag() == PAWN) {
                    return;
                } else if (this->promoting_){
                    this->promoting_ = false;
                    this->chessboard_->reset_move_highlights();
                }
                if (this->chessboard_->turn() == WHITE &&
                    this->chessboard_->white_pieces()->count(pos) > 0) {
                    // this->chessboard_->at(pos)->setCursor(QCursor(Qt::PointingHandCursor));
                    if (this->chessboard_->selected_piece())
                        this->chessboard_->at(this->chessboard_->selected_piece()->position())->lock_drag();

                    this->chessboard_->select_piece(pos, WHITE);
                    if (!this->chessboard_->selected_piece()->legal_moves().empty())
                        this->chessboard_->at(pos)->unlock_drag();

                } else if (this->chessboard_->turn() == BLACK &&
                           this->chessboard_->black_pieces()->count(pos) > 0) {
                    // this->chessboard_->at(pos)->setCursor(QCursor(Qt::PointingHandCursor));
                    if (this->chessboard_->selected_piece())
                        this->chessboard_->at(this->chessboard_->selected_piece()->position())->lock_drag();
                    this->chessboard_->select_piece(pos, BLACK);

                    if (!this->chessboard_->selected_piece()->legal_moves().empty())
                        this->chessboard_->at(pos)->unlock_drag();

                // MOVING PIECE
                } else if (this->chessboard_->selected_piece().get() != nullptr &&
                           this->chessboard_->at(pos)->is_highlighted()){

                    auto piece = this->chessboard_->selected_piece();
                    std::vector<std::shared_ptr<Piece>> attackers = this->chessboard_->get_attackers(pos, this->chessboard_->turn());
                    bool twin = std::count_if(attackers.begin(), attackers.end(), [&piece] (std::shared_ptr<Piece> &pc) {
                                    return piece.get() != pc.get() && piece->tag() == pc->tag();
                                }) > 0;
                    auto pc_at = this->chessboard_->piece_at(pos);
                    if (pc_at) {
                        QProperty<int> &points = this->chessboard_->turn() == WHITE ? white_points_ : black_points_;
                        points.setValue(pc_at->value() + points.value());
                    }

                    this->chessboard_->move(pos);

                    // CHECKING FOR PROMOTIONS
                    if (this->chessboard_->check_promotion()) {

                        // TURN IS SET TO PREVIOUS! MOVE FUNCTION AUTOMATICALLY SWITCHED IT
                        this->chessboard_->__set_turn(turn);
                        this->promoting_ = true;
                        this->chessboard_->promotion_dialog()->init_promotions(piece->position(), piece);
                        this->chessboard_->promotion_dialog()->list_promotions(piece->position(), ui->chessGrid);

                        auto &pieces = piece->color() == WHITE ? this->chessboard_->white_pieces() : this->chessboard_->black_pieces();
                        for (auto &pair : this->chessboard_->promotion_dialog()->squares()) {
                            PieceTag tag = pair.first;
                            pair.second->setCursor(Qt::PointingHandCursor);
                            pair.second->connect(pair.second.get(), &Square::clicked, this, [this, tag, opposite, &pieces, piece] () {
                                Position p(piece->position());
                                pieces->erase(p);
                                pieces->insert({p, this->chessboard_->promotion_dialog()->pieces().at(tag)});
                                this->chessboard_->at(p)->setPixmap(*pieces->at(p)->pixmap());

                                QProperty<int> &points = opposite == WHITE ? this->white_points_ : this->black_points_;
                                points.setValue(points.value() - pieces->at(p)->value());

                                this->chessboard_->promotion_dialog()->collapse();
                                this->chessboard_->__set_turn(opposite);

                                this->chessboard_->trim_legal_moves();

                                this->promoting_ = false;
                                this->chessboard_->reset_move_highlights();

                                this->mate_.setValue(this->chessboard_->check_for_mate());
                                this->draw_.setValue(this->chessboard_->check_for_draw());

                                Move promotion_move(this->chessboard_->last_move());
                                promotion_move.mate_ = this->mate_.value();
                                promotion_move.check_ = this->chessboard_->scan_checks();
                                promotion_move.promotion_into_ = pieces->at(p);

                                this->move_dialog_->append_move(promotion_move, false);
                                if (!this->mate_.value() && !this->draw_.value() && this->chessboard_->flips_after_move())
                                    this->chessboard_->flip_chessboard();
                            });
                        }
                        this->chessboard_->reset_move_highlights();
                    }
                    // NO PROMOTION
                    else {
                        Move mv(this->chessboard_->last_move());
                        this->chessboard_->reset_move_highlights();
                        this->mate_.setValue(this->chessboard_->check_for_mate());
                        this->draw_.setValue(this->chessboard_->check_for_draw());
                        mv.mate_ = this->mate_.value();
                        mv.check_ = this->chessboard_->scan_checks();
                        this->move_dialog_->append_move(mv, twin);
                        if (!this->mate_.value() && !this->draw_.value() && this->chessboard_->flips_after_move())
                            this->chessboard_->flip_chessboard();


                    }
                    this->chessboard_->at(piece->position())->setCursor(Qt::ArrowCursor);

                } else {
                    this->chessboard_->at(pos)->setCursor(Qt::ArrowCursor);
                    this->chessboard_->reset_move_highlights();

                }
            });
        }
    }
}

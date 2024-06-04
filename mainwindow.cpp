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

#include <QPushButton>
#include <qlabel.h>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainwindow)
{
    ui->setupUi(this);

    int playing_area = this->width() * 0.8;
    int square_length = playing_area / 8;

    // Chessboard init
    chessboard_.reset(new Chessboard(square_length, ui->gridLayout, ui->centralwidget));
    for (int i = 0; i < 10; i++) {
        ui->gridLayout->setColumnMinimumWidth(i, square_length);
    }
    for (int i = 0; i < 12; i++) {
        ui->gridLayout->setRowMinimumHeight(i, square_length);
    }
    // setFixedSize(width(), square_length * 11);

    mate_notifier_ = chessboard_->mate_property()->addNotifier([this] () {
        this->ui->label->setText(this->chessboard_->turn() == WHITE ? "Black wins!" : "White wins!");
        qDebug() << this->ui->label->text();
    });
    draw_notifier_ = chessboard_->draw_property()->addNotifier([this] () {
        this->ui->label->setText("It's a draw!");
        qDebug() << this->ui->label->text();
    });

    for (int rank = 1; rank <= 8; rank++) {
        for (int file = 0; file < 8; file++) {
            connect(chessboard_->at(file, rank).get(), &Square::hovered, this, [this, file, rank] () {
                std::shared_ptr<Piece> piece_at = this->chessboard_->piece_at(Position(file, rank));
                if ((piece_at.get() != nullptr && piece_at->color() == this->chessboard_->turn()) ||
                    this->chessboard_->at(Position(file, rank))->is_highlighted()) {
                    this->chessboard_->at(file, rank)->setCursor(QCursor(Qt::PointingHandCursor));
                } else {
                    this->chessboard_->at(file, rank)->setCursor(QCursor(Qt::ArrowCursor));
                }
            });

            connect(chessboard_->at(file, rank).get(), &Square::clicked, this, [this, file, rank] () {
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
                    this->chessboard_->select_piece(pos, WHITE);

                } else if (this->chessboard_->turn() == BLACK &&
                           this->chessboard_->black_pieces()->count(pos) > 0) {
                    // this->chessboard_->at(pos)->setCursor(QCursor(Qt::PointingHandCursor));
                    this->chessboard_->select_piece(pos, BLACK);

                } else if (this->chessboard_->selected_piece().get() != nullptr &&
                           this->chessboard_->at(pos)->is_highlighted()){

                    auto piece = this->chessboard_->selected_piece();

                    this->chessboard_->move(pos);

                    if (this->chessboard_->check_promotion()) {
                        this->chessboard_->__set_turn(turn);
                        this->promoting_ = true;
                        this->chessboard_->promotion_dialog()->init_promotions(piece->position(), piece);
                        this->chessboard_->promotion_dialog()->list_promotions(piece->position(), ui->gridLayout);

                        auto &pieces = piece->color() == WHITE ? this->chessboard_->white_pieces() : this->chessboard_->black_pieces();
                        for (auto &pair : this->chessboard_->promotion_dialog()->squares()) {
                            PieceTag tag = pair.first;
                            pair.second->setCursor(Qt::PointingHandCursor);
                            pair.second->connect(pair.second.get(), &Square::clicked, this, [this, tag, opposite, &pieces, piece] () {
                                Position p(piece->position());
                                pieces->erase(p);
                                pieces->insert({p, this->chessboard_->promotion_dialog()->pieces().at(tag)});
                                this->chessboard_->at(p)->setPixmap(*pieces->at(p)->pixmap());

                                this->chessboard_->promotion_dialog()->collapse();
                                this->chessboard_->__set_turn(opposite);

                                this->chessboard_->trim_legal_moves();

                                this->promoting_ = false;
                                this->chessboard_->reset_move_highlights();

                                this->chessboard_->check_for_mate();
                                this->chessboard_->check_for_draw();
                            });
                        }
                        this->chessboard_->reset_move_highlights();
                    }
                    else {
                        this->chessboard_->reset_move_highlights();
                        this->chessboard_->check_for_mate();
                        qDebug() << this->chessboard_->mate_property()->value();
                        this->chessboard_->check_for_draw();
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

MainWindow::~MainWindow()
{
    delete ui;
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Chessboard.h>
#include <piece.h>
#include <QMainWindow>
#include <movedialog.h>
#include <drawofferwindow.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class mainwindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::mainwindow *ui;
    QWidget *settings_widget_ = new QWidget;

    std::unique_ptr<DrawOfferWindow> draw_offer_window_;

    MoveDialog *move_dialog_ = new MoveDialog;

    std::unique_ptr<Chessboard> chessboard_;

    std::vector<FEN> position_history_;

    bool promoting_ = false;

    int square_length_;

    int move_count_;

    QProperty<bool> mate_, draw_;
    QPropertyNotifier mate_notifier_, draw_notifier_;

    QProperty<int> white_points_, black_points_;
    QPropertyNotifier white_pts_notif_, black_pts_notif_;

    bool resigned_ = false;

    void enable_buttons();

    void init();

    void set_interactive_squares();

    // MoveDialog move_dialog_;
    void closeEvent(QCloseEvent *event);

    void enableNewGame();

    void disableNewGame();
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Chessboard.h>
#include <piece.h>
#include <QMainWindow>
#include <movedialog.h>
#include <drawofferwindow.h>
#include <SettingsWindow.h>

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

    std::unique_ptr<DrawOfferWindow> draw_offer_window_;
    std::unique_ptr<SettingsWindow> settings_window_;

    MoveDialog *move_dialog_ = new MoveDialog;

    std::unique_ptr<Chessboard> chessboard_;

    std::vector<FEN> position_history_;

    bool promoting_ = false;

    int square_length_;

    int move_count_;

    QPropertyNotifier draw_offer_notif_;
    QPropertyNotifier flip_notif_;

    QProperty<bool> mate_, draw_;
    QPropertyNotifier mate_notifier_, draw_notifier_;

    QProperty<int> white_points_, black_points_;
    QPropertyNotifier white_pts_notif_, black_pts_notif_;

    QPropertyNotifier light_square_changed_, dark_square_changed_, attacking_changed_,
        last_move_changed_, promoting_changed_;

    bool resigned_ = false;

    void enable_buttons();

    void init_settings();

    void init();

    void set_interactive_squares();

    // MoveDialog move_dialog_;
    void closeEvent(QCloseEvent *event);

    void enableNewGame();

    void disableNewGame();
};
#endif // MAINWINDOW_H

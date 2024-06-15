#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Chessboard.h>
#include <piece.h>
#include <QMainWindow>
#include <movedialog.h>

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
    std::vector<Move> white_moves_, black_moves_;

    QStandardItemModel *model_ = new QStandardItemModel;

    std::unique_ptr<Chessboard> chessboard_;

    bool promoting_;

    int move_count_;

    QPropertyNotifier mate_notifier_, draw_notifier_;

    void set_interactive_squares();

    // MoveDialog move_dialog_;
    void closeEvent(QCloseEvent *event);
};
#endif // MAINWINDOW_H

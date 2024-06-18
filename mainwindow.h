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

    MoveDialog *move_dialog_ = new MoveDialog;

    std::unique_ptr<Chessboard> chessboard_;

    std::vector<FEN> position_history_;

    bool promoting_ = false;

    int square_length_;

    int move_count_;

    bool mate_, draw_;

    void set_interactive_squares();

    // MoveDialog move_dialog_;
    void closeEvent(QCloseEvent *event);
};
#endif // MAINWINDOW_H

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

    std::unique_ptr<Chessboard> chessboard_;

    bool promoting_;

    QPropertyNotifier mate_notifier_, draw_notifier_;

    // MoveDialog move_dialog_;
};
#endif // MAINWINDOW_H

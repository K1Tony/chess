#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Chessboard.h>
#include <piece.h>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    std::unique_ptr<Chessboard> chessboard_;

    bool promoting_;
};
#endif // MAINWINDOW_H

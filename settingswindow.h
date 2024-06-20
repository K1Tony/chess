#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include <QProperty>
#include <colordialog.h>
#include <QColorDialog>
#include <QCheckBox>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();

    [[nodiscard]] QProperty<bool> &flip() {return flip_;}

    [[nodiscard]] QProperty<MColor> &light_square() {return light_square_;}

    [[nodiscard]] QProperty<MColor> &dark_square() {return dark_square_;}

    [[nodiscard]] QProperty<MColor> &attacking() {return attacking_;}

    [[nodiscard]] QProperty<MColor> &last_move() {return last_move_;}

    [[nodiscard]] QProperty<MColor> &promoting() {return promoting_;}

private:
    Ui::SettingsWindow *ui;

    QColorDialog dialog_;

    QProperty<bool> flip_;

    QProperty<MColor> light_square_, dark_square_, attacking_, last_move_, promoting_;

    void set_color(QProperty<MColor> &prop);

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // SETTINGSWINDOW_H

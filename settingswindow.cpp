#include "settingswindow.h"
#include "ui_settingswindow.h"

#include <QColorDialog>

SettingsWindow::SettingsWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);

    setWindowTitle("Settings");
    flip_.setValue(true);

    connect(ui->flipOnMove, &QCheckBox::stateChanged, this, [this] () {
        this->flip_.setValue(!this->flip_);
    });

    connect(ui->lightSquare, &QPushButton::clicked, this, [this] () {
        this->set_color(this->light_square_);
    });

    connect(ui->darkSquare, &QPushButton::clicked, this, [this] () {
        this->set_color(this->dark_square_);
    });

    connect(ui->attackingSquare, &QPushButton::clicked, this, [this] () {
        this->set_color(this->attacking_);
    });

    connect(ui->lastSquare, &QPushButton::clicked, this, [this] () {
        this->set_color(this->last_move_);
    });

    connect(ui->promotionSquare, &QPushButton::clicked, this, [this] () {
        this->set_color(this->promoting_);
    });
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::set_color(QProperty<MColor> &prop)
{
    disconnect(&dialog_, &QColorDialog::currentColorChanged, this, nullptr);
    dialog_.setCurrentColor(prop.value());
    connect(&dialog_, &QColorDialog::currentColorChanged, this, [this, &prop] () {
        if (this->dialog_.currentColor().isValid()) {
            prop.setValue(MColor(this->dialog_.currentColor()));
        }
    });
    dialog_.show();
}

void SettingsWindow::closeEvent([[maybe_unused]] QCloseEvent *event)
{
    disconnect(&dialog_, &QColorDialog::currentColorChanged, this, nullptr);
    dialog_.close();
}

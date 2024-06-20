#include "game.h"

#include <QHBoxLayout>

Game::Game() : QGroupBox() {
    name_label_.reset(new QLabel("Blank"));
    action_.reset(new QPushButton("Load"));

    auto layout = new QHBoxLayout(this);
    setLayout(layout);
}

void Game::set_name(const QString &name) {
    name_ = name;
    name_label_->setText(name);
}

#ifndef SQUARE_H
#define SQUARE_H

#include "properties.h"
#include "colordialog.h"
#include "QProperty"

#include <qlabel.h>

class Square : public QLabel
{
    Q_OBJECT
public:
    Square(QWidget *parent = Q_NULLPTR);

    void set_attributes(int rank, File field);

    [[nodiscard]] int rank() const {return rank_;}

    [[nodiscard]] File file() const {return file_;}

    [[nodiscard]] std::string code() {return code_;}

    [[nodiscard]] bool is_highlighted() const {return highlighted_;}

    void set_highlight(bool highlight) {highlighted_ = highlight;}

// members
    MColor background_color() const;
    void set_background_color(const MColor &new_background_color);

private:
    std::string code_;
    int rank_;
    File file_;

    bool highlighted_;

    QProperty<MColor> background_color_ = QProperty<MColor>(MColor(255, 255, 255));
    QPropertyNotifier background_change_notifier_;

// methods
private:
    void set_code();

signals:

    void clicked();

    void hovered();

protected:

    void mousePressEvent([[maybe_unused]] QMouseEvent *event);

    void enterEvent([[maybe_unused]] QEnterEvent *event);

public slots:

    void highlight(const QString &color);
};

#endif // SQUARE_H

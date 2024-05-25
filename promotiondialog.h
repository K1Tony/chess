#ifndef PROMOTIONDIALOG_H
#define PROMOTIONDIALOG_H

#include "QGridLayout"
#include "piece.h"
#include "square.h"

class PromotionDialog
{
public:
    PromotionDialog(QWidget *parent);

    [[nodiscard]] std::map<PieceTag, std::unique_ptr<Square> > &squares() {return squares_;}

    void init_promotions(const Position &promotion_square);

    void list_promotions(const Position &promotion_square, QGridLayout *layout);

private:

    std::map<PieceTag, std::unique_ptr<Piece> > pieces_;
    std::map<PieceTag, std::unique_ptr<Square> > squares_;
};

#endif // PROMOTIONDIALOG_H

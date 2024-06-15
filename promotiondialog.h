#ifndef PROMOTIONDIALOG_H
#define PROMOTIONDIALOG_H

#include "QGridLayout"
#include "piece.h"
#include "square.h"

class PromotionDialog
{
public:
    PromotionDialog(QWidget *parent = Q_NULLPTR);

    [[nodiscard]] std::map<PieceTag, std::unique_ptr<Square> > &squares() {return squares_;}

    [[nodiscard]] std::map<PieceTag, std::shared_ptr<Piece> > &pieces() {return pieces_;}

    void init_promotions(const Position &promotion_square, std::shared_ptr<Piece> &pawn);

    void list_promotions(const Position &promotion_square, QGridLayout *layout);

    void collapse();


private:

    std::map<PieceTag, std::shared_ptr<Piece> > pieces_;
    std::map<PieceTag, std::unique_ptr<Square> > squares_;

    std::shared_ptr<Piece> pawn_;
};

#endif // PROMOTIONDIALOG_H

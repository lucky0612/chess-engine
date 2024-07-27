#pragma once

#include "types.h"

namespace ChessEngine {

class Move {
public:
    Move() : from_(Square::NONE), to_(Square::NONE), promotion_(PieceType::NONE) {}
    Move(Square from, Square to, PieceType promotion = PieceType::NONE)
        : from_(from), to_(to), promotion_(promotion) {}

    Square getFrom() const { return from_; }
    Square getTo() const { return to_; }
    PieceType getPromotion() const { return promotion_; }

    bool isNull() const { return from_ == Square::NONE && to_ == Square::NONE; }

private:
    Square from_;
    Square to_;
    PieceType promotion_;
};

} // namespace ChessEngine
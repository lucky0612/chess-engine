#pragma once

#include "types.h"

namespace ChessEngine {

class Piece {
public:
    Piece() : type_(PieceType::NONE), color_(Color::WHITE) {}
    Piece(PieceType type, Color color) : type_(type), color_(color) {}

    PieceType getType() const { return type_; }
    Color getColor() const { return color_; }

    bool isNone() const { return type_ == PieceType::NONE; }

private:
    PieceType type_;
    Color color_;
};

} // namespace ChessEngine
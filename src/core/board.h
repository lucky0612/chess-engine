#pragma once

#include "types.h"
#include "piece.h"
#include "move.h"
#include <array>
#include <vector>

namespace ChessEngine {

class Board {
public:
    Board();
    void resetToStartingPosition();
    Piece getPiece(Square square) const;
    void setPiece(Square square, Piece piece);
    bool isSquareAttacked(Square square, Color attackingColor) const;
    std::vector<Move> generateLegalMoves() const;
    bool makeMove(const Move& move);
    void undoMove(const Move& move);
    bool isInCheck(Color color) const;
    bool isCheckmate() const;
    bool isStalemate() const;

private:
    std::array<Piece, 64> pieces_;
    Color sideToMove_;
    Bitboard pieceBitboards_[6][2];  // [PieceType][Color]
    Bitboard occupiedBitboard_;
    // Add more member variables as needed (e.g., for castling rights, en passant square, etc.)

    // Helper functions
    void updateBitboards();
    std::vector<Move> generatePseudoLegalMoves() const;
    bool isLegalMove(const Move& move) const;
};

} // namespace ChessEngine
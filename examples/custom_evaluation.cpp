#include <iostream>
#include "../src/core/board.h"
#include "../src/engine/evaluation.h"

class CustomEvaluation : public AdaptiveNN
{
public:
    float evaluate(const Board &board) override
    {
        // Simple material counting evaluation
        float score = 0.0f;
        for (int sq = 0; sq < 64; ++sq)
        {
            Piece piece = board.getPiece(Square(sq));
            switch (piece)
            {
            case Piece::WHITE_PAWN:
                score += 1.0f;
                break;
            case Piece::WHITE_KNIGHT:
                score += 3.0f;
                break;
            case Piece::WHITE_BISHOP:
                score += 3.0f;
                break;
            case Piece::WHITE_ROOK:
                score += 5.0f;
                break;
            case Piece::WHITE_QUEEN:
                score += 9.0f;
                break;
            case Piece::BLACK_PAWN:
                score -= 1.0f;
                break;
            case Piece::BLACK_KNIGHT:
                score -= 3.0f;
                break;
            case Piece::BLACK_BISHOP:
                score -= 3.0f;
                break;
            case Piece::BLACK_ROOK:
                score -= 5.0f;
                break;
            case Piece::BLACK_QUEEN:
                score -= 9.0f;
                break;
            default:
                break;
            }
        }
        return score;
    }
};

int main()
{
    Board board;
    CustomEvaluation eval;

    std::cout << "Starting position evaluation: " << eval.evaluate(board) << std::endl;

    // Make a move
    board.makeMove(Move(Square::E2, Square::E4));
    std::cout << "Evaluation after 1.e4: " << eval.evaluate(board) << std::endl;

    return 0;
}
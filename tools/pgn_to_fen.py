import chess
import chess.pgn
import sys

def pgn_to_fen(pgn_file):
    with open(pgn_file) as f:
        while True:
            game = chess.pgn.read_game(f)
            if game is None:
                break
            
            board = game.board()
            for move in game.mainline_moves():
                board.push(move)
                print(board.fen())

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python pgn_to_fen.py <pgn_file>")
        sys.exit(1)
    
    pgn_file = sys.argv[1]
    pgn_to_fen(pgn_file)
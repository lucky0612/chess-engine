import math
import sys

def calculate_elo_change(rating_a, rating_b, score_a, k_factor=32):
    expected_a = 1 / (1 + 10 ** ((rating_b - rating_a) / 400))
    change = k_factor * (score_a - expected_a)
    return change

def main():
    if len(sys.argv) != 4:
        print("Usage: python elo_calculator.py <rating_a> <rating_b> <score_a>")
        sys.exit(1)

    rating_a = float(sys.argv[1])
    rating_b = float(sys.argv[2])
    score_a = float(sys.argv[3])

    elo_change = calculate_elo_change(rating_a, rating_b, score_a)

    print(f"Player A's rating change: {elo_change:.2f}")
    print(f"Player B's rating change: {-elo_change:.2f}")
    print(f"Player A's new rating: {rating_a + elo_change:.2f}")
    print(f"Player B's new rating: {rating_b - elo_change:.2f}")

if __name__ == "__main__":
    main()
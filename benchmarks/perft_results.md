# Perft Results

This document contains the results of performance tests (perft) for our chess engine.

## Starting Position

| Depth | Nodes      | Time (ms) | NPS        |
|-------|------------|-----------|------------|
| 1     | 20         | 0.1       | 200,000    |
| 2     | 400        | 0.5       | 800,000    |
| 3     | 8,902      | 2         | 4,451,000  |
| 4     | 197,281    | 30        | 6,576,033  |
| 5     | 4,865,609  | 750       | 6,487,478  |
| 6     | 119,060,324| 18,500    | 6,435,693  |

## Position 2: After 1.e4 e5

| Depth | Nodes      | Time (ms) | NPS        |
|-------|------------|-----------|------------|
| 1     | 29         | 0.1       | 290,000    |
| 2     | 841        | 0.8       | 1,051,250  |
| 3     | 23,527     | 4         | 5,881,750  |
| 4     | 657,834    | 80        | 8,222,925  |
| 5     | 18,412,964 | 2,200     | 8,369,529  |

These results were obtained on a system with the following specifications:
- CPU: Intel Core i7-9700K @ 3.60GHz
- RAM: 32GB DDR4
- OS: Ubuntu 20.04 LTS
#pragma once

#include "../core/board.h"
#include <vector>
#include <random>

namespace ChessEngine
{

    class NeuralNetwork
    {
    public:
        NeuralNetwork(const std::vector<int> &layerSizes);
        float evaluate(const Board &board);
        void train(const std::vector<std::pair<Board, float>> &trainingData, int epochs, float learningRate);
        void saveWeights(const std::string &filename) const;
        void loadWeights(const std::string &filename);

    private:
        std::vector<std::vector<std::vector<float>>> weights;
        std::vector<std::vector<float>> biases;
        std::mt19937 rng;

        std::vector<float> boardToInput(const Board &board) const;
        float activate(float x) const;
        float activateDerivative(float x) const;
        std::vector<float> forwardPropagate(const std::vector<float> &input);
        void backPropagate(const std::vector<float> &input, float target, float learningRate);
    };

} // namespace ChessEngine
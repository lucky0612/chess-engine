#include "neuralnet.h"
#include <cmath>
#include <fstream>
#include <algorithm>

namespace ChessEngine
{

    NeuralNetwork::NeuralNetwork(const std::vector<int> &layerSizes) : rng(std::random_device{}())
    {
        for (size_t i = 1; i < layerSizes.size(); ++i)
        {
            weights.push_back(std::vector<std::vector<float>>(layerSizes[i], std::vector<float>(layerSizes[i - 1])));
            biases.push_back(std::vector<float>(layerSizes[i]));

            std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
            for (auto &neuron : weights.back())
            {
                for (float &weight : neuron)
                {
                    weight = dist(rng);
                }
            }
            for (float &bias : biases.back())
            {
                bias = dist(rng);
            }
        }
    }

    float NeuralNetwork::evaluate(const Board &board)
    {
        std::vector<float> input = boardToInput(board);
        std::vector<float> output = forwardPropagate(input);
        return output[0]; // Assuming the output layer has only one neuron
    }

    void NeuralNetwork::train(const std::vector<std::pair<Board, float>> &trainingData, int epochs, float learningRate)
    {
        for (int epoch = 0; epoch < epochs; ++epoch)
        {
            for (const auto &[board, target] : trainingData)
            {
                std::vector<float> input = boardToInput(board);
                backPropagate(input, target, learningRate);
            }
        }
    }

    std::vector<float> NeuralNetwork::boardToInput(const Board &board) const
    {
        // Convert board state to neural network input
        // This is a placeholder implementation
        std::vector<float> input(64 * 12, 0.0f); // 64 squares, 12 piece types (6 pieces * 2 colors)
        // TODO: Implement actual board to input conversion
        return input;
    }

    float NeuralNetwork::activate(float x) const
    {
        return 1.0f / (1.0f + std::exp(-x)); // Sigmoid activation
    }

    float NeuralNetwork::activateDerivative(float x) const
    {
        float sigmoid = activate(x);
        return sigmoid * (1 - sigmoid);
    }

    std::vector<float> NeuralNetwork::forwardPropagate(const std::vector<float> &input)
    {
        std::vector<float> layerOutput = input;
        for (size_t layer = 0; layer < weights.size(); ++layer)
        {
            std::vector<float> newOutput(weights[layer].size());
            for (size_t neuron = 0; neuron < weights[layer].size(); ++neuron)
            {
                float sum = 0.0f;
                for (size_t prevNeuron = 0; prevNeuron < weights[layer][neuron].size(); ++prevNeuron)
                {
                    sum += weights[layer][neuron][prevNeuron] * layerOutput[prevNeuron];
                }
                sum += biases[layer][neuron];
                newOutput[neuron] = activate(sum);
            }
            layerOutput = std::move(newOutput);
        }
        return layerOutput;
    }

    void NeuralNetwork::backPropagate(const std::vector<float> &input, float target, float learningRate)
    {
        // Forward pass
        std::vector<std::vector<float>> layerOutputs = {input};
        for (size_t layer = 0; layer < weights.size(); ++layer)
        {
            std::vector<float> newOutput(weights[layer].size());
            for (size_t neuron = 0; neuron < weights[layer].size(); ++neuron)
            {
                float sum = 0.0f;
                for (size_t prevNeuron = 0; prevNeuron < weights[layer][neuron].size(); ++prevNeuron)
                {
                    sum += weights[layer][neuron][prevNeuron] * layerOutputs.back()[prevNeuron];
                }
                sum += biases[layer][neuron];
                newOutput[neuron] = activate(sum);
            }
            layerOutputs.push_back(std::move(newOutput));
        }

        // Backward pass
        std::vector<std::vector<float>> deltas(weights.size());
        for (int layer = weights.size() - 1; layer >= 0; --layer)
        {
            deltas[layer].resize(weights[layer].size());
            for (size_t neuron = 0; neuron < weights[layer].size(); ++neuron)
            {
                float error = (layer == weights.size() - 1) ? (target - layerOutputs.back()[neuron]) : 0.0f;
                if (layer < weights.size() - 1)
                {
                    for (size_t nextNeuron = 0; nextNeuron < weights[layer + 1].size(); ++nextNeuron)
                    {
                        error += weights[layer + 1][nextNeuron][neuron] * deltas[layer + 1][nextNeuron];
                    }
                }
                deltas[layer][neuron] = error * activateDerivative(layerOutputs[layer + 1][neuron]);
            }
        }

        // Update weights and biases
        for (size_t layer = 0; layer < weights.size(); ++layer)
        {
            for (size_t neuron = 0; neuron < weights[layer].size(); ++neuron)
            {
                for (size_t prevNeuron = 0; prevNeuron < weights[layer][neuron].size(); ++prevNeuron)
                {
                    weights[layer][neuron][prevNeuron] += learningRate * deltas[layer][neuron] * layerOutputs[layer][prevNeuron];
                }
                biases[layer][neuron] += learningRate * deltas[layer][neuron];
            }
        }
    }

    void NeuralNetwork::saveWeights(const std::string &filename) const
    {
        std::ofstream file(filename, std::ios::binary);
        if (!file)
        {
            throw std::runtime_error("Could not open file for writing: " + filename);
        }

        for (const auto &layer : weights)
        {
            for (const auto &neuron : layer)
            {
                file.write(reinterpret_cast<const char *>(neuron.data()), neuron.size() * sizeof(float));
            }
        }

        for (const auto &layer : biases)
        {
            file.write(reinterpret_cast<const char *>(layer.data()), layer.size() * sizeof(float));
        }
    }

    void NeuralNetwork::loadWeights(const std::string &filename)
    {
        std::ifstream file(filename, std::ios::binary);
        if (!file)
        {
            throw std::runtime_error("Could not open file for reading: " + filename);
        }

        for (auto &layer : weights)
        {
            for (auto &neuron : layer)
            {
                file.read(reinterpret_cast<char *>(neuron.data()), neuron.size() * sizeof(float));
            }
        }

        for (auto &layer : biases)
        {
            file.read(reinterpret_cast<char *>(layer.data()), layer.size() * sizeof(float));
        }
    }

} // namespace ChessEngine
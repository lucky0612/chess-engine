#pragma once

#include "neuralnet.h"
#include <vector>

namespace ChessEngine
{

    class GeneticAlgorithm
    {
    public:
        GeneticAlgorithm(int populationSize, float mutationRate);
        NeuralNetwork evolve(int generations);

    private:
        int populationSize;
        float mutationRate;
        std::vector<NeuralNetwork> population;

        void initializePopulation();
        std::vector<float> evaluatePopulation();
        std::vector<NeuralNetwork> selection(const std::vector<float> &fitness);
        NeuralNetwork crossover(const NeuralNetwork &parent1, const NeuralNetwork &parent2);
        void mutate(NeuralNetwork &individual);
    };

} // namespace ChessEngine
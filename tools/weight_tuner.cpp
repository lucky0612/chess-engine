#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "../src/ai/neuralnet.h"
#include "../src/core/board.h"

class WeightTuner
{
public:
    WeightTuner(AdaptiveNN &nn) : nn(nn) {}

    void tune(const std::vector<std::pair<Board, float>> &trainingData, int generations, int populationSize)
    {
        std::vector<std::vector<float>> population = initializePopulation(populationSize);

        for (int gen = 0; gen < generations; ++gen)
        {
            std::vector<float> fitnesses = evaluatePopulation(population, trainingData);
            std::vector<std::vector<float>> newPopulation = selection(population, fitnesses);
            crossover(newPopulation);
            mutate(newPopulation);
            population = newPopulation;

            std::cout << "Generation " << gen << " best fitness: " << *std::max_element(fitnesses.begin(), fitnesses.end()) << std::endl;
        }

        std::vector<float> bestWeights = population[0]; // Assuming the best is at index 0 after sorting
        nn.setWeights(bestWeights);
    }

private:
    AdaptiveNN &nn;
    std::mt19937 gen{std::random_device{}()};

    std::vector<std::vector<float>> initializePopulation(int size)
    {
        std::vector<std::vector<float>> population(size);
        std::uniform_real_distribution<> dis(-1.0, 1.0);
        for (auto &individual : population)
        {
            individual = std::vector<float>(nn.getWeightCount());
            for (auto &weight : individual)
            {
                weight = dis(gen);
            }
        }
        return population;
    }

    std::vector<float> evaluatePopulation(const std::vector<std::vector<float>> &population,
                                          const std::vector<std::pair<Board, float>> &trainingData)
    {
        std::vector<float> fitnesses(population.size());
        for (size_t i = 0; i < population.size(); ++i)
        {
            nn.setWeights(population[i]);
            float fitness = 0.0f;
            for (const auto &[board, expectedEval] : trainingData)
            {
                float eval = nn.evaluate(board);
                fitness -= std::abs(eval - expectedEval); // Negative because lower error is better
            }
            fitnesses[i] = fitness;
        }
        return fitnesses;
    }

    std::vector<std::vector<float>> selection(std::vector<std::vector<float>> &population, const std::vector<float> &fitnesses)
    {
        std::vector<size_t> indices(population.size());
        std::iota(indices.begin(), indices.end(), 0);
        std::sort(indices.begin(), indices.end(),
                  [&fitnesses](size_t a, size_t b)
                  { return fitnesses[a] > fitnesses[b]; });

        std::vector<std::vector<float>> selected;
        for (size_t i = 0; i < population.size() / 2; ++i)
        {
            selected.push_back(population[indices[i]]);
        }
        return selected;
    }

    void crossover(std::vector<std::vector<float>> &population)
    {
        std::uniform_int_distribution<> dis(0, population[0].size() - 1);
        for (size_t i = 1; i < population.size(); i += 2)
        {
            size_t crossoverPoint = dis(gen);
            for (size_t j = crossoverPoint; j < population[i].size(); ++j)
            {
                std::swap(population[i][j], population[i - 1][j]);
            }
        }
    }

    void mutate(std::vector<std::vector<float>> &population)
    {
        std::uniform_real_distribution<> dis(-0.1, 0.1);
        for (auto &individual : population)
        {
            for (auto &weight : individual)
            {
                if (std::uniform_real_distribution<>(0, 1)(gen) < 0.01)
                { // 1% mutation rate
                    weight += dis(gen);
                }
            }
        }
    }
};

int main()
{
    AdaptiveNN nn;
    WeightTuner tuner(nn);

    // Generate some dummy training data
    std::vector<std::pair<Board, float>> trainingData;
    for (int i = 0; i < 1000; ++i)
    {
        Board board;
        // Set up some random position
        float expectedEval = std::uniform_real_distribution<>(-1.0, 1.0)(std::mt19937{std::random_device{}()});
        trainingData.emplace_back(board, expectedEval);
    }

    tuner.tune(trainingData, 100, 100); // 100 generations, population size 100

    std::cout << "Weight tuning completed." << std::endl;
    return 0;
}
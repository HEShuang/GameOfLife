#include "BenchMark.h"
#include "io/BoardSerializer.h"

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <numeric>   // For std::accumulate
#include <algorithm> // For std::sort
#include <filesystem> // For std::filesystem::file_size and std::filesystem::remove
#include <iomanip>    // For std::setw

void BenchMark::populationCapacity() {

    //Populates a game board with a given number of population randomly distributed,
    //so that the population can be fixed
    auto populateGame = [](GameBenchmark& game, size_t nPopulation) {

        if (nPopulation == 0)
            return;

        int dimension = static_cast<int>(sqrt(static_cast<double>(nPopulation) * 2.0));
        std::mt19937 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> distrib(-dimension / 2, dimension / 2);
        std::set<Point> aliveCells;
        while (aliveCells.size() < nPopulation) {
            aliveCells.insert({distrib(rng), distrib(rng)});
        }
        game.setState(aliveCells);
    };

    // Define the different population sizes to test
    const std::vector<size_t> populationTargets = {
        100000, 250000, 500000, 750000, 1000000, 1250000, 1500000
    };

    const int nSamples = 1;

    std::cout << "Starting high-precision performance benchmark..." << std::endl;
    std::cout << "------------------------------------------------------------------" << std::endl;
    std::cout << "Population | Avg Time (ms) |Min Time (ms) | Max Time (ms)" << std::endl;
    std::cout << "------------------------------------------------------------------" << std::endl;

    for (const auto& nPopulation : populationTargets) {
        std::vector<double> timings_ms;
        timings_ms.reserve(nSamples);

        for (int i = 0; i < nSamples; ++i) {
            // Create a fresh board with the exact population for each sample.
            GameBenchmark game;
            populateGame(game, nPopulation);

            // Time a single generation.
            auto startTime = std::chrono::high_resolution_clock::now();
            game.nextGeneration();
            auto endTime = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
            timings_ms.push_back(duration.count());
        }

        // Calculate statistics for this population size.
        double sum = std::accumulate(timings_ms.begin(), timings_ms.end(), 0.0);
        double average = sum / nSamples;

        std::sort(timings_ms.begin(), timings_ms.end());
        double min_val = timings_ms.front();
        double max_val = timings_ms.back();

        std::cout << nPopulation << "\t\t" << average << "\t\t" << min_val << "\t\t" << max_val << std::endl;
    }

    std::cout << "------------------------------------------------------------------" << std::endl;
    std::cout << "Benchmark complete." << std::endl;
}

void BenchMark::boardCapacity() {

    auto populateBoardCorners = [](int dimension) -> std::set<Point> {
        if (dimension <= 0) return {};
        int d = dimension - 1;
        return {
            {0, 0}, {d, 0}, {0, d}, {d, d}
        };
    };

    const std::vector<int> dimensionTargets = {
        1000, 2000, 3000, 4000, 5000, 6000, 8000, 10000, 15000, 20000
    };

    const std::string tempFile = "benchmark_temp_save.txt";

    std::cout << "Starting Dense Save Benchmark (Dimension vs. File Size & Time)..." << std::endl;
    std::cout << "---------------------------------------------------------------------" << std::endl;
    std::cout << std::left << std::setw(15) << "Dimension"
              << std::left << std::setw(20) << "File Size (MB)"
              << std::left << std::setw(20) << "Save Time (ms)" << std::endl;
    std::cout << "---------------------------------------------------------------------" << std::endl;

    for (const auto& dim : dimensionTargets) {
        // Create the cell set that defines the bounding box.
        std::set<Point> aliveCells = populateBoardCorners(dim);
        BBox bbox;
        bbox.compute(aliveCells);

        // Time the save operation.
        auto startTime = std::chrono::high_resolution_clock::now();
        bool success = BoardSerializer::saveDense(tempFile, aliveCells, bbox);
        auto endTime = std::chrono::high_resolution_clock::now();

        if (!success) {
            std::cerr << "Failed to save for dimension " << dim << std::endl;
            std::filesystem::remove(tempFile);
            continue;
        }

        // Get file size and duration.
        auto fileSizeBytes = std::filesystem::file_size(tempFile);
        double fileSizeMb = static_cast<double>(fileSizeBytes) / (1024.0 * 1024.0);
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

        std::cout << std::left << std::setw(15) << (std::to_string(dim) + "x" + std::to_string(dim))
                  << std::left << std::setw(20) << fileSizeMb
                  << std::left << std::setw(20) << duration << std::endl;

        std::filesystem::remove(tempFile);
    }

    std::cout << "---------------------------------------------------------------------" << std::endl;
    std::cout << "Benchmark complete." << std::endl;

}

#include "GameController.h"
#include "core/GameOfLife.h"
#include "core/Exceptions.h"
#include "io/BoardSerializer.h"

#include <iostream>
#include <filesystem>
#include <chrono>
#include <thread>

GameController::GameController(int argc, char* argv[], std::unique_ptr<RenderInterface> renderer) :
    m_renderer(std::move(renderer))
{
    m_sProgName = argv[0];
    for (int i = 1; i < argc; ++i) {
        m_args.emplace_back(argv[i]);
    }
}

int GameController::run() {

    if (!parseArguments()) {
        printManual();
        return 1;
    }

    //Validate arguments
    if (m_sInputFile.empty()) {
        std::cerr << "Error: input file can not be empty.\n";
        printManual();
        return 1;
    }

    if (m_nIterations <= 0) {
        std::cerr << "Error: iterations must be a positive integer.\n";
        printManual();
        return 1;
    }

    //Create game
    auto upGame = std::unique_ptr<GameOfLife>(new GameOfLife);
    if (!BoardSerializer::load(m_sInputFile, upGame->aliveCells)) {
        std::cerr << "Error: Failed to initialize board from file: " << m_sInputFile << std::endl;
        return 1;
    }

    //Set MAX_ALIVE_CELLS of game
    if (m_maxPopulation > 0) {
        GameOfLife::MAX_ALIVE_CELLS = m_maxPopulation;
    }

    //Init render view based on terminal size
    m_renderer->initView(upGame);

    if (m_bPrintAll) {
        m_renderer->clear();
        std::cout << "--- Inital board ---\n";
        m_renderer->render(upGame);
        std::this_thread::sleep_for(std::chrono::milliseconds(m_msSleep));
    }

    int i = 0;

    //Start profiling
    auto startTime = std::chrono::high_resolution_clock::now();
    //Launch game
    try {
        for(; i < m_nIterations; ++i) {
            upGame->nextGeneration();
            if (m_bPrintAll) {
                m_renderer->clear();
                std::cout << "---Generation " << i+1 << "----\n";
                m_renderer->render(upGame);
                std::this_thread::sleep_for(std::chrono::milliseconds(m_msSleep));
            }
        }
    } catch (const CapacityException& e) {
        std::cout << "CapacityException: " << e.what() << std::endl;
    } catch (std::exception& e) {
        std::cout << "Error during generation: " << e.what() << std::endl;
        return 1;
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    if (!m_bPrintAll) {
        std::cout << "---Last state (Generation " << i + 1 << ")----\n";
        m_renderer->render(upGame);
    }

    std::string outFilePath = generateOutputFilePath();
    if (!BoardSerializer::save(outFilePath, upGame->aliveCells) ) {
        std::cerr << "Error saving final board state to " << outFilePath << std::endl;
        return 1;
    }

    std::cout << "Total game time: " << duration.count() << " ms" << std::endl;
    return 0; //Succes
}

bool GameController::parseArguments() {
    //Parse command line arguments

    if (m_args.empty()) {
        std::cerr << "Error: --input is mandatory.\n";
        return false;
    }

    int nArgs = m_args.size();
    for (int i = 0; i < nArgs; ++i) {

        auto arg = m_args[i];
        if ( arg == "--input") {

            if (i + 1 < nArgs) {
                m_sInputFile = m_args[++i];
            }
            else {
                std::cerr << "Error: --input requires a file path.\n";
                return false;
            }
        }

        else if (arg == "--iterations") {

            if (i + 1 < nArgs) {
                try {
                    m_nIterations = std::stoi(m_args[++i]);
                    if (m_nIterations <= 0) {
                        std::cerr << "Error: --iterations value must > 0.\n";
                        return false;
                    }
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Error: --iterations value must be an integer.\n";
                    return false;
                } catch (const std::out_of_range& e) {
                    std::cerr << "Error: --iterations value is out of range.\n";
                    return false;
                }
            }
            else {
                std::cerr << "Error: --iterations requires a number.\n";
                return false;
            }
        }

        else if (arg == "--all") {
            m_bPrintAll = true;
        }

        else if (arg == "--sleep") {

            if (i + 1 < nArgs) {
                try {
                    m_msSleep = std::stoi(m_args[++i]);
                    if (m_msSleep < 0) {
                        std::cerr << "Error: --sleep value must >= 0.\n";
                        return false;
                    }
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Error: --sleep value must be an integer.\n";
                    return false;
                } catch (const std::out_of_range& e) {
                    std::cerr << "Error: --sleep value is out of range.\n";
                    return false;
                }
            }
            else {
                std::cerr << "Error: --sleep requires a number.\n";
                return false;
            }
        }

        else if (arg == "--maxPopulation") {

            if (i + 1 < nArgs) {
                try {
                    m_maxPopulation = std::stoi(m_args[++i]);
                    if (m_maxPopulation < 0) {
                        std::cerr << "Error: --maxPopulation value must >= 0.\n";
                        return false;
                    }
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Error: --maxPopulation value must be an integer.\n";
                    return false;
                } catch (const std::out_of_range& e) {
                    std::cerr << "Error: --maxPopulation value is out of range.\n";
                    return false;
                }
            }
            else {
                std::cerr << "Error: --maxPopulation requires a number.\n";
                return false;
            }
        }

        else {
            std::cerr << "Error: Unknown argument '" << arg << "'\n";
            return false;
        }
    }
    return true;
}

void GameController::printManual() const {
    std::cerr << "\nUsage: " << m_sProgName << " --input <filepath> [--iterations <number>] [--all] [--sleep <time>] \n"
              << "Parameters:\n"
              << "  --input <filepath>    : Mandatory. Path to the initial board file.\n"
              << "  --iterations <number> : Default 100. A positive integer for the number of iterations.\n"
              << "  --all                 : Optional. If present, all iterations are printed. Otherwise, only the last one is printed\n"
              << "  --sleep               : Default 0. A positive integer in millisecond for sleep time between print of two generation\n"
              << "  --maxPopulation       : Defualt is 2 million. A positive integer for population limit\n\n";

}

std::string GameController::generateOutputFilePath() const {

    std::filesystem::path inputPath(m_sInputFile);

    auto dir = inputPath.parent_path();
    auto stem = inputPath.stem().string();
    auto ext = inputPath.extension().string();

    auto newFilename = stem + "_" + std::to_string(m_nIterations) + ext;

    return (dir / newFilename).string();
}

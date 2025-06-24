/* =====================================================================================
 *
 * Filename:  GameController.h
 *
 * Description:  The main application class that manages the application's lifecycle.
 *
 * =====================================================================================
 */

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <memory>
#include <vector>
#include <string>

#include "render/RenderInterface.h"
#include "render/RenderConsole.h"

/**
 * @class GameController
 * @brief Manages the overall application flow.
 *
 * This class is responsible for parsing command-line arguments, setting up the
 * game simulation, running the main loop, and coordinating between the game engine, renderer, and serializer.
 */
class GameController
{
public:
    /**
     * @brief Constructs the GameController.
     * @param argc The argument count from main().
     * @param argv The argument vector from main().
     *
     * Syntax : --input <filepath> --iterations <number> [--all]
     * --input : (Required) Path to a board file. The format should use * for live cells and _ for dead cells.
     * --iterations : (Default: 100) The number of generations to simulate.
     * --all: (Optional) If present, render every generation state to the console.
     * --sleep: (Optional, default: 0) The sleep time between rendering two generations, for controlling animation speed.
     *
     * @param renderer A unique_ptr to a renderer implementation. Defaults to RenderConsole.
     */
    GameController(int argc, char* argv[]
                   , std::unique_ptr<RenderInterface> renderer = std::make_unique<RenderConsole>());

    /**
     * @brief Executes the main application logic.
     * @return An exit code (0 for success, non-zero for failure).
     */
    int run();

private:
    bool parseArguments();
    bool validateArguments() const;
    void printManual() const;
    std::string generateOutputFilePath() const;

    std::vector<std::string> m_args;
    std::string m_sProgName;
    std::string m_sInputFile;
    int m_nIterations = 100;
    bool m_bPrintAll = false;
    std::unique_ptr<RenderInterface> m_renderer = nullptr;
    int m_msSleep = 0; //sleep time between each render in milliseconds
};

#endif // GAMECONTROLLER_H

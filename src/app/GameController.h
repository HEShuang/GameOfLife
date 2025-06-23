#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <memory>
#include <vector>
#include <string>

#include "render/RenderInterface.h"
#include "render/RenderConsole.h"

class GameController
{
public:
    //Takes the command line arguments from main and a renderer, which by default is console
    GameController(int argc, char* argv[]
                   , std::unique_ptr<RenderInterface> renderer = std::make_unique<RenderConsole>());

    //Return 0 for success, non-zero for failure
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
    int m_msSleep = 100; //sleep time between each render in ms
};

#endif // GAMECONTROLLER_H

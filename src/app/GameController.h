#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <vector>
#include <string>

class GameController
{
public:
    //Takes the command line arguments from main
    GameController(int argc, char* argv[]);

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
};

#endif // GAMECONTROLLER_H

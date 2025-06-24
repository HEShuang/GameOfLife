#include "GameController.h"

#ifdef _WIN32
#include <windows.h>
//This will make the Windows console process ANSI escape codes like macOS and linux
void enableVirtualTerminalProcessing() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#endif


/**
 * @brief The main function for the Game of Life application.
 *
 * Its sole responsibility is to instantiate the GameController and
 * execute its run() method, returning its exit code.
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line argument strings.
 * @return The application's exit code.
 */

int main(int argc, char* argv[])
{
#ifdef _WIN32
    enableVirtualTerminalProcessing();
#endif

    GameController controller(argc, argv);
    return controller.run();
}

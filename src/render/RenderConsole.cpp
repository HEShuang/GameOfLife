#include "RenderConsole.h"
#include "core/BBox.h"
#include "core/GameOfLife.h"

#include <iostream>

#ifdef _WIN32 //works on 32-bit and 64-bit
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

void RenderConsole::initView(const std::unique_ptr<GameOfLife>& upGame) {

    int width = 200, height = 60;

    // Get terminal size
#ifdef _WIN32
    // This uses the Windows API, which works on 32-bit and 64-bit.
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
    // This uses the POSIX API (ioctl), which works on Linux and macOS.
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    width = size.ws_col;
    height = size.ws_row - 4;// Use a slightly smaller height to leave room for prompts
#endif

    const auto& aliveCells = upGame->getAliveCells();
    if (aliveCells.empty()) {
        m_viewBox.minX = 0;
        m_viewBox.maxX = width - 1;
        m_viewBox.minY = 0;
        m_viewBox.maxY = height - 1;
        return;
    }

    BBox bbox;
    bbox.compute(aliveCells);

    // Define the viewport boundaries centered around the pattern
    m_viewBox.minX = bbox.center.x - (width / 2);
    m_viewBox.maxX = m_viewBox.minX + width - 1;
    m_viewBox.minY = bbox.center.y - (height / 2);
    m_viewBox.maxY = m_viewBox.minY + height - 1;
}

void RenderConsole::render(const std::unique_ptr<GameOfLife>& upGame) {

    const auto& aliveCells = upGame->getAliveCells();

    std::string frame_buffer;
    frame_buffer.reserve((m_viewBox.maxX - m_viewBox.minX + 1) * (m_viewBox.maxY - m_viewBox.minY + 1));

    for (int y = m_viewBox.minY; y <= m_viewBox.maxY; ++y) {
        for (int x = m_viewBox.minX; x <= m_viewBox.maxX; ++x) {
            if (aliveCells.count({x, y})) {
                frame_buffer += '*';
            } else {
                frame_buffer += ' ';
            }
        }
        frame_buffer += '\n';
    }
    m_outStream << frame_buffer << std::flush;    // Print the entire frame at once
}


void RenderConsole::clear() {
#ifdef _WIN32
    // A more advanced Windows-specific method that reduces flicker.
    // It gets the console handle and fills the screen with spaces.
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    DWORD count;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hStdOut, &csbi);
    FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
    SetConsoleCursorPosition(hStdOut, coord);
#else
    // for Linux/macOS using ANSI escape codes.
    // \033[2J clears the screen, \033[H moves the cursor to the top-left.
    std::cout << "\033[2J\033[H" << std::flush;
#endif

}

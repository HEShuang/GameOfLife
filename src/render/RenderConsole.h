/* =====================================================================================
 *
 * Filename:  RenderConsole.h
 *
 * Description:  A concrete implementation of the RenderInterface for printing
 * the board to a standard text console.
 *
 * =====================================================================================
 */

#ifndef RENDER_CONSOLE_H
#define RENDER_CONSOLE_H

#include "RenderInterface.h"
#include "core/BBox.h"

#include <iostream>

/**
 * @class RenderConsole
 * @brief A renderer that displays the Game of Life board in the console.
 *
 * This class implements the RenderInterface to provide a simple text-based visualization,
 * where living cells are represented by '*', dead cells are empty
 */
class RenderConsole: public RenderInterface {

public:
    /**
     * @brief Constructs a Console Renderer.
     * @param out The output stream to write to. Defaults to std::cout.
     */
    RenderConsole(std::ostream& out = std::cout) : m_outStream(out) {}

    void initView(const std::unique_ptr<GameOfLife>& upGame) override;
    void render(const std::unique_ptr<GameOfLife>& upGame) override;
    void clear() override;

private:
    std::ostream& m_outStream;
    BBox m_viewBox;
};

#endif // RENDER_CONSOLE_H

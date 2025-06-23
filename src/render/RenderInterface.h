/* =====================================================================================
 *
 * Filename:  RenderInterface.h
 *
 * Description:  Defines the abstract interface for all renderer classes.
 *
 * Different rendering methods can be created to display the game state (e.g., simple console, TUI, GUI).
 *
 * =====================================================================================
 */

#ifndef RENDER_INTERFACE_H
#define RENDER_INTERFACE_H

#include <memory>
#include "core/GameOfLife.h"

/**
 * @class RenderInterface
 * @brief An abstract base class for any object that can render the Game of Life.
 *
 * This class defines the essential functions for displaying the simulation,
 * including setting the initial view, rendering a frame, and clearing the screen.
 */
class RenderInterface {

public:

    /**
     * @brief Virtual destructor to ensure proper cleanup of derived classes.
     */
    virtual ~RenderInterface() = default;

    /**
     * @brief Sets up the initial viewport based on the starting board state.
     *
     * This method is intended to be called once at the beginning of a simulation
     * @param upGame A unique_ptr to the GameOfLife instance containing the initial state.
     */
    virtual void initView(const std::unique_ptr<GameOfLife>& upGame) = 0;

    /**
     * @brief Renders the current state of the game.
     * @param upGame A unique_ptr to the GameOfLife instance to be rendered.
     */
    virtual void render(const std::unique_ptr<GameOfLife>& upGame) = 0;

    /**
     * @brief Clears the display area.
     *
     * This is typically called before rendering a new frame in an animation.
     */
    virtual void clear() = 0;
};

#endif // RENDER_INTERFACE_H

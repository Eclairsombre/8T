#ifndef CONSOLE_GRID
#define CONSOLE_GRID

#include "../core/Game.h"

/**
 * @class GameConsole
 * @brief This class is responsible for the console of the game.
 */
class GameConsole
{
private:
    Game game; /**< The game of the console. */

public:
    /**
     * @brief Constructor for the GameConsole class.
     *
     */
    GameConsole();

    /**
     * @brief Destructor for the GameConsole class.
     *
     */
    ~GameConsole();

    /**
     * @brief print the grid of the game.
     *
     * @param gridIndex The index of the grid.
     */

    void printGrid(int gridIndex);

    /**
     * @brief print the deck of the game.
     *
     * @param gridIndex The index of the grid.
     */
    void printDeck(int gridIndex);

    /**
     * @brief print the menu of the game.
     */
    int menu(int gridIndex);

    void placePiece(int gridIndex, int x, int y);
    void playCard(int gridIndex, int cardIndex);
    // Game &getGame();
    // void setGame(Game game) { this->game = game; }
};

#endif // CONSOLE
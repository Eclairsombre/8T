#ifndef GAME_CONSOLE
#define GAME_CONSOLE

#include "../console/GameConsole.h"

/**
 * @class Console
 * @brief This class is responsible for the console of the game.
 */
class Console
{
private:
    bool running = true;     /**< The state of the console. */
    GameConsole gameConsole; /**< The game console of the game. */

public:
    /**
     * @brief Constructor for the Console class.
     *
     */
    Console();

    /**
     * @brief Destructor for the Console class.
     *
     */
    ~Console();

    /**
     * @brief Start the console.
     *
     */
    void play();
};

#endif // CONSOLE
#ifndef GAME
#define GAME

#include <vector>
#include "Grid.h"
#include "Player.h"

/**
 * @class Game
 * @brief This class is used to represent a game
 */
class Game
{
private:
    std::vector<Grid> grids = std::vector<Grid>();       /**< Grids of the game */
    std::vector<Player> players = std::vector<Player>(); /**< Players of the game */
    int currentPlayer;                                   /**< Current player */

    bool wait = false;        // wait for the other player to play
    bool haveNetwork = false; // if the game is played on a network

public:
    /**
     * @brief Construct a new Game object
     *
     */
    Game();

    /**
     * @brief Construct a new Game object
     *
     * @param grids
     * @param players
     */
    Game(std::vector<Player> players);

    /**
     * @brief Destroy the Game object
     *
     */
    ~Game();

    /**
     * @brief Get the Grids of the game
     *
     * @return std::vector<Grid>
     */
    Grid getGrid(int index);

    /**
     * @brief Get the Current Player
     *
     * @return Player
     */
    int getCurrentPlayer();

    /**
     * @brief Set the Current Player
     *
     * @param player
     */
    void setCurrentPlayer(int player);

    /**
     * @brief Replace a player
     *
     * @param player
     */
    void setPlayer(Player player);

    /**
     * @brief Switch the current player
     *
     */
    void switchPlayer();

    /**
     * @brief Add a grid to the game
     *
     * @param grid
     */
    void addGrid(const Grid &grid);

    /**
     * @brief Get the Players of the game
     *
     * @return std::vector<Player>
     */
    std::vector<Player> getPlayer();

    /**
     * @brief Set the grid at the given index
     *
     * @param index
     * @param grid
     */
    void setGrid(int index, const Grid &grid);

    /**
     * @brief Create and set a piece on the grid
     *
     * @param cellX
     * @param cellY
     * @param CurrentGrid
     */
    void createAndSetPiece(int cellX, int cellY, int CurrentGrid);

    /**
     * @brief Get the Rules of the game
     *
     * @param symbol The symbol of the player.
     *
     * @return Rules
     */

    Player findPlayerBySymbol(std::string symbol);

    /**
     * @brief Check if a case has a piece (symbol + color) from a player.
     *
     * @param cellX The x coordinate of the cell.
     * @param cellY The y coordinate of the cell.
     * @param CurrentGrid The current grid of the game.
     * @param player The player to check.
     */
    bool isCaseOfPlayer(int cellX, int cellY, int CurrentGrid, Player player);

    /**
     * @brief add the score of the player in the grid
     *
     * @param cellX The x coordinate of the cell.
     * @param cellY The y coordinate of the cell.
     * @param CurrentGrid The current grid of the game.
     * @param direction The direction of the alignment.
     */
    void computeAlignementScoreOnDirection(int cellX, int cellY, int CurrentGrid, int direction);
};

#endif // Game

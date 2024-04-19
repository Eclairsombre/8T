#ifndef GRID
#define GRID

#include <vector>
#include "Player.h"
#include "Card.h"
#include <string>
#include <iostream>
#include <chrono>

class Case;

/**
 * @struct GridRules
 * @brief This struct is used to represent the rules of the grid
 */
struct GridRules
{
    bool canPlayCard = false;
    bool canPlacePiece = false;
    bool canDrawCard = false;
    bool checkWin = false;
    bool endGame = false;
    bool pickPlayOrPlace = false;
};

/**
 * @class Grid
 * @brief This class is used to represent the game grid
 */
class Grid
{
private:
    std::vector<std::vector<Case *>> cases; /**< Cases of the grid */
    std::vector<Card *> globalRules;        /**< Rules that are applied to the grid and the player, in ordre. */
    int currentGlobalRule = 0;
    int currentGlobalRuleIteration = 0; /**< Use to execute only once the current global rule */
    GridRules rules;                    /**< Rules of the grid */

    int nbAlignToWin = 3; /**< Number of pieces to align to win */

    using Clock = std::chrono::high_resolution_clock; // Define the clock
    Clock::time_point start = Clock::now();           // Start the clock
    Clock::time_point end = Clock::now();             // End the clock
    int time;                                         // The time of the game

public:
    /**
     * @brief Construct a new Grid object
     *
     */
    Grid();

    /**
     * @brief Construct a new Grid object
     *
     * @param cases
     */
    ~Grid();

    /**
     * @brief Add a global rule to the grid
     *
     * @param card
     */
    void addGlobalRule(Card *card);

    /**
     * @brief Get the global rules of the grid
     *
     * @return std::vector<Card>
     */
    std::vector<std::vector<Case *>> getCases();

    /**
     * @brief Set the cases of the grid
     *
     * @param cases
     */
    void setCases(std::vector<std::vector<Case *>> cases);

    /**
     * @brief Get the width of the grid
     *
     * @return int
     */
    int getGridWidth() const;

    /**
     * @brief Get the height of the grid
     *
     * @return int
     */
    int getGridHeight() const;

    /**
     * @brief Set the number of pieces to align to win
     *
     * @param nb
     */
    void setNbAlignToWin(int nb);

    /**
     * @brief Get the number of pieces to align to win
     *
     * @return int
     */
    int getNbAlignToWin();

    /**
     * @brief Check if a player has won
     *
     * @param player
     * @param cellX
     * @param cellY
     * @return true
     * @return false
     */
    bool checkWin(Player player, int cellX, int cellY);

    /**
     * @brief Set the case at the given position
     *
     * @param x
     * @param y
     * @param c
     */
    void setCase(int x, int y, Case *c);

    /**
     * @brief Get the case at the given position
     *
     * @param x
     * @param y
     * @return Case
     */
    Case *getCase(int x, int y) const;

    /**
     * @brief Reset the grid
     *
     */
    void resetGrid();

    /**
     * @brief Create the global rules of the grid
     *
     */
    void createGlobalRules();

    /**
     * @brief Get the global rules of the grid
     *
     * @return std::vector<Card>
     */
    std::vector<Card *> getGlobalRules();
    /**
     * @brief Show the grid terminal
     *
     */
    void showGridTerminal();

    /**
     * @brief Get the rules of the grid
     *
     * @return GridRules
     */
    GridRules getRules();

    /**
     * @brief Set the rules of the grid
     *
     * @param rules
     */
    void setRules(GridRules rules);

    /**
     * @brief Get the current global rule
     *
     * @return int
     */
    int getCurrentGlobalRule() const;

    /**
     * @brief Get the current global rule iteration
     *
     * @return int
     */
    int getCurrentGlobalRuleIteration() const;

    /**
     * @brief Add a current global rule iteration
     *
     */
    void addCurrentGlobalRuleIteration();

    /**
     * @brief Reset the current global rule iteration
     *
     */
    void resetCurrentGlobalRuleIteration();

    /**
     * @brief Go to the next global rule
     *
     */
    void nextGlobalRule();

    /**
     * @brief Check if the grid is full
     *
     * @return bool
     */
    bool isGridFull() const;

    /**
     * @brief Get the time of the game
     *
     * @return int
     */
    int getTimeFromLastRule();
    /**
     * @brief Start the time for the current rule
     *
     */
    void startTimeForCurrentRule();
};

#endif // GRID
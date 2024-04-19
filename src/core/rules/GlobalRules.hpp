#ifndef GLOBALRULES_HPP
#define GLOBALRULES_HPP

#include "../Card.h"
#include "../Game.h"
#include "../Player.h"
#include "../Grid.h"
#include <iostream>
#include <vector>

/**
 * @class CardAlignToWin
 *
 * @brief This class is responsible for the card AlignToWin.
 *
 */
class CardAlignToWin : public Card
{
public:
    /**
     * @brief Constructor for the CardAlignToWin class.
     *
     * @param name The name of the card.
     * @param description The description of the card.
     * @param id The id of the card.
     */
    CardAlignToWin(std::string name, std::string description, int id) : Card(name, description, id)
    {
        this->canBeGlobalRules = true;
    };

    /**
     * @brief Destructor for the CardAlignToWin class.
     *
     */
    ~CardAlignToWin(){};

    /**
     * @brief Apply the card AlignToWin.
     *
     * @param x The x coordinate of the card.
     * @param y The y coordinate of the card.
     * @param CurrentGrid The current grid of the game.
     * @param currentPlayer The current player of the game.
     * @param game The game of the card.
     * @param sens The direction of the card.
     */
    void applyCard(int x, int y, int CurrentGrid, Player &currentPlayer, Game &game, std::string sens) override
    {
        if (game.getGrid(CurrentGrid).getTimeFromLastRule() > minimumSecondsDelay)
        {
            applyWhenGlobalRule(game, CurrentGrid);
            updateTime(game, CurrentGrid);
            Grid grid = game.getGrid(CurrentGrid);

            int nbAlignToWin = grid.getNbAlignToWin();

            for (int x = 0; x < grid.getGridWidth(); x++)
            {
                for (int y = 0; y < grid.getGridHeight(); y++)
                {
                    if ((grid.getGridWidth() - x) > nbAlignToWin - 1) // Enough spaces to win on the line
                    {
                        if (y >= nbAlignToWin - 1) // Enough space to win on the anti-diagonal from bottom to top from here, going right
                        {
                            game.computeAlignementScoreOnDirection(x, y, CurrentGrid, 0);
                        }
                        game.computeAlignementScoreOnDirection(x, y, CurrentGrid, 1);

                        if ((grid.getGridHeight() - y) > nbAlignToWin - 1) // Enough space to win on the diagonal from top to bottom from here, going right
                        {
                            game.computeAlignementScoreOnDirection(x, y, CurrentGrid, 3);
                        }
                    }

                    if ((grid.getGridHeight() - y) > nbAlignToWin - 1) // Enough spaces to win on the row
                    {
                        game.computeAlignementScoreOnDirection(x, y, CurrentGrid, 2);
                    }
                }
            }
        }
    }
};

/**
 * @class CardDrawCard
 *
 * @brief This class is responsible for the card DrawCard.
 *
 */
class CardDrawCard : public Card
{
public:
    /**
     * @brief Constructor for the CardDrawCard class.
     *
     * @param name The name of the card.
     * @param description The description of the card.
     * @param id The id of the card.
     */
    CardDrawCard(std::string name, std::string description, int id) : Card(name, description, id)
    {
        this->canBeGlobalRules = true;
    };

    /**
     * @brief Destructor for the CardDrawCard class.
     *
     */
    ~CardDrawCard(){};

    /**
     * @brief Apply the card DrawCard.
     *
     * @param x The x coordinate of the card.
     * @param y The y coordinate of the card.
     * @param CurrentGrid The current grid of the game.
     * @param currentPlayer The current player of the game.
     * @param game The game of the card.
     * @param sens The direction of the card.
     */
    void applyCard(int x, int y, int CurrentGrid, Player &currentPlayer, Game &game, std::string sens) override
    {
        updateTime(game, CurrentGrid);
        Grid grid = game.getGrid(CurrentGrid);
        GridRules rules = grid.getRules();
        rules.canDrawCard = true;
        // grid.nextGlobalRule(); // Wait for player input
        grid.setRules(rules);
        game.setGrid(CurrentGrid, grid);
    }
};

/**
 * @class CardSwitchPlayer
 *
 * @brief This class is responsible for the card SwitchPlayer.
 *
 */
class CardSwitchPlayer : public Card
{
public:
    /**
     * @brief Constructor for the CardSwitchPlayer class.
     *
     * @param name The name of the card.
     * @param description The description of the card.
     * @param id The id of the card.
     */
    CardSwitchPlayer(std::string name, std::string description, int id) : Card(name, description, id)
    {
        this->canBeGlobalRules = true;
        arrowDirection.push_back("static");
    };
    /**
     * @brief Destructor for the CardSwitchPlayer class.
     *
     */
    ~CardSwitchPlayer(){};

    /**
     * @brief Apply the card SwitchPlayer.
     *
     * @param x The x coordinate of the card.
     * @param y The y coordinate of the card.
     * @param CurrentGrid The current grid of the game.
     * @param currentPlayer The current player of the game.
     * @param game The game of the card.
     * @param sens The direction of the card.
     */
    void applyCard(int x, int y, int CurrentGrid, Player &currentPlayer, Game &game, std::string sens) override
    {
        if (game.getGrid(CurrentGrid).getTimeFromLastRule() > minimumSecondsDelay || !isGlobalRule)
        {
            updateTime(game, CurrentGrid);
            game.switchPlayer();
            applyWhenGlobalRule(game, CurrentGrid);
        }
    }
};

/**
 * @class CardPlacePiece
 *
 * @brief This class is responsible for the card CardPlacePiece.
 *
 */
class CardPlacePiece : public Card
{
public:
    /**
     * @brief Constructor for the CardPlacePiece class.
     *
     * @param name The name of the card.
     * @param description The description of the card.
     * @param id The id of the card.
     */
    CardPlacePiece(std::string name, std::string description, int id) : Card(name, description, id)
    {
        this->canBeGlobalRules = true;
    };
    /**
     * @brief Destructor for the CardPlacePiece class.
     *
     */
    ~CardPlacePiece(){};

    /**
     * @brief Apply the card AddToRules.
     *
     * @param x The x coordinate of the card.
     * @param y The y coordinate of the card.
     * @param CurrentGrid The current grid of the game.
     * @param currentPlayer The current player of the game.
     * @param game The game of the card.
     * @param sens The direction of the card.
     */
    void applyCard(int x, int y, int CurrentGrid, Player &currentPlayer, Game &game, std::string sens) override
    {
        updateTime(game, CurrentGrid);
        Grid grid = game.getGrid(CurrentGrid);
        GridRules rules = grid.getRules();
        rules.canPlacePiece = true;
        if (grid.isGridFull())
        {
            grid.nextGlobalRule(); // Do not wait for player input
            rules.canPlacePiece = false;
        }

        grid.setRules(rules);
        game.setGrid(CurrentGrid, grid);
    }
};

/**
 * @class CardPlayCard
 *
 * @brief This class is responsible for the card CardPlayCard.
 *
 */
class CardPlayCard : public Card
{
public:
    /**
     * @brief Constructor for the CardPlayCard class.
     *
     * @param name The name of the card.
     * @param description The description of the card.
     * @param id The id of the card.
     */
    CardPlayCard(std::string name, std::string description, int id) : Card(name, description, id)
    {
        this->canBeGlobalRules = true;
    };
    /**
     * @brief Destructor for the CardPlayCard class.
     *
     */
    ~CardPlayCard(){};

    /**
     * @brief Apply the card PlayCard.
     *
     * @param x The x coordinate of the card.
     * @param y The y coordinate of the card.
     * @param CurrentGrid The current grid of the game.
     * @param currentPlayer The current player of the game.
     * @param game The game of the card.
     * @param sens The direction of the card.
     */
    void applyCard(int x, int y, int CurrentGrid, Player &currentPlayer, Game &game, std::string sens) override
    {
        updateTime(game, CurrentGrid);
        Grid grid = game.getGrid(CurrentGrid);
        GridRules rules = grid.getRules();
        rules.canPlayCard = true;
        if (game.getPlayer()[game.getCurrentPlayer()].getDeck(CurrentGrid).getCards().empty())
        {
            if (game.getGrid(CurrentGrid).getTimeFromLastRule() > minimumSecondsDelay)
            {
                grid.nextGlobalRule(); // Do not wait for player input
                rules.canPlayCard = false;
            }
        }
        grid.setRules(rules);
        game.setGrid(CurrentGrid, grid);
    }
};

/**
 * @class CardEnd
 *
 * @brief This class is responsible for the card CardEnd.
 *
 */
class CardEnd : public Card
{
private:
    int nbRoundLeft; /**< The number of rounds left. */

public:
    /**
     * @brief Constructor for the CardEnd class.
     *
     * @param name The name of the card.
     * @param description The description of the card.
     * @param id The id of the card.
     */
    CardEnd(std::string name, std::string description, int id) : Card(name, description, id)
    {
        this->canBeGlobalRules = true;
        srand(static_cast<unsigned int>(time(nullptr)));
        nbRoundLeft = 15;
        // nbRoundLeft = 10 + rand() % 41;
    };
    /**
     * @brief Destructor for the CardEnd class.
     *
     */
    ~CardEnd(){};

    /**
     * @brief Apply the card End.
     *
     * @param x The x coordinate of the card.
     * @param y The y coordinate of the card.
     * @param CurrentGrid The current grid of the game.
     * @param currentPlayer The current player of the game.
     * @param game The game of the card.
     * @param sens The direction of the card.
     */
    void applyCard(int x, int y, int CurrentGrid, Player &currentPlayer, Game &game, std::string sens) override
    {
        if (game.getGrid(CurrentGrid).getTimeFromLastRule() > minimumSecondsDelay)
        {
            applyWhenGlobalRule(game, CurrentGrid);
            updateTime(game, CurrentGrid);

            if (nbRoundLeft == 0)
            {
                Grid grid = game.getGrid(CurrentGrid);
                GridRules rules = grid.getRules();
                rules.endGame = true;
                grid.setRules(rules);
                game.setGrid(CurrentGrid, grid);
            }
            else
            {
                nbRoundLeft--;
            }
        }
    }

    /**
     * @brief Get the Nb Round Left object
     *
     * @return int
     */
    int getNbRoundLeft()
    {
        return nbRoundLeft;
    }

    /**
     * @brief Set the Nb Round Left object
     *
     * @param nbRoundLeft
     */
    void setNbRoundLeft(int nbRoundLeft)
    {
        this->nbRoundLeft = nbRoundLeft;
    }
};

#endif // GLOBALRULES_HPP
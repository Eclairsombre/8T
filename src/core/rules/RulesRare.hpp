#include "../Card.h"
#include "../Game.h"
#include "../Player.h"
#include "../Case.h"
#include "../Grid.h"
#include <iostream>
#include <vector>
#include "GlobalRules.hpp"

/**
 * @class CardGravity
 *
 * @brief This class is responsible for the card Gravity.
 *
 */
class CardGravity : public Card
{

public:
    /**
     * @brief Constructor for the CardGravity class.
     *
     * @param name The name of the card.
     * @param description The description of the card.
     * @param id The id of the card.
     */
    CardGravity(std::string name, std::string description, int id) : Card(name, description, id)
    {
        this->canBeGlobalRules = true;

        arrowDirection.push_back("down");
    };

    /**
     * @brief Destructor for the CardGravity class.
     *
     */
    ~CardGravity(){};

    /**
     * @brief Apply the card Gravity.
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
            applyWhenGlobalRule(game, CurrentGrid);
            Grid currentGrid = game.getGrid(CurrentGrid);
            std::vector<std::vector<Case *>> cases = currentGrid.getCases();
            for (unsigned int i = 0; i < cases[0].size(); i++)
            {
                for (int x = (int) cases.size() - 1; x >= 0; x--)
                {
                    if (cases[x][i]->getPieces().size() > 0)
                    {
                        int nextEmpty = x;
                        while (static_cast<unsigned int>(nextEmpty + 1) < cases.size() && cases[nextEmpty + 1][i]->getPieces().size() == 0)
                        {
                            nextEmpty++;
                        }
                        if (x != nextEmpty)
                        {
                            Case *c = cases[x][i];
                            cases[x][i] = cases[nextEmpty][i];
                            cases[nextEmpty][i] = c;
                            currentGrid.setCases(cases);
                            game.setGrid(CurrentGrid, currentGrid);
                        }
                    }
                }
            }
        }
    }
};

class CardPickPlayOrPlace : public Card
{
public:
    /**
     * @brief Constructor for the CardPickPlayOrPlace class.
     *
     * @param name The name of the card.
     * @param description The description of the card.
     * @param id The id of the card.
     */
    CardPickPlayOrPlace(std::string name, std::string description, int id) : Card(name, description, id)
    {
        this->arrowDirection.push_back("static");
        this->canBeGlobalRules = true;
    };

    /**
     * @brief Destructor for the CardPickPlayOrPlace class.
     *
     */
    ~CardPickPlayOrPlace(){};

    /**
     * @brief Apply the card PickPlayOrPlace.
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
        rules.pickPlayOrPlace = true;
        // grid.nextGlobalRule(); // Wait for player input
        grid.setRules(rules);
        game.setGrid(CurrentGrid, grid);
    }
};

class CardEndPlusOne : public Card
{
public:
    /**
     * @brief Constructor for the CardEndPlusOne class.
     *
     * @param name The name of the card.
     * @param description The description of the card.
     * @param id The id of the card.
     */
    CardEndPlusOne(std::string name, std::string description, int id) : Card(name, description, id)
    {
        this->arrowDirection.push_back("static");
        this->canBeGlobalRules = true;
    };

    /**
     * @brief Destructor for the CardEndPlusOne class.
     *
     */
    ~CardEndPlusOne(){};

    /**
     * @brief Apply the card EndPlusOne.
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
            applyWhenGlobalRule(game, CurrentGrid);

            std::vector<Card *> globalRules = game.getGrid(CurrentGrid).getGlobalRules();
            for (unsigned int i = 0; i < globalRules.size(); i++)
            {
                if (globalRules[i]->getId() == 14)
                {
                    CardEnd *card = dynamic_cast<CardEnd *>(globalRules[i]);
                    card->setNbRoundLeft(card->getNbRoundLeft() + 1);
                }
            }
        }
    }
};

class CardEndMinusOne : public Card
{
public:
    /**
     * @brief Constructor for the CardEndMinusOne class.
     *
     * @param name The name of the card.
     * @param description The description of the card.
     * @param id The id of the card.
     */
    CardEndMinusOne(std::string name, std::string description, int id) : Card(name, description, id)
    {
        this->arrowDirection.push_back("static");
        this->canBeGlobalRules = true;
    };

    /**
     * @brief Destructor for the CardEndMinusOne class.
     *
     */
    ~CardEndMinusOne(){};

    /**
     * @brief Apply the card EndMinusOne.
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
            applyWhenGlobalRule(game, CurrentGrid);

            std::vector<Card *> globalRules = game.getGrid(CurrentGrid).getGlobalRules();
            for (unsigned int i = 0; i < globalRules.size(); i++)
            {
                if (globalRules[i]->getId() == 14)
                {
                    CardEnd *card = dynamic_cast<CardEnd *>(globalRules[i]);
                    card->setNbRoundLeft(card->getNbRoundLeft() - 1);
                }
            }
        }
    }
};
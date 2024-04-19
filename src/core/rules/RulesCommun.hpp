#include "../Case.h"
#include "../Game.h"
#include "../Player.h"

#include "../Grid.h"
#include <vector>

/**
 * @class CardAddLine
 *
 * @brief This class is responsible for the card AddLine.
 *
 */
class CardAddLine : public Card
{

public:
    /**
     * @brief Constructor for the CardAddLine class.
     *
     * @param name The name of the card.
     * @param description The description of the card.
     * @param id The id of the card.
     */
    CardAddLine(std::string name, std::string description, int id) : Card(name, description, id)
    {
        arrowDirection.push_back("up");
        arrowDirection.push_back("down");
    };
    /**
     * @brief Destructor for the CardAddLine class.
     *
     */
    ~CardAddLine(){};

    /**
     * @brief Apply the card AddLine.
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
        applyWhenGlobalRule(game, CurrentGrid);
        if (sens == "up" || sens == "default")
        {
            addUp(CurrentGrid, game);
        }
        else if (sens == "down")
        {
            addDown(CurrentGrid, game);
        }
    }

    /**
     * @brief Add a line to the grid on top.
     *
     * @param CurrentGrid The current grid of the game.
     * @param game The game of the card.
     */

    void addUp(int CurrentGrid, Game &game)
    {
        Grid currentGrid = game.getGrid(CurrentGrid);
        std::vector<std::vector<Case *>> cases = currentGrid.getCases();
        std::vector<Case *> row;
        for (unsigned int i = 0; i < cases[0].size(); i++)
        {
            row.push_back(new Case());
        }
        cases.insert(cases.begin(), row);
        currentGrid.setCases(cases);
        game.setGrid(CurrentGrid, currentGrid);
    }

    /**
     * @brief Add a line to the grid on bottom.
     *
     * @param CurrentGrid The current grid of the game.
     * @param game The game of the card.
     */
    void addDown(int CurrentGrid, Game &game)
    {
        Grid currentGrid = game.getGrid(CurrentGrid);
        std::vector<std::vector<Case *>> cases = currentGrid.getCases();
        std::vector<Case *> row;
        for (unsigned int i = 0; i < cases[0].size(); i++)
        {
            row.push_back(new Case());
        }
        cases.push_back(row);
        currentGrid.setCases(cases);
        game.setGrid(CurrentGrid, currentGrid);
    }
};

/**
 * @class CardAddColumn
 *
 * @brief This class is responsible for the card AddColumn.
 *
 */
class CardAddColumn : public Card
{

public:
    /**
     * @brief Constructor for the CardAddColumn class.
     *
     * @param name The name of the card.
     * @param description The description of the card.
     * @param id The id of the card.
     */
    CardAddColumn(std::string name, std::string description, int id) : Card(name, description, id)
    {
        arrowDirection.push_back("left");
        arrowDirection.push_back("right");
    };
    /**
     * @brief Destructor for the CardAddColumn class.
     *
     */
    ~CardAddColumn(){};

    /**
     * @brief Apply the card AddColumn.
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
        applyWhenGlobalRule(game, CurrentGrid);
        if (sens == "left" || sens == "default")
        {
            addLeft(CurrentGrid, game);
        }
        else if (sens == "right")
        {
            addRight(CurrentGrid, game);
        }
    }

    /**
     * @brief Add a column to the grid on left.
     *
     * @param CurrentGrid The current grid of the game.
     * @param game The game of the card.
     */
    void addLeft(int CurrentGrid, Game &game)
    {
        Grid currentGrid = game.getGrid(CurrentGrid);
        std::vector<std::vector<Case *>> cases = currentGrid.getCases();
        for (unsigned int i = 0; i < cases.size(); i++)
        {
            cases[i].insert(cases[i].begin(), new Case());
        }
        currentGrid.setCases(cases);
        game.setGrid(CurrentGrid, currentGrid);
    }

    /**
     * @brief Add a column to the grid on right.
     *
     * @param CurrentGrid The current grid of the game.
     * @param game The game of the card.
     */
    void addRight(int CurrentGrid, Game &game)
    {
        Grid currentGrid = game.getGrid(CurrentGrid);
        std::vector<std::vector<Case *>> cases = currentGrid.getCases();
        for (unsigned int i = 0; i < cases.size(); i++)
        {
            cases[i].push_back(new Case());
        }
        currentGrid.setCases(cases);
        game.setGrid(CurrentGrid, currentGrid);
    }
};

/**
 * @class CardRemoveLine
 *
 * @brief This class is responsible for the card RemoveLine.
 *
 */
class CardRemoveLine : public Card
{

public:
    /**
     * @brief Constructor for the CardRemoveLine class.
     *
     * @param name The name of the card.
     * @param description The description of the card.
     * @param id The id of the card.
     */
    CardRemoveLine(std::string name, std::string description, int id) : Card(name, description, id)
    {
        arrowDirection.push_back("up");
        arrowDirection.push_back("down");
    };
    /**
     * @brief Destructor for the CardRemoveLine class.
     *
     */
    ~CardRemoveLine(){};

    /**
     * @brief Apply the card RemoveLine.
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
        applyWhenGlobalRule(game, CurrentGrid);
        if (sens == "up" || sens == "default")
        {
            removeUp(CurrentGrid, game);
        }
        else if (sens == "down")
        {
            removeDown(CurrentGrid, game);
        }
    }

    /**
     * @brief Remove a line to the grid on top.
     *
     * @param CurrentGrid The current grid of the game.
     * @param game The game of the card.
     */
    void removeUp(int CurrentGrid, Game &game)
    {
        Grid currentGrid = game.getGrid(CurrentGrid);
        std::vector<std::vector<Case *>> cases = currentGrid.getCases();
        if (cases.size() > 1)
        {
            cases.erase(cases.begin());
            currentGrid.setCases(cases);
            game.setGrid(CurrentGrid, currentGrid);
        }
    }

    /**
     * @brief Remove a line to the grid on bottom.
     *
     * @param CurrentGrid The current grid of the game.
     * @param game The game of the card.
     */
    void removeDown(int CurrentGrid, Game &game)
    {
        Grid currentGrid = game.getGrid(CurrentGrid);
        std::vector<std::vector<Case *>> cases = currentGrid.getCases();
        if (cases.size() > 1)
        {
            cases.pop_back();
            currentGrid.setCases(cases);
            game.setGrid(CurrentGrid, currentGrid);
        }
    }
};

/**
 * @class CardRemoveColumn
 *
 * @brief This class is responsible for the card RemoveColumn.
 *
 */
class CardRemoveColumn : public Card
{

public:
    /**
     * @brief Constructor for the CardRemoveColumn class.
     *
     * @param name The name of the card.
     * @param description The description of the card.
     * @param id The id of the card.
     */
    CardRemoveColumn(std::string name, std::string description, int id) : Card(name, description, id)
    {
        arrowDirection.push_back("left");
        arrowDirection.push_back("right");
    };
    /**
     * @brief Destructor for the CardRemoveColumn class.
     *
     */
    ~CardRemoveColumn(){};

    /**
     * @brief Apply the card RemoveColumn.
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
        applyWhenGlobalRule(game, CurrentGrid);
        if (sens == "left" || sens == "default")
        {
            removeLeft(CurrentGrid, game);
        }
        else if (sens == "right")
        {
            removeRight(CurrentGrid, game);
        }
    }

    /**
     * @brief Remove a column to the grid on right.
     *
     * @param CurrentGrid The current grid of the game.
     * @param game The game of the card.
     */
    void removeRight(int CurrentGrid, Game &game)
    {
        Grid currentGrid = game.getGrid(CurrentGrid);
        std::vector<std::vector<Case *>> cases = currentGrid.getCases();
        for (unsigned int i = 0; i < cases.size(); i++)
        {
            if (cases[i].size() > 1)
            {
                cases[i].pop_back();
            }
        }
        currentGrid.setCases(cases);
        game.setGrid(CurrentGrid, currentGrid);
    }

    /**
     * @brief Remove a column to the grid on left.
     *
     * @param CurrentGrid The current grid of the game.
     * @param game The game of the card.
     */
    void removeLeft(int CurrentGrid, Game &game)
    {
        Grid currentGrid = game.getGrid(CurrentGrid);
        std::vector<std::vector<Case *>> cases = currentGrid.getCases();
        for (unsigned int i = 0; i < cases.size(); i++)
        {
            if (cases[i].size() > 1)
            {
                cases[i].erase(cases[i].begin());
            }
        }
        currentGrid.setCases(cases);
        game.setGrid(CurrentGrid, currentGrid);
    }
};

/**
 * @class CardTurnGrid
 *
 * @brief This class is responsible for the card TurnGrid.
 *
 */
class CardTurnGrid : public Card
{

public:
    /**
     * @brief Constructor for the CardTurnGrid class.
     *
     * @param name The name of the card.
     * @param description The description of the card.
     * @param id The id of the card.
     */
    CardTurnGrid(std::string name, std::string description, int id) : Card(name, description, id)
    {
        this->canBeGlobalRules = true;
        arrowDirection.push_back("turnLeft");
        arrowDirection.push_back("turnRight");
    };
    /**
     * @brief Destructor for the CardTurnGrid class.
     *
     */
    ~CardTurnGrid(){};

    /**
     * @brief Apply the card TurnGrid.
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
            if (sens == "turnLeft" || sens == "default")
            {
                turnLeft(CurrentGrid, game);
            }
            else if (sens == "turnRight")
            {
                turnRight(CurrentGrid, game);
            }
        }
    }

    /**
     * @brief Turn the grid to the left .
     *
     * @param CurrentGrid The current grid of the game.
     * @param game The game of the card.
     */
    void turnLeft(int CurrentGrid, Game &game)
    {
        Grid currentGrid = game.getGrid(CurrentGrid);
        std::vector<std::vector<Case *>> cases = currentGrid.getCases();
        std::vector<std::vector<Case *>> newCases;

        for (int i = (int) cases[0].size() - 1; i >= 0; i--)
        {
            std::vector<Case *> newRow;
            for (unsigned int j = 0; j < cases.size(); j++)
            {
                newRow.push_back(cases[j][i]);
            }
            newCases.push_back(newRow);
        }

        currentGrid.setCases(newCases);
        game.setGrid(CurrentGrid, currentGrid);
    }

    /**
     * @brief Turn the grid to the right.
     *
     * @param CurrentGrid The current grid of the game.
     * @param game The game of the card.
     */
    void turnRight(int CurrentGrid, Game &game)
    {
        Grid currentGrid = game.getGrid(CurrentGrid);
        std::vector<std::vector<Case *>> cases = currentGrid.getCases();
        std::vector<std::vector<Case *>> newCases;

        for (unsigned int i = 0; i < cases[0].size(); i++)
        {
            std::vector<Case *> newRow;
            for (int j = (int) cases.size() - 1; j >= 0; j--)
            {
                newRow.push_back(cases[j][i]);
            }
            newCases.push_back(newRow);
        }

        currentGrid.setCases(newCases);
        game.setGrid(CurrentGrid, currentGrid);
    }
};

/**
 * @class CardAlignToWinPlusOne
 *
 * @brief This class is responsible for the card CardAlignToWinPlusOne.
 *
 */
class CardAlignToWinPlusOne : public Card
{
public:
    /**
     * @brief Constructor for the CardAlignToWinPlusOne class.
     *
     * @param name The name of the card.
     * @param description The description of the card.
     * @param id The id of the card.
     */
    CardAlignToWinPlusOne(std::string name, std::string description, int id) : Card(name, description, id)
    {
        arrowDirection.push_back("static");
    };

    /**
     * @brief Destructor for the CardAlignToWinPlusOne class.
     *
     */
    ~CardAlignToWinPlusOne(){};

    /**
     * @brief Apply the card CardAlignToWinPlusOne.
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
        applyWhenGlobalRule(game, CurrentGrid);
        Grid grid = game.getGrid(CurrentGrid);
        grid.setNbAlignToWin(grid.getNbAlignToWin() + 1);
        game.setGrid(CurrentGrid, grid);
    }
};

/**
 * @class CardAlignToWinMinusOne
 *
 * @brief This class is responsible for the card CardAlignToWinMinusOne.
 *
 */
class CardAlignToWinMinusOne : public Card
{
public:
    /**
     * @brief Constructor for the CardAlignToWinMinusOne class.
     *
     * @param name The name of the card.
     * @param description The description of the card.
     * @param id The id of the card.
     */
    CardAlignToWinMinusOne(std::string name, std::string description, int id) : Card(name, description, id)
    {
        arrowDirection.push_back("static");
    };

    /**
     * @brief Destructor for the CardAlignToWinMinusOne class.
     *
     */
    ~CardAlignToWinMinusOne(){};

    /**
     * @brief Apply the card CardAlignToWinMinusOne.
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
        applyWhenGlobalRule(game, CurrentGrid);
        Grid grid = game.getGrid(CurrentGrid);
        grid.setNbAlignToWin(grid.getNbAlignToWin() - 1);
        game.setGrid(CurrentGrid, grid);
    }
};
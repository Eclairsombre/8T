#include "Card.h"
#include "Game.h"
#include "rules/RulesCommun.hpp"
#include "rules/RulesRare.hpp"

Card::Card(std::string name, std::string description, int id) : name(name), description(description), id(id)
{
}


std::string Card::getName()
{
    return this->name;
}

Card::Card(const Card &other) : name(other.name), description(other.description), id(other.id)
{
}

bool Card::operator==(const Card &other) const
{
    return name == other.name && description == other.description;
}

void Card::createNewCardAndApply(int id, int x, int y, int currentGrid, Player &currentPlayer, Game &game, std::string sens)
{

    Card *card = nullptr;

    switch (id)
    {
    case GravityId:
        card = new CardGravity("Gravity", "Pose une pièce sur le plateau", 1);
        card->applyCard(x, y, currentGrid, currentPlayer, game, sens);
        break;
    case AddLineId:
        card = new CardAddLine("AddLine", "Ajoute une ligne au plateau", 2);
        card->applyCard(x, y, currentGrid, currentPlayer, game, sens);
        break;
    case AddColumnId:
        card = new CardAddColumn("AddCol", "Ajoute une colonne au plateau", 3);
        card->applyCard(x, y, currentGrid, currentPlayer, game, sens);
        break;
    case TurnGridId:
        card = new CardTurnGrid("TurnGrid", "Tourne le plateau", 4);
        card->applyCard(x, y, currentGrid, currentPlayer, game, sens);
        break;
    case RemoveLineId:
        card = new CardRemoveLine("RemoveLine", "Supprime une ligne du plateau", 5);
        card->applyCard(x, y, currentGrid, currentPlayer, game, sens);
        break;
    case RemoveColumnId:
        card = new CardRemoveColumn("RemoveCol", "Supprime une colonne du plateau", 6);
        card->applyCard(x, y, currentGrid, currentPlayer, game, sens);
        break;

    default:
        break;
    }
    delete card;
}

std::vector<std::string> Card::getArrowDirection()
{
    return arrowDirection;
}

bool Card::isAGlobalRule() const
{
    return this->isGlobalRule;
}

void Card::setGlobalRuleState(bool state)
{
    this->isGlobalRule = state;
}

void Card::applyWhenGlobalRule(Game &game, int CurrentGrid)
{
    if (isGlobalRule)
    {
        Grid currentGrid = game.getGrid(CurrentGrid);
        currentGrid.nextGlobalRule();
        game.setGrid(CurrentGrid, currentGrid);
    }
}

void Card::updateTime(Game &game, int CurrentGrid)
{
    Grid grid = game.getGrid(CurrentGrid);
    grid.startTimeForCurrentRule();
    game.setGrid(CurrentGrid, grid);
}
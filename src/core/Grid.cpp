#include "Grid.h"
#include "Case.h"
#include "./rules/GlobalRules.hpp"
#include "./rules/RulesRare.hpp"
#include "./rules/RulesCommun.hpp"

Grid::Grid()
{
    for (int i = 0; i < 3; i++)
    {
        std::vector<Case *> row; // Change the type of the vector from std::vector<Case> to std::vector<Case*>

        for (int j = 0; j < 3; j++)
        {
            row.push_back(new Case()); // Allocate new Case objects with 'new'
        }
        this->cases.push_back(row);
    }

    this->createGlobalRules();
}

Grid::~Grid()
{
}

std::vector<std::vector<Case *>> Grid::getCases()
{
    return this->cases;
}

void Grid::setCases(std::vector<std::vector<Case *>> cases)
{
    this->cases = cases;
}

int Grid::getGridWidth() const
{
    return (int)this->cases[0].size();
}

int Grid::getGridHeight() const
{
    return (int)this->cases.size();
}

void Grid::setCase(int x, int y, Case *c)
{
    this->cases[y][x] = c;
}

Case *Grid::getCase(int x, int y) const
{
    return this->cases[y][x];
}

void Grid::setNbAlignToWin(int nb)
{
    this->nbAlignToWin = nb;
}

int Grid::getNbAlignToWin()
{
    return this->nbAlignToWin;
}

bool Grid::checkWin(Player player, int cellX, int cellY)
{
    std::string symbol = player.getSymbol();
    int dx[] = {-1, 0, 1, 1};
    int dy[] = {1, 1, 1, 0};

    for (int dir = 0; dir < 4; ++dir)
    {
        int nbAlign = 0;
        for (int i = -this->getNbAlignToWin() + 1; i < this->getNbAlignToWin(); ++i)
        {
            int x = cellX + i * dx[dir];
            int y = cellY + i * dy[dir];
            if (x >= 0 && y >= 0 && x < this->getGridWidth() && y < this->getGridHeight() &&
                this->getCase(x, y)->getPieces().size() > 0 && this->getCase(x, y)->getPieces()[0].getSymbol() == symbol)
            {
                nbAlign++;
                if (nbAlign == this->getNbAlignToWin())
                {
                    return true;
                }
            }
            else
            {

                nbAlign = 0;
            }
        }
    }
    return false;
}

void Grid::resetGrid()
{
    for (int i = 0; i < this->getGridWidth(); i++)
    {
        for (int j = 0; j < this->getGridHeight(); j++)
        {
            this->setCase(i, j, new Case());
        }
    }
}

void Grid::addGlobalRule(Card *card)
{
    card->setGlobalRuleState(true);
    this->globalRules.push_back(card);
}

void Grid::createGlobalRules()
{
    CardPickPlayOrPlace *card = new CardPickPlayOrPlace("PickPlayOrPlace", "Choisis entre jouer ou placer une pièce", 15);
    this->addGlobalRule(card);
    CardSwitchPlayer *card2 = new CardSwitchPlayer("SwitchPlayer", "Change de joueur", 10);
    this->addGlobalRule(card2);
    CardAlignToWin *card3 = new CardAlignToWin("AlignToWin", "Change le nombre d'alignement pour gagner", 11);
    this->addGlobalRule(card3);
}

std::vector<Card *> Grid::getGlobalRules()
{
    return this->globalRules;
}

void Grid::showGridTerminal()
{
    for (int i = 0; i < this->getGridWidth(); i++)
    {
        for (int j = 0; j < this->getGridHeight(); j++)
        {
            std::cout << this->getCase(i, j)->getPieces().size() << " ";
        }
        std::cout << std::endl;
    }
}

GridRules Grid::getRules()
{
    return this->rules;
}

void Grid::setRules(GridRules rules)
{
    this->rules = rules;
}

int Grid::getCurrentGlobalRule() const
{
    return this->currentGlobalRule;
}

int Grid::getCurrentGlobalRuleIteration() const
{
    return this->currentGlobalRuleIteration;
}

void Grid::addCurrentGlobalRuleIteration()
{
    this->currentGlobalRuleIteration += 1;
}

void Grid::resetCurrentGlobalRuleIteration()
{
    this->currentGlobalRule = 0;
}

void Grid::nextGlobalRule()
{
    this->currentGlobalRule = (this->currentGlobalRule + 1) % (this->globalRules.size());
}

bool Grid::isGridFull() const
{
    for (int x = 0; x < this->getGridWidth(); x++)
    {
        for (int y = 0; y < this->getGridHeight(); y++)
        {
            if (this->getCase(x, y)->isPiecesEmpty())
            {
                return false;
            }
        }
    }
    return true;
}

int Grid::getTimeFromLastRule()
{
    this->end = Clock::now(); // Update the time
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    return (int)duration.count();
}

void Grid::startTimeForCurrentRule()
{
    this->start = Clock::now();
}
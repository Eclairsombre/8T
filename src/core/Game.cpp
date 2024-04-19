#include "Game.h"
#include "Case.h"
#include <iostream>
#include <vector>
#include "Piece.h"

Game::Game()
{

    this->players.push_back(Player("X", "red"));
    this->players.push_back(Player("O", "blue"));

    this->grids.push_back(Grid());
    this->currentPlayer = 0;
}

Game::Game(std::vector<Player> players)
{
    this->players = players;
    this->grids.push_back(Grid());
    this->currentPlayer = 0;
}

Game::~Game()
{
}

Grid Game::getGrid(int index)
{
    return this->grids[index];
}

int Game::getCurrentPlayer()
{
    return this->currentPlayer;
}

void Game::addGrid(const Grid &grid)
{
    this->grids.push_back(grid);
}

void Game::setGrid(int index, const Grid &grid)
{
    this->grids[index] = grid;
}

void Game::switchPlayer()
{
    if (this->currentPlayer == 0)
    {
        this->currentPlayer = 1;
    }
    else
    {
        this->currentPlayer = 0;
    }
}

std::vector<Player> Game::getPlayer()
{
    return this->players;
}

void Game::createAndSetPiece(int cellX, int cellY, int CurrentGrid)
{

    PieceEffects pieceEffects;
    CaseEffects caseEffects;
    Player currentPlayer = this->players[this->getCurrentPlayer()];
    Piece piece = Piece(currentPlayer.getSymbol(), currentPlayer.getColor(), pieceEffects);
    std::vector<Piece> pieces;
    pieces.push_back(piece);
    Case *c = new Case(pieces, caseEffects);
    Grid grid = this->getGrid(CurrentGrid);
    grid.setCase(cellX, cellY, c);
    this->setGrid(CurrentGrid, grid);
}

void Game::setCurrentPlayer(int player)
{
    this->currentPlayer = player;
}

void Game::setPlayer(Player player)
{
    for (unsigned int i = 0; i < this->players.size(); i++)
    {
        if (this->players[i].getSymbol() == player.getSymbol())
        {
            this->players[i] = player;
        }
    }
}

Player Game::findPlayerBySymbol(std::string symbol)
{
    for (unsigned int i = 0; i < this->players.size(); i++)
    {
        if (this->players[i].getSymbol() == symbol)
        {
            return this->players[i];
        }
    }
    return Player("", "");
}

bool Game::isCaseOfPlayer(int cellX, int cellY, int CurrentGrid, Player player)
{
    if (!this->getGrid(CurrentGrid).getCase(cellX, cellY)->getPieces().empty())
    {
        if (this->getGrid(CurrentGrid).getCase(cellX, cellY)->getPieces()[0].getSymbol() == player.getSymbol() && this->getGrid(CurrentGrid).getCase(cellX, cellY)->getPieces()[0].getColor() == player.getColor())
        {
            return true;
        }
    }
    return false;
}

void Game::computeAlignementScoreOnDirection(int cellX, int cellY, int CurrentGrid, int direction)
{
    Grid grid = this->getGrid(CurrentGrid);
    int nbAlignToWin = grid.getNbAlignToWin();
    std::vector<Player> players = this->getPlayer();

    for (long unsigned int p = 0; p < players.size(); p++)
    {
        Player player = players[p];
        int directionX = 0;
        int directionY = 0;
        switch (direction)
        {
        case 0:              // Anti-diagonal ((x, y) to  (x+NbToAlign, y+NbToAlign))
            directionX = 1;  // Right
            directionY = -1; // Up
            break;
        case 1:             // Line
            directionX = 1; // Right
            break;
        case 2:             // Row
            directionY = 1; // Down
            break;
        case 3:             // Diagonal
            directionX = 1; // Right
            directionY = 1; // Down
            break;
        }

        int aligned = 0;
        while (((aligned < nbAlignToWin) && (this->isCaseOfPlayer(cellX + (directionX * aligned), cellY + (directionY * aligned), CurrentGrid, player))))
        {
            aligned += 1;
        }

        if (aligned == nbAlignToWin)
        {
            player.setScore(player.getScore() + 1);
            this->setPlayer(player); // Update the player score
        }
    }
}
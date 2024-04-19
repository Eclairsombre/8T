#include "GameConsole.h"
#include <functional>
#include <iostream>
#include <vector>
#include "../core/Piece.h"
#include "../core/Case.h"

GameConsole::GameConsole()
{
}

GameConsole::~GameConsole()
{
}

void GameConsole::printGrid(int gridIndex)
{

    std::cout << "\n----- Grid " << gridIndex << " -----\n"
              << std::endl;

    for (int y = 0; y < game.getGrid(gridIndex).getGridHeight(); y++)
    {
        for (int x = 0; x < game.getGrid(gridIndex).getGridWidth(); x++)
        {
            Case *c = this->game.getGrid(gridIndex).getCase(x, y);
            std::vector<Piece> pieces = c->getPieces();
            if (pieces.empty())
            {
                std::cout << " ";
            }
            else
            {
                std::cout << pieces[0].getSymbol(); // Only one pieces limitation
            }

            if (x < game.getGrid(gridIndex).getGridWidth() - 1)
            {
                std::cout << "|";
            }
        }
        std::cout << std::endl;
    }
}

void GameConsole::printDeck(int gridIndex)
{
    std::cout << "\n----- Deck " << gridIndex << " -----\n"
              << std::endl;
    for (unsigned int i = 0; i < this->game.getPlayer()[this->game.getCurrentPlayer()].getDeck(gridIndex).getCards().size(); i++)
    {
        Card *card = game.getPlayer()[game.getCurrentPlayer()].getDeck(gridIndex).getCards()[i];
        if (card->getName().empty())
        {
            std::cout << " ";
        }
        else
        {
            std::cout << card->getName();
        }

        if (i < this->game.getPlayer()[this->game.getCurrentPlayer()].getDeck(gridIndex).getCards().size() - 1)
        {
            std::cout << " | ";
        }
    }
    std::cout << std::endl;
}

int GameConsole::menu(int gridIndex)
{
    auto inputVerification = [](int min, int max)
    {
        int input;
        std::cout << "\nSelect an action [" << min << "-" << max << "]: ";
        while (true)
        {
            std::cin >> input;
            if (input >= min && input <= max)
            {
                break;
            }
            else
            {
                std::cout << "\nInvalid input. Please enter a number between " << min << " and " << max << ": ";
            }
        }
        return input;
    };

    auto showOptions = [](std::vector<std::string> options)
    {
        for (unsigned int i = 1; i < options.size() + 1; i++)
        {
            std::cout << "\n[" << i << "] " << options[i - 1];
        }
    };

    std::cout << "\n**--- Player " << game.getPlayer()[game.getCurrentPlayer()].getSymbol() << " ---**" << std::endl;

    std::vector<std::string> options = {"Place a piece", "Play a card", "Draw a card", "Exit"};
    showOptions(options);
    int input = inputVerification(1, (int) options.size());

    switch (input)
    {
    case 1:
    {
        std::cout << "\nEnter coordinates: " << std::endl;
        std::cout << "\nx: ";
        int x = inputVerification(1, game.getGrid(gridIndex).getGridWidth());
        std::cout << "\ny: ";
        int y = inputVerification(1, game.getGrid(gridIndex).getGridHeight());
        game.createAndSetPiece(x - 1, y - 1, gridIndex);
        game.switchPlayer();
        return 1;
    }

    case 2:
    {
        Deck deck = game.getPlayer()[game.getCurrentPlayer()].getDeck(gridIndex);
        std::vector<std::string> options;
        for (unsigned int i = 0; i < deck.getCards().size(); i++)
        {
            Card card = *game.getPlayer()[game.getCurrentPlayer()].getDeck(gridIndex).getCards()[i];
            options.push_back(card.getName());
        }
        showOptions(options);
        int index = inputVerification(1, (int) deck.getCards().size()) - 1;

        Player player = game.getPlayer()[game.getCurrentPlayer()];
        std::cout << "Choose a direction to apply the card: " << std::endl;
        std::vector<std::string> directions = deck.getCards()[index]->getArrowDirection();
        showOptions(directions);
        int direction = inputVerification(1, (int) directions.size());
        (*deck.getCards()[index]).applyCard(0, 0, gridIndex, player, game, directions[direction - 1]);
        return 1;
    }
    case 3:
    {
        Player player = game.getPlayer()[game.getCurrentPlayer()];
        player.drawCard();
        return 1;
    }
    case 4:
    {
        return 0;
    }
    }
    return 0;
}
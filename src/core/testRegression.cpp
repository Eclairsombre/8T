#include "Game.h"
#include "Case.h"
#include "../rules/GlobalRules.hpp"
#include "../rules/RulesRare.hpp"
#include "../rules/RulesCommun.hpp"
#include <cassert>

void TestRegression()
{

    Game game;
    Grid grid = game.getGrid(0);
    assert(grid.getGridHeight() == 3);
    assert(grid.getGridWidth() == 3);
    assert(grid.getNbAlignToWin() == 3);
    grid.setNbAlignToWin(4);
    assert(grid.getNbAlignToWin() == 4);

    game.createAndSetPiece(0, 0, 0);
    game.switchPlayer();
    game.createAndSetPiece(1, 0, 0);

    assert(game.getGrid(0).getCase(0, 0)->getPieces()[0].getSymbol() == "X");
    assert(game.getGrid(0).getCase(1, 0)->getPieces()[0].getSymbol() == "O");

    game.createAndSetPiece(0, 1, 0);
    game.switchPlayer();
    game.createAndSetPiece(1, 1, 0);

    assert(game.getGrid(0).getCase(0, 1)->getPieces()[0].getSymbol() == "O");
    assert(game.getGrid(0).getCase(1, 1)->getPieces()[0].getSymbol() == "X");

    Deck deck;
    deck.addCard(CardAddColumn("AddCol", "Ajoute une colonne au plateau", 3));
    deck.addCard(CardAddLine("AddLine", "Ajoute une ligne au plateau", 2));
    deck.addCard(CardGravity("Gravity", "Pose une pièce sur le plateau", 1));
    deck.addCard(CardRemoveColumn("RemoveCol", "Supprime une colonne du plateau", 6));

    assert(deck.getCards()[0]->getName() == "AddCol");
    assert(deck.getCards()[1]->getName() == "AddLine");
    assert(deck.getCards()[2]->getName() == "Gravity");
    assert(deck.getCards()[3]->getName() == "RemoveCol");

    game.getGrid(0).addGlobalRule(deck.getCards()[0]);

    assert(game.getGrid(0).getGlobalRules()[0]->getName() == "PickPlayOrPlace");

    Player player1("X", "Rouge");
    Player player2("O", "Bleu");

    assert(player1.getSymbol() == "X");
    assert(player1.getColor() == "Rouge");
    assert(player2.getSymbol() == "O");
    assert(player2.getColor() == "Bleu");

    Piece piece1;
    Piece piece2("X", "Rouge", PieceEffects());
    piece1.setSymbol("O");
    piece1.setColor("Bleu");

    assert(piece1.getSymbol() == "O");
    assert(piece1.getColor() == "Bleu");
    assert(piece2.getSymbol() == "X");
    assert(piece2.getColor() == "Rouge");

    Case c;
    c.addPiece(piece1);

    assert(c.getPieces()[0].getSymbol() == "O");
}

int main()
{
    TestRegression();
    return 0;
}

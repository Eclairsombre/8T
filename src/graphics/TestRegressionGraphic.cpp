#include "Graphic.h"
#include "../rules/GlobalRules.hpp"
#include <assert.h>

int main()
{
    Graphic graphic;

    GridGraphic grid = graphic.getGrid();

    assert(grid.getCaseHeight() == 100);
    assert(grid.getCaseWidth() == 100);

    int gridX = grid.getGridX();
    int gridY = grid.getGridY();

    grid.moveGrid(10, 10);

    assert(grid.getGridX() == gridX + 10);
    assert(grid.getGridY() == gridY + 10);

    CardPlayCard *card = new CardPlayCard("PlayCard", "description", 8);
    graphic.setCard(card);

    assert(graphic.getCard() == card);
    assert(graphic.getCard()->getId() == 8);

    return 0;
}
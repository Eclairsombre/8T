#include "GridGraphic.h"
#include "Graphic.h"
#include "../core/Piece.h"
#include "../core/Case.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <algorithm>
#include <cstddef>
#include <string>
#include "../core/rules/GlobalRules.hpp"

GridGraphic::GridGraphic(/* args */)
{
}

GridGraphic::~GridGraphic()
{
}

void addTexturePlayer(SDL_Renderer *renderer, std::vector<SDL_Texture *> &playerTextures, Player player1)
{
    if (player1.getSymbol() == "X")
    {
        if (player1.getColor() == "Rouge")
        {
            SDL_Surface *surface = IMG_Load("../data/images/piece_cross_red.png");
            if (surface == nullptr)
            {
                printf("Error: %s\n", IMG_GetError());
            }
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (texture == nullptr)
            {
                printf("Error: %s\n", SDL_GetError());
            }
            SDL_FreeSurface(surface);

            playerTextures.push_back(texture);
        }
        else if (player1.getColor() == "Bleu")
        {
            SDL_Surface *surface = IMG_Load("../data/images/piece_cross_blue.png");
            if (surface == nullptr)
            {
                printf("Error: %s\n", IMG_GetError());
            }
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            playerTextures.push_back(texture);
        }
        else if (player1.getColor() == "Vert")
        {
            SDL_Surface *surface = IMG_Load("../data/images/piece_cross_green.png");
            if (surface == nullptr)
            {
                printf("Error: %s\n", IMG_GetError());
            }
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            playerTextures.push_back(texture);
        }
        else if (player1.getColor() == "Jaune")
        {
            SDL_Surface *surface = IMG_Load("../data/images/piece_cross_yellow.png");
            if (surface == nullptr)
            {
                printf("Error: %s\n", IMG_GetError());
            }
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            playerTextures.push_back(texture);
        }
    }
    else if (player1.getSymbol() == "O")
    {
        if (player1.getColor() == "Rouge")
        {
            SDL_Surface *surface = IMG_Load("../data/images/piece_circle_red.png");
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            playerTextures.push_back(texture);
        }
        else if (player1.getColor() == "Bleu")
        {
            SDL_Surface *surface = IMG_Load("../data/images/piece_circle_blue.png");
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            playerTextures.push_back(texture);
        }
        else if (player1.getColor() == "Vert")
        {
            SDL_Surface *surface = IMG_Load("../data/images/piece_circle_green.png");
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            playerTextures.push_back(texture);
        }
        else if (player1.getColor() == "Jaune")
        {
            SDL_Surface *surface = IMG_Load("../data/images/piece_circle_yellow.png");
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            playerTextures.push_back(texture);
        }
    }
    else if (player1.getSymbol() == "T")
    {
        if (player1.getColor() == "Rouge")
        {
            SDL_Surface *surface = IMG_Load("../data/images/piece_triangle_red.png");
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            playerTextures.push_back(texture);
        }
        else if (player1.getColor() == "Bleu")
        {
            SDL_Surface *surface = IMG_Load("../data/images/piece_triangle_blue.png");
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            playerTextures.push_back(texture);
        }
        else if (player1.getColor() == "Vert")
        {
            SDL_Surface *surface = IMG_Load("../data/images/piece_triangle_green.png");
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            playerTextures.push_back(texture);
        }
        else if (player1.getColor() == "Jaune")
        {
            SDL_Surface *surface = IMG_Load("../data/images/piece_triangle_yellow.png");
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            playerTextures.push_back(texture);
        }
    }
    else
    {
        if (player1.getColor() == "Rouge")
        {
            SDL_Surface *surface = IMG_Load("../data/images/piece_cube_red.png");
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            playerTextures.push_back(texture);
        }
        else if (player1.getColor() == "Bleu")
        {
            SDL_Surface *surface = IMG_Load("../data/images/piece_cube_blue.png");
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            playerTextures.push_back(texture);
        }
        else if (player1.getColor() == "Vert")
        {
            SDL_Surface *surface = IMG_Load("../data/images/piece_cube_green.png");
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            playerTextures.push_back(texture);
        }
        else if (player1.getColor() == "Jaune")
        {
            SDL_Surface *surface = IMG_Load("../data/images/piece_cube_yellow.png");
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
            playerTextures.push_back(texture);
        }
    }
}

GridGraphic::GridGraphic(SDL_Renderer *renderer, Player player1, Player player2)
{
    std::vector<Player> players;
    players.push_back(player1);
    players.push_back(player2);
    this->game = Game(players);

    addTexturePlayer(renderer, this->playerTextures, player1);

    addTexturePlayer(renderer, this->playerTextures, player2);

    SDL_Surface *surface = IMG_Load("../data/images/card_draw.png");
    this->deckTexture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    surface = IMG_Load("../data/images/case.png");
    this->caseTexture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    surface = IMG_Load("../data/images/deck.png");
    this->backgroundTexture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    surface = IMG_Load("../data/images/arrow_up.png");
    this->arrowUpTexture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    surface = IMG_Load("../data/images/arrow_down.png");
    this->arrowDownTexture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    surface = IMG_Load("../data/images/arrow_left.png");
    this->arrowLeftTexture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    surface = IMG_Load("../data/images/arrow_right.png");
    this->arrowRightTexture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    surface = IMG_Load("../data/images/arrow_turn_left.png");
    this->arrowTurnLeftTexture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    surface = IMG_Load("../data/images/arrow_turn_right.png");
    this->arrowTurnRightTexture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    surface = IMG_Load("../data/images/card_addRule.png");
    this->addToRulesTexture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    surface = IMG_Load("../data/images/logo_big.png");
    this->logo = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    surface = IMG_Load("../data/images/score.png");
    this->score = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    surface = IMG_Load("../data/images/card_shadow.png");
    this->shadowCard = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    surface = IMG_Load("../data/images/card_apply.png");
    this->applyTexture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);
}

void GridGraphic::initCardTexture(SDL_Renderer *renderer)
{
    SDL_Surface *surface = IMG_Load("../data/images/card_gravity.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    this->cardsTextures.push_back(texture);
    SDL_FreeSurface(surface);

    surface = IMG_Load("../data/images/card_addline.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    this->cardsTextures.push_back(texture);
    SDL_FreeSurface(surface);

    surface = IMG_Load("../data/images/card_addrow.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    this->cardsTextures.push_back(texture);
    SDL_FreeSurface(surface);

    surface = IMG_Load("../data/images/card_turn.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    this->cardsTextures.push_back(texture);
    SDL_FreeSurface(surface);

    surface = IMG_Load("../data/images/card_removeLine.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    this->cardsTextures.push_back(texture);
    SDL_FreeSurface(surface);

    surface = IMG_Load("../data/images/card_removeRow.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    this->cardsTextures.push_back(texture);
    SDL_FreeSurface(surface);

    surface = IMG_Load("../data/images/card_place.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    this->cardsTextures.push_back(texture);
    SDL_FreeSurface(surface);

    surface = IMG_Load("../data/images/card_play.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    this->cardsTextures.push_back(texture);
    SDL_FreeSurface(surface);

    surface = IMG_Load("../data/images/card_draw.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    this->cardsTextures.push_back(texture);
    SDL_FreeSurface(surface);

    surface = IMG_Load("../data/images/card_switch.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    this->cardsTextures.push_back(texture);
    SDL_FreeSurface(surface);

    surface = IMG_Load("../data/images/card_align.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    this->cardsTextures.push_back(texture);
    SDL_FreeSurface(surface);

    surface = IMG_Load("../data/images/card_align+1.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    this->cardsTextures.push_back(texture);
    SDL_FreeSurface(surface);

    surface = IMG_Load("../data/images/card_align-1.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    this->cardsTextures.push_back(texture);
    SDL_FreeSurface(surface);

    surface = IMG_Load("../data/images/card_end.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    this->cardsTextures.push_back(texture);
    SDL_FreeSurface(surface);

    surface = IMG_Load("../data/images/card_placePlayPick.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    this->cardsTextures.push_back(texture);
    SDL_FreeSurface(surface);

    surface = IMG_Load("../data/images/card_end+1.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    this->cardsTextures.push_back(texture);
    SDL_FreeSurface(surface);

    surface = IMG_Load("../data/images/card_end-1.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    this->cardsTextures.push_back(texture);
    SDL_FreeSurface(surface);
}

void GridGraphic::showGrid(SDL_Renderer *renderer, Graphic &graphic)
{
    std::vector<std::vector<Case *>> grid = this->game.getGrid(0).getCases();
    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
    std::vector<Player> players = this->game.getPlayer();

    int GridWidth = grid[0].size() * graphic.caseWidth;
    int GridHeight = grid.size() * graphic.caseWidth;

    int startX = (windowWidth - GridWidth) / 2;
    int startY = (windowHeight - GridHeight) / 2;


    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    for (unsigned int i = 0; i < grid.size(); i++)
    {
        for (unsigned int j = 0; j < grid[i].size(); j++)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

            std::vector<Piece> pieces = grid[i][j]->getPieces();
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

            SDL_Rect rect = {(int)(startX + j * graphic.caseWidth + this->gridX), (int)(startY + i * graphic.caseWidth + this->gridY), graphic.caseWidth, graphic.caseWidth};
            SDL_RenderCopy(renderer, caseTexture, NULL, &rect);
            if (pieces.size() > 0)
            {
                for (unsigned int k = 0; k < players.size(); k++)
                {
                    if (players[k].getSymbol() == pieces[0].getSymbol())
                    {
                        SDL_RenderCopy(renderer, playerTextures[k], NULL, &rect);
                        // graphic.drawPlayer(startX + j * 100 + 50 + this->gridX, startY + i * 100 + 50 + this->gridY, 40, 5, players[k]);
                    }
                }
            }
        }
    }
}

void GridGraphic::moveGrid(int dx, int dy)
{
    gridX += dx;
    gridY += dy;
}

Game &GridGraphic::getGame()
{
    return this->game;
}

void GridGraphic::drawDeck(SDL_Renderer *renderer, Graphic &graphic)
{
    Player player = this->game.getPlayer()[this->game.getCurrentPlayer()];
    Deck deck = player.getDeck(player.getCurrentGrid());
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY); // Get mouse position

    int lastCardIndex = deck.getCards().size()-1;
    int maxCardIndex = graphic.background_deck.w/(graphic.cardWidth + graphic.gap)-1;
    int limitCardIndex = std::min(lastCardIndex, maxCardIndex);

    int currentCardIndex = 0;

    int i = 0;

    while (i <= limitCardIndex) 
    {
        currentCardIndex = (i +  lastCardIndex+1) % (lastCardIndex+1);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        int cardX = (i) * (graphic.cardWidth + graphic.gap) + graphic.background_deck.x + graphic.gap;
        int cardY = graphic.background_deck.y + graphic.gap;
        int cardWidth = graphic.cardWidth;
        int cardHeight = graphic.cardHeight;
        if (graphic.getCard() != nullptr && graphic.getCard()->getUniqueId() == deck.getCards()[i]->getUniqueId())
        {
            cardHeight *= graphic.cardZoomFactor;
            cardWidth *= graphic.cardZoomFactor;
            cardY -= ((cardHeight * graphic.cardZoomFactor) - cardHeight - graphic.gap)/2 +2;
            cardX -= ((cardWidth * graphic.cardZoomFactor) - cardWidth - graphic.gap)/2;
        }
        SDL_Rect rect = {cardX, cardY, cardWidth, cardHeight};
        SDL_RenderCopy(renderer, cardsTextures[deck.getCards()[currentCardIndex]->getId() - 1], NULL, &rect);

        drawCardDetails(deck.getCards()[currentCardIndex], graphic, cardX, cardY, currentCardIndex);
        i++;
    }
}

void GridGraphic::drawGlobalrules(SDL_Renderer *renderer, Graphic &graphic)
{
    Player player = this->game.getPlayer()[this->game.getCurrentPlayer()];
    Grid grid = this->game.getGrid(player.getCurrentGrid());
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    int lastCardIndex = grid.getGlobalRules().size()-1;
    int maxCardIndex = graphic.background_rules.w/(graphic.cardWidth + graphic.gap)-1;
    int limitCardIndex = std::min(lastCardIndex, maxCardIndex);

    int shiftedIndex = 0;
    int currentCardIndex = grid.getCurrentGlobalRule();

    if ((lastCardIndex > maxCardIndex)) { 
        shiftedIndex =  currentCardIndex - maxCardIndex/2; 
    }

    int i = 0;

    while (i <= limitCardIndex) 
    {
        currentCardIndex = (i +  lastCardIndex+1 + shiftedIndex) % (lastCardIndex+1);

        int cardX = (i) * (graphic.cardWidth + graphic.gap) + graphic.background_rules.x + graphic.gap;
        int cardY = graphic.background_rules.y + graphic.gap;
        int cardWidth = graphic.cardWidth;;
        int cardHeight = graphic.cardHeight;

        if ((int) grid.getCurrentGlobalRule() == currentCardIndex)
        {
            cardHeight *= graphic.cardZoomFactor;
            cardWidth *= graphic.cardZoomFactor;
            cardY -= ((cardHeight * graphic.cardZoomFactor) - cardHeight - graphic.gap)/2 +2;
            cardX -= ((cardWidth * graphic.cardZoomFactor) - cardWidth - graphic.gap)/2;

            graphic.shadowRect.x = cardX;
            graphic.shadowRect.y = cardY;
            graphic.shadowRect.w = cardWidth;
            graphic.shadowRect.h = cardHeight;

            SDL_RenderCopy(renderer, shadowCard, NULL, &graphic.shadowRect);
        }

        SDL_Rect rect = {cardX, cardY, cardWidth, cardHeight};
        SDL_RenderCopy(renderer, cardsTextures[grid.getGlobalRules()[currentCardIndex]->getId() - 1], NULL, &rect);

        drawCardDetails(grid.getGlobalRules()[currentCardIndex], graphic, cardX, cardY, currentCardIndex);
        i++;
    }
}

void GridGraphic::drawCardDetails(Card *card, Graphic &graphic, int cardX, int cardY, int indiceCard)
{
    if (card != nullptr)
    {
        int x, y;

        x = cardX + 20;
        y = cardY + 110;

        if (graphic.getGrid().getGame().getGrid(this->game.getPlayer()[this->game.getCurrentPlayer()].getCurrentGrid()).getCurrentGlobalRule() == static_cast<int>(indiceCard))
        {
            x = cardX + 20;
            y = cardY + 130;
        }
        else if (graphic.getCard() != nullptr && graphic.getCard()->getUniqueId() == card->getUniqueId())
        {
            x = cardX + 20;
            y = cardY + 130;
        }

        switch (card->getId())
        {
        case 11:
        {
            std::string nbAlignToWin = std::to_string(this->game.getGrid(this->game.getPlayer()[this->game.getCurrentPlayer()].getCurrentGrid()).getNbAlignToWin());
            graphic.drawText(nbAlignToWin.c_str(), x, y);
            break;
        }
        case 14:
        {
            auto endCard = dynamic_cast<CardEnd *>(card);
            if (endCard != nullptr)
            {
                std::string roundLeft = std::to_string(endCard->getNbRoundLeft());
                graphic.drawText(roundLeft.c_str(), x, y);
            }
            break;
        }
        break;

        default:
            break;
        }
    }
}

void GridGraphic::setInitialGridSize(int width, int height)
{
    initialGridWidth = width;
    initialGridHeight = height;
}

void GridGraphic::drawPartInterface(SDL_Renderer *renderer, Graphic &graphic)
{
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &graphic.background_deck);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &graphic.background_rules);
}

void GridGraphic::drawArrowDirection(SDL_Renderer *renderer, Graphic &graphic)
{
    std::vector<std::vector<Case *>> grid = this->game.getGrid(0).getCases();
    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);

    int GridWidth = grid[0].size() * graphic.caseWidth;
    int GridHeight = grid.size() * graphic.caseWidth;

    int startX = (windowWidth - GridWidth) / 2;
    int startY = (windowHeight - GridHeight) / 2;

    int endX = startX + GridWidth;
    int endY = startY + GridHeight;

    if (graphic.getCard() != nullptr)
    {

        Card *card = graphic.getCard();
        std::vector<std::string> directions = card->getArrowDirection();
        for (unsigned int i = 0; i < directions.size(); i++)
        {
            if (directions[i] == "up")
            {
                SDL_Rect rect = {startX + GridWidth / 2 + this->gridX - graphic.arrowWidth/2, startY - graphic.arrowWidth + this->gridY, graphic.arrowWidth, graphic.arrowWidth};

                SDL_RenderCopy(renderer, arrowUpTexture, NULL, &rect);
            }
            if (directions[i] == "down")
            {
                SDL_Rect rect = {startX + GridWidth / 2 + this->gridX - graphic.arrowWidth/2, endY + this->gridY, graphic.arrowWidth, graphic.arrowWidth};

                SDL_RenderCopy(renderer, arrowDownTexture, NULL, &rect);
            }
            if (directions[i] == "left")
            {
                SDL_Rect rect = {startX - graphic.arrowWidth + this->gridX, startY + GridHeight / 2 + this->gridY - graphic.arrowWidth/2, graphic.arrowWidth, graphic.arrowWidth};

                SDL_RenderCopy(renderer, arrowLeftTexture, NULL, &rect);
            }
            if (directions[i] == "right")
            {

                SDL_Rect rect = {endX + this->gridX, startY + GridHeight / 2 + this->gridY - graphic.arrowWidth/2, graphic.arrowWidth, graphic.arrowWidth};

                SDL_RenderCopy(renderer, arrowRightTexture, NULL, &rect);
            }
            if (directions[i] == "static")
            {
                SDL_Rect rect = {windowWidth - graphic.cardHeight, windowHeight - (graphic.cardHeight + graphic.margin + graphic.gap), graphic.cardWidth, graphic.cardHeight};
                SDL_RenderCopy(renderer, applyTexture, NULL, &rect);
            }
            if (directions[i] == "turnLeft")
            {
                SDL_Rect rect = {startX - graphic.arrowWidth + this->gridX, startY + GridHeight / 2 + this->gridY - graphic.arrowWidth/2, graphic.arrowWidth, graphic.arrowWidth};
                SDL_RenderCopy(renderer, arrowTurnLeftTexture, NULL, &rect);
            }
            if (directions[i] == "turnRight")
            {
                SDL_Rect rect = {endX + this->gridX, startY + GridHeight / 2 + this->gridY - graphic.arrowWidth/2, graphic.arrowWidth, graphic.arrowWidth};
                SDL_RenderCopy(renderer, arrowTurnRightTexture, NULL, &rect);
            }
        }
    }
}

void GridGraphic::drawGlobalRuleButton(SDL_Renderer *renderer, Graphic &graphic)
{
    std::vector<std::vector<Case *>> grid = this->game.getGrid(0).getCases();
    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);

    if (graphic.getCard() != nullptr && graphic.getCard()->getCanBeGlobal())
    {
        SDL_RenderCopy(renderer, addToRulesTexture, NULL, &graphic.globalRuleButton);
    }
}

void GridGraphic::drawInfoPart(SDL_Renderer *renderer, Graphic &graphic)
{
    SDL_RenderCopy(renderer, this->logo, NULL, &graphic.logo);
    SDL_RenderCopy(renderer, this->caseTexture, NULL, &graphic.currentPlayerRect);
    std::vector<Player> players = this->game.getPlayer();
    Player player = this->game.getPlayer()[this->game.getCurrentPlayer()];

    for (unsigned int k = 0; k < players.size(); k++)
    {
        if (players[k].getSymbol() == player.getSymbol())
        {
            SDL_RenderCopy(renderer, playerTextures[k], NULL, &graphic.currentPlayerRect);
        }
    }

    SDL_RenderCopy(renderer, this->score, NULL, &graphic.scoreRect);
    for (unsigned int k = 0; k < players.size(); k++)
    {
        graphic.playerMiniRect.y = graphic.scoreRect.y + graphic.small_margin/2 + k * (graphic.small_caseWidth + graphic.small_margin);
        SDL_RenderCopy(renderer, playerTextures[k], NULL, &graphic.playerMiniRect);
        graphic.drawText(std::to_string(players[k].getScore()).c_str(), graphic.playerMiniRect.x + graphic.small_caseWidth, graphic.playerMiniRect.y + graphic.small_caseWidth/2 - graphic.fontSize/2);
    }
}

SDL_Texture *GridGraphic::getPlayerTexture(int indice)
{
    return this->playerTextures[indice];
}

void GridGraphic::drawPioche(SDL_Renderer *renderer, Graphic &graphic)
{

    SDL_RenderCopy(renderer, deckTexture, NULL, &graphic.newCard);
}
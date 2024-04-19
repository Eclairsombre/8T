#include "Graphic.h"
#include "../core/Case.h"
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

Graphic::Graphic()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    if (TTF_Init() != 0)
    {
        std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
        exit(1);
    }

    int screenWidth, screenHeight;
    SDL_DisplayMode dm;
    if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
    {
        std::cout << "SDL_GetDesktopDisplayMode Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    screenWidth = dm.w;
    screenHeight = dm.h;

    window = SDL_CreateWindow("8T", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, 0);

    if (window == nullptr)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if (renderer == nullptr)
    {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    color = {0, 0, 0, 255};
    this->font = TTF_OpenFont("../font/dogica.ttf", 10);
    if (font == nullptr)
    {
        std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        exit(1);
    }

    fontColor = {0, 0, 0, 255};
    fontSize = 10;
    fontStyle = TTF_STYLE_NORMAL;
    this->grid = GridGraphic();
    this->grid.setInitialGridSize(3, 3);
    this->grid.initCardTexture(renderer);

    newCard.x = 10;
    newCard.y = 500;
    newCard.w = 100;
    newCard.h = 150;

    globalRuleButton.x = 100;
    globalRuleButton.y = 300;
    globalRuleButton.w = 200;
    globalRuleButton.h = 50;

    this->cardClicked = nullptr;
}

Graphic::Graphic(SDL_Window *window, SDL_Renderer *renderer, Player player1, Player player2)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    this->window = window;
    this->renderer = renderer;
    color = {0, 0, 0, 255};
    this->font = TTF_OpenFont("../font/dogica.ttf", 15);
    if (font == nullptr)
    {
        std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        exit(1);
    }

    Mix_Music *music = Mix_LoadMUS("../data/sounds/sound.mp3");
    if (music == nullptr)
    {
        std::cout << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << std::endl;
        exit(1);
    }

    Mix_PlayMusic(music, -1);

    fontColor = {0, 0, 0, 255};
    fontSize = 15;
    fontStyle = TTF_STYLE_NORMAL;
    this->grid = GridGraphic(renderer, player1, player2);
    this->grid.initCardTexture(renderer);

    this->grid.setInitialGridSize(3, 3);

    updateInterface();

    this->cardClicked = nullptr;
}

Graphic::Graphic(SDL_Window *window, SDL_Renderer *renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    this->window = window;
    this->renderer = renderer;
    color = {0, 0, 0, 255};
    this->font = TTF_OpenFont("../font/dogica.ttf", 10);
    if (font == nullptr)
    {
        std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        exit(1);
    }

    fontColor = {0, 0, 0, 255};
    fontSize = 10;
    fontStyle = TTF_STYLE_NORMAL;
    this->grid = GridGraphic();
    this->grid.setInitialGridSize(3, 3);
    this->grid.initCardTexture(renderer);

    newCard.x = 10;
    newCard.y = 500;
    newCard.w = 100;
    newCard.h = 150;

    globalRuleButton.x = 100;
    globalRuleButton.y = 300;
    globalRuleButton.w = 200;
    globalRuleButton.h = 50;

    this->cardClicked = nullptr;
}
Graphic::~Graphic()
{
}

void Graphic::updateInterface()
{
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    globalMargin = windowWidth/4;
    deckHeight = cardHeight + 2 * gap;
    deckWidht = windowWidth - 2 * globalMargin;

    newCard.x = windowWidth - (cardWidth + margin); // On the right with a margin
    newCard.y = (windowHeight / 2) - (cardHeight / 2); // Vertically centered
    newCard.w = cardWidth;
    newCard.h = cardHeight;

    globalRuleButton.x = windowWidth - (cardWidth + margin);
    globalRuleButton.y = margin + gap; // On the top right corner with same gap as deck
    globalRuleButton.w = cardWidth;
    globalRuleButton.h = cardHeight;

    background_deck.x = globalMargin;
    background_deck.y = windowHeight - (deckHeight + margin);
    background_deck.w = deckWidht;
    background_deck.h = deckHeight;

    background_rules.x = globalMargin;
    background_rules.y = margin;
    background_rules.w = deckWidht;
    background_rules.h = deckHeight;

    logo.x = margin;
    logo.y = margin;
    logo.w = cardWidth;
    logo.h = cardWidth;

    currentPlayerRect.x = margin;
    currentPlayerRect.y = windowHeight - (caseWidth + margin);
    currentPlayerRect.w = cardWidth;
    currentPlayerRect.h = cardWidth;

    scoreRect.x = margin;
    scoreRect.y = (windowHeight / 2) - (cardHeight / 2); // Vertically centered
    scoreRect.w = cardWidth;
    scoreRect.h = cardHeight;

    playerMiniRect.x = scoreRect.x + small_margin/2;
    playerMiniRect.w = small_caseWidth;
    playerMiniRect.h = small_caseWidth;
}

void Graphic::drawText(const char *text, int x, int y)
{
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, fontColor);
    if (!surface)
    {
        std::cout << "TTF_RenderText_Solid Error: " << TTF_GetError() << std::endl;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
    }
    SDL_Rect rect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Graphic::clear()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
}

void Graphic::present()
{
    SDL_RenderPresent(renderer);
}

void Graphic::play(GameState &gamestate)
{
    while (GameState::Game == gamestate)
    {
        if (this->grid.getGame().getGrid(this->grid.getGame().getPlayer()[this->grid.getGame().getCurrentPlayer()].getCurrentGrid()).getRules().endGame)
        {
            gamestate = GameState::End;
        }
        eventHolder(gamestate);
        clear();
        draw();
        present();
        gameloop();
    }
}

void Graphic::draw()
{
    updateInterface();
    this->grid.showGrid(renderer, *this);
    this->grid.drawArrowDirection(renderer, *this);
    this->grid.drawPartInterface(renderer, *this);
    this->grid.drawDeck(renderer, *this);
    this->grid.drawGlobalRuleButton(renderer, *this);
    this->grid.drawGlobalrules(renderer, *this);
    this->grid.drawPioche(renderer, *this);
    this->grid.drawInfoPart(renderer, *this);
}

void Graphic::handleQuitEvent(GameState &gamestate)
{
    gamestate = GameState::Quit;
}

bool CoIncid(int x, int y, int x1, int y1, int x2, int y2)
{
    return (x >= x1 && x < x2 && y >= y1 && y < y2);
}

bool Graphic::MouseClickInterface(int x, int y)
{
    return CoIncid(x, y, this->background_deck.x, this->background_deck.y, this->background_deck.x + this->background_deck.w, this->background_deck.y + this->background_deck.h);
}

void Graphic::gameloop()
{
    int CurrentGrid = this->grid.getGame().getPlayer()[this->grid.getGame().getCurrentPlayer()].getCurrentGrid();
    Player player = this->grid.getGame().getPlayer()[this->grid.getGame().getCurrentPlayer()];
    Deck deck = player.getDeck(player.getCurrentGrid());
    Game game = this->grid.getGame();
    Grid grid = game.getGrid(CurrentGrid);
    grid.getGlobalRules()[grid.getCurrentGlobalRule()]->applyCard(0, 0, CurrentGrid, player, game, "default");
    this->grid.setGame(game);
}

void Graphic::handleMouseButtonDownEvent(SDL_Event &event)
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    int screenWidth, screenHeight;
    SDL_GetRendererOutputSize(renderer, &screenWidth, &screenHeight);

    int CurrentGrid = this->grid.getGame().getPlayer()[this->grid.getGame().getCurrentPlayer()].getCurrentGrid();
    int CasesWidth = this->grid.getGame().getGrid(CurrentGrid).getGridWidth();
    int CasesHeight = this->grid.getGame().getGrid(CurrentGrid).getGridHeight();

    int gridX = ((screenWidth - CasesWidth * this->grid.getCaseWidth()) / 2) + this->grid.getGridX();
    int gridY = ((screenHeight - CasesHeight * this->grid.getCaseHeight()) / 2) + this->grid.getGridY();

    mouseX -= gridX;
    mouseY -= gridY;
    int cellX = -1;
    int cellY = -1;

    if (mouseX > 0 && mouseY > 0)
    {
        cellX = (int) round(std::floor(mouseX / 100));
        cellY = (int) round(std::floor(mouseY / 100));
    }

    Player player = this->grid.getGame().getPlayer()[this->grid.getGame().getCurrentPlayer()];
    Deck deck = player.getDeck(player.getCurrentGrid());
    SDL_GetMouseState(&mouseX, &mouseY);

    Game game = this->grid.getGame();
    Grid grid = game.getGrid(CurrentGrid);

    handleArrowClick(mouseX, mouseY, screenWidth, screenHeight);
    handleGlobalRuleButtonClick(mouseX, mouseY, screenWidth, screenHeight);

    // Play a card
    if (grid.getRules().canPlayCard || grid.getRules().pickPlayOrPlace)
    {
        for (unsigned int i = 0; i < deck.getCards().size(); i++)
        {
            int cardX =(i) * (cardWidth + gap) + background_deck.x + 2 * gap;
            int cardY = background_deck.y + 2 * gap;

            if (CoIncid(mouseX, mouseY, cardX, cardY, cardX + cardWidth, cardY + cardHeight))
            {
                if (this->cardClicked == deck.getCards()[i])
                {
                    this->cardClicked = nullptr;
                    this->isCardClicked = false;
                    game.setGrid(CurrentGrid, grid);
                    break;
                }
                else
                {
                    this->isCardClicked = true;
                    this->setCard(deck.getCards()[i]);
                    this->grid.setGame(game); // Update the grid with next global rule
                    break;
                }
            }
        }
    }

    // Draw a card
    if (grid.getRules().canDrawCard || grid.getRules().pickPlayOrPlace)
    {
        if (CoIncid(mouseX, mouseY, this->newCard.x, this->newCard.y, this->newCard.x + this->newCard.w, this->newCard.y + this->newCard.h))
        {
            grid.nextGlobalRule();
            GridRules rules = grid.getRules();

            rules.canDrawCard = false;
            grid.setRules(rules);
            game.setGrid(0, grid);
            this->grid.setGame(game); // Update the grid with next global rule

            player.drawCard();
            this->grid.getGame().setPlayer(player);
            // this->grid.getGame().setCurrentPlayer(player); // Update the grid with the new card added to the player
        }
    }

    // Place a piece
    if (grid.getRules().canPlacePiece || grid.getRules().pickPlayOrPlace)
    {
        if (CoIncid(cellX, cellY, 0, 0, CasesWidth, CasesHeight) && !this->isCardClicked && !MouseClickInterface(mouseX, mouseY))
        {
            if (grid.getCase(cellX, cellY)->getPieces().size() > 0)
            {
                if (grid.getCase(cellX, cellY)->getPieces()[0].getSymbol() == game.getPlayer()[game.getCurrentPlayer()].getSymbol())
                {
                    // TODO : working with multiple pieces on one case
                }
            }
            else
            { // Place a piece on a new piece
                GridRules rules = grid.getRules();
                rules.canPlacePiece = false;
                rules.pickPlayOrPlace = false;
                grid.setRules(rules);
                grid.nextGlobalRule();

                game.setGrid(CurrentGrid, grid);
                game.createAndSetPiece(cellX, cellY, CurrentGrid);

                // TODO : manage player effect
                // player.getPlayerEffects().posePiece = false;
                // game.setPlayer(player);
                // game.setCurrentPlayer(player);

                this->grid.setGame(game);
            }
        }
    }
}

void Graphic::handleArrowClick(int mouseX, int mouseY, int screenWidth, int screenHeight)
{
    Player player = this->grid.getGame().getPlayer()[this->grid.getGame().getCurrentPlayer()];
    int CurrentGrid = player.getCurrentGrid();
    Grid gridForRules = this->grid.getGame().getGrid(CurrentGrid); // To rename
    GridRules rules = gridForRules.getRules();

    if (rules.canPlayCard || rules.pickPlayOrPlace)
    {
        std::vector<std::vector<Case *>> grid = this->grid.getGame().getGrid(0).getCases();
        int GridWidth = (int) round(grid[0].size() * caseWidth);
        int GridHeight = (int) round(grid.size() * caseWidth);
        int startX = (screenWidth - GridWidth) / 2;
        int startY = (screenHeight - GridHeight) / 2;

        int endX = startX + GridWidth;
        int endY = startY + GridHeight;

        int arrowUpX = startX + GridWidth / 2 + this->grid.getGridX() - small_margin;
        int arrowUpY = startY - arrowWidth + this->grid.getGridY();
        int arrowUpWidth = arrowWidth;
        int arrowUpHeight = arrowWidth;

        int arrowDownX = startX + GridWidth / 2 + this->grid.getGridX() - small_margin;
        int arrowDownY = endY + this->grid.getGridY();
        int arrowDownWidth = arrowWidth;
        int arrowDownHeight = arrowWidth;

        int arrowLeftX = startX - arrowWidth + this->grid.getGridX();
        int arrowLeftY = startY + GridHeight / 2 + this->grid.getGridY() - small_margin;
        int arrowLeftWidth = arrowWidth;
        int arrowLeftHeight = arrowWidth;

        int arrowRightX = endX + this->grid.getGridX();
        int arrowRightY = startY + GridHeight / 2 + this->grid.getGridY() - small_margin;
        int arrowRightWidth = arrowWidth;
        int arrowRightHeight = arrowWidth;

        int staticRightX = screenWidth - 150;
        int staticRightY = screenHeight - 185;
        int staticRightWidth = 100;
        int staticRightHeight = 150;

        int x, y, h, w;

        if (this->isCardClicked)
        {
            std::vector<std::string> directions = this->cardClicked->getArrowDirection();
            for (unsigned int i = 0; i < directions.size(); i++)
            {
                if (directions[i] == "up")
                {
                    x = arrowUpX;
                    y = arrowUpY;
                    h = arrowUpHeight;
                    w = arrowUpWidth;
                }
                else if (directions[i] == "down")
                {
                    x = arrowDownX;
                    y = arrowDownY;
                    h = arrowDownHeight;
                    w = arrowDownWidth;
                }
                else if (directions[i] == "left" || directions[i] == "turnLeft")
                {
                    x = arrowLeftX;
                    y = arrowLeftY;
                    h = arrowLeftHeight;
                    w = arrowLeftWidth;
                }
                else if (directions[i] == "right" || directions[i] == "turnRight")
                {
                    x = arrowRightX;
                    y = arrowRightY;
                    h = arrowRightHeight;
                    w = arrowRightWidth;
                }
                else if (directions[i] == "static")
                {

                    x = staticRightX;
                    y = staticRightY;
                    h = staticRightHeight;
                    w = staticRightWidth;
                }

                if (CoIncid(mouseX, mouseY, x, y, x + w, y + h))
                {
                    this->cardClicked->setGlobalRuleState(false);
                    this->cardClicked->applyCard(0, 0, CurrentGrid, player, this->grid.getGame(), directions[i]);
                    
                    Grid gridForRules = this->grid.getGame().getGrid(CurrentGrid); // To rename
                    GridRules rules = gridForRules.getRules();
                    rules.canPlayCard = false;

                    if (this->cardClicked->getId() != 15) 
                    {
                        gridForRules.nextGlobalRule(); 
                    } else // pickPlaceOrPlace has been played and should let the player play again
                    {
                        rules.pickPlayOrPlace = true;
                    }

                    this->deleteCard();
                    this->isCardClicked = false;

                    gridForRules.setRules(rules);
                    this->grid.getGame().setGrid(CurrentGrid, gridForRules);
                }
            }
        }
    }
}

void Graphic::handleGlobalRuleButtonClick(int mouseX, int mouseY, int screenWidth, int screenHeight)
{
    Player player = this->grid.getGame().getPlayer()[this->grid.getGame().getCurrentPlayer()];
    int CurrentGrid = this->grid.getGame().getPlayer()[this->grid.getGame().getCurrentPlayer()].getCurrentGrid();
    Grid grid = this->grid.getGame().getGrid(CurrentGrid);

    if (CoIncid(mouseX, mouseY, globalRuleButton.x, globalRuleButton.y, globalRuleButton.x + globalRuleButton.w, globalRuleButton.y + globalRuleButton.h) && this->isCardClicked && this->cardClicked->getCanBeGlobal())
    {
        this->cardClicked->setGlobalRuleState(true);
        grid.addGlobalRule(this->cardClicked);
        this->deleteCard();
        this->isCardClicked = false;

        grid.nextGlobalRule();
        GridRules rules = grid.getRules();
        rules.canPlayCard = false;
        rules.pickPlayOrPlace = false;
        grid.setRules(rules);
        this->grid.getGame().setGrid(CurrentGrid, grid);
    }
}

void Graphic::handleKeyDownEvent(SDL_Event &event, GameState &gamestate)
{
    Game game = this->grid.getGame();
    Player player = this->grid.getGame().getPlayer()[this->grid.getGame().getCurrentPlayer()];
    Deck deck = player.getDeck(player.getCurrentGrid());

    switch (event.key.keysym.sym)
    {
    case SDLK_UP:
        this->grid.moveGrid(0, 10);
        break;
    case SDLK_DOWN:
        this->grid.moveGrid(0, -10);
        break;
    case SDLK_LEFT:
        this->grid.moveGrid(10, 0);
        break;
    case SDLK_RIGHT:
        this->grid.moveGrid(-10, 0);
        break;
    case SDLK_SPACE:
        deck.moveCard(-1);
        player.setDeck(player.getCurrentGrid(), deck);
        break;
    case SDLK_BACKSPACE:
        deck.moveCard(1);
        player.setDeck(player.getCurrentGrid(), deck);
        break;

    case SDLK_ESCAPE:
        gamestate = GameState::Pause;
        break;
    }

    game.setPlayer(player);
    this->grid.setGame(game);
}

void Graphic::handleCheckWin(int cellX, int cellY, Game game)
{
    Grid grid = game.getGrid(game.getPlayer()[game.getCurrentPlayer()].getCurrentGrid());
    Player player = this->grid.getGame().getPlayer()[this->grid.getGame().getCurrentPlayer()];

    if (grid.checkWin(player, cellX, cellY))
    {
        player.setScore(player.getScore() + 1);
        // game.setCurrentPlayer(player);
        game.setPlayer(player);
    }
    this->grid.setGame(game);
}

void Graphic::eventHolder(GameState &gamestate)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            this->handleQuitEvent(gamestate);
            break;
        case SDL_MOUSEBUTTONDOWN:
            this->handleMouseButtonDownEvent(event);
            break;
        case SDL_KEYDOWN:
            handleKeyDownEvent(event, gamestate);
            break;
        }
    }
}

bool Graphic::isCardEmpty()
{
    return this->cardClicked == nullptr;
}

void Graphic::deleteCard()
{
    Player player = this->grid.getGame().getPlayer()[this->grid.getGame().getCurrentPlayer()];
    Deck deck = player.getDeck(player.getCurrentGrid());
    deck.removeCard(this->cardClicked);
    player.setDeck(player.getCurrentGrid(), deck);
    this->grid.getGame().setPlayer(player);
    // this->grid.getGame().setCurrentPlayer(player);
    this->cardClicked = nullptr;
}
void Graphic::setCard(Card *card)
{
    this->cardClicked = card;
}

Card *Graphic::getCard()
{
    return this->cardClicked;
}

int Graphic::getWinnerId()
{
    int scorePlayer1 = this->grid.getGame().getPlayer()[0].getScore();
    int scorePlayer2 = this->grid.getGame().getPlayer()[1].getScore();
    if (scorePlayer1 > scorePlayer2)
    {
        return 0;
    }
    else if (scorePlayer1 < scorePlayer2)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

SDL_Texture *Graphic::getWinnerTexture()
{
    int winnerId = this->getWinnerId();
    if (winnerId == 0)
    {
        return this->grid.getPlayerTexture(0);
    }
    else if (winnerId == 1)
    {
        return this->grid.getPlayerTexture(1);
    }
    else
    {
        return IMG_LoadTexture(renderer, "../img/draw.png");
    }
}
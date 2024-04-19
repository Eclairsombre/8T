#ifndef GRAPHIC_GRID
#define GRAPHIC_GRID

/**
 * @class GridGraphic
 * @brief This class is responsible for the graphical rendering of the grid in the game.
 */

#include <SDL2/SDL.h>
#include "../core/Game.h"

class Graphic;
class GridGraphic
{
private:
    Game game;             /**< The game of the grid. */
    int gridX = 0;         /**< The x and y coordinates of the grid. */
    int gridY = 0;         /**< The x and y coordinates of the grid. */
    int initialGridWidth;  /**< The initial width and height of the grid. */
    int initialGridHeight; /**< The initial width and height of the grid. */
    int initialGridX;      /**< The initial x and y coordinates of the grid. */
    int initialGridY;      /**< The initial x and y coordinates of the grid. */

    std::vector<SDL_Texture *> playerTextures, cardsTextures; /**< The textures of the players and the cards. */
    SDL_Texture *deckTexture;                                 /**< The texture of the deck. */
    SDL_Texture *caseTexture;                                 /**< The texture of the case. */
    SDL_Texture *backgroundTexture;                           /**< The texture of the background. */

    SDL_Texture *arrowUpTexture;        /**< The texture of the arrow up. */
    SDL_Texture *arrowDownTexture;      /**< The texture of the arrow down. */
    SDL_Texture *arrowLeftTexture;      /**< The texture of the arrow left. */
    SDL_Texture *arrowRightTexture;     /**< The texture of the arrow right. */
    SDL_Texture *arrowTurnLeftTexture;  /**< The texture of the arrow left. */
    SDL_Texture *arrowTurnRightTexture; /**< The texture of the arrow right. */

    SDL_Texture *addToRulesTexture; /**< The texture of the add to rules button. */
    SDL_Texture *logo;              /**< The texture of the logo. */
    SDL_Texture *score;             /**< The texture of the score. */
    SDL_Texture *shadowCard;        /**< The texture of the shadow card. */
    SDL_Texture *applyTexture;      /**< The texture of the apply button. */

public:
    /**
     * @brief Constructor for the GridGraphic class.
     */
    GridGraphic();

    /**
     * @brief Constructor for the GridGraphic class.
     *
     * @param renderer The renderer of the game.
     * @param player1 The first player of the game.
     * @param player2 The second player of the game.
     */
    GridGraphic(SDL_Renderer *renderer, Player player1, Player player2);
    /**
     * @brief Destructor for the GridGraphic class.
     */
    ~GridGraphic();

    /**
     * @brief Shows the grid on the screen.
     *
     * @param renderer The renderer of the game.
     * @param graphic The graphic of the game.
     */
    void showGrid(SDL_Renderer *renderer, Graphic &graphic);

    /**
     * @brief Moves the grid on the screen.
     *
     * @param dx The change in the x coordinate of the grid.
     * @param dy The change in the y coordinate of the grid.
     */
    void moveGrid(int dx, int dy);

    /**
     * @brief Gets the x coordinate of the grid.
     *
     * @return The x coordinate of the grid.
     */
    int getGridX() { return gridX; }

    /**
     * @brief Gets the y coordinate of the grid.
     *
     * @return The y coordinate of the grid.
     */
    int getGridY() { return gridY; }

    /**
     * @brief Gets the width of a case in the grid.
     *
     * @return The width of a case in the grid.
     */
    int getCaseWidth() { return 100; }

    /**
     * @brief Gets the height of a case in the grid.
     *
     * @return The height of a case in the grid.
     */
    int getCaseHeight() { return 100; }

    /**
     * @brief Gets the game of the grid.
     *
     * @return The game of the grid.
     */
    Game &getGame();

    /**
     * @brief Sets the game of the grid.
     *
     * @param game The game of the grid.
     */
    void setGame(Game game) { this->game = game; }

    /**
     * @brief Draws the deck on the screen.
     *
     * @param renderer The renderer of the game.
     * @param graphic The graphic of the game.
     */
    void drawDeck(SDL_Renderer *renderer, Graphic &graphic);

    /**
     * @brief Draws the global rules on the screen.
     *
     * @param renderer The renderer of the game.
     * @param graphic The graphic of the game.
     */
    void drawGlobalrules(SDL_Renderer *renderer, Graphic &graphic);

    /**
     * @brief set the initial grid size
     *
     * @param width The width of the grid.
     * @param height The height of the grid.
     */
    void setInitialGridSize(int width, int height);

    /**
     * @brief Draw all the part of the interface
     *
     * @param renderer The renderer of the game.
     * @param graphic The graphic of the game.
     */
    void drawPartInterface(SDL_Renderer *renderer, Graphic &graphic);

    /**
     * @brief Draw the pioche
     *
     * @param renderer The renderer of the game.
     * @param graphic The graphic of the game.
     */
    void drawPioche(SDL_Renderer *renderer, Graphic &graphic);

    /**
     * @brief Draw the arrows for the card direction
     *
     * @param renderer The renderer of the game.
     * @param graphic The graphic of the game.
     */
    void drawArrowDirection(SDL_Renderer *renderer, Graphic &graphic);

    /**
     * @brief Draw the add to global rules button
     *
     * @param renderer The renderer of the game.
     * @param graphic The graphic of the game.
     */
    void drawGlobalRuleButton(SDL_Renderer *renderer, Graphic &graphic);

    /**
     * @brief Initialise all the card texture
     *
     * @param renderer The renderer of the game.
     */
    void initCardTexture(SDL_Renderer *renderer);

    /**
     * @brief Draw all the part for the info of the game
     *
     * @param renderer The renderer of the game.
     * @param graphic The graphic of the game.
     */
    void drawInfoPart(SDL_Renderer *renderer, Graphic &graphic);

    /**
     * @brief Draw the details on the card
     *
     * @param renderer The renderer of the game.
     * @param graphic The graphic of the game.
     */

    void drawCardDetails(Card *card, Graphic &graphic, int cardX, int cardY, int indiceCard);
    /**
     * @brief Get the texture of the player.
     *
     * @param indice The indice of the player.
     *
     * @return The texture of the player.
     */
    SDL_Texture *getPlayerTexture(int indice);
};

#endif // GRAPHIC_GRID
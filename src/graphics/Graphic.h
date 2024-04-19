#ifndef GRAPHIC
#define GRAPHIC

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "GridGraphic.h"

/**
 *@enum GameState
 * @brief Enumeration of the game states.
 */

enum class GameState
{
    Menu,
    Game,
    ChooseGameMode,
    CreateOnlineGame,
    JoinOnlineGame,
    ChooseCreateOrJoin,
    GameCreation,
    Options,
    Pause,
    Credits,
    Quit,
    End
};

/**
 * @class Graphic
 * @brief This class is responsible for all the graphical rendering in the game.
 */

class Graphic
{

private:
    SDL_Window *window;     /**< The window of the game. */
    SDL_Renderer *renderer; /**< The renderer of the game. */
    SDL_Color color;        /**< The color of the renderer. */
    TTF_Font *font;         /**< The font of the renderer. */
    SDL_Color fontColor;    /**< The color of the font. */
    int fontStyle;          /**< The style of the font. */

    GridGraphic grid; /**< The grid of the game. */

    Card *cardClicked;          /**< The card of the game. */
    bool isCardClicked = false; /**< The state of the card. */

public:
    SDL_Rect background_rules;          // The part of the screen where the deck is
    SDL_Rect newCard;            // The part of the screen where the draw is
    SDL_Rect globalRuleButton;  // The part of the screen where the global rule button is
    SDL_Rect background_deck;        // The part of the screen where the background is
    SDL_Rect logo;              // The part of the screen where the logo is
    SDL_Rect currentPlayerRect; // The part of the screen where the current player is
    SDL_Rect scoreRect;         // The part of the screen where the score is
    SDL_Rect playerMiniRect;    // The part of the screen where the mini player is
    SDL_Rect shadowRect;        // The part of the screen where the card shadow is

    int fontSize;
    int cardHeight = 150;
    int cardWidth = 100;
    int caseWidth = 100;
    int small_caseWidth = 50;
    int arrowWidth = 100;
    int deckHeight;
    int deckWidht;
    int margin = 50;
    int small_margin = 25;
    int gap = 5;
    int globalMargin;
    float cardZoomFactor = 1.1f;
    int windowWidth, windowHeight;

    /**
     * @brief Constructor for the Graphic class.
     *
     * Initializes the color, font, fontColor, fontSize, and fontStyle.
     */
    Graphic();

    /**
     * @brief Constructor for the Graphic class.
     *
     * Initializes the window, renderer, color, font, fontColor, fontSize, and fontStyle.
     *
     * @param window The window of the game.
     * @param renderer The renderer of the game.
     */

    Graphic(SDL_Window *window, SDL_Renderer *renderer);

    /**
     * @brief Constructor for the Graphic class.
     *
     * Initializes the window, renderer, color, font, fontColor, fontSize, and fontStyle.
     *
     * @param window The window of the game.
     * @param renderer The renderer of the game.
     * @param player1 The first player of the game.
     * @param player2 The second player of the game.
     */
    Graphic(SDL_Window *window, SDL_Renderer *renderer, Player player1, Player player2);

    /**
     * @brief Destructor for the Graphic class.
     *
     * Destroys the renderer and window.
     */
    ~Graphic();

    /**
    * @brief Update global values used by the interface depending on the window size.
    */
    void updateInterface();

    /**
     * @brief Draws text on the screen.
     *
     * @param text The text to be drawn.
     * @param x The x coordinate of the text.
     * @param y The y coordinate of the text.
     */
    void drawText(const char *text, int x, int y);

    /**
     * @brief Clears the screen.
     */
    void clear();

    /**
     * @brief Presents the screen.
     */
    void present();

    /**
     * @brief Handle all the event of the game.
     */
    void eventHolder(GameState &gamestate);

    /**
     * @brief Handle the quit event of the game.
     */
    void handleQuitEvent(GameState &gamestate);

    /**
     * @brief Handle the mouse button down event of the game.
     *
     * @param event The event to be handled.
     */
    void handleMouseButtonDownEvent(SDL_Event &event);

    /**
     * @brief Handle the key down event of the game.
     *
     * @param event The event to be handled.
     */
    void handleKeyDownEvent(SDL_Event &event, GameState &gamestate);

    /**
     * @brief Play the game.
     */
    void play(GameState &gamestate);

    /**
     * @brief Draw the game.
     */
    void draw();
    /**
     * @brief Apply global rules one by one.
     */
    void gameloop();

    /**
     * @brief Handle the check win event of the game.
     *
     * @param cellX The x coordinate of the cell to be checked.
     * @param cellY The y coordinate of the cell to be checked.
     * @param game The game to be checked.
     */
    void handleCheckWin(int cellX, int cellY, Game game);

    /**
     * @brief Check if the mouse is clicked on the interface of the game.
     *
     * @param x  The x coordinate of the mouse.
     * @param y  The y coordinate of the mouse.
     *
     * @return true if the mouse is clicked on the interface of the game, false otherwise
     */
    bool MouseClickInterface(int x, int y);

    /**
     * @brief Check if the card is empty
     *
     * @return true if the card is empty, false otherwise
     *
     */
    bool isCardEmpty();

    /**
     * @brief Delete the card
     *
     */
    void deleteCard();

    /**
     * @brief Set the card
     *
     * @param card The card to be set
     */
    void setCard(Card *card);

    /**
     * @brief Get the card that is clicked
     *
     * @return The card
     */
    Card *getCard();

    /**
     * @brief Handle the arrow click event of the game.
     *
     * @param mouseX The x coordinate of the mouse.
     * @param mouseY The y coordinate of the mouse.
     * @param screenWidth The width of the screen.
     * @param screenHeight The height of the screen.
     *
     */
    void handleArrowClick(int mouseX, int mouseY, int screenWidth, int screenHeight);

    /**
     * @brief Handle the global rule button click event of the game.
     *
     * @param mouseX The x coordinate of the mouse.
     * @param mouseY The y coordinate of the mouse.
     * @param screenWidth The width of the screen.
     * @param screenHeight The height of the screen.
     *
     */
    void handleGlobalRuleButtonClick(int mouseX, int mouseY, int screenWidth, int screenHeight);

    /**
     * @brief Get the GridGraphic of the game.
     *
     * @return The GridGraphic of the game.
     *
     */
    GridGraphic &getGrid() { return grid; };

    /**
     * @brief Get the winner id of the game.
     *
     * @return The winner id of the game.
     *
     */
    int getWinnerId();

    /**
     * @brief Get the winner texture of the game.
     *
     * @return The winner texture of the game.
     *
     */
    SDL_Texture *getWinnerTexture();
};

#endif // GRAPHIC

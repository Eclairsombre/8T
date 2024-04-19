#ifndef PLAYER
#define PLAYER

#include <vector>
#include <iostream>
#include <map>
#include <tuple>
#include "Deck.h"

/**
 * @brief Structure to store the effects of a player
 */
struct PlayerEffects
{
    bool posePiece; /**< Test */
};

/**
 * @class Player
 * @brief This class is used to represent a player in the game
 */
class Player
{
private:
    std::string symbol;          /**< Symbol of the player */
    std::string color;           /**< Color of the player */
    int currentGrid;             /**< Current grid of the player */
    std::vector<Deck> decks;     /**< Decks of the player */
    PlayerEffects playerEffects; /**< Effects of the player */
    int score = 0;              /**< Score of the player */

public:
    /**
     * @brief Construct a new Player object
     *
     */
    Player();

    /**
     * @brief Construct a new Player object
     *
     * @param symbol
     * @param color
     */
    Player(std::string symbol, std::string color);

    /**
     * @brief Destroy the Player object
     *
     */
    ~Player();

    /**
     * @brief Get the symbol of the player
     *
     */
    std::string getSymbol();

    /**
     * @brief Get the current grid of the player
     *
     * @return string
     *
     */
    int getCurrentGrid();

    /**
     * @brief Get the color of the player
     *
     * @return std::string
     *
     */
    std::string getColor();

    /**
     * @brief Convert a string to a RGB color
     *
     * @return std::tuple<int, int, int>
     *
     */
    std::tuple<int, int, int> stringToRgb();

    /**
     * @brief Get a deck of the player
     *
     * @param index
     * @return Deck
     */
    Deck getDeck(int index);
    /**
     * @brief Get the player effects
     *
     * @return PlayerEffects
     */
    PlayerEffects &getPlayerEffects();

    /**
     * @brief Set the player effects
     *
     * @param playerEffects
     */
    void setPlayerEffects(PlayerEffects playerEffects);

    /**
     * @brief Make the player draw a card
     *
     */
    void drawCard();

    
    /**
     * @brief Set the deck of the player
     *
     * @param index
     * @param deck
     */
    void setDeck(int index, Deck deck);

    /**
     * @brief Get the score of the player
     *
     */
    int getScore();

    /**
     * @brief Set the score of the player
     *
     * @param score
     */
    void setScore(int score);
};

#endif // PLAYER
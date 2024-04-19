#ifndef CARD
#define CARD

#include <string>
#include <iostream>
#include <vector>
class Game;
class Player;

/**
 * @enum CardId
 * @brief This enum is used to represent the different cards id in the game
 */

enum
{
    Id,
    GravityId,
    AddLineId,
    AddColumnId,
    TurnGridId,
    RemoveLineId,
    RemoveColumnId,
    PlacePieceId,
    PlayCardId,
    DrawCardId,
    SwitchPlayerId,
    AlignToWinId,
    AlignToWinPlusOneId,
    AlignToWinMinusOneId,
    EndId,
    PlayPlaceOrPickId,
    CardEndPlusOneId,
    CardEndMinusOneId

};

/**
 * @class Card
 * @brief This class is used to represent a card in the game
 */
class Card
{
protected:
    std::string name;                        //< The name of the card
    std::string description;                 //< The description of the card
    int id;                                  //< The id of the card
    int uniqueId;                            //< The unique id of the card in the game
    std::vector<std::string> arrowDirection; //< The direction of the arrow of the card if it has one
    bool isGlobalRule;                       //< if the card is a global rule
    bool canBeGlobalRules = false;           //< if the card can be a global rule
    double minimumSecondsDelay = 0.7;        //< The minimum delay between 2 rules

public:
    /**
     * @brief Construct a new Card object
     *
     * @param name
     * @param description
     * @param id
     */
    Card(std::string name, std::string description, int id);

    /**
     * @brief Destroy the Card object
     *
     */
    virtual ~Card(){};

    /**
     * @brief Get the Name object
     *
     * @return std::string
     */
    std::string getName();

    /**
     * @brief Get the id of the card
     *
     * @return int
     */
    int getId() { return id; }

    /**
     * @brief Overload of the == operator between 2 cards
     *
     * @return std::bool
     */
    bool operator==(const Card &other) const;

    /**
     * @brief Apply the card to the game , made to be overriden by the child Card classes
     *
     * @param x
     * @param y
     * @param currentGrid
     * @param currentPlayer
     * @param game
     * @param sens
     */
    virtual void applyCard(int x, int y, int currentGrid, Player &currentPlayer, Game &game, std::string sens)
    {
        std::cout << "This is not supposed to show up" << std::endl;
    };

    /**
     * @brief Copy constructor of the card
     *
     * @param other
     */
    Card(const Card &other);

    /**
     * @brief Create a new card and apply it dirrectly to the game, made for the networking
     *
     * @param id
     * @param x
     * @param y
     * @param currentGrid
     * @param currentPlayer
     * @param game
     * @param sens
     */
    void createNewCardAndApply(int id, int x, int y, int currentGrid, Player &currentPlayer, Game &game, std::string sens);

    /**
     * @brief Get the direction of the arrow of the card
     *
     * @return std::vector<std::string>
     */
    std::vector<std::string> getArrowDirection();

    /**
     * @brief Set the unique id of the card
     *
     * @param id
     */
    void setUniqueId(int id) { uniqueId = id; };

    /**
     * @brief Get the unique id of the card
     *
     * @return int
     */
    int getUniqueId() { return uniqueId; };

    /**
     * @brief Set the global rule state of the card
     *
     * @param state
     */
    bool isAGlobalRule() const;

    /**
     * @brief Set the global rule state of the card
     *
     * @param state
     */
    void setGlobalRuleState(bool state);

    /**
     * @brief Apply the global rule of the card
     *
     * @param game
     * @param CurrentGrid
     */
    void applyWhenGlobalRule(Game &game, int CurrentGrid);

    /**
     * @brief Get the can be global attribute of the card
     *
     * @return bool
     */
    bool getCanBeGlobal() { return canBeGlobalRules; }

    /**
     * @brief Update the time to have delay between rule execution
     *
     * @param game The game
     * @param CurrentGrid The current grid
     *
     * @return bool
     */
    void updateTime(Game &game, int CurrentGrid);
};

#endif // CARD
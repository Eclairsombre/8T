#ifndef PIECE
#define PIECE

#include <map>
#include <string>
#include <vector>

/**
 * @brief Structure to store the effects of a piece
 */
struct PieceEffects
{
    bool test; /**< Test */
};

/**
 * @class Piece
 * @brief This class is used to represent a piece in the game
 */

class Piece
{
private:
    std::string symbol;        /**< Symbol of the piece */
    std::string color;         /**< Color of the piece */
    PieceEffects pieceEffects; /**< Effects of the piece */

public:
    /**
     * @brief Construct a new Piece object
     *
     */
    Piece();

    /**
     * @brief Construct a new Piece object
     *
     * @param symbol
     * @param color
     * @param pieceEffects
     */
    Piece(std::string symbol, std::string color, PieceEffects pieceEffects);

    /**
     * @brief Destroy the Piece object
     *
     */
    ~Piece();

    /**
     * @brief Set the symbol of the piece
     *
     * @param symbol
     */
    void setSymbol(std::string symbol);

    /**
     * @brief Set the color of the piece
     *
     * @param color
     */
    void setColor(std::string symbol);

    /**
     * @brief Set the effects of the piece
     *
     * @param pieceEffects
     */
    std::string getSymbol() const;

    /**
     * @brief Get the color of the piece
     *
     * @return std::string
     */
    std::string getColor() const;

    /**
     * @brief Get the effects of the piece
     *
     * @return PieceEffects
     */
    PieceEffects getEffects() const;
};

#endif // PIECE
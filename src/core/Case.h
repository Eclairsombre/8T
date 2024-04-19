#ifndef CASE
#define CASE

#include <map>
#include <string>
#include <vector>
#include "Piece.h"

/**
 * @brief Structure to store the effects of a case
 */
struct CaseEffects
{
    /* data */
};

/**
 * @class Case
 * @brief This class is used to represent a case in the game
 */
class Case
{
private:
    std::vector<Piece> pieces; /**< Pieces on the case */
    CaseEffects caseEffects;   /**< Effects of the case */

public:
    /**
     * @brief Construct a new Case object
     *
     */
    Case();

    /**
     * @brief Construct a new Case object
     *
     * @param pieces
     * @param caseEffects
     */
    Case(std::vector<Piece> pieces, CaseEffects caseEffects);

    /**
     * @brief Destroy the Case object
     *
     */
    ~Case();

    /**
     * @brief Add a piece to the case
     *
     * @param piece
     */
    void addPiece(const Piece &piece);


    /**
     * @brief Get the pieces on the case
     *
     * @return std::vector<Piece>
     */
    std::vector<Piece> getPieces() const;

    /**
     * @brief Get the effects of the case
     *
     * @return CaseEffects
     */
    CaseEffects getEffects() const;

    /**
     * @brief Check if the case is empty
     *
     * @return true
     * @return false
     */
    bool isPiecesEmpty() const;

    /**
     * @brief Overload the = operator
     *
     * @param c
     * @return Case
     */
    Case operator=(const Case &c);
};

#endif // CASE

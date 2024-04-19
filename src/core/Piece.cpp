#include "Piece.h"

Piece::Piece()
{
    this->symbol = "";
    this->color = "";
    this->pieceEffects = PieceEffects();
}

Piece::Piece(std::string symbol, std::string color, PieceEffects pieceEffects)
{
    this->symbol = symbol;
    this->color = color;
    this->pieceEffects = pieceEffects;
}

Piece::~Piece()
{
}

void Piece::setSymbol(std::string symbol)
{
    this->symbol = symbol;
}

void Piece::setColor(std::string color)
{
    this->color = color;
}

std::string Piece::getSymbol() const
{
    return this->symbol;
}

std::string Piece::getColor() const
{
    return this->color;
}

PieceEffects Piece::getEffects() const
{
    return this->pieceEffects;
}

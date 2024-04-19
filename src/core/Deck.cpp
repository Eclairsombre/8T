#include "Deck.h"
#include "./rules/RulesRare.hpp"
#include "./rules/RulesCommun.hpp"
#include "./rules/GlobalRules.hpp"

Deck::Deck()
{
}

Deck::Deck(std::vector<Card *> cards) : cards(cards)
{
}

Deck::~Deck()
{
}

void Deck::addCard(const Card &card)
{
    this->cards.push_back(new Card(card));
}

void Deck::setBaseCard()
{
}

std::vector<Card *> Deck::getCards()
{
    return this->cards;
}

void Deck::drawCard()
{
    int randomIndex = rand() % 17 + 1;
    switch (randomIndex)
    {
    case GravityId:
    {
        CardGravity *card = new CardGravity("Gravity", "Pose une pièce sur le plateau", GravityId);
        card->setUniqueId(uniqueIdCounter);
        uniqueIdCounter++;
        this->cards.push_back(card);
        break;
    }
    case AddLineId:
    {
        CardAddLine *card = new CardAddLine("AddLine", "Ajoute une ligne au plateau", AddLineId);
        card->setUniqueId(uniqueIdCounter);
        uniqueIdCounter++;
        this->cards.push_back(card);
        break;
    }
    case AddColumnId:
    {
        CardAddColumn *card = new CardAddColumn("AddColumn", "Ajoute une colonne au plateau", AddColumnId);
        card->setUniqueId(uniqueIdCounter);
        uniqueIdCounter++;
        this->cards.push_back(card);
        break;
    }
    case TurnGridId:
    {
        CardTurnGrid *card = new CardTurnGrid("TurnGrid", "Tourne le plateau", TurnGridId);
        card->setUniqueId(uniqueIdCounter);
        uniqueIdCounter++;
        this->cards.push_back(card);
        break;
    }
    case RemoveLineId:
    {
        CardRemoveLine *card = new CardRemoveLine("RemoveLine", "Supprime une ligne du plateau", RemoveLineId);
        card->setUniqueId(uniqueIdCounter);
        uniqueIdCounter++;
        this->cards.push_back(card);
        break;
    }
    case RemoveColumnId:
    {
        CardRemoveColumn *card = new CardRemoveColumn("RemoveCol", "Supprime une colonne du plateau", RemoveColumnId);
        card->setUniqueId(uniqueIdCounter);
        uniqueIdCounter++;
        this->cards.push_back(card);
        break;
    }
    case PlacePieceId:
    {
        CardPlacePiece *card = new CardPlacePiece("PlacePiece", "Pose une pièce sur le plateau", PlacePieceId);
        card->setUniqueId(uniqueIdCounter);
        uniqueIdCounter++;
        this->cards.push_back(card);
        break;
    }
    case PlayCardId:
    {
        CardPlayCard *card = new CardPlayCard("PlayCard", "Joue une carte", PlayCardId);
        card->setUniqueId(uniqueIdCounter);
        uniqueIdCounter++;
        this->cards.push_back(card);
        break;
    }
    case DrawCardId:
    {
        CardDrawCard *card = new CardDrawCard("DrawCard", "Pioche une carte", DrawCardId);
        card->setUniqueId(uniqueIdCounter);
        uniqueIdCounter++;
        this->cards.push_back(card);
        break;
    }
    case AlignToWinId:
    {
        CardAlignToWin *card = new CardAlignToWin("AlignToWin", "Le nombre d'alignement pour gagner", AlignToWinId);
        card->setUniqueId(uniqueIdCounter);
        uniqueIdCounter++;
        this->cards.push_back(card);
        break;
    }
    case AlignToWinPlusOneId:
    {
        CardAlignToWinPlusOne *card = new CardAlignToWinPlusOne("AlignToWinPlusOne", "Le nombre d'alignement pour gagner +1", AlignToWinPlusOneId);
        card->setUniqueId(uniqueIdCounter);
        uniqueIdCounter++;
        this->cards.push_back(card);
        break;
    }
    case AlignToWinMinusOneId:
    {
        CardAlignToWinMinusOne *card = new CardAlignToWinMinusOne("AlignToWinMinusOne", "Le nombre d'alignement pour gagner -1", AlignToWinMinusOneId);
        card->setUniqueId(uniqueIdCounter);
        uniqueIdCounter++;
        this->cards.push_back(card);
        break;
    }
    case EndId:
    {
        CardEnd *card = new CardEnd("End", "Termine le tour", EndId);
        card->setUniqueId(uniqueIdCounter);
        uniqueIdCounter++;
        this->cards.push_back(card);
        break;
    }
    case PlayPlaceOrPickId:
    {
        CardPickPlayOrPlace *card = new CardPickPlayOrPlace("PickPlayOrPlace", "Pose ou prend une pièce sur le plateau", PlayPlaceOrPickId);
        card->setUniqueId(uniqueIdCounter);
        uniqueIdCounter++;
        this->cards.push_back(card);
        break;
    }
    case CardEndPlusOneId:
    {
        CardEndPlusOne *card = new CardEndPlusOne("EndPlusOne", "Termine le tour +1", CardEndPlusOneId);
        card->setUniqueId(uniqueIdCounter);
        uniqueIdCounter++;
        this->cards.push_back(card);
        break;
    }
    case CardEndMinusOneId:
    {
        CardEndMinusOne *card = new CardEndMinusOne("EndMinusOne", "Termine le tour -1", CardEndMinusOneId);
        card->setUniqueId(uniqueIdCounter);
        uniqueIdCounter++;
        this->cards.push_back(card);
        break;
    }
        // case SwitchPlayerId:
        // {
        //     CardSwitchPlayer *card = new CardSwitchPlayer("CardSwitchPlayer", "Change de joueur", SwitchPlayerId);
        //     card->setUniqueId(uniqueIdCounter);
        //     uniqueIdCounter++;
        //     this->cards.push_back(card);
        //     break;
        // }

    default:
        drawCard();
        break;
    }
}

void Deck::removeCard(Card *card)
{
    auto it = std::find(this->cards.begin(), this->cards.end(), card);
    if (it != this->cards.end())
    {
        this->cards.erase(it);
    }
}

void Deck::moveCard(int direction)
{
    if (direction > 0)
    { // move card to the right
        if (!cards.empty())
        {
            std::rotate(cards.begin(), cards.begin() + 1, cards.end());
        }
    }
    else
    { // move card to the left
        if (!cards.empty())
        {
            std::rotate(cards.begin(), cards.end() - 1, cards.end());
        }
    }
}
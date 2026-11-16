#include "Player.h"

Player::Player()
{
	this->name = "Unamed Player";
	this->hand = {};
	this->score = 0;
}

string Player::getName()
{
	return this->name;
}

void Player::setName(string new_name)
{
	this->name = new_name;
}

int Player::getHandSize()
{
	return this->hand.size();
}

vector<Card> Player::getHand()
{
	return this->hand;
}

void Player::clearHand()
{
	this->hand.clear();
}

Card Player::peekCard(int index)
{
	return this->hand[index];
}

bool Player::isEmpty()
{
	return this->hand.empty();
}

Card Player::getCard(int index)
{
	//Temporary variable must be created to return object after deleting card from vector.
	Card tmp_card = this->hand[index];
	this->hand.erase(this->hand.begin() + index);
	return tmp_card;
}

void Player::addCard(Card new_card)
{
	this->hand.push_back(new_card);
}

void Player::removeCard(int index)
{
	this->hand.erase(this->hand.begin() + index);
}

int Player::sumHand()
{
	int total = 0;
	for (Card c : this->hand) {
		total += c.getRank();
	}

	return total;
}

void Player::outputHand()
{
	//Iterate through each card in hand and output toString for each one
	for (Card c : this->hand) {
		cout << c.toString() << endl;
	}
}

void Player::changeScoreBy(int toAdd)
{
	this->score += toAdd;
}

void Player::setScore(int newScore)
{
	this->score = newScore;
}

int Player::getScore()
{
	return this->score;
}

// All below this line was made by Joshua Sullivan

void Player::printHand() // Prints the player's hand in a more user-friendly format with each card on a new line and numbered for easy selection
{
	for (int i = 0; i < this->hand.size(); i++) { // Loop through each card in the player's hand
		cout << endl; // Print a blank line for spacing
		cout << this->hand[i].toString() << endl; // Print the card's toString representation with a number for easy selection
	} 
}

bool Player::hasValidMove(Card top, string currentSuit) // Checks if the player has any valid moves available based on the top card of the discard pile. A valid move is defined as having a card in the player's hand that matches the rank or suit of the top card or if the player has an eight, they can play it regardless of the rank or suit.
{
	for (Card c : this->hand) { // Iterate through each card in the player's hand
		if (c.getRank() == top.getRank() || c.getSuit() == currentSuit || c.getRank() == 8) { // Check if the card matches the rank or suit of the top card or if it is an eight
			return true; // Return true if a valid move is found
		} // End of if statement
	} // End of for loop
	return false; // Return false if no valid moves are found
}

void Player::drawCard(Card new_card) // Draws a new card from the draw deck and adds it to the player's hand.
{
	this->hand.push_back(new_card); // Add the new card to the player's hand
}
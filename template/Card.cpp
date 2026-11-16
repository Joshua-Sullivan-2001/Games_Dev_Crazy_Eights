#include "Card.h"

Card::Card(int init_rank, string init_suit)
{
	this->rank = init_rank;
	this->suit = init_suit;
}

int Card::getRank()
{
	return this->rank;
}

string Card::getSuit()
{
	return this->suit;
}

void Card::setRank(int new_rank)
{
	this->rank = new_rank;
}

void Card::setSuit(string new_suit)
{
	this->suit = new_suit;
}
/* Original toString in function
string Card::toString()
{
	return to_string(this->rank) + " of " + this->getSuit();
}
*/

// New toString function made by Joshua Sullivan to display Ace, Jack, Queen, King instead of 1, 11, 12, 13 whil e still displaying the rank of the card as an integer for other cards.
string Card::toString() // A function that returns a string representation of the card in the format "[rank] of [suit]". For example, "Ace of Hearts", "10 of Diamonds", "Queen of Spades", etc.
{
	string rankName; // Declare a variable to hold the rank name of the card

	if (this->rank == 1) { // Check if the rank is 1 (Ace)
		rankName = "Ace"; // Set the rank name to "Ace"
	} 
	else if (this->rank == 11) { // Check if the rank is 11 (Jack)
		rankName = "Jack"; // Set the rank name to "Jack"
	}
	else if (this->rank == 12) { // Check if the rank is 12 (Queen)
		rankName = "Queen"; // Set the rank name to "Queen"
	}
	else if (this->rank == 13) { // Check if the rank is 13 (King)
		rankName = "King"; // Set the rank name to "King"
	}
	else { // For all other ranks (2-10)
		rankName = to_string(this->rank); // Convert the rank to a string and set it as the rank name
	}

	return rankName + " of " + this->getSuit(); // Return the string representation of the card in the format "[rank] of [suit]"

}
// This .cpp file will hold the crazy eights full game code
#include "game.h" // Include the header file for this .cpp file
#include "Deck.h" // Include the header file for the Deck class
#include "Player.h" // Include the header file for the Player class
#include "Card.h" // Include the header file for the Card class
#include <iostream> // Include the iostream library for input/output operations
#include <cstdlib> // Include the cstdlib library for system commands
#include <vector> // Include the vector library for dynamically sized arrays

using namespace std; // Use the standard namespace to avoid prefixing standard library names with "std::"


static void gameRules(){

    system("cls"); // Clear the console screen
    
    cout << "-------------------------------------------" << endl; // Print a separator line
    cout <<"-----------" << "Crazy Eights" << "-----------" << endl; // Print welcome message
    cout << "-------------------------------------------" << endl; // Print a separator line

    cout << endl; // Print a blank line

    cout << "-------------------------------------------" << endl; // Print a separator line
    cout << "-----------" << "Game Rules" << "-----------" << endl; // Print game rules header
    cout << "-------------------------------------------" << endl; // Print a separator line
    
    cout << endl; // Print a blank line

    cout << "1. The game is played with a standard deck of 52 cards." << endl; // Print rule 1
    cout << "2. if playing with 3 - 5 players, each player is dealt 5 cards." << endl; // Print rule 2
    cout << "3. if playing with 2 players each player is dealt 7 cards." << endl; // Print rule 3
    cout << "4. The remaining cards are placed face down to form a draw pile." << endl; // Print rule 4
    cout << "5. The top card of the draw pile is turned face up to start the discard pile." << endl; // Print rule 5
    cout << "6. The player to the left of the dealer goes first." << endl; // Print rule 6
    cout << "7. On a player's turn they must play a card from their hand that matches the rank or suit of the top card of the discard pile or if they have an eight, they can play it regardless of the rank or suit." << endl; // Print rule 7
    cout << "8. If a player plays an eight, they must declare the suit that the next player must play." << endl; // Print rule 8
    cout << "9. If a player cannot play a card, they must draw a card from the draw pile." << endl; // Print rule 9
    cout << "10. If the drawn card can be played the player may play it immediately. Otherwise the turn passes to the next player." << endl; // Print rule 10
    cout << "11. If the draw pile is empty and a player cannot play a card, they must pass their turn." << endl; // Print rule 11
    cout << "12. The first player to get rid of all their cards wins the game." << endl; // Print rule 12
    cout << "13. Count the card points in the other players hands and add them to the winner's score." << endl; // Print rule 13
    cout << "14. Each eight left in a hand is worth 50 points. Each king, queen, jack or ten is worth 10 points, each ace is worth 1 point and all other number cards are worth their face value." << endl; // Print rule 14
    cout << "15. Play multiple rounds rotating the dealer to the left each time. The first player to reach 100 points (for 2 players) or 150 to 250 points (for 3 to 5 players) wins the game." << endl; // Print rule 15
    
    cout << endl; // Print a blank line
    cout << "Press any key to continue..." << endl; // Prompt the user to press any key to continue
    cin.get(); // Wait for the user to press a key

    return; // Return from the function
}

static void gameStart(){

    clearScreen(); // Clear the console screen

    cout << "Starting a new game..." << endl; // Print message indicating a new game is starting
    cout << "Press any key to continue..." << endl; // Prompt the user to press any key to continue
    cin.get(); // Wait for the user to press a key

    startGame(); // Call the startGame function to begin the game


    return; // Return from the function
}

static void clearScreen(){

    system("cls"); // Clear the console screen

    return; // Return from the function
}

static void mainMenuExit(){

    clearScreen(); // Clear the console screen

    cout << "Exiting the game..." << endl; // Print message indicating the game is exiting
    cout << "Press any key to continue..." << endl; // Prompt the user to press any key to continue
    cin.get(); // Wait for the user to press a key
    exit(0); // Exit the program with a status code of 0 (indicating successful termination)

    return; // Return from the function
}

static void mainMenu(){

    clearScreen(); // Clear the console screen

    cout << "-------------------------------------------" << endl; // Print a separator line
    cout << "-----------" << "Main Menu" << "-----------" << endl; // Print main menu header
    cout << "-------------------------------------------" << endl; // Print a separator line
    cout << endl; // Print a blank line
    cout << "1. Start New Game" << endl; // Print option 1
    cout << "2. View Game Rules" << endl; // Print option 2
    cout << "3. Exit Game" << endl; // Print option 3
    cout << endl; // Print a blank line
    cout << "Enter your choice (1-3): ";

    int choice;

    cin >> choice;

    switch(choice){
        case 1:
            gameStart();
            break;
        case 2:
            gameRules();
            break;
        case 3:
            mainMenuExit();
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            mainMenu();
    }

    return; // Return from the function
}

static int playerAmount(){

    clearScreen(); // Clear the console screen

    cout << "-------------------------------------------" << endl; // Print a separator line
    cout << "-----------" << "Player Amount" << "-----------" << endl; // Print player amount header
    cout << "-------------------------------------------" << endl; // Print a separator line
    cout << endl; // Print a blank line
    cout << "Enter the number of players (2-5): ";

    int numPlayers;

    cin >> numPlayers;

    if(numPlayers < 2 || numPlayers > 5){
        cout << "Invalid number of players. Please try again." << endl;
        return playerAmount();
    }

    return numPlayers; // Return the number of players
}

static void playerNames(int numPlayers){

    clearScreen(); // Clear the console screen

    cout << "-------------------------------------------" << endl; // Print a separator line
    cout << "-----------" << "Player Names" << "-----------" << endl; // Print player names header
    cout << "-------------------------------------------" << endl; // Print a separator line
    cout << endl; // Print a blank line

    vector<string> playerNames(numPlayers);

    for(int i = 0; i < numPlayers; i++){
        cout << "Enter name for Player " << i + 1 << ": ";
        cin >> playerNames[i];
    }

    return; // Return from the function
}

static void playerTurn(int currentPlayer, int numPlayers){

    clearScreen(); // Clear the console screen

    cout << "-------------------------------------------" << endl; // Print a separator line
    cout << "-----------" << "Player Turn" << "-----------" << endl; // Print player turn header
    cout << "-------------------------------------------" << endl; // Print a separator line
    cout << endl; // Print a blank line
    cout << "It is Player " << currentPlayer + 1 << "'s turn." << endl; // Print the current player's turn
    cout << endl; // Print a blank line
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();

    cout << endl; // Print a blank line
    cout << "Top card of the discard pile: ";
    discardPile.peakTopCard(); // Peek at the top card of the discard pile
    cout << endl; // Print a blank line

    checkHand(currentPlayer, numPlayers); // Call the check hand function to display the current player's hand



    return; // Return from the function
}

static void checkHand(int currentPlayer, int numPlayers){

    clearScreen(); // Clear the console screen

    cout << "-----------" << "Current Hand" << "-----------" << endl; // Print check hand header
    cout << endl; // Print a blank line

    cout << "Player " << currentPlayer + 1 << "'s hand: ";
    players[currentPlayer].printHand(); // Print the current player's hand
    cout << endl; // Print a blank line
    cout << "Press Enter to continue...";
    cout << endl; // Print a blank line
    cin.ignore();
    cin.get();
    

    return; // Return from the function
}

static void startGame(){


    int numPlayers; // Declare a variable to hold the number of players
    numPlayers = playerAmount(); // Call the player amount function to get the number of players

    playerNames(numPlayers); // Call the player names function to get the names of the players

    playerTurn(0, numPlayers); // Call the player turn function to start the first player's turn

    return; // Return from the function
}

static void nextRound(int currentRound){

    clearScreen(); // Clear the console screen

    cout << "-------------------------------------------" << endl; // Print a separator line
    cout << "-----------" << "Next Round" << "-----------" << endl; // Print next round header
    cout << "-------------------------------------------" << endl; // Print a separator line
    cout << endl; // Print a blank line
    cout << "Starting Round " << currentRound + 1 << "..." << endl; // Print the current round number
    cout << endl; // Print a blank line
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();

    return; // Return from the function
}



static void rulesForGameCodeWhilePlaying(){
    // Automatic rules for the game code while playing, to ensure that the game is played correctly and fairly. This function will be called at the start of each player's turn in the background to ensure they can only make valid moves and that the game is played correctly. This function will also be called at the end of each player's turn to ensure that the game state is updated correctly and that the next player can only make valid moves.

    // ranks: 2 - 10, jack, queen, king, ace, 8
    //check if any player has a valid move in order to not prematurely end the game. If no player has a valid move, the game is a draw. If a player has no cards left, they win the game. If a player has no valid moves, they must draw a card from the draw pile. If the drawn card can be played, they may play it immediately. Otherwise, the turn passes to the next player. If the draw pile is empty and a player cannot play a card, they must pass their turn. If both the draw and discard piles are empty but player has valid moves, they may play a card. If both the draw and discard piles are empty and player has no valid moves, they must pass their turn. If both the draw and discard piles are empty and player has only one card left, they must pass their turn. If both the draw and discard piles are empty and player has valid moves but only one card left, they may play a card. So short, the game will continue until a player has no cards left or both the draw and discard piles are empty and no player has valid moves. The game will also continue until a player has no cards left or both the draw and discard piles are empty and a player has only one card left. The game will also continue until a player has no cards left or both the draw and discard piles are empty and a player has valid moves but only one card left and will only end after they play that final card.


    if (drawDeck.isEmpty() && discardPile.isEmpty() && players[currentPlayer].getHandSize() == 0) {
        cout << "The draw pile and discard pile are both empty. The game is a draw." << endl;
        exit(0); // Exit the game if both piles are empty
    }
    else if (players[currentPlayer].getHandSize() == 0) {
        cout << "Player " << currentPlayer + 1 << " has no cards left. They win the game!" << endl;
        exit(0); // Exit the game if a player has no cards left
    }
    else if (players[currentPlayer].getHandSize() > 0 && players[currentPlayer].hasValidMove(discardPile.getTopCard()) == false) {
        cout << "Player " << currentPlayer + 1 << " has no valid moves. They must draw a card." << endl;
        players[currentPlayer].drawCard(drawDeck); // Draw a card from the draw pile
    }
    else if (players[currentPlayer].getHandSize() > 0 && players[currentPlayer].hasValidMove(discardPile.getTopCard()) == true) {
        cout << "Player " << currentPlayer + 1 << " has valid moves. They may play a card." << endl;
    }
    else if (players[currentPlayer].getHandSize() > 0 && players[currentPlayer].hasValidMove(discardPile.getTopCard()) == false && drawDeck.isEmpty()) {
        cout << "Player " << currentPlayer + 1 << " has no valid moves and the draw pile is empty. They must pass their turn." << endl;
    }
    else if (players[currentPlayer].getHandSize() > 0 && players[currentPlayer].hasValidMove(discardPile.getTopCard()) == true && drawDeck.isEmpty()) {
        cout << "Player " << currentPlayer + 1 << " has valid moves but the draw pile is empty. They may play a card." << endl;
    }
    else if (players[currentPlayer].getHandSize() > 0 && players[currentPlayer].hasValidMove(discardPile.getTopCard()) == false && drawDeck.isEmpty() && discardPile.isEmpty()) {
        cout << "Player " << currentPlayer + 1 << " has no valid moves and both the draw pile and discard pile are empty. They must pass their turn." << endl;
    }
    else if (players[currentPlayer].getHandSize() > 0 && players[currentPlayer].hasValidMove(discardPile.getTopCard()) == true && drawDeck.isEmpty() && discardPile.isEmpty()) {
        cout << "Player " << currentPlayer + 1 << " has valid moves but both the draw pile and discard pile are empty. They may play a card." << endl;
    }
    else if (players[currentPlayer].getHandSize() > 0 && players[currentPlayer].hasValidMove(discardPile.getTopCard()) == false && drawDeck.isEmpty() && discardPile.isEmpty() && players[currentPlayer].getHandSize() == 1) {
        cout << "Player " << currentPlayer + 1 << " has no valid moves, both the draw pile and discard pile are empty, and they have only one card left. They must pass their turn." << endl;
    }
    else if (players[currentPlayer].getHandSize() > 0 && players[currentPlayer].hasValidMove(discardPile.getTopCard()) == true && drawDeck.isEmpty() && discardPile.isEmpty() && players[currentPlayer].getHandSize() == 1) {
        cout << "Player " << currentPlayer + 1 << " has valid moves, both the draw pile and discard pile are empty, and they have only one card left. They may play a card." << endl;
    }

    // Aces are 1

    // suits: hearts, diamonds, clubs, spades

    // 8 is a wild card and can be played on any card. When an 8 is played, the player must declare the suit that the next player must play.

    // If a player cannot play a card, they must draw a card from the draw pile. If the drawn card can be played, the player may play it immediately. Otherwise, the turn passes to the next player.

    // If the draw pile is empty and a player cannot play a card, they must pass their turn.

    // The first player to get rid of all their cards wins the game. Count the card points in the other players hands and add them to the winner's score. Each 8 left in a hand is worth 50 points. Each king, queen, jack or ten is worth 10 points, each ace is worth 1 point and all other number cards are worth their face value.

    // Play multiple rounds rotating the dealer to the left each time. The first player to reach 100 points (for 2 players) or 150 to 250 points (for 3 to 5 players) wins the game.

    // The game can be played with 2 to 5 players. If playing with 3 - 5 players, each player is dealt 5 cards. If playing with 2 players, each player is dealt 7 cards. The remaining cards are placed face down to form a draw pile. The top card of the draw pile is turned face up to start the discard pile. The player to the left of the dealer goes first.

    // The game is played with a standard deck of 52 cards.

}

static void playerScores(vector<int> playerScores){

    clearScreen(); // Clear the console screen

    cout << "-------------------------------------------" << endl; // Print a separator line
    cout << "-----------" << "Player Scores" << "-----------" << endl; // Print player scores header
    cout << "-------------------------------------------" << endl; // Print a separator line
    cout << endl; // Print a blank line

    for(int i = 0; i < playerScores.size(); i++){
        cout << "Player " << i + 1 << "'s score: " << playerScores[i] << endl; // Print the score of each player
    }

    cout << endl; // Print a blank line
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();

    return; // Return from the function
}

static void countScore(int winner, vector<int> playerScores){

    clearScreen(); // Clear the console screen

    cout << "-------------------------------------------" << endl; // Print a separator line
    cout << "-----------" << "Score Count" << "-----------" << endl; // Print score count header
    cout << "-------------------------------------------" << endl; // Print a separator line
    cout << endl; // Print a blank line
    cout << "Player " << winner + 1 << " wins this round!" << endl; // Print the winner of the round
    cout << endl; // Print a blank line

    for(int i = 0; i < playerScores.size(); i++){
        if(i != winner){
            cout << "Player " << i + 1 << "'s score: " << playerScores[i] << endl; // Print the score of each player
        }
    }

    cout << endl; // Print a blank line
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();

    return; // Return from the function
}

int main(){

    clearScreen(); // Clear the console screen

    Deck drawDeck; // Create a new Deck object
    drawDeck.shuffle(); // Shuffle the deck of cards

    Deck discardPile; // Create a new Deck object for the discard pile
    discardPile.clear(); // Clear the discard pile to ensure it starts empty

    discardPile.addCard(drawDeck.getTopCard()); // Add the top card from the main deck to the discard pile
    























    mainMenu(); // Call the main menu function to start the game


    return 0;
}
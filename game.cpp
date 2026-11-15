// This .cpp file will hold the crazy eights full game code
#include "game.h" // Include the header file for this .cpp file
#include "template/Deck.h" // Include the header file for the Deck class
#include "template/Player.h" // Include the header file for the Player class
#include "template/Card.h" // Include the header file for the Card class
#include <iostream> // Include the iostream library for input/output operations
#include <cstdlib> // Include the cstdlib library for system commands
#include <vector> // Include the vector library for dynamically sized arrays
using namespace std; // Use the standard namespace to avoid prefixing standard library names with "std::"

// Declare global variables for the draw deck, discard pile, players and current player index

Deck drawDeck; // Declare a global variable for the draw deck
Deck discardPile; // Declare a global variable for the discard pile
vector<Player> players; // Declare a global variable for the vector of players
int currentPlayer = 0; // Declare a global variable for the current player index

// Declare function prototypes for the compiler to recognize the functions before they are defined

static void gameRules(); // Declare a function to display the game rules
static void gameStart(); // Declare a function to start the game
static void clearScreen(); // Declare a function to clear the console screen
static void mainMenuExit(); // Declare a function to exit the game from the main menu
static void mainMenu(); // Declare a function to display the main menu
static int playerAmount(); // Declare a function to get the number of players
static void playerNames(int numPlayers); // Declare a function to get the names of the players
static void playerTurn(int currentPlayer, int numPlayers); // Declare a function to handle a player's turn
static void checkHand(int currentPlayer, int numPlayers); // Declare a function to check a player's hand for valid moves
static void startGame(); // Declare a function to start the game
static void nextRound(int currentRound); // Declare a function to start the next round
static void activeValidatorForRulesDuringGamePlay(); // Declare a function to validate the game rules
static void playerScores(vector<int> playerScores); // Declare a function to display the scores of the players
static void countScore(int winner, vector<int> playerScores); // Declare a function to count the scores of the players and display the winner
static int readNumber(); // Declare a function to read a number from the user input


static int readNumber(){

    int number; // Declare a variable to hold the number input by the user
    
    if (!(cin >> number)){ // Check if the input is not a number
        cin.clear(); // Clear the error flag on cin
        number = 0; // Set the number to 0 if the input is not a number
    }

    cin.ignore(10000, '\n'); // Ignore the rest of the input line to prevent any leftover characters from affecting future input
    return number; // Return the number input by the user

}

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

    int choice = readNumber(); // Read the user's choice using the readNumber function

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
            cout << "Press any key to continue..." << endl; // Prompt the user to press any key to continue
            cin.get(); // Wait for the user to press a key
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

    int numPlayers = readNumber(); // Read the number of players using the readNumber function

    if(numPlayers < 2 || numPlayers > 5){
        cout << "Invalid number of players. Please try again." << endl;
        cout << "Press any key to continue..." << endl; // Prompt the user to press any key to continue
        cin.get(); // Wait for the user to press a key
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

    players.clear(); // Clear the players vector to ensure it starts empty

    for(int i = 0; i < numPlayers; i++){
        string name; // Declare a variable to hold the player's name
        cout << "Enter name for Player " << i + 1 << ": ";
        getline(cin, name); // Get the player's name from input

        if (name.empty()) { // Check if the name is empty
            name = "Player " + to_string(i + 1); // Assign a default name if the input is empty
        }
        Player newPlayer; // Create a new Player object
        newPlayer.setName(name); // Set the player's name
        players.push_back(newPlayer); // Add the new Player object to the players vector

    }

    return; // Return from the function
}

static void playerTurn(int currentPlayer, int numPlayers){

    clearScreen(); // Clear the console screen

    cout << "-------------------------------------------" << endl; // Print a separator line
    cout << "-----------" << "Player Turn" << "-----------" << endl; // Print player turn header
    cout << "-------------------------------------------" << endl; // Print a separator line
    cout << endl; // Print a blank line
    cout << "It is " << players[currentPlayer].getName() << "'s turn." << endl; // Print the current player's turn
    cout << endl; // Print a blank line
    cout << "Press Enter to continue...";
    cin.get();

    checkHand(currentPlayer, numPlayers); // Call the check hand function to display the current player's hand

    return; // Return from the function
}

static void checkHand(int currentPlayer, int numPlayers){

    clearScreen(); // Clear the console screen

    cout << "The top card of the discard pile is: " << discardPile.peekTopCard().toString() << endl; // Print the top card of the discard pile
    cout << endl; // Print a blank line


    cout << "-----------" << "Current Hand" << "-----------" << endl; // Print check hand header
    cout << endl; // Print a blank line

    cout << "Player " << players[currentPlayer].getName() << "'s hand: ";
    players[currentPlayer].printHand(); // Print the current player's hand
    cout << endl; // Print a blank line
    cout << "Press Enter to continue...";
    cout << endl; // Print a blank line
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
    cin.get();

    return; // Return from the function
}

static void activeValidatorForRulesDuringGamePlay(){

    // This function will be called at the start of each player's turn in the background to ensure they can only make valid moves and that the game is played correctly. This function will also be called at the end of each player's turn to ensure that the game state is updated correctly and that the next player can only make valid moves.

    if(players[currentPlayer].hasValidMove(discardPile.peekTopCard())){
        // Player has a valid move, continue with their turn
    } else {
        // Player does not have a valid move, they must draw a card
        players[currentPlayer].drawCard(drawDeck.getTopCard());
        cout << "Player " << currentPlayer + 1 << " has no valid moves and must draw a card." << endl;
    }




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
    cin.get();

    return; // Return from the function
}

int main(){

    clearScreen(); // Clear the console screen

    drawDeck.shuffle(); // Shuffle the deck of cards

    discardPile.clear(); // Clear the discard pile to ensure it starts empty

    discardPile.addCard(drawDeck.getTopCard()); // Add the top card from the main deck to the discard pile
    
    while (true) { // Start an infinite loop to keep the game running until the user chooses to exit
        mainMenu(); // Call the main menu function to display the main menu and handle user input
    }






    return 0;
}
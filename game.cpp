/// \file game.cpp
/// \author Joshua Sullivan
/// \date 2024-06-01
/// \brief This file contains the implementation of the Crazy Eights game.
/// \details This file contains the implementation of the Crazy Eights game, including the main function, game rules and game logic. It uses the Player, Deck and Card classes to manage the game state and player interactions. It also includes functions to handle user input and output as well as functions to manage the game flow and scoring. The game is played in a console window and uses standard input and output for user interaction. May contain some bugs (but tested and not found any) but should be fully functional. The game is designed to be played by 2-5 players and can be played in multiple rounds until a player reaches a predetermined score to win the game. The game rules are based on the traditional Crazy Eights card game.
/// \see https://en.wikipedia.org/wiki/Crazy_Eights
/// \copyright 2024 Joshua Sullivan. All rights reserved.
/// \copyright This project is open source and free to use modify and distribute.
/// \attention This project is open source and free to use, modify and distribute. However, please give credit to the original author (Joshua Sullivan) and include this notice in any copies or substantial portions of the software. Additionally please note that this project is provided "as is" without any warranty of any kind, either express or implied including but not limited to the warranties of merchantability fitness for a particular purpose and noninfringement. In no event shall the authors or copyright holders be liable for any claim, damages or other liability whether in an action of contract tort or otherwise arising from out of or in connection with the software or the use or other dealings in the software.
/// \todo Add more features to the game, such as AI players, different game modes and a graphical user interface. Also consider adding more error handling and input validation to improve the user experience. Additionally consider adding more comments and documentation to the code to improve readability and maintainability. Finally consider refactoring the code to improve its structure and organization.

// ---------------------------------------------------------------------------
// Includes
// This section includes the necessary header files for the Crazy Eights game implementation. It includes the Player, Deck and Card classes as well as standard libraries for input/output and system commands. It also includes the game.h header file which contains the function prototypes for the game logic and user interaction.
// ---------------------------------------------------------------------------

#include "template/Deck.h" // Include the header file for the Deck class
#include "template/Player.h" // Include the header file for the Player class
#include "template/Card.h" // Include the header file for the Card class
#include <iostream> // Include the iostream library for input/output operations
#include <cstdlib> // Include the cstdlib library for system commands
#include <vector> // Include the vector library for the dynamically sized arrays
#include "game.h" // Include the header file for this .cpp file

// ---------------------------------------------------------------------------
// Global Variables
// This section declares the global variables for the Crazy Eights game. It includes the draw deck, discard pile, players and current suit.
// ---------------------------------------------------------------------------

// Declare global variables for the draw deck, discard pile, players and current player index
/// \brief The draw deck is a Deck object that contains the cards to be drawn by the players during the game.
Deck drawDeck; // Declare a global variable for the deck of cards to draw from
/// \brief The discard pile is a Deck object that contains the cards that have been played by the players during the game.
Deck discardPile; // Declare a global variable for the discard pile of cards
/// \brief The players is a vector of Player objects that contains the players in the game.
vector<Player> players; // Declare a global variable for the vector list of players in the game
/// \brief The current suit is a string that contains the current suit of the game.
/// \details It is used to determine if a player can play a card based on the suit of the top card of the discard pile.
string currentSuit; // Declare a global variable for the current suit of the game

// ---------------------------------------------------------------------------
// Function Prototypes
// This section declares the function prototypes for the Crazy Eights game. Each function is documented with Doxygen at its definition below.
// ---------------------------------------------------------------------------

// Declare function prototypes for the compiler to recognize the functions before they are defined
static void gameRules(); // A function that displays the rules of the game to the user
static void gameStart(); // A function that starts a new game of Crazy Eights
static void clearScreen(); // A function that clears the console screen
static void mainMenuExit(); // A function that exits the game and terminates the program
static void mainMenu(); // A function that displays the main menu
static int playerAmount(); // A function that prompts the user to enter the number of players in the game
static void playerNames(int numPlayers); // A function that prompts the user to enter the names of the players in the game
static void playerTurn(int currentPlayer, int numPlayers); // A function that handles a player's turn in the game
static void checkHand(int currentPlayer, int numPlayers); // A function that checks the current player's hand and displays it to the user
static void startGame(); // A function that starts the game and handles the main game loop
static void nextRound(int currentRound); // A function that handles the transition to the next round of the game
static bool activeValidatorForRulesDuringGamePlay(int player); // A function that validates the game rules during gameplay
static void playerScores(vector<int> playerScores); // A function that displays the scores of the players at the end of a round
static void countScore(int winner, vector<int> playerScores); // A function that counts the scores of the players and displays the winner
static int readNumber(); // A function that reads a number from the user and validates the input
static void playerMove(int player); // A function that handles a player's move
static void dealCards(int numPlayers); // A function to deal cards to the players
static int playRound(int startPlayer, int numPlayers); // A function to play a round of the game
static bool isPlayable(Card card, Card top); // A function to check if a card is playable based on the game rules
static int chooseCard(int player); // A function to allow the player to choose a card to play
static string callANewSuit(); // A function to allow the player to call a new suit when playing an eight
static void drawNewCard(int player); // A function to allow the player to draw a new card from the draw deck
static void shuffleDiscardKeepTopCard(); // A function to shuffle the discard pile and keep the top card in place
static int cardPoints(Card card); // A function to calculate the points of a card based on the game rules
static void checkScoring(int winner, int numPlayers); // A function to check the scoring of the players at the end of a round and update their scores

// ---------------------------------------------------------------------------
// Main Function
// ---------------------------------------------------------------------------

/// \brief The main function that serves as the entry point of the program.
/// \details This function serves as the entry point of the program. It clears the console screen and starts an infinite loop to keep the game running until the user chooses to exit. It calls the main menu function to display the main menu and handle user input.
/// \see This function calls the clearScreen function to clear the console screen and the mainMenu function to display the main menu and handle user input.
/// \note This function uses the clearScreen function to clear the console screen before starting the game loop. It also uses the mainMenu function to display the main menu and handle user input.
/// \return This function never returns normally as it loops forever. The program is terminated by exit() in mainMenuExit or readNumber.
int main(){ // The main function that serves as the entry point of the program

    clearScreen(); // Clear the console screen
    
    while (true) { // Start an infinite loop to keep the game running until the user chooses to exit
        mainMenu(); // Call the main menu function to display the main menu and handle user input
    }
}

// ---------------------------------------------------------------------------
// Utility Functions
// This section contains utility functions that are used throughout the program. It includes functions for reading user input and validating it as a number, displaying the game rules, starting a new game, clearing the console screen, exiting the game, displaying the main menu, getting the number of players, getting the names of the players, handling a player's turn, checking a player's hand, starting the game loop, transitioning to the next round, validating the game rules during gameplay, displaying player scores, counting player scores and determining the winner of a round.
// ---------------------------------------------------------------------------

/// \brief The function "readNumber" reads a number from the user and validates the input.
/// \details The function "readNumber" reads a number from the user and validates the input. It checks if the input is a valid integer and handles any errors that may occur during input. If the input is not a valid integer, it clears the input stream and prompts the user to enter a valid number. It also handles end-of-file (EOF) conditions and exits the program if the input stream is closed.
/// \see No other functions are directly called.
/// \par Local variables
/// - \c number The number input by the user is stored in this variable and returned by the function.
/// \return The function returns the number input by the user as an integer.
static int readNumber(){ // A function that reads a number from the user and validates the input

    int number; // Declare a variable to hold the number input by the user
    if (!(cin >> number)){ // Check if the input is not a number
        if (cin.eof()) { // Check if the input stream is closed (end-of-file)
            cout << "Input closed. Exiting." << endl; exit(0); // If the input stream is closed print a message and exit the program
        } // End of if statement
        cin.clear(); // Clear the error flag on cin
        number = 0; // Set the number to 0 if the input is not a number
    }

    cin.ignore(10000, '\n'); // Ignore the rest of the input line to prevent any leftover characters from affecting future input
    return number; // Return the number input by the user
}

/// \brief The function "gameRules" displays the rules of the game to the user.
/// \details The function "gameRules" displays the rules of the game to the user. It clears the console screen and prints the rules of the game in a formatted manner. It also prompts the user to press Enter to continue after reading the rules.
/// \see This function calls the clearScreen function to clear the console screen before displaying the rules.
static void gameRules(){ // A function that displays the rules of the game to the user

    clearScreen(); // Clear the console screen
    
    cout << "-------------------------------------------" << endl; // Print a separator line
    cout <<"---------------" << " Crazy Eights " << "--------------" << endl; // Print welcome message
    cout << "-------------------------------------------" << endl; // Print a separator line

    cout << endl; // Print a blank line

    cout << "-------------------------------------------" << endl; // Print a separator line
    cout << "----------------" << " Game Rules " << "---------------" << endl; // Print game rules header
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
    cout << "12. The first player to get rid of all their cards wins the round." << endl; // Print rule 12
    cout << "13. The winner of the round scores points based on the cards remaining in the other players hands. The game continues until a player reaches a predetermined score (e.g., 100 points for 2 players, 150-250 points for 3-5 players) to win the game." << endl; // Print rule 13
    cout << "14. Each eight left in a hand is worth 50 points. Each king, queen, jack or ten is worth 10 points, each ace is worth 1 point and all other number cards are worth their face value." << endl; // Print rule 14
    cout << "15. Play multiple rounds rotating the dealer to the left each time. The first player to reach 100 points (for 2 players) or 150 to 250 points (for 3 to 5 players) wins the game." << endl; // Print rule 15
    
    cout << endl; // Print a blank line
    cout << "Press Enter to continue..." << endl; // Prompt the user to press Enter to continue
    cin.get(); // Wait for the user to press Enter

    return; // Return from the function
}

/// \brief The function "gameStart" starts a new game of Crazy Eights.
/// \details The function "gameStart" starts a new game of Crazy Eights. It clears the console screen and prints a message indicating that a new game is starting. It then prompts the user to press Enter to continue and calls the startGame function to begin the game.
/// \see The function "clearScreen" is called to clear the console screen and the function "startGame" is called to begin the game.
static void gameStart(){ // A function that starts a new game of Crazy Eights

    clearScreen(); // Clear the console screen

    cout << "Starting a new game..." << endl; // Print message indicating a new game is starting
    cout << "Press Enter to continue..." << endl; // Prompt the user to press Enter to continue
    cin.get(); // Wait for the user to press Enter

    startGame(); // Call the startGame function to begin the game

    return; // Return from the function
}

/// \brief The function "clearScreen" clears the console screen.
/// \details The function "clearScreen" clears the console screen using the system command "cls".   
/// \see This function calls inbuilt system command to clear the console screen.
/// \note This function is platform-dependent and may not work on all operating systems. It is designed to work on Windows systems. For cross-platform compatibility, consider using a library like ncurses or a different method to clear the console screen.
static void clearScreen(){ // A function that clears the console screen

    system("cls"); // Clear the console screen

    return; // Return from the function
}

/// \brief The function "mainMenuExit" exits the game and terminates the program.
/// \details The function "mainMenuExit" exits the game and terminates the program. It clears the console screen, prints a message indicating that the game is exiting, prompts the user to press Enter to continue, and then calls the exit function to terminate the program with a status code of 0 (indicating successful exit).
/// \see The function "clearScreen" is called to clear the console screen and the function "exit" is called to terminate the program.
static void mainMenuExit(){ // A function that exits the game and terminates the program

    clearScreen(); // Clear the console screen

    cout << "Exiting the game..." << endl; // Print message indicating the game is exiting
    cout << "Press Enter to continue..." << endl; // Prompt the user to press Enter to continue
    cin.get(); // Wait for the user to press Enter
    exit(0); // Exit the program with a status code of 0 (indicating successful Exit)

    return; // Return from the function
}

/// \brief The function "mainMenu" displays the main menu and handles user input.
/// \details The function "mainMenu" displays the main menu and handles user input. It clears the console screen, prints the main menu options, prompts the user to enter their choice, and uses a switch statement to handle the user's choice. Depending on the user's choice, it calls the appropriate function to start a new game, view the game rules or exit the game. If the user enters an invalid choice, it prints an error message and prompts the user to try again.
/// \see The function "clearScreen" is called to clear the console screen, the function "readNumber" is called to read and validate the user's input as a number and the functions "gameStart", "gameRules" and "mainMenuExit" are called based on the user's choice in the switch statement.
/// \par Local variables
/// - \c choice The user's choice is stored in this variable and used in the switch statement to determine which action to take.
static void mainMenu(){ // A function that displays the main menu

    clearScreen(); // Clear the console screen

    cout << "-------------------------------------------" << endl; // Print a separator line
    cout << "----------------" << " Main Menu " << "----------------" << endl; // Print main menu header
    cout << "-------------------------------------------" << endl; // Print a separator line
    
    cout << endl; // Print a blank line

    cout << "1. Start New Game" << endl; // Print option 1
    cout << "2. View Game Rules" << endl; // Print option 2
    cout << "3. Exit Game" << endl; // Print option 3
    
    cout << endl; // Print a blank line

    cout << "Enter your choice (1-3): "; // Prompt the user to enter their choice

    int choice = readNumber(); // Read the user's choice using the readNumber function

    switch(choice){ // Use a switch statement to handle the user's choice
        case 1: // If the user chooses option 1
            gameStart(); // Call the gameStart function to start a new game
            break; // Break out of the switch statement
        case 2: // If the user chooses option 2
            gameRules(); // Call the gameRules function to display the game rules
            break; // Break out of the switch statement
        case 3: // If the user chooses option 3
            mainMenuExit(); // Call the mainMenuExit function to exit the game
            break; // Break out of the switch statement
        default: // If the user enters an invalid choice
            cout << "Invalid choice. Please try again." << endl; // Print message indicating the choice is invalid
            cout << "Press Enter to continue..." << endl; // Prompt the user to press Enter to continue
            cin.get(); // Wait for the user to press Enter
            mainMenu(); // Call the mainMenu function again to display the main menu and prompt for input
    } // End of switch statement

    return; // Return from the function
}

/// \brief The function "playerAmount" prompts the user to enter the number of players in the game.
/// \details The function "playerAmount" prompts the user to enter the number of players in the game. It clears the console screen, prints a header for player amount, prompts the user to enter a number between 2 and 5 and reads the input using the readNumber function. If the input is invalid (less than 2 or greater than 5), it prints an error message and prompts the user to try again by calling itself recursively. If the input is valid, it returns the number of players.
/// \see The function "clearScreen" is called to clear the console screen and the function "readNumber" is called to read and validate the user's input as a number. The function also uses recursion to prompt the user again if the input is invalid.
/// \par Local variables
/// - \c numPlayers The number of players input by the user is stored in this variable and returned by the function.
/// \return The function returns the number of players input by the user as an integer.
static int playerAmount(){ // A function that prompts the user to enter the number of players in the game

    clearScreen(); // Clear the console screen

    cout << "-------------------------------------------" << endl; // Print a separator line
    cout << "-------------" << " Player Amount " << "--------------" << endl; // Print player amount header
    cout << "-------------------------------------------" << endl; // Print a separator line
    
    cout << endl; // Print a blank line
    
    cout << "Enter the number of players (2-5): "; // Prompt the user to enter the number of players

    int numPlayers = readNumber(); // Read the number of players using the readNumber function

    if(numPlayers < 2 || numPlayers > 5){ // Check if the number of players is less than 2 or greater than 5
        cout << "Invalid number of players. Please try again." << endl; // Print message indicating the number of players is invalid
        cout << "Press Enter to continue..." << endl; // Prompt the user to press Enter to continue
        cin.get(); // Wait for the user to press Enter
        return playerAmount(); // Call the playerAmount function again to prompt for input
    } // End of if statement

    return numPlayers; // Return the number of players
}

/// \brief The function "playerNames" prompts the user to enter the names of the players in the game.
/// \details The function "playerNames" prompts the user to enter the names of the players in the game. It clears the console screen, prints a header for player names, and loops through the number of players to prompt the user to enter each player's name. If the user enters an empty name, it assigns a default name (e.g., "Player 1", "Player 2", etc.). It creates a new Player object for each player, sets their name and adds them to the players vector. The function ensures that the players vector starts empty by clearing it before adding new players.
/// \see The function "clearScreen" is called to clear the console screen and the inbuilt function "getline" is called to read the player's name from input. The function uses a loop to prompt for each player's name and creates Player objects accordingly.
/// \param numPlayers The number of players in the game.
/// \par Local variables
/// - \c name The player's name input by the user is stored in this variable and used to set the name of the Player object.
/// - \c newPlayer A new Player object is created for each player and their name is set using the setName method. The Player object is then added to the players vector.
static void playerNames(int numPlayers){ // A function that prompts the user to enter the names of the players in the game

    clearScreen(); // Clear the console screen

    cout << "-------------------------------------------" << endl; // Print a separator line
    cout << "--------------" << " Player Names " << "---------------" << endl; // Print player names header
    cout << "-------------------------------------------" << endl; // Print a separator line
    
    cout << endl; // Print a blank line

    players.clear(); // Clear the players vector to ensure it starts empty

    for(int i = 0; i < numPlayers; i++){ // Loop through the number of players to get their names
        string name; // Declare a variable to hold the player's name
        cout << "Enter name for Player " << i + 1 << ": "; // Prompt the user to enter the name for the current player
        getline(cin, name); // Get the player's name from input

        if (name.empty()) { // Check if the name is empty
            name = "Player " + to_string(i + 1); // Assign a default name if the input is empty
        }
        Player newPlayer; // Create a new Player object
        newPlayer.setName(name); // Set the player's name
        players.push_back(newPlayer); // Add the new Player object to the players vector
    } // End of for loop

    return; // Return from the function
}

/// \brief The function "playerTurn" handles a player's turn in the game.
/// \details The function "playerTurn" handles a player's turn in the game. It clears the console screen, prints a header indicating the player's turn, displays the current player's name and prompts the user to press Enter to continue. It then calls the checkHand function to display the current player's hand and allow them to make a move. The function ensures that the game flow continues smoothly by managing the player's turn and interactions with the game state.
/// \see The function "clearScreen" is called to clear the console screen and the function "checkHand" is called to display the current player's hand and allow them to make a move.
/// \param currentPlayer The index of the current player in the players vector.
/// \param numPlayers The total number of players in the game.
static void playerTurn(int currentPlayer, int numPlayers){ // A function that handles a player's turn in the game

    clearScreen(); // Clear the console screen

    cout << "-------------------------------------------" << endl; // Print a separator line
    cout << "---------------" << " Player Turn " << "---------------" << endl; // Print player turn header
    cout << "-------------------------------------------" << endl; // Print a separator line
    
    cout << endl; // Print a blank line
    
    cout << "It is " << players[currentPlayer].getName() << "'s turn." << endl; // Print the current player's turn
    cout << endl; // Print a blank line
    cout << "Press Enter to continue..."; // Prompt the user to press Enter to continue
    cin.get(); // Wait for the user to press Enter

    checkHand(currentPlayer, numPlayers); // Call the check hand function to display the current player's hand

    return; // Return from the function
}

/// \brief The function "checkHand" checks the current player's hand and displays it to the user.
/// \details The function "checkHand" checks the current player's hand and displays it to the user. It clears the console screen, prints the top card of the discard pile and the current suit. It then displays the current player's hand and prompts the user to press Enter to continue. The function calls the "playerMove" function to handle the current player's move.
/// \see The function "clearScreen" is called to clear the console screen and the function "playerMove" is called to handle the current player's move. The function also uses the "peekTopCard" method of the discard pile to display the top card and the "printHand" method of the Player class to display the current player's hand.
/// \param currentPlayer The index of the current player in the players vector.
/// \param numPlayers The total number of players in the game.
/// \par Global variables used
/// - \c discardPile The discard pile is a Deck object that contains the cards that have been played by the players during the game. The top card of the discard pile is displayed to the user.
/// - \c currentSuit The current suit is a string that contains the current suit of the game. It is used to determine if a player can play a card based on the suit of the top card of the discard pile.
static void checkHand(int currentPlayer, int numPlayers){ // A function that checks the current player's hand and displays it to the user

    clearScreen(); // Clear the console screen

    cout << "The top card of the discard pile is: " << discardPile.peekTopCard().toString() << endl; // Print the top card of the discard pile
    cout << "The current suit is: " << currentSuit << endl; // Print the current suit of the game
    cout << endl; // Print a blank line

    cout << "-----------" << "Current Hand" << "-----------" << endl; // Print check hand header
    cout << endl; // Print a blank line

    cout << "Player " << players[currentPlayer].getName() << "'s hand: "; // Print the current player's hand
    cout << endl; // Print a blank line for spacing
    players[currentPlayer].printHand(); // Print the current player's hand
    cout << endl; // Print a blank line
    cout << "Press Enter to continue..."; // Prompt the user to press Enter to continue
    cout << endl; // Print a blank line
    cin.get(); // Wait for the user to press Enter
    
    playerMove(currentPlayer); // Call the player move function to handle the current player's move

    return; // Return from the function
}

/// \brief The function "startGame" starts the game and handles the main game loop.
/// \details The function "startGame" starts the game and handles the main game loop. It gets the number of players and their names, sets the target score and initializes the starting player and round counter. It enters an infinite loop to play rounds of the game until a player reaches the target score. After each round it checks the scoring displays the scores of the players and determines if a player has won. If a player reaches the target score it announces the winner and ends the game. The function also manages the transition to the next round and updates the starting player for each round.
/// \see The function "playerAmount" is called to get the number of players, the function "playerNames" is called to get the names of the players, the function "playRound" is called to play a round of the game, the function "checkScoring" is called to update the scores of the players, the function "countScore" is called to display the scores and determine the winner of a round and the function "nextRound" is called to handle the transition to the next round. The function also uses a vector to hold the scores of the players and manages user input for continuing between rounds.
/// \par Local variables
/// - \c numPlayers The number of players in the game is stored in this variable and used to manage the game flow and scoring.
/// - \c targetScore The target score is calculated based on the number of players and is used to determine when a player has won the game.
/// - \c startPlayer The starting player index is initialized to 0 and is updated after each round to determine which player goes first in the next round.
/// - \c round The round counter is initialized to 0 and is incremented after each round to keep track of the number of rounds played.
/// - \c scores A vector is used to hold the scores of the players after each round and is used to display the scores and determine the winner of a round.
/// - \c winner The index of the winning player for each round is stored in this variable and is used to update the scores and determine if a player has won the game.
static void startGame(){ // A function that starts the game and handles the main game loop

    int numPlayers = playerAmount(); // Get the number of players using the playerAmount function
    playerNames(numPlayers); // Get the names of the players using the playerNames function
    int targetScore = 50 * numPlayers; // Set the target score based on the number of players
    int startPlayer = 0; // Set the starting player index to 0
    int round = 0; // Initialize the round counter to 0

    while (true){ // Start an infinite loop to keep the game running until a player reaches the target score

        int winner = playRound(startPlayer, numPlayers); // Call the play round function to play a round of the game and get the index of the winning player

        checkScoring(winner, numPlayers); // Call the check scoring function to update the scores of the players and display the winner of the round

        vector<int> scores; // Create a vector to hold the scores of the players
        for (int i = 0; i < numPlayers; i++) { // Loop through the number of players to get their scores
            cout << "Player " << players[i].getName() << "'s score: " << players[i].getScore() << endl; // Print each player's score
            cout << endl; // Print a blank line
            cout << "Press Enter to continue..."; // Prompt the user to press Enter to continue
            cin.get(); // Wait for the user to press Enter
            scores.push_back(players[i].getScore()); // Add each player's score to the playerScores vector
        } // End of for loop

        countScore(winner, scores); // Call the count score function to display the scores and the winner of the round
        playerScores(scores); // Call the player scores function to display the scores of the players

        if (players[winner].getScore() >= targetScore) { // Check if the winning player's score is greater than or equal to the target score
            cout << "Player " << players[winner].getName() << " has reached the target score of " << targetScore << " and wins the game!" << endl; // Print the winning player's name and score
            cout << "Press Enter to continue..."; // Prompt the user to press Enter to continue
            cin.get(); // Wait for the user to press Enter
            return; // Return from the function to end the game
        } // End of if statement
        
        round++; // Increment the round counter
        nextRound(round); // Call the next round function to start the next round
        

        startPlayer = (winner + 1) % numPlayers; // Set the starting player for the next round to the player after the winner
    }
}

/// \brief The function "nextRound" handles the transition to the next round of the game.
/// \details The function "nextRound" handles the transition to the next round of the game. It clears the console screen, prints a header indicating the next round, displays the current round number and prompts the user to press Enter to continue. The function ensures that the game flow continues smoothly by managing the transition between rounds and allowing the user to prepare for the next round. 
/// \see The function "clearScreen" is called to clear the console screen before displaying the next round information.
/// \param currentRound The current round number is passed as a parameter to the function and is used to display the next round number to the user.
static void nextRound(int currentRound){ // A function that handles the transition to the next round of the game

    clearScreen(); // Clear the console screen

    cout << "-------------------------------------------" << endl; // Print a separator line
    cout << "---------------" << " Next Round " << "---------------" << endl; // Print next round header
    cout << "-------------------------------------------" << endl; // Print a separator line
    
    cout << endl; // Print a blank line
    
    cout << "Starting Round " << currentRound + 1 << "..." << endl; // Print the current round number
    cout << endl; // Print a blank line
    cout << "Press Enter to continue..."; // Prompt the user to press Enter to continue
    cin.get(); // Wait for the user to press Enter

    return; // Return from the function
}

/// \brief The function "activeValidatorForRulesDuringGamePlay" that validates the game rules during gameplay.
/// \details The function "activeValidatorForRulesDuringGamePlay" checks if the current player has a valid move based on the top card of the discard pile and the current suit. It calls the hasValidMove function of the Player class to determine if the player can make a valid move according to the game rules. The function returns true if the player has a valid move and false otherwise.
/// \see This function calls the hasValidMove function of the Player class to check if the player has a valid move based on the top card of the discard pile and the current suit.
/// \param player The index of the player whose move is being validated.
/// \return true if the player has a valid move, false otherwise.
static bool activeValidatorForRulesDuringGamePlay(int player){ // A function that validates the game rules during gameplay

    return players[player].hasValidMove(discardPile.peekTopCard(), currentSuit); // Call the hasValidMove function to check if the player has a valid move
}

/// \brief The function "playerScores" that displays the scores of the players at the end of a round.
/// \details The function "playerScores" takes a vector of player scores as input and displays the scores of each player at the end of a round. It clears the console screen, prints a header for player scores and loops through the playerScores vector to display each player's score. The function prompts the user to press Enter to continue after displaying the scores.
/// \see This function calls the clearScreen function to clear the console screen before displaying the scores. It also uses a loop to iterate through the playerScores vector and display each player's score.
/// \param playerScores A vector containing the scores of each player.
static void playerScores(vector<int> playerScores){ // A function that displays the scores of the players at the end of a round

    clearScreen(); // Clear the console screen

    cout << "-------------------------------------------" << endl; // Print a separator line
    cout << "--------------" << " Player Scores " << "--------------" << endl; // Print player scores header
    cout << "-------------------------------------------" << endl; // Print a separator line
    cout << endl; // Print a blank line

    for(int i = 0; i < playerScores.size(); i++){ // Loop through the playerScores vector to display each player's score
        cout << "Player " << players[i].getName() << "'s score: " << playerScores[i] << endl; // Print the score of each player
    } // End of for loop

    cout << endl; // Print a blank line
    cout << "Press Enter to continue..."; // Prompt the user to press Enter to continue
    cin.get(); // Wait for the user to press Enter

    return; // Return from the function
}

/// \brief The function "countScore" that counts the scores of the players and displays the winner.
/// \details The function "countScore" takes the index of the winning player and a vector of player scores as input. It clears the console screen, prints a header for score count, displays the winner of the round and loops through the playerScores vector to display each player's score. The function prompts the user to press Enter to continue after displaying the scores and winner.
/// \see This function calls the clearScreen function to clear the console screen before displaying the scores and winner. It also uses a loop to iterate through the playerScores vector and display each player's score excluding the winner as the winner's score is displayed before loop.
/// \param winner The index of the winning player.
/// \param playerScores A vector containing the scores of each player.
static void countScore(int winner, vector<int> playerScores){ // A function that counts the scores of the players and displays the winner

    clearScreen(); // Clear the console screen

    cout << "-------------------------------------------" << endl; // Print a separator line
    cout << "---------------" << " Score Count " << "---------------" << endl; // Print score count header
    cout << "-------------------------------------------" << endl; // Print a separator line
    
    cout << endl; // Print a blank line
    cout << "Player " << players[winner].getName() << " wins this round!" << endl; // Print the winner of the round
    cout << endl; // Print a blank line

    for(int i = 0; i < playerScores.size(); i++){ // Loop through the playerScores vector to display each player's score
        if(i != winner){ // Check if the current player is not the winner
            cout << "Player " << players[i].getName() << "'s score: " << playerScores[i] << endl; // Print the score of each player
        } // End of if statement
    } // End of for loop

    cout << endl; // Print a blank line
    cout << "Press Enter to continue..."; // Prompt the user to press Enter to continue
    cin.get(); // Wait for the user to press Enter

    return; // Return from the function
}

/// \brief The function "dealCards" that deals cards to the players at the start of a round.
/// \details The function "dealCards" takes the number of players as input and deals cards to each player at the start of a round. It clears the draw deck and discard pile, fills and shuffles the draw deck and clears each player's hand. It then deals a specified number of cards to each player based on the number of players (7 cards for 2 players, 5 cards for 3-5 players). Finally it adds the top card from the draw deck to the discard pile and sets the current suit based on that card.
/// \see This function calls the clear, fillDeck, shuffle, clearHand, addCard and peekTopCard methods of the Deck and Player classes to manage the dealing of cards and game state. It also uses a loop to iterate through the number of players and deal cards accordingly.
/// \param numPlayers The number of players in the game is passed as a parameter to the function and is used to determine how many cards to deal to each player and manage the game state.
/// \par Local variables
/// - \c handSize A variable that holds the number of cards to deal to each player based on the number of players in the game. It is set to 7 for 2 players and 5 for 3-5 players.
/// \note The function ensures that the draw deck and discard pile are cleared before dealing cards to avoid any leftover cards from previous rounds affecting the current round.
static void dealCards(int numPlayers){ // A function to deal cards to the players

    drawDeck.clear(); // Clear the draw deck to ensure it starts empty
    drawDeck.fillDeck(); // Fill the draw deck with a standard deck of 52 cards
    drawDeck.shuffle(); // Shuffle the draw deck to randomize the order of the cards

    discardPile.clear(); // Clear the discard pile to ensure it starts empty

    for (int i = 0; i < numPlayers; i++) { // Loop through the number of players to clear their hands
        players[i].clearHand(); // Clear each player's hand to ensure it starts empty
        } // End of for loop
    
    int handSize; // Declare a variable to hold the number of cards to deal to each player
    
    if (numPlayers == 2) { // Check if there are 2 players
        handSize = 7; // Set the hand size to 7 for 2 players
    } else { // If there are 3-5 players
        handSize = 5; // Set the hand size to 5 for 3-5 players
    } // End of if statement

    for (int i = 0; i < handSize; i++) { // Loop through the hand size to deal cards to each player
        for (int p = 0; p < numPlayers; p++) { // Loop through the number of players to deal cards to each player
            players[p].addCard(drawDeck.getTopCard()); // Add the top card from the draw deck to the current player's hand
        } // End of for loop
    } // End of for loop

    discardPile.addCard(drawDeck.getTopCard()); // Add the top card from the draw deck to the discard pile to start the game
    currentSuit = discardPile.peekTopCard().getSuit(); // Set the current suit to the suit of the top card of the discard pile
}

/// \brief The function "playRound" that plays a round of the game and returns the index of the winning player.
/// \details The function "playRound" takes the starting player index and the number of players as input. It deals cards to the players, sets the current player to the starting player and enters an infinite loop to handle each player's turn. It calls the playerTurn function to manage the current player's turn and checks if the current player has won by checking if their hand is empty. If a player wins it returns the index of the winning player. The function also manages the transition to the next player by incrementing the current player index and wrapping around using modulo arithmetic.
/// \see This function calls the dealCards and playerTurn functions to manage the game state and player interactions. It also uses the isEmpty method of the Player class to check if a player has won by having an empty hand.
/// \param startPlayer The index of the starting player for the round is passed as a parameter to the function and is used to determine which player goes first in the round.
/// \param numPlayers The number of players in the game is passed as a parameter to the function and is used to manage the game flow and determine when to wrap around to the first player.
/// \par Local variables
/// - \c current The index of the current player is initialized to the starting player and is updated after each turn to manage the game flow and determine which player's turn it is.
/// \return The index of the winning player (the first player to empty their hand).
/// \note The function uses an infinite loop to keep the round running until a player wins and it returns the index of the winning player when a player has an empty hand.
static int playRound(int startPlayer, int numPlayers){ // A function to play a round of the game

    dealCards(numPlayers); // Deal cards to players and set up the discard pile
    int current = startPlayer; // Set the current player to the starting player

    while (true) { // Start an infinite loop to keep the round running until a player wins
        playerTurn(current, numPlayers); // Call the player turn function to handle the current player's turn

        if (players[current].isEmpty()) { // Check if the current player has won the round
            return current; // Return the index of the winning player
        } // End of if statement

        current = (current + 1) % numPlayers; // Move to the next player
    } // End of while loop
}

/// \brief The function "playerMove" that handles a player's move during their turn.
/// \details The function "playerMove" checks if the current player has any valid moves available. If not it prompts the player to draw a card. If the player has valid moves it allows them to choose a card to play. If the chosen card is an eight it prompts the player to choose a new suit. The function updates the current suit based on the chosen card and displays the current suit to match. It also prompts the user to press Enter to continue after handling the player's move.
/// \see This function calls the activeValidatorForRulesDuringGamePlay, drawNewCard, chooseCard, callANewSuit and isPlayable functions to manage the player's move and game state. It also uses the addCard method of the discard pile to add the chosen card to the discard pile and the getRank and getSuit methods of the Card class to determine the rank and suit of the chosen card.
/// \param player The index of the current player is passed as a parameter to the function and is used to manage the player's move and interactions with the game state.
/// \par Local variables
/// - \c card The chosen card is a Card object that is used to determine the rank and suit of the card played by the player and to update the current suit of the game.
/// \par Global variables used
/// - \c currentSuit The current suit is a string that contains the current suit of the game. It is updated based on the chosen card and used to determine if a player can play a card based on the suit of the top card of the discard pile.
static void playerMove(int player) { // Handle a player's move during their turn

    if (!activeValidatorForRulesDuringGamePlay(player)){ // Check if the player has any valid moves available

        cout << "Player " << players[player].getName() << " has no valid moves and must draw a card." << endl; // Print message indicating the player has no valid moves
        drawNewCard(player); // Call the draw new card function to draw a card for the player
    } // End of if statement
    else { // If the player has valid moves available
        int index = chooseCard(player); // Call the choose card function to get the index of the card the player wants to play
        Card card = players[player].getCard(index); // Get the card object at the chosen index
        discardPile.addCard(card); // Add the chosen card to the discard pile

        if (card.getRank() == 8) { // Check if the chosen card is an eight
            cout << "Player " << players[player].getName() << " played an eight and gets to choose a new suit." << endl; // Print message indicating the player played an eight
            currentSuit = callANewSuit(); // Call the choose suit function to get the new suit for the game
        } else { // If the chosen card is not an eight
            currentSuit = card.getSuit(); // Set the current suit to the suit of the chosen card
        } // End of if statement
        cout << "Player " << players[player].getName() << " played " << card.toString() << "." << endl; // Print message indicating the player played a card
    } // End of else statement

    cout << "The Suit to match is now: " << currentSuit << endl; // Print the current suit to match
    cout << "Press Enter to continue..."; // Prompt the user to press Enter to continue
    cin.get(); // Wait for the user to press Enter
}

/// \brief The function "isPlayable" that checks if a card is playable based on the game rules.
/// \details The function "isPlayable" takes a card and the top card of the discard pile as input. It checks if the card is playable based on the game rules which allow a card to be played if it matches the rank or suit of the top card of the discard pile or if it is an eight. The function returns true if the card is playable and false otherwise.
/// \see This function uses the getRank and getSuit methods of the Card class to determine the rank and suit of the card and the top card of the discard pile. It also uses the currentSuit variable to check if the card matches the current suit of the game.
/// \param card The card to be checked for playability is passed as a parameter to the function and is used to determine if it can be played based on the game rules.
/// \param top The top card of the discard pile is passed as a parameter to the function and is used to determine if the card can be played based on its rank or suit.
/// \par Global variables used
/// - \c currentSuit The current suit is a string that contains the current suit of the game. It is used to determine if a card can be played based on the suit of the top card of the discard pile.
/// \return true if the card is playable false otherwise.
static bool isPlayable(Card card, Card top){ // A function to check if a card is playable based on the game rules

    return card.getRank() == 8 || card.getRank() == top.getRank() || card.getSuit() == currentSuit; // Check if the card is playable based on the game rules
}

/// \brief The function "chooseCard" that allows the player to choose a card to play during their turn.
/// \details The function "chooseCard" prompts the player to choose a card to play from their hand. It checks if the chosen card is valid and playable based on the game rules. If the chosen card is not valid or playable it prompts the player to choose again. The function returns the index of the chosen card in the player's hand.
/// \see This function uses the readNumber function to read the player's input and the isPlayable function to check if the chosen card is playable based on the game rules. It also uses the getHandSize and peekCard methods of the Player class to display the player's hand and check if the chosen card is valid.
/// \param player The index of the current player is passed as a parameter to the function and is used to manage the player's move and interactions with the game state.
/// \par Local variables
/// - \c choice The player's choice of card is read from input and stored in this variable. It is used to determine which card the player wants to play and to check if the choice is valid and playable.
/// \return The index of the chosen card in the player's hand.
/// \note The function uses an infinite loop to keep prompting the player until they choose a valid and playable card. It also provides feedback to the player if their choice is invalid or not playable.
static int chooseCard(int player) { // Allow the player to choose a card to play

    while (true){ // Start an infinite loop to keep prompting the player until they choose a valid card
        cout << "Player " << players[player].getName() << " Which card would you like to play: "; // Prompt the player to choose a card to play
        int choice = readNumber(); // Read the player's choice using the readNumber function
        if (choice < 1 || choice > players[player].getHandSize()) { // Check if the choice is valid
            cout << "That card is not in your hand." << endl; // Print message indicating the choice is invalid
            continue; // Continue to the next iteration of the loop
        } // End of if statement
        else if (isPlayable(players[player].peekCard(choice - 1), discardPile.peekTopCard())) { // Check if the chosen card is playable
            return choice - 1; // Return the index of the chosen card
        } // End of else if statement
        else { // If the chosen card is not playable
            cout << "That card cannot be played." << endl; // Print message indicating the chosen card cannot be played
            cout << "Match the rank or suit of the top card of the discard pile, or play an eight." << endl; // Print message indicating the player must match the rank or suit or play an eight
        } // End of else statement
    } // End of while loop
}

/// \brief The function "callANewSuit" that allows the player to call a new suit when playing an eight.
/// \details The function "callANewSuit" prompts the player to choose a new suit when they play an eight. It displays the options for the four suits and reads the player's choice. If the choice is valid it returns the chosen suit as a string. If the choice is invalid it prompts the player to choose again until a valid choice is made.
/// \see This function calls the readNumber function to read the player's input and an array of strings to hold the four suits. It also provides feedback to the player if their choice is invalid and prompts them to choose again.
/// \par Local variables
/// - \c choice The player's choice of suit is read from input and stored in this variable. It is used to determine which suit the player wants to call and to check if the choice is valid.
/// - \c suits An array of strings is used to hold the four suits (Hearts, Diamonds, Clubs, Spades) and is used to display the options to the player and return the chosen suit.
/// \return The chosen suit as a string.
static string callANewSuit(){ // Allow the player to call a new suit when playing an eight

    string suits[4] = {"Hearts", "Diamonds", "Clubs", "Spades"}; // Create an array of strings to hold the four suits
    cout << "1. Hearts 2. Diamonds 3. Clubs 4. Spades" << endl; // Print options for the player to choose a new suit
    while (true){ // Start an infinite loop to keep prompting the player until they choose a valid suit
        cout << "Call a new suit (1-4): "; // Prompt the player to choose a new suit
        int choice = readNumber(); // Read the player's choice using the readNumber function
        if (choice < 1 || choice > 4) { // Check if the choice is valid
            cout << "Invalid choice. Please try again." << endl; // Print message indicating the choice is invalid
            continue; // Continue to the next iteration of the loop
        } // End of if statement
        else { // If the choice is valid
            return suits[choice - 1]; // Return the chosen suit as a string
        } // End of else statement
    } // End of while loop
}

/// \brief The function "drawNewCard" that allows the player to draw a new card from the draw deck.
/// \details The function "drawNewCard" checks if the draw deck is empty and shuffles the discard pile if necessary. It then draws a new card for the player and checks if it is playable. If the card is playable, it prompts the player to choose whether to play it or keep it. If the card is not playable, it automatically adds it to the player's hand. The function also handles the case where the draw deck is empty and there are no cards left to draw.
/// \see This function calls the shuffleDiscardKeepTopCard function to shuffle the discard pile and keep the top card if the draw deck is empty. It also uses the isPlayable function to check if the drawn card is playable and the addCard method of the Player class to add the card to the player's hand. The function provides feedback to the player about their options and handles user input for their choice.
/// \param player The index of the current player is passed as a parameter to the function and is used to manage the player's move and interactions with the game state.
/// \par Local variables
/// - \c card The drawn card is a Card object that is used to determine if it is playable and to update the player's hand or the discard pile based on the player's choice.
/// - \c choice The player's choice of whether to play the drawn card or keep it is read from input and stored in this variable. It is used to determine how to handle the drawn card based on the player's decision.
/// \note The function ensures that the draw deck is not empty before drawing a card and handles the case where the player has no valid moves and must draw a card. It also provides feedback to the player about their options and handles user input for their choice.
static void drawNewCard(int player) { // A function to draw a new card for the player
    
    if (drawDeck.isEmpty()) { // Check if the draw deck is empty
        shuffleDiscardKeepTopCard(); // Call the shuffle discard function to shuffle the discard pile and keep the top card
    } // End of if statement

    if (drawDeck.isEmpty()) { // Check again if the draw deck is empty after shuffling the discard pile
        cout << "The draw deck is empty and there are no cards left to draw." << endl; // Print message indicating the draw deck is empty
        return; // Return from the function
    }

    Card card = drawDeck.getTopCard(); // Get the top card from the draw deck
    cout << "Player " << players[player].getName() << " drew " << card.toString() << "." << endl; // Print message indicating the player drew a card
    char choice; // Declare a variable to store the player's choice
    if (isPlayable(card, discardPile.peekTopCard())) { // Check if the drawn card is playable
        cout << "Do you want to play this card? (y/n): "; // Ask the player if they want to play the drawn card
        cin >> choice; // Read the player's choice
        cin.ignore(10000, '\n'); // Ignore the rest of the input line to prevent any leftover characters from affecting future input
        while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') { // Check if the choice is valid
            cout << "Invalid choice. Please enter 'y' or 'n': "; // Print message indicating the choice is invalid
            cin >> choice; // Read the player's choice again
            cin.ignore(10000, '\n'); // Ignore the rest of the input line to prevent any leftover characters from affecting future input
        } // End of while loop
        if (choice == 'y' || choice == 'Y') { // Checks if player whishes to play the drawn card
            discardPile.addCard(card); // Add the drawn card to the discard pile
            cout << "Player " << players[player].getName() << " played the drawn card." << endl; // Print message indicating the player played the drawn card
        if (card.getRank() == 8) { // Check if the drawn card is an eight
            currentSuit = callANewSuit(); // Call the choose suit function to get the new suit for the game
            } 
        else { // If the drawn card is not an eight
            currentSuit = card.getSuit(); // Set the current suit to the suit of the drawn card
            } // End of if statement
            } // End of if statement
        else { // If the player does not wish to play the drawn card
            players[player].addCard(card); // Add the drawn card to the player's hand
            cout << "Player " << players[player].getName() << " has kept the card." << endl; // Print message indicating the player kept the drawn card
            } // End of else statement
        } // End of if statement
        else { // If the player does not wish to play the drawn card
                players[player].addCard(card); // Add the drawn card to the player's hand
                cout << "Player " << players[player].getName() << " cannot play the drawn card and must keep it." << endl; // Print message indicating the player cannot play the drawn card and must keep it
        } // End of else statement            
}

/// \brief The function "shuffleDiscardKeepTopCard" that shuffles the discard pile and keeps the top card.
/// \details The function "shuffleDiscardKeepTopCard" is called when the draw deck is empty and there are no cards left to draw. It shuffles the discard pile and keeps the top card of the discard pile. The function moves all cards from the discard pile to the draw deck, shuffles the draw deck and then adds the top card back to the discard pile. This ensures that the game can continue even when the draw deck is empty.
/// \see This function uses the getTopCard, isEmpty, addCard, and shuffle methods of the Deck class to manage the discard pile and draw deck. It also provides feedback to the player about the shuffling process and ensures that the top card of the discard pile is preserved.
/// \par Local variables
/// - \c top The top card of the discard pile is stored in this variable and is used to keep the top card of the discard pile after shuffling the rest of the cards into the draw deck.
/// \note The function ensures that the top card of the discard pile is preserved after shuffling the rest of the cards into the draw deck. It also handles the case where the discard pile is empty and there are no cards left to shuffle.
static void shuffleDiscardKeepTopCard() { // A function to shuffle the discard pile and keep the top card

    Card top = discardPile.getTopCard(); // Get the top card of the discard pile

    while (!discardPile.isEmpty()) { // While the discard pile is not empty
        drawDeck.addCard(discardPile.getTopCard()); // Move cards from the discard pile to the draw deck
    } // End of while loop
    
    drawDeck.shuffle(); // Shuffle the draw deck to randomize the order of the cards
    discardPile.addCard(top); // Add the top card back to the discard pile
}

/// \brief The function "cardPoints" that calculates the points for a given card based on its rank.
/// \details The function "cardPoints" takes a Card object as input and calculates the points for the card based on its rank. It returns 50 points for an eight, 10 points for a ten, jack, queen, or king, 1 point for an ace and the rank of the card as points for all other cards. The function is used to calculate the total points for a round based on the cards in the players hands.
/// \see This function uses the getRank method of the Card class to determine the rank of the card and calculate the points accordingly. It provides feedback to the player about the points earned for each card based on its rank.
/// \param card The Card object is passed as a parameter to the function and is used to determine the rank of the card and calculate the points accordingly.
/// \return The points for the given card based on its rank.
static int cardPoints(Card card) {

    if (card.getRank() == 8) { // Check if the card is an eight
        return 50; // Return 50 points for an eight
    } else if (card.getRank() >= 10) { // Check if the card is a ten, jack, queen, or king
        return 10; // Return 10 points for a ten, jack, queen, or king
    } else if (card.getRank() == 1) { // Check if the card is an ace
        return 1; // Return 1 point for an ace
    } else { // For all other cards
        return card.getRank(); // Return the rank of the card as points
    } // End of if statement
}

/// \brief The function "checkScoring" that calculates the total points for a round and updates the winner's score.
/// \details The function "checkScoring" takes the index of the winning player and the number of players as input. It calculates the total points for the round by summing the points of all cards in the hands of the losing players. It then updates the winner's score with the total points earned and displays a message indicating the winner and the points earned. The function prompts the user to press Enter to continue after displaying the scoring information.
/// \see This function uses the cardPoints function to calculate the points for each card in the losing players' hands. It also uses the getHandSize and peekCard methods of the Player class to access the cards in the players' hands and the changeScoreBy method to update the winner's score. The function provides feedback to the player about the scoring process and ensures that the game flow continues smoothly by managing the scoring and allowing the user to prepare for the next round.
/// \param winner The index of the winning player is passed as a parameter to the function and is used to update the winner's score and display the scoring information.
/// \param numPlayers The number of players in the game is passed as a parameter to the function and is used to loop through the players and calculate the total points for the round based on the cards in the losing players' hands.
/// \par Local variables
/// - \c roundPoints A variable that holds the total points for the round is initialized to zero and is used to accumulate the points from the losing players' hands. It is updated as the function loops through the players and their hands to calculate the total points earned by the winner.
static void checkScoring(int winner, int numPlayers){

    int roundPoints = 0; // Initialize a variable to hold the total points for the round

    for (int i = 0; i < numPlayers; i++) { // Loop through the number of players to calculate the total points for the round
        if (i != winner) { // Check if the current player is not the winner
            for (int j = 0; j < players[i].getHandSize(); j++) { // Loop through the current player's hand to calculate the points
                roundPoints = roundPoints + cardPoints(players[i].peekCard(j)); // Add the points of each card in the current player's hand to the total round points
            } // End of for loop
        } // End of if statement
    } // End of for loop

    players[winner].changeScoreBy(roundPoints); // Add the total round points to the winner's score
    
    cout << "Player " << players[winner].getName() << " won the round and earned " << roundPoints << " points!" << endl; // Print message indicating the winner of the round and the points earned
    cout << "Press Enter to continue..."; // Prompt the user to press Enter to continue
    cin.get(); // Read the user's input

}

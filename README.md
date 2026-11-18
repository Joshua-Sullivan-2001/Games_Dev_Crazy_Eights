# Games Dev Crazy Eights

**Joshua Sullivan**  
CLASS-1a: Introduction to Studying Computer Science & AI and Robotics

## Project Overview

You will develop the card game 'Crazy Eights' in C++ to be played through terminal. Your game must support at least two players through hotseat-style multiplayer. Your C++ project must use the three template classes provided although these can be modified if needed.

Through this project you will learn fundamental algorithmic concepts including variables, conditional statements, loops, arrays and functions. You will demonstrate your understanding of these concepts in your project.

You are also encouraged to extend your implementation of Crazy Eights building off the base project requirements. For example, this could include the implementation of a 'bot' player, a menu system or ASCII art.

## Development Status

I have added a Main Menu and a in game Rules menu option in addition to basic requirements.

The game is now playable from the main menu all the way to a winner being declared. I have not added a bot player/players or ASCII art though may update this as a personal project in the future.

The game currently only works on windows due to the usage of the "cls" or clear screen command only working on windows machines. I may also update this later to be usable on other machines eg linux if i find time / do enough research.

## Project Layout

Almost everything is in "game.cpp" however template folder contain the supplied three template classes: "Card", "Deck" and "Player". I have modified slightly the "Card" and "Player" templates however have commented and separate what i have written from what was already there. In Card i only added code in Player i commented out original code and rewrote what i needed.

## What You Need

1. A Windows PC
2. A C++ Compiler (Will use g++ from MSYS2 as example)
3. Git To Download Project (or download via zip from GitHub Repo)

## How To Install

Step 1

Skip "" and <> from commands

Option 1 (Git)

1. Command: git clone "<https://github.com/Joshua-Sullivan-2001/Games_Dev_Crazy_Eights>"
2. Command: cd Games_Dev_Crazy_Eights

Option 2 (Zip)

1. Go to "<https://github.com/Joshua-Sullivan-2001/Games_Dev_Crazy_Eights>"
2. Click green code button and press download as zip
3. Right click zip and then choose extract all
4. Open the extracted folder

Step 2

1. Download and install MSYS2 from <https://www.msys2.org>
2. Open the "MSYS2 UCRT64" app from the Start menu
3. Run this command and press Enter when asked to proceed: "pacman -S mingw-w64-ucrt-x86_64-gcc"
4. Add C:\msys64\ucrt64\bin to your Windows PATH: "Start menu > search "Edit the system environment variables" > Environment Variables > select Path under User variables > Edit > New > paste the folder > OK"
5. Close and reopen PowerShell then check it worked: "g++ --version"

If a version number is shown the compiler is ready

If you have VS code installed you can also just open extracted folder as project inside it and use below Option 2 command to create the .exe

## How To Compile

Option 1

Open PowerShell inside the project folder (the one containing game.cpp) and run: "g++ -std=c++17 game.cpp template/Card.cpp template/Deck.cpp template/Player.cpp -o crazy_eights.exe"

All four .cpp files must be included or the compile will fail. When it finishes there should be a crazy_eights.exe file in the folder.

Option 2

Visual Studio option (Developer Command Prompt): "cl /EHsc /Fe:crazy_eights.exe game.cpp template\Card.cpp template\Deck.cpp template\Player.cpp"

## How to Run

In the same PowerShell window run: ".\crazy_eights.exe" or double click created created .exe

Use a full terminal window like PowerShell or Windows Terminal so the screen clearing works.

## How to Play

1. At the main menu type 1 to start a new game or 2 to read the rules or 3 to exit then press Enter
2. Enter the number of players (2 to 5)
3. Enter a name for each player (leave it blank for a default name like Player 1)
4. Each turn the game tells you whose turn it is. Press Enter then the top card of the discard pile and the current suit are shown along with your hand
5. Type the number of the card you want to play and press Enter. You can play a card that matches the rank or the suit of the top card or any eight
6. If you play an eight you choose the new suit by typing 1 to 4 (Hearts or Diamonds or Clubs or Spades)
7. If you have no valid card you draw one automatically. If the drawn card can be played you are asked y or n whether to play it
8. The first player to empty their hand wins the round and scores points for the cards left in the other hands
9. Rounds keep going until someone reaches the target score (50 points multiplied by the number of players so 100 for 2 players up to 250 for 5 players)
10. Hands are 7 cards for 2 players and 5 cards for 3 to 5 players.
11. Card points: each eight is 50. Each ten or jack or queen or king is 10. Each ace is 1. All other cards are their face value.
12. Pass the keyboard to the next player when the game says whose turn it is so nobody sees another player's hand.

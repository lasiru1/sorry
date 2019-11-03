/**
 *  @file main.cpp
 *  @author Uriel Salazar
 *  @date May 4, 2015, 6:11 PM
 *  @brief CSC5 Project II
 * 
 *  College programming project: The family board game "Sorry!" by Parker
 *  Brothers coded and developed in C++, using NetBeans IDE and Cygwin compiler.
 *  Riverside City College - CSC5 (Program Logic using C++) Section: 43952
 */

//System Libraries
#include <iostream>     //Input/Output Library
#include <iomanip>      //Parametric Library
#include <ctime>        //Time Library
#include <cstdlib>      //Utilities Library
#include <string>       //String Library
#include <fstream>      //File Stream Library
#include <sstream>      //String stream library
using namespace std;    //Input/Output Library under standard namespace

//User Libraries

//Global Constants
const unsigned short TPOSTNS = 75;     //Total number of positions for any player (74)

//Function Prototypes
int int_chk(int);       //Function to validate input is a positive integer
void onePlyr();         //One player version (AI version)
void twoPlyr();         //Two player version
void trePlyr();         //Three player version
void forPlyr();         //Four player version

/**
 * @brief main
 * 
 * This is the main function of the program, execution begins here.
 * 
 * @return Void
 */
int main()
{    
    //Declare variables
    unsigned short plyrs, nPlyrs;               //Number of players (1 - 4)
    char another;                               //Variable for new game (Yes or No)
        
    //Output program title
    cout << setw(24) << " CSC5 Project 2 " << endl;
    cout << setw(24) << "by Uriel Salazar" << endl;
    cout << setw(24) << "----------------" << endl;    
    cout << " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n"
            "|  _   _ _ _ _ _ _ _ _ _ _ _ _  |\n"
            "| | | |              _ _ _ _ _| |\n"
            "| | | |           & |_ _ _ _ _  |\n"
            "| | | |                       | |\n"
            "| | | |                       | |\n"
            "| | |_|                       | |\n"
            "| |                           | |\n"
            "| |  *        SORRY!          | |\n"
            "| |                        @  | |\n"
            "| |                        _  | |\n"
            "| |                       | | | |\n"
            "| |                       | | | |\n"
            "| |_ _ _ _ _              | | | |\n"
            "|  _ _ _ _ _| #           | | | |\n"
            "| |_ _ _ _ _ _ _ _ _ _ _ _| |_| |\n"
            "|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|\n";
    
    //Loop the main menu
    do
    {
        //Prompt user for number of players
        do
        {
            //Prompt user for number of players
            cout << "\nPlease enter the number of players: ";
            nPlyrs = int_chk(plyrs);
            cin.ignore();

            //Determine number of players
            switch (nPlyrs)
            {
                case 1:
                    onePlyr();
                    break;
                case 2:
                    twoPlyr();
                    break;
                case 3:
                    trePlyr();
                    break;
                case 4:
                    forPlyr();
                    break;
                default:
                    cout << "\nThis game can only be played with 1 - 4 players" << endl;  
            }        
        } while(nPlyrs >= 5);       //End do-while loop
        cout << endl;
        
        //Prompt the user if they would like to play again
        cout << "Would you like to play again? (Y/N)? ";
        cin >> another;
        
    //Exit or repeat the do-while loop    
    } while(another == 'Y' || another == 'y');
   
    //Exit the program
    cout << "\nGood-bye!" << endl;
    return 0;
}

/**
 * @brief One Player Mode
 * 
 * This version only prompts for input once, then uses a series of if-statements
 * to simulate an artificial intelligence.
 * Introduces the asterisk character (*) and the octothorpe characters.
 * Utilizes the player 1 and player 2 game boards.
 * 
 * @return Void
 */
void onePlyr()
{
    //Seed the random number generator
    srand(time(0));
    
    //Declare variables
    unsigned short card = 0;                    //Card drawn (Random)
    unsigned short choice, pChoice = 0;         //Which option the user wants after they draw a card
    unsigned short p1cPosn = 0;                 //Player 1's current position on the game board
    unsigned short p2cPosn = 0;                 //Player 2's current position on the game board
    unsigned short temp = 0;                    //Hold a temporary value
    bool restart = false;                       //Bypasses the remaining players turn
    string pOnePos[TPOSTNS];                    //Array containing Player 1 game boards (*)
    string pTwoPos[TPOSTNS];                    //Array containing Player 2 game boards (#)
    string p1Sstrg, p2Sstrg;                    //Player 1 & 2 substrings
    size_t pos1 = 0, pos2;                      //Cursors for creating substrings
    stringstream buffer;                        //variable for the string stream buffer
    
    
    //Load the text file for player 1
    ifstream in_p1("Player1_GameBoards.txt");
    buffer << in_p1.rdbuf();
    p1Sstrg = buffer.str();
    
    //Read the text file into the player 1 array
    for(int i = 0; i < TPOSTNS; i++)
    {
        pos2 = p1Sstrg.find(",", pos1);                    //Search for the "," (position 2 will be where the comma was found)
        pOnePos[i] = p1Sstrg.substr(pos1, (pos2-pos1));    //Make the substring
        pos1 = pos2 + 1;
    }
    
    //Load the text file for player 2
    ifstream in_p2("Player2_GameBoards.txt");
    buffer << in_p2.rdbuf();
    p2Sstrg = buffer.str();
    
    //Read the text file into the player 2 array
    for(int c = 0; c < TPOSTNS; c++)
    {
        pos2 = p2Sstrg.find(",", pos1);                     //Search for the "," (position 2 will be where the comma was found)
        pTwoPos[c] = p2Sstrg.substr(pos1, (pos2-pos1));     //Make the substring
        pos1 = pos2 + 1;
    }
    
    //Output Title
    cout << endl;
    cout << setw(17) << "AI Mode" << endl;
    cout << endl;
    
    //Print players and their symbols
    cout << "Player 1 \t Player 2" << endl;
    cout << "-------- \t --------" << endl;
    cout << "    *    \t     #   " << endl;
        
    //Begin the game
    //Loop until a player exceeds their native 74 position
    while(p1cPosn < 74 && p2cPosn < 74)
    {
        cout << endl;
        cout << setw(25) << "PLAYER 1'S TURN:";
        cout << "\nPress the Enter key to draw a card! ";
        cin.get();

        //generate a random card
        card = (rand() % 11) + 1;
        cout << endl;

        //Determine the card value and apply the rules
        //Player 1 draws a "1"
        if(card == 1)
        {
            //Print the card's specific menu
            cout << "You drew a 1!" << endl;
            cout << "1. Start" << endl;
            cout << "2. Move 1 space forward" << endl;
            cout << "3. Skip turn" << endl;

            //Check for legal move
            do
            {
                if((pChoice > 3) || (pChoice == 1 && p1cPosn >= 9) || (pChoice == 2 && p1cPosn < 9) || (pChoice == 3))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);                
            }while((pChoice > 3) || (pChoice == 1 && p1cPosn >= 9) || (pChoice == 2 && p1cPosn < 9) || (pChoice == 3));

            //Execute the desired action
            switch(pChoice)
            {
                case 1: 
                    p1cPosn = 10;
                    cout << pOnePos[p1cPosn] << endl;   //Output modified game board
                    break;
                case 2:
                    p1cPosn += 1;
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 3:
                    break;
            }
        }

        //Player 1 draws a "2"
        else if(card == 2)
        {
            //Print the card's specific menu
            cout << "You drew a 2!" << endl;
            cout << "1. Start" << endl;
            cout << "2. Move 2 spaces forward" << endl;
            cout << "3. Skip turn" << endl;

            //Check for legal move
            do
            {
                if((pChoice > 3) || (pChoice == 1 && p1cPosn >= 9) || (pChoice == 1 && p1cPosn >= 9) || (pChoice == 3))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice); 
            }while((pChoice > 3) || (pChoice == 1 && p1cPosn >= 9) || (pChoice == 1 && p1cPosn >= 9) || (pChoice == 3));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn = 10;
                    cout << pOnePos[p1cPosn] << endl;   //Output modified game board
                    break;
                case 2:
                    p1cPosn += 2;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;   //Output modified game board
                    break;
                case 3:
                    break;
            }
        }

        //Player 1 draws a "3"
        else if(card == 3)
        {
            //Print the card's specific menu
            cout << "You drew a 3!" << endl;
            cout << "1. Move 3 spaces forward" << endl;
            cout << "2. Skip turn" << endl;

            //Check for legal move 
            do
            {
                if((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);                    
            } while((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn += 3;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    break;
            }
        }

        //Player 1 draws a "4"
        else if(card == 4)
        {
            //Print the card's specific menu
            cout << "You drew a 4!" << endl;
            cout << "1. Move 4 spaces backward" << endl;
            cout << "2. Skip turn" << endl;

            //Check for legal move
            do
            {
                if((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);
            } while((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn -= 4;                       

                    //Determine if Player 1 has moved before their safe zone (P1-0 - P1-8)
                    if(p1cPosn == 8)
                    {
                        p1cPosn = 68;
                    }
                    else if(p1cPosn == 7)
                    {
                        p1cPosn = 67;
                    }
                    else if(p1cPosn == 6)
                    {
                        p1cPosn = 66;
                    }
                    else if(p1cPosn == 5)
                    {
                        p1cPosn = 65;
                    }
                    else if(p1cPosn == 4)
                    {
                        p1cPosn = 64;
                    }
                    else if(p1cPosn == 3)
                    {
                        p1cPosn = 63;
                    }
                    else if(p1cPosn == 2)
                    {
                        p1cPosn = 62;
                    }
                    else if(p1cPosn == 1)
                    {
                        p1cPosn = 61;
                    }
                    else if(p1cPosn == 0)
                    {
                        p1cPosn = 60;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    break;
            }
        }

        //Player 1 draws a "5"
        else if(card == 5)
        {
            //Print the card's specific menu
            cout << "You drew a 5!" << endl;
            cout << "1. Move 5 spaces forward" << endl;
            cout << "2. Skip turn" << endl;

            //Check for legal move
            do
            {
                if((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);  
            } while((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn += 5;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    break;
            }
        }

        //Player 1 draws a "7"
        else if(card == 6)
        {
            //Print the card's specific menu
            cout << "You drew a 7!" << endl;
            cout << "1. Move 7 spaces forward" << endl;
            cout << "2. Move the opponent 7 spaces backward" << endl;
            cout << "3. Skip turn" << endl;

            //Check for legal move
            do
            {
                if((pChoice > 3) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p2cPosn < 9) || (pChoice == 3 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);
            } while((pChoice > 3) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p2cPosn < 9) || (pChoice == 3 && p1cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn += 7;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    p2cPosn -= 7;                       

                    //Determine if Player 2 has moved before their safe zone (P1-0 - P1-8)
                    if(p2cPosn == 8)
                    {
                        p2cPosn = 68;
                    }
                    else if(p2cPosn == 7)
                    {
                        p2cPosn = 67;
                    }
                    else if(p2cPosn == 6)
                    {
                        p2cPosn = 66;
                    }
                    else if(p2cPosn == 5)
                    {
                        p2cPosn = 65;
                    }
                    else if(p2cPosn == 4)
                    {
                        p2cPosn = 64;
                    }
                    else if(p2cPosn == 3)
                    {
                        p2cPosn = 63;
                    }
                    else if(p2cPosn == 2)
                    {
                        p2cPosn = 62;
                    }
                    else if(p2cPosn == 1)
                    {
                        p2cPosn = 61;
                    }
                    else if(p2cPosn == 0)
                    {
                        p2cPosn = 60;
                    }
                    cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                    break;
                case 3:
                    break;
            }
        }

        //Player 1 draws an "8"
        else if(card == 7)
        {
            //Print the card's specific menu
            cout << "You drew an 8!" << endl;
            cout << "1. Move 8 spaces forward" << endl;
            cout << "2. Skip turn" << endl;

            //Check for legal move
            do
            {
                if((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);                
            } while((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn += 8;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    break;
            }
        }

        //Player 1 draws a "10"
        else if(card == 8)
        {
            //Print the card's specific menu
            cout << "You drew a 10!" << endl;
            cout << "1. Move 10 spaces forward" << endl;
            cout << "2. Move 1 space backward" << endl;
            cout << "3. Skip turn" << endl;

            //Check for legal move
            do
            {
                if((pChoice > 3) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn < 9) || (pChoice == 3 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);                   
            }while((pChoice > 3) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn < 9) || (pChoice == 3 && p1cPosn >= 9));           

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn += 10;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    p1cPosn -= 1;                        

                    //Determine if Player 1 has moved before their safe zone (P1-0 - P1-8)
                    if(p1cPosn == 8)
                    {
                        p1cPosn = 68;
                    }
                    else if(p1cPosn == 7)
                    {
                        p1cPosn = 67;
                    }
                    else if(p1cPosn == 6)
                    {
                        p1cPosn = 66;
                    }
                    else if(p1cPosn == 5)
                    {
                        p1cPosn = 65;
                    }
                    else if(p1cPosn == 4)
                    {
                        p1cPosn = 64;
                    }
                    else if(p1cPosn == 3)
                    {
                        p1cPosn = 63;
                    }
                    else if(p1cPosn == 2)
                    {
                        p1cPosn = 62;
                    }
                    else if(p1cPosn == 1)
                    {
                        p1cPosn = 61;
                    }
                    else if(p1cPosn == 0)
                    {
                        p1cPosn = 60;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 3:
                    break;
            }
        }

        //Player 1 draws an "11"
        else if(card == 9)
        {
            //Print the card's specific menu
            cout << "You drew an 11!" << endl;
            cout << "1. Move 11 spaces forward" << endl;
            cout << "2. Switch places with an opposing pawn" << endl;
            cout << "3. Skip turn" << endl;

            //Check for legal move 
            do
            {
                if((pChoice > 3) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn < 9) ||
                  (pChoice == 2 && p2cPosn < 9) || (pChoice == 3 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);
            } while((pChoice > 3) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn < 9) ||
                   (pChoice == 2 && p2cPosn < 9) || (pChoice == 3 && p1cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn += 11;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    if(p1cPosn >= 15 && p2cPosn >= 15)
                    {
                        temp = p1cPosn;
                        p1cPosn = p2cPosn - 15;
                        p2cPosn = temp + 15;
                    }
                    else if(p1cPosn >= 15 && p2cPosn <= 15)
                    {
                        temp = p1cPosn;
                        p1cPosn = 60 + p2cPosn - 15;
                        p2cPosn = 15 - (60 - temp);
                    }
                    else if(p1cPosn <= 15 && p2cPosn <= 15)
                    {
                        temp = p1cPosn;
                        p1cPosn = 60 + p2cPosn - 15;
                        p2cPosn = temp + 15;
                    }
                    else if(p1cPosn <= 15 && p2cPosn >= 15)
                    {
                        p1cPosn = p2cPosn - 15;
                        p2cPosn = p2cPosn - (p1cPosn - 10);
                    }                       

                    //Determine if Player 1 has moved before their safe zone (P1-0 - P1-8)
                    if(p1cPosn == 8)
                    {
                        p1cPosn = 68;
                    }
                    else if(p1cPosn == 7)
                    {
                        p1cPosn = 67;
                    }
                    else if(p1cPosn == 6)
                    {
                        p1cPosn = 66;
                    }
                    else if(p1cPosn == 5)
                    {
                        p1cPosn = 65;
                    }
                    else if(p1cPosn == 4)
                    {
                        p1cPosn = 64;
                    }
                    else if(p1cPosn == 3)
                    {
                        p1cPosn = 63;
                    }
                    else if(p1cPosn == 2)
                    {
                        p1cPosn = 62;
                    }
                    else if(p1cPosn == 1)
                    {
                        p1cPosn = 61;
                    }
                    else if(p1cPosn == 0)
                    {
                        p1cPosn = 60;
                    }

                    //Determine if Player 2 has moved before their safe zone (P2-0 - P2-8)
                    if(p2cPosn == 8)
                    {
                        p2cPosn = 68;
                    }
                    else if(p2cPosn == 7)
                    {
                        p2cPosn = 67;
                    }
                    else if(p2cPosn == 6)
                    {
                        p2cPosn = 66;
                    }
                    else if(p2cPosn == 5)
                    {
                        p2cPosn = 65;
                    }
                    else if(p2cPosn == 4)
                    {
                        p2cPosn = 64;
                    }
                    else if(p2cPosn == 3)
                    {
                        p2cPosn = 63;
                    }
                    else if(p2cPosn == 2)
                    {
                        p2cPosn = 62;
                    }
                    else if(p2cPosn == 1)
                    {
                        p2cPosn = 61;
                    }
                    else if(p2cPosn == 0)
                    {
                        p2cPosn = 60;
                    }
                    cout << pOnePos[p1cPosn] << endl;
                    cout << endl;
                    cout << pTwoPos[p2cPosn] << endl;
                    break;
                case 3:
                    break;
            }
        }

        //Player 1 draws a "12"
        else if(card == 10)
        {
            //Print the card's specific menu
            cout << "You drew a 12!" << endl;
            cout << "1. Move 12 spaces forward" << endl;
            cout << "2. Skip turn" << endl;

            //Check for legal move 
            do
            {
                if((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);
            } while((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn += 12;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    break;
            }
        }      

        //Player 1 draws a "Sorry!" card
        else
        {
            //Print the card's specific menu
            cout << "You drew a \"Sorry!\" Card!" << endl;
            cout << "1. Move an opponent's pawn off the game board!" << endl;
            cout << "2. Skip turn" << endl;

            //Check for legal move 
            do
            {
                if((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);
            } while((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p2cPosn = 0;
                    cout << "\nPlayer 2 has been moved off the game board!" << endl;
                    cout << pTwoPos[0] << endl;
                    break;
                case 2:
                    break;
            }
        }

        //Determine whether Player 1 has won the game
        if(p1cPosn == 74)
        {
            cout << "\nPlayer 1 has won the game!" << endl;
            restart = true;
        }
        
        if(restart == false)
        {            
            //Simulate the AI (Player 2)
            cout << endl;
            cout << setw(25) << "PLAYER 2'S TURN:";
            cout << "\nPress the Enter key to continue... ";
            cin.ignore();
            cin.get();

            //generate a random card
            card = (rand() % 11) + 1;
            cout << endl;

            //Determine the card value and apply the rules
            //Player 2 draws a "1"
            if(card == 1)
            {
                cout << "Player 2 drew a 1!" << endl;

                //Check for legal move
                if(p2cPosn >= 9)
                {
                    pChoice = 2;
                }
                else
                {
                    pChoice = 1;
                }

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        cout << "Player 2 chose to start." << endl;
                        p2cPosn = 10;
                        cout << pTwoPos[p2cPosn] << endl;   //Output modified game board
                        break;
                    case 2:
                        cout << "Player 2 had to move 1 space forward." << endl;    
                        p2cPosn += 1;
                        cout << pTwoPos[p2cPosn] << endl;   //Output modified game board
                        break;
                }
            }

            //Player 2 draws a "2"
            else if(card == 2)
            {
                cout << "Player 2 drew a 2!" << endl;

                //Check for legal move
                if(p2cPosn >= 9)
                {
                    pChoice = 2;
                }
                else
                {
                    pChoice = 1;
                }       

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        cout << "Player 2 chose to start." << endl;
                        p2cPosn = 10;
                        cout << pTwoPos[p2cPosn] << endl;   //Output modified game board
                        break;
                    case 2:
                        cout << "Player 2 had to move 2 spaces forward." << endl;
                        p2cPosn += 2;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;   //Output modified game board
                        break;
                }
            }

            //Player 2 draws a "3"
            else if(card == 3)
            {
                cout << "Player 2 drew a 3!" << endl;

                //Check for legal move
                if(p2cPosn >= 9)
                {
                    pChoice = 1;
                }
                else
                {
                    pChoice = 2;
                }        

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        cout << "Player 2 chose to move 3 spaces forward." << endl;
                        p2cPosn += 3;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;   //Output modified game board
                        break;
                    case 2:
                        cout << "Player 2 had to skip their turn." << endl;
                        break;
                } 
            }

            //Player 2 draws a "4"
            else if(card == 4)
            {
                cout << "Player 2 drew a 4!" << endl;

                //Check for legal move
                if(p2cPosn >= 9)
                {
                    pChoice = 1;
                }
                else
                {
                    pChoice = 2;
                }        

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        cout << "Player 2 chose to move 4 spaces backward." << endl;
                        p2cPosn -= 4;                       

                        //Determine if Player 2 has moved before their safe zone (P2-0 - P2-8)
                        if(p2cPosn == 8)
                        {
                            p2cPosn = 68;
                        }
                        else if(p2cPosn == 7)
                        {
                            p2cPosn = 67;
                        }
                        else if(p2cPosn == 6)
                        {
                            p2cPosn = 66;
                        }
                        else if(p2cPosn == 5)
                        {
                            p2cPosn = 65;
                        }
                        else if(p2cPosn == 4)
                        {
                            p2cPosn = 64;
                        }
                        else if(p2cPosn == 3)
                        {
                            p2cPosn = 63;
                        }
                        else if(p2cPosn == 2)
                        {
                            p2cPosn = 62;
                        }
                        else if(p2cPosn == 1)
                        {
                            p2cPosn = 61;
                        }
                        else if(p2cPosn == 0)
                        {
                            p2cPosn = 60;
                        }
                        cout << pTwoPos[p2cPosn] << endl;   //Output modified game board
                        break;
                    case 2:
                        cout << "Player 2 had to skip their turn." << endl;
                        break;
                } 
            }

            //Player 2 draws a "5"
            else if(card == 5)
            {
                cout << "Player 2 drew a 5!" << endl;

                //Check for legal move
                if(p2cPosn >= 9)
                {
                    pChoice = 1;
                }
                else
                {
                    pChoice = 2;
                }        

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        cout << "Player 2 chose to move 5 spaces forward." << endl;
                        p2cPosn += 5;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;   //Output modified game board
                        break;
                    case 2:
                        cout << "Player 2 had to skip their turn." << endl;
                        break;
                } 
            }

            //Player 2 draws a "7"
            else if(card == 6)
            {
                cout << "Player 2 drew a 7!" << endl;

                //Check for legal move
                if(p1cPosn < (p2cPosn - 15) || p2cPosn >= 18)
                {
                    pChoice = 1;
                }
                else if(p1cPosn > (p2cPosn - 15) && p1cPosn >= 18)
                {
                    pChoice = 2;
                }
                else
                {
                    pChoice = 3;
                }         

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        cout << "Player 2 chose to move 7 spaces forward." << endl;
                        p2cPosn += 7;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;   //Output modified game board
                        break;
                    case 2:
                        cout << "Player 2 chose to move their opponent 7 spaces backward." << endl;
                        p1cPosn -= 7;                        

                        //Determine if Player 2 has moved before their safe zone (P2-0 - P2-8)
                        if(p1cPosn == 8)
                        {
                            p1cPosn = 68;
                        }
                        else if(p1cPosn == 7)
                        {
                            p1cPosn = 67;
                        }
                        else if(p1cPosn == 6)
                        {
                            p1cPosn = 66;
                        }
                        else if(p1cPosn == 5)
                        {
                            p1cPosn = 65;
                        }
                        else if(p1cPosn == 4)
                        {
                            p1cPosn = 64;
                        }
                        else if(p1cPosn == 3)
                        {
                            p1cPosn = 63;
                        }
                        else if(p1cPosn == 2)
                        {
                            p1cPosn = 62;
                        }
                        else if(p1cPosn == 1)
                        {
                            p1cPosn = 61;
                        }
                        else if(p1cPosn == 0)
                        {
                            p1cPosn = 60;
                        }  
                        cout << pOnePos[p1cPosn] << endl;   //Output modified game board
                        break;
                    case 3:
                        cout << "Player 2 had to skip their turn." << endl;
                        break;
                } 
            }

            //Player 2 draws an "8"
            else if(card == 7)
            {
                cout << "Player 2 drew an 8!" << endl;

                //Check for legal move
                if(p2cPosn >= 9)
                {
                    pChoice = 1;
                }
                else
                {
                    pChoice = 2;
                }       

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        cout << "Player 2 chose to move 8 spaces forward." << endl;
                        p2cPosn += 8;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;   //Output modified game board
                        break;
                    case 2:
                        cout << "Player 2 had to skip their turn." << endl;
                        break;
                } 
            }

            //Player 2 draws a "10"
            else if(card == 8)
            {
                cout << "Player 2 drew a 10!" << endl;

                //Check for legal move
                if(p2cPosn < 9) 
                {
                    pChoice = 3;
                }
                else if(p2cPosn == 9 || p2cPosn == 10)
                {
                    pChoice = 2;
                }
                else
                {
                    pChoice = 1;
                }

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        cout << "Player 2 chose to move 10 spaces forward." << endl;
                        p2cPosn += 10;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;   //Output modified game board
                        break;
                    case 2:
                        cout << "Player 2 chose to move 1 space backwards." << endl;
                        p2cPosn -= 1;                        

                        //Determine if Player 2 has moved before their safe zone (P2-0 - P2-8)
                        if(p2cPosn == 8)
                        {
                            p2cPosn = 68;
                        }
                        else if(p2cPosn == 7)
                        {
                            p2cPosn = 67;
                        }
                        else if(p2cPosn == 6)
                        {
                            p2cPosn = 66;
                        }
                        else if(p2cPosn == 5)
                        {
                            p2cPosn = 65;
                        }
                        else if(p2cPosn == 4)
                        {
                            p2cPosn = 64;
                        }
                        else if(p2cPosn == 3)
                        {
                            p2cPosn = 63;
                        }
                        else if(p2cPosn == 2)
                        {
                            p2cPosn = 62;
                        }
                        else if(p2cPosn == 1)
                        {
                            p2cPosn = 61;
                        }
                        else if(p2cPosn == 0)
                        {
                            p2cPosn = 60;
                        } 
                        cout << pTwoPos[p2cPosn] << endl;   //Output modified game board
                        break;
                    case 3:
                        cout << "Player 2 had to skip their turn." << endl;
                        break;
                } 
            }

            //Player 2 draws an "11"
            else if(card == 9)
            {
                cout << "Player 2 drew an 11!" << endl;

                //Check for legal move
                if(p2cPosn >= 1 && p2cPosn < p1cPosn)
                {
                    pChoice = 2;
                }
                else if(p2cPosn >= 10)
                {
                    pChoice = 1;
                }
                else
                {
                    pChoice = 3;
                }

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        cout << "Player 2 chose to move 11 spaces forwards." << endl;
                        p2cPosn += 11;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;   //Output modified game board
                        break;
                    case 2:              
                        cout << "Player 2 chose to switch places with Player 1." << endl;
                        if(p2cPosn >= 15 && p1cPosn >= 15)
                        {
                            temp = p2cPosn;
                            p2cPosn = p1cPosn + 15;
                            p1cPosn = temp - 15;
                        }
                        else if(p1cPosn >= 15 && p2cPosn <= 15)
                        {
                            temp = p2cPosn;
                            p2cPosn = 15 - (60 - p1cPosn);
                            p1cPosn = 60 + temp - 15;
                        }
                        else if(p1cPosn <= 15 && p2cPosn <= 15)
                        {
                            temp = p2cPosn;
                            p1cPosn = p1cPosn + 15;
                            p2cPosn = 60 - (15 - p2cPosn);
                        }
                        else if(p1cPosn <= 15 && p2cPosn >= 15)
                        {
                            temp = p2cPosn;
                            p2cPosn = p1cPosn + 15;
                            p1cPosn = 60 + (temp - 15);
                        }                        

                        //Determine if Player 1 has moved before their safe zone (P1-0 - P1-8)
                        if(p1cPosn == 8)
                        {
                            p1cPosn = 68;
                        }
                        else if(p1cPosn == 7)
                        {
                            p1cPosn = 67;
                        }
                        else if(p1cPosn == 6)
                        {
                            p1cPosn = 66;
                        }
                        else if(p1cPosn == 5)
                        {
                            p1cPosn = 65;
                        }
                        else if(p1cPosn == 4)
                        {
                            p1cPosn = 64;
                        }
                        else if(p1cPosn == 3)
                        {
                            p1cPosn = 63;
                        }
                        else if(p1cPosn == 2)
                        {
                            p1cPosn = 62;
                        }
                        else if(p1cPosn == 1)
                        {
                            p1cPosn = 61;
                        }
                        else if(p1cPosn == 0)
                        {
                            p1cPosn = 60;
                        }

                        //Determine if Player 2 has moved before their safe zone (P2-0 - P2-8)
                        if(p2cPosn == 8)
                        {
                            p2cPosn = 68;
                        }
                        else if(p2cPosn == 7)
                        {
                            p2cPosn = 67;
                        }
                        else if(p2cPosn == 6)
                        {
                            p2cPosn = 66;
                        }
                        else if(p2cPosn == 5)
                        {
                            p2cPosn = 65;
                        }
                        else if(p2cPosn == 4)
                        {
                            p2cPosn = 64;
                        }
                        else if(p2cPosn == 3)
                        {
                            p2cPosn = 63;
                        }
                        else if(p2cPosn == 2)
                        {
                            p2cPosn = 62;
                        }
                        else if(p2cPosn == 1)
                        {
                            p2cPosn = 61;
                        }
                        else if(p2cPosn == 0)
                        {
                            p2cPosn = 60;
                        }
                        cout << pTwoPos[p2cPosn] << endl;   //Output modified game board
                        cout << endl;
                        cout << pOnePos[p1cPosn] << endl;   //Output modified game board
                        break;
                    case 3:
                        cout << "Player 2 had to skip their turn." << endl;
                        break;
                } 
            }

            //Player 2 draws a "12"
            else if(card == 10)
            {
                cout << "Player 2 drew a 12!" << endl;

                //Check for legal move
                if(p2cPosn >= 10)
                {
                    pChoice = 1;
                }
                else
                {
                    pChoice = 2;
                }       

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        cout << "Player 2 chose to move 12 spaces forward." << endl;
                        p2cPosn += 12;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;   //Output modified game board
                        break;
                    case 2:
                        cout << "Player 2 had to skip their turn." << endl;
                        break;
                } 
            }

            //Player 2 draws a "Sorry!" card
            else
            {
                cout << "Player 2 drew a \"Sorry!\" card!" << endl;

                //Check for legal move
                if(p1cPosn >= 1)
                {
                    pChoice = 1;
                }
                else
                {
                    pChoice = 2;
                }       

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p1cPosn = 0;
                        cout << "Player 1 has been moved off the game board!" << endl;
                        cout << pOnePos[0] << endl;    
                        break;
                    case 2:
                        cout << "Player 2 had to skip their turn." << endl;
                        break;
                } 
            }

            //Determine whether player 2 has won the game
            if(p2cPosn >= 74)
            {
                cout << "\nPlayer 2 has won the game!" << endl;
            }
        }
        
        //Reset the player's choice
        pChoice = 0;

    //Exit or repeat the while loop
    }
}

/**
 * @brief Two Player Mode
 * 
 * This function prompts for input twice; once for each human player.
 * 
 * @return Void
 */
void twoPlyr()
{   
    //Seed the random number generator
    srand(time(0));
    
    //Declare variables
    unsigned short card = 0;                    //Card drawn (Random)
    unsigned short choice, pChoice = 0;         //Which option the user wants after they draw a card
    unsigned short p1cPosn = 0;                 //Player 1's current position on the game board
    unsigned short p2cPosn = 0;                 //Player 2's current position on the game board
    unsigned short temp = 0;                    //Hold a temporary value
    bool restart = false;                       //Bypasses the remaining players turn
    string pOnePos[TPOSTNS];                    //Array containing Player 1 game boards (*)
    string pTwoPos[TPOSTNS];                    //Array containing Player 2 game boards (#)
    string p1Sstrg, p2Sstrg;                    //Player 1 & 2 substrings
    size_t pos1 = 0, pos2;                      //Cursors for creating substrings
    stringstream buffer;                        //variable for the string stream buffer
    
    //Output Title
    cout << endl;
    cout << setw(20) << "2 player Mode" << endl;
    cout << endl;
    
    //Print players and their symbols
    cout << "Player 1 \t Player 2" << endl;
    cout << "-------- \t --------" << endl;
    cout << "    *    \t     #   " << endl;
    
    //Load the text file for player 1
    ifstream in_p1("Player1_GameBoards.txt");
    buffer << in_p1.rdbuf();
    p1Sstrg = buffer.str();
    
    //Read the text file into the player 1 array
    for(int i = 0; i < TPOSTNS; i++)
    {
        pos2 = p1Sstrg.find(",", pos1);                    //Search for the "," (position 2 will be where the comma was found)
        pOnePos[i] = p1Sstrg.substr(pos1, (pos2-pos1));    //Make the substring
        pos1 = pos2 + 1;
    }
    
    //Load the text file for player 2
    ifstream in_p2("Player2_GameBoards.txt");
    buffer << in_p2.rdbuf();
    p2Sstrg = buffer.str();
    
    //Read the text file into the player 2 array
    for(int c = 0; c < TPOSTNS; c++)
    {
        pos2 = p2Sstrg.find(",", pos1);                     //Search for the "," (position 2 will be where the comma was found)
        pTwoPos[c] = p2Sstrg.substr(pos1, (pos2-pos1));     //Make the substring
        pos1 = pos2 + 1;
    }
    
    //Begin the game
    //Loop until a player exceeds their native 74th position
    while(p1cPosn < 74 && p2cPosn < 74)
    {
        cout << endl;
        cout << setw(25) << "PLAYER 1'S TURN:";
        cout << "\nPress the Enter key to draw a card! ";
        cin.get();

        //generate a random card
        card = (rand() % 11) + 1;
        cout << endl;

        //Determine the card value and apply the rules
        //Player 1 draws a "1"
        if(card == 1)
        {
            //Print the card's specific menu
            cout << "You drew a 1!" << endl;
            cout << "1. Start" << endl;
            cout << "2. Move 1 space forward" << endl;
            cout << "3. Skip turn" << endl;

            //Check for legal move
            do
            {
                if((pChoice > 3) || (pChoice == 1 && p1cPosn >= 9) || (pChoice == 2 && p1cPosn < 9) || (pChoice == 3))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);                
            }while((pChoice > 3) || (pChoice == 1 && p1cPosn >= 9) || (pChoice == 2 && p1cPosn < 9) || (pChoice == 3));

            //Execute the desired action
            switch(pChoice)
            {
                case 1: 
                    p1cPosn = 10;
                    cout << pOnePos[p1cPosn] << endl;   //Output modified game board
                    break;
                case 2:
                    p1cPosn += 1;
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 3:
                    break;
            }
        }

        //Player 1 draws a "2"
        else if(card == 2)
        {
            //Print the card's specific menu
            cout << "You drew a 2!" << endl;
            cout << "1. Start" << endl;
            cout << "2. Move 2 spaces forward" << endl;
            cout << "3. Skip turn" << endl;

            //Check for legal move
            do
            {
                if((pChoice > 3) || (pChoice == 1 && p1cPosn >= 9) || (pChoice == 1 && p1cPosn >= 9) || (pChoice == 3))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice); 
            }while((pChoice > 3) || (pChoice == 1 && p1cPosn >= 9) || (pChoice == 1 && p1cPosn >= 9) || (pChoice == 3));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn = 10;
                    cout << pOnePos[p1cPosn] << endl;   //Output modified game board
                    break;
                case 2:
                    p1cPosn += 2;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;   //Output modified game board
                    break;
                case 3:
                    break;
            }
        }

        //Player 1 draws a "3"
        else if(card == 3)
        {
            //Print the card's specific menu
            cout << "You drew a 3!" << endl;
            cout << "1. Move 3 spaces forward" << endl;
            cout << "2. Skip turn" << endl;

            //Check for legal move 
            do
            {
                if((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);                    
            } while((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn += 3;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    break;
            }
        }

        //Player 1 draws a "4"
        else if(card == 4)
        {
            //Print the card's specific menu
            cout << "You drew a 4!" << endl;
            cout << "1. Move 4 spaces backward" << endl;
            cout << "2. Skip turn" << endl;

            //Check for legal move
            do
            {
                if((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);
            } while((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn -= 4;                       

                    //Determine if Player 1 has moved before their safe zone (P1-0 - P1-8)
                    if(p1cPosn == 8)
                    {
                        p1cPosn = 68;
                    }
                    else if(p1cPosn == 7)
                    {
                        p1cPosn = 67;
                    }
                    else if(p1cPosn == 6)
                    {
                        p1cPosn = 66;
                    }
                    else if(p1cPosn == 5)
                    {
                        p1cPosn = 65;
                    }
                    else if(p1cPosn == 4)
                    {
                        p1cPosn = 64;
                    }
                    else if(p1cPosn == 3)
                    {
                        p1cPosn = 63;
                    }
                    else if(p1cPosn == 2)
                    {
                        p1cPosn = 62;
                    }
                    else if(p1cPosn == 1)
                    {
                        p1cPosn = 61;
                    }
                    else if(p1cPosn == 0)
                    {
                        p1cPosn = 60;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    break;
            }
        }

        //Player 1 draws a "5"
        else if(card == 5)
        {
            //Print the card's specific menu
            cout << "You drew a 5!" << endl;
            cout << "1. Move 5 spaces forward" << endl;
            cout << "2. Skip turn" << endl;

            //Check for legal move
            do
            {
                if((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);  
            } while((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn += 5;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    break;
            }
        }

        //Player 1 draws a "7"
        else if(card == 6)
        {
            //Print the card's specific menu
            cout << "You drew a 7!" << endl;
            cout << "1. Move 7 spaces forward" << endl;
            cout << "2. Move the opponent 7 spaces backward" << endl;
            cout << "3. Skip turn" << endl;

            //Check for legal move
            do
            {
                if((pChoice > 3) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p2cPosn < 9) || (pChoice == 3 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);
            } while((pChoice > 3) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p2cPosn < 9) || (pChoice == 3 && p1cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn += 7;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    p2cPosn -= 7;                       

                    //Determine if Player 2 has moved before their safe zone (P1-0 - P1-8)
                    if(p2cPosn == 8)
                    {
                        p2cPosn = 68;
                    }
                    else if(p2cPosn == 7)
                    {
                        p2cPosn = 67;
                    }
                    else if(p2cPosn == 6)
                    {
                        p2cPosn = 66;
                    }
                    else if(p2cPosn == 5)
                    {
                        p2cPosn = 65;
                    }
                    else if(p2cPosn == 4)
                    {
                        p2cPosn = 64;
                    }
                    else if(p2cPosn == 3)
                    {
                        p2cPosn = 63;
                    }
                    else if(p2cPosn == 2)
                    {
                        p2cPosn = 62;
                    }
                    else if(p2cPosn == 1)
                    {
                        p2cPosn = 61;
                    }
                    else if(p2cPosn == 0)
                    {
                        p2cPosn = 60;
                    }
                    cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                    break;
                case 3:
                    break;
            }
        }

        //Player 1 draws an "8"
        else if(card == 7)
        {
            //Print the card's specific menu
            cout << "You drew an 8!" << endl;
            cout << "1. Move 8 spaces forward" << endl;
            cout << "2. Skip turn" << endl;

            //Check for legal move
            do
            {
                if((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);                
            } while((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn += 8;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    break;
            }
        }

        //Player 1 draws a "10"
        else if(card == 8)
        {
            //Print the card's specific menu
            cout << "You drew a 10!" << endl;
            cout << "1. Move 10 spaces forward" << endl;
            cout << "2. Move 1 space backward" << endl;
            cout << "3. Skip turn" << endl;

            //Check for legal move
            do
            {
                if((pChoice > 3) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn < 9) || (pChoice == 3 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);                   
            }while((pChoice > 3) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn < 9) || (pChoice == 3 && p1cPosn >= 9));           

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn += 10;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    p1cPosn -= 1;                        

                    //Determine if Player 1 has moved before their safe zone (P1-0 - P1-8)
                    if(p1cPosn == 8)
                    {
                        p1cPosn = 68;
                    }
                    else if(p1cPosn == 7)
                    {
                        p1cPosn = 67;
                    }
                    else if(p1cPosn == 6)
                    {
                        p1cPosn = 66;
                    }
                    else if(p1cPosn == 5)
                    {
                        p1cPosn = 65;
                    }
                    else if(p1cPosn == 4)
                    {
                        p1cPosn = 64;
                    }
                    else if(p1cPosn == 3)
                    {
                        p1cPosn = 63;
                    }
                    else if(p1cPosn == 2)
                    {
                        p1cPosn = 62;
                    }
                    else if(p1cPosn == 1)
                    {
                        p1cPosn = 61;
                    }
                    else if(p1cPosn == 0)
                    {
                        p1cPosn = 60;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 3:
                    break;
            }
        }

        //Player 1 draws an "11"
        else if(card == 9)
        {
            //Print the card's specific menu
            cout << "You drew an 11!" << endl;
            cout << "1. Move 11 spaces forward" << endl;
            cout << "2. Switch places with an opposing pawn" << endl;
            cout << "3. Skip turn" << endl;

            //Check for legal move 
            do
            {
                if((pChoice > 3) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn < 9) ||
                  (pChoice == 2 && p2cPosn < 9) || (pChoice == 3 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);
            } while((pChoice > 3) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn < 9) ||
                   (pChoice == 2 && p2cPosn < 9) || (pChoice == 3 && p1cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn += 11;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    if(p1cPosn >= 15 && p2cPosn >= 15)
                    {
                        temp = p1cPosn;
                        p1cPosn = p2cPosn - 15;
                        p2cPosn = temp + 15;
                    }
                    else if(p1cPosn >= 15 && p2cPosn <= 15)
                    {
                        temp = p1cPosn;
                        p1cPosn = 60 + p2cPosn - 15;
                        p2cPosn = 15 - (60 - temp);
                    }
                    else if(p1cPosn <= 15 && p2cPosn <= 15)
                    {
                        temp = p1cPosn;
                        p1cPosn = 60 + p2cPosn - 15;
                        p2cPosn = temp + 15;
                    }
                    else if(p1cPosn <= 15 && p2cPosn >= 15)
                    {
                        p1cPosn = p2cPosn - 15;
                        p2cPosn = p2cPosn - (p1cPosn - 10);
                    }                       

                    //Determine if Player 1 has moved before their safe zone (P1-0 - P1-8)
                    if(p1cPosn == 8)
                    {
                        p1cPosn = 68;
                    }
                    else if(p1cPosn == 7)
                    {
                        p1cPosn = 67;
                    }
                    else if(p1cPosn == 6)
                    {
                        p1cPosn = 66;
                    }
                    else if(p1cPosn == 5)
                    {
                        p1cPosn = 65;
                    }
                    else if(p1cPosn == 4)
                    {
                        p1cPosn = 64;
                    }
                    else if(p1cPosn == 3)
                    {
                        p1cPosn = 63;
                    }
                    else if(p1cPosn == 2)
                    {
                        p1cPosn = 62;
                    }
                    else if(p1cPosn == 1)
                    {
                        p1cPosn = 61;
                    }
                    else if(p1cPosn == 0)
                    {
                        p1cPosn = 60;
                    }

                    //Determine if Player 2 has moved before their safe zone (P2-0 - P2-8)
                    if(p2cPosn == 8)
                    {
                        p2cPosn = 68;
                    }
                    else if(p2cPosn == 7)
                    {
                        p2cPosn = 67;
                    }
                    else if(p2cPosn == 6)
                    {
                        p2cPosn = 66;
                    }
                    else if(p2cPosn == 5)
                    {
                        p2cPosn = 65;
                    }
                    else if(p2cPosn == 4)
                    {
                        p2cPosn = 64;
                    }
                    else if(p2cPosn == 3)
                    {
                        p2cPosn = 63;
                    }
                    else if(p2cPosn == 2)
                    {
                        p2cPosn = 62;
                    }
                    else if(p2cPosn == 1)
                    {
                        p2cPosn = 61;
                    }
                    else if(p2cPosn == 0)
                    {
                        p2cPosn = 60;
                    }
                    cout << pOnePos[p1cPosn] << endl;
                    cout << endl;
                    cout << pTwoPos[p2cPosn] << endl;
                    break;
                case 3:
                    break;
            }
        }

        //Player 1 draws a "12"
        else if(card == 10)
        {
            //Print the card's specific menu
            cout << "You drew a 12!" << endl;
            cout << "1. Move 12 spaces forward" << endl;
            cout << "2. Skip turn" << endl;

            //Check for legal move 
            do
            {
                if((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);
            } while((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn += 12;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    break;
            }
        }      

        //Player 1 draws a "Sorry!" card
        else
        {
            //Print the card's specific menu
            cout << "You drew a \"Sorry!\" Card!" << endl;
            cout << "1. Move an opponent's pawn off the game board!" << endl;
            cout << "2. Skip turn" << endl;

            //Check for legal move 
            do
            {
                if((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);
            } while((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p2cPosn = 0;
                    cout << "\nPlayer 2 has been moved off the game board!" << endl;
                    cout << pTwoPos[0] << endl;
                    break;
                case 2:
                    break;
            }
        }

        //Determine whether Player 1 has won the game
        if(p1cPosn == 74)
        {
            cout << "\nPlayer 1 has won the game!" << endl;
            restart = true;
        }

        //Reset the player's choice
        pChoice = 0;
        
        //Begin Player 2's turn
        if(restart == false)
        {
            cout << endl;
            cout << setw(25) << "PLAYER 2'S TURN:";
            cout << "\nPress the Enter key to draw a card! ";  
            cin.ignore();
            cin.get();

            //generate a random card
            card = (rand() % 11) + 1;
            cout << endl;

            //Determine the card value and apply the rules
            //Player 2 draws a "1"
            if(card == 1)
            {
                //Print the card's specific menu
                cout << "You drew a 1!" << endl;
                cout << "1. Start" << endl;
                cout << "2. Move 1 space forward" << endl;
                cout << "3. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 3) || (pChoice == 1 && p2cPosn >= 9) || (pChoice == 2 && p2cPosn < 9) || (pChoice == 3))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);                
                }while((pChoice > 3) || (pChoice == 1 && p2cPosn >= 9) || (pChoice == 2 && p2cPosn < 9) || (pChoice == 3));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1: 
                        p2cPosn = 10;
                        cout << pTwoPos[p2cPosn] << endl;   //Output modified game board
                        break;
                    case 2:
                        p2cPosn += 1;
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 3:
                        break;
                }
            }

            //Player 2 draws a "2"
            else if(card == 2)
            {
                //Print the card's specific menu
                cout << "You drew a 2!" << endl;
                cout << "1. Start" << endl;
                cout << "2. Move 2 spaces forward" << endl;
                cout << "3. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 3) || (pChoice == 1 && p2cPosn >= 9) || (pChoice == 1 && p2cPosn >= 9) || (pChoice == 3))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice); 
                }while((pChoice > 3) || (pChoice == 1 && p2cPosn >= 9) || (pChoice == 1 && p2cPosn >= 9) || (pChoice == 3));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p2cPosn = 10;
                        cout << pTwoPos[p2cPosn] << endl;   //Output modified game board
                        break;
                    case 2:
                        p2cPosn += 2;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;   //Output modified game board
                        break;
                    case 3:
                        break;
                }
            }

            //Player 2 draws a "3"
            else if(card == 3)
            {
                //Print the card's specific menu
                cout << "You drew a 3!" << endl;
                cout << "1. Move 3 spaces forward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move 
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);                    
                } while((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p2cPosn += 3;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }

            //Player 2 draws a "4"
            else if(card == 4)
            {
                //Print the card's specific menu
                cout << "You drew a 4!" << endl;
                cout << "1. Move 4 spaces backward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p2cPosn -= 4;                       

                        //Determine if Player 2 has moved before their safe zone (P1-0 - P1-8)
                        if(p2cPosn == 8)
                        {
                            p2cPosn = 68;
                        }
                        else if(p2cPosn == 7)
                        {
                            p2cPosn = 67;
                        }
                        else if(p2cPosn == 6)
                        {
                            p2cPosn = 66;
                        }
                        else if(p2cPosn == 5)
                        {
                            p2cPosn = 65;
                        }
                        else if(p2cPosn == 4)
                        {
                            p2cPosn = 64;
                        }
                        else if(p2cPosn == 3)
                        {
                            p2cPosn = 63;
                        }
                        else if(p2cPosn == 2)
                        {
                            p2cPosn = 62;
                        }
                        else if(p2cPosn == 1)
                        {
                            p2cPosn = 61;
                        }
                        else if(p2cPosn == 0)
                        {
                            p2cPosn = 60;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }

            //Player 2 draws a "5"
            else if(card == 5)
            {
                //Print the card's specific menu
                cout << "You drew a 5!" << endl;
                cout << "1. Move 5 spaces forward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);  
                } while((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p2cPosn += 5;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }

            //Player 2 draws a "7"
            else if(card == 6)
            {
                //Print the card's specific menu
                cout << "You drew a 7!" << endl;
                cout << "1. Move 7 spaces forward" << endl;
                cout << "2. Move the opponent 7 spaces backward" << endl;
                cout << "3. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 3) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p1cPosn < 9) || (pChoice == 3 && p2cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 3) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p1cPosn < 9) || (pChoice == 3 && p2cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p2cPosn += 7;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        p1cPosn -= 7;                       

                        //Determine if Player 1 has moved before their safe zone (P1-0 - P1-8)
                        if(p1cPosn == 8)
                        {
                            p1cPosn = 68;
                        }
                        else if(p1cPosn == 7)
                        {
                            p1cPosn = 67;
                        }
                        else if(p1cPosn == 6)
                        {
                            p1cPosn = 66;
                        }
                        else if(p1cPosn == 5)
                        {
                            p1cPosn = 65;
                        }
                        else if(p1cPosn == 4)
                        {
                            p1cPosn = 64;
                        }
                        else if(p1cPosn == 3)
                        {
                            p1cPosn = 63;
                        }
                        else if(p1cPosn == 2)
                        {
                            p1cPosn = 62;
                        }
                        else if(p1cPosn == 1)
                        {
                            p1cPosn = 61;
                        }
                        else if(p1cPosn == 0)
                        {
                            p1cPosn = 60;
                        }
                        cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                        break;
                    case 3:
                        break;
                }
            }

            //Player 2 draws an "8"
            else if(card == 7)
            {
                //Print the card's specific menu
                cout << "You drew an 8!" << endl;
                cout << "1. Move 8 spaces forward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);                
                } while((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p2cPosn += 8;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }

            //Player 2 draws a "10"
            else if(card == 8)
            {
                //Print the card's specific menu
                cout << "You drew a 10!" << endl;
                cout << "1. Move 10 spaces forward" << endl;
                cout << "2. Move 1 space backward" << endl;
                cout << "3. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 3) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn < 9) || (pChoice == 3 && p2cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);                   
                }while((pChoice > 3) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn < 9) || (pChoice == 3 && p2cPosn >= 9));           

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p2cPosn += 10;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        p2cPosn -= 1;                        

                        //Determine if Player 2 has moved before their safe zone (P1-0 - P1-8)
                        if(p2cPosn == 8)
                        {
                            p2cPosn = 68;
                        }
                        else if(p2cPosn == 7)
                        {
                            p2cPosn = 67;
                        }
                        else if(p2cPosn == 6)
                        {
                            p2cPosn = 66;
                        }
                        else if(p2cPosn == 5)
                        {
                            p2cPosn = 65;
                        }
                        else if(p2cPosn == 4)
                        {
                            p2cPosn = 64;
                        }
                        else if(p2cPosn == 3)
                        {
                            p2cPosn = 63;
                        }
                        else if(p2cPosn == 2)
                        {
                            p2cPosn = 62;
                        }
                        else if(p2cPosn == 1)
                        {
                            p2cPosn = 61;
                        }
                        else if(p2cPosn == 0)
                        {
                            p2cPosn = 60;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 3:
                        break;
                }
            }

            //Player 2 draws an "11"
            else if(card == 9)
            {
                //Print the card's specific menu
                cout << "You drew an 11!" << endl;
                cout << "1. Move 11 spaces forward" << endl;
                cout << "2. Switch places with an opposing pawn" << endl;
                cout << "3. Skip turn" << endl;

                //Check for legal move 
                do
                {
                    if((pChoice > 3) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn < 9) ||
                      (pChoice == 2 && p1cPosn < 9) || (pChoice == 3 && p2cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 3) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn < 9) ||
                       (pChoice == 2 && p1cPosn < 9) || (pChoice == 3 && p2cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p2cPosn += 11;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        if(p2cPosn >= 15 && p1cPosn >= 15)
                        {
                            temp = p2cPosn;
                            p2cPosn = p1cPosn - 15;
                            p1cPosn = temp + 15;
                        }
                        else if(p2cPosn >= 15 && p1cPosn <= 15)
                        {
                            temp = p2cPosn;
                            p2cPosn = 60 + p1cPosn - 15;
                            p1cPosn = 15 - (60 - temp);
                        }
                        else if(p2cPosn <= 15 && p1cPosn <= 15)
                        {
                            temp = p2cPosn;
                            p2cPosn = 60 + p1cPosn - 15;
                            p1cPosn = temp + 15;
                        }
                        else if(p2cPosn <= 15 && p1cPosn >= 15)
                        {
                            p2cPosn = p1cPosn - 15;
                            p1cPosn = p1cPosn - (p2cPosn - 10);
                        }                       

                        //Determine if Player 2 has moved before their safe zone (P1-0 - P1-8)
                        if(p2cPosn == 8)
                        {
                            p2cPosn = 68;
                        }
                        else if(p2cPosn == 7)
                        {
                            p2cPosn = 67;
                        }
                        else if(p2cPosn == 6)
                        {
                            p2cPosn = 66;
                        }
                        else if(p2cPosn == 5)
                        {
                            p2cPosn = 65;
                        }
                        else if(p2cPosn == 4)
                        {
                            p2cPosn = 64;
                        }
                        else if(p2cPosn == 3)
                        {
                            p2cPosn = 63;
                        }
                        else if(p2cPosn == 2)
                        {
                            p2cPosn = 62;
                        }
                        else if(p2cPosn == 1)
                        {
                            p2cPosn = 61;
                        }
                        else if(p2cPosn == 0)
                        {
                            p2cPosn = 60;
                        }

                        //Determine if Player 1 has moved before their safe zone (P2-0 - P2-8)
                        if(p1cPosn == 8)
                        {
                            p1cPosn = 68;
                        }
                        else if(p1cPosn == 7)
                        {
                            p1cPosn = 67;
                        }
                        else if(p1cPosn == 6)
                        {
                            p1cPosn = 66;
                        }
                        else if(p1cPosn == 5)
                        {
                            p1cPosn = 65;
                        }
                        else if(p1cPosn == 4)
                        {
                            p1cPosn = 64;
                        }
                        else if(p1cPosn == 3)
                        {
                            p1cPosn = 63;
                        }
                        else if(p1cPosn == 2)
                        {
                            p1cPosn = 62;
                        }
                        else if(p1cPosn == 1)
                        {
                            p1cPosn = 61;
                        }
                        else if(p1cPosn == 0)
                        {
                            p1cPosn = 60;
                        }
                        cout << pTwoPos[p2cPosn] << endl;
                        cout << endl;
                        cout << pTwoPos[p1cPosn] << endl;
                        break;
                    case 3:
                        break;
                }
            }

            //Player 2 draws a "12"
            else if(card == 10)
            {
                //Print the card's specific menu
                cout << "You drew a 12!" << endl;
                cout << "1. Move 12 spaces forward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move 
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p2cPosn += 12;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }      

            //Player 2 draws a "Sorry!" card
            else
            {
                //Print the card's specific menu
                cout << "You drew a \"Sorry!\" Card!" << endl;
                cout << "1. Move an opponent's pawn off the game board!" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move 
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p1cPosn = 0;
                        cout << "\nPlayer 1 has been moved off the game board!" << endl;
                        cout << pTwoPos[0] << endl;
                        break;
                    case 2:
                        break;
                }
            }

            //Determine whether player 2 has won the game
            if(p2cPosn >= 74)
            {
                cout << "\nPlayer 2 has won the game!" << endl;
            }
        }

        //Reset the player's choice
        pChoice = 0;
        cin.clear();
        cin.ignore();          

    //Exit or repeat the while loop
    }
}

/**
 * @brief Three Player Mode
 * 
 * This function prompts for input three times; once for each human player
 * Introduces the ampersand character (&) and utilizes the player 3 game boards
 * 
 * @return Void
 */
void trePlyr()
{
    //Seed the random number generator
    srand(time(0));
    
    //Declare variables
    unsigned short card = 0;                    //Card drawn (Random)
    unsigned short choice, pChoice = 0;         //Which option the user wants after they draw a card
    unsigned short p1cPosn = 0;                 //Player 1's current position on the game board
    unsigned short p2cPosn = 0;                 //Player 2's current position on the game board
    unsigned short p3cPosn = 0;                 //Player 2's current position on the game board
    unsigned short temp = 0;                    //Hold a temporary value
    bool restart = false;                       //Exits the function if player 1 wins
    string pOnePos[TPOSTNS];                    //Array containing Player 1 game boards (*)
    string pTwoPos[TPOSTNS];                    //Array containing Player 2 game boards (#)
    string pTrePos[TPOSTNS];                    //Array containing Player 3 game boards (#)
    string p1Sstrg, p2Sstrg, p3Sstrg;           //Player 1 & 2 substrings
    size_t pos1 = 0, pos2;                      //Cursors for creating substrings
    stringstream buffer;                        //variable for the string stream buffer
    
    //Output Title
    cout << endl;
    cout << setw(27) << "3 player Mode" << endl;
    cout << endl;
    
    //Print players and their symbols
    cout << "Player 1 \t Player 2 \t Player 3" << endl;
    cout << "-------- \t -------- \t --------" << endl;
    cout << "    *    \t     #    \t     &   " << endl;
    
    //Load the text file for player 1
    ifstream in_p1("Player1_GameBoards.txt");
    buffer << in_p1.rdbuf();
    p1Sstrg = buffer.str();
    
    //Read the text file into the player 1 array
    for(int i = 0; i < TPOSTNS; i++)
    {
        pos2 = p1Sstrg.find(",", pos1);                    //Search for the "," (position 2 will be where the comma was found)
        pOnePos[i] = p1Sstrg.substr(pos1, (pos2-pos1));    //Make the substring
        pos1 = pos2 + 1;
    }
    
    //Load the text file for player 2
    ifstream in_p2("Player2_GameBoards.txt");
    buffer << in_p2.rdbuf();
    p2Sstrg = buffer.str();
    
    //Read the text file into the player 2 array
    for(int c = 0; c < TPOSTNS; c++)
    {
        pos2 = p2Sstrg.find(",", pos1);                     //Search for the "," (position 2 will be where the comma was found)
        pTwoPos[c] = p2Sstrg.substr(pos1, (pos2-pos1));     //Make the substring
        pos1 = pos2 + 1;
    }
    
    //Load the text file for player 3
    ifstream in_p3("Player3_GameBoards.txt");
    buffer << in_p3.rdbuf();
    p3Sstrg = buffer.str();
    
    //Read the text file into the player 3 array
    for(int j = 0; j < TPOSTNS; j++)
    {
        pos2 = p3Sstrg.find(",", pos1);                     //Search for the "," (position 2 will be where the comma was found)
        pTrePos[j] = p3Sstrg.substr(pos1, (pos2-pos1));     //Make the substring
        pos1 = pos2 + 1;
    }
    
    //Begin the game
    //Loop until a player exceeds their native 74th position
    while(p1cPosn < 74 && p2cPosn < 74 && p3cPosn < 74)
    {
        cout << endl;
        cout << setw(25) << "PLAYER 1'S TURN:";
        cout << "\nPress the Enter key to draw a card! ";
        cin.get();

        //generate a random card
        card = (rand() % 11) + 1;
        cout << endl;

        //Determine the card value and apply the rules
        //Player 1 draws a "1"
        if(card == 1)
        {
            //Print the card's specific menu
            cout << "You drew a 1!" << endl;
            cout << "1. Start" << endl;
            cout << "2. Move 1 space forward" << endl;
            cout << "3. Skip turn" << endl;

            //Check for legal move
            do
            {
                if((pChoice > 3) || (pChoice == 1 && p1cPosn >= 9) || (pChoice == 2 && p1cPosn < 9) || (pChoice == 3))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);                
            }while((pChoice > 3) || (pChoice == 1 && p1cPosn >= 9) || (pChoice == 2 && p1cPosn < 9) || (pChoice == 3));

            //Execute the desired action
            switch(pChoice)
            {
                case 1: 
                    p1cPosn = 10;
                    cout << pOnePos[p1cPosn] << endl;   //Output modified game board
                    break;
                case 2:
                    p1cPosn += 1;
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 3:
                    break;
            }
        }

        //Player 1 draws a "2"
        else if(card == 2)
        {
            //Print the card's specific menu
            cout << "You drew a 2!" << endl;
            cout << "1. Start" << endl;
            cout << "2. Move 2 spaces forward" << endl;
            cout << "3. Skip turn" << endl;

            //Check for legal move
            do
            {
                if((pChoice > 3) || (pChoice == 1 && p1cPosn >= 9) || (pChoice == 1 && p1cPosn >= 9) || (pChoice == 3))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice); 
            }while((pChoice > 3) || (pChoice == 1 && p1cPosn >= 9) || (pChoice == 1 && p1cPosn >= 9) || (pChoice == 3));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn = 10;
                    cout << pOnePos[p1cPosn] << endl;   //Output modified game board
                    break;
                case 2:
                    p1cPosn += 2;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;   //Output modified game board
                    break;
                case 3:
                    break;
            }
        }

        //Player 1 draws a "3"
        else if(card == 3)
        {
            //Print the card's specific menu
            cout << "You drew a 3!" << endl;
            cout << "1. Move 3 spaces forward" << endl;
            cout << "2. Skip turn" << endl;

            //Check for legal move 
            do
            {
                if((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);                    
            } while((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn += 3;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    break;
            }
        }

        //Player 1 draws a "4"
        else if(card == 4)
        {
            //Print the card's specific menu
            cout << "You drew a 4!" << endl;
            cout << "1. Move 4 spaces backward" << endl;
            cout << "2. Skip turn" << endl;

            //Check for legal move
            do
            {
                if((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);
            } while((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn -= 4;                       

                    //Determine if Player 1 has moved before their safe zone (P1-0 - P1-8)
                    if(p1cPosn == 8)
                    {
                        p1cPosn = 68;
                    }
                    else if(p1cPosn == 7)
                    {
                        p1cPosn = 67;
                    }
                    else if(p1cPosn == 6)
                    {
                        p1cPosn = 66;
                    }
                    else if(p1cPosn == 5)
                    {
                        p1cPosn = 65;
                    }
                    else if(p1cPosn == 4)
                    {
                        p1cPosn = 64;
                    }
                    else if(p1cPosn == 3)
                    {
                        p1cPosn = 63;
                    }
                    else if(p1cPosn == 2)
                    {
                        p1cPosn = 62;
                    }
                    else if(p1cPosn == 1)
                    {
                        p1cPosn = 61;
                    }
                    else if(p1cPosn == 0)
                    {
                        p1cPosn = 60;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    break;
            }
        }

        //Player 1 draws a "5"
        else if(card == 5)
        {
            //Print the card's specific menu
            cout << "You drew a 5!" << endl;
            cout << "1. Move 5 spaces forward" << endl;
            cout << "2. Skip turn" << endl;

            //Check for legal move
            do
            {
                if((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);  
            } while((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn += 5;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    break;
            }
        }

        //Player 1 draws a "7"
        else if(card == 6)
        {
            //Print the card's specific menu
            cout << "You drew a 7!" << endl;
            cout << "1. Move 7 spaces forward" << endl;
            cout << "2. Move Player Two 7 spaces backward" << endl;
            cout << "3. Move Player Three 7 spaces backward" << endl;
            cout << "4. Skip turn" << endl;

            //Check for legal move
            do
            {
                if((pChoice > 4) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p2cPosn < 9) ||
                  (pChoice == 3 && p3cPosn < 9) || (pChoice == 4 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);
            } while((pChoice > 4) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p2cPosn < 9) ||
                   (pChoice == 3 && p3cPosn < 9) || (pChoice == 4 && p1cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn += 7;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    p2cPosn -= 7;                       

                    //Determine if Player 2 has moved before their safe zone (P1-0 - P1-8)
                    if(p2cPosn == 8)
                    {
                        p2cPosn = 68;
                    }
                    else if(p2cPosn == 7)
                    {
                        p2cPosn = 67;
                    }
                    else if(p2cPosn == 6)
                    {
                        p2cPosn = 66;
                    }
                    else if(p2cPosn == 5)
                    {
                        p2cPosn = 65;
                    }
                    else if(p2cPosn == 4)
                    {
                        p2cPosn = 64;
                    }
                    else if(p2cPosn == 3)
                    {
                        p2cPosn = 63;
                    }
                    else if(p2cPosn == 2)
                    {
                        p2cPosn = 62;
                    }
                    else if(p2cPosn == 1)
                    {
                        p2cPosn = 61;
                    }
                    else if(p2cPosn == 0)
                    {
                        p2cPosn = 60;
                    }
                    cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                    break;
                case 3:
                    p3cPosn -= 7;                       

                    //Determine if Player 2 has moved before their safe zone (P1-0 - P1-8)
                    if(p3cPosn == 8)
                    {
                        p3cPosn = 68;
                    }
                    else if(p3cPosn == 7)
                    {
                        p3cPosn = 67;
                    }
                    else if(p3cPosn == 6)
                    {
                        p3cPosn = 66;
                    }
                    else if(p3cPosn == 5)
                    {
                        p3cPosn = 65;
                    }
                    else if(p3cPosn == 4)
                    {
                        p3cPosn = 64;
                    }
                    else if(p3cPosn == 3)
                    {
                        p3cPosn = 63;
                    }
                    else if(p3cPosn == 2)
                    {
                        p3cPosn = 62;
                    }
                    else if(p3cPosn == 1)
                    {
                        p3cPosn = 61;
                    }
                    else if(p3cPosn == 0)
                    {
                        p3cPosn = 60;
                    }
                    cout << pTrePos[p3cPosn] << endl;    //Output modified game board
                    break;
                case 4:
                    break;
            }
        }

        //Player 1 draws an "8"
        else if(card == 7)
        {
            //Print the card's specific menu
            cout << "You drew an 8!" << endl;
            cout << "1. Move 8 spaces forward" << endl;
            cout << "2. Skip turn" << endl;

            //Check for legal move
            do
            {
                if((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);                
            } while((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn += 8;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    break;
            }
        }

        //Player 1 draws a "10"
        else if(card == 8)
        {
            //Print the card's specific menu
            cout << "You drew a 10!" << endl;
            cout << "1. Move 10 spaces forward" << endl;
            cout << "2. Move 1 space backward" << endl;
            cout << "3. Skip turn" << endl;

            //Check for legal move
            do
            {
                if((pChoice > 3) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn < 9) || (pChoice == 3 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);                   
            }while((pChoice > 3) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn < 9) || (pChoice == 3 && p1cPosn >= 9));           

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn += 10;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    p1cPosn -= 1;                        

                    //Determine if Player 1 has moved before their safe zone (P1-0 - P1-8)
                    if(p1cPosn == 8)
                    {
                        p1cPosn = 68;
                    }
                    else if(p1cPosn == 7)
                    {
                        p1cPosn = 67;
                    }
                    else if(p1cPosn == 6)
                    {
                        p1cPosn = 66;
                    }
                    else if(p1cPosn == 5)
                    {
                        p1cPosn = 65;
                    }
                    else if(p1cPosn == 4)
                    {
                        p1cPosn = 64;
                    }
                    else if(p1cPosn == 3)
                    {
                        p1cPosn = 63;
                    }
                    else if(p1cPosn == 2)
                    {
                        p1cPosn = 62;
                    }
                    else if(p1cPosn == 1)
                    {
                        p1cPosn = 61;
                    }
                    else if(p1cPosn == 0)
                    {
                        p1cPosn = 60;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 3:
                    break;
            }
        }

        //Player 1 draws an "11"
        else if(card == 9)
        {
            //Print the card's specific menu
            cout << "You drew an 11!" << endl;
            cout << "1. Move 11 spaces forward" << endl;
            cout << "2. Switch places with Player Two's pawn" << endl;
            cout << "3. Switch places with Player Three's pawn" << endl;
            cout << "4. Skip turn" << endl;

            //Check for legal move 
            do
            {
                if((pChoice > 4) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn < 9) ||
                  (pChoice == 2 && p2cPosn < 9) || (pChoice == 3 && p1cPosn < 9) || (pChoice == 3 && p3cPosn < 9) ||
                  (pChoice == 4 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);
            } while((pChoice > 4) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn < 9) ||
                   (pChoice == 2 && p2cPosn < 9) || (pChoice == 3 && p1cPosn < 9) || (pChoice == 3 && p3cPosn < 9) ||
                   (pChoice == 4 && p1cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn += 11;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    if(p1cPosn >= 15 && p2cPosn >= 15)
                    {
                        temp = p1cPosn;
                        p1cPosn = p2cPosn - 15;
                        p2cPosn = temp + 15;
                    }
                    else if(p1cPosn >= 15 && p2cPosn <= 15)
                    {
                        temp = p1cPosn;
                        p1cPosn = 60 + p2cPosn - 15;
                        p2cPosn = 15 - (60 - temp);
                    }
                    else if(p1cPosn <= 15 && p2cPosn <= 15)
                    {
                        temp = p1cPosn;
                        p1cPosn = 60 + p2cPosn - 15;
                        p2cPosn = temp + 15;
                    }
                    else if(p1cPosn <= 15 && p2cPosn >= 15)
                    {
                        p1cPosn = p2cPosn - 15;
                        p2cPosn = p2cPosn - (p1cPosn - 10);
                    }                       

                    //Determine if Player 1 has moved before their safe zone (P1-0 - P1-8)
                    if(p1cPosn == 8)
                    {
                        p1cPosn = 68;
                    }
                    else if(p1cPosn == 7)
                    {
                        p1cPosn = 67;
                    }
                    else if(p1cPosn == 6)
                    {
                        p1cPosn = 66;
                    }
                    else if(p1cPosn == 5)
                    {
                        p1cPosn = 65;
                    }
                    else if(p1cPosn == 4)
                    {
                        p1cPosn = 64;
                    }
                    else if(p1cPosn == 3)
                    {
                        p1cPosn = 63;
                    }
                    else if(p1cPosn == 2)
                    {
                        p1cPosn = 62;
                    }
                    else if(p1cPosn == 1)
                    {
                        p1cPosn = 61;
                    }
                    else if(p1cPosn == 0)
                    {
                        p1cPosn = 60;
                    }

                    //Determine if Player 2 has moved before their safe zone (P2-0 - P2-8)
                    if(p2cPosn == 8)
                    {
                        p2cPosn = 68;
                    }
                    else if(p2cPosn == 7)
                    {
                        p2cPosn = 67;
                    }
                    else if(p2cPosn == 6)
                    {
                        p2cPosn = 66;
                    }
                    else if(p2cPosn == 5)
                    {
                        p2cPosn = 65;
                    }
                    else if(p2cPosn == 4)
                    {
                        p2cPosn = 64;
                    }
                    else if(p2cPosn == 3)
                    {
                        p2cPosn = 63;
                    }
                    else if(p2cPosn == 2)
                    {
                        p2cPosn = 62;
                    }
                    else if(p2cPosn == 1)
                    {
                        p2cPosn = 61;
                    }
                    else if(p2cPosn == 0)
                    {
                        p2cPosn = 60;
                    }
                    cout << pOnePos[p1cPosn] << endl;
                    cout << endl;
                    cout << pTwoPos[p2cPosn] << endl;
                    break;
                case 3:
                    if(p1cPosn >= 15 && p3cPosn >= 15)
                    {
                        temp = p1cPosn;
                        p1cPosn = p3cPosn - 15;
                        p3cPosn = temp + 15;
                    }
                    else if(p1cPosn >= 15 && p3cPosn <= 15)
                    {
                        temp = p1cPosn;
                        p1cPosn = 60 + p3cPosn - 15;
                        p3cPosn = 15 - (60 - temp);
                    }
                    else if(p1cPosn <= 15 && p3cPosn <= 15)
                    {
                        temp = p1cPosn;
                        p1cPosn = 60 + p3cPosn - 15;
                        p3cPosn = temp + 15;
                    }
                    else if(p1cPosn <= 15 && p3cPosn >= 15)
                    {
                        p1cPosn = p3cPosn - 15;
                        p3cPosn = p3cPosn - (p1cPosn - 10);
                    }                       

                    //Determine if Player 1 has moved before their safe zone
                    if(p1cPosn == 8)
                    {
                        p1cPosn = 68;
                    }
                    else if(p1cPosn == 7)
                    {
                        p1cPosn = 67;
                    }
                    else if(p1cPosn == 6)
                    {
                        p1cPosn = 66;
                    }
                    else if(p1cPosn == 5)
                    {
                        p1cPosn = 65;
                    }
                    else if(p1cPosn == 4)
                    {
                        p1cPosn = 64;
                    }
                    else if(p1cPosn == 3)
                    {
                        p1cPosn = 63;
                    }
                    else if(p1cPosn == 2)
                    {
                        p1cPosn = 62;
                    }
                    else if(p1cPosn == 1)
                    {
                        p1cPosn = 61;
                    }
                    else if(p1cPosn == 0)
                    {
                        p1cPosn = 60;
                    }

                    //Determine if Player 3 has moved before their safe zone
                    if(p3cPosn == 8)
                    {
                        p3cPosn = 68;
                    }
                    else if(p3cPosn == 7)
                    {
                        p3cPosn = 67;
                    }
                    else if(p3cPosn == 6)
                    {
                        p3cPosn = 66;
                    }
                    else if(p3cPosn == 5)
                    {
                        p3cPosn = 65;
                    }
                    else if(p3cPosn == 4)
                    {
                        p3cPosn = 64;
                    }
                    else if(p3cPosn == 3)
                    {
                        p3cPosn = 63;
                    }
                    else if(p3cPosn == 2)
                    {
                        p3cPosn = 62;
                    }
                    else if(p3cPosn == 1)
                    {
                        p3cPosn = 61;
                    }
                    else if(p3cPosn == 0)
                    {
                        p3cPosn = 60;
                    }
                    cout << pOnePos[p1cPosn] << endl;
                    cout << endl;
                    cout << pTrePos[p3cPosn] << endl;
                    break;
                case 4:
                    break;
            }
        }

        //Player 1 draws a "12"
        else if(card == 10)
        {
            //Print the card's specific menu
            cout << "You drew a 12!" << endl;
            cout << "1. Move 12 spaces forward" << endl;
            cout << "2. Skip turn" << endl;

            //Check for legal move 
            do
            {
                if((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);
            } while((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn += 12;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    break;
            }
        }      

        //Player 1 draws a "Sorry!" card
        else
        {
            //Print the card's specific menu
            cout << "You drew a \"Sorry!\" Card!" << endl;
            cout << "1. Move Player Two's pawn off the game board" << endl;
            cout << "2. Move Player Three's pawn off the game board" << endl;
            cout << "3. Skip turn" << endl;

            //Check for legal move 
            do
            {
                if((pChoice > 3) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p3cPosn < 9) ||
                  (pChoice == 3 && p2cPosn >= 9) || (pChoice == 3 && p3cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);
            } while((pChoice > 3) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p3cPosn < 9) ||
                   (pChoice == 3 && p2cPosn >= 9) || (pChoice == 3 && p3cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p2cPosn = 0;
                    cout << "\nPlayer 2 has been moved off the game board!" << endl;
                    cout << pTwoPos[0] << endl;
                    break;
                case 2:
                    p3cPosn = 0;
                    cout << "\nPlayer 3 has been moved off the game board!" << endl;
                    cout << pTrePos[0] << endl;
                    break;
                case 3:
                    break;
            }
        }

        //Determine whether Player 1 has won the game
        if(p1cPosn == 74)
        {
            cout << "\nPlayer 1 has won the game!" << endl;
            restart = true;
        }

        //Reset the player's choice
        pChoice = 0;
        
        //Begin Player 2's turn
        if(restart == false)
        {            
            cout << endl;
            cout << setw(25) << "PLAYER 2'S TURN:";
            cout << "\nPress the Enter key to draw a card! ";  
            cin.ignore();
            cin.get();

            //generate a random card
            card = (rand() % 11) + 1;
            cout << endl;

            //Determine the card value and apply the rules
            //Player 2 draws a "1"
            if(card == 1)
            {
                //Print the card's specific menu
                cout << "You drew a 1!" << endl;
                cout << "1. Start" << endl;
                cout << "2. Move 1 space forward" << endl;
                cout << "3. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 3) || (pChoice == 1 && p2cPosn >= 9) || (pChoice == 2 && p2cPosn < 9) || (pChoice == 3))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);                
                }while((pChoice > 3) || (pChoice == 1 && p2cPosn >= 9) || (pChoice == 2 && p2cPosn < 9) || (pChoice == 3));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1: 
                        p2cPosn = 10;
                        cout << pTwoPos[p2cPosn] << endl;   //Output modified game board
                        break;
                    case 2:
                        p2cPosn += 1;
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 3:
                        break;
                }
            }

            //Player 2 draws a "2"
            else if(card == 2)
            {
                //Print the card's specific menu
                cout << "You drew a 2!" << endl;
                cout << "1. Start" << endl;
                cout << "2. Move 2 spaces forward" << endl;
                cout << "3. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 3) || (pChoice == 1 && p2cPosn >= 9) || (pChoice == 1 && p2cPosn >= 9) || (pChoice == 3))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice); 
                }while((pChoice > 3) || (pChoice == 1 && p2cPosn >= 9) || (pChoice == 1 && p2cPosn >= 9) || (pChoice == 3));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p2cPosn = 10;
                        cout << pTwoPos[p2cPosn] << endl;   //Output modified game board
                        break;
                    case 2:
                        p2cPosn += 2;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;   //Output modified game board
                        break;
                    case 3:
                        break;
                }
            }

            //Player 2 draws a "3"
            else if(card == 3)
            {
                //Print the card's specific menu
                cout << "You drew a 3!" << endl;
                cout << "1. Move 3 spaces forward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move 
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);                    
                } while((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p2cPosn += 3;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }

            //Player 2 draws a "4"
            else if(card == 4)
            {
                //Print the card's specific menu
                cout << "You drew a 4!" << endl;
                cout << "1. Move 4 spaces backward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p2cPosn -= 4;                       

                        //Determine if Player 2 has moved before their safe zone (P1-0 - P1-8)
                        if(p2cPosn == 8)
                        {
                            p2cPosn = 68;
                        }
                        else if(p2cPosn == 7)
                        {
                            p2cPosn = 67;
                        }
                        else if(p2cPosn == 6)
                        {
                            p2cPosn = 66;
                        }
                        else if(p2cPosn == 5)
                        {
                            p2cPosn = 65;
                        }
                        else if(p2cPosn == 4)
                        {
                            p2cPosn = 64;
                        }
                        else if(p2cPosn == 3)
                        {
                            p2cPosn = 63;
                        }
                        else if(p2cPosn == 2)
                        {
                            p2cPosn = 62;
                        }
                        else if(p2cPosn == 1)
                        {
                            p2cPosn = 61;
                        }
                        else if(p2cPosn == 0)
                        {
                            p2cPosn = 60;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }

            //Player 2 draws a "5"
            else if(card == 5)
            {
                //Print the card's specific menu
                cout << "You drew a 5!" << endl;
                cout << "1. Move 5 spaces forward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);  
                } while((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p2cPosn += 5;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }

            //Player 2 draws a "7"
            else if(card == 6)
            {
                //Print the card's specific menu
                cout << "You drew a 7!" << endl;
                cout << "1. Move 7 spaces forward" << endl;
                cout << "2. Move Player One 7 spaces backward" << endl;
                cout << "3. Move Player Three 7 spaces backward" << endl;
                cout << "4. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 4) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p1cPosn < 9) ||
                      (pChoice == 3 && p3cPosn < 9) || (pChoice == 4 && p2cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 4) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p1cPosn < 9) ||
                       (pChoice == 3 && p3cPosn < 9) || (pChoice == 4 && p2cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p2cPosn += 7;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        p1cPosn -= 7;                       

                        //Determine if Player 1 has moved before their safe zone (P1-0 - P1-8)
                        if(p1cPosn == 8)
                        {
                            p1cPosn = 68;
                        }
                        else if(p1cPosn == 7)
                        {
                            p1cPosn = 67;
                        }
                        else if(p1cPosn == 6)
                        {
                            p1cPosn = 66;
                        }
                        else if(p1cPosn == 5)
                        {
                            p1cPosn = 65;
                        }
                        else if(p1cPosn == 4)
                        {
                            p1cPosn = 64;
                        }
                        else if(p1cPosn == 3)
                        {
                            p1cPosn = 63;
                        }
                        else if(p1cPosn == 2)
                        {
                            p1cPosn = 62;
                        }
                        else if(p1cPosn == 1)
                        {
                            p1cPosn = 61;
                        }
                        else if(p1cPosn == 0)
                        {
                            p1cPosn = 60;
                        }
                        cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                        break;
                    case 3:
                        p3cPosn -= 7;                       

                        //Determine if Player 3 has moved before their safe zone
                        if(p3cPosn == 8)
                        {
                            p3cPosn = 68;
                        }
                        else if(p3cPosn == 7)
                        {
                            p3cPosn = 67;
                        }
                        else if(p3cPosn == 6)
                        {
                            p3cPosn = 66;
                        }
                        else if(p3cPosn == 5)
                        {
                            p3cPosn = 65;
                        }
                        else if(p3cPosn == 4)
                        {
                            p3cPosn = 64;
                        }
                        else if(p3cPosn == 3)
                        {
                            p3cPosn = 63;
                        }
                        else if(p3cPosn == 2)
                        {
                            p3cPosn = 62;
                        }
                        else if(p3cPosn == 1)
                        {
                            p3cPosn = 61;
                        }
                        else if(p3cPosn == 0)
                        {
                            p3cPosn = 60;
                        }
                        cout << pTrePos[p3cPosn] << endl;    //Output modified game board
                        break;
                    case 4:
                        break;
                }
            }

            //Player 2 draws an "8"
            else if(card == 7)
            {
                //Print the card's specific menu
                cout << "You drew an 8!" << endl;
                cout << "1. Move 8 spaces forward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);                
                } while((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p2cPosn += 8;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }

            //Player 2 draws a "10"
            else if(card == 8)
            {
                //Print the card's specific menu
                cout << "You drew a 10!" << endl;
                cout << "1. Move 10 spaces forward" << endl;
                cout << "2. Move 1 space backward" << endl;
                cout << "3. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 3) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn < 9) || (pChoice == 3 && p2cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);                   
                }while((pChoice > 3) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn < 9) || (pChoice == 3 && p2cPosn >= 9));           

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p2cPosn += 10;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        p2cPosn -= 1;                        

                        //Determine if Player 2 has moved before their safe zone (P1-0 - P1-8)
                        if(p2cPosn == 8)
                        {
                            p2cPosn = 68;
                        }
                        else if(p2cPosn == 7)
                        {
                            p2cPosn = 67;
                        }
                        else if(p2cPosn == 6)
                        {
                            p2cPosn = 66;
                        }
                        else if(p2cPosn == 5)
                        {
                            p2cPosn = 65;
                        }
                        else if(p2cPosn == 4)
                        {
                            p2cPosn = 64;
                        }
                        else if(p2cPosn == 3)
                        {
                            p2cPosn = 63;
                        }
                        else if(p2cPosn == 2)
                        {
                            p2cPosn = 62;
                        }
                        else if(p2cPosn == 1)
                        {
                            p2cPosn = 61;
                        }
                        else if(p2cPosn == 0)
                        {
                            p2cPosn = 60;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 3:
                        break;
                }
            }

            //Player 2 draws an "11"
            else if(card == 9)
            {
                //Print the card's specific menu
                cout << "You drew an 11!" << endl;
                cout << "1. Move 11 spaces forward" << endl;
                cout << "2. Switch places with Player One's pawn" << endl;
                cout << "3. Switch places with Player Three's pawn" << endl;
                cout << "4. Skip turn" << endl;

                //Check for legal move 
                do
                {
                    if((pChoice > 4) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn < 9) ||
                      (pChoice == 2 && p1cPosn < 9) || (pChoice == 3 && p2cPosn < 9) || (pChoice == 3 && p3cPosn < 9) ||
                      (pChoice == 4 && p1cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 4) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn < 9) ||
                       (pChoice == 2 && p1cPosn < 9) || (pChoice == 3 && p2cPosn < 9) || (pChoice == 3 && p3cPosn < 9) ||
                       (pChoice == 4 && p1cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p2cPosn += 11;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        if(p2cPosn >= 15 && p1cPosn >= 15)
                        {
                            temp = p2cPosn;
                            p2cPosn = p1cPosn - 15;
                            p1cPosn = temp + 15;
                        }
                        else if(p2cPosn >= 15 && p1cPosn <= 15)
                        {
                            temp = p2cPosn;
                            p2cPosn = 60 + p1cPosn - 15;
                            p1cPosn = 15 - (60 - temp);
                        }
                        else if(p2cPosn <= 15 && p1cPosn <= 15)
                        {
                            temp = p2cPosn;
                            p2cPosn = 60 + p1cPosn - 15;
                            p1cPosn = temp + 15;
                        }
                        else if(p2cPosn <= 15 && p1cPosn >= 15)
                        {
                            p2cPosn = p1cPosn - 15;
                            p1cPosn = p1cPosn - (p2cPosn - 10);
                        }                       

                        //Determine if Player 2 has moved before their safe zone
                        if(p2cPosn == 8)
                        {
                            p2cPosn = 68;
                        }
                        else if(p2cPosn == 7)
                        {
                            p2cPosn = 67;
                        }
                        else if(p2cPosn == 6)
                        {
                            p2cPosn = 66;
                        }
                        else if(p2cPosn == 5)
                        {
                            p2cPosn = 65;
                        }
                        else if(p2cPosn == 4)
                        {
                            p2cPosn = 64;
                        }
                        else if(p2cPosn == 3)
                        {
                            p2cPosn = 63;
                        }
                        else if(p2cPosn == 2)
                        {
                            p2cPosn = 62;
                        }
                        else if(p2cPosn == 1)
                        {
                            p2cPosn = 61;
                        }
                        else if(p2cPosn == 0)
                        {
                            p2cPosn = 60;
                        }            

                        //Determine if Player 1 has moved before their safe zone (P1-0 - P1-8)
                        if(p1cPosn == 8)
                        {
                            p1cPosn = 68;
                        }
                        else if(p1cPosn == 7)
                        {
                            p1cPosn = 67;
                        }
                        else if(p1cPosn == 6)
                        {
                            p1cPosn = 66;
                        }
                        else if(p1cPosn == 5)
                        {
                            p1cPosn = 65;
                        }
                        else if(p1cPosn == 4)
                        {
                            p1cPosn = 64;
                        }
                        else if(p1cPosn == 3)
                        {
                            p1cPosn = 63;
                        }
                        else if(p1cPosn == 2)
                        {
                            p1cPosn = 62;
                        }
                        else if(p1cPosn == 1)
                        {
                            p1cPosn = 61;
                        }
                        else if(p1cPosn == 0)
                        {
                            p1cPosn = 60;
                        }
                        cout << pTwoPos[p2cPosn] << endl;
                        cout << endl;
                        cout << pOnePos[p1cPosn] << endl; 
                        break;
                    case 3:
                        if(p2cPosn >= 15 && p3cPosn >= 15)
                        {
                            temp = p2cPosn;
                            p2cPosn = p3cPosn - 15;
                            p3cPosn = temp + 15;
                        }
                        else if(p2cPosn >= 15 && p3cPosn <= 15)
                        {
                            temp = p2cPosn;
                            p2cPosn = 60 + p3cPosn - 15;
                            p3cPosn = 15 - (60 - temp);
                        }
                        else if(p2cPosn <= 15 && p3cPosn <= 15)
                        {
                            temp = p2cPosn;
                            p2cPosn = 60 + p3cPosn - 15;
                            p3cPosn = temp + 15;
                        }
                        else if(p2cPosn <= 15 && p3cPosn >= 15)
                        {
                            p2cPosn = p3cPosn - 15;
                            p3cPosn = p3cPosn - (p2cPosn - 10);
                        }                       

                        //Determine if Player 2 has moved before their safe zone
                        if(p2cPosn == 8)
                        {
                            p2cPosn = 68;
                        }
                        else if(p2cPosn == 7)
                        {
                            p2cPosn = 67;
                        }
                        else if(p2cPosn == 6)
                        {
                            p2cPosn = 66;
                        }
                        else if(p2cPosn == 5)
                        {
                            p2cPosn = 65;
                        }
                        else if(p2cPosn == 4)
                        {
                            p2cPosn = 64;
                        }
                        else if(p2cPosn == 3)
                        {
                            p2cPosn = 63;
                        }
                        else if(p2cPosn == 2)
                        {
                            p2cPosn = 62;
                        }
                        else if(p2cPosn == 1)
                        {
                            p2cPosn = 61;
                        }
                        else if(p2cPosn == 0)
                        {
                            p2cPosn = 60;
                        }

                        //Determine if Player 3 has moved before their safe zone
                        if(p3cPosn == 8)
                        {
                            p3cPosn = 68;
                        }
                        else if(p3cPosn == 7)
                        {
                            p3cPosn = 67;
                        }
                        else if(p3cPosn == 6)
                        {
                            p3cPosn = 66;
                        }
                        else if(p3cPosn == 5)
                        {
                            p3cPosn = 65;
                        }
                        else if(p3cPosn == 4)
                        {
                            p3cPosn = 64;
                        }
                        else if(p3cPosn == 3)
                        {
                            p3cPosn = 63;
                        }
                        else if(p3cPosn == 2)
                        {
                            p3cPosn = 62;
                        }
                        else if(p3cPosn == 1)
                        {
                            p3cPosn = 61;
                        }
                        else if(p3cPosn == 0)
                        {
                            p3cPosn = 60;
                        }
                        cout << pTwoPos[p2cPosn] << endl;
                        cout << endl;
                        cout << pTrePos[p3cPosn] << endl;
                        break;
                    case 4:
                        break;
                }
            }

            //Player 2 draws a "12"
            else if(card == 10)
            {
                //Print the card's specific menu
                cout << "You drew a 12!" << endl;
                cout << "1. Move 12 spaces forward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move 
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p2cPosn += 12;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }      

            //Player 2 draws a "Sorry!" card
            else
            {
                //Print the card's specific menu
                cout << "You drew a \"Sorry!\" Card!" << endl;
                cout << "1. Move Player One's pawn off the game board" << endl;
                cout << "2. Move Player Three's pawn off the game board" << endl;
                cout << "3. Skip turn" << endl;

                //Check for legal move 
                do
                {
                    if((pChoice > 3) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p3cPosn < 9) ||
                      (pChoice == 3 && p1cPosn >= 9) || (pChoice == 3 && p3cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 3) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p3cPosn < 9) ||
                       (pChoice == 3 && p1cPosn >= 9) || (pChoice == 3 && p3cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p1cPosn = 0;
                        cout << "\nPlayer 1 has been moved off the game board!" << endl;
                        cout << pOnePos[0] << endl;
                        break;
                    case 2:
                        p3cPosn = 0;
                        cout << "\nPlayer 3 has been moved off the game board!" << endl;
                        cout << pTrePos[0] << endl;
                        break;
                    case 3:
                        break;
                }
            }

            //Determine whether player 2 has won the game
            if(p2cPosn >= 74)
            {
                cout << "\nPlayer 2 has won the game!" << endl;
                restart = true;
            }
        }

        //Reset the player's choice
        pChoice = 0;       
        
        //Begin Player 3's turn
        if(restart == false)
        {            
            cout << endl;
            cout << setw(25) << "PLAYER 3'S TURN:";
            cout << "\nPress the Enter key to draw a card! ";  
            cin.ignore();
            cin.get();

            //generate a random card
            card = (rand() % 11) + 1;
            cout << endl;

            //Determine the card value and apply the rules
            //Player 3 draws a "1"
            if(card == 1)
            {
                //Print the card's specific menu
                cout << "You drew a 1!" << endl;
                cout << "1. Start" << endl;
                cout << "2. Move 1 space forward" << endl;
                cout << "3. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 3) || (pChoice == 1 && p3cPosn >= 9) || (pChoice == 2 && p3cPosn < 9) || (pChoice == 3))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);                
                }while((pChoice > 3) || (pChoice == 1 && p3cPosn >= 9) || (pChoice == 2 && p3cPosn < 9) || (pChoice == 3));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1: 
                        p3cPosn = 10;
                        cout << pTrePos[p3cPosn] << endl;   //Output modified game board
                        break;
                    case 2:
                        p3cPosn += 1;
                        cout << pTrePos[p3cPosn] << endl;    //Output modified game board
                        break;
                    case 3:
                        break;
                }
            }

            //Player 3 draws a "2"
            else if(card == 2)
            {
                //Print the card's specific menu
                cout << "You drew a 2!" << endl;
                cout << "1. Start" << endl;
                cout << "2. Move 2 spaces forward" << endl;
                cout << "3. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 3) || (pChoice == 1 && p3cPosn >= 9) || (pChoice == 1 && p3cPosn >= 9) || (pChoice == 3))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice); 
                }while((pChoice > 3) || (pChoice == 1 && p3cPosn >= 9) || (pChoice == 1 && p3cPosn >= 9) || (pChoice == 3));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p3cPosn = 10;
                        cout << pTrePos[p3cPosn] << endl;   //Output modified game board
                        break;
                    case 2:
                        p3cPosn += 2;
                        if(p3cPosn > 74)
                        {
                            p3cPosn = 74;
                        }
                        cout << pTrePos[p3cPosn] << endl;   //Output modified game board
                        break;
                    case 3:
                        break;
                }
            }

            //Player 3 draws a "3"
            else if(card == 3)
            {
                //Print the card's specific menu
                cout << "You drew a 3!" << endl;
                cout << "1. Move 3 spaces forward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move 
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p3cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);                    
                } while((pChoice > 2) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p3cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p3cPosn += 3;
                        if(p3cPosn > 74)
                        {
                            p3cPosn = 74;
                        }
                        cout << pTrePos[p3cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }

            //Player 3 draws a "4"
            else if(card == 4)
            {
                //Print the card's specific menu
                cout << "You drew a 4!" << endl;
                cout << "1. Move 4 spaces backward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p3cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 2) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p3cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p3cPosn -= 4;                       

                        //Determine if Player 2 has moved before their safe zone
                        if(p3cPosn == 8)
                        {
                            p3cPosn = 68;
                        }
                        else if(p3cPosn == 7)
                        {
                            p3cPosn = 67;
                        }
                        else if(p3cPosn == 6)
                        {
                            p3cPosn = 66;
                        }
                        else if(p3cPosn == 5)
                        {
                            p3cPosn = 65;
                        }
                        else if(p3cPosn == 4)
                        {
                            p3cPosn = 64;
                        }
                        else if(p3cPosn == 3)
                        {
                            p3cPosn = 63;
                        }
                        else if(p3cPosn == 2)
                        {
                            p3cPosn = 62;
                        }
                        else if(p3cPosn == 1)
                        {
                            p3cPosn = 61;
                        }
                        else if(p3cPosn == 0)
                        {
                            p3cPosn = 60;
                        }
                        cout << pTrePos[p3cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }

            //Player 3 draws a "5"
            else if(card == 5)
            {
                //Print the card's specific menu
                cout << "You drew a 5!" << endl;
                cout << "1. Move 5 spaces forward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p3cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);  
                } while((pChoice > 2) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p3cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p3cPosn += 5;
                        if(p3cPosn > 74)
                        {
                            p3cPosn = 74;
                        }
                        cout << pTrePos[p3cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }

            //Player 3 draws a "7"
            else if(card == 6)
            {
                //Print the card's specific menu
                cout << "You drew a 7!" << endl;
                cout << "1. Move 7 spaces forward" << endl;
                cout << "2. Move Player One 7 spaces backward" << endl;
                cout << "3. Move Player Two 7 spaces backward" << endl;
                cout << "4. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 4) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p1cPosn < 9) ||
                      (pChoice == 3 && p2cPosn < 9) || (pChoice == 4 && p3cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 4) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p1cPosn < 9) ||
                       (pChoice == 3 && p2cPosn < 9) || (pChoice == 4 && p3cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p3cPosn += 7;
                        if(p3cPosn > 74)
                        {
                            p3cPosn = 74;
                        }
                        cout << pTrePos[p3cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        p1cPosn -= 7;                       

                        //Determine if Player 1 has moved before their safe zone (P1-0 - P1-8)
                        if(p1cPosn == 8)
                        {
                            p1cPosn = 68;
                        }
                        else if(p1cPosn == 7)
                        {
                            p1cPosn = 67;
                        }
                        else if(p1cPosn == 6)
                        {
                            p1cPosn = 66;
                        }
                        else if(p1cPosn == 5)
                        {
                            p1cPosn = 65;
                        }
                        else if(p1cPosn == 4)
                        {
                            p1cPosn = 64;
                        }
                        else if(p1cPosn == 3)
                        {
                            p1cPosn = 63;
                        }
                        else if(p1cPosn == 2)
                        {
                            p1cPosn = 62;
                        }
                        else if(p1cPosn == 1)
                        {
                            p1cPosn = 61;
                        }
                        else if(p1cPosn == 0)
                        {
                            p1cPosn = 60;
                        }
                        cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                        break;
                    case 3:
                        p2cPosn -= 7;                       

                        //Determine if Player 3 has moved before their safe zone
                        if(p2cPosn == 8)
                        {
                            p2cPosn = 68;
                        }
                        else if(p2cPosn == 7)
                        {
                            p2cPosn = 67;
                        }
                        else if(p2cPosn == 6)
                        {
                            p2cPosn = 66;
                        }
                        else if(p2cPosn == 5)
                        {
                            p2cPosn = 65;
                        }
                        else if(p2cPosn == 4)
                        {
                            p2cPosn = 64;
                        }
                        else if(p2cPosn == 3)
                        {
                            p2cPosn = 63;
                        }
                        else if(p2cPosn == 2)
                        {
                            p2cPosn = 62;
                        }
                        else if(p2cPosn == 1)
                        {
                            p2cPosn = 61;
                        }
                        else if(p2cPosn == 0)
                        {
                            p2cPosn = 60;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 4:
                        break;
                }
            }

            //Player 3 draws an "8"
            else if(card == 7)
            {
                //Print the card's specific menu
                cout << "You drew an 8!" << endl;
                cout << "1. Move 8 spaces forward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p3cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);                
                } while((pChoice > 2) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p3cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p3cPosn += 8;
                        if(p3cPosn > 74)
                        {
                            p3cPosn = 74;
                        }
                        cout << pTrePos[p3cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }

            //Player 3 draws a "10"
            else if(card == 8)
            {
                //Print the card's specific menu
                cout << "You drew a 10!" << endl;
                cout << "1. Move 10 spaces forward" << endl;
                cout << "2. Move 1 space backward" << endl;
                cout << "3. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 3) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p3cPosn < 9) || (pChoice == 3 && p3cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);                   
                }while((pChoice > 3) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p3cPosn < 9) || (pChoice == 3 && p3cPosn >= 9));           

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p3cPosn += 10;
                        if(p3cPosn > 74)
                        {
                            p3cPosn = 74;
                        }
                        cout << pTrePos[p3cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        p3cPosn -= 1;                        

                        //Determine if Player 2 has moved before their safe zone (P1-0 - P1-8)
                        if(p3cPosn == 8)
                        {
                            p3cPosn = 68;
                        }
                        else if(p3cPosn == 7)
                        {
                            p3cPosn = 67;
                        }
                        else if(p3cPosn == 6)
                        {
                            p3cPosn = 66;
                        }
                        else if(p3cPosn == 5)
                        {
                            p3cPosn = 65;
                        }
                        else if(p3cPosn == 4)
                        {
                            p3cPosn = 64;
                        }
                        else if(p3cPosn == 3)
                        {
                            p3cPosn = 63;
                        }
                        else if(p3cPosn == 2)
                        {
                            p3cPosn = 62;
                        }
                        else if(p3cPosn == 1)
                        {
                            p3cPosn = 61;
                        }
                        else if(p3cPosn == 0)
                        {
                            p3cPosn = 60;
                        }
                        cout << pTrePos[p3cPosn] << endl;    //Output modified game board
                        break;
                    case 3:
                        break;
                }
            }

            //Player 3 draws an "11"
            else if(card == 9)
            {
                //Print the card's specific menu
                cout << "You drew an 11!" << endl;
                cout << "1. Move 11 spaces forward" << endl;
                cout << "2. Switch places with Player One's pawn" << endl;
                cout << "3. Switch places with Player Two's pawn" << endl;
                cout << "4. Skip turn" << endl;

                //Check for legal move 
                do
                {
                    if((pChoice > 4) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p3cPosn < 9) ||
                      (pChoice == 2 && p1cPosn < 9) || (pChoice == 3 && p2cPosn < 9) || (pChoice == 3 && p2cPosn < 9) ||
                      (pChoice == 4 && p1cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 4) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p3cPosn < 9) ||
                       (pChoice == 2 && p1cPosn < 9) || (pChoice == 3 && p2cPosn < 9) || (pChoice == 3 && p2cPosn < 9) ||
                       (pChoice == 4 && p1cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p3cPosn += 11;
                        if(p3cPosn > 74)
                        {
                            p3cPosn = 74;
                        }
                        cout << pTrePos[p3cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        if(p3cPosn >= 15 && p1cPosn >= 15)
                        {
                            temp = p3cPosn;
                            p3cPosn = p1cPosn - 15;
                            p1cPosn = temp + 15;
                        }
                        else if(p3cPosn >= 15 && p1cPosn <= 15)
                        {
                            temp = p3cPosn;
                            p3cPosn = 60 + p1cPosn - 15;
                            p1cPosn = 15 - (60 - temp);
                        }
                        else if(p3cPosn <= 15 && p1cPosn <= 15)
                        {
                            temp = p3cPosn;
                            p3cPosn = 60 + p1cPosn - 15;
                            p1cPosn = temp + 15;
                        }
                        else if(p3cPosn <= 15 && p1cPosn >= 15)
                        {
                            p3cPosn = p1cPosn - 15;
                            p1cPosn = p1cPosn - (p3cPosn - 10);
                        }                       

                        //Determine if Player 3 has moved before their safe zone
                        if(p3cPosn == 8)
                        {
                            p3cPosn = 68;
                        }
                        else if(p3cPosn == 7)
                        {
                            p3cPosn = 67;
                        }
                        else if(p3cPosn == 6)
                        {
                            p3cPosn = 66;
                        }
                        else if(p3cPosn == 5)
                        {
                            p3cPosn = 65;
                        }
                        else if(p3cPosn == 4)
                        {
                            p3cPosn = 64;
                        }
                        else if(p3cPosn == 3)
                        {
                            p3cPosn = 63;
                        }
                        else if(p3cPosn == 2)
                        {
                            p3cPosn = 62;
                        }
                        else if(p3cPosn == 1)
                        {
                            p3cPosn = 61;
                        }
                        else if(p3cPosn == 0)
                        {
                            p3cPosn = 60;
                        }            

                        //Determine if Player 1 has moved before their safe zone
                        if(p1cPosn == 8)
                        {
                            p1cPosn = 68;
                        }
                        else if(p1cPosn == 7)
                        {
                            p1cPosn = 67;
                        }
                        else if(p1cPosn == 6)
                        {
                            p1cPosn = 66;
                        }
                        else if(p1cPosn == 5)
                        {
                            p1cPosn = 65;
                        }
                        else if(p1cPosn == 4)
                        {
                            p1cPosn = 64;
                        }
                        else if(p1cPosn == 3)
                        {
                            p1cPosn = 63;
                        }
                        else if(p1cPosn == 2)
                        {
                            p1cPosn = 62;
                        }
                        else if(p1cPosn == 1)
                        {
                            p1cPosn = 61;
                        }
                        else if(p1cPosn == 0)
                        {
                            p1cPosn = 60;
                        }
                        cout << pTrePos[p3cPosn] << endl;
                        cout << endl;
                        cout << pOnePos[p1cPosn] << endl; 
                        break;
                    case 3:
                        if(p3cPosn >= 15 && p2cPosn >= 15)
                        {
                            temp = p3cPosn;
                            p3cPosn = p2cPosn - 15;
                            p2cPosn = temp + 15;
                        }
                        else if(p3cPosn >= 15 && p2cPosn <= 15)
                        {
                            temp = p3cPosn;
                            p3cPosn = 60 + p2cPosn - 15;
                            p2cPosn = 15 - (60 - temp);
                        }
                        else if(p3cPosn <= 15 && p2cPosn <= 15)
                        {
                            temp = p3cPosn;
                            p3cPosn = 60 + p2cPosn - 15;
                            p2cPosn = temp + 15;
                        }
                        else if(p3cPosn <= 15 && p2cPosn >= 15)
                        {
                            p3cPosn = p2cPosn - 15;
                            p2cPosn = p2cPosn - (p3cPosn - 10);
                        }                       

                        //Determine if Player 3 has moved before their safe zone
                        if(p3cPosn == 8)
                        {
                            p3cPosn = 68;
                        }
                        else if(p3cPosn == 7)
                        {
                            p3cPosn = 67;
                        }
                        else if(p3cPosn == 6)
                        {
                            p3cPosn = 66;
                        }
                        else if(p3cPosn == 5)
                        {
                            p3cPosn = 65;
                        }
                        else if(p3cPosn == 4)
                        {
                            p3cPosn = 64;
                        }
                        else if(p3cPosn == 3)
                        {
                            p3cPosn = 63;
                        }
                        else if(p3cPosn == 2)
                        {
                            p3cPosn = 62;
                        }
                        else if(p3cPosn == 1)
                        {
                            p3cPosn = 61;
                        }
                        else if(p3cPosn == 0)
                        {
                            p3cPosn = 60;
                        }

                        //Determine if Player 2 has moved before their safe zone
                        if(p2cPosn == 8)
                        {
                            p2cPosn = 68;
                        }
                        else if(p2cPosn == 7)
                        {
                            p2cPosn = 67;
                        }
                        else if(p2cPosn == 6)
                        {
                            p2cPosn = 66;
                        }
                        else if(p2cPosn == 5)
                        {
                            p2cPosn = 65;
                        }
                        else if(p2cPosn == 4)
                        {
                            p2cPosn = 64;
                        }
                        else if(p2cPosn == 3)
                        {
                            p2cPosn = 63;
                        }
                        else if(p2cPosn == 2)
                        {
                            p2cPosn = 62;
                        }
                        else if(p2cPosn == 1)
                        {
                            p2cPosn = 61;
                        }
                        else if(p2cPosn == 0)
                        {
                            p2cPosn = 60;
                        }
                        cout << pTrePos[p3cPosn] << endl;
                        cout << endl;
                        cout << pTwoPos[p2cPosn] << endl;
                        break;
                    case 4:
                        break;
                }
            }

            //Player 3 draws a "12"
            else if(card == 10)
            {
                //Print the card's specific menu
                cout << "You drew a 12!" << endl;
                cout << "1. Move 12 spaces forward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move 
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p3cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 2) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p3cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p3cPosn += 12;
                        if(p3cPosn > 74)
                        {
                            p3cPosn = 74;
                        }
                        cout << pTrePos[p3cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }      

            //Player 3 draws a "Sorry!" card
            else
            {
                //Print the card's specific menu
                cout << "You drew a \"Sorry!\" Card!" << endl;
                cout << "1. Move Player One's pawn off the game board" << endl;
                cout << "2. Move Player Two's pawn off the game board" << endl;
                cout << "3. Skip turn" << endl;

                //Check for legal move 
                do
                {
                    if((pChoice > 3) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p2cPosn < 9) ||
                      (pChoice == 3 && p1cPosn >= 9) || (pChoice == 3 && p2cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 3) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p2cPosn < 9) ||
                       (pChoice == 3 && p1cPosn >= 9) || (pChoice == 3 && p2cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p1cPosn = 0;
                        cout << "\nPlayer 1 has been moved off the game board!" << endl;
                        cout << pOnePos[0] << endl;
                        break;
                    case 2:
                        p3cPosn = 0;
                        cout << "\nPlayer 2 has been moved off the game board!" << endl;
                        cout << pTwoPos[0] << endl;
                        break;
                    case 3:
                        break;
                }
            }

            //Determine whether player 3 has won the game
            if(p3cPosn >= 74)
            {
                cout << "\nPlayer 3 has won the game!" << endl;
                restart = true;
            }           
        }
        
        //Reset the player's choice
        pChoice = 0;
        cin.clear();
        cin.ignore();

    //Exit or repeat the while loop
    }
}

/**
 * @brief Four Player Mode
 * 
 * This function prompts for input four times; once for each human player
 * Introduces the ampersat character (@) and utilizes the player 4 game boards.
 * 
 * @return Void
 */
void forPlyr()
{
    //Seed the random number generator
    srand(time(0));
    
    //Declare variables
    unsigned short card = 0;                    //Card drawn (Random)
    unsigned short choice, pChoice = 0;         //Which option the user wants after they draw a card
    unsigned short p1cPosn = 0;                 //Player 1's current position on the game board
    unsigned short p2cPosn = 0;                 //Player 2's current position on the game board
    unsigned short p3cPosn = 0;                 //Player 3's current position on the game board
    unsigned short p4cPosn = 0;                 //Player 4's current position on the game board
    unsigned short temp = 0;                    //Hold a temporary value
    bool restart = false;                       //Exits the function if player 1 wins
    string pOnePos[TPOSTNS];                    //Array containing Player 1 game boards (*)
    string pTwoPos[TPOSTNS];                    //Array containing Player 2 game boards (#)
    string pTrePos[TPOSTNS];                    //Array containing Player 3 game boards (&)
    string pForPos[TPOSTNS];                    //Array containing Player 4 game boards (@) 
    string p1Sstrg, p2Sstrg, p3Sstrg, p4Sstrg;  //Player 1 & 2 substrings
    size_t pos1 = 0, pos2;                      //Cursors for creating substrings
    stringstream buffer;                        //variable for the string stream buffer
    
    //Output Title
    cout << endl;
    cout << setw(36) << "4 player Mode" << endl;
    cout << endl;
    
    //Print players and their symbols
    cout << "Player 1 \t Player 2 \t Player 3 \t Player 4" << endl;
    cout << "-------- \t -------- \t -------- \t --------" << endl;
    cout << "    *    \t     #    \t     &    \t     @   " << endl;
    
    //Load the text file for player 1
    ifstream in_p1("Player1_GameBoards.txt");
    buffer << in_p1.rdbuf();
    p1Sstrg = buffer.str();
    
    //Read the text file into the player 1 array
    for(int i = 0; i < TPOSTNS; i++)
    {
        pos2 = p1Sstrg.find(",", pos1);                    //Search for the "," (position 2 will be where the comma was found)
        pOnePos[i] = p1Sstrg.substr(pos1, (pos2-pos1));    //Make the substring
        pos1 = pos2 + 1;
    }
    
    //Load the text file for player 2
    ifstream in_p2("Player2_GameBoards.txt");
    buffer << in_p2.rdbuf();
    p2Sstrg = buffer.str();
    
    //Read the text file into the player 2 array
    for(int c = 0; c < TPOSTNS; c++)
    {
        pos2 = p2Sstrg.find(",", pos1);                     //Search for the "," (position 2 will be where the comma was found)
        pTwoPos[c] = p2Sstrg.substr(pos1, (pos2-pos1));     //Make the substring
        pos1 = pos2 + 1;
    }
    
    //Load the text file for player 3
    ifstream in_p3("Player3_GameBoards.txt");
    buffer << in_p3.rdbuf();
    p3Sstrg = buffer.str();
    
    //Read the text file into the player 3 array
    for(int j = 0; j < TPOSTNS; j++)
    {
        pos2 = p3Sstrg.find(",", pos1);                     //Search for the "," (position 2 will be where the comma was found)
        pTrePos[j] = p3Sstrg.substr(pos1, (pos2-pos1));     //Make the substring
        pos1 = pos2 + 1;
    }
    
    //Load the text file for player 4
    ifstream in_p4("Player4_GameBoards.txt");
    buffer << in_p4.rdbuf();
    p4Sstrg = buffer.str();
    
    //Read the text file into the player 4 array
    for(int r = 0; r < TPOSTNS; r++)
    {
        pos2 = p4Sstrg.find(",", pos1);                     //Search for the "," (position 2 will be where the comma was found)
        pForPos[r] = p4Sstrg.substr(pos1, (pos2-pos1));     //Make the substring
        pos1 = pos2 + 1;
    }
    
    //Begin the game
    //Loop until a player exceeds their native 74th position
    while(p1cPosn < 74 && p2cPosn < 74 && p3cPosn < 74 && p4cPosn < 74)
    {
        cout << endl;
        cout << setw(25) << "PLAYER 1'S TURN:";
        cout << "\nPress the Enter key to draw a card! ";
        cin.get();

        //generate a random card
        card = (rand() % 11) + 1;
        cout << endl;

        //Determine the card value and apply the rules
        //Player 1 draws a "1"
        if(card == 1)
        {
            //Print the card's specific menu
            cout << "You drew a 1!" << endl;
            cout << "1. Start" << endl;
            cout << "2. Move 1 space forward" << endl;
            cout << "3. Skip turn" << endl;

            //Check for legal move
            do
            {
                if((pChoice > 3) || (pChoice == 1 && p1cPosn >= 9) || (pChoice == 2 && p1cPosn < 9) || (pChoice == 3))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);                
            }while((pChoice > 3) || (pChoice == 1 && p1cPosn >= 9) || (pChoice == 2 && p1cPosn < 9) || (pChoice == 3));

            //Execute the desired action
            switch(pChoice)
            {
                case 1: 
                    p1cPosn = 10;
                    cout << pOnePos[p1cPosn] << endl;   //Output modified game board
                    break;
                case 2:
                    p1cPosn += 1;
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 3:
                    break;
            }
        }

        //Player 1 draws a "2"
        else if(card == 2)
        {
            //Print the card's specific menu
            cout << "You drew a 2!" << endl;
            cout << "1. Start" << endl;
            cout << "2. Move 2 spaces forward" << endl;
            cout << "3. Skip turn" << endl;

            //Check for legal move
            do
            {
                if((pChoice > 3) || (pChoice == 1 && p1cPosn >= 9) || (pChoice == 1 && p1cPosn >= 9) || (pChoice == 3))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice); 
            }while((pChoice > 3) || (pChoice == 1 && p1cPosn >= 9) || (pChoice == 1 && p1cPosn >= 9) || (pChoice == 3));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn = 10;
                    cout << pOnePos[p1cPosn] << endl;   //Output modified game board
                    break;
                case 2:
                    p1cPosn += 2;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;   //Output modified game board
                    break;
                case 3:
                    break;
            }
        }

        //Player 1 draws a "3"
        else if(card == 3)
        {
            //Print the card's specific menu
            cout << "You drew a 3!" << endl;
            cout << "1. Move 3 spaces forward" << endl;
            cout << "2. Skip turn" << endl;

            //Check for legal move 
            do
            {
                if((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);                    
            } while((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn += 3;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    break;
            }
        }

        //Player 1 draws a "4"
        else if(card == 4)
        {
            //Print the card's specific menu
            cout << "You drew a 4!" << endl;
            cout << "1. Move 4 spaces backward" << endl;
            cout << "2. Skip turn" << endl;

            //Check for legal move
            do
            {
                if((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);
            } while((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn -= 4;                       

                    //Determine if Player 1 has moved before their safe zone (P1-0 - P1-8)
                    if(p1cPosn == 8)
                    {
                        p1cPosn = 68;
                    }
                    else if(p1cPosn == 7)
                    {
                        p1cPosn = 67;
                    }
                    else if(p1cPosn == 6)
                    {
                        p1cPosn = 66;
                    }
                    else if(p1cPosn == 5)
                    {
                        p1cPosn = 65;
                    }
                    else if(p1cPosn == 4)
                    {
                        p1cPosn = 64;
                    }
                    else if(p1cPosn == 3)
                    {
                        p1cPosn = 63;
                    }
                    else if(p1cPosn == 2)
                    {
                        p1cPosn = 62;
                    }
                    else if(p1cPosn == 1)
                    {
                        p1cPosn = 61;
                    }
                    else if(p1cPosn == 0)
                    {
                        p1cPosn = 60;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    break;
            }
        }

        //Player 1 draws a "5"
        else if(card == 5)
        {
            //Print the card's specific menu
            cout << "You drew a 5!" << endl;
            cout << "1. Move 5 spaces forward" << endl;
            cout << "2. Skip turn" << endl;

            //Check for legal move
            do
            {
                if((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);  
            } while((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn += 5;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    break;
            }
        }

        //Player 1 draws a "7"
        else if(card == 6)
        {
            //Print the card's specific menu
            cout << "You drew a 7!" << endl;
            cout << "1. Move 7 spaces forward" << endl;
            cout << "2. Move Player Two 7 spaces backward" << endl;
            cout << "3. Move Player Three 7 spaces backward" << endl;
            cout << "4. Move Player Four 7 spaces backward" << endl;
            cout << "5. Skip turn" << endl;

            //Check for legal move
            do
            {
                if((pChoice > 5) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p2cPosn < 9) ||
                  (pChoice == 3 && p3cPosn < 9) || (pChoice == 4 && p4cPosn < 9) || (pChoice == 5 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);
            } while((pChoice > 5) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p2cPosn < 9) ||
                   (pChoice == 3 && p3cPosn < 9) || (pChoice == 4 && p4cPosn < 9) || (pChoice == 5 && p1cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn += 7;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    p2cPosn -= 7;                       

                    //Determine if Player 2 has moved before their safe zone
                    if(p2cPosn == 8)
                    {
                        p2cPosn = 68;
                    }
                    else if(p2cPosn == 7)
                    {
                        p2cPosn = 67;
                    }
                    else if(p2cPosn == 6)
                    {
                        p2cPosn = 66;
                    }
                    else if(p2cPosn == 5)
                    {
                        p2cPosn = 65;
                    }
                    else if(p2cPosn == 4)
                    {
                        p2cPosn = 64;
                    }
                    else if(p2cPosn == 3)
                    {
                        p2cPosn = 63;
                    }
                    else if(p2cPosn == 2)
                    {
                        p2cPosn = 62;
                    }
                    else if(p2cPosn == 1)
                    {
                        p2cPosn = 61;
                    }
                    else if(p2cPosn == 0)
                    {
                        p2cPosn = 60;
                    }
                    cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                    break;
                case 3:
                    p3cPosn -= 7;                       

                    //Determine if Player 3 has moved before their safe zone
                    if(p3cPosn == 8)
                    {
                        p3cPosn = 68;
                    }
                    else if(p3cPosn == 7)
                    {
                        p3cPosn = 67;
                    }
                    else if(p3cPosn == 6)
                    {
                        p3cPosn = 66;
                    }
                    else if(p3cPosn == 5)
                    {
                        p3cPosn = 65;
                    }
                    else if(p3cPosn == 4)
                    {
                        p3cPosn = 64;
                    }
                    else if(p3cPosn == 3)
                    {
                        p3cPosn = 63;
                    }
                    else if(p3cPosn == 2)
                    {
                        p3cPosn = 62;
                    }
                    else if(p3cPosn == 1)
                    {
                        p3cPosn = 61;
                    }
                    else if(p3cPosn == 0)
                    {
                        p3cPosn = 60;
                    }
                    cout << pTrePos[p3cPosn] << endl;    //Output modified game board
                    break;
                case 4:
                    p4cPosn -= 7;                       

                    //Determine if Player 4 has moved before their safe zone
                    if(p4cPosn == 8)
                    {
                        p4cPosn = 68;
                    }
                    else if(p4cPosn == 7)
                    {
                        p4cPosn = 67;
                    }
                    else if(p4cPosn == 6)
                    {
                        p4cPosn = 66;
                    }
                    else if(p4cPosn == 5)
                    {
                        p4cPosn = 65;
                    }
                    else if(p4cPosn == 4)
                    {
                        p4cPosn = 64;
                    }
                    else if(p4cPosn == 3)
                    {
                        p4cPosn = 63;
                    }
                    else if(p4cPosn == 2)
                    {
                        p4cPosn = 62;
                    }
                    else if(p4cPosn == 1)
                    {
                        p4cPosn = 61;
                    }
                    else if(p4cPosn == 0)
                    {
                        p4cPosn = 60;
                    }
                    cout << pForPos[p4cPosn] << endl;    //Output modified game board
                    break;
                case 5:
                    break;
            }
        }

        //Player 1 draws an "8"
        else if(card == 7)
        {
            //Print the card's specific menu
            cout << "You drew an 8!" << endl;
            cout << "1. Move 8 spaces forward" << endl;
            cout << "2. Skip turn" << endl;

            //Check for legal move
            do
            {
                if((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);                
            } while((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn += 8;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    break;
            }
        }

        //Player 1 draws a "10"
        else if(card == 8)
        {
            //Print the card's specific menu
            cout << "You drew a 10!" << endl;
            cout << "1. Move 10 spaces forward" << endl;
            cout << "2. Move 1 space backward" << endl;
            cout << "3. Skip turn" << endl;

            //Check for legal move
            do
            {
                if((pChoice > 3) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn < 9) || (pChoice == 3 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);                   
            }while((pChoice > 3) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn < 9) || (pChoice == 3 && p1cPosn >= 9));           

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn += 10;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    p1cPosn -= 1;                        

                    //Determine if Player 1 has moved before their safe zone (P1-0 - P1-8)
                    if(p1cPosn == 8)
                    {
                        p1cPosn = 68;
                    }
                    else if(p1cPosn == 7)
                    {
                        p1cPosn = 67;
                    }
                    else if(p1cPosn == 6)
                    {
                        p1cPosn = 66;
                    }
                    else if(p1cPosn == 5)
                    {
                        p1cPosn = 65;
                    }
                    else if(p1cPosn == 4)
                    {
                        p1cPosn = 64;
                    }
                    else if(p1cPosn == 3)
                    {
                        p1cPosn = 63;
                    }
                    else if(p1cPosn == 2)
                    {
                        p1cPosn = 62;
                    }
                    else if(p1cPosn == 1)
                    {
                        p1cPosn = 61;
                    }
                    else if(p1cPosn == 0)
                    {
                        p1cPosn = 60;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 3:
                    break;
            }
        }

        //Player 1 draws an "11"
        else if(card == 9)
        {
            //Print the card's specific menu
            cout << "You drew an 11!" << endl;
            cout << "1. Move 11 spaces forward" << endl;
            cout << "2. Switch places with Player Two's pawn" << endl;
            cout << "3. Switch places with Player Three's pawn" << endl;
            cout << "4. Switch places with Player Four's pawn" << endl;
            cout << "5. Skip turn" << endl;

            //Check for legal move 
            do
            {
                if((pChoice > 5) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn < 9) ||
                  (pChoice == 2 && p2cPosn < 9) || (pChoice == 3 && p1cPosn < 9) || (pChoice == 3 && p3cPosn < 9) ||
                  (pChoice == 4 && p1cPosn < 9) || (pChoice == 4 && p4cPosn < 9) || (pChoice == 4 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);
            } while((pChoice > 5) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn < 9) ||
                   (pChoice == 2 && p2cPosn < 9) || (pChoice == 3 && p1cPosn < 9) || (pChoice == 3 && p3cPosn < 9) ||
                   (pChoice == 4 && p1cPosn < 9) || (pChoice == 4 && p4cPosn < 9) || (pChoice == 4 && p1cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn += 11;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    if(p1cPosn >= 15 && p2cPosn >= 15)
                    {
                        temp = p1cPosn;
                        p1cPosn = p2cPosn - 15;
                        p2cPosn = temp + 15;
                    }
                    else if(p1cPosn >= 15 && p2cPosn <= 15)
                    {
                        temp = p1cPosn;
                        p1cPosn = 60 + p2cPosn - 15;
                        p2cPosn = 15 - (60 - temp);
                    }
                    else if(p1cPosn <= 15 && p2cPosn <= 15)
                    {
                        temp = p1cPosn;
                        p1cPosn = 60 + p2cPosn - 15;
                        p2cPosn = temp + 15;
                    }
                    else if(p1cPosn <= 15 && p2cPosn >= 15)
                    {
                        p1cPosn = p2cPosn - 15;
                        p2cPosn = p2cPosn - (p1cPosn - 10);
                    }                       

                    //Determine if Player 1 has moved before their safe zone (P1-0 - P1-8)
                    if(p1cPosn == 8)
                    {
                        p1cPosn = 68;
                    }
                    else if(p1cPosn == 7)
                    {
                        p1cPosn = 67;
                    }
                    else if(p1cPosn == 6)
                    {
                        p1cPosn = 66;
                    }
                    else if(p1cPosn == 5)
                    {
                        p1cPosn = 65;
                    }
                    else if(p1cPosn == 4)
                    {
                        p1cPosn = 64;
                    }
                    else if(p1cPosn == 3)
                    {
                        p1cPosn = 63;
                    }
                    else if(p1cPosn == 2)
                    {
                        p1cPosn = 62;
                    }
                    else if(p1cPosn == 1)
                    {
                        p1cPosn = 61;
                    }
                    else if(p1cPosn == 0)
                    {
                        p1cPosn = 60;
                    }

                    //Determine if Player 2 has moved before their safe zone (P2-0 - P2-8)
                    if(p2cPosn == 8)
                    {
                        p2cPosn = 68;
                    }
                    else if(p2cPosn == 7)
                    {
                        p2cPosn = 67;
                    }
                    else if(p2cPosn == 6)
                    {
                        p2cPosn = 66;
                    }
                    else if(p2cPosn == 5)
                    {
                        p2cPosn = 65;
                    }
                    else if(p2cPosn == 4)
                    {
                        p2cPosn = 64;
                    }
                    else if(p2cPosn == 3)
                    {
                        p2cPosn = 63;
                    }
                    else if(p2cPosn == 2)
                    {
                        p2cPosn = 62;
                    }
                    else if(p2cPosn == 1)
                    {
                        p2cPosn = 61;
                    }
                    else if(p2cPosn == 0)
                    {
                        p2cPosn = 60;
                    }
                    cout << pOnePos[p1cPosn] << endl;
                    cout << endl;
                    cout << pTwoPos[p2cPosn] << endl;
                    break;
                case 3:
                    if(p1cPosn >= 15 && p3cPosn >= 15)
                    {
                        temp = p1cPosn;
                        p1cPosn = p3cPosn - 15;
                        p3cPosn = temp + 15;
                    }
                    else if(p1cPosn >= 15 && p3cPosn <= 15)
                    {
                        temp = p1cPosn;
                        p1cPosn = 60 + p3cPosn - 15;
                        p3cPosn = 15 - (60 - temp);
                    }
                    else if(p1cPosn <= 15 && p3cPosn <= 15)
                    {
                        temp = p1cPosn;
                        p1cPosn = 60 + p3cPosn - 15;
                        p3cPosn = temp + 15;
                    }
                    else if(p1cPosn <= 15 && p3cPosn >= 15)
                    {
                        p1cPosn = p3cPosn - 15;
                        p3cPosn = p3cPosn - (p1cPosn - 10);
                    }                       

                    //Determine if Player 1 has moved before their safe zone
                    if(p1cPosn == 8)
                    {
                        p1cPosn = 68;
                    }
                    else if(p1cPosn == 7)
                    {
                        p1cPosn = 67;
                    }
                    else if(p1cPosn == 6)
                    {
                        p1cPosn = 66;
                    }
                    else if(p1cPosn == 5)
                    {
                        p1cPosn = 65;
                    }
                    else if(p1cPosn == 4)
                    {
                        p1cPosn = 64;
                    }
                    else if(p1cPosn == 3)
                    {
                        p1cPosn = 63;
                    }
                    else if(p1cPosn == 2)
                    {
                        p1cPosn = 62;
                    }
                    else if(p1cPosn == 1)
                    {
                        p1cPosn = 61;
                    }
                    else if(p1cPosn == 0)
                    {
                        p1cPosn = 60;
                    }

                    //Determine if Player 3 has moved before their safe zone
                    if(p3cPosn == 8)
                    {
                        p3cPosn = 68;
                    }
                    else if(p3cPosn == 7)
                    {
                        p3cPosn = 67;
                    }
                    else if(p3cPosn == 6)
                    {
                        p3cPosn = 66;
                    }
                    else if(p3cPosn == 5)
                    {
                        p3cPosn = 65;
                    }
                    else if(p3cPosn == 4)
                    {
                        p3cPosn = 64;
                    }
                    else if(p3cPosn == 3)
                    {
                        p3cPosn = 63;
                    }
                    else if(p3cPosn == 2)
                    {
                        p3cPosn = 62;
                    }
                    else if(p3cPosn == 1)
                    {
                        p3cPosn = 61;
                    }
                    else if(p3cPosn == 0)
                    {
                        p3cPosn = 60;
                    }
                    cout << pOnePos[p1cPosn] << endl;
                    cout << endl;
                    cout << pTrePos[p3cPosn] << endl;
                    break;
                case 4:
                    if(p1cPosn >= 15 && p4cPosn >= 15)
                    {
                        temp = p1cPosn;
                        p1cPosn = p4cPosn - 15;
                        p4cPosn = temp + 15;
                    }
                    else if(p1cPosn >= 15 && p4cPosn <= 15)
                    {
                        temp = p1cPosn;
                        p1cPosn = 60 + p4cPosn - 15;
                        p4cPosn = 15 - (60 - temp);
                    }
                    else if(p1cPosn <= 15 && p4cPosn <= 15)
                    {
                        temp = p1cPosn;
                        p1cPosn = 60 + p4cPosn - 15;
                        p4cPosn = temp + 15;
                    }
                    else if(p1cPosn <= 15 && p4cPosn >= 15)
                    {
                        p1cPosn = p4cPosn - 15;
                        p4cPosn = p4cPosn - (p1cPosn - 10);
                    }                       

                    //Determine if Player 1 has moved before their safe zone
                    if(p1cPosn == 8)
                    {
                        p1cPosn = 68;
                    }
                    else if(p1cPosn == 7)
                    {
                        p1cPosn = 67;
                    }
                    else if(p1cPosn == 6)
                    {
                        p1cPosn = 66;
                    }
                    else if(p1cPosn == 5)
                    {
                        p1cPosn = 65;
                    }
                    else if(p1cPosn == 4)
                    {
                        p1cPosn = 64;
                    }
                    else if(p1cPosn == 3)
                    {
                        p1cPosn = 63;
                    }
                    else if(p1cPosn == 2)
                    {
                        p1cPosn = 62;
                    }
                    else if(p1cPosn == 1)
                    {
                        p1cPosn = 61;
                    }
                    else if(p1cPosn == 0)
                    {
                        p1cPosn = 60;
                    }

                    //Determine if Player 4 has moved before their safe zone
                    if(p4cPosn == 8)
                    {
                        p4cPosn = 68;
                    }
                    else if(p4cPosn == 7)
                    {
                        p4cPosn = 67;
                    }
                    else if(p4cPosn == 6)
                    {
                        p4cPosn = 66;
                    }
                    else if(p4cPosn == 5)
                    {
                        p4cPosn = 65;
                    }
                    else if(p4cPosn == 4)
                    {
                        p4cPosn = 64;
                    }
                    else if(p4cPosn == 3)
                    {
                        p4cPosn = 63;
                    }
                    else if(p4cPosn == 2)
                    {
                        p4cPosn = 62;
                    }
                    else if(p4cPosn == 1)
                    {
                        p4cPosn = 61;
                    }
                    else if(p4cPosn == 0)
                    {
                        p4cPosn = 60;
                    }
                    cout << pOnePos[p1cPosn] << endl;
                    cout << endl;
                    cout << pForPos[p4cPosn] << endl;
                    break;
                case 5:
                    break;
            }
        }

        //Player 1 draws a "12"
        else if(card == 10)
        {
            //Print the card's specific menu
            cout << "You drew a 12!" << endl;
            cout << "1. Move 12 spaces forward" << endl;
            cout << "2. Skip turn" << endl;

            //Check for legal move 
            do
            {
                if((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);
            } while((pChoice > 2) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p1cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p1cPosn += 12;
                    if(p1cPosn > 74)
                    {
                        p1cPosn = 74;
                    }
                    cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                    break;
                case 2:
                    break;
            }
        }      

        //Player 1 draws a "Sorry!" card
        else
        {
            //Print the card's specific menu
            cout << "You drew a \"Sorry!\" Card!" << endl;
            cout << "1. Move Player Two's pawn off the game board" << endl;
            cout << "2. Move Player Three's pawn off the game board" << endl;
            cout << "3. Move Player Four's pawn off the game board" << endl;
            cout << "4. Skip turn" << endl;

            //Check for legal move 
            do
            {
                if((pChoice > 4) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p3cPosn < 9) || (pChoice == 3 && p4cPosn < 9) ||
                  (pChoice == 4 && p2cPosn >= 9) || (pChoice == 4 && p3cPosn >= 9) || (pChoice == 4 && p4cPosn >= 9))
                {
                    cout << "That's an illegal move!";
                }
                cout << "\nWhich choice would you like to make? ";
                pChoice = int_chk(choice);
            } while((pChoice > 4) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p3cPosn < 9) || (pChoice == 3 && p4cPosn < 9) ||
                   (pChoice == 4 && p2cPosn >= 9) || (pChoice == 4 && p3cPosn >= 9) || (pChoice == 4 && p4cPosn >= 9));

            //Execute the desired action
            switch(pChoice)
            {
                case 1:
                    p2cPosn = 0;
                    cout << "\nPlayer 2 has been moved off the game board!" << endl;
                    cout << pTwoPos[0] << endl;
                    break;
                case 2:
                    p3cPosn = 0;
                    cout << "\nPlayer 3 has been moved off the game board!" << endl;
                    cout << pTrePos[0] << endl;
                    break;
                case 3:
                    p4cPosn = 0;
                    cout << "\nPlayer 4 has been moved off the game board!" << endl;
                    cout << pForPos[0] << endl;
                    break;
                case 4:
                    break;
            }
        }

        //Determine whether Player 1 has won the game
        if(p1cPosn == 74)
        {
            cout << "\nPlayer 1 has won the game!" << endl;
            restart = true;
        }

        //Reset the player's choice
        pChoice = 0;
        
        //Begin player 2's turn
        if(restart == false)
        {
            cout << endl;
            cout << setw(25) << "PLAYER 2'S TURN:";
            cout << "\nPress the Enter key to draw a card! ";
            cin.ignore();
            cin.get();

            //generate a random card
            card = (rand() % 11) + 1;
            cout << endl;

            //Determine the card value and apply the rules
            //Player 2 draws a "1"
            if(card == 1)
            {
                //Print the card's specific menu
                cout << "You drew a 1!" << endl;
                cout << "1. Start" << endl;
                cout << "2. Move 1 space forward" << endl;
                cout << "3. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 3) || (pChoice == 1 && p2cPosn >= 9) || (pChoice == 2 && p2cPosn < 9) || (pChoice == 3))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);                
                }while((pChoice > 3) || (pChoice == 1 && p2cPosn >= 9) || (pChoice == 2 && p2cPosn < 9) || (pChoice == 3));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1: 
                        p2cPosn = 10;
                        cout << pTwoPos[p2cPosn] << endl;   //Output modified game board
                        break;
                    case 2:
                        p2cPosn += 1;
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 3:
                        break;
                }
            }

            //Player 2 draws a "2"
            else if(card == 2)
            {
                //Print the card's specific menu
                cout << "You drew a 2!" << endl;
                cout << "1. Start" << endl;
                cout << "2. Move 2 spaces forward" << endl;
                cout << "3. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 3) || (pChoice == 1 && p2cPosn >= 9) || (pChoice == 1 && p2cPosn >= 9) || (pChoice == 3))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice); 
                }while((pChoice > 3) || (pChoice == 1 && p2cPosn >= 9) || (pChoice == 1 && p2cPosn >= 9) || (pChoice == 3));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p2cPosn = 10;
                        cout << pTwoPos[p2cPosn] << endl;   //Output modified game board
                        break;
                    case 2:
                        p2cPosn += 2;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;   //Output modified game board
                        break;
                    case 3:
                        break;
                }
            }

            //Player 2 draws a "3"
            else if(card == 3)
            {
                //Print the card's specific menu
                cout << "You drew a 3!" << endl;
                cout << "1. Move 3 spaces forward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move 
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);                    
                } while((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p2cPosn += 3;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }

            //Player 2 draws a "4"
            else if(card == 4)
            {
                //Print the card's specific menu
                cout << "You drew a 4!" << endl;
                cout << "1. Move 4 spaces backward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p2cPosn -= 4;                       

                        //Determine if Player 1 has moved before their safe zone (P1-0 - P1-8)
                        if(p2cPosn == 8)
                        {
                            p2cPosn = 68;
                        }
                        else if(p2cPosn == 7)
                        {
                            p2cPosn = 67;
                        }
                        else if(p2cPosn == 6)
                        {
                            p2cPosn = 66;
                        }
                        else if(p2cPosn == 5)
                        {
                            p2cPosn = 65;
                        }
                        else if(p2cPosn == 4)
                        {
                            p2cPosn = 64;
                        }
                        else if(p2cPosn == 3)
                        {
                            p2cPosn = 63;
                        }
                        else if(p2cPosn == 2)
                        {
                            p2cPosn = 62;
                        }
                        else if(p2cPosn == 1)
                        {
                            p2cPosn = 61;
                        }
                        else if(p2cPosn == 0)
                        {
                            p2cPosn = 60;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }

            //Player 2 draws a "5"
            else if(card == 5)
            {
                //Print the card's specific menu
                cout << "You drew a 5!" << endl;
                cout << "1. Move 5 spaces forward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);  
                } while((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p2cPosn += 5;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }

            //Player 2 draws a "7"
            else if(card == 6)
            {
                //Print the card's specific menu
                cout << "You drew a 7!" << endl;
                cout << "1. Move 7 spaces forward" << endl;
                cout << "2. Move Player One 7 spaces backward" << endl;
                cout << "3. Move Player Three 7 spaces backward" << endl;
                cout << "4. Move Player Four 7 spaces backward" << endl;
                cout << "5. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 5) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p1cPosn < 9) ||
                      (pChoice == 3 && p3cPosn < 9) || (pChoice == 4 && p4cPosn < 9) || (pChoice == 5 && p2cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 5) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p1cPosn < 9) ||
                       (pChoice == 3 && p3cPosn < 9) || (pChoice == 4 && p4cPosn < 9) || (pChoice == 5 && p2cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p2cPosn += 7;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        p1cPosn -= 7;                       

                        //Determine if Player 2 has moved before their safe zone
                        if(p1cPosn == 8)
                        {
                            p1cPosn = 68;
                        }
                        else if(p1cPosn == 7)
                        {
                            p1cPosn = 67;
                        }
                        else if(p1cPosn == 6)
                        {
                            p1cPosn = 66;
                        }
                        else if(p1cPosn == 5)
                        {
                            p1cPosn = 65;
                        }
                        else if(p1cPosn == 4)
                        {
                            p1cPosn = 64;
                        }
                        else if(p1cPosn == 3)
                        {
                            p1cPosn = 63;
                        }
                        else if(p1cPosn == 2)
                        {
                            p1cPosn = 62;
                        }
                        else if(p1cPosn == 1)
                        {
                            p1cPosn = 61;
                        }
                        else if(p1cPosn == 0)
                        {
                            p1cPosn = 60;
                        }
                        cout << pTwoPos[p1cPosn] << endl;    //Output modified game board
                        break;
                    case 3:
                        p3cPosn -= 7;                       

                        //Determine if Player 3 has moved before their safe zone
                        if(p3cPosn == 8)
                        {
                            p3cPosn = 68;
                        }
                        else if(p3cPosn == 7)
                        {
                            p3cPosn = 67;
                        }
                        else if(p3cPosn == 6)
                        {
                            p3cPosn = 66;
                        }
                        else if(p3cPosn == 5)
                        {
                            p3cPosn = 65;
                        }
                        else if(p3cPosn == 4)
                        {
                            p3cPosn = 64;
                        }
                        else if(p3cPosn == 3)
                        {
                            p3cPosn = 63;
                        }
                        else if(p3cPosn == 2)
                        {
                            p3cPosn = 62;
                        }
                        else if(p3cPosn == 1)
                        {
                            p3cPosn = 61;
                        }
                        else if(p3cPosn == 0)
                        {
                            p3cPosn = 60;
                        }
                        cout << pTrePos[p3cPosn] << endl;    //Output modified game board
                        break;
                    case 4:
                        p4cPosn -= 7;                       

                        //Determine if Player 4 has moved before their safe zone
                        if(p4cPosn == 8)
                        {
                            p4cPosn = 68;
                        }
                        else if(p4cPosn == 7)
                        {
                            p4cPosn = 67;
                        }
                        else if(p4cPosn == 6)
                        {
                            p4cPosn = 66;
                        }
                        else if(p4cPosn == 5)
                        {
                            p4cPosn = 65;
                        }
                        else if(p4cPosn == 4)
                        {
                            p4cPosn = 64;
                        }
                        else if(p4cPosn == 3)
                        {
                            p4cPosn = 63;
                        }
                        else if(p4cPosn == 2)
                        {
                            p4cPosn = 62;
                        }
                        else if(p4cPosn == 1)
                        {
                            p4cPosn = 61;
                        }
                        else if(p4cPosn == 0)
                        {
                            p4cPosn = 60;
                        }
                        cout << pForPos[p4cPosn] << endl;    //Output modified game board
                        break;
                    case 5:
                        break;
                }
            }

            //Player 2 draws an "8"
            else if(card == 7)
            {
                //Print the card's specific menu
                cout << "You drew an 8!" << endl;
                cout << "1. Move 8 spaces forward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);                
                } while((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p2cPosn += 8;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }

            //Player 2 draws a "10"
            else if(card == 8)
            {
                //Print the card's specific menu
                cout << "You drew a 10!" << endl;
                cout << "1. Move 10 spaces forward" << endl;
                cout << "2. Move 1 space backward" << endl;
                cout << "3. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 3) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn < 9) || (pChoice == 3 && p2cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);                   
                }while((pChoice > 3) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn < 9) || (pChoice == 3 && p2cPosn >= 9));           

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p2cPosn += 10;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        p2cPosn -= 1;                        

                        //Determine if Player 1 has moved before their safe zone (P1-0 - P1-8)
                        if(p2cPosn == 8)
                        {
                            p2cPosn = 68;
                        }
                        else if(p2cPosn == 7)
                        {
                            p2cPosn = 67;
                        }
                        else if(p2cPosn == 6)
                        {
                            p2cPosn = 66;
                        }
                        else if(p2cPosn == 5)
                        {
                            p2cPosn = 65;
                        }
                        else if(p2cPosn == 4)
                        {
                            p2cPosn = 64;
                        }
                        else if(p2cPosn == 3)
                        {
                            p2cPosn = 63;
                        }
                        else if(p2cPosn == 2)
                        {
                            p2cPosn = 62;
                        }
                        else if(p2cPosn == 1)
                        {
                            p2cPosn = 61;
                        }
                        else if(p2cPosn == 0)
                        {
                            p2cPosn = 60;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 3:
                        break;
                }
            }

            //Player 2 draws an "11"
            else if(card == 9)
            {
                //Print the card's specific menu
                cout << "You drew an 11!" << endl;
                cout << "1. Move 11 spaces forward" << endl;
                cout << "2. Switch places with Player One's pawn" << endl;
                cout << "3. Switch places with Player Three's pawn" << endl;
                cout << "4. Switch places with Player Four's pawn" << endl;
                cout << "5. Skip turn" << endl;

                //Check for legal move 
                do
                {
                    if((pChoice > 5) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn < 9) ||
                      (pChoice == 2 && p1cPosn < 9) || (pChoice == 3 && p2cPosn < 9) || (pChoice == 3 && p3cPosn < 9) ||
                      (pChoice == 4 && p2cPosn < 9) || (pChoice == 4 && p4cPosn < 9) || (pChoice == 4 && p2cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 5) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn < 9) ||
                       (pChoice == 2 && p1cPosn < 9) || (pChoice == 3 && p2cPosn < 9) || (pChoice == 3 && p3cPosn < 9) ||
                       (pChoice == 4 && p2cPosn < 9) || (pChoice == 4 && p4cPosn < 9) || (pChoice == 4 && p2cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p2cPosn += 11;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        if(p2cPosn >= 15 && p1cPosn >= 15)
                        {
                            temp = p2cPosn;
                            p2cPosn = p1cPosn - 15;
                            p1cPosn = temp + 15;
                        }
                        else if(p2cPosn >= 15 && p1cPosn <= 15)
                        {
                            temp = p2cPosn;
                            p2cPosn = 60 + p1cPosn - 15;
                            p1cPosn = 15 - (60 - temp);
                        }
                        else if(p2cPosn <= 15 && p1cPosn <= 15)
                        {
                            temp = p2cPosn;
                            p2cPosn = 60 + p1cPosn - 15;
                            p1cPosn = temp + 15;
                        }
                        else if(p2cPosn <= 15 && p1cPosn >= 15)
                        {
                            p2cPosn = p1cPosn - 15;
                            p1cPosn = p1cPosn - (p2cPosn - 10);
                        }                       

                        //Determine if Player 2 has moved before their safe zone
                        if(p2cPosn == 8)
                        {
                            p2cPosn = 68;
                        }
                        else if(p2cPosn == 7)
                        {
                            p2cPosn = 67;
                        }
                        else if(p2cPosn == 6)
                        {
                            p2cPosn = 66;
                        }
                        else if(p2cPosn == 5)
                        {
                            p2cPosn = 65;
                        }
                        else if(p2cPosn == 4)
                        {
                            p2cPosn = 64;
                        }
                        else if(p2cPosn == 3)
                        {
                            p2cPosn = 63;
                        }
                        else if(p2cPosn == 2)
                        {
                            p2cPosn = 62;
                        }
                        else if(p2cPosn == 1)
                        {
                            p2cPosn = 61;
                        }
                        else if(p2cPosn == 0)
                        {
                            p2cPosn = 60;
                        }

                        //Determine if Player 2 has moved before their safe zone
                        if(p1cPosn == 8)
                        {
                            p1cPosn = 68;
                        }
                        else if(p1cPosn == 7)
                        {
                            p1cPosn = 67;
                        }
                        else if(p1cPosn == 6)
                        {
                            p1cPosn = 66;
                        }
                        else if(p1cPosn == 5)
                        {
                            p1cPosn = 65;
                        }
                        else if(p1cPosn == 4)
                        {
                            p1cPosn = 64;
                        }
                        else if(p1cPosn == 3)
                        {
                            p1cPosn = 63;
                        }
                        else if(p1cPosn == 2)
                        {
                            p1cPosn = 62;
                        }
                        else if(p1cPosn == 1)
                        {
                            p1cPosn = 61;
                        }
                        else if(p1cPosn == 0)
                        {
                            p1cPosn = 60;
                        }
                        cout << pTwoPos[p2cPosn] << endl;
                        cout << endl;
                        cout << pOnePos[p1cPosn] << endl;
                        break;
                    case 3:
                        if(p2cPosn >= 15 && p3cPosn >= 15)
                        {
                            temp = p2cPosn;
                            p2cPosn = p3cPosn - 15;
                            p3cPosn = temp + 15;
                        }
                        else if(p2cPosn >= 15 && p3cPosn <= 15)
                        {
                            temp = p2cPosn;
                            p2cPosn = 60 + p3cPosn - 15;
                            p3cPosn = 15 - (60 - temp);
                        }
                        else if(p2cPosn <= 15 && p3cPosn <= 15)
                        {
                            temp = p2cPosn;
                            p2cPosn = 60 + p3cPosn - 15;
                            p3cPosn = temp + 15;
                        }
                        else if(p2cPosn <= 15 && p3cPosn >= 15)
                        {
                            p2cPosn = p3cPosn - 15;
                            p3cPosn = p3cPosn - (p2cPosn - 10);
                        }                       

                        //Determine if Player 2 has moved before their safe zone
                        if(p2cPosn == 8)
                        {
                            p2cPosn = 68;
                        }
                        else if(p2cPosn == 7)
                        {
                            p2cPosn = 67;
                        }
                        else if(p2cPosn == 6)
                        {
                            p2cPosn = 66;
                        }
                        else if(p2cPosn == 5)
                        {
                            p2cPosn = 65;
                        }
                        else if(p2cPosn == 4)
                        {
                            p2cPosn = 64;
                        }
                        else if(p2cPosn == 3)
                        {
                            p2cPosn = 63;
                        }
                        else if(p2cPosn == 2)
                        {
                            p2cPosn = 62;
                        }
                        else if(p2cPosn == 1)
                        {
                            p2cPosn = 61;
                        }
                        else if(p2cPosn == 0)
                        {
                            p2cPosn = 60;
                        }

                        //Determine if Player 3 has moved before their safe zone
                        if(p3cPosn == 8)
                        {
                            p3cPosn = 68;
                        }
                        else if(p3cPosn == 7)
                        {
                            p3cPosn = 67;
                        }
                        else if(p3cPosn == 6)
                        {
                            p3cPosn = 66;
                        }
                        else if(p3cPosn == 5)
                        {
                            p3cPosn = 65;
                        }
                        else if(p3cPosn == 4)
                        {
                            p3cPosn = 64;
                        }
                        else if(p3cPosn == 3)
                        {
                            p3cPosn = 63;
                        }
                        else if(p3cPosn == 2)
                        {
                            p3cPosn = 62;
                        }
                        else if(p3cPosn == 1)
                        {
                            p3cPosn = 61;
                        }
                        else if(p3cPosn == 0)
                        {
                            p3cPosn = 60;
                        }
                        cout << pTwoPos[p2cPosn] << endl;
                        cout << endl;
                        cout << pTrePos[p3cPosn] << endl;
                        break;
                    case 4:
                        if(p2cPosn >= 15 && p4cPosn >= 15)
                        {
                            temp = p2cPosn;
                            p2cPosn = p4cPosn - 15;
                            p4cPosn = temp + 15;
                        }
                        else if(p2cPosn >= 15 && p4cPosn <= 15)
                        {
                            temp = p2cPosn;
                            p2cPosn = 60 + p4cPosn - 15;
                            p4cPosn = 15 - (60 - temp);
                        }
                        else if(p2cPosn <= 15 && p4cPosn <= 15)
                        {
                            temp = p2cPosn;
                            p2cPosn = 60 + p4cPosn - 15;
                            p4cPosn = temp + 15;
                        }
                        else if(p2cPosn <= 15 && p4cPosn >= 15)
                        {
                            p2cPosn = p4cPosn - 15;
                            p4cPosn = p4cPosn - (p2cPosn - 10);
                        }                       

                        //Determine if Player 1 has moved before their safe zone
                        if(p2cPosn == 8)
                        {
                            p2cPosn = 68;
                        }
                        else if(p2cPosn == 7)
                        {
                            p2cPosn = 67;
                        }
                        else if(p2cPosn == 6)
                        {
                            p2cPosn = 66;
                        }
                        else if(p2cPosn == 5)
                        {
                            p2cPosn = 65;
                        }
                        else if(p2cPosn == 4)
                        {
                            p2cPosn = 64;
                        }
                        else if(p2cPosn == 3)
                        {
                            p2cPosn = 63;
                        }
                        else if(p2cPosn == 2)
                        {
                            p2cPosn = 62;
                        }
                        else if(p2cPosn == 1)
                        {
                            p2cPosn = 61;
                        }
                        else if(p2cPosn == 0)
                        {
                            p2cPosn = 60;
                        }

                        //Determine if Player 4 has moved before their safe zone
                        if(p4cPosn == 8)
                        {
                            p4cPosn = 68;
                        }
                        else if(p4cPosn == 7)
                        {
                            p4cPosn = 67;
                        }
                        else if(p4cPosn == 6)
                        {
                            p4cPosn = 66;
                        }
                        else if(p4cPosn == 5)
                        {
                            p4cPosn = 65;
                        }
                        else if(p4cPosn == 4)
                        {
                            p4cPosn = 64;
                        }
                        else if(p4cPosn == 3)
                        {
                            p4cPosn = 63;
                        }
                        else if(p4cPosn == 2)
                        {
                            p4cPosn = 62;
                        }
                        else if(p4cPosn == 1)
                        {
                            p4cPosn = 61;
                        }
                        else if(p4cPosn == 0)
                        {
                            p4cPosn = 60;
                        }
                        cout << pTwoPos[p2cPosn] << endl;
                        cout << endl;
                        cout << pForPos[p4cPosn] << endl;
                        break;
                    case 5:
                        break;
                }
            }

            //Player 2 draws a "12"
            else if(card == 10)
            {
                //Print the card's specific menu
                cout << "You drew a 12!" << endl;
                cout << "1. Move 12 spaces forward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move 
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 2) || (pChoice == 1 && p2cPosn < 9) || (pChoice == 2 && p2cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p2cPosn += 12;
                        if(p2cPosn > 74)
                        {
                            p2cPosn = 74;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }      

            //Player 2 draws a "Sorry!" card
            else
            {
                //Print the card's specific menu
                cout << "You drew a \"Sorry!\" Card!" << endl;
                cout << "1. Move Player One's pawn off the game board" << endl;
                cout << "2. Move Player Three's pawn off the game board" << endl;
                cout << "3. Move Player Four's pawn off the game board" << endl;
                cout << "4. Skip turn" << endl;

                //Check for legal move 
                do
                {
                    if((pChoice > 4) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p3cPosn < 9) || (pChoice == 3 && p4cPosn < 9) ||
                      (pChoice == 4 && p1cPosn >= 9) || (pChoice == 4 && p3cPosn >= 9) || (pChoice == 4 && p4cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 4) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p3cPosn < 9) || (pChoice == 3 && p4cPosn < 9) ||
                       (pChoice == 4 && p1cPosn >= 9) || (pChoice == 4 && p3cPosn >= 9) || (pChoice == 4 && p4cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p1cPosn = 0;
                        cout << "\nPlayer 1 has been moved off the game board!" << endl;
                        cout << pOnePos[0] << endl;
                        break;
                    case 2:
                        p3cPosn = 0;
                        cout << "\nPlayer 3 has been moved off the game board!" << endl;
                        cout << pTrePos[0] << endl;
                        break;
                    case 3:
                        p4cPosn = 0;
                        cout << "\nPlayer 4 has been moved off the game board!" << endl;
                        cout << pForPos[0] << endl;
                        break;
                    case 4:
                        break;
                }
            }

            //Determine whether Player 2 has won the game
            if(p2cPosn == 74)
            {
                cout << "\nPlayer 2 has won the game!" << endl;
                restart = true;
            }
        }
        
        //Reset the player's choice
        pChoice = 0;
        
        //Begin Player 3's Turn
        if(restart == false)
        {
            cout << endl;
            cout << setw(25) << "PLAYER 3'S TURN:";
            cout << "\nPress the Enter key to draw a card! ";
            cin.ignore();
            cin.get();

            //generate a random card
            card = (rand() % 11) + 1;
            cout << endl;
            

            //Determine the card value and apply the rules
            //Player 3 draws a "1"
            if(card == 1)
            {
                //Print the card's specific menu
                cout << "You drew a 1!" << endl;
                cout << "1. Start" << endl;
                cout << "2. Move 1 space forward" << endl;
                cout << "3. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 3) || (pChoice == 1 && p3cPosn >= 9) || (pChoice == 2 && p3cPosn < 9) || (pChoice == 3))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);                
                }while((pChoice > 3) || (pChoice == 1 && p3cPosn >= 9) || (pChoice == 2 && p3cPosn < 9) || (pChoice == 3));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1: 
                        p3cPosn = 10;
                        cout << pTrePos[p3cPosn] << endl;   //Output modified game board
                        break;
                    case 2:
                        p3cPosn += 1;
                        cout << pTrePos[p3cPosn] << endl;    //Output modified game board
                        break;
                    case 3:
                        break;
                }
            }

            //Player 3 draws a "2"
            else if(card == 2)
            {
                //Print the card's specific menu
                cout << "You drew a 2!" << endl;
                cout << "1. Start" << endl;
                cout << "2. Move 2 spaces forward" << endl;
                cout << "3. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 3) || (pChoice == 1 && p3cPosn >= 9) || (pChoice == 1 && p3cPosn >= 9) || (pChoice == 3))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice); 
                }while((pChoice > 3) || (pChoice == 1 && p3cPosn >= 9) || (pChoice == 1 && p3cPosn >= 9) || (pChoice == 3));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p3cPosn = 10;
                        cout << pTrePos[p3cPosn] << endl;   //Output modified game board
                        break;
                    case 2:
                        p3cPosn += 2;
                        if(p3cPosn > 74)
                        {
                            p3cPosn = 74;
                        }
                        cout << pTrePos[p3cPosn] << endl;   //Output modified game board
                        break;
                    case 3:
                        break;
                }
            }

            //Player 3 draws a "3"
            else if(card == 3)
            {
                //Print the card's specific menu
                cout << "You drew a 3!" << endl;
                cout << "1. Move 3 spaces forward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move 
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p3cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);                    
                } while((pChoice > 2) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p3cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p3cPosn += 3;
                        if(p3cPosn > 74)
                        {
                            p3cPosn = 74;
                        }
                        cout << pTrePos[p3cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }

            //Player 3 draws a "4"
            else if(card == 4)
            {
                //Print the card's specific menu
                cout << "You drew a 4!" << endl;
                cout << "1. Move 4 spaces backward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p3cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 2) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p3cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p3cPosn -= 4;                       

                        //Determine if Player 1 has moved before their safe zone (P1-0 - P1-8)
                        if(p3cPosn == 8)
                        {
                            p3cPosn = 68;
                        }
                        else if(p3cPosn == 7)
                        {
                            p3cPosn = 67;
                        }
                        else if(p3cPosn == 6)
                        {
                            p3cPosn = 66;
                        }
                        else if(p3cPosn == 5)
                        {
                            p3cPosn = 65;
                        }
                        else if(p3cPosn == 4)
                        {
                            p3cPosn = 64;
                        }
                        else if(p3cPosn == 3)
                        {
                            p3cPosn = 63;
                        }
                        else if(p3cPosn == 2)
                        {
                            p3cPosn = 62;
                        }
                        else if(p3cPosn == 1)
                        {
                            p3cPosn = 61;
                        }
                        else if(p3cPosn == 0)
                        {
                            p3cPosn = 60;
                        }
                        cout << pTrePos[p3cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }

            //Player 3 draws a "5"
            else if(card == 5)
            {
                //Print the card's specific menu
                cout << "You drew a 5!" << endl;
                cout << "1. Move 5 spaces forward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p3cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);  
                } while((pChoice > 2) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p3cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p3cPosn += 5;
                        if(p3cPosn > 74)
                        {
                            p3cPosn = 74;
                        }
                        cout << pTrePos[p3cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }

            //Player 3 draws a "7"
            else if(card == 6)
            {
                //Print the card's specific menu
                cout << "You drew a 7!" << endl;
                cout << "1. Move 7 spaces forward" << endl;
                cout << "2. Move Player One 7 spaces backward" << endl;
                cout << "3. Move Player Two 7 spaces backward" << endl;
                cout << "4. Move Player Four 7 spaces backward" << endl;
                cout << "5. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 5) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p1cPosn < 9) ||
                      (pChoice == 3 && p2cPosn < 9) || (pChoice == 4 && p4cPosn < 9) || (pChoice == 5 && p3cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 5) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p1cPosn < 9) ||
                       (pChoice == 3 && p2cPosn < 9) || (pChoice == 4 && p4cPosn < 9) || (pChoice == 5 && p3cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p3cPosn += 7;
                        if(p3cPosn > 74)
                        {
                            p3cPosn = 74;
                        }
                        cout << pTrePos[p3cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        p1cPosn -= 7;                       

                        //Determine if Player 1 has moved before their safe zone
                        if(p1cPosn == 8)
                        {
                            p1cPosn = 68;
                        }
                        else if(p1cPosn == 7)
                        {
                            p1cPosn = 67;
                        }
                        else if(p1cPosn == 6)
                        {
                            p1cPosn = 66;
                        }
                        else if(p1cPosn == 5)
                        {
                            p1cPosn = 65;
                        }
                        else if(p1cPosn == 4)
                        {
                            p1cPosn = 64;
                        }
                        else if(p1cPosn == 3)
                        {
                            p1cPosn = 63;
                        }
                        else if(p1cPosn == 2)
                        {
                            p1cPosn = 62;
                        }
                        else if(p1cPosn == 1)
                        {
                            p1cPosn = 61;
                        }
                        else if(p1cPosn == 0)
                        {
                            p1cPosn = 60;
                        }
                        cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                        break;
                    case 3:
                        p2cPosn -= 7;                       

                        //Determine if Player 3 has moved before their safe zone
                        if(p2cPosn == 8)
                        {
                            p2cPosn = 68;
                        }
                        else if(p2cPosn == 7)
                        {
                            p2cPosn = 67;
                        }
                        else if(p2cPosn == 6)
                        {
                            p2cPosn = 66;
                        }
                        else if(p2cPosn == 5)
                        {
                            p2cPosn = 65;
                        }
                        else if(p2cPosn == 4)
                        {
                            p2cPosn = 64;
                        }
                        else if(p2cPosn == 3)
                        {
                            p2cPosn = 63;
                        }
                        else if(p2cPosn == 2)
                        {
                            p2cPosn = 62;
                        }
                        else if(p2cPosn == 1)
                        {
                            p2cPosn = 61;
                        }
                        else if(p2cPosn == 0)
                        {
                            p2cPosn = 60;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 4:
                        p4cPosn -= 7;                       

                        //Determine if Player 4 has moved before their safe zone
                        if(p4cPosn == 8)
                        {
                            p4cPosn = 68;
                        }
                        else if(p4cPosn == 7)
                        {
                            p4cPosn = 67;
                        }
                        else if(p4cPosn == 6)
                        {
                            p4cPosn = 66;
                        }
                        else if(p4cPosn == 5)
                        {
                            p4cPosn = 65;
                        }
                        else if(p4cPosn == 4)
                        {
                            p4cPosn = 64;
                        }
                        else if(p4cPosn == 3)
                        {
                            p4cPosn = 63;
                        }
                        else if(p4cPosn == 2)
                        {
                            p4cPosn = 62;
                        }
                        else if(p4cPosn == 1)
                        {
                            p4cPosn = 61;
                        }
                        else if(p4cPosn == 0)
                        {
                            p4cPosn = 60;
                        }
                        cout << pForPos[p4cPosn] << endl;    //Output modified game board
                        break;
                    case 5:
                        break;
                }
            }

            //Player 3 draws an "8"
            else if(card == 7)
            {
                //Print the card's specific menu
                cout << "You drew an 8!" << endl;
                cout << "1. Move 8 spaces forward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p3cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);                
                } while((pChoice > 2) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p3cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p3cPosn += 8;
                        if(p3cPosn > 74)
                        {
                            p3cPosn = 74;
                        }
                        cout << pTrePos[p3cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }

            //Player 3 draws a "10"
            else if(card == 8)
            {
                //Print the card's specific menu
                cout << "You drew a 10!" << endl;
                cout << "1. Move 10 spaces forward" << endl;
                cout << "2. Move 1 space backward" << endl;
                cout << "3. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 3) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p3cPosn < 9) || (pChoice == 3 && p3cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);                   
                }while((pChoice > 3) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p3cPosn < 9) || (pChoice == 3 && p3cPosn >= 9));           

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p3cPosn += 10;
                        if(p3cPosn > 74)
                        {
                            p3cPosn = 74;
                        }
                        cout << pTrePos[p3cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        p3cPosn -= 1;                        

                        //Determine if Player 1 has moved before their safe zone (P1-0 - P1-8)
                        if(p3cPosn == 8)
                        {
                            p3cPosn = 68;
                        }
                        else if(p3cPosn == 7)
                        {
                            p3cPosn = 67;
                        }
                        else if(p3cPosn == 6)
                        {
                            p3cPosn = 66;
                        }
                        else if(p3cPosn == 5)
                        {
                            p3cPosn = 65;
                        }
                        else if(p3cPosn == 4)
                        {
                            p3cPosn = 64;
                        }
                        else if(p3cPosn == 3)
                        {
                            p3cPosn = 63;
                        }
                        else if(p3cPosn == 2)
                        {
                            p3cPosn = 62;
                        }
                        else if(p3cPosn == 1)
                        {
                            p3cPosn = 61;
                        }
                        else if(p3cPosn == 0)
                        {
                            p3cPosn = 60;
                        }
                        cout << pTrePos[p3cPosn] << endl;    //Output modified game board
                        break;
                    case 3:
                        break;
                }
            }

            //Player 3 draws an "11"
            else if(card == 9)
            {
                //Print the card's specific menu
                cout << "You drew an 11!" << endl;
                cout << "1. Move 11 spaces forward" << endl;
                cout << "2. Switch places with Player One's pawn" << endl;
                cout << "3. Switch places with Player Two's pawn" << endl;
                cout << "4. Switch places with Player Four's pawn" << endl;
                cout << "5. Skip turn" << endl;

                //Check for legal move 
                do
                {
                    if((pChoice > 5) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p3cPosn < 9) ||
                      (pChoice == 2 && p1cPosn < 9) || (pChoice == 3 && p3cPosn < 9) || (pChoice == 3 && p2cPosn < 9) ||
                      (pChoice == 4 && p3cPosn < 9) || (pChoice == 4 && p4cPosn < 9) || (pChoice == 4 && p3cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 5) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p3cPosn < 9) ||
                       (pChoice == 2 && p1cPosn < 9) || (pChoice == 3 && p3cPosn < 9) || (pChoice == 3 && p2cPosn < 9) ||
                       (pChoice == 4 && p3cPosn < 9) || (pChoice == 4 && p4cPosn < 9) || (pChoice == 4 && p3cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p3cPosn += 11;
                        if(p3cPosn > 74)
                        {
                            p3cPosn = 74;
                        }
                        cout << pTrePos[p3cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        if(p3cPosn >= 15 && p1cPosn >= 15)
                        {
                            temp = p3cPosn;
                            p3cPosn = p1cPosn - 15;
                            p1cPosn = temp + 15;
                        }
                        else if(p3cPosn >= 15 && p1cPosn <= 15)
                        {
                            temp = p3cPosn;
                            p3cPosn = 60 + p1cPosn - 15;
                            p1cPosn = 15 - (60 - temp);
                        }
                        else if(p3cPosn <= 15 && p1cPosn <= 15)
                        {
                            temp = p3cPosn;
                            p3cPosn = 60 + p1cPosn - 15;
                            p1cPosn = temp + 15;
                        }
                        else if(p3cPosn <= 15 && p1cPosn >= 15)
                        {
                            p3cPosn = p1cPosn - 15;
                            p1cPosn = p1cPosn - (p3cPosn - 10);
                        }                       

                        //Determine if Player 2 has moved before their safe zone
                        if(p3cPosn == 8)
                        {
                            p3cPosn = 68;
                        }
                        else if(p3cPosn == 7)
                        {
                            p3cPosn = 67;
                        }
                        else if(p3cPosn == 6)
                        {
                            p3cPosn = 66;
                        }
                        else if(p3cPosn == 5)
                        {
                            p3cPosn = 65;
                        }
                        else if(p3cPosn == 4)
                        {
                            p3cPosn = 64;
                        }
                        else if(p3cPosn == 3)
                        {
                            p3cPosn = 63;
                        }
                        else if(p3cPosn == 2)
                        {
                            p3cPosn = 62;
                        }
                        else if(p3cPosn == 1)
                        {
                            p3cPosn = 61;
                        }
                        else if(p3cPosn == 0)
                        {
                            p3cPosn = 60;
                        }

                        //Determine if Player 2 has moved before their safe zone
                        if(p1cPosn == 8)
                        {
                            p1cPosn = 68;
                        }
                        else if(p1cPosn == 7)
                        {
                            p1cPosn = 67;
                        }
                        else if(p1cPosn == 6)
                        {
                            p1cPosn = 66;
                        }
                        else if(p1cPosn == 5)
                        {
                            p1cPosn = 65;
                        }
                        else if(p1cPosn == 4)
                        {
                            p1cPosn = 64;
                        }
                        else if(p1cPosn == 3)
                        {
                            p1cPosn = 63;
                        }
                        else if(p1cPosn == 2)
                        {
                            p1cPosn = 62;
                        }
                        else if(p1cPosn == 1)
                        {
                            p1cPosn = 61;
                        }
                        else if(p1cPosn == 0)
                        {
                            p1cPosn = 60;
                        }
                        cout << pTrePos[p3cPosn] << endl;
                        cout << endl;
                        cout << pOnePos[p1cPosn] << endl;
                        break;
                    case 3:
                        if(p3cPosn >= 15 && p2cPosn >= 15)
                        {
                            temp = p3cPosn;
                            p3cPosn = p2cPosn - 15;
                            p2cPosn = temp + 15;
                        }
                        else if(p3cPosn >= 15 && p2cPosn <= 15)
                        {
                            temp = p3cPosn;
                            p3cPosn = 60 + p2cPosn - 15;
                            p2cPosn = 15 - (60 - temp);
                        }
                        else if(p3cPosn <= 15 && p2cPosn <= 15)
                        {
                            temp = p3cPosn;
                            p3cPosn = 60 + p2cPosn - 15;
                            p2cPosn = temp + 15;
                        }
                        else if(p3cPosn <= 15 && p2cPosn >= 15)
                        {
                            p3cPosn = p2cPosn - 15;
                            p2cPosn = p2cPosn - (p3cPosn - 10);
                        }                       

                        //Determine if Player 2 has moved before their safe zone
                        if(p3cPosn == 8)
                        {
                            p3cPosn = 68;
                        }
                        else if(p3cPosn == 7)
                        {
                            p3cPosn = 67;
                        }
                        else if(p3cPosn == 6)
                        {
                            p3cPosn = 66;
                        }
                        else if(p3cPosn == 5)
                        {
                            p3cPosn = 65;
                        }
                        else if(p3cPosn == 4)
                        {
                            p3cPosn = 64;
                        }
                        else if(p3cPosn == 3)
                        {
                            p3cPosn = 63;
                        }
                        else if(p3cPosn == 2)
                        {
                            p3cPosn = 62;
                        }
                        else if(p3cPosn == 1)
                        {
                            p3cPosn = 61;
                        }
                        else if(p3cPosn == 0)
                        {
                            p3cPosn = 60;
                        }

                        //Determine if Player 3 has moved before their safe zone
                        if(p2cPosn == 8)
                        {
                            p2cPosn = 68;
                        }
                        else if(p2cPosn == 7)
                        {
                            p2cPosn = 67;
                        }
                        else if(p2cPosn == 6)
                        {
                            p2cPosn = 66;
                        }
                        else if(p2cPosn == 5)
                        {
                            p2cPosn = 65;
                        }
                        else if(p2cPosn == 4)
                        {
                            p2cPosn = 64;
                        }
                        else if(p2cPosn == 3)
                        {
                            p2cPosn = 63;
                        }
                        else if(p2cPosn == 2)
                        {
                            p2cPosn = 62;
                        }
                        else if(p2cPosn == 1)
                        {
                            p2cPosn = 61;
                        }
                        else if(p2cPosn == 0)
                        {
                            p2cPosn = 60;
                        }
                        cout << pTrePos[p3cPosn] << endl;
                        cout << endl;
                        cout << pTwoPos[p2cPosn] << endl;
                        break;
                    case 4:
                        if(p3cPosn >= 15 && p4cPosn >= 15)
                        {
                            temp = p3cPosn;
                            p3cPosn = p4cPosn - 15;
                            p4cPosn = temp + 15;
                        }
                        else if(p3cPosn >= 15 && p4cPosn <= 15)
                        {
                            temp = p3cPosn;
                            p3cPosn = 60 + p4cPosn - 15;
                            p4cPosn = 15 - (60 - temp);
                        }
                        else if(p3cPosn <= 15 && p4cPosn <= 15)
                        {
                            temp = p3cPosn;
                            p3cPosn = 60 + p4cPosn - 15;
                            p4cPosn = temp + 15;
                        }
                        else if(p3cPosn <= 15 && p4cPosn >= 15)
                        {
                            p3cPosn = p4cPosn - 15;
                            p4cPosn = p4cPosn - (p3cPosn - 10);
                        }                       

                        //Determine if Player 1 has moved before their safe zone
                        if(p3cPosn == 8)
                        {
                            p3cPosn = 68;
                        }
                        else if(p3cPosn == 7)
                        {
                            p3cPosn = 67;
                        }
                        else if(p3cPosn == 6)
                        {
                            p3cPosn = 66;
                        }
                        else if(p3cPosn == 5)
                        {
                            p3cPosn = 65;
                        }
                        else if(p3cPosn == 4)
                        {
                            p3cPosn = 64;
                        }
                        else if(p3cPosn == 3)
                        {
                            p3cPosn = 63;
                        }
                        else if(p3cPosn == 2)
                        {
                            p3cPosn = 62;
                        }
                        else if(p3cPosn == 1)
                        {
                            p3cPosn = 61;
                        }
                        else if(p3cPosn == 0)
                        {
                            p3cPosn = 60;
                        }

                        //Determine if Player 4 has moved before their safe zone
                        if(p4cPosn == 8)
                        {
                            p4cPosn = 68;
                        }
                        else if(p4cPosn == 7)
                        {
                            p4cPosn = 67;
                        }
                        else if(p4cPosn == 6)
                        {
                            p4cPosn = 66;
                        }
                        else if(p4cPosn == 5)
                        {
                            p4cPosn = 65;
                        }
                        else if(p4cPosn == 4)
                        {
                            p4cPosn = 64;
                        }
                        else if(p4cPosn == 3)
                        {
                            p4cPosn = 63;
                        }
                        else if(p4cPosn == 2)
                        {
                            p4cPosn = 62;
                        }
                        else if(p4cPosn == 1)
                        {
                            p4cPosn = 61;
                        }
                        else if(p4cPosn == 0)
                        {
                            p4cPosn = 60;
                        }
                        cout << pTrePos[p3cPosn] << endl;
                        cout << endl;
                        cout << pForPos[p4cPosn] << endl;
                        break;
                    case 5:
                        break;
                }
            }

            //Player 3 draws a "12"
            else if(card == 10)
            {
                //Print the card's specific menu
                cout << "You drew a 12!" << endl;
                cout << "1. Move 12 spaces forward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move 
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p3cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 2) || (pChoice == 1 && p3cPosn < 9) || (pChoice == 2 && p3cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p3cPosn += 12;
                        if(p3cPosn > 74)
                        {
                            p3cPosn = 74;
                        }
                        cout << pTrePos[p3cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }      

            //Player 3 draws a "Sorry!" card
            else
            {
                //Print the card's specific menu
                cout << "You drew a \"Sorry!\" Card!" << endl;
                cout << "1. Move Player One's pawn off the game board" << endl;
                cout << "2. Move Player Two's pawn off the game board" << endl;
                cout << "3. Move Player Four's pawn off the game board" << endl;
                cout << "4. Skip turn" << endl;

                //Check for legal move 
                do
                {
                    if((pChoice > 4) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p2cPosn < 9) || (pChoice == 3 && p4cPosn < 9) ||
                      (pChoice == 4 && p1cPosn >= 9) || (pChoice == 4 && p2cPosn >= 9) || (pChoice == 4 && p4cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 4) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p2cPosn < 9) || (pChoice == 3 && p4cPosn < 9) ||
                       (pChoice == 4 && p1cPosn >= 9) || (pChoice == 4 && p2cPosn >= 9) || (pChoice == 4 && p4cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p1cPosn = 0;
                        cout << "\nPlayer 1 has been moved off the game board!" << endl;
                        cout << pOnePos[0] << endl;
                        break;
                    case 2:
                        p2cPosn = 0;
                        cout << "\nPlayer 2 has been moved off the game board!" << endl;
                        cout << pTwoPos[0] << endl;
                        break;
                    case 3:
                        p4cPosn = 0;
                        cout << "\nPlayer 4 has been moved off the game board!" << endl;
                        cout << pForPos[0] << endl;
                        break;
                    case 4:
                        break;
                }
            }

            //Determine whether Player 3 has won the game
            if(p3cPosn == 74)
            {
                cout << "\nPlayer 3 has won the game!" << endl;
                restart = true;
            }
        }
        
        //Reset the player's choice
        pChoice = 0;
        
        //Begin Player 4's Turn
        if(restart == false)
        {
            cout << endl;
            cout << setw(25) << "PLAYER 4'S TURN:";
            cout << "\nPress the Enter key to draw a card! ";
            cin.ignore();
            cin.get();

            //generate a random card
            card = (rand() % 11) + 1;
            cout << endl;

            //Determine the card value and apply the rules
            //Player 4 draws a "1"
            if(card == 1)
            {
                //Print the card's specific menu
                cout << "You drew a 1!" << endl;
                cout << "1. Start" << endl;
                cout << "2. Move 1 space forward" << endl;
                cout << "3. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 3) || (pChoice == 1 && p4cPosn >= 9) || (pChoice == 2 && p4cPosn < 9) || (pChoice == 3))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);                
                }while((pChoice > 3) || (pChoice == 1 && p4cPosn >= 9) || (pChoice == 2 && p4cPosn < 9) || (pChoice == 3));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1: 
                        p4cPosn = 10;
                        cout << pForPos[p4cPosn] << endl;   //Output modified game board
                        break;
                    case 2:
                        p4cPosn += 1;
                        cout << pForPos[p4cPosn] << endl;    //Output modified game board
                        break;
                    case 3:
                        break;
                }
            }

            //Player 4 draws a "2"
            else if(card == 2)
            {
                //Print the card's specific menu
                cout << "You drew a 2!" << endl;
                cout << "1. Start" << endl;
                cout << "2. Move 2 spaces forward" << endl;
                cout << "3. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 3) || (pChoice == 1 && p4cPosn >= 9) || (pChoice == 1 && p4cPosn >= 9) || (pChoice == 3))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice); 
                }while((pChoice > 3) || (pChoice == 1 && p4cPosn >= 9) || (pChoice == 1 && p4cPosn >= 9) || (pChoice == 3));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p4cPosn = 10;
                        cout << pForPos[p4cPosn] << endl;   //Output modified game board
                        break;
                    case 2:
                        p4cPosn += 2;
                        if(p4cPosn > 74)
                        {
                            p4cPosn = 74;
                        }
                        cout << pForPos[p4cPosn] << endl;   //Output modified game board
                        break;
                    case 3:
                        break;
                }
            }

            //Player 4 draws a "3"
            else if(card == 3)
            {
                //Print the card's specific menu
                cout << "You drew a 3!" << endl;
                cout << "1. Move 3 spaces forward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move 
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p4cPosn < 9) || (pChoice == 2 && p4cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);                    
                } while((pChoice > 2) || (pChoice == 1 && p4cPosn < 9) || (pChoice == 2 && p4cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p4cPosn += 3;
                        if(p4cPosn > 74)
                        {
                            p4cPosn = 74;
                        }
                        cout << pForPos[p4cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }

            //Player 4 draws a "4"
            else if(card == 4)
            {
                //Print the card's specific menu
                cout << "You drew a 4!" << endl;
                cout << "1. Move 4 spaces backward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p4cPosn < 9) || (pChoice == 2 && p4cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 2) || (pChoice == 1 && p4cPosn < 9) || (pChoice == 2 && p4cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p4cPosn -= 4;                       

                        //Determine if Player 1 has moved before their safe zone (P1-0 - P1-8)
                        if(p4cPosn == 8)
                        {
                            p4cPosn = 68;
                        }
                        else if(p4cPosn == 7)
                        {
                            p4cPosn = 67;
                        }
                        else if(p4cPosn == 6)
                        {
                            p4cPosn = 66;
                        }
                        else if(p4cPosn == 5)
                        {
                            p4cPosn = 65;
                        }
                        else if(p4cPosn == 4)
                        {
                            p4cPosn = 64;
                        }
                        else if(p4cPosn == 3)
                        {
                            p4cPosn = 63;
                        }
                        else if(p4cPosn == 2)
                        {
                            p4cPosn = 62;
                        }
                        else if(p4cPosn == 1)
                        {
                            p4cPosn = 61;
                        }
                        else if(p4cPosn == 0)
                        {
                            p4cPosn = 60;
                        }
                        cout << pForPos[p4cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }

            //Player 4 draws a "5"
            else if(card == 5)
            {
                //Print the card's specific menu
                cout << "You drew a 5!" << endl;
                cout << "1. Move 5 spaces forward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p4cPosn < 9) || (pChoice == 2 && p4cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);  
                } while((pChoice > 2) || (pChoice == 1 && p4cPosn < 9) || (pChoice == 2 && p4cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p4cPosn += 5;
                        if(p4cPosn > 74)
                        {
                            p4cPosn = 74;
                        }
                        cout << pForPos[p4cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }

            //Player 4 draws a "7"
            else if(card == 6)
            {
                //Print the card's specific menu
                cout << "You drew a 7!" << endl;
                cout << "1. Move 7 spaces forward" << endl;
                cout << "2. Move Player One 7 spaces backward" << endl;
                cout << "3. Move Player Two 7 spaces backward" << endl;
                cout << "4. Move Player Three 7 spaces backward" << endl;
                cout << "5. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 5) || (pChoice == 1 && p4cPosn < 9) || (pChoice == 2 && p1cPosn < 9) ||
                      (pChoice == 3 && p2cPosn < 9) || (pChoice == 4 && p3cPosn < 9) || (pChoice == 5 && p4cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 5) || (pChoice == 1 && p4cPosn < 9) || (pChoice == 2 && p1cPosn < 9) ||
                       (pChoice == 3 && p2cPosn < 9) || (pChoice == 4 && p3cPosn < 9) || (pChoice == 5 && p4cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p4cPosn += 7;
                        if(p4cPosn > 74)
                        {
                            p4cPosn = 74;
                        }
                        cout << pForPos[p4cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        p1cPosn -= 7;                       

                        //Determine if Player 1 has moved before their safe zone
                        if(p1cPosn == 8)
                        {
                            p1cPosn = 68;
                        }
                        else if(p1cPosn == 7)
                        {
                            p1cPosn = 67;
                        }
                        else if(p1cPosn == 6)
                        {
                            p1cPosn = 66;
                        }
                        else if(p1cPosn == 5)
                        {
                            p1cPosn = 65;
                        }
                        else if(p1cPosn == 4)
                        {
                            p1cPosn = 64;
                        }
                        else if(p1cPosn == 3)
                        {
                            p1cPosn = 63;
                        }
                        else if(p1cPosn == 2)
                        {
                            p1cPosn = 62;
                        }
                        else if(p1cPosn == 1)
                        {
                            p1cPosn = 61;
                        }
                        else if(p1cPosn == 0)
                        {
                            p1cPosn = 60;
                        }
                        cout << pOnePos[p1cPosn] << endl;    //Output modified game board
                        break;
                    case 3:
                        p2cPosn -= 7;                       

                        //Determine if Player 3 has moved before their safe zone
                        if(p2cPosn == 8)
                        {
                            p2cPosn = 68;
                        }
                        else if(p2cPosn == 7)
                        {
                            p2cPosn = 67;
                        }
                        else if(p2cPosn == 6)
                        {
                            p2cPosn = 66;
                        }
                        else if(p2cPosn == 5)
                        {
                            p2cPosn = 65;
                        }
                        else if(p2cPosn == 4)
                        {
                            p2cPosn = 64;
                        }
                        else if(p2cPosn == 3)
                        {
                            p2cPosn = 63;
                        }
                        else if(p2cPosn == 2)
                        {
                            p2cPosn = 62;
                        }
                        else if(p2cPosn == 1)
                        {
                            p2cPosn = 61;
                        }
                        else if(p2cPosn == 0)
                        {
                            p2cPosn = 60;
                        }
                        cout << pTwoPos[p2cPosn] << endl;    //Output modified game board
                        break;
                    case 4:
                        p3cPosn -= 7;                       

                        //Determine if Player 4 has moved before their safe zone
                        if(p3cPosn == 8)
                        {
                            p3cPosn = 68;
                        }
                        else if(p3cPosn == 7)
                        {
                            p3cPosn = 67;
                        }
                        else if(p3cPosn == 6)
                        {
                            p3cPosn = 66;
                        }
                        else if(p3cPosn == 5)
                        {
                            p3cPosn = 65;
                        }
                        else if(p3cPosn == 4)
                        {
                            p3cPosn = 64;
                        }
                        else if(p3cPosn == 3)
                        {
                            p3cPosn = 63;
                        }
                        else if(p3cPosn == 2)
                        {
                            p3cPosn = 62;
                        }
                        else if(p3cPosn == 1)
                        {
                            p3cPosn = 61;
                        }
                        else if(p3cPosn == 0)
                        {
                            p3cPosn = 60;
                        }
                        cout << pTrePos[p3cPosn] << endl;    //Output modified game board
                        break;
                    case 5:
                        break;
                }
            }

            //Player 4 draws an "8"
            else if(card == 7)
            {
                //Print the card's specific menu
                cout << "You drew an 8!" << endl;
                cout << "1. Move 8 spaces forward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p4cPosn < 9) || (pChoice == 2 && p4cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);                
                } while((pChoice > 2) || (pChoice == 1 && p4cPosn < 9) || (pChoice == 2 && p4cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p4cPosn += 8;
                        if(p4cPosn > 74)
                        {
                            p4cPosn = 74;
                        }
                        cout << pForPos[p4cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }

            //Player 4 draws a "10"
            else if(card == 8)
            {
                //Print the card's specific menu
                cout << "You drew a 10!" << endl;
                cout << "1. Move 10 spaces forward" << endl;
                cout << "2. Move 1 space backward" << endl;
                cout << "3. Skip turn" << endl;

                //Check for legal move
                do
                {
                    if((pChoice > 3) || (pChoice == 1 && p4cPosn < 9) || (pChoice == 2 && p4cPosn < 9) || (pChoice == 3 && p4cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);                   
                }while((pChoice > 3) || (pChoice == 1 && p4cPosn < 9) || (pChoice == 2 && p4cPosn < 9) || (pChoice == 3 && p4cPosn >= 9));           

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p4cPosn += 10;
                        if(p4cPosn > 74)
                        {
                            p4cPosn = 74;
                        }
                        cout << pForPos[p4cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        p4cPosn -= 1;                        

                        //Determine if Player 1 has moved before their safe zone (P1-0 - P1-8)
                        if(p4cPosn == 8)
                        {
                            p4cPosn = 68;
                        }
                        else if(p4cPosn == 7)
                        {
                            p4cPosn = 67;
                        }
                        else if(p4cPosn == 6)
                        {
                            p4cPosn = 66;
                        }
                        else if(p4cPosn == 5)
                        {
                            p4cPosn = 65;
                        }
                        else if(p4cPosn == 4)
                        {
                            p4cPosn = 64;
                        }
                        else if(p4cPosn == 3)
                        {
                            p4cPosn = 63;
                        }
                        else if(p4cPosn == 2)
                        {
                            p4cPosn = 62;
                        }
                        else if(p4cPosn == 1)
                        {
                            p4cPosn = 61;
                        }
                        else if(p4cPosn == 0)
                        {
                            p4cPosn = 60;
                        }
                        cout << pForPos[p4cPosn] << endl;    //Output modified game board
                        break;
                    case 3:
                        break;
                }
            }

            //Player 4 draws an "11"
            else if(card == 9)
            {
                //Print the card's specific menu
                cout << "You drew an 11!" << endl;
                cout << "1. Move 11 spaces forward" << endl;
                cout << "2. Switch places with Player One's pawn" << endl;
                cout << "3. Switch places with Player Two's pawn" << endl;
                cout << "4. Switch places with Player Three's pawn" << endl;
                cout << "5. Skip turn" << endl;

                //Check for legal move 
                do
                {
                    if((pChoice > 5) || (pChoice == 1 && p4cPosn < 9) || (pChoice == 2 && p4cPosn < 9) ||
                      (pChoice == 2 && p1cPosn < 9) || (pChoice == 3 && p4cPosn < 9) || (pChoice == 3 && p2cPosn < 9) ||
                      (pChoice == 4 && p4cPosn < 9) || (pChoice == 4 && p3cPosn < 9) || (pChoice == 4 && p4cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 5) || (pChoice == 1 && p4cPosn < 9) || (pChoice == 2 && p4cPosn < 9) ||
                       (pChoice == 2 && p1cPosn < 9) || (pChoice == 3 && p4cPosn < 9) || (pChoice == 3 && p2cPosn < 9) ||
                       (pChoice == 4 && p4cPosn < 9) || (pChoice == 4 && p3cPosn < 9) || (pChoice == 4 && p4cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p4cPosn += 11;
                        if(p4cPosn > 74)
                        {
                            p4cPosn = 74;
                        }
                        cout << pForPos[p4cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        if(p4cPosn >= 15 && p1cPosn >= 15)
                        {
                            temp = p4cPosn;
                            p4cPosn = p1cPosn - 15;
                            p1cPosn = temp + 15;
                        }
                        else if(p4cPosn >= 15 && p1cPosn <= 15)
                        {
                            temp = p4cPosn;
                            p4cPosn = 60 + p1cPosn - 15;
                            p1cPosn = 15 - (60 - temp);
                        }
                        else if(p4cPosn <= 15 && p1cPosn <= 15)
                        {
                            temp = p4cPosn;
                            p4cPosn = 60 + p1cPosn - 15;
                            p1cPosn = temp + 15;
                        }
                        else if(p4cPosn <= 15 && p1cPosn >= 15)
                        {
                            p4cPosn = p1cPosn - 15;
                            p1cPosn = p1cPosn - (p4cPosn - 10);
                        }                       

                        //Determine if Player 4 has moved before their safe zone
                        if(p4cPosn == 8)
                        {
                            p4cPosn = 68;
                        }
                        else if(p4cPosn == 7)
                        {
                            p4cPosn = 67;
                        }
                        else if(p4cPosn == 6)
                        {
                            p4cPosn = 66;
                        }
                        else if(p4cPosn == 5)
                        {
                            p4cPosn = 65;
                        }
                        else if(p4cPosn == 4)
                        {
                            p4cPosn = 64;
                        }
                        else if(p4cPosn == 3)
                        {
                            p4cPosn = 63;
                        }
                        else if(p4cPosn == 2)
                        {
                            p4cPosn = 62;
                        }
                        else if(p4cPosn == 1)
                        {
                            p4cPosn = 61;
                        }
                        else if(p4cPosn == 0)
                        {
                            p4cPosn = 60;
                        }

                        //Determine if Player 1 has moved before their safe zone
                        if(p1cPosn == 8)
                        {
                            p1cPosn = 68;
                        }
                        else if(p1cPosn == 7)
                        {
                            p1cPosn = 67;
                        }
                        else if(p1cPosn == 6)
                        {
                            p1cPosn = 66;
                        }
                        else if(p1cPosn == 5)
                        {
                            p1cPosn = 65;
                        }
                        else if(p1cPosn == 4)
                        {
                            p1cPosn = 64;
                        }
                        else if(p1cPosn == 3)
                        {
                            p1cPosn = 63;
                        }
                        else if(p1cPosn == 2)
                        {
                            p1cPosn = 62;
                        }
                        else if(p1cPosn == 1)
                        {
                            p1cPosn = 61;
                        }
                        else if(p1cPosn == 0)
                        {
                            p1cPosn = 60;
                        }
                        cout << pForPos[p4cPosn] << endl;
                        cout << endl;
                        cout << pOnePos[p1cPosn] << endl;
                        break;
                    case 3:
                        if(p4cPosn >= 15 && p2cPosn >= 15)
                        {
                            temp = p4cPosn;
                            p4cPosn = p2cPosn - 15;
                            p2cPosn = temp + 15;
                        }
                        else if(p4cPosn >= 15 && p2cPosn <= 15)
                        {
                            temp = p4cPosn;
                            p4cPosn = 60 + p2cPosn - 15;
                            p2cPosn = 15 - (60 - temp);
                        }
                        else if(p4cPosn <= 15 && p2cPosn <= 15)
                        {
                            temp = p4cPosn;
                            p4cPosn = 60 + p2cPosn - 15;
                            p2cPosn = temp + 15;
                        }
                        else if(p4cPosn <= 15 && p2cPosn >= 15)
                        {
                            p4cPosn = p2cPosn - 15;
                            p2cPosn = p2cPosn - (p4cPosn - 10);
                        }                       

                        //Determine if Player 4 has moved before their safe zone
                        if(p4cPosn == 8)
                        {
                            p4cPosn = 68;
                        }
                        else if(p4cPosn == 7)
                        {
                            p4cPosn = 67;
                        }
                        else if(p4cPosn == 6)
                        {
                            p4cPosn = 66;
                        }
                        else if(p4cPosn == 5)
                        {
                            p4cPosn = 65;
                        }
                        else if(p4cPosn == 4)
                        {
                            p4cPosn = 64;
                        }
                        else if(p4cPosn == 3)
                        {
                            p4cPosn = 63;
                        }
                        else if(p4cPosn == 2)
                        {
                            p4cPosn = 62;
                        }
                        else if(p4cPosn == 1)
                        {
                            p4cPosn = 61;
                        }
                        else if(p4cPosn == 0)
                        {
                            p4cPosn = 60;
                        }

                        //Determine if Player 2 has moved before their safe zone
                        if(p2cPosn == 8)
                        {
                            p2cPosn = 68;
                        }
                        else if(p2cPosn == 7)
                        {
                            p2cPosn = 67;
                        }
                        else if(p2cPosn == 6)
                        {
                            p2cPosn = 66;
                        }
                        else if(p2cPosn == 5)
                        {
                            p2cPosn = 65;
                        }
                        else if(p2cPosn == 4)
                        {
                            p2cPosn = 64;
                        }
                        else if(p2cPosn == 3)
                        {
                            p2cPosn = 63;
                        }
                        else if(p2cPosn == 2)
                        {
                            p2cPosn = 62;
                        }
                        else if(p2cPosn == 1)
                        {
                            p2cPosn = 61;
                        }
                        else if(p2cPosn == 0)
                        {
                            p2cPosn = 60;
                        }
                        cout << pForPos[p4cPosn] << endl;
                        cout << endl;
                        cout << pTwoPos[p2cPosn] << endl;
                        break;
                    case 4:
                        if(p4cPosn >= 15 && p3cPosn >= 15)
                        {
                            temp = p4cPosn;
                            p4cPosn = p3cPosn - 15;
                            p3cPosn = temp + 15;
                        }
                        else if(p4cPosn >= 15 && p3cPosn <= 15)
                        {
                            temp = p4cPosn;
                            p4cPosn = 60 + p3cPosn - 15;
                            p3cPosn = 15 - (60 - temp);
                        }
                        else if(p4cPosn <= 15 && p3cPosn <= 15)
                        {
                            temp = p4cPosn;
                            p4cPosn = 60 + p3cPosn - 15;
                            p3cPosn = temp + 15;
                        }
                        else if(p4cPosn <= 15 && p3cPosn >= 15)
                        {
                            p4cPosn = p3cPosn - 15;
                            p3cPosn = p3cPosn - (p4cPosn - 10);
                        }                       

                        //Determine if Player 4 has moved before their safe zone
                        if(p4cPosn == 8)
                        {
                            p4cPosn = 68;
                        }
                        else if(p4cPosn == 7)
                        {
                            p4cPosn = 67;
                        }
                        else if(p4cPosn == 6)
                        {
                            p4cPosn = 66;
                        }
                        else if(p4cPosn == 5)
                        {
                            p4cPosn = 65;
                        }
                        else if(p4cPosn == 4)
                        {
                            p4cPosn = 64;
                        }
                        else if(p4cPosn == 3)
                        {
                            p4cPosn = 63;
                        }
                        else if(p4cPosn == 2)
                        {
                            p4cPosn = 62;
                        }
                        else if(p4cPosn == 1)
                        {
                            p4cPosn = 61;
                        }
                        else if(p4cPosn == 0)
                        {
                            p4cPosn = 60;
                        }

                        //Determine if Player 3 has moved before their safe zone
                        if(p3cPosn == 8)
                        {
                            p3cPosn = 68;
                        }
                        else if(p3cPosn == 7)
                        {
                            p3cPosn = 67;
                        }
                        else if(p3cPosn == 6)
                        {
                            p3cPosn = 66;
                        }
                        else if(p3cPosn == 5)
                        {
                            p3cPosn = 65;
                        }
                        else if(p3cPosn == 4)
                        {
                            p3cPosn = 64;
                        }
                        else if(p3cPosn == 3)
                        {
                            p3cPosn = 63;
                        }
                        else if(p3cPosn == 2)
                        {
                            p3cPosn = 62;
                        }
                        else if(p3cPosn == 1)
                        {
                            p3cPosn = 61;
                        }
                        else if(p3cPosn == 0)
                        {
                            p3cPosn = 60;
                        }
                        cout << pForPos[p4cPosn] << endl;
                        cout << endl;
                        cout << pTrePos[p3cPosn] << endl;
                        break;
                    case 5:
                        break;
                }
            }

            //Player 4 draws a "12"
            else if(card == 10)
            {
                //Print the card's specific menu
                cout << "You drew a 12!" << endl;
                cout << "1. Move 12 spaces forward" << endl;
                cout << "2. Skip turn" << endl;

                //Check for legal move 
                do
                {
                    if((pChoice > 2) || (pChoice == 1 && p4cPosn < 9) || (pChoice == 2 && p4cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 2) || (pChoice == 1 && p4cPosn < 9) || (pChoice == 2 && p4cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p4cPosn += 12;
                        if(p4cPosn > 74)
                        {
                            p4cPosn = 74;
                        }
                        cout << pForPos[p4cPosn] << endl;    //Output modified game board
                        break;
                    case 2:
                        break;
                }
            }      

            //Player 4 draws a "Sorry!" card
            else
            {
                //Print the card's specific menu
                cout << "You drew a \"Sorry!\" Card!" << endl;
                cout << "1. Move Player One's pawn off the game board" << endl;
                cout << "2. Move Player Two's pawn off the game board" << endl;
                cout << "3. Move Player Three's pawn off the game board" << endl;
                cout << "4. Skip turn" << endl;

                //Check for legal move 
                do
                {
                    if((pChoice > 4) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p2cPosn < 9) || (pChoice == 3 && p3cPosn < 9) ||
                      (pChoice == 4 && p1cPosn >= 9) || (pChoice == 4 && p2cPosn >= 9) || (pChoice == 4 && p3cPosn >= 9))
                    {
                        cout << "That's an illegal move!";
                    }
                    cout << "\nWhich choice would you like to make? ";
                    pChoice = int_chk(choice);
                } while((pChoice > 4) || (pChoice == 1 && p1cPosn < 9) || (pChoice == 2 && p2cPosn < 9) || (pChoice == 3 && p3cPosn < 9) ||
                       (pChoice == 4 && p1cPosn >= 9) || (pChoice == 4 && p2cPosn >= 9) || (pChoice == 4 && p3cPosn >= 9));

                //Execute the desired action
                switch(pChoice)
                {
                    case 1:
                        p1cPosn = 0;
                        cout << "\nPlayer 1 has been moved off the game board!" << endl;
                        cout << pOnePos[0] << endl;
                        break;
                    case 2:
                        p2cPosn = 0;
                        cout << "\nPlayer 2 has been moved off the game board!" << endl;
                        cout << pTwoPos[0] << endl;
                        break;
                    case 3:
                        p3cPosn = 0;
                        cout << "\nPlayer 3 has been moved off the game board!" << endl;
                        cout << pTrePos[0] << endl;
                        break;
                    case 4:
                        break;
                }
            }

            //Determine whether Player 4 has won the game
            if(p4cPosn == 74)
            {
                cout << "\nPlayer 4 has won the game!" << endl;
            }
        }
        
        //Reset the player's choice
        pChoice = 0;
        cin.clear();
        cin.ignore();  
    
    //Exit or repeat the while loop
    }
}

/**
 * @brief Integer Check
 * 
 * This is the Input Validation function.
 * It makes sure all values passed are positive integers only.
 * 
 * @return "number", the input value
 */
int int_chk(int number)
{
    //Check for input
    while(!(cin >> number) || number < 1)
    {
        cout << "ERROR: Invalid Input\n"
                "Please enter a valid integer: ";
        cin.clear();
        cin.ignore(1e9, '\n');
    }
    
    //Return choice after it has been validated
    return(number);
}
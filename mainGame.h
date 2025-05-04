//
// Created by Scott on 04/05/2025.
//
#include "structures.h"

#ifndef MAINGAME_H
#define MAINGAME_H

void displayGameWelcome(void);
//Title screen for game

pos_t getRandPos(int xBound, int yBound);
//Generate a random x,y position
//returns intialised pos_t

pos_t getRandStartPos(int gameXspan);
//Gets a random position with y coord of 0.

void displayUserOptions(char **gameArray,character_t *character,int gameX,int gameY);
//Display user options function
//Takes gameArray and character
//Displays the moves that the user can make

void displayGame(char **gameArray,character_t *character,int gameX,int gameY);
//Display game function
//Displays the header and calls function to display gameArray and user options

int checkValidMove(character_t *character,char userMove,char **gameArray,int gameX,int gameY);
//check valid move function
//takes the character, usersMove, gameArr and game bounds
//Calculates if the move is allowed.
//returns 1 if a valid move and 0 if not.

move_t getNewUserPos(char userEntry,character_t *character);
//Get new user move function
//takes the users entry and character
//Computes new position based off the entered move
//returns the new positon and entered move in form of move_t
//if the move does not move the player simply returns existing position

move_t getUserMove(char **gameArray,character_t *character,material_t *materialArr,int gameX,int gameY)
//getUserMove function
//Gets a character from the user
//Checks if character is a valid move.
//Computes new user position if the move is a position change
//Returns move_t

char getItemToCollect(char **gameArr,pos_t newPosition);
//getItemToCollect function
//Returns item in position in passed grid

char runGame(material_t *materialArr,shopItem_t *shopItemArr);
//runGame function
//Main game function. Calls all functions to make the game function
//Returns and character representing an exitCode depending on reason of exit

#endif //MAINGAME_H

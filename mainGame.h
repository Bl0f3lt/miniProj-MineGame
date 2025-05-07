//
// Created by Scott on 04/05/2025.
//
#include "structures.h"

#ifndef MAINGAME_H
#define MAINGAME_H

void setMaterial(material_t *, char , char [10], int, int, int, int);
//setMaterial function
//Take passed data and pointer and assign attributes

material_t *generateMaterials(void);
//Generate Materials Function
//generate an array of material_t
//Call setMaterial function with data to fill array
//return material_t array

void setShopItem(shopItem_t *, int, char [10], int, int);
//Sets passed pointer attributes from passed data
//Uses pointers

shopItem_t *generateShopItems(void);
//generate shop items function
//generates an array of shopItem_t
//Calls set shop items with each items details
//returns array of shopItem_t

char **generate2Darr(int,int);
//generate 2d array function
//generates a 2d character array with size of passed values

int getTotalWeight(material_t *);
//get Total Weight function
//Finds sum of weights of all materials
//Returns integer

char *generateWeightArray(material_t *, int);
//Creates an array with size of the sum of material weights
//Places the respective number of each material into the array
//Returns character array

void setMineableObjects(char **, material_t *,character_t *, int ,int );
//Set the mineable objects
//Uses weighted random distribution
//Uses pointers

void setImpassableObjects(char **,material_t *,character_t *, int ,int );
//Populate the gameArray with pseudo-random distribution of impassable objects
//Places initial randomly
//Uses second random dist to fill out other impassable objects
//Uses pointers

void setGameArrayValues(char **,material_t *,character_t *,int ,int);
//set game array values function
//Call functions to populate the gameArray
//Uses pointers

char **generateWorld(int ,int ,material_t *,character_t *);
//Generate World function
//Calls functions to generate and populate a 2d array.
//Returns a filled 2d array of characters

void displayWorld(char **,int ,int);
//display world function
//Takes the gameArray and iterates through printing each cell.

pos_t getRandPos(int, int);
//Generate a random x,y position
//returns intialised pos_t

pos_t getRandStartPos(int);
//Gets a random position with y coord of 0.

void initInvArr(character_t *,material_t *,shopItem_t *);
//Initialise character inventory arrays
//creates arrays of length of number of materials
//And array of number of shop items.

void initCharacter(char **,character_t *,material_t *,shopItem_t *, int );
//initCharacter function
//calls respective functions to initialise the character structure with passed data
//Uses pointers

void displayUserInv(character_t *,material_t *);
//Display user invenetory function
//Iterates through the users materials and prints the different materials and quantities

void displayCharacterMoney(character_t *);
//Display character money function
//Takes pointer to character and prints available money

void updateMaterialQuant(character_t *,char );
//updateMaterialQuant function
//Iterates through materials in inventory and updates quant if is found to be the chosen material

void updateUserInventory(character_t *,char **,pos_t);
//updateUserInventory function
//Updates the users inventory if a material is collected

void updateUserPosition(char **,pos_t ,character_t *);
//updateUserPosition function
//Updates the users icon on grid and places to new position
//Fills old position with air

void updateConsumables(character_t *);
//updateConsumables function
//Updates the players move counter and stats each move

void setPlayerScore(character_t *);
//setPlayerScore function
//Math function to calculate the users score based on character stats
//Has conditions to prevent divide by 0 error


void setShopItem(shopItem_t *, int , char [10], int , int );
//Sets passed pointer attributes from passed data
//Uses pointers

shopItem_t *generateShopItems(void);
//generate shop items function
//generates an array of shopItem_t
//Calls set shop items with each items details
//returns array of shopItem_t

void displayShopOptions(character_t *);
//Display shop options function
//clears console and prints shop options

int checkValidShopOpt(int);
//Check function for shop options
//Takes players move and returns 1 if its valid and 0 if not.

void sellMaterials(character_t *);
//Sell Materials Function
//takes pointer to character
//iterates through each material multiplying quantity by value and adding this to player funds.

void displayShopItems(shopItem_t *,character_t *);
//displayShopItems function
//Prints the required info for the shop

buyValid_t checkValidBuyOption(character_t *, shopItem_t *, int );
//check buy option is valid function
//Takes the users Selection and pointers to character and shopitems
//Checks that users entry exists in the avaialbe items
//checks user has available funds
//Returns the buyValid structure which contains if the op is valid and also the reason

void buyShopItem(shopItem_t *, character_t *);
//buy item function
//Takes respective pointers to structures containing relevant info
//Takes user entry and checks if is a valid operation
//Updates pointers from result

void shop(shopItem_t *, character_t *);
//Shop function
//Calls respective functions to operate shop
//Uses pointers to adjust data.

void displayGameWelcome(void);
//Title screen for game

pos_t getRandPos(int, int);
//Generate a random x,y position
//returns intialised pos_t

pos_t getRandStartPos(int);
//Gets a random position with y coord of 0.

void displayUserOptions(char **,character_t *,int ,int);
//Display user options function
//Takes gameArray and character
//Displays the moves that the user can make

void displayGame(char **,character_t *,int ,int );
//Display game function
//Displays the header and calls function to display gameArray and user options

int checkValidMove(character_t *,char ,char **,int ,int );
//check valid move function
//takes the character, usersMove, gameArr and game bounds
//Calculates if the move is allowed.
//returns 1 if a valid move and 0 if not.

move_t getNewUserPos(char ,character_t *);
//Get new user move function
//takes the users entry and character
//Computes new position based off the entered move
//returns the new positon and entered move in form of move_t
//if the move does not move the player simply returns existing position

move_t getUserMove(char **,character_t *,material_t *,int ,int );
//getUserMove function
//Gets a character from the user
//Checks if character is a valid move.
//Computes new user position if the move is a position change
//Returns move_t

char getItemToCollect(char **,pos_t );
//getItemToCollect function
//Returns item in position in passed grid

char runGame(material_t *,shopItem_t *);
//runGame function
//Main game function. Calls all functions to make the game function
//Returns and character representing an exitCode depending on reason of exit

#endif //MAINGAME_H

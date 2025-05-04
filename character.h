//
// Created by bl0f3lt on 02/05/2025.
//

#ifndef CHARACTER_H
#define CHARACTER_H

#include "structures.h"

void initInvArr(character_t *character,material_t *materialArr,shopItem_t *shopItemArr);
//Initialise character inventory arrays
//creates arrays of length of number of materials
//And array of number of shop items.

void initCharacter(char **gameArr,character_t *character,material_t *materialArr,shopItem_t *shopItemArr, int gameXspan);
//initCharacter function
//calls respective functions to initialise the character structure with passed data
//Uses pointers

void displayUserInv(character_t *character,material_t *materialArr);
//Display user invenetory function
//Iterates through the users materials and prints the different materials and quantities

void displayCharacterMoney(character_t *character);
//Display character money function
//Takes pointer to character and prints available money

void updateMaterialQuant(character_t *character,char material)
//updateMaterialQuant function
//Iterates through materials in inventory and updates quant if is found to be the chosen material

void updateUserInventory(character_t *character,char **gameArr,pos_t newPosition);
//updateUserInventory function
//Updates the users inventory if a material is collected

void updateUserPosition(char **gameArr,pos_t newPos,character_t *character);
//updateUserPosition function
//Updates the users icon on grid and places to new position
//Fills old position with air

void updateConsumables(character_t *character);
//updateConsumables function
//Updates the players move counter and stats each move

void setPlayerScore(character_t *character);
//setPlayerScore function
//Math function to calculate the users score based on character stats
//Has conditions to prevent divide by 0 error

#endif //CHARACTER_H

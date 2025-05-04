//
// Created by Scott on 04/05/2025.
//

#include "structures.h"


#ifndef WORLD_H
#define WORLD_H

char **generate2Darr(int x,int y);
//generate 2d array function
//generates a 2d character array with size of passed values

int getTotalWeight(material_t *materialArr);
//get Total Weight function
//Finds sum of weights of all materials
//Returns integer

char *generateWeightArray(material_t *materialArr, int totalWeight);
//Creates an array with size of the sum of material weights
//Places the respective number of each material into the array
//Returns character array

void setMineableObjects(char **gameArray, material_t *materialArr,character_t *character, int gameXspan,int gameYspan);
//Set the mineable objects
//Uses weighted random distribution
//Uses pointers

void setImpassableObjects(char **gameArray,material_t *materialArr,character_t *character, int gameXspan,int gameYspan);
//Populate the gameArray with pseudo-random distribution of impassable objects
//Places initial randomly
//Uses second random dist to fill out other impassable objects
//Uses pointers

void setGameArrayValues(char **gameArray,material_t *materialArr,character_t *character,int gameXspan,int gameYspan);
//set game array values function
//Call functions to populate the gameArray
//Uses pointers

char **generateWorld(int gameXspan,int gameYspan,material_t *materialArr,character_t *character);
//Generate World function
//Calls functions to generate and populate a 2d array.
//Returns a filled 2d array of characters

void displayWorld(char **gameArray,int gameX,int gameY);
//display world function
//Takes the gameArray and iterates through printing each cell.

#endif //WORLD_H

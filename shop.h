//
// Created by Scott on 04/05/2025.
//
#include "structures.h"


#ifndef SHOP_H
#define SHOP_H

void setShopItem(shopItem_t *shopPointer, int itemNum, char itemName[10], int cost, int foodValue);
//Sets passed pointer attributes from passed data
//Uses pointers

shopItem_t *generateShopItems();
//generate shop items function
//generates an array of shopItem_t
//Calls set shop items with each items details
//returns array of shopItem_t

void displayShopOptions(character_t *character);
//Display shop options function
//clears console and prints shop options

int checkValidShopOpt(int userEntry);
//Check function for shop options
//Takes players move and returns 1 if its valid and 0 if not.

void sellMaterials(character_t *character);
//Sell Materials Function
//takes pointer to character
//iterates through each material multiplying quantity by value and adding this to player funds.

void displayShopItems(shopItem_t *shopItemArr,character_t *character);
//displayShopItems function
//Prints the required info for the shop

buyValid_t checkValidBuyOption(character_t *character, shopItem_t *shopItemArr, int userSelection);
//check buy option is valid function
//Takes the users Selection and pointers to character and shopitems
//Checks that users entry exists in the avaialbe items
//checks user has available funds
//Returns the buyValid structure which contains if the op is valid and also the reason

void buyShopItem(shopItem_t *shopItemArr, character_t *character);
//buy item function
//Takes respective pointers to structures containing relevant info
//Takes user entry and checks if is a valid operation
//Updates pointers from result

void shop(shopItem_t *shopItemArr, character_t *character);
//Shop function
//Calls respective functions to operate shop
//Uses pointers to adjust data.

#endif //SHOP_H

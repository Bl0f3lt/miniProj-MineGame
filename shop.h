//
// Created by Scott on 04/05/2025.
//
#include "structures.h"


#ifndef SHOP_H
#define SHOP_H

void displayShopOptions(character_t *character);

int checkValidShopOpt(int userEntry);

void sellMaterials(character_t *character);

void displayShopItems(shopItem_t *shopItemArr,character_t *character);

buyValid_t checkValidBuyOption(character_t *character, shopItem_t *shopItemArr, int userSelection);

void buyShopItem(shopItem_t *shopItemArr, character_t *character);

void shop(shopItem_t *shopItemArr, character_t *character);




#endif //SHOP_H

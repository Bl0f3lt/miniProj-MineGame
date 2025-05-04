//
// Created by bl0f3lt on 02/05/2025.
//

#ifndef CHARACTER_H
#define CHARACTER_H

#include "structures.h"

void initInvArr(character_t *character,material_t *materialArr,shopItem_t *shopItemArr);

void initCharacter(char **gameArr,character_t *character,material_t *materialArr,shopItem_t *shopItemArr, int gameXspan);

void displayUserInv(character_t *character,material_t *materialArr);

void displayCharacterMoney(character_t *character);

void updateMaterialQuant(character_t *character,char material)

void updateConsumables(character_t *character);

void setPlayerScore(character_t *character);

#endif //CHARACTER_H

//
// Created by Scott on 04/05/2025.
//

#include "structures.h"


#ifndef WORLD_H
#define WORLD_H

char **generate2Darr(int x,int y);

int getTotalWeight(material_t *materialArr);

char *generateWeightArray(material_t *materialArr, int totalWeight);

void setMineableObjects(char **gameArray, material_t *materialArr,character_t *character, int gameXspan,int gameYspan);

void setImpassableObjects(char **gameArray,material_t *materialArr,character_t *character, int gameXspan,int gameYspan);

void setGameArrayValues(char **gameArray,material_t *materialArr,character_t *character,int gameXspan,int gameYspan);

char **generateWorld(int gameXspan,int gameYspan,material_t *materialArr,character_t *character);

void displayWorld(char **gameArray,int gameX,int gameY);

#endif //WORLD_H

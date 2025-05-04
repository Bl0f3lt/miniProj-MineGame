//
// Created by bl0f3lt on 02/05/2025.
//
#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "constants.h"

//Defining structures

//pos structure
struct pos {
    int x;
    int y;
};
typedef struct pos pos_t;

//move structure
struct move {
    pos_t newPos;
    char userEntry;
};
typedef struct move move_t;

//material strucutre
struct material {
    char ident;
    char name[10];
    int weight;
    int value;
    int size;
    int mineable;
};
typedef struct material material_t;

//materialInvItem structure
struct materialInvItem {
    material_t* invMaterial;
    int quant;
};
typedef struct materialInvItem materialInvItem_t;

//shopItem structure
struct shopItem {
    int itemIdent;
    char itemName[10];
    int cost;
    int foodValue;
};
typedef struct shopItem shopItem_t;

//itemInvItem structure
struct itemInvItem {
    shopItem_t* invItem;
    int quant;
};
typedef struct itemInvItem itemInvItem_t;

//buyValid Structure
struct buyValid {
    int valid;
    char reason[20];
};
typedef struct buyValid buyValid_t;

//Character Structure
struct character {
    pos_t playerPos;
    int food;
    int health;
    int playerMove;
    int lastCollectionMove;
    int money;
    int totalStartMaterials;
    int materialRem;
    float playerScore;
    materialInvItem_t materialInventory[NUM_MATERIALS];
    itemInvItem_t itemInventory[NUM_SHOP_ITEMS];
};
typedef struct character character_t;

#endif //STRUCTURES_H

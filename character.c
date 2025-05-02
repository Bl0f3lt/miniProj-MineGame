//
// Created by bl0f3lt on 02/05/2025.
//
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "structures.h"
#include "character.h"

//character functions

void initInvArr(character_t *character,material_t *materialArr,shopItem_t *shopItemArr) {
    //Initialise character inventory arrays
    //creates arrays of length of number of materials
    //And array of number of shop items.

    int i;
    for (i=0;i<NUM_MATERIALS;i++) {
        character->materialInventory[i].invMaterial = &materialArr[i];
        character->materialInventory[i].quant = 0;
    }
    for (i=0;i<NUM_SHOP_ITEMS;i++) {
        character->itemInventory[i].invItem = &shopItemArr[i];
        character->itemInventory[i].quant = 0;
    }
}

void initCharacter(char **gameArr,character_t *character,material_t *materialArr,shopItem_t *shopItemArr, int gameXspan) {
    //initCharacter function
    //calls respective functions to initialise the character structure with passed data
    //Uses pointers

    //Generate random start position
    pos_t randPos = getRandStartPos(gameXspan);
    //Assign rand start pos to character.
    character->playerPos.x = randPos.x;
    character->playerPos.y = randPos.y;

    //Initialise the player materialInventory
    initInvArr(character,materialArr,shopItemArr);

    //Initialise consumable resource
    character->food = 10;
    character->health = 3;
    character->playerMove = 0;
    character->lastCollectionMove = 0;
    character->money = 0;
    character->playerScore = 0;

    //Place character in gameArr
    gameArr[character->playerPos.y][character->playerPos.x] = '@';
}

void displayUserInv(character_t *character,material_t *materialArr){
    //Display user invenetory function
    //Iterates through the users materials and prints the different materials and quantities

    int i;
    system("cls");
    fseek(stdin,0,SEEK_END);
    for (i=0;i<NUM_MATERIALS;i++) {
        if (character->materialInventory[i].quant > 0 && character->materialInventory[i].invMaterial->ident != '.') {
            printf("%s: %d\nvalue: %d\n\n",character->materialInventory[i].invMaterial->name,
                   character->materialInventory[i].quant,
                   (character->materialInventory[i].invMaterial->value)*(character->materialInventory[i].quant));
        }
    }
    printf("Press enter to continue\n");
    char enter = NULL;
    scanf("%c",&enter);

}

void displayCharacterMoney(character_t *character) {
    //Display character money function
    //Takes pointer to character and prints available money

    printf("Money Available: %d\n",character->money);
}

void updateConsumables(character_t *character) {
    //updateConsumables function
    //Updates the players move counter and stats each move

    character->playerMove += 1;
    if (((character->playerMove)%2)==0) {
        if ((character->food) != 0) {
            character->food -= 1;
        }
        else {
            character->health -= 1;
        }
    }
}

void setPlayerScore(character_t *character) {
    //setPlayerScore function
    //Math function to calculate the users score based on character stats
    //Has conditions to prevent divide by 0 error

    float sumOfMoney = ((character->money) + ((character->food)*5));
    float collectedMats;
    if (character->playerMove == 0) {
        character->playerScore = 0;
    }
    else if ((character->health * 5)+(sumOfMoney) == 0) {
        character->playerScore = 0;
    }
    else {
        collectedMats = (character->totalStartMaterials - character->materialRem);
        character->playerScore = collectedMats/(character->playerMove) * ((character->health * 5)+(sumOfMoney));
    }
}
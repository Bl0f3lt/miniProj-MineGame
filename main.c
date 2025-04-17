#include <stdio.h>
#include <stdlib.h>
#include <windows.system.h>
#include <time.h>

//Constant value equal to number of collectable items in the Game.
#define NUMITEMS 4

//Defining structures
struct pos {
    int x;
    int y;
};
typedef struct pos pos_t;

struct move {
    pos_t newPos;
    char userEntry;
};
typedef struct move move_t;

struct material {
    char ident;
    char name[10];
    int weight;
    int value;
    int size;
    int mineable;
};
typedef struct material material_t;

struct invItem {
    material_t* invMaterial;
    int quant;
};
typedef struct invItem invItem_t;

struct character {
    pos_t playerPos;
    int food;
    int health;
    int playerMove;
    invItem_t inventory[NUMITEMS];
};
typedef struct character character_t;

//Functions

void setMaterial(material_t *materialPointer, char ident, char name[10], int weight, int value, int size, int mineable) {
    materialPointer->ident = ident;
    strcpy(materialPointer->name,name);
    materialPointer->weight = weight;
    materialPointer->value = value;
    materialPointer->size = size;
    materialPointer->mineable = mineable;
}


material_t *generateMaterials() {
    material_t *materialArr = malloc(NUMITEMS*sizeof(material_t));
    if (!materialArr) {
        return NULL;
    }

    //Needs updating with getting material details from file
    setMaterial(&materialArr[0],'.',"air",100,0,0,1);
    setMaterial(&materialArr[1],'e',"emerald",10,25,10,1);
    setMaterial(&materialArr[2],'d',"diamond",5,40,5,1);
    setMaterial(&materialArr[3],'B',"bedrock",10,100,25,0);

    return materialArr;
}

char **generate2Darr(int x,int y) {
    char** array;
    int z;

    //Dynamic memory allocation means memory not reserved at compilation but instead runtime
    array = (char**)calloc(y,x*sizeof(char));
    for (z=0;z<y;z++) {
        array[z] = (char*)malloc(x*sizeof(char));
    }
    if (!array) {
        return NULL;
    }
    return array;
}

int getTotalWeight(material_t *materialArr) {
    int totalWeight=0;
    int i;
    for (i=0;i<NUMITEMS;i++) {
        if (materialArr[i].mineable == 1) {
            totalWeight += materialArr[i].weight;
        }
    }
    return totalWeight;
}

char *generateWeightArray(material_t *materialArr, int totalWeight) {
    char *weightArray = malloc(totalWeight*sizeof(char));
    int materialIndex,weightIndex,lastIndex=0,currentMatWeight;
    for (materialIndex=0;materialIndex<NUMITEMS;materialIndex++) {
        if (materialArr[materialIndex].mineable == 1) {
            currentMatWeight = materialArr[materialIndex].weight;
            char currentMatIdent = materialArr[materialIndex].ident;
            for (weightIndex=0;weightIndex<currentMatWeight;weightIndex++) {
                weightArray[lastIndex] = currentMatIdent;
                lastIndex++;
            }
        }
    }
    return weightArray;
}

void setMineableObjects(char **gameArray, material_t *materialArr, int gameXspan,int gameYspan) {
    int totalWeight;
    totalWeight = getTotalWeight(materialArr);
    char *weightedMaterialArr;
    weightedMaterialArr = generateWeightArray(materialArr,totalWeight);

    int i,j,randInt;
    char randChar;
    for (i=0;i<gameYspan;i++) {
        for (j=0;j<gameXspan;j++) {
            randInt = rand() % totalWeight;
            randChar = weightedMaterialArr[randInt];
            gameArray[i][j] = randChar;
        }
    }
}

void setImpassableObjects(char **gameArray,material_t *materialArr, int gameXspan,int gameYspan) {
    int i,j,k,randNum;
    material_t impassableMat;
    for (k=0; k<NUMITEMS; k++) {
        if (materialArr[k].mineable == 0) {
            impassableMat = materialArr[k];
        }
    }
    printf("impassable mat: %c",impassableMat.ident);

    for (j=0;j<gameYspan;j++) {
        for (i=0;i<gameXspan;i++) {
            randNum = rand() % 100;
            if (randNum > 95) { //Value to determine frequency of clumps
                gameArray[j][i] = impassableMat.ident;
            }
        }
    }

    int rowChance = 2;
    for (j=1;j<gameYspan;j++) {
        for (i=0; i<gameXspan;i++) {
            if (gameArray[j][i] == impassableMat.ident) {
                randNum = rand() % rowChance;
                if (randNum < 4) { //Number to set the size of impassable clumps
                    if ((i+1)<gameXspan) {
                        gameArray[j][i+1] = impassableMat.ident;
                    }
                    else if ((j+1)<gameYspan) {
                        gameArray[j+1][i] = impassableMat.ident;
                    }
                    else {
                        break;
                    }
                    rowChance = rowChance + 2;

                }
                else {
                    rowChance = 2;
                }
            }
        }
    }
}

void setGameArrayValues(char **gameArray,material_t *materialArr,int gameXspan,int gameYspan) {
    setMineableObjects(gameArray,materialArr,gameXspan,gameYspan);
    setImpassableObjects(gameArray,materialArr,gameXspan,gameYspan);
}


char **generateWorld(int gameXspan,int gameYspan,material_t *materialArr) {
    char **gameArray;
    gameArray = generate2Darr(gameXspan,gameYspan);

    //Error handling case of gameArr allocation failure.
    if (!gameArray) {
        printf("Error in 2dArr gen.\n");
        return NULL;
    }

    setGameArrayValues(gameArray,materialArr,gameXspan,gameYspan);
    return gameArray;
}

//Character functs:

pos_t getRandPos(xBound,yBound) {
    pos_t randPos;
    if (xBound == 0) {
        xBound++;
    }
    if (yBound == 0) {
        yBound++;
    }

    randPos.x = rand() % xBound;
    randPos.y = rand() % yBound;
    return randPos;
}

pos_t getRandStartPos(int gameXspan) {
    return getRandPos(gameXspan,0);
}

void initInvArr(character_t *character,material_t *materialArr) {
    int i;
    for (i=0;i<NUMITEMS;i++) {
        character->inventory[i].invMaterial = &materialArr[i];
        character->inventory[i].quant = 0;
    }
}

void initCharacter(char **gameArr,character_t *character,material_t *materialArr,int gameXspan) {
    //Generate random start position
    pos_t randPos = getRandStartPos(gameXspan);
    //Assign rand start pos to character.
    character->playerPos.x = randPos.x;
    character->playerPos.y = randPos.y;

    //Initialise the player inventory
    initInvArr(character,materialArr);

    //Initialise consumable resource
    character->food = 10;
    character->health = 3;
    character->playerMove = 0;

    //Place character in gameArr
    gameArr[character->playerPos.y][character->playerPos.x] = '@';
}

//Main game loop functions
void displayWorld(char **gameArray,int gameX,int gameY) {
    int i,j;
    for (i=0;i<gameY;i++) {
        for (j=0;j<gameX;j++) {
            printf("%c ",gameArray[i][j]);
        }
        printf("\n");
    }
}

void displayUserOptions(char **gameArray,character_t *character,int gameX,int gameY) {
    pos_t characterPos = character->playerPos;
    if (!((characterPos.y - 1)<0)) {
        printf("up: w\n");
    }
    if (!((characterPos.x + 1)>gameX)) {
        printf("east: d\n");
    }
    if (!((characterPos.y + 1)>gameY)) {
        printf("down: s\n");
    }
    if (!((characterPos.x - 1)<0)) {
        printf("west: a\n");
    }
}

void displayGame(char **gameArray,character_t *character,int gameX,int gameY) {
    //Display game head, temp as filler text
    printf("Food: %d\tHealth: %d\n\n",character->food,character->health);
    displayWorld(gameArray,gameX,gameY);
    printf("\n");
    displayUserOptions(gameArray,character,gameX,gameY);
    printf("Enter a move to play: ");
}

int checkValidMove(character_t *character,char userMove,char **gameArray,int gameX,int gameY) {
    pos_t characterPos = character->playerPos;

    if (userMove == 'w') {
        if ((characterPos.y - 1) >= 0) {
            if (gameArray[characterPos.y-1][characterPos.x] != 'B') {
                return 1;
            }
        }
    }
    else if (userMove == 'd') {
        if ((characterPos.x + 1) < gameX) {
            if (gameArray[characterPos.y][characterPos.x+1] != 'B') {
                return 1;
            }
        }
    }
    else if (userMove == 's') {
        if ((characterPos.y + 1) < gameY) {
            if (gameArray[characterPos.y+1][characterPos.x] != 'B') {
                return 1;
            }
        }
    }
    else if (userMove == 'a') {
        if ((characterPos.x - 1) >= 0) {
            if (gameArray[characterPos.y][characterPos.x-1] != 'B') {
                return 1;
            }
        }
    }
    else if (userMove == 'i') {
        return 1;
    }
    else if (userMove == 'r') {
        return 1;
    }
    return 0;

}

move_t getNewUserMove(char userEntry,character_t *character) {
    move_t newMove;
    newMove.newPos = character->playerPos;
    if (userEntry == 'w') {
        newMove.newPos.y -= 1;
        newMove.userEntry = 'w';
        return newMove;
    }
    else if (userEntry == 'd') {
        newMove.newPos.x += 1;
        newMove.userEntry = 'd';
        return newMove;
    }
    else if (userEntry == 's') {
        newMove.newPos.y += 1;
        newMove.userEntry = 's';
        return newMove;
    }
    else if (userEntry == 'a') {
        newMove.newPos.x -= 1;
        newMove.userEntry = 'a';
        return newMove;
    }
    else if (userEntry == 'i') {
        newMove.userEntry = 'i';
        return newMove;
    }
    else if (userEntry == 'r') {
        newMove.userEntry = 'r';
        return newMove;
    }
}

void displayUserInv(character_t *character,material_t *materialArr){
    int i;
    system("cls");
    fseek(stdin,0,SEEK_END);
    for (i=0;i<NUMITEMS;i++) {
        if (character->inventory[i].quant > 0 && character->inventory[i].invMaterial->ident != '.') {
            printf("%s: %d\nvalue: %d\n\n",character->inventory[i].invMaterial->name,
                   character->inventory[i].quant,
                   (character->inventory[i].invMaterial->value)*(character->inventory[i].quant));
        }
    }
    printf("Press enter to continue\n");
    char enter = NULL;
    scanf("%c",&enter);

}

void shop() {

}

move_t getUserMove(char **gameArray,character_t *character,material_t *materialArr,int gameX,int gameY) {
    char userEntry;
    int validEntry = 0;
    fseek(stdin,0,SEEK_END);
    while (!validEntry) {
        scanf("%c",&userEntry);
        if (!checkValidMove(character,userEntry,gameArray,gameX,gameY)) {
            printf("Not valid input! Try again: ");
            fseek(stdin,0,SEEK_END); //Clear input buffer to accept another input. Prevents looping.
        }
        else {
            validEntry = 1;
        }
    }
    /*
    if (userEntry == 'i') {
        displayUserInv(character,materialArr);
    }
    */

    move_t newMove = getNewUserMove(userEntry,character);
    return newMove;
}

//Check against design below:

char getItemToCollect(char **gameArr,pos_t newPosition) {
    return gameArr[newPosition.y][newPosition.x];
}

void updateMaterialQuant(character_t *character,char material) {
    int i;
    for (i=0;i<NUMITEMS;i++) {
        if (character->inventory[i].invMaterial->ident == material) {
            character->inventory[i].quant += 1;
            break;
        }
    }
}

void updateUserInventory(character_t *character,char **gameArr,pos_t newPosition) {
    if (!((newPosition.x == character->playerPos.x) && (newPosition.y == character->playerPos.y))) {
        char material = getItemToCollect(gameArr,newPosition);
        updateMaterialQuant(character,material);
    }
}

void updateUserPosition(char **gameArr,pos_t newPos,character_t *character) {
    if (!((newPos.x == character->playerPos.x) && (newPos.y == character->playerPos.y))) {
        gameArr[character->playerPos.y][character->playerPos.x] = '.';
        character->playerPos = newPos;
        gameArr[character->playerPos.y][character->playerPos.x] = '@';
    }
}

void updateConsumables(character_t *character) {
    character->playerMove += 1;
    if (((character->playerMove)%2)==0) {
        if ((character->food) != 0) {
            character->food -= 1;
            printf("foodNum: %d\n",character->food);
        }
        else {
            character->health -= 1;
            printf("heath: %d\n",character->health);
        }
    }
}

void freeGameArr(char **gameArray, int ySpan) {
    int i;
    for (i=0;i<ySpan;i++) {
        free(gameArray[i]);
    }
    free(gameArray);
}

char runGame(material_t *materialArr) {
    //Manual definition of size for now. May change to add difficulty.
    int gameXspan,gameYspan;
    gameXspan = 12;
    gameYspan = 12;

    //GameArray generation
    char **gameArray;
    gameArray = generateWorld(gameXspan,gameYspan,materialArr);

    //Generate character
    character_t *character = malloc(sizeof(character_t));
    if (!character) {
        printf("Error in allocation of memory for character!\n");
        return 'c';
    }

    initCharacter(gameArray,character,materialArr,gameXspan);


    move_t newMove;
    //main game loop
    while (character->health>0) {
        displayGame(gameArray,character,gameXspan,gameYspan);
        newMove = getUserMove(gameArray,character,materialArr,gameXspan,gameYspan);
        if (newMove.userEntry == 'r' && character->playerMove == 0) {
            return 'r';
        }
        else if ((newMove.userEntry != 'w' )|| (newMove.userEntry != 'a') || (newMove.userEntry != 'd') || (newMove.userEntry != 's')) {
            //shop,inv
            if (newMove.userEntry == 'i') {
                displayUserInv(character,materialArr);
            }
            else if (newMove.userEntry == 's') {
                shop();
            }
        }
        else {
            updateUserInventory(character,gameArray,newMove.newPos);
            updateUserPosition(gameArray,newMove.newPos,character);
            system("cls"); //Clear the console before next print.
            updateConsumables(character);
        }
        /*
        updateUserInventory(character,gameArray,newMove.newPos);
        updateUserPosition(gameArray,newMove.newPos,character);
        system("cls"); //Clear the console before next print.
        updateConsumables(character);
        */
    }
    freeGameArr(gameArray,gameYspan);
    free(character);
    return 'd';
}

int main() {
    //Initialise Time
    srand(time(NULL));

    //Material array generation.
    material_t *materialArr;
    materialArr = generateMaterials();

    //Exit code table:
    // s: safe - normal running
    // d: player death
    // r: player game reset
    // c: game crash.

    char exitCode = 's';

    //Main game below.
    while (exitCode == 's' || exitCode == 'r') {
        exitCode = runGame(materialArr);
    }
}

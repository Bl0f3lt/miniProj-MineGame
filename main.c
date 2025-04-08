#include <stdio.h>
#include <stdlib.h>
#include <windows.system.h>
#include <time.h>

//Constant value equal to number of collectable items in the Game.
#define NUMITEMS 3

//Defining structures
struct pos {
    int x;
    int y;
};
typedef struct pos pos_t;

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
        totalWeight += materialArr[i].weight;
    }
    return totalWeight;
}

char *generateWeightArray(material_t *materialArr, int totalWeight) {
    char *weightArray = malloc(totalWeight*sizeof(char));
    int materialIndex,weightIndex,lastIndex=0,currentMatWeight;
    for (materialIndex=0;materialIndex<NUMITEMS;materialIndex++) {
        currentMatWeight = materialArr[materialIndex].weight;
        char currentMatIdent = materialArr[materialIndex].ident;
        for (weightIndex=0;weightIndex<currentMatWeight;weightIndex++) {
            weightArray[lastIndex] = currentMatIdent;
            lastIndex++;
        }
    }
    return weightArray;
}

void setGameArrayValues(char **gameArray,material_t *materialArr,int gameXspan,int gameYspan) {
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

int checkValidMove(character_t *character,char userMove,int gameX,int gameY) {
    pos_t characterPos = character->playerPos;

    if (userMove == 'w') {
        if (!((characterPos.y - 1)<0)) {
            return 1;
        }
    }
    else if (userMove == 'd') {
        if (!((characterPos.x + 1)>gameX)) {
            return 1;
        }
    }
    else if (userMove == 's') {
        if (!((characterPos.y + 1)>gameY)) {
            return 1;
        }
    }
    else if (userMove == 'a') {
        if (!((characterPos.x - 1)<0)) {
            return 1;
        }
    }
    else if (userMove == 'i') {
        return 1;
    }
    return 0;

}

pos_t getNewUserPos(char userEntry,character_t *character) {
    pos_t newPos;
    newPos = character->playerPos;
    if (userEntry == 'w') {
        newPos.y -= 1;
        return newPos;
    }
    else if (userEntry == 'd') {
        newPos.x += 1;
        return newPos;
    }
    else if (userEntry == 's') {
        newPos.y += 1;
        return newPos;
    }
    else if (userEntry == 'a') {
        newPos.x -= 1;
        return newPos;
    }
    else if (userEntry == 'i') {
        return newPos;
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

pos_t getUserMove(character_t *character,material_t *materialArr,int gameX,int gameY) {
    char userEntry;
    int validEntry = 0;
    fseek(stdin,0,SEEK_END);
    while (!validEntry) {
        scanf("%c",&userEntry);
        if (!checkValidMove(character,userEntry,gameX,gameY)) {
            printf("Not valid input! Try again: ");
            fseek(stdin,0,SEEK_END); //Clear input buffer to accept another input. Prevents looping.
        }
        else {
            validEntry = 1;
        }
    }
    if (userEntry == 'i') {
        displayUserInv(character,materialArr);
    }

    pos_t newPos = getNewUserPos(userEntry,character);
    return newPos;
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

int main() {
    //Initialise Time
    srand(time(NULL));

    //Test material array generation.
    material_t *materialArr;
    materialArr = generateMaterials();

    //Manual definition of size for now. May change to add difficulty.
    int gameXspan,gameYspan;
    gameXspan = 12;
    gameYspan = 12;

    char **gameArray;
    gameArray = generateWorld(gameXspan,gameYspan,materialArr);

    character_t *character;
    initCharacter(gameArray,character,materialArr,gameXspan);

    pos_t newUserPos;
    //main game loop
    while (character->health>0) {
        displayGame(gameArray,character,gameXspan,gameYspan);
        newUserPos = getUserMove(character,materialArr,gameXspan,gameYspan);
        updateUserInventory(character,gameArray,newUserPos);
        updateUserPosition(gameArray,newUserPos,character);
        system("cls"); //Clear the console before next print.
        updateConsumables(character);
    }
    freeGameArr(gameArray,gameYspan);

}

#include <stdio.h>
#include <stdlib.h>
#include <windows.system.h>
#include <time.h>
//24066799 MineGame C mini Project

//Constant value equal to number of collectable items in the Game.
#define NUM_MATERIALS 4
#define NUM_SHOP_ITEMS 2

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
//Functions

void setMaterial(material_t *materialPointer, char ident, char name[10], int weight, int value, int size, int mineable) {
    //setMaterial function
    //Take passed data and pointer and assign attributes

    materialPointer->ident = ident;
    strcpy(materialPointer->name,name);
    materialPointer->weight = weight;
    materialPointer->value = value;
    materialPointer->size = size;
    materialPointer->mineable = mineable;
}


material_t *generateMaterials() {
    //Generate Materials Function
    //generate an array of material_t
    //Call setMaterial function with data to fill array
    //return material_t array

    material_t *materialArr = malloc(NUM_MATERIALS*sizeof(material_t));
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

void setShopItem(shopItem_t *shopPointer, int itemNum, char itemName[10], int cost, int foodValue) {
    //Sets passed pointer attributes from passed data
    //Uses pointers

    shopPointer->itemIdent = itemNum;
    strcpy(shopPointer->itemName,itemName);
    shopPointer->cost = cost;
    shopPointer->foodValue = foodValue;
}

shopItem_t *generateShopItems() {
    //generate shop items function
    //generates an array of shopItem_t
    //Calls set shop items with each items details
    //returns array of shopItem_t

    shopItem_t *shopArr = malloc(NUM_SHOP_ITEMS*sizeof(shopItem_t));
    if (!shopArr) {
        return NULL;
    }

    setShopItem(&shopArr[0],1,"steak",100,5);
    setShopItem(&shopArr[1],2,"pizza",200,15);

    return shopArr;
}

char **generate2Darr(int x,int y) {
    //generate 2d array function
    //generates a 2d character array with size of passed values

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
    //get Total Weight function
    //Finds sum of weights of all materials
    //Returns integer

    int totalWeight=0;
    int i;
    for (i=0;i<NUM_MATERIALS;i++) {
        if (materialArr[i].mineable == 1) {
            totalWeight += materialArr[i].weight;
        }
    }
    return totalWeight;
}

char *generateWeightArray(material_t *materialArr, int totalWeight) {
    //Creates an array with size of the sum of material weights
    //Places the respective number of each material into the array
    //Returns character array

    char *weightArray = malloc(totalWeight*sizeof(char));
    int materialIndex,weightIndex,lastIndex=0,currentMatWeight;
    for (materialIndex=0;materialIndex<NUM_MATERIALS;materialIndex++) {
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

void setMineableObjects(char **gameArray, material_t *materialArr,character_t *character, int gameXspan,int gameYspan) {
    //Set the mineable objects
    //Uses weighted random distribution
    //Uses pointers

    int totalWeight;
    totalWeight = getTotalWeight(materialArr);
    char *weightedMaterialArr;
    weightedMaterialArr = generateWeightArray(materialArr,totalWeight);

    int i,j,randInt;
    char randChar;
    character->materialRem = 0;
    for (i=0;i<gameYspan;i++) {
        for (j=0;j<gameXspan;j++) {
            randInt = rand() % totalWeight;
            randChar = weightedMaterialArr[randInt];
            if (randChar != '.') {
                character->materialRem += 1;
            }
            gameArray[i][j] = randChar;
        }
    }
    character->totalStartMaterials = character->materialRem;
}

void setImpassableObjects(char **gameArray,material_t *materialArr,character_t *character, int gameXspan,int gameYspan) {
    //Populate the gameArray with pseudo-random distribution of impassable objects
    //Places initial randomly
    //Uses second random dist to fill out other impassable objects
    //Uses pointers

    int i,j,k,randNum;
    material_t impassableMat;
    for (k=0; k<NUM_MATERIALS; k++) {
        if (materialArr[k].mineable == 0) {
            impassableMat = materialArr[k];
        }
    }

    for (j=0;j<gameYspan;j++) {
        for (i=0;i<gameXspan;i++) {
            randNum = rand() % 100;
            if (randNum > 95) { //Value to determine frequency of clumps
                if (gameArray[j][i] != '.') {
                    character->materialRem -= 1;
                }
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
                        if (gameArray[j][i+1] != '.') {
                            character->materialRem -= 1;
                        }
                        gameArray[j][i+1] = impassableMat.ident;
                    }
                    else if ((j+1)<gameYspan) {
                        if (gameArray[j+1][i] != '.') {
                            character->materialRem -= 1;
                        }
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

void setGameArrayValues(char **gameArray,material_t *materialArr,character_t *character,int gameXspan,int gameYspan) {
    //set game array values function
    //Call functions to populate the gameArray
    //Uses pointers

    setMineableObjects(gameArray,materialArr,character,gameXspan,gameYspan);
    setImpassableObjects(gameArray,materialArr,character,gameXspan,gameYspan);
}


char **generateWorld(int gameXspan,int gameYspan,material_t *materialArr,character_t *character) {
    //Generate World function
    //Calls functions to generate and populate a 2d array.
    //Returns a filled 2d array of characters

    char **gameArray;
    gameArray = generate2Darr(gameXspan,gameYspan);

    //Error handling case of gameArr allocation failure.
    if (!gameArray) {
        printf("Error in 2dArr gen.\n");
        return NULL;
    }

    setGameArrayValues(gameArray,materialArr,character,gameXspan,gameYspan);
    return gameArray;
}

//Character functs:

pos_t getRandPos(xBound,yBound) {
    //Generate a random x,y position
    //returns intialised pos_t

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
    //Gets a random position with y coord of 0.
    return getRandPos(gameXspan,0);
}

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

//Main game loop functions
void displayWorld(char **gameArray,int gameX,int gameY) {
    //display world function
    //Takes the gameArray and iterates through printing each cell.

    int i,j;
    for (i=0;i<gameY;i++) {
        for (j=0;j<gameX;j++) {
            printf("%c ",gameArray[i][j]);
        }
        printf("\n");
    }
}

void displayUserOptions(char **gameArray,character_t *character,int gameX,int gameY) {
    //Display user options function
    //Takes gameArray and character
    //Displays the moves that the user can make

    if (character->playerMove == 0) {
        printf("reset grid: r\n\n");
    }

    pos_t characterPos = character->playerPos;
    if (!((characterPos.y - 1)<0)) {
        if (gameArray[characterPos.y-1][characterPos.x] != 'B') {
            printf("up: w\n");
        }
    }
    if (!((characterPos.x + 1)>=gameX)) {
        if (gameArray[characterPos.y][characterPos.x+1] != 'B') {
            printf("east: d\n");
        }
    }

    if (!((characterPos.y + 1)>=gameY)) {
        if (gameArray[characterPos.y+1][characterPos.x] != 'B') {
            printf("down: s\n");
        }
    }

    if (!((characterPos.x - 1)<0)) {
        if (gameArray[characterPos.y][characterPos.x-1] != 'B') {
            printf("west: a\n");
        }
    }
    if (((character->playerMove) - (character->lastCollectionMove))>=12) {
        printf("exit grid: l\n");
    }

    printf("\n");
    printf("shop: b\n");

}

void displayGame(char **gameArray,character_t *character,int gameX,int gameY) {
    //Display game function
    //Displays the header and calls function to display gameArray and user options

    printf("Food: %d\tHealth: %d\n\n",character->food,character->health);
    displayWorld(gameArray,gameX,gameY);
    printf("\n");
    displayUserOptions(gameArray,character,gameX,gameY);
    printf("Enter a move to play: ");
}

int checkValidMove(character_t *character,char userMove,char **gameArray,int gameX,int gameY) {
    //check valid move function
    //takes the character, usersMove, gameArr and game bounds
    //Calculates if the move is allowed.
    //returns 1 if a valid move and 0 if not.

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
    else if (userMove == 'b') {
        return 1;
    }
    else if (userMove == 'r') {
        return 1;
    }
    else if (userMove == 'l') {
        if (((character->playerMove) - (character->lastCollectionMove))>=12) {
            return 1;
        }
    }
    return 0;

}

move_t getNewUserMove(char userEntry,character_t *character) {
    //Get new user move function
    //takes the users entry and character
    //Computes new position based off the entered move
    //returns the new positon and entered move in form of move_t
    //if the move does not move the player simply returns existing position

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
    else if (userEntry == 'b') {
        newMove.userEntry = 'b';
        return newMove;
    }
    else if (userEntry == 'r') {
        newMove.userEntry = 'r';
        return newMove;
    }
    else if (userEntry == 'l') {
        newMove.userEntry = 'l';
        return newMove;
    }
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

void displayShopOptions(character_t *character) {
    //Display shop options function
    //clears console and prints shop options

    system("cls");
    printf("Welcome to the Shop!\n");
    displayCharacterMoney(character);
    printf("Shop options: \n");
    printf("1: Sell Materials\n");
    printf("2: Buy Items\n");
    printf("3: Close shop\n");
}

int checkValidShopOpt(int userEntry) {
    //Check function for shop options
    //Takes players move and returns 1 if its valid and 0 if not.

    printf("Checking valid shop option\n");
    switch (userEntry) {
        case 1 ... 3:
            return 1;
        default:
            return 0;
    }
}

void sellMaterials(character_t *character) {
    //Sell Materials Function
    //takes pointer to character
    //iterates through each material multiplying quantity by value and adding this to player funds.

    int i;
    printf("Selling items!\n");
    for (i=0;i<NUM_MATERIALS;i++) {
        if (character->materialInventory[i].quant > 0 && character->materialInventory[i].invMaterial->ident != '.' && character->materialInventory[i].invMaterial->mineable == 1) {
            character->money += (character->materialInventory[i].quant)*(character->materialInventory[i].invMaterial->value);
            character->materialInventory[i].quant = 0;
        }
    }
}

void displayShopItems(shopItem_t *shopItemArr,character_t *character) {
    //displayShopItems function
    //Prints the required info for the shop

    printf("Buy Items\n");
    displayCharacterMoney(character);
    printf("Items available for purchase: \n");
    printf("0: Exit Shop\n");
    int i;
    for (i=0;i<NUM_SHOP_ITEMS;i++) {
        printf("Item %d: %s  cost: %d\n",i+1,shopItemArr[i].itemName,shopItemArr[i].cost);
    }
}

buyValid_t checkValidBuyOption(character_t *character, shopItem_t *shopItemArr, int userSelection) {
    //check buy option is valid function
    //Takes the users Selection and pointers to character and shopitems
    //Checks that users entry exists in the avaialbe items
    //checks user has available funds
    //Returns the buyValid structure which contains if the op is valid and also the reason

    //Check that the entry exists in the shop arr.
    int i;
    buyValid_t validityResult;
    for (i=0;i<NUM_SHOP_ITEMS;i++) {
        if (shopItemArr[i].itemIdent == userSelection) {
            //Check user has funds
            if (character->money >= shopItemArr[i].cost) {
                validityResult.valid = 1;
                strcpy(validityResult.reason,"Success");
                return validityResult;
            }
            else {
                validityResult.valid = 0;
                strcpy(validityResult.reason,"Insufficient Funds!");
                return validityResult;
            }
        }

    }
    //Check if user selection to exit shop
    if (userSelection == 0) {
        validityResult.valid = 1;
        return validityResult;
    }
    validityResult.valid = 0;
    strcpy(validityResult.reason,"Item not found!");
    return validityResult;
}

void buyShopItem(shopItem_t *shopItemArr, character_t *character) {
    //buy item function]
    //Takes respective pointers to structures containing relevant info
    //Takes user entry and checks if is a valid operation
    //Updates pointers from result

    //Entry checking
    int userEntry;
    buyValid_t validityResult;
    validityResult.valid = 0;
    while (!validityResult.valid) {
        fseek(stdin,0,SEEK_END);
        scanf("%d",&userEntry);
        validityResult = checkValidBuyOption(character,shopItemArr,userEntry);
        if (!validityResult.valid && validityResult.reason == "Insufficient Funds!") {
            printf("%s\n",validityResult.reason);
            validityResult.valid = 1;
            fseek(stdin,0,SEEK_END);
        }
        else if (!validityResult.valid) {
            printf("%s\n",validityResult.reason);
            fseek(stdin,0,SEEK_END);
        }
    }

    //Update user inventory/stats with the item purchased
    //userEntry of 0 means exit.
    if (userEntry != 0) {
        shopItem_t itemBrought = shopItemArr[userEntry-1];
        if (itemBrought.foodValue > 0 && validityResult.reason != "Insufficient Funds!") {
            character->food += itemBrought.foodValue;
            character->money -= itemBrought.cost;
        }
        else if (validityResult.reason != "Insufficient Funds!") {
            character->itemInventory[userEntry-1].quant += 1;
            character->money -= itemBrought.cost;
        }
    }
    else {
        printf("Returning to shop main page.\n");
    }

}

void shop(shopItem_t *shopItemArr, character_t *character) {
    //Shop function
    //Calls respective functions to operate shop
    //Uses pointers to adjust data.

    displayShopOptions(character);

    //User Entry Validation
    int validEntry = 0;
    int userSelection;
    fseek(stdin,0,SEEK_END);
    while (!validEntry) {
        scanf("%d",&userSelection);
        if (!checkValidShopOpt(userSelection)) {
            printf("Invalid shop option\n");
            fseek(stdin,0,SEEK_END);
        }
        else {
            validEntry = 1;
        }
    }

    //Compute user entry to correct function path.
    switch (userSelection) {
        case 1:
            sellMaterials(character);
            shop(shopItemArr, character);
            break;
        case 2:
            displayShopItems(shopItemArr,character);
            buyShopItem(shopItemArr,character);
            shop(shopItemArr, character);
            break;
        case 3:
            break;
    }


}

move_t getUserMove(char **gameArray,character_t *character,material_t *materialArr,int gameX,int gameY) {
    //getUserMove function
    //Gets a character from the user
    //Checks if character is a valid move.
    //Computes new user position if the move is a position change
    //Returns move_t

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


char getItemToCollect(char **gameArr,pos_t newPosition) {
    //getItemToCollect function
    //Returns item in position in passed grid

    return gameArr[newPosition.y][newPosition.x];
}

void updateMaterialQuant(character_t *character,char material) {
    //updateMaterialQuant function
    //Iterates through materials in inventory and updates quant if is found to be the chosen material

    int i;
    for (i=0;i<NUM_MATERIALS;i++) {
        if (character->materialInventory[i].invMaterial->ident == material) {
            character->materialInventory[i].quant += 1;
            break;
        }
    }
}

void updateUserInventory(character_t *character,char **gameArr,pos_t newPosition) {
    //updateUserInventory function
    //Updates the users inventory if a material is collected

    if (!((newPosition.x == character->playerPos.x) && (newPosition.y == character->playerPos.y))) {
        char material = getItemToCollect(gameArr,newPosition);
        if (material != '.') {
            character->materialRem--;
            character->lastCollectionMove = character->playerMove;
            updateMaterialQuant(character,material);
        }
    }
}

void updateUserPosition(char **gameArr,pos_t newPos,character_t *character) {
    //updateUserPosition function
    //Updates the users icon on grid and places to new position
    //Fills old position with air

    if (!((newPos.x == character->playerPos.x) && (newPos.y == character->playerPos.y))) {
        gameArr[character->playerPos.y][character->playerPos.x] = '.';
        character->playerPos = newPos;
        gameArr[character->playerPos.y][character->playerPos.x] = '@';
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

void freeGameArr(char **gameArray, int ySpan) {
    //function to free the 2d gameArray
    //Prevents memory block up.
    //Called on ever exit from runGame

    int i;
    for (i=0;i<ySpan;i++) {
        free(gameArray[i]);
    }
    free(gameArray);
}

char runGame(material_t *materialArr,shopItem_t *shopItemArr) {
    //runGame function
    //Main game function. Calls all functions to make the game function
    //Returns and character representing an exitCode depending on reason of exit

    //Manual definition of size for now. May change to add difficulty.
    int gameXspan,gameYspan;
    gameXspan = 12;
    gameYspan = 12;

    //Generate character structure
    character_t *character = malloc(sizeof(character_t));
    if (!character) {
        printf("Error in allocation of memory for character!\n");
        return 'c';
    }

    //GameArray generation
    char **gameArray;
    gameArray = generateWorld(gameXspan,gameYspan,materialArr,character);

    //Instance character attributes
    initCharacter(gameArray,character,materialArr,shopItemArr,gameXspan);

    move_t newMove;
    int backOut = 0;

    //Main Game Loop
    while ((character->health>0) && !backOut) {

        if (character->materialRem == 0) {
            //Win exit path

            char entry;
            system("cls");
            printf("You Win!\n");
            setPlayerScore(character);
            printf("Your Score is: %.2f \n",character->playerScore);
            printf("Press Enter to continue!");
            fseek(stdin,0,SEEK_END);
            scanf("%c",&entry);

            freeGameArr(gameArray,gameYspan);
            free(character);
            return 'w';
        }

        //Main game code
        displayGame(gameArray,character,gameXspan,gameYspan);
        newMove = getUserMove(gameArray,character,materialArr,gameXspan,gameYspan);


        //user move functions
        if (newMove.userEntry == 'r' && character->playerMove == 0) {
            //reset game exit path

            freeGameArr(gameArray,gameYspan);
            free(character);
            system("cls");
            return 'r';
        }

        else if (newMove.userEntry == 'l' && (((character->playerMove) - (character->lastCollectionMove))>=12)) {
            //Player exit path

            char entry;
            system("cls");
            printf("You chose to leave the mine.\n");
            setPlayerScore(character);
            printf("Your Score is: %.2f \n",character->playerScore);
            printf("Press Enter to continue!");
            fseek(stdin,0,SEEK_END);
            scanf("%c",&entry);

            freeGameArr(gameArray,gameYspan);
            free(character);
            return 'l';
        }

        else if (newMove.userEntry == 'i') {
            displayUserInv(character,materialArr);
        }
        else if (newMove.userEntry == 'b') {
            shop(shopItemArr,character);
        }
        else if (newMove.userEntry == 'w' || newMove.userEntry == 'a' || newMove.userEntry == 'd' || newMove.userEntry == 's'){
            updateUserInventory(character,gameArray,newMove.newPos);
            updateUserPosition(gameArray,newMove.newPos,character);
            system("cls"); //Clear the console before next print.
            updateConsumables(character);
        }
    }

    //player death exit path
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

    //Shop item array generation
    shopItem_t *shopItemArr;
    shopItemArr = generateShopItems();

    //Exit code table:
    // s: default state
    // w: player win
    // l: player exit
    // d: player death
    // r: player game reset
    // c: game crash.

    char exitCode = 's';

    //Main game below.
    while (exitCode == 's' || exitCode == 'r') {
        exitCode = runGame(materialArr, shopItemArr);
    }
    printf("Exit code: %c\n",exitCode);

    scanf("%c",&exitCode);
}

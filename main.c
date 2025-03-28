#include <stdio.h>
#include <stdlib.h>
#include <windows.system.h>
#include <time.h>

//Constant value equal to number of collectable items in the Game.
#define NUMITEMS 2



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
    int consumableRemaining;
    invItem_t inventory[NUMITEMS];
};

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
    setMaterial(&materialArr[0],'c',"coal",50,3,5,1);
    setMaterial(&materialArr[1],'e',"emerald",10,25,10,1);

    return materialArr;
}

char **generate2Darr(int x,int y) {
    char** array;
    int z;

    //Dynamic memory allocation means memory not reserved at compilation but instead runtime
    array = (char**)calloc(y,x*sizeof(char));
    for (z=0;z<y;z++) {
        array[y] = (char*)malloc(x*sizeof(char));
    }
    return array;
}

int getTotalWeight(material_t *materialArr) {
    int totalWeight=0;
    int i;
    for (i=0;i<NUMITEMS;i++) {
        totalWeight += materialArr[i].weight;
        printf("matWeight:  %d  totalWeight: %d\n",materialArr[i].weight,totalWeight);
    }
    return totalWeight;
}

void setGameArrayValues(char **gameArray,material_t *materialArr) {
    int totalWeight;
    totalWeight = getTotalWeight(materialArr);
    printf("totalWeight: %d",totalWeight);
}

char **generateWorld(int gameXspan,int gameYspan,material_t *materialArr) {
    char **gameArray;
    gameArray = generate2Darr(gameXspan,gameYspan);
    setGameArrayValues(gameArray,materialArr);
}


int main() {
    //Test matterial array generation.
    material_t *materialArr;
    materialArr = generateMaterials();

    //Manual definition of size for now. May change to add dificulty.
    int gameXspan,gameYspan;
    gameXspan = 12;
    gameYspan = 12;

    char **gameArray;
    gameArray = generateWorld(gameXspan,gameYspan,materialArr);

}

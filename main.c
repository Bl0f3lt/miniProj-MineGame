#include <stdio.h>
#include <stdlib.h>
#include <windows.system.h>
#include <time.h>

//Constant value equal to number of collectable items in the Game.
const int numItems = 2;


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
    //invItem_t inventory[numItems];
};

//Functions

material_t *generateMaterials() {
    material_t *materialArr = malloc(numItems*sizeof(material_t));
    if (!materialArr) {
        return NULL;
    }

    //Hard coding two materials for initial testing. Needs to be updated
    materialArr[0].ident= 'c';
    strcpy(materialArr[0].name,"coal");
    materialArr[0].weight = 50;
    materialArr[0].value = 3;
    materialArr[0].size = 5;
    materialArr[0].mineable = 1;

    materialArr[1].ident= 'e';
    strcpy(materialArr[1].name,"emerald");
    materialArr[1].weight = 10;
    materialArr[1].value = 25;
    materialArr[1].size = 10;
    materialArr[1].mineable = 1;

    return materialArr;

}


int main() {
    //Test matterial array generation.
    material_t *materialArr;
    materialArr = generateMaterials();

    //Print out some details of mat array to confirm good running
    printf("%s\n",materialArr[0].name);
    printf("%s",materialArr[1].name);
}

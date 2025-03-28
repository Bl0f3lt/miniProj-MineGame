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
    material_t *materialArr = malloc(numItems*sizeof(material_t));
    if (!materialArr) {
        return NULL;
    }

    //Needs updating with getting material details from file
    setMaterial(&materialArr[0],'c',"coal",50,3,5,1);
    setMaterial(&materialArr[1],'e',"emerald",10,25,10,1);

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

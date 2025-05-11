#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct IceCream {
    double priceKg;
    int kg;
    char name[20];
    char Id[3];
};

void searchIcePrice(struct IceCream *array, int elNum, char letter[2]) {
    double priceTotal = 0;

    for(int i = 0; i < elNum; i++) {
        if(strncmp(letter, array[i].Id, 1) == 0) {
            priceTotal += array[i].priceKg;
        }
    }

    printf("The total price of the iceCreams with Id %s is: %.2f\n", letter, priceTotal);
}

void iceCreamCount(struct IceCream *array, int elNum, double price, int kg) {
    FILE *fp;
    int counter = 0;

    if((fp = fopen("info.txt", "w")) == NULL) {
        printf("Can`t open file");
        exit(1);
    }

    for(int i = 0; i < elNum; i++) {
        if (price > array[i].priceKg && array[i].kg > kg) {
            fprintf(fp, "%s;", array[i].Id);
            fprintf(fp, "%s;", array[i].name);
            fprintf(fp, "%d;", array[i].kg);
            fprintf(fp, "%.2f leva\n", array[i].priceKg);
            counter++;
        }
    }

    fclose(fp);
    printf("%d", counter);
}

void searchFile(char Id[3]) {
    FILE *fp;
    struct IceCream ic;

    if ((fp = fopen("icecream.bin", "rb")) == NULL) {
        printf("Can`t open file");
        exit(2);
    }

    while(fread(&ic, sizeof(struct IceCream), 1, fp) == 1) {
        if(strcmp(ic.Id, Id) == 0) {
            printf("IceCream - %s\n", ic.name);
            printf("Price - %.2f BGN\n", ic.priceKg);
        }
    }

    fclose(fp);
}

int main() {
    int size;
    int isValid = 1;
    while(isValid != 0) {
        printf("Enter number of elements: ");
        scanf("%d", &size);

        if (5 > size || size > 15) {
            printf("Number should be between 5 and 15\n");
        } else {
            isValid = 0;
        }
    }
    
    struct IceCream* creams = (struct IceCream*)malloc(size * sizeof(struct IceCream));

    if (creams == NULL) {
        printf("Error mem alloc");
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        printf("Name: ");
        scanf("%s", creams[i].name);

        printf("Id: ");
        scanf("%s", creams[i].Id);

        printf("Kg: ");
        scanf("%d", &creams[i].kg);

        printf("Price Per Kg: ");
        scanf("%lf", &creams[i].priceKg);
        printf("--------\n");
    }

    for (int i = 0; i < size; i++) {
        printf("Name: %s\n", creams[i].name);

        printf("Id: %s\n", creams[i].Id);

        printf("Kg: %d\n", creams[i].kg);

        printf("Price Per Kg: %.2f\n", creams[i].priceKg);
        printf("--------\n");
    }

    searchIcePrice(creams, size, "A");
    iceCreamCount(creams, size, 4.44, 30);
    searchFile("A2");
}
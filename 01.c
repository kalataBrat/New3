# include <stdio.h>
# include <stdlib.h>
# include <string.h>

struct Medicine{
    double price;
    int quantity;
    int Id;
    char name[30];
    char date[30];
};

void medicinesDate(struct Medicine *array, int elNum, char date[30]) {
    int arrayGiven[2];
    int arrayHave[2];
    char data[30];
    int result1, result2; 
    char *ptr1, *ptr2;

    ptr1 = strtok(date, ".");
    while(ptr1 != NULL) {
        for(int i = 0; i < 2; i++) {
            arrayGiven[i] = atoi(ptr1);
            ptr1 = strtok(NULL, ".");
        }
    }

    result1 = (arrayGiven[1] * 12) + arrayGiven[0];
    
    for(int i = 0; i < elNum; i++) {
        strcpy(data, array[i].date);
        ptr2 = strtok(data, ".");
        while(ptr2 != NULL) {
            for(int j = 0; j < 2; j++) {
                arrayHave[j] = atoi(ptr2);
                ptr2 = strtok(NULL, ".");
            }
        }

        result2 = (arrayHave[1] * 12) + arrayHave[0];

        if(result1 > result2) {
            printf("Funkciq\n");
            printf("Price: %.2f\n", array[i].price);
            printf("Quantity: %d\n", array[i].quantity);
            printf("Id: %d\n", array[i].Id);
            printf("Name: %s\n", array[i].name);
            printf("Date: %s\n", array[i].date);
            printf("--------\n");
        }
    }
}

void minMaxPrice(struct Medicine *array, int elNum, double minPrice, double maxPrice) {
    FILE *fp2;
    
    if ((fp2 = fopen("offer.txt", "w")) == NULL) {
        printf("Can`t open file");
        exit(1);
    }

    for(int i = 0; i < elNum; i++) {
        if(minPrice < array[i].price && array[i].price < maxPrice) {

            fprintf(fp2, "%s\n", array[i].name);
            fprintf(fp2, "%s\n", array[i].date);
            fprintf(fp2, "%d\n", array[i].Id);
            fprintf(fp2, "%.2f leva\n", array[i].price);
        }
    } 

    fclose(fp2);
}

struct Medicine *deleteMed(struct Medicine *array, int *elNum, char medName[30], char data[30]) {
    int found = -1;

    for(int i = 0; i < *elNum; i++) {
        if (strcmp(array[i].name, medName) == 0 && strcmp(array[i].date, data) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("No medicine found");
        return array;
    }

    for(int i = found; i < *elNum - 1; i++) {
        array[i] = array[i + 1];
    }

    struct Medicine *temp = realloc(array, (*elNum - 1) * sizeof(struct Medicine));
    if (temp == NULL && *elNum - 1 > 0) {
        printf("Mem alloc failed");
        return array;
    }

    (*elNum)--;
    return temp;
}

int main() {
    int size;
    printf("Enter size of med array: ");
    scanf("%d", &size);
    struct Medicine* meds = (struct Medicine*)calloc(size, sizeof(*meds));
    FILE *fp;


    if (meds == NULL) {
        printf("error mem alloc");
        exit(1);
    }

    if ((fp = fopen("medicine.bin", "wb")) == NULL) {
        printf("Error opening file");
        exit(1);
    }

    for(int i = 0; i < size; i++) {
        printf("Price: ");
        scanf("%lf", &meds[i].price);

        printf("Quantity: ");
        scanf("%d", &meds[i].quantity);

        printf("Id: ");
        scanf("%d", &meds[i].Id);

        printf("Name: ");
        scanf("%s", &meds[i].name);

        printf("Date: ");
        scanf("%s", &meds[i].date);

        if (fwrite(&meds[i], sizeof(struct Medicine), 1, fp) != 1) {
            printf("Error writing");
            exit(2);
        }
    }

    fclose(fp);
    printf("-------------\n");

    if ((fp = fopen("medicine.bin", "rb")) == NULL) {
        printf("Error opening file");
        exit(1);
    }

    for(int i = 0; i < size; i++) {
        if (fread(&meds[i], sizeof(struct Medicine), 1, fp) != 1) {
            printf("Error writing");
            exit(2);
        } else {
            printf("Price: %.2f\n", meds[i].price);
            printf("Quantity: %d\n", meds[i].quantity);
            printf("Id: %d\n", meds[i].Id);
            printf("Name: %s\n", meds[i].name);
            printf("Date: %s\n", meds[i].date);
            printf("--------\n");
        }
    }

    fclose(fp);
    medicinesDate(meds, size, "09.2020");
    minMaxPrice(meds, size, 1.11, 3.33);
    meds = deleteMed(meds, &size, "Proba", "03.2023");

    if ((fp = fopen("medicine.bin", "wb")) == NULL) {
        printf("Error opening file");
        exit(1);
    }

    for(int i = 0; i < size; i++) {
        if (fwrite(&meds[i], sizeof(struct Medicine), 1, fp) != 1) {
            printf("Error writing");
            exit(2);
        }
    }
    fclose(fp);

    if ((fp = fopen("medicine.bin", "rb")) == NULL) {
        printf("Error opening file");
        exit(1);
    }

    for(int i = 0; i < size; i++) {
        if (fread(&meds[i], sizeof(struct Medicine), 1, fp) != 1) {
            printf("Error writing");
            exit(2);
        } else {
            printf("Price: %.2f\n", meds[i].price);
            printf("Quantity: %d\n", meds[i].quantity);
            printf("Id: %d\n", meds[i].Id);
            printf("Name: %s\n", meds[i].name);
            printf("Date: %s\n", meds[i].date);
            printf("--------\n");
        }
    }
    fclose(fp);
    free(meds);
}
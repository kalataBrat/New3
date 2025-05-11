#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Treatment {
    int id;
    char diagnose[51];
    char name[31];
    char data[11];
};

int main() {
    FILE *fp;
    int size;

    if((fp = fopen("history.bin", "rb")) == NULL) {
        printf("Can`t open file");
        exit(1);
    }

    if(fread(&size, sizeof(int), 1, fp) != 1) {
        printf("Failed to read size");
        fclose(fp);
        return 1;
    }

    struct Treatment *history = (struct Treatment*)calloc(size, sizeof(struct Treatment));

    if (!history) {
        printf("Mem alloc failed");
        fclose(fp);
        return 1;
    }

    size_t items = fread(history, sizeof(struct Treatment), size, fp);

    if (items != size) {
        printf("Error expected items");
        fclose(fp);
        free(history);
        return 1;
    }

    fclose(fp);
    free(history);
    return 0;
}

void count_Treatment(struct Treatment *array, int size, char name[31], char diagnose[51]) {
    int count = 0;

    for(int i = 0; i < size; i++) {
        if (strcmp(array[i].name, name) == 0 && strcmp(array[i].diagnose, diagnose) == 0) {
            count++;
        }
    }

    if (count != 0) {
        printf("%d", count);
    } else {
        printf("No match: %d", 0);
    }
}

struct Treatment *add_new_treatment(struct Treatment *array, int *size) {
    struct Treatment *temp = realloc(array, (*size + 1) * sizeof(struct Treatment));

    if (!temp) {
        printf("Mem alloc failed");
        return array;
    }

    printf("Name: ");
    scanf("%s", temp[*size].name);
    printf("Diagnose: ");
    scanf("%s", temp[*size].diagnose);
    printf("Date: ");
    scanf("%s", temp[*size].data);
    printf("ID: ");
    scanf("%d", &temp[*size].id);

    (*size)++;
    return (*size > 0) ? temp : NULL;
}

void write_text_file(struct Treatment *array, int size, char diagnose[51]) {
    FILE *fp2;
    int count = 0;

    if((fp2 = fopen("illness.txt", "w")) == NULL) {
        printf("can`t open file");
        exit(1);
    }

    for(int i = 0; i < size; i++) {
        if(strcmp(array[i].diagnose, diagnose) == 0) {
            fprintf(fp2, "Bolnichen prestoi na %s\nza lechenie na %s:\n%s\n\n", array[i].name, array[i].diagnose, array[i].data);
            count++;
        }
    }

    if(count != 0) {
        printf("%d writes to file", count);
    } else {
        printf("No matches: %d", count);
    }
    fclose(fp2);
}
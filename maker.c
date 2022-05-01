#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 1024

typedef char page[LENGTH];

FILE *change(page dir) {
    page path, file;
    strcpy(path, dir);

    printf("Name of file to change to: ");
    scanf("%s", file); getc(stdin);
    strcat(path, file);
    strcat(path, ".txt");

    return fopen(path, "a+");
}

FILE *new(page dir) {
    page path, file;
    strcpy(path, dir);

    printf("Name of file to be created: ");
    scanf("%s", file); getc(stdin);
    strcat(path, file);
    strcat(path, ".txt");

    return fopen(path, "w+");
}

void displayFile(FILE *fp) {
    page buffer;

    while (!feof(fp)) {
        buffer[0] = '\0';
        fgets(buffer, LENGTH, fp);
        printf("%s", buffer);
    }
}

void edit(FILE *fp, page dir) {
    int choices, decision;
    page *paths = (page *) malloc (choices * sizeof(page));
    page buffer;
    
    while (1) {
        fseek(fp, 0, SEEK_SET);
        displayFile(fp);

        fseek(fp, 0, SEEK_SET);
        fscanf(fp, "%d\n", &choices);
        for (int i = 0; i < choices; i++) {
            fgets(buffer, LENGTH, fp);

            strcpy(paths[i], dir);
            strcat(paths[i], buffer);
        }

        printf("\nWhat would you like to do?\n");
        printf("1. Change number of branches\n");
        printf("2. Change branch paths\n");
        printf("3. Change text\n");
        printf("4. Go back to main menu\n");

        printf("Choice: ");
        scanf("%d", &decision); getc(stdin);

        if (decision == 1) {

        }
    }
}

int main() {
    page directory, path;
    
    printf("Game Directory: ");
    scanf("%s", directory); getc(stdin);

    strcat(directory, "//");
    strcpy(path, directory);

    strcat(path, "main.txt");
    FILE *current = fopen(path, "a+");
    if (!current) {
        printf("Unable to open game, please make sure that everything is entered correctly and try again\nAlso make sure that you have created the directory that you have specified!\n");
        return 0;
    }

    int decision;

    while (1) {
        printf("Currently in %s\n\n", path);
        fseek(current, 0, SEEK_SET);
        displayFile(current);

        printf("\nWhat would you like to do now?\n");
        printf("1. Create new working file and change to it\n");
        printf("2. Change to different working file\n");
        printf("3. Edit current file\n");
        printf("4. Quit Maker\n");

        printf("Choice: ");
        scanf("%d", &decision); getc(stdin);

        if (decision == 1) {
            fclose(current);
            current = new(directory);
            if (!current) {
                printf("Unable to create file!\nMake sure that you don't have another file in the directory of the same name!\n");
                return 0;
            }
        }
        else if (decision == 2) {
            fclose(current);
            current = change(directory);
            if (!current) {
                printf("Unable to change to file!\nMake sure that you entered the name correctly!\n");
                current = fopen(path, "a+");
            }
        }
        else if (decision == 3) {
            edit(current, directory);
        }
        else if (decision == 4) 
            break;
        else
            printf("Invalid Selection! Please try again\n");
    }

    return 1;
}

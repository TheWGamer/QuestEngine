#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 1024

typedef char page[LENGTH];

void printCurrent(FILE *fp) {
    page buffer;
    
    while (1) {
        fgets(buffer, 1024, fp);

        if (!strcmp(buffer, "#@#\n"))
            break;
    }

    while(!feof(fp)) {
        buffer[0] = '\0';
        fgets(buffer, LENGTH, fp);
        printf("%s", buffer);
    }
}

int main() {
    page directory, path;
    
    printf("Game Directory: ");
    scanf("%s", directory); getc(stdin);

    strcat(directory, "//");
    strcpy(path, directory);

    strcat(path, "main.txt");
    FILE *current = fopen(path, "r");
    if (!current) {
        printf("Unable to open game, please make sure that everything is entered correctly and try again\n");
        return 0;
    }

    int choices; // Number of branches in a page
    int decision; // The branch the player chooses to pursue
    page buffer;

    while (1) {
        printf("\n");
        fscanf(current, "%d\n", &choices);

        page *branches = (page *) malloc (choices * sizeof(page)); //The file paths associated with the branches in the current page
        for (int i = 0; i < choices; i++) {
            fscanf(current, "%s\n", buffer);

            strcpy(branches[i], directory);
            strcat(branches[i], buffer);
        }

        printCurrent(current);

        if (choices > 0) {
            printf("Choice: ");
            scanf("%d", &decision); getc(stdin);

            if (decision > 0 && decision <= choices) {
                fclose(current);
                --decision;

                current = fopen(branches[decision], "r");
                if (!current) {
                    printf("ERROR!\nCOULD NOT LOCATE BRANCH FILE!\n");
                    return 0;
                }

                free(branches);
            }
            else {
                printf("Hm, that doesn't seem to be an option here... Please try again!\n");
                fseek(current, 0, SEEK_SET);
            }
        }
        else {
            printf("\nGAME OVER!\n");
            break;
        }
    }

    return 1;
}
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
//Alexis Indick
//Autocomplete for CSC 344
//2/17/2021
struct Node {
    char c; //Don't put counter before c, program won't work!
    int counter;

    char f[200][100]; //2D Array for file names
    struct Node *next;
} Node;
int main() {

    char *userDir = malloc(sizeof(char) * 300);



    //This is for making the 26 node Linked List.
    struct Node *head = malloc(sizeof(Node));
    struct Node *current = head;
    head->c = '0';
    head->next = NULL;

    //Accounts for ascii values
    for (int i = 1; i < 127; i++) {
        current->next = malloc(sizeof(Node));
        current = current->next;
        current->c = '0';
        current->counter = 0;
    }




    //Obtains user directory
    printf("Enter a folder name: ");
    scanf("%s", userDir);




    //Reads all the file names in a directory and sorts them into a Linked List.
    DIR *dir;
    struct dirent *dStruct;
    dir = opendir("C:\\Users\\13154\\OneDrive\\Documents");


    while ((dStruct = readdir(dir)) != NULL) {
        struct Node *current = head;

        int k = 1;


        while (k) {
            if (current->c != '0') {
                if (tolower(current->c) == tolower(dStruct->d_name[0])) {

                    //Places file in current node
                    strcpy(current->f[current->counter], dStruct->d_name);
                    current->counter++;
                    k = 0;
                }
                current = current->next;
            } else {
                //Defines the current node c as the first char of the file
                current->c = dStruct->d_name[0];

                //Puts the file in the current node
                strcpy(current->f[current->counter], dStruct->d_name);
                current->counter++;
                k = 0;
            }
        }
    }
    closedir(dir);

    //Will ask user for a prefix and then, when the string is = to 0, the program ends.

    char *pre = malloc(sizeof(char) * 100);
    fgets(pre, sizeof(pre), stdin);

    //Calculates the length of the # of chars before the 1st occurrence of the char is present.
    pre[strcspn(pre, "\n ")] = '\0';

    do {
        printf("\nFiles that begin with: ");

        fgets(pre, sizeof(pre), stdin);

        //Calculates the length of the # of chars before the 1st occurrence of the char is present.
        pre[strcspn(pre, "\n")] = '\0';

        struct Node *curr = head;
        while (curr->next != NULL) {
            if (tolower(curr->c) == tolower(pre[0])) {
                for (int j = 0; j < 50; j++) {


                    int a = strncmp(pre, curr->f[j], strlen(pre));

                    if(a == 0) {
                        printf("%s\n",curr->f[j]); //print the file names
                    }
                }
                break;
            } else {
                curr = curr->next;
            }
        }
    //Compares the string with the size of that string
    } while (strncmp(pre, "", sizeof(pre)));



    return (0);
}
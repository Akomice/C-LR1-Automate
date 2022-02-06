#include <stdlib.h>
#include <stdio.h>

#include "string.h"

void add_char(char **my_string,char c) {
    int i = 0; //Indice parcourant la chaine de caractère
    char *new = *my_string; 
    while (new[i] != '\0') i+=1; //Recherche de la fin, cette dernière existant grâce à la précondition sur my_string
    new[i+1]='\0'; //Décalage de la fin
    new[i]=c; //Ajout du caractère
}

int stringsize(char *my_string) {
    int size = 0; //Déclaration de la variable représentant la taille de la chaine
    while (my_string[size] != '\0') size+=1; //Recherche de la fin, cette dernière existant grâce à la précondition sur my_string
    return size;
}

void contraction(char **my_string) {
    int possede_alphabet_minuscule = 0;
    int possede_alphabet_majuscule = 0;
    int c = 65;
    int d = 97;
    char *new = *my_string;
    int n = stringsize(new);
    for (int i = 0 ; i < n ; i+=1 ) {
        if (new[i] == c) {
            c += 1;
        }
        if (new[i] == d) {
            d+=1;
        }
    }
    if (c == 91) {
        possede_alphabet_majuscule = 1;
    }
    if (d == 123) {
        possede_alphabet_minuscule = 1;
    }
    if (possede_alphabet_majuscule == 1 && possede_alphabet_minuscule == 1) {
        new[0] = '\0';
        add_char(&new,'A');
        add_char(&new,'-');
        add_char(&new,'Z');
        add_char(&new,'a');
        add_char(&new,'-');
        add_char(&new,'z');
    }
}

#include <stdlib.h>
#include <stdio.h>

#include "parser.h"

action value_action(octet *buffer,octet s, char c, int debut) { //debut représente l'indice de l'action (0,0), on utilise la division euclidienne ensuite
    return buffer[debut+s*128+c]; //On traite s et c comme des entiers et on cherche la valeur d'action au bon indice
}

octet premiere_composante_reduit(octet* buffer, int debut,octet s) {
    return buffer[debut+s];//debut représente la première composante de réduit(0)
}

octet deuxieme_composante_reduit(octet* buffer, int debut,octet s) {
    return buffer[debut+s];//debut représente la deuxième composante de réduit(0)
}

octet decale(int debut, int fin, octet *buffer, octet s, char c) {
    int i = debut;
    while (i <= fin && (buffer[i]!=s || buffer[i+1]!=c) ) { 
        i += 1;
    }
    return buffer[i+2];
}

octet branchement(int debut, int fin, octet *buffer, octet s, octet a) {
    int i = debut;
    while (i <= fin && (buffer[i]!=s || buffer[i+1]!=a )) { 
        i += 1;
    }
    return buffer[i+2];
}


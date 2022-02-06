#ifndef _PARSER_H
#define _PARSER_H

typedef unsigned char octet;

typedef int action;

/* La fonction value_action 
@ requires : une chaine d'octets 'buffer' valide
@ assigns : rien
@ ensures : renvoie l'action correspondant à l'état s et au caractère c
*/
action value_action(octet *buffer,octet s, char c, int debut);

/* La fonction premiere_composante_reduit
@ requires : une chaine d'octets 'buffer' valide
@ assigns : rien
@ ensures : renvoie la première composante de réduit correspondant à l'état s
*/
octet premiere_composante_reduit(octet* buffer, int debut,octet s);

/* La fonction deuxieme_composante_reduit
@ requires : une chaine d'octets 'buffer' valide
@ assigns : rien
@ ensures : renvoie la deuxième composante de réduit correspondant à l'état s
*/
octet deuxieme_composante_reduit(octet* buffer, int debut,octet s);

/* La fonction decale
@ requires : une chaine d'octets 'buffer' valide
@ assigns : rien
@ ensures : renvoie le résultat de la fonction partielle décale appliquée à l'état s et au caractère c
*/
octet decale(int debut, int fin, octet *buffer, octet s, char c);

/* La fonction branchement
@ requires : une chaine d'octets 'buffer' valide
@ assigns : rien
@ ensures : renvoie le résultat de la fonction partielle branchement appliquée à l'état s et à l'octet a
*/
octet branchement(int debut, int fin, octet *buffer, octet s, octet a);

#endif
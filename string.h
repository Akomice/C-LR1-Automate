#ifndef _STRING_H
#define _STRING_H

/* La fonction add_char 
@ requires : 'my_string' valide et est une chaine de caractère (au sens où elle possède un élement égal à '\0')
@ assigns : ajoute un élement à la chaine de caractère 'my_string'
@ ensures : ajoute le caractère 'c' à la chaine de caractère 'my_string'
*/
void add_char(char** my_string,char c);

/* La fonction stringsize 
@ requires : 'my_string' valide et est une chaine de caractère (au sens où elle possède un élement égal à '\0')
@ assigns : rien
@ ensures : renvoie la taille de la chaine de caractère 'my_string'
*/
int stringsize(char* my_string);

/* La fonction contraction 
@ requires : 'my_string' valide et est une chaine de caractère (au sens où elle possède un élement égal à '\0') qui possède l'alphabet majuscule puis minuscule collé
@ assigns : modifie la chaine 'my_string'
@ ensures : remplace les suites de l'alphabet par des contractions
*/
void contraction(char **my_string);

#endif
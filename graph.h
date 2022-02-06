#ifndef _GRAPH_H
#define _GRAPH_H

/* La fonction draw_graph
@ requires : une chaine d'octets 'buffer' valide, une chaine de caractère 'graphfilename' valide
@ assigns : rien
@ ensures : crée un fichier au format .dot correspondant à l'automate donné en entrée
*/
void draw_graph(char *graphfilename, octet *buffer, int n);

#endif
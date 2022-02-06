#include <stdlib.h>
#include <stdio.h>

#include "string.h"
#include "parser.h"
#include "graph.h"

void draw_graph(char *graphfilename, octet *buffer, int n) {
    FILE *fp;
    /* Création du fichier .dot et ouverture en écriture et troncature, portant le nom graphfilename (donné en argument) */
    fp = fopen(graphfilename,"w+");
    /* Instruction au format DOT permettant de créer un graphe sans répétition d'arếtes (strict) et possédant une arête pointant vers Q0 */
    fprintf(fp,"strict digraph {\n -1[style=\"invis\"];\n -1->Q0;\n ");

    /* Les informations suivantes ont été récupéré grâce à l'analyse de la structure d'un fichier .aut */
    /* On peut alors récupérer l'indice du début des valeurs de chaque fonction grâce aux formules suivantes */
    
    int nb_de_chiffres_de_n = n / 10;
    int position = 3 + nb_de_chiffres_de_n;
    int debut_action = position + 1;
    int debut_reduit_1 = debut_action + n * 128 + 1;
    int debut_reduit_2 = debut_reduit_1 + n + 1;
    int debut_decale = debut_reduit_2 + n + 1;
    int fin_decale;
    int debut_branchement;
    int fin_branchement;

    fin_decale = debut_decale;

    /* Les deux boucles while terminent si le fichier donné en argument est un fichier conforme aux normes d'un fichier .aut */

    while (buffer[fin_decale] != (octet)'\255' || buffer[fin_decale+1] != (octet)'\255' || buffer[fin_decale+2] != (octet)'\255') {
        fin_decale+=1;
    }
    debut_branchement = fin_decale+3;

    fin_branchement = debut_branchement;
    while ((buffer[fin_branchement] != (octet)'\255') || (buffer[fin_branchement+1] != (octet)'\255') || (buffer[fin_branchement+2] != (octet)'\255')) {
        fin_branchement+=1;
    }

    int node_number = 0; //Déclaration du variable qui va parcourir les états de l'automate
    char* label_reduit = malloc(sizeof(char)*128); //label correspond au label associée aux arêtes de réduction
    char* labels; //labels correspond au label associée aux autres arêtes (décale,validation)

    int mat_adj[n][n];
    char *label_decale[n][n];

    for (int k = 0 ; k < n ; k +=1 ) {
        for (int l = 0 ; l < n ; l+=1 ) {
            mat_adj[k][l] = 0;
            label_decale[k][l] = malloc(sizeof(char) * 256);
            label_decale[k][l][0] = '\0'; 
        }
    }

    while (node_number < n) { //node_number est incrémenté de 1 à chaque tour de boucle d'où la terminaison
        label_reduit[0]='\0'; //A un etat donné on initialise label_reduit comme une chaine de caractères vide que l'on remplira s'il le faut
        for (int c = 0; c < 128 ; c+=1) { //Parcourt de l'ensemble des caractères (code ascii entre 0 et 127 compris)
            switch(c) { //Petite traduction sur les caractères spéciaux : un \0 impose d'afficher '\0' à l'écran, d'où les changements nécessaires
                    case 0:
                        labels = "\'\\\\0\'";
                        break;
                    case 8:
                        labels = "\'\\\\b\'";
                        break;
                    case 10:
                        labels = "\'\\\\n\'";
                        break;
                    case 30:
                        labels = "\'\\\\␞\'";
                        break;
                    default: //Sinon, on prend simplement le caractère comme label
                        labels=malloc(sizeof(char)*2);
                        labels[0]=c;
                        labels[1]='\0';
                        break;
            }
            switch(value_action(buffer,node_number,c,debut_action)) {  //On regarde ce que vaut action(s,c) avec s = node_number et c variant dans la boucle
                case 1: //Si action vaut 1, on doit relier node_number à Accepte
                    fprintf(fp,"Accepte [shape=plaintext fontcolor=green color=green];\n ");
                    fprintf(fp,"Q%i -> Accepte [color=green fontcolor=green label=\"%s\"];\n ",node_number,labels);
                    break;
                case 2: ;//Si action vaut 2, on relie node_number à la valeur de décale(s,c)
                    octet value_decale = decale(debut_decale,fin_decale,buffer,node_number,c);
                    mat_adj[node_number][value_decale] = 1;
                    char *label_dec = label_decale[node_number][value_decale];
                    for (int m = 0 ; m < stringsize(labels) ; m+=1) {
                        add_char(&label_dec,labels[m]);
                    }
                    break;
                case 3: //Si action vaut 3, on ajoute à label_reduit le label du caractère (préalablement modifié si c'est un '\n' par exemple)
                    for (int m = 0 ; m < stringsize(labels) ; m+=1) {
                        add_char(&label_reduit,labels[m]);
                    }
                    //Puis on relie les couples (i,j), i<j entre eux si branchement(i,A) = j avec A la deuxième composante de reduit(node_number)
                    int a = deuxieme_composante_reduit(buffer,debut_reduit_2,node_number);
                    for (int i =0; i < n ; i+=1 ) {
                        for (int j = i + 1 ; j < n ; j+=1 ) {
                            int test =branchement(debut_branchement,fin_branchement,buffer,i,a);
                            if ((test!=-1) && (test == j)) {
                                fprintf(fp,"Q%i -> Q%i [color=red fontcolor=red label=\"%c\"];\n ",i,j,a);
                            }
                        }
                    }
                    break;
            }
        }
        for (int k = 0 ; k < n ; k+=1 ) {
            if (mat_adj[node_number][k] == 1) {
                char *new_label = label_decale[node_number][k];
                contraction(&new_label);
                fprintf(fp,"Q%i -> Q%i [label=\"%s\"];\n ",node_number,k,label_decale[node_number][k]);
            }
        } 
        //A un node_number donné, si on a eu des action valant 3 (i.e. label_reduit n'est pas vide), on crée l'arête reliant vers une réduction
        int prem = premiere_composante_reduit(buffer,debut_reduit_1,node_number);
        int deux = deuxieme_composante_reduit(buffer,debut_reduit_2,node_number);
        if (label_reduit[0] != '\0') {
            if (prem != 255)
            {
                fprintf(fp,"%i [label=\"(%i,%c)\" shape=plaintext fontcolor=blue];\n ",node_number,prem,deux); 
                fprintf(fp,"Q%i -> %i [label=\"%s\" color=blue fontcolor=blue];\n ",node_number,node_number,label_reduit);
            }
        }
        node_number+=1;
    }
    fprintf(fp,"}");
    fclose(fp);
}

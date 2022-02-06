#include <stdlib.h>
#include <stdio.h>

#include "parser.h"
#include "stack.h"
#include "string.h"
#include "graph.h"

int main(int argc, char *argv[]) {

    /* Vérification du bon nombre d'argument donné en entrée*/

    if (argc != 2) {
        printf("Usage : wrong number of arguments (given : %i, expected : 1)\n",argc-1);
        exit(1);
    }

    /* Petite opération sur le nom du fichier, on réalise une troncature sur un file.aut pour obtenir le string file et permettre ainsi la création d'un file.dot */
    
    char filename[256];
    char graphfilename[260];
    sscanf(argv[1],"%[^.]s",filename);
    sprintf(graphfilename,"%s.dot",filename);

    //graphfilename contient ainsi 'file.dot'

    /* ouverture du fichier */

    FILE *fsrs;
    if ((fsrs = fopen(argv[1],"r")) == NULL ) {
        printf("File unreadable\n");
        exit(1);
    }

    /* obtention de la taille du fichier */
    
    fseek(fsrs , 0 , SEEK_END);
    long length = ftell(fsrs);
    rewind(fsrs);
    
    /* allocation du tampon de lecture du fichier */

    octet *buffer;
    buffer = malloc(sizeof(octet)*length); 
    /* la totalité du fichier se retrouve alors dans le tampon buffer*/
    fread(buffer,length,1,fsrs);
    rewind(fsrs);
    
    /* On récupère l'entier n */

    int n;
    sscanf((char *)buffer,"a %i\n",&n);

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
    /* Sinon, le cas de sortie est lorsque l'indice arrive au bout du fichier, et dans ce cas crée une erreur */

    while ((buffer[fin_decale] != (octet)'\255' || buffer[fin_decale+1] != (octet)'\255' || buffer[fin_decale+2] != (octet)'\255') && fin_decale < length) {
        fin_decale+=1;
    }
    debut_branchement = fin_decale+3;

    if (fin_decale == length) {
        printf("File \"%s.aut\" incorrectly read.\n",filename);
        exit(1);
    }

    fin_branchement = debut_branchement;
    while (((buffer[fin_branchement] != (octet)'\255') || (buffer[fin_branchement+1] != (octet)'\255') || (buffer[fin_branchement+2] != (octet)'\255')) && fin_branchement < length) {
        fin_branchement+=1;
    }

    if (fin_branchement == length) {
        printf("File \"%s.aut\" incorrectly read.\n",filename);
        exit(1);
    }

    
    /* Création du fichier .dot correspondant */

    draw_graph(graphfilename,buffer,n);

    /* Arrivé ici, le fichier est donc correctement lu et on est prêt à recevoir les entrées */

    printf("File \"%s.aut\" correctly read. Please enter your inputs.\n",filename);

    /* Boucle infinie correspondant à la volonté de pouvoir continuer à écrire des mots dans l'entrée sans arrêt */

    while (1) {
        char buf[256]; //buf représente la chaine de caractère donné en entrée
        stack_t * pile = initialise(); // Création d'une pile avec comme état initial 0
        fgets(buf,256,stdin);
        int lengthofchar = stringsize(buf);
        int i = 0; // indice parcourant la chaine de caractère
        while (i<=lengthofchar) { 
            int val = value_action(buffer,top_of_stack(pile),buf[i],debut_action); 
            switch(val) {//On agit en fonction de la valeur de action(s,c) où s est le haut de la pile (l'état courant) et c le caractère de la chaine
                case 0:
                    if (i < lengthofchar - 1) printf("Rejected : %c char at position number : %i\n",buf[i],i); //Si on a un rejet lors du parcours de la chaine, c'est le caractère qui crée l'erreur : on l'affiche donc
                    else printf("Rejected : Missing chars\n"); //Si on a un rejet à la fin, c'est qu'il doit manquer un ou plusieurs caractères 
                    break;
                case 1:
                    printf("Accepted\n");//On accepte le mot si l'action vaut 1
                    break;
                case 2:
                    add_stack(decale(debut_decale,fin_decale,buffer,top_of_stack(pile),buf[i]),&pile); //On empile décale(s,c) si action vaut 2 
                    i+=1; //On passe au caractère suivant
                    break;
                case 3: ;
                    // On suit l'instruction de l'énoncé, si action(s,c) vaut 3, alors en notant (n,am) = reduit(s), on dépile n fois et on empile branchement(s',A)
                    octet n_reduit = premiere_composante_reduit(buffer,debut_reduit_1,top_of_stack(pile));
                    octet am = deuxieme_composante_reduit(buffer,debut_reduit_2,top_of_stack(pile));
                    for (int j = 0 ; j < n_reduit ; j+=1) {
                        del(&pile);
                    }
                    add_stack(branchement(debut_branchement,fin_branchement,buffer,top_of_stack(pile),am),&pile);
                    break;
            }
            if (val == 0 || val == 1) { // Si on a un rejet ou un accepte, on peut passer au mot suivant
                break;
            }
        }
    }
    fclose(fsrs);
    return 0;
}

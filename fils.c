#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "fonction_bases.h"

int main(int argc, char *argv[]) {
    char lettre = argv[2][0];
    char *message = argv[1];
    int taille_message = 0, i = 0;
    while (message[i] != '\0') {
        taille_message++;
        i++;
    }
    taille_message++; // Pour le caractère '\0'
    float indice_max = 0.;
    char *clef_associee = "aa";
    char *meilleur_message = malloc(sizeof(char)*taille_message);
    for (int i = 'a'; i <= 'z'; i++) {
        char *clef = malloc(sizeof(char)*3);
        sprintf(clef, "%c%c",lettre, i);
        int taille_clef = 2;
        char *message_decrypte = malloc(sizeof(char)*taille_message);
        decryptage(message, message_decrypte, clef, taille_clef);
        float indice_tmp = indice_de_coincidence(message_decrypte);
        if (indice_tmp > indice_max) {
            indice_max = indice_tmp;
            clef_associee = clef;
            meilleur_message = message_decrypte;
        }
    }
    char buffer[1024];
    sprintf(buffer, "indice_max = %.8f avec %s\n%s\n\n", indice_max, clef_associee, meilleur_message);
    printf("%s", buffer);
    return 0;
}

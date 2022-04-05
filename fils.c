#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>

#include "fonction_bases.h"

int main(int argc, char *argv[]) {
    char *message = argv[1];
    int taille_message = strlen(message);

    char *lettre = argv[2];

    char *clef = malloc(sizeof(char)*2);

    float meilleur_indice = 0.0;
    char *meilleure_clef = malloc(sizeof(char)*2);
    char *meilleur_message = malloc(sizeof(char) * taille_message);

    for (int i = 'a'; i <= 'z'; i++) {
        sprintf(clef, "%s%c",lettre, i);
        char *message_dechiffre = malloc(sizeof(char)*taille_message);
        decryptage(message, message_dechiffre, clef, 2);
        float indice_actuel = indice_de_coincidence(message_dechiffre);
        // printf("(%s --- %s = %.15f)\n", message_dechiffre, clef, indice_actuel); fflush(stdout); // debug
        
        // Comparaison des indices de co.
        if (indice_actuel > meilleur_indice) {
            meilleur_indice = indice_actuel;
            strcpy(meilleure_clef, clef);
            strcpy(meilleur_message, message_dechiffre);
        }
    }

    // printf("message: %s\nclef: %s et indice: %f\n", meilleur_message, meilleure_clef, meilleur_indice); fflush(stdout);

    /* Résultats dans fichier */
    char *nom_fichier = malloc(sizeof(char) * 13);
    char *nom_fixe = "out/res_";
    strcat(nom_fichier, nom_fixe);
    strcat(nom_fichier, lettre);
    strcat(nom_fichier, ".txt");

    // printf("nom fichier: %s\n", nom_fichier); fflush(stdout); // debug

    mkdir("out", 00777);
    int desc = open(nom_fichier, O_WRONLY|O_CREAT, 00777);
    char *meilleur_indice_str = malloc(sizeof(char) * 17);
    sprintf(meilleur_indice_str, "%.15f", meilleur_indice);
    write(desc, meilleur_indice_str, strlen(meilleur_indice_str));
    write(desc, "\n", 1);
    
    write(desc, meilleure_clef, 2);
    write(desc, "\n", 1);

    write(desc, meilleur_message, strlen(meilleur_message));
    close(desc);
    exit(0);
}

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
            // printf("(%s --- %s = %f)\n", message_decrypte, clef, indice_tmp); // debug
        }
    }
    char buffer[10000];
    sprintf(buffer, "%.9f\n%s\n%s", indice_max, clef_associee, meilleur_message);
    int taille_buffer = 0;
    i = 0;
    while (buffer[i] != '\0') {
        taille_buffer++;
        i++;
    }
    // printf("%s", buffer); // debug

     /* Résultats dans fichier */
    char *nom_fichier = malloc(sizeof(char) * 14);
    char *nom_fixe = "out/res_";
    char *lettre_var = malloc(sizeof(char) * 2);
    lettre_var[0] = argv[2][0]; lettre_var[1] = '\0';
    strcat(nom_fichier, nom_fixe);
    strcat(nom_fichier, lettre_var);
    strcat(nom_fichier, ".txt");
    mkdir("out", 00777);
    // printf("nom du fichier : %s\n", nom_fichier); // debug
    int desc = open(nom_fichier, O_WRONLY|O_CREAT, 00777);

    write(desc, &buffer, taille_buffer);
    close(desc);
    exit(0);
    return 0;
}

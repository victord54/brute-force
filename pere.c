#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include "fonction_bases.h"

int main(int argc, char *argv[]) {
    pid_t fils;
    struct stat sb;
    char *fichier = argv[1];

    if (stat(fichier, &sb) == -1) {
        perror("Erreur stat");
        exit(-1);
    }

    int taille = sb.st_size;

    int desc = open(fichier, O_RDONLY);

    char *message = malloc(sizeof(char) * taille);

    read(desc, message, taille);
    close(desc);

    if (argc < 2) {
        printf("Arguments manquants\n");
        exit(-1);
    }

    for(int i = 'a'; i <= 'z'; i++) {
        char lettre[1];
        lettre[0] = i;
        fils = fork();

        if (fils == -1) {
            perror("Création impossible\n");
            exit(-1);
        } else if (fils == 0) {
            fflush(stdout);
            if (execl("./fils", "fils", message, lettre, NULL) == -1) {
                perror("Recouvrement impossible");
                exit(-1);
            }
        } else {
            wait(NULL);
        }
    }
    char *nom_fichier = malloc(sizeof(char) * 13);
    float meilleur_indice = 0.0;
    char *meilleure_clef = malloc(sizeof(char)*2);
    char *meilleur_message = malloc(sizeof(char) * taille);
    for (int i = 'g'; i <= 'i'; i++) {
        float indice = 0.0;
        char *indice_str = malloc(sizeof(char) * 17);
        char *clef = malloc(sizeof(char)*2);
        char *message = malloc(sizeof(char) * taille);
        sprintf(nom_fichier, "out/res_%c.txt", i);
        // printf("nom_fichier: %s\n", nom_fichier); // debug
        int desc = open(nom_fichier, O_RDONLY);
        read(desc, indice_str, 17);
        read(desc, clef, 1); // juste pour lire le saut de ligne dans le vide
        read(desc, clef, 2);
        read(desc, message, 1); // juste pour lire le saut de ligne dans le vide
        read(desc, message, taille);
        close(desc);
        indice = indice_de_coincidence(message);
        if (indice > meilleur_indice) {
            meilleur_indice = indice;
            strcpy(meilleure_clef, clef);
            strcpy(meilleur_message, message);
        }
    }

    printf("clef la plus probable: %s\n", meilleure_clef);
    printf("message le plus probable:\n\t %s\n", meilleur_message);
    return 0;
}

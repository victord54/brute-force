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
    int status;
    pid_t fils;

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
            if (execl("./fils", "fils", argv[1], lettre, NULL) == -1) {
                perror("Recouvrement impossible");
                exit(-1);
            }
        }
    }
    sleep(1); // sinon la boucle du dessous ne récupère pas tout !
    printf("\n");
    while (wait(&status) != fils) {
        printf("...");
        fflush(stdout);
    }
    printf("\n");
    float ind_max = 0, ind_tmp = 0;
    char *buffer_max = malloc(sizeof(char) * 10000);
    char *clef_finale = malloc(sizeof(char) * 3);
    for (int i = 'a'; i <= 'z'; i++) {
        char *buffer = malloc(sizeof(char) * 10000);
        char *nom_fichier = malloc(sizeof(char) * 14);
        char *nom_fixe = "out/res_";
        char *lettre_var = malloc(sizeof(char) * 2);
        lettre_var[0] = i; lettre_var[1] = '\0';
        strcat(nom_fichier, nom_fixe);
        strcat(nom_fichier, lettre_var);
        strcat(nom_fichier, ".txt");
        int desc = open(nom_fichier, O_RDONLY);
        read(desc, buffer, 11);
        ind_tmp = atof(buffer);
        if (ind_tmp > ind_max) {
            ind_max = ind_tmp;
            read(desc, buffer_max, 1); // Pour enlever le saut de ligne
            read(desc, clef_finale, 2); // Stocker la clé
            clef_finale[2] = '\0';
            read(desc, buffer_max, 1); // Pour enlever le saut de ligne
            read(desc, buffer_max, 10000);
            close(desc);
        }
    }
    printf("Clef : %s\nmessage : %s\n", clef_finale, buffer_max);
    return 0;
}

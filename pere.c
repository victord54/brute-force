#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include "fonction_bases.h"

int main(int argc, char *argv[]) {
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

    // lire les fichiers et récup le max.
    return 0;
}

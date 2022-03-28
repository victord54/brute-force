#ifndef FONCTION_BASE_H
#define FONCTION_BASE_H

float indice_de_coincidence(char* text);
void cryptage(char* message, char* new_mess, char* clef, int tailleClef);
void decryptage(char* message, char* new_mess, char* clef, int tailleClef);

#endif

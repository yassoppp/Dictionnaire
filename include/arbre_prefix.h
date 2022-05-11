#ifndef _ARBRE_PREFIX_H
#define _ARBRE_PREFIX_H

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define NUM_ALPHA 26

typedef struct noeud{
    struct noeud* fils[NUM_ALPHA];
    bool est_mot;
}noeud;
typedef noeud* arbre;


noeud* creer_noeud();
void ajouter_mot(arbre* ,char* );
void print_arbre(arbre );
arbre Fichier_en_arbre(char* );
bool search(arbre ,char* );
void free_arbre(arbre );
void trouver_(char* ,arbre* );

#endif
#ifndef ARBRE_LEXI
#define ARBRE_LEXI

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct maillion{
    char lettre;
    struct maillion* fils;
    struct maillion* frere;
    bool est_mot;
}maillion,maillon_t;

typedef maillion* arbre;




maillion* creer_maillon(char );
void ajout(maillion**,char* );
maillion** recherche(maillion**,char* ,int*,int *);

void insertion_mot(maillon_t** , char* , int );

void ajout(arbre* ,char*);

maillon_t** rechercher_mot(maillon_t **, char *, int *, int *);

maillon_t * creer_liste();

void Fichier_en_arbre(arbre* a,char*);

void ajouter_h(maillon_t** prec, maillon_t* maillon);

void ajouter_v(maillon_t** prec, maillon_t* maillon);

void creer_h(maillon_t* cour ,maillon_t* maillon);

void creer_v(maillon_t* cour , maillon_t* maillon);


#endif
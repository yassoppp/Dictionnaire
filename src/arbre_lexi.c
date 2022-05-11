#include "arbre_lexi.h"
#include <ctype.h>
#include <time.h>

#define MAX 50

/*************************************************************************************************************/
/*****************************************Methode de l'arbre_lexigographique**********************************/
/*************************************************************************************************************/





maillion* creer_maillon(char c)
{
    maillion* r=malloc(sizeof(maillion));
    r->est_mot=false;
    r->lettre=c;
    r->fils=NULL;
    r->frere=NULL;
    return r;
}

maillon_t** rechercher_mot(maillon_t **arbre, char *mot_t, int *existe, int *dernier_indice)
{   
    char mot[MAX];
    strncpy(mot,mot_t,sizeof(mot));
    for(unsigned int i=0;i<strlen(mot_t);i++){
        mot[i]=tolower(mot[i]);
    }
    //Les éléments qui vont parcourir l'arbre:
    maillon_t** prec=arbre;
    maillon_t* cour=*arbre;

    //On l'aura besoin pour savoir la place du dernier indice où on a arrêté le traitement.
    *dernier_indice=0;

    //On le passe à 1 si on trouve le mot recherché.
    *existe=0;
    
    int fin=0; //Variable pour détecter la fin de la recherche.

    while(!fin && mot[*dernier_indice]!='\0') //Tant qu'on n'a pas terminé le traitement et tant que le mot n'est pas terminé.
    {
         
        if (cour) //Si cour arrive à nulle on termine la procédure ; fin reçoit 1.
        { 

            //Si la lettre dans la cellule correspond à la lettre dans le mot et le mot ne se terminera pas à la prochaine itération.
            if ((tolower((cour)->lettre)==mot[*dernier_indice]) && (mot[*dernier_indice+1]!='\0'))
            { 
                prec=&(cour->fils);
                cour=cour->fils;
                (*dernier_indice)++;
            }

            //Si la lettre dans la cellule correspond à la lettre dans le mot et le mot se terminera à la prochaine itération.
            else if((tolower(cour->lettre)==mot[*dernier_indice]) && (mot[*dernier_indice+1]=='\0') && (cour->est_mot==true))
            { 
                fin=1;
                *existe=1; //Fin de la recherche et mot trouvé.
                (*dernier_indice)++;
            }

            //Si la lettre dans la cellule est inférieure à la lettre dans le mot.
            else if ((tolower((cour)->lettre) < mot[*dernier_indice]))
            {
                prec=&(cour->frere);
                cour=cour->frere;
            }
            else
            {
                fin=1;
            }

        }
        else
        {
            fin=1;  //Fin de la recherche et mot non trouvé.
        }
    }
    return prec;
}

void insertion_mot(maillon_t** prec, char* mot, int dernier_indice)
{
    maillon_t *nv_lettre=creer_maillon(mot[dernier_indice]); //On crée une maillon contenant la nouvelle lettre qui compléte le mot

    ajouter_h(prec, nv_lettre); //On insére horisontalement pour la première lettre.

    prec=&(nv_lettre->fils); //prec prfin l'adresse du fils de la nouvelle lettre.
    
    dernier_indice++;
   

    while(mot[dernier_indice]!='\0') //Tant qu'on n'a pas terminé le mot.
    {
        nv_lettre=creer_maillon(mot[dernier_indice]);
        ajouter_v(prec, nv_lettre); //On insére verticalement chaque nouvelle lettre.
        prec=&(nv_lettre->fils); //prec prfin l'adresse du fils de la nouvelle lettre.
        dernier_indice++; 
    }

    nv_lettre->est_mot=1; //La dernière lettre doit être en majuscule.
}

void ajout(arbre* a,char* mot)//fonction pour ajouter un mot dans la structure de l'arbre l'exicographique
{
    int indice;
    int existe=0;
    maillion** prec=rechercher_mot(a,mot,&existe,&indice);
    if(existe==1){
        printf("le mot existe dans l'arbre");
    }else{
        insertion_mot(prec,mot,indice);
    }
}

void liberer_arbre(maillon_t* arbre)
{   
    //parcourir jusqu a trouver un NULL puis liberer les fils et les freres
    maillon_t* cour=arbre;
    if(!arbre) return;
    if(cour->fils) liberer_arbre(cour->fils);
    if(cour->frere) liberer_arbre(cour->frere);
    free(cour);
    arbre=NULL;
}

void trouver_(char* text,arbre* a){
    char mot[MAX];
    for(int i=0;i<MAX;i++){
        mot[i]='\0';
    }//pour obtenir un mot que avec des caracteres 0
    char c;
    int i=0;
    FILE* fichier=fopen(text,"r");//ouvrir le texte
    if(fichier==NULL){
        printf("erreur d'ouverture du fichier texte\n");
        exit(1);
    }
    FILE* resultat=fopen("./tests/resultats_arbre_lexi","w");//ouvrir le fichier ou on mettra les resultat
    if(resultat==NULL){
        printf("erreur d'ouverture du fichier resultat\n");
        exit(2);
    }
    fputs("*****************************************Methode de l'arbre_lexigographique**********************************\n\n",resultat);
    fputs("les mot qui sont dans le dictionnaire mais pas dans le texte sont: \n\n",resultat);
    do{// lire le text jusqu'a trouver un caractere special et determiner le mot avant de le chercher
        c=fgetc(fichier);
        if((c>='a'&& c<='z') || (c>='A' && c<='Z')){
            mot[i]=c;
            i++;
        }else if(mot[0]!='\0'){
            int existe=0;
            int indice=0;
            maillion** b=rechercher_mot(a,mot,&existe,&indice);
            (void)b;
            if(!existe){
                fputs(mot,resultat);
                fputs("\n",resultat);
            }
            for(int i=0;i<MAX;i++){//remettre le mot a 0
                 mot[i]='\0';
            }
            i=0;
        }   
    }while(c!=EOF); 
    fclose(fichier);
    fclose(resultat);
}
/*-----------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------Des fonction pour manipuler les pile------------------------------*/

maillon_t * creer_liste()
{
    return NULL;
}

void ajouter_h(maillon_t** prec, maillon_t* maillon)
{
    maillon->frere=*prec;
    *prec=maillon;
}

void ajouter_v(maillon_t** prec, maillon_t* maillon)
{
    maillon->fils=*prec;
    *prec=maillon;
}

void creer_h(maillon_t* cour ,maillon_t* maillon)
{
    cour->frere=maillon;
}

void creer_v(maillon_t* cour , maillon_t* maillon)
{
    cour->fils=maillon;
}
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/
void Fichier_en_arbre(arbre* a,char* fichier){
    char chaine[50];
    FILE* f=fopen(fichier,"r");
    if(f!=NULL){
        while(fgets(chaine,50,f)){
            chaine[strlen(chaine)-1]='\0';
            ajout(a,chaine);
        }
    }
    fclose(f);
}
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/

int main(int argc,char* argv[]){
    (void)argc;
    int t=clock();
    arbre a=NULL;
    Fichier_en_arbre(&a,argv[1]);//remplir l'arbre lexicographique a partir du dictionnaire
    trouver_(argv[2],&a);//chercher les mots qui n'existent pas et les mettre dans un fichier resultats; 
    liberer_arbre(a);
    t=clock()-t;
    printf("\n\n\n\n");
    printf("*****************************************************************************\n");
    printf("le temps d'execution pour l'arbre lexicograpphique est %lf s\n",t/(double)CLOCKS_PER_SEC);
    printf("le resultat est dans le dossier tests\n");
    printf("*****************************************************************************\n");
    printf("\n\n\n\n");
    return 0;
}



/************************************************************************************************************/
/******************************************     fin     *****************************************************/

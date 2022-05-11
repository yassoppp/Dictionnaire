#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

/*************************************************************************************************************/
/*******************************************Methode de l'atable de hashage************************************/
/*************************************************************************************************************/

#define MAX 50
#define TAILLE_HACHAGE 2000

int hash(char* mot_t){
    int a=0;
    char mot[MAX];
    strncpy(mot,mot_t,sizeof(mot));
    for(unsigned int i=0;i<strlen(mot_t);i++){
        a=a+mot[i];
    }
    return a%TAILLE_HACHAGE;
}
typedef struct noued{
    char word[MAX];
    struct noued* next;
}noued;
noued* hash_tab[TAILLE_HACHAGE];

void ajouter(noued** pile,noued* sommet){
    sommet->next=*pile;
    *pile=sommet;
}
noued* creer_noued(char*mot_t){
    char mot[MAX];
    strncpy(mot,mot_t,sizeof(mot));
    noued* resultat=malloc(sizeof(noued));
    strncpy(resultat->word,mot,sizeof(mot));
    resultat->next=NULL;
    return resultat;
}
/************************************************************************************************************/
/************************************************************************************************************/



void init_hash_tab(){//initialization de la table de hashage
    for(int i=0;i<TAILLE_HACHAGE;i++){
        hash_tab[i]=NULL;
    }
}

bool is_inhash(char mot_t[]){
    char mot[MAX];
    strncpy(mot,mot_t,sizeof(mot));
    for(unsigned int i=0;i<strlen(mot_t);i++){
        mot[i]=tolower(mot[i]);
    }
    int a=hash(mot);
    if(hash_tab[a]==NULL){
        return false;
    }else{
        noued*tmp=hash_tab[a];
        while(tmp!=NULL){
            if(!strcmp(mot,tmp->word)){
                return true;
            }
            tmp=tmp->next;
        }
        return false;
    }
}
void add_mot(char*mot_t){
    char mot[MAX];
    strncpy(mot,mot_t,sizeof(mot));
    int a=hash(mot_t);
    noued*b=creer_noued(mot_t);
    if(!is_inhash(mot)){
        ajouter(&hash_tab[a],b);
    }
}
void free1(noued** liste)
{
    noued* tmp = *liste;
    noued* tmpnxt;
 
    /* Tant que l'on n'est pas au bout de la liste */
    while(tmp != NULL)
    {
        /* On stocke l'élément suivant pour pouvoir ensuite avancer */
        tmpnxt = tmp->next;
        /* On efface l'élément courant */
        free(tmp);
        /* On avance d'une case */
        tmp = tmpnxt;
    }
}

void free_tab(){//free chaque liste pile qui sort des case de la table de hashage
    for(int i=0;i<TAILLE_HACHAGE;i++){
        free1(hash_tab+i);
    }
}


void Fichier_en_hash(char* fichier){
    char chaine[MAX];
    FILE* f=fopen(fichier,"r");
    if(f!=NULL){
        while(fgets(chaine,MAX,f)){
            chaine[strlen(chaine)-1]='\0';
            add_mot(chaine);
        }
    }
    fclose(f);
}

void trouver_(char* text){//comme dans les autres methodes
    char mot[MAX];
    for(int i=0;i<MAX;i++){
        mot[i]='\0';
    }
    char c;
    int i=0;
    FILE* fichier=fopen(text,"r");
    FILE* resultat=fopen("./tests/resultats_tabhash","w");
    if(resultat==NULL){
        printf("erreur d'ouverture du fichier\n");
        exit(1);
    }
    fputs("*****************************************Methode de la table d'hashage**********************************\n\n",resultat);
    fputs("les mot qui sont dans le dictionnaire mais pas dans le texte sont: \n\n",resultat);
    do{
        c=fgetc(fichier);
        if((c>='a'&& c<='z') || (c>='A' && c<='Z')){
            mot[i]=c;
            i++;
        }else if(mot[0]!='\0'){
            if(!is_inhash(mot)){
                fputs(mot,resultat);
                fputs("\n",resultat);
            }
            //printf("%s\n",mot);
            for(int i=0;i<MAX;i++){
                 mot[i]='\0';
            }
            i=0;
        }   
    }while(c!=EOF); 
    fclose(fichier);
    fclose(resultat);
}


int main(){
    init_hash_tab();
    int t=clock();
    Fichier_en_hash("FR.txt");
    trouver_("a_la_recherche_du_temps_perdu.txt");
    free_tab();
    t=clock()-t;
    printf("\n\n\n\n");
    printf("**************************************************************************\n");
    printf("le temps de l'execution de la methode table de hashage est : %lf s\n",t/(double)CLOCKS_PER_SEC);
    printf("le resultat est dans le dossier tests\n");
    printf("**************************************************************************\n");
    printf("\n\n\n\n");
    return 0;

}

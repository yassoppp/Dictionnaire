#include "arbre_prefix.h"



/*************************************************************************************************************/
/*****************************************Methode de l'arbre_Préfix*******************************************/
/*************************************************************************************************************/

#define MAX 50

noeud* creer_noeud(){
    noeud*  n=malloc(sizeof(noeud));
    for(int i=0;i<NUM_ALPHA;i++){
        n->fils[i]=NULL;
    }
    n->est_mot=false;//tous les mot ne sont pas final a leur creation;
    return n;
}

void ajouter_mot(arbre* tree,char* mot){//ajouter un mot a une arbre
    if(*tree==NULL)
    {
        (*tree)=creer_noeud();
    }
    noeud* tmp=(*tree);

    unsigned int longueur_mot=strlen(mot);

    for(unsigned int i=0;i<longueur_mot;i++){

        if(tmp->fils[(unsigned int)mot[i]-(unsigned int)('a')]==NULL)
        {

            tmp->fils[(unsigned int)mot[i]-(unsigned int)('a')]=creer_noeud();
        }

        tmp=tmp->fils[(unsigned int)mot[i]-(unsigned int)('a')];

    }

    tmp->est_mot=true;
}

void print_mot(noeud* curr,char*prefixe, int longueur){
    if(curr->est_mot==true){
        printf("mot : %s\n",prefixe);
    }
    for(int i=0;i<NUM_ALPHA;i++){
        if(curr->fils[i]!=NULL){
            char newpref[longueur+2];
            memcpy(newpref,prefixe,longueur);
            newpref[longueur]=i+97;
            newpref[longueur+1]='\0';
            print_mot(curr->fils[i],newpref,longueur+1);
        }
    }
}

void print_arbre(arbre tree){
    if(tree==NULL){
        return;
    }else{
        print_mot(tree,NULL,0);
    }
}

arbre Fichier_en_arbre(char* fichier){
    arbre tree=NULL;
    char chaine[50];
    FILE* f=fopen(fichier,"r");
    if(f!=NULL){
        while(fgets(chaine,50,f)){
            chaine[strlen(chaine)-1]='\0';
            ajouter_mot(&tree,chaine);
        }
    }
    fclose(f);
    return tree;
}

bool a_fils(noeud* n){//determiner si un sommet a un fils cad sa liste des fils n'est pass toute vide;
    for(int i=0;i<26;i++){
        if(n->fils[i]!=NULL){
            return true;
        }
    }
    return false;
}

bool search(arbre a,char* mot_t){//
    char mot[MAX];

    strncpy(mot,mot_t,sizeof(mot));

    for(unsigned int i=0;i<strlen(mot_t);i++){//rendre tous le mot en miniscule
        mot[i]=tolower(mot[i]);
    }
    noeud* tmp=a;//tmp qui va parcourir notre arbre

    for(unsigned int i=0;i<strlen(mot);i++){
        if(tmp->fils[mot[i]-97]==NULL){
            return false;
        }else{
            tmp=tmp->fils[mot[i]-97];
        }
    }
    if(tmp->est_mot==true){//si le mot a la fin est final retourner true
        return true;
    }
    return false;
}

void free_arbre(arbre a){// free de maniere recurssive
    if(a_fils(a)){
        for(int i=0;i<26;i++){
            if(a->fils[i]!=NULL){
                free_arbre(a->fils[i]);
            }
        }
    }
    if(a!=NULL){
        free(a);
    }
}

void trouver_(char* text,arbre* a){//mettre tous les mot du text qui ne sont pas dans dans le dictionnaire dans un fihier resultat.
    char mot[MAX];
    for(int i=0;i<MAX;i++){
        mot[i]='\0';
    }
    char c;
    int i=0;
    FILE* resultat=fopen("./tests/resultats_arbre_prefix","w");
    if(resultat==NULL){
        printf("erreur d'ouverture du fichier\n");
        exit(1);
    }
    fputs("*****************************************Methode de l'arbre_prefix**********************************\n\n",resultat);
    fputs("les mot qui sont dans le dictionnaire mais pas dans le texte sont: \n\n",resultat);
    FILE* fichier=fopen(text,"r");
    do{//caratere par caractere jusqu'a trouver un caratere speciale;
        c=fgetc(fichier);
        if((c>='a'&& c<='z') || (c>='A' && c<='Z')){
            mot[i]=c;
            i++;
        }else if(mot[0]!='\0'){
            if(!search(*a,mot)){
                fputs(mot,resultat);
                fputs("\n",resultat);
            }
            for(int i=0;i<MAX;i++){
                 mot[i]='\0';
            }
            i=0;
        }   
    }while(c!=EOF);
    fclose(fichier);
    fclose(resultat);
}
int main(int argc ,char* argv[]){
    (void) argc;
    int t=clock();
    arbre n=NULL;
    n=Fichier_en_arbre(argv[1]);
    trouver_(argv[2],&n);
    free_arbre(n);
    t=clock()-t;
    printf("\n\n\n\n");
    printf("*****************************************************************************\n");
    printf("le temps de l'execution de la methde arbre prefix est : %lf s\n",t/(double)CLOCKS_PER_SEC);
    printf("le resultat est dans le dossier tests\n");
    printf("*****************************************************************************\n");
    printf("\n\n\n\n");
    return 0;
}

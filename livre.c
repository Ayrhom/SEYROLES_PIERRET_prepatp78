#include "livre.h"


void saisirLivre(T_livre * ptrL)
{
    
lireChaine("TITRE :", (ptrL->titre), MAX_TITRE );
lireChaine("AUTEUR :", (ptrL->auteur ), MAX);
do
{
    printf("ANNEE : ");
    scanf("%d",&ptrL->annee);
} while (ptrL->annee < 0 && ptrL->annee > 2023);
getchar();
lireChaine("EDITEUR :", (ptrL->editeur ), MAX);
strcpy(ptrL->emprunteur.nomemprunteur,"NULL");
}

void afficherLivre(const T_livre *ptrL)
{
afficherChaine("CODE :", (ptrL->code ));
printf(" - ");
afficherChaine("TITRE :", (ptrL->titre));
printf(" - ");
afficherChaine("AUTEUR :", (ptrL->auteur ));
printf(" - ");
printf("ANNEE : %d",ptrL->annee);
printf(" - ");
afficherChaine("EDITEUR :", (ptrL->editeur ));

if(strcmp(ptrL->emprunteur.nomemprunteur, "NULL") != 0){
printf(" - ");
afficherChaine("EMPRUNT :", (ptrL->emprunteur.nomemprunteur));
//printf(" - DATE : %d %d %d",ptrL->emprunteur.ladate, ptrL->emprunteur.lemois, ptrL->emprunteur.lannee);
}
printf("\n");
}


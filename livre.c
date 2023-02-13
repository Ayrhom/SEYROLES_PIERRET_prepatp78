#include "livre.h"


void saisirLivre(T_livre * ptrL)
{
lireChaine("TITRE :", (ptrL->titre), MAX_TITRE );
lireChaine("AUTEUR :", (ptrL->auteur ), MAX);
printf("ANNEE : ");
scanf("%d",&ptrL->annee);
getchar();
lireChaine("EDITEUR :", (ptrL->editeur ), MAX);
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
printf("\n");
}


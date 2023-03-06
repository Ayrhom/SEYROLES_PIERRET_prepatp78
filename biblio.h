#ifndef BIBLIO_H   //compilation conditionnelle
#define BIBLIO_H

#include "livre.h"

#define CAPACITE_BIBLIO 20 // nb maximum de livres ds la bibliotheque

typedef  T_livre 	T_tabloDeLivres[CAPACITE_BIBLIO];

typedef struct
{
	T_tabloDeLivres etagere;
	int nbLivres;  //nb de livres actuellement ds la bibliotheque

} T_Bibliotheque;




//prototypes
void init (T_Bibliotheque *ptrB);
int ajouterLivre(T_Bibliotheque  *ptrB);
int  afficherBibliotheque(const T_Bibliotheque  *ptrB);
int rechercherLivre(const T_Bibliotheque *ptrB, const T_Titre *title);
void livresAuteurs(const T_Bibliotheque *ptrB, const T_Aut *auteur);
int supprimerLivre(T_Bibliotheque *ptrB, const T_Titre *book);
char * empruntLivre(T_Bibliotheque *ptrB, T_livre *book);
char * rendreLivre(T_Bibliotheque *ptrB, const T_Titre *title, T_Emp nomEmprunt);
void triTitre(T_Bibliotheque *ptrB);
void triAuteur(T_Bibliotheque *ptrB);
void triAnnee(T_Bibliotheque *ptrB);
void listerLivreDispo(T_Bibliotheque *ptrB);
int estEnRetard(T_Emp emp);


#endif
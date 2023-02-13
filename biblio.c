# include "biblio.h"
# include <string.h>


void init (T_Bibliotheque *ptrB)
{

ptrB->nbLivres=0;
// ou (*ptrB).nbLivres=0;
}

int ajouterLivre(T_Bibliotheque  *ptrB)
{
	int i=ptrB->nbLivres;
	if (ptrB->nbLivres<CAPACITE_BIBLIO)// reste t il de la place?
	{
		i = sprintf(ptrB->etagere[i].code,"%d",i);
		saisirLivre(&(ptrB->etagere[ptrB->nbLivres]));
		ptrB->nbLivres++;
		return 1;
	}
	
return 0;
}


int  afficherBibliotheque(const T_Bibliotheque  *ptrB)
{
int i;
if(ptrB->nbLivres==0)
	return 0;
	else
		{
		for(i=0;i<ptrB->nbLivres;i++)
			{
			afficherLivre( &(ptrB->etagere[i])  );
			
			}


		
		return 1;
		}
}

int rechercherLivre(const T_Bibliotheque *ptrB, const T_Titre *title){
	int i;
	if (ptrB->nbLivres==0) return -1;
	else
	{
		for (i = 0; i < ptrB->nbLivres; i++)
		{
			if (strcmp(*title,ptrB->etagere[i].titre)==0)
			{
				return i;
			}
			
		}
		
	}
return -1;
}

void livresAuteurs(const T_Bibliotheque *ptrB, const T_Aut *auteur){
	int i;
	if (ptrB->nbLivres==0) printf("Pas de livre de cet(te) auteur(e)");
	else{
		for (i = 0; i < ptrB->nbLivres; i++)
		{
			if (strcmp(ptrB->etagere[i].auteur,*auteur)==0)
			{
				afficherChaine("TITRE : ",ptrB->etagere[i].titre);
				printf("\n");
			}
		}
	}
}


int supprimerLivre (T_Bibliotheque *ptrB, const T_Titre *title){
	int test = rechercherLivre(ptrB, title);
	if (test == -1) return 0;	
	else {
		strcpy(ptrB->etagere[test].titre,ptrB->etagere[(ptrB->nbLivres)-1].titre);
		ptrB->nbLivres--; 
	}
return 1;	
}
/*
int empruntLivre(T_Bibliotheque *ptrB, T_livre *book){
	T_Emp emprunt;
	int i;
	if (ptrB->nbLivres == 0) return 0;
	else
	{
		if (rechercherLivre(ptrB,book->titre)==-1)
		{
			return 0;
		}
		else
		{
			printf("Livre présent dans la bibliothèque\n");
			lireChaine("Nom de l'emprunteur : ", book->emprunteur.nomemprunteur,K_MaxEmp);
			printf("\n quel est le jour de cet emprunt (0=lundi 1=mardi 2=mercredi 3=jeudi 4=vendredi 5 =samedi 6=dimanche)");
			scanf("%d",&i);
			getchar();
			book->emprunteur.lejour=i;
		}
		
	}
	
}*/
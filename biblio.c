# include "biblio.h"
# include <string.h>
#include <time.h>

void init (T_Bibliotheque *ptrB)
{

ptrB->nbLivres=0;
// ou (*ptrB).nbLivres=0;
}

void lireDateSysteme(T_Emp *E)
{
char j[9],m[10],h[9],mer[11],vir[2];
int d,a;


system("date > ladate"	);
FILE * fic=NULL;  // pointeur de fichier
fic=fopen("ladate","r"); //fileOpen en mode 'r'EAD

//ici , si fic vaut NULL, alors le fopen a indiquÃ©
//que le fichier ladate n'est pas accessible
if (fic!=NULL)
	{
	while(!feof(fic))	
		{
		fscanf(fic,"%s %d %s %d %s %s %s",j,&d,m,&a,vir,h,mer);		
		if (!feof(fic)) 
			printf("\n-->LU : %s- %d- %s- %d- %s- %s",j,d,m,a,h,mer);		

		}
	fclose(fic);
	
if (strstr(j,"lundi")==0) E->lejour=lundi;
else if (strstr(j,"mardi")==0) E->lejour=mardi;
else if (strstr(j,"mercredi")==0) E->lejour=mercredi;
else if (strstr(j,"jeudi")==0) E->lejour=jeudi;
else if (strstr(j,"vendredi")==0) E->lejour=vendredi;
else if (strstr(j,"samedi")==0) E->lejour=samedi;
else if (strstr(j,"dimanche")==0) E->lejour=dimanche;

E->ladate=d;

if (strcmp(m,"janvier")==0) E->lemois=janvier+1;
else if (strcmp(m,"fevrier")==0) E->lemois=fevrier+1;
else if (strcmp(m,"mars")==0) E->lemois=mars+1;
else if (strcmp(m,"avril")==0) E->lemois=avril;
else if (strcmp(m,"mai")==0) E->lemois=mai+1;
else if (strcmp(m,"juin")==0) E->lemois=juin+1;
else if (strcmp(m,"juillet")==0) E->lemois=juillet+1;
else if (strcmp(m,"aout")==0) E->lemois=aout+1;
else if (strcmp(m,"septembre")==0) E->lemois=septembre+1;
else if (strcmp(m,"octobre")==0) E->lemois=octobre+1;
else if (strcmp(m,"novembre")==0) E->lemois=novembre+1;
else if (strcmp(m,"decembre")==0) E->lemois=decembre+1;

E->lannee=a;
	}
	else
	{
		printf("n souci avec la date systeme !!");
		
		//on range une date irrÃ©elle 
		E->lejour=dimanche;
		E->ladate=99;
		E->lemois=decembre;
		E->lannee=-999;


	}

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

char * empruntLivre(T_Bibliotheque *ptrB, T_livre *book){
	printf("TITRE = %s\n",book->titre);

	if (ptrB->nbLivres == 0) return 0;
	else
	{
		printf("Livre présent dans la bibliothèque\n");
		strcpy(book->emprunteur.nomemprunteur, lireChaine("Nom de l'emprunteur : ", book->emprunteur.nomemprunteur,K_MaxEmp));
		lireDateSysteme(&(book->emprunteur));
		return book->emprunteur.nomemprunteur;
	}
}

char * rendreLivre(T_Bibliotheque *ptrB, const T_Titre *title, T_Emp nomEmprunt){
	int recherche = rechercherLivre(ptrB, title);
	T_livre book = ptrB->etagere[recherche];

	if (recherche == -1) { printf("\nLe livre n'est pas dans la bibliothèque !"); return ptrB->etagere[recherche].emprunteur.nomemprunteur; }
	else if (strcmp(book.emprunteur.nomemprunteur, nomEmprunt.nomemprunteur) != 0) { printf("\nLe nom d'emprunteur ne correspond pas !"); return ptrB->etagere[recherche].emprunteur.nomemprunteur; }
	else {
		printf("Livre rendu !\n");
		return "NULL";
	}
}

void triTitre(T_Bibliotheque *ptrB){
	int tri=1,i;
	T_livre aux;
	
	while(tri){
		tri = 0;
		for (i = 0; i < ptrB->nbLivres-1; i++)
		{
			if (strcmp(ptrB->etagere[i].titre, ptrB->etagere[i+1].titre) > 0)
			{
				tri = 1;
				strcpy(aux.titre, ptrB->etagere[i+1].titre);
				strcpy(ptrB->etagere[i+1].titre, ptrB->etagere[i].titre);
				strcpy(ptrB->etagere[i].titre, aux.titre);
			}
		}
	}
}

void triAuteur(T_Bibliotheque *ptrB){
	int tri=1,i;
	T_livre aux;
	
	while(tri){
		tri = 0;
		for (i = 0; i < ptrB->nbLivres-1; i++)
		{
			if (strcmp(ptrB->etagere[i].auteur, ptrB->etagere[i+1].auteur) > 0)
			{
				tri = 1;
				strcpy(aux.auteur, ptrB->etagere[i+1].auteur);
				strcpy(ptrB->etagere[i+1].auteur, ptrB->etagere[i].auteur);
				strcpy(ptrB->etagere[i].auteur, aux.auteur);
			}
		}
	}
}

void triAnnee(T_Bibliotheque *ptrB){
	int tri=1,i;
	T_livre aux;
	
	while(tri){
		tri = 0;
		for (i = 0; i < ptrB->nbLivres-1; i++)
		{
			if (ptrB->etagere[i].annee > ptrB->etagere[i+1].annee)
			{
				tri = 1;
				aux.annee = ptrB->etagere[i+1].annee;
				ptrB->etagere[i+1].annee = ptrB->etagere[i].annee;
				ptrB->etagere[i].annee = aux.annee;
			}
		}
	}
}

void listerLivreDispo(T_Bibliotheque *ptrB){
	for (int i = 0; i < ptrB->nbLivres; i++) if (strcmp(ptrB->etagere[i].emprunteur.nomemprunteur, "NULL")==0) afficherLivre(&(ptrB->etagere[i]));
}

int estEnRetard(T_Emp emp){
	int jours,an=2020;
	T_Emp empRetard;
	lireDateSysteme(&empRetard);
	empRetard.ladate = 15;
	empRetard.lemois = 12;
	lireDateSysteme(&emp);
	emp.ladate = 1;
	int month,i;
	printf("DATE EMP : %d - %d - %d\n",emp.ladate,emp.lemois,emp.lannee);
	printf("DATE EMPRETARD : %d - %d - %d\n",empRetard.ladate,empRetard.lemois,empRetard.lannee);
	// nb jours dans le mois
	if (emp.lemois <= 7)
	{
		if (emp.lemois%2 == 1) jours = 31;
		else jours = 30;		
	}
	else if (emp.lemois)
	{
		if (emp.lemois%2 == 1) jours = 30;
		else jours = 31;	
	}
	if (emp.lemois == 1)
	{
		if ((emp.lannee - an)%4 == 0) jours = 29;
		else jours = 28;
	}
	printf("NB jour Mois : %d\n",jours);
	//date de rendu en début de mois et date d'emprunt fin de mois
	if ((emp.ladate + 7 > jours))
	{
		int date = emp.ladate,i=0; //compteurs
		while(date - jours != empRetard.ladate){
			i++;
			date++;
		}

		//retard de mois
		if (emp.lemois != empRetard.lemois-1)
		{
			month = empRetard.lemois - emp.lemois;
			if (jours==30)
			{
				for (int j = 0; j < month; j++)
				{
					if (j%2==0) i = i + (jours+1); // mois de 30 jours
					else i = i + jours; // mois de 31 jours
				}
				return i-7;
			}
			else if (jours==31)
			{
				for (int j = 0; j < month; j++)
				{
					if (j%2==0) i = i + (jours-1); // 
					else i = i + jours; // 
				}
				return i-7;
			}//mois de fevrier (28/29 jours) pas pris en compte dans le retard de mois
		}

		//dans le meme mois en retard
		else if (i>7) return i-7;

		//dans le meme mois pas en retard
		else return i;
	}
	//en retard cas classique
	else if (((emp.ladate + 7) < empRetard.ladate)){
		//retard de mois
		if (emp.lemois != empRetard.lemois)
		{
			month = empRetard.lemois - emp.lemois;
			if (jours==30)
			{
				for (int j = 0; j < month; j++)
				{
					if (j%2==0) i = i + (jours+1); // mois de 30 jours
					else i = i + jours; // mois de 31 jours
				}
				return i-7;
			}
			else if (jours==31)
			{
				for (int j = 0; j < month; j++)
				{
					if (j%2==0) i = i + (jours-1); // 
					else i = i + jours; // 
				}
				return i-7;
			}//mois de fevrier (28/29 jours) pas pris en compte dans le retard de mois
		}
	} return (empRetard.ladate - (emp.ladate+7));
	
return (empRetard.ladate - (emp.ladate));
}


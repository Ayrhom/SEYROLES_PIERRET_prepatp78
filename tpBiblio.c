// TP GESTION D'UNE BIBLIOTHEQUE 
#include "biblio.h"

void lectureFichierTXT();
void sauvegarde(T_Bibliotheque *ptrB);
void chargement(T_Bibliotheque *ptrB);

int menu()
{
	int choix;
// au programme du TP7 :


printf("\n\n 1 - ajouter un nouveau livre dans la bibliotheque "); 
printf("\n 2 - afficher tous les livres de la bibliotheque "); 
printf("\n 3 - rechercher un livre (par son titre)");  // il peut y avoir plusieurs livres de même titre. Dans ce cas, indiquez le nombre d'exemplaires disponibles
printf("\n 4 - rechercher et afficher tous les livres d'un auteur");
printf("\n 5 - supprimer un livre d	pr la bibliotheque");
// si les 5 choix ci dessus sont bien codés, modifiez votre structure T_Livre et passez à 5 champs (avec cote,editeur et annee)


// au programme du TP8 :
// ajouter le champ emprunteur à votre structure T_Livre

printf("\n 6 - emprunter un livre de la bibliotheque");
printf("\n 7 - restituer/rendre un livre de la bibliotheque");
printf("\n 8 - trier les livres (par titre)");
printf("\n 9 - trier les livres (par auteur)");
printf("\n 10 - trier les livres (par annee)");
// si les 5 choix (6-10) sont bien codés, changez le type T_Emp et remplacez-le par la structure T_Emp visible dans livre.h
// vous pourrez alors faire les menus 11,12,etc...
printf("\n 11- lister les livres disponibles "); 
printf("\n 12 - lister les emprunts en retard "); //on suppose qu'un emprunt dure 7 jours.
// printf("\n 13 - ... imaginez vous même vos propres fonctionnalités ")

printf("\n 0 - QUITTER");
printf("\n Votre choix : ");
scanf("%d[^\n]",&choix);getchar();
return choix;
}


int main()
{
int reponse,chx;
T_livre livre;
T_Titre titre;
T_Aut auteur;
T_Emp emp;
T_Bibliotheque B; 

init( &B );
chargement(&B);

do
{
chx= menu();
switch(chx)
	{
	case  1 : reponse = ajouterLivre(&B);
				if (reponse==1)
					printf(" ajout reussi !!");
					else
					printf("impossible d ajouter (bibliotheque pleine)");
			break;
	case 2 : reponse=afficherBibliotheque(&B);
			if (reponse==0)	
					printf("La bibliotheque est vide");

			break;	
	case 3: 
			lireChaine("Saisir titre : ",titre, MAX_TITRE);
			reponse = rechercherLivre(&B, &titre);
			if (reponse == -1)
			{
				printf("Le livre n'est pas dans la bibliothèque");
			}
			else
			{
				printf("Le livre a été trouvé en position %d dans la bibliothèque", reponse);
			}
			break;
	case 4:
			lireChaine("Saisir auteur(e) : ",auteur,K_MaxAut);
			printf("Livres de l'auteur(e) :%s\n",auteur);	
			livresAuteurs(&B,&auteur);
			break;
	case 5 :
			lireChaine("Saisir titre : ",titre, MAX_TITRE);
			reponse = supprimerLivre(&B, &titre);
			printf("Livre supprimée \n");
			break;
	case 6 :
			lireChaine("Saisir le titre du livre à emprunter : ",titre, MAX_TITRE);
			reponse = rechercherLivre(&B, &titre);
			if(reponse != -1 ) {
			livre = B.etagere[rechercherLivre(&B, &titre)];
			strcpy(B.etagere[reponse].emprunteur.nomemprunteur, empruntLivre(&B, &livre));
			printf("%s a emprunté le livre %s de %s !\n",B.etagere[reponse].emprunteur.nomemprunteur, titre, B.etagere[reponse].auteur);
			}
			break;
			
	
	case 7 : 
			lireChaine("saisir titre : ", titre, MAX_TITRE);
			lireChaine("nom de l'emprunteur : ",  emp.nomemprunteur, MAX);
			livre = B.etagere[rechercherLivre(&B, &titre)];
			strcpy(livre.emprunteur.nomemprunteur, rendreLivre(&B, &titre, emp));
			break;
	case 8 :
			triTitre(&B);
			break;
	case 9 : 
			triAuteur(&B);
			break;
	case 10:
			triAnnee(&B);
			break;
	case 11 : 
			listerLivreDispo(&B);
			break;
	case 12 :
			lireChaine("saisir titre : ", titre, MAX_TITRE);
			lireChaine("nom de l'emprunteur : ",  emp.nomemprunteur, MAX);
			if (rechercherLivre(&B, &titre) != -1)
			{
			livre = B.etagere[rechercherLivre(&B, &titre)];
			if (estEnRetard(livre.emprunteur) <= 7) printf("Le livre a été emprunté il y a %d jours\n", estEnRetard(livre.emprunteur));
			else printf("Le livre est en retard de %d jours\n", estEnRetard(livre.emprunteur));
			}
			break;
	}

}while(chx!=0);
sauvegarde(&B);
return 0;
}

//LECTURE////////////////////////
void lectureFichierTXT()
{
//int M=100;
FILE *fic=NULL; //le type FILE
//char chaine[M];
//char chaine2[M];
char c;
fic=fopen("fic.txt","rt"); // r = le mode read   w = mode write (avec ecrasement)
//fopen renvoie NULL si probleme (fichier effac� , disque non accessible ...
if (fic!=NULL)
	{
	do
		{
		//fgets(chaine,M,fic);   //fputs pour �crire dans un fichier txt
		//fscanf(fic,"%s",chaine); //fprintf pour �crire dans un fichier txt
	//	fscanf(fic,"%s %s",chaine,chaine2);
		fscanf(fic,"%c",&c);
		//fscanf(fic,"%c",&chaine[0]);
	//	if (!feof(fic))
           //printf("\n\t >%s--%s<",chaine,chaine2);
        printf(">%c<",c);
		}
    while(!feof(fic));
	fclose(fic);
	puts("\nLECTURE REUSSIE ..............");
	}
	else puts("ECHEC DE LECTURE DU FICHIER TXT !!!!!  ");
}

//CHARGEMENT///////////////////////////
void chargement(T_Bibliotheque *ptrB)
{
FILE *fic=NULL; //le type FILE
int i=0;
fic=fopen("baseLivres","r"); // r = le mode read
//fopen renvoie NULL si probleme (disque plein, disque non accessible ...
if (fic!=NULL)
	{
	do
		{

		fread(  &(ptrB->etagere[i]) ,sizeof(T_livre),1,fic);
		i++;
		}
		while(!feof(fic));
	fclose(fic);
	ptrB->nbLivres=i-1;
	puts("CHARGEMENT  REUSSI ..............");
	}
	else puts("ECHEC DE CHARGEMENT  !!!!!  ");

}

//SAUVEGARDE///////////////////////
void sauvegarde(T_Bibliotheque *ptrB)
{
FILE *fic=NULL; //le type FILE
int i;
fic=fopen("baseLivres","w"); // w = le mode = write avec ECRASEMENT
//fopen renvoie NULL si probleme (disque plein, disque non accessible ...
if (fic!=NULL)
	{
	for(i=0;i<ptrB->nbLivres;i++)
		{
//fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
    fwrite(  &(ptrB->etagere[i])        ,sizeof(T_livre),1,fic);

		}
	fclose(fic);
	puts("SAUVEGARDE REUSSIE ..............");



	}
	else puts("ECHEC DE SAUVEGARDE  !!!!!  ");
}
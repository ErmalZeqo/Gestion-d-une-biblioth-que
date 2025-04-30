#include<stdio.h>
#include<stdlib.h>
#include "biblioLC.h"
#include "entreeSortieLC.h"
#include "biblioH.h"
#include "entreeSortieH.h"

void menu()
{
/*______________AFFICHAGE DU MENU____________________*/
	printf("Actions possibles sur la bibliothèque : \n");
	printf(" - 0 : Quitter le programme\n");
	printf(" - 1 : Affichage\n");
	printf(" - 2 : Insertion d'ouvrage\n");
	printf(" - 3 : suppression d'ouvrage\n");
	printf(" - 4 : recherche par titre\n");
	printf(" - 5 : recherche par numero\n");
	printf(" - 6 : recherche par auteur\n");
	printf(" - 7 : recherche ouvrages à plusieurs exemplaires\n");
}

int main(int argc, char* argv[] )
{
	Biblio *b_lc = charger_n_entrees(argv[1], atoi(argv[2]));
	BiblioH *b_h = charger_n_entrees_H(argv[1], atoi(argv[2]));
	int stop = 1;
	char buffer[256];
	char nom_livre[256];
	char nom_auteur[256];
	int num;
	int type;
	
	while(stop)
	{
		printf("Choisir le type :\n - 1 Liste chainée\n 2 - Table de hachage\n");
		fgets(buffer, sizeof(int), stdin);
		type=atoi(buffer);
		switch(type){
			case 1:
				menu();
				printf("saisir l'action a effectuer.\n");
				fgets(buffer, sizeof(int), stdin);
				stop=atoi(buffer);

				switch(stop)
				{
				case 0:
					printf("Merci et au revoir\n");
					break;
				case 1:
					afficher_biblio(b_lc);
					break;
				case 2:
					printf("Entrez un nom de livre, un nom d'auteur et un numéro\n");
					fgets(buffer, 256, stdin);
					sscanf(buffer,"%s %s %d",nom_livre,nom_auteur,&num);
					inserer_en_tete(b_lc,num,nom_livre,nom_auteur);
					printf("Ajout fait\n");
					break;
				case 3:
					printf("Entrez un nom de livre, un nom d'auteur et un numéro\n");
					fgets(buffer, 256, stdin);
					sscanf(buffer,"%s %s %d",nom_livre,nom_auteur,&num);
					supr_ouvrage(b_lc,num,nom_auteur,nom_livre);
					printf("Suppression terminée\n");
					break;
				case 4:
					printf("Entrez un nom de livre\n");
					fgets(buffer, 256, stdin);
					sscanf(buffer,"%s",nom_livre);
					printf("Les livres sont:\n");
						afficher_livre(recherche_par_titre(b_lc,nom_livre));
					
					break;
				case 5:
					printf("Entrez un numero de livre\n");
					fgets(buffer, 256, stdin);
					sscanf(buffer,"%d",&num);
					printf("Les livres sont:\n");
					
					afficher_livre(recherche_par_num(b_lc,num));
					
					break;
				case 6:
					printf("Entrez un nom d'auteur\n");
					fgets(buffer, 256, stdin);
					sscanf(buffer,"%s",nom_auteur);
					printf("Les livres sont:\n");
					
			Biblio* blc_auteur=recherche_par_meme_auteur(b_lc,nom_auteur);
					
					afficher_biblio(blc_auteur);
					liberer_biblio(blc_auteur);
					break;
				case 7:
					afficher_biblio(plusieurs_exemplaires(b_lc));
				}
				break;

			case 2:
				menu();
				printf("saisir l'action a effectuer.\n");
				fgets(buffer, sizeof(int), stdin);
				stop=atoi(buffer);

				switch(stop)
				{
				case 0:
					printf("Merci et au revoir\n");
					break;
				case 1:
					afficher_biblio_H(b_h);
					break;
				case 2:
					printf("Entrez un nom de livre, un nom d'auteur et un numéro\n");
					fgets(buffer, 256, stdin);
					sscanf(buffer,"%s %s %d",nom_livre,nom_auteur,&num);
					inserer(b_h,num,nom_livre,nom_auteur);
					printf("Ajout fait\n");
					break;
				case 3:
					printf("Entrez un nom de livre, un nom d'auteur et un numéro\n");
					fgets(buffer, 256, stdin);
					sscanf(buffer,"%s %s %d",nom_livre,nom_auteur,&num);
					suppression_ouvrage_H(b_h,num,nom_auteur,nom_livre);
					printf("Suppression terminée\n");
					break;
				case 4:
					printf("Entrez un nom de livre\n");
					fgets(buffer, 256, stdin);
					sscanf(buffer,"%s",nom_livre);
					printf("Les livres sont:\n");
					afficher_livre_H(recherche_par_titre_H(b_h,nom_livre));
					
					break;
				case 5:
					printf("Entrez un numero de livre\n");
					fgets(buffer, 256, stdin);
					sscanf(buffer,"%d",&num);
					printf("Les livres sont:\n");
					
					afficher_livre_H(recherche_par_num_H(b_h,num));
					
					break;
				case 6:
					printf("Entrez un nom d'auteur\n");
					fgets(buffer, 256, stdin);
					sscanf(buffer,"%s",nom_auteur);
					printf("Les livres sont:\n");
					BiblioH* bh_auteur=recherche_par_auteur_H(b_h,nom_auteur);
					afficher_biblio_H(bh_auteur);
					liberer_biblio_H(bh_auteur);
					break;
				case 7:
					afficher_biblio_H(plusieurs_exemplaires_H(b_h));
				}
			break;
		}
	}
	
	liberer_biblio(b_lc);
	liberer_biblio_H(b_h);

	return 0;
}

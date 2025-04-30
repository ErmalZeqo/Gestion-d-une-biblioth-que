
#include <stdio.h>
#include <stdlib.h>
#include "entreeSortieLC.h"
#include "biblioLC.h"

Biblio* charger_n_entrees(char* nomfic, int n){
	char buffer[256]; int i=0;
	char auteur[256], titre[256]; int num;
	Biblio* biblio=creer_biblio(); //Creation d"une biblio
	FILE* fichier=fopen(nomfic,"r"); //Ouverture du fichier en mode lecture
	if (fichier==NULL) return NULL; //Erreur lors de l'ouverture
	while (i<n && (fgets(buffer,256,fichier)!=NULL)){ //Lecture de n lignes ou jusqu'à fin du fichier
		i++;
		sscanf(buffer,"%d %s %s\n",&num,titre,auteur);
		inserer_en_tete(biblio,num,titre,auteur); //Insertion du Livre dans la Biblio
		}
	fclose(fichier); //fermeture du fichier
	return biblio;
	}
	
void enregistrer_biblio(Biblio *b, char* nomfic)
{
	if(b->L ==NULL)return; 
	
	FILE *fichier = fopen(nomfic, "w"); //Ouverture du fichier en mode ecriture
	if (fichier==NULL) return; //Erreur lors de l'ouverture
	Livre *prc = b->L;
	while(prc)
	{
		fprintf(fichier, "%d %s %s\n", prc->num, prc->titre, prc->auteur); //Ecriture d'un Livre
		prc=prc->suiv; //Itérer dans la Biblio
	}
	fclose(fichier);
}

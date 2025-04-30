#include <stdio.h>
#include <stdlib.h>
#include "entreeSortieH.h"
#include "biblioH.h"

BiblioH* charger_n_entrees_H(char* nomfic, int n){
  	char buffer[256]; int i=0;
	char auteur[256];
	char titre[256]; int num;
	BiblioH* biblio=creer_biblio_H(100); //Creation de la BiblioH 
	FILE* fichier=fopen(nomfic,"r"); //Ouverture du fichier en mode lecture
	if (fichier==NULL) return NULL; //En cas d'erreur lors de l'ouverture
	while ((fgets(buffer,256,fichier)!=NULL) && (i<n)){ //Lecture de n lignes ou jusqu'à la fin du fichier
		i++;
		sscanf(buffer," %d %s %s\n",&num,titre,auteur); //Lecture d'un LivreH
		inserer(biblio,num,titre,auteur); //Insertion du LivreH dans BiblioH
		}
	fclose(fichier); //Fermeture du fichier
	return biblio;
}


void enregistrer_biblioH(BiblioH *b, char* nomfic){
	FILE *fichier = fopen(nomfic, "w"); //ouverture du fichier en mode ecriture
  	for (int i=0;i<b->m;i++){ //Parcours du table de hachage
	   LivreH *prc = b->T[i]; 
	    while(prc){ //Parcours de la liste chainée dans le tableau d'hachage
		       fprintf(fichier, "%d %s %s\n", prc->num, prc->titre, prc->auteur); //ecriture du LivreH
		       prc=prc->suiv;
	    }
  }
	fclose(fichier);
}

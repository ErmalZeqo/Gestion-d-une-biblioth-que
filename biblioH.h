#ifndef BIBLIO_H_H
#define BIBLIO_H_H

typedef struct livreh
{
	int clef;
	int num;
	char *titre;
	char *auteur;
	struct livreh* suiv;
}LivreH;

typedef struct table
{
	int nE ;		/*nombre d’elements contenus dans la table de hachage */
	int m ; 		/*taille de la table de hachage */
	LivreH ** T;	/*table de hachage avec resolution des collisions par chainage */
} BiblioH ;

//PROTOTYPES

int fonctionClef(char* auteur);
LivreH *creer_livre_H(int num, char* titre, char* auteur);
void liberer_livre_H(LivreH* l);
void afficher_livre_H(LivreH *l);
BiblioH* creer_biblio_H(int taille);
void liberer_biblio_H(BiblioH* b);
int fonctionHachage(int cle, int m);
BiblioH* fusion_H(BiblioH* b1, BiblioH* b2);
BiblioH *suppression_ouvrage_H(BiblioH *b, int num, char* auteur, char * titre);
BiblioH* recherche_par_auteur_H(BiblioH* b, char* auteur);
LivreH* recherche_par_titre_H(BiblioH* b, char* titre);
LivreH* recherche_par_num_H(BiblioH* b, int num);
void afficher_biblio_H(BiblioH * b);
void inserer(BiblioH* b , int num, char* titre,char* auteur);
void plusieurs_exemplaires_i(BiblioH *b, BiblioH *res, int i);
int livres_identiques_H(LivreH *l1, LivreH *l2);
BiblioH* plusieurs_exemplaires_H(BiblioH* b);


#endif

#include <stdio.h>
#include <stdlib.h>
#include "biblioH.h"
#include "entreeSortieH.h"
#include <assert.h>

int main(int argc, char *argv[])
{
	/*char *test="Ben"; //66+101+110=277
	assert(fonctionClef(test)==277);
	
	//test de creation, affichage et libération d'un livre, a executer avec valgrind :
	
	LivreH *lh=creer_livre(1234, "La Dame Aux Camelias", "Alexandre Dumas fils");
	
	afficher_livre(lh);
	
	liberer_livre(lh);
	return 0;*/
	
	//test : livres identiques :

LivreH *l1=creer_livre_H(1, "Les_Fleurs_Du_Mal", "Beaudelaire");
LivreH *l2=creer_livre_H(2, "Les_Fleurs_Du_Mal", "Beaudelaire");
assert(livres_identiques_H(l1, l2)==1);

//tests de la fonction plusieurs_exemplaires
BiblioH *b1=charger_n_entrees_H("tests_plusieurs_exemplaires/test_plusieurs_exemplaires_1.txt", 1 );
BiblioH *b2=charger_n_entrees_H("tests_plusieurs_exemplaires/test_plusieurs_exemplaires_2.txt", 6 );
BiblioH *b3=charger_n_entrees_H("tests_plusieurs_exemplaires/test_plusieurs_exemplaires_3.txt", 6 );
BiblioH *b4=charger_n_entrees_H("tests_plusieurs_exemplaires/test_plusieurs_exemplaires_4.txt", 10 );

printf("b1 avant appel :\n");
afficher_biblio_H(b1);
printf("b2 avant appel :\n");
afficher_biblio_H(b2);
printf("b3 avant appel :\n");
afficher_biblio_H(b3);
printf("b4 avant appel :\n");
afficher_biblio_H(b4);

BiblioH *b1_doublons=plusieurs_exemplaires_H(b1);
BiblioH *b2_doublons=plusieurs_exemplaires_H(b2);
BiblioH *b3_doublons=plusieurs_exemplaires_H(b3);
BiblioH *b4_doublons=plusieurs_exemplaires_H(b4);

printf("b1 après appel :\n");
afficher_biblio_H(b1);
printf("b1 doublons :\n");
afficher_biblio_H(b1_doublons);

printf("b2 après appel :\n");
afficher_biblio_H(b2);
printf("b2 doublons :\n");
afficher_biblio_H(b2_doublons);

printf("b3 après appel :\n");
afficher_biblio_H(b3);
printf("b3 doublons :\n");
afficher_biblio_H(b3_doublons);

printf("b4 après appel :\n");
afficher_biblio_H(b4);
printf("b4 doublons :\n");
afficher_biblio_H(b4_doublons);

liberer_biblio_H(b1);
liberer_biblio_H(b2);
liberer_biblio_H(b3);
liberer_biblio_H(b4);


liberer_biblio_H(b1_doublons);
liberer_biblio_H(b2_doublons);
liberer_biblio_H(b3_doublons);
liberer_biblio_H(b4_doublons);

liberer_livre_H(l1);
liberer_livre_H(l2);

return 0;
}

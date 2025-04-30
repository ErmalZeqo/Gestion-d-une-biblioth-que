#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "biblioLC.h"
#include "entreeSortieLC.h"

int main(int argc, char* argv[] )
{

//test : livres identiques :

Livre *l1=creer_livre(1, "Les_Fleurs_Du_Mal", "Beaudelaire");
Livre *l2=creer_livre(2, "Les_Fleurs_Du_Mal", "Beaudelaire");
assert(livres_identiques(l1, l2)==1);

//tests de la fonction plusieurs_exemplaires
Biblio *b1=charger_n_entrees("tests_plusieurs_exemplaires/test_plusieurs_exemplaires_1.txt", 1 );
Biblio *b2=charger_n_entrees("tests_plusieurs_exemplaires/test_plusieurs_exemplaires_2.txt", 6 );
Biblio *b3=charger_n_entrees("tests_plusieurs_exemplaires/test_plusieurs_exemplaires_3.txt", 6 );
Biblio *b4=charger_n_entrees("tests_plusieurs_exemplaires/test_plusieurs_exemplaires_4.txt", 10 );

printf("b1 avant appel :\n");
afficher_biblio(b1);
printf("b2 avant appel :\n");
afficher_biblio(b2);
printf("b3 avant appel :\n");
afficher_biblio(b3);
printf("b4 avant appel :\n");
afficher_biblio(b4);

Biblio *b1_doublons=plusieurs_exemplaires(b1);
Biblio *b2_doublons=plusieurs_exemplaires(b2);
Biblio *b3_doublons=plusieurs_exemplaires(b3);
Biblio *b4_doublons=plusieurs_exemplaires(b4);

printf("b1 après appel :\n");
afficher_biblio(b1);
printf("b1 doublons :\n");
afficher_biblio(b1_doublons);

printf("b2 après appel :\n");
afficher_biblio(b2);
printf("b2 doublons :\n");
afficher_biblio(b2_doublons);

printf("b3 après appel :\n");
afficher_biblio(b3);
printf("b3 doublons :\n");
afficher_biblio(b3_doublons);

printf("b4 après appel :\n");
afficher_biblio(b4);
printf("b4 doublons :\n");
afficher_biblio(b4_doublons);

liberer_biblio(b1);
liberer_biblio(b2);
liberer_biblio(b3);
liberer_biblio(b4);

liberer_biblio(b1_doublons);
liberer_biblio(b2_doublons);
liberer_biblio(b3_doublons);
liberer_biblio(b4_doublons);

liberer_livre(l1);
liberer_livre(l2);

return 0;
}

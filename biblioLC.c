#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioLC.h"

//_______________ALLOCATION_D'UN_LIVRE_____________________
Livre *creer_livre(int num, char* titre, char* auteur)
	{
	Livre * new_livre = (Livre*)malloc(sizeof(Livre)); //Allocation d'un Livre
	if (new_livre==NULL){ //En cas d'erreur d'allocation
		return NULL;
	}
	new_livre->num=num;	//Affectation des valeurs
	new_livre->titre = strdup(titre);
	new_livre->auteur = strdup(auteur);
	return new_livre;
	}

//__________________LIBERATION_D'UN_LIVRE___________________	
void liberer_livre(Livre* l)
{
	free(l->titre);		//Liberation des zones mémoires allouées avec strdup
	free(l->auteur);
	free(l);		//Liberation du Livre
}



/*_______________________ALLOCATION_BIBLIO________________*/	
Biblio* creer_biblio(){
	Biblio* biblio=(Biblio*)malloc(sizeof(Biblio)); //Allocation dynamique d'une Biblio
	biblio->L=NULL;
	return biblio;
	}

//______________________LIBERATION_D'UNE_BIBLIO____________
void liberer_biblio(Biblio* b)
{
	Livre* parc=b->L;
	Livre* tmp;
	while(parc)	//Parcours de la liste de Livre
	{
		tmp=parc->suiv;
		liberer_livre(parc); //Liberation des Livre
		parc=tmp;
	}
	free(b); // Liberation de la Biblio
}

//_________________INSERTION_EN_TETE_________________________
void inserer_en_tete(Biblio* b, int num, char* titre,char* auteur){
	Livre * l=creer_livre(num,titre,auteur); //Creation d'un livre
	l->suiv=b->L;		//Insertion en tête
	b->L=l;			//Changement de la zone à laquelle pointe b->L
	}

//______________________AFFICHAGE_LIVRE_______________________
void afficher_livre(Livre *l){
	if (l!=NULL){
		printf("Numero : %d , Titre: %s , Auteur: %s\n", l->num,l->titre, l->auteur);
		}
	}

//______________________AFFICHAGE_BIBLIO_____________________
void afficher_biblio(Biblio *b){
	Livre* prc = b->L;
	while (prc){	//Parcours de la liste de Livre
		afficher_livre(prc);	//Affichade de chaque Livre
		prc=prc->suiv;
	}
	printf("\n");
	}

//____________________________RECHERCHE_OUVRAGE_PAR_NUMERO_____________________
Livre* recherche_par_num(Biblio *b, int num){
	while ((b->L) && (b->L->num!=num)){	//Parcours de liste jusqu'à trouver un Livre ayant numéro=num ou fin de la liste
		b->L=b->L->suiv;
	}
	return b->L;
	}

//___________________________RECHERCHE_PAR_TITRE_________________
Livre* recherche_par_titre(Biblio *b, char *titre){
	while ((b->L) && (strcmp(b->L->titre,titre)!=0)){ //Parcours de liste jusqu'à trouver un Livre ayant titre="titre" ou fin de la liste
		b->L=b->L->suiv;
	}
	return b->L;
	}

//_____________________________RECHERCHE_PAR_AUTEUR______________________
Biblio* recherche_par_meme_auteur(Biblio *b , char *auteur){
	Biblio *new_b=creer_biblio(); //Creation d'une Biblio
	while (b->L){ //Parcours de liste de Livre
		if (strcmp(b->L->auteur,auteur)==0){ //Comparaison entre la valeur auteur en argument et l'autre du Livre
			inserer_en_tete(new_b,b->L->num,b->L->titre,b->L->auteur); //insertion en tete
		}
		b->L=b->L->suiv;
	}
	return new_b;
	}

//___________________________SUPRESSION_D'OUVRAGE____________________________
Biblio *supr_ouvrage(Biblio *b, int num, char* auteur, char * titre)
{	

	Livre *ptr=b->L;
	Livre* pred=NULL;
	
	while ((ptr!=NULL) && ((ptr->num != num) || (strcmp(ptr->auteur, auteur)!=0) || (strcmp(ptr->titre, titre)!=0))){ //Iteration jusqu'à rencontrer le Livre à supprimer ou atteindre la fin de la liste
		pred=ptr;
		ptr=ptr->suiv;
	}
	
	if (ptr!=NULL){
		if (pred!=NULL){
			pred->suiv=ptr->suiv; //Livre à supprimer est en tete de la liste
		}else{
			pred=ptr->suiv; //changement des liaisons
			b->L=pred;  //changement de la tete de liste
			return b;
		}
		liberer_livre(ptr); //liberation de livre qui est à supprimer
	}
	return b;
}

//____________________________FUSION_DE_BIBLIOS__________________
Biblio *fusion(Biblio *b1, Biblio *b2)
{
	Biblio *tete_b2=b2;
	while(b2->L) //parcours de la liste
	{
		inserer_en_tete(b1, b2->L->num, b2->L->titre, b2->L->auteur); //insertion d livre dans la Biblio b1
		b2->L=b2->L->suiv;
	}
	liberer_biblio(tete_b2); //liberation de la Biblio b2
	return b1;
}

//_______COMPARAISON_DE_DEUX_LIVRES_____________________//

int livres_identiques(Livre *l1, Livre *l2)
{
	if((strcmp(l1->auteur, l2->auteur)==0)&&(strcmp(l1->titre, l2->titre)==0)) //Livre ayant même auteur et même titre
	{
		return 1;
	}
	return 0;
}

/*____________________________PLUSIEURS_EXEMPLAIRES___________________*/

//Cette fonction prend une bibliotheque et retourne une liste de livres qui contient tous les ouvrages présents en plusieur exemplaires. On duplique la bibliotheque fournie au fur et a mesure du parcours avec la fonction inserer_en_tete(Biblio, num, livre, auteur). Cette duplication est nécessaire car nous allons procéder par suppression de tous les ouvrages présents en un unique exemplaire dans la liste d'origine pointéee au départ par b->l. On fait le choix de conserver la donnée intacte. Note : b->l après execution de la fonction contiendra tous les éléments de b->l mais en ordre inverse. 

//Afin d'obtenir une complexité en n2, on n'utilisera pas la focntion de suppression "supr_ouvrage" qui procède a une recherche et est donc en O(n), on supprimera l'élément dans le corps de la boucle en O(1) a la place. 

Biblio* plusieurs_exemplaires(Biblio *b)
{
//declaration variables :
Livre* parc1 = b->L; //var de parcours de la premiere boucle
Livre* parc2; //var de parcours de la deuxième boucle
Livre* prec = parc1; //Element précédent en vue de l'eventuelle suppression
Livre* head = b->L; //On garde un pointeur sur la tête de liste
int flag; //drapeau a lever en cas de detection d'un doublon
Biblio *res=creer_biblio();
/*tests sur la liste vide et liste d'un seul élément*/

if( (parc1 == NULL) || (parc1->suiv==NULL) )
{
	return res;
}

b->L=NULL; //On peut maintenant "vider" la bibliothèque qu'on remplira a nouveau avec des copies de chacun des éléments au fil du parcours.

//PARCOURS1 : premiere boucle
while(parc1)
{
	inserer_en_tete(b, parc1->num, parc1->titre, parc1->auteur); //copie de l'élément en cours
	parc2=head; //on affecte la variable de parcours no 2
	flag = 0; //on initialise la variable de test a 0 a chaque nouvel élément testé
	
	//PARCOURS2 : deuxieme boucle
	while(parc2)
	{
		if((livres_identiques(parc1, parc2))&&(parc1!=parc2)) //on vérifie qu'ils sont identiques mais qu'ils ne sont pas la même instance
		{
			//on a trouvé un livre identique a l'élément testé (parc1)
			flag=1;//on lève le drapeau
			break;
		}
		parc2=parc2->suiv;
	}
	
	if(!flag)//si on a pas trouvé de doublon on procède a la suppression de l'élément
	{
		if(parc1==head)//si notre élément a supr est en tête de liste
		{
			head=parc1->suiv; //on deplace la tete a l'element suivant
			liberer_livre(parc1);
			parc1=head; //On retablit la variable de parcours (note elle a été itérée lors de la suppression) 
		}
		else
		{
			prec->suiv=parc1->suiv; //suppression d'un élément de la liste qui n'est pas en tête
			liberer_livre(parc1);
			parc1=prec->suiv; 
		}
	}
	else
	{
		//l'itération n'a lieu que si on a pas supprimé d'élément car la suppression itère la variable de parcours au passage. 
		prec=parc1;
		parc1=parc1->suiv; 
	}
	
}
res->L=head;
return res;	
}
		

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "fonctions.h"
#include "fonctions.c"

#define N 10

int main () {

    time_t debut, fin;

    time (&debut);

    char lettre_saisie;

    Init_Grille(); // Initialisation de la Grille au préalable

    while (Demineur.nb_BOMB != 0) { // Affichage de la grille, du menu et gestion du déroulement de la partie
        
        system("cls");
        Aff_Grille(); // Afi
        Cpt_temps(&fin, debut);
		printf("Appuyer sur t (pour voir le temps), k (ajouter/retirer drapeau), d (Demasquer la cellule), p (Nouvelle partie), q (Quitter la partie): ");

        lettre_saisie = getche();
        putchar ('\n');

        if      (lettre_saisie == 't') printf("");

        else if (lettre_saisie == 'k') Drapeau_ajoute();

        else if (lettre_saisie == 'd') Demasque_case();

        else if (lettre_saisie == 'p') {
            Cpt_temps(&fin, debut);
			Init_Grille();
			time(&debut);
        }
        else if (lettre_saisie == 'q') {
            Fin_du_jeu();
			Cpt_temps(&fin, debut);
        }
        else printf("");
    }
    Fin_du_jeu (); // Lorsque toutes les bombes ont été marquée par le joueur

    Cpt_temps (&fin, debut);

    return 0;
}
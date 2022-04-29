#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "fonctions.h"


struct Jeu_Demineur {     // Création d'une structure qui va nous permettre de manipuler notre grille de mots binaires ainsi que le nombre de mines trouvées, et cela à travers tout le programme
    int nb_BOMB;
    unsigned char Grille[N][N];
} Demineur;

int is_DeMasked (unsigned char x) { // Retourne 1 si la case est démasquée
	int i;
	unsigned char m = 0x80;
    if ((x&m)==0) return 0;
    else return 1;
}

int is_Mined (unsigned char x) { // Retourne 1 si la case est minée
	int i, res;
	unsigned char m = 0x40;
    if ((x&m)==0) return 0;
    else return 1;
}

int is_Marked (unsigned char x) { // Retourne 1 si la case est marquée
	int i, res; 
	unsigned char m = 0x20;
    if ((x&m)==0) return 0;
    else return 1;
}

int Init_Grille () { // Initialise la Grille
    int i, j, x, y, valeur;
    int lignes [8], colonnes [8];
    Demineur.nb_BOMB = 10;                 // Le nombre de mines présentes sur la grille.
    srand (time(NULL));

    for (i=0; i<N; i++) {		         // Toutes les cases sont initialisées à 0.
		for(j=0; j<N; j++) {
			Demineur.Grille[i][j] = 0;
        }
    }
	for (i = 0; i < Demineur.nb_BOMB; i++) { // Tirage aléatoires de coordonées pour les bombes et placement des mines 
            x = rand() % 10;
            y = rand() % 10;                     // Ojectif : Insérer ici un tirage aléatoire au sein d'un tableau qui sort un res; x = res / 10; y = res % 10;
            if (!is_Mined(Demineur.Grille[x][y])) {
                Demineur.Grille[x][y] = 64;

                lignes[0] = x - 1;	colonnes[0] = y + 1;  // On prend les postions des cases adjacentes à la celulle minée
                lignes[1] = x;		colonnes[1] = y + 1;
                lignes[2] = x + 1;	colonnes[2] = y + 1;
                lignes[3] = x - 1;	colonnes[3] = y;
                lignes[4] = x + 1;	colonnes[4] = y;
                lignes[5] = x - 1;	colonnes[5] = y - 1;
                lignes[6] = x;		colonnes[6] = y - 1;
                lignes[7] = x + 1;	colonnes[7] = y - 1;

                for (j = 0; j < 8; j++){
                    valeur = Demineur.Grille [lignes[j]] [colonnes[j]];
                    if ((lignes[j] >= 0 && lignes[j] < N) && (colonnes[j] >= 0 && colonnes[j] < N)) {	    // Si la case adjacente à la case minée est dans le tableau
                            if (!is_Mined(valeur))														    // Et qu'elle n'est pas elle même minée
                                Demineur.Grille [lignes[j]] [colonnes[j]] += 1;							    //	Alors on l'incrémente de 1
                    }
                }
            }
		    else {
			    i--;
			    continue;
	    	}
	}
}

void Aff_Grille () { // Affiche la grille
    int i, j, valeur;

    printf("   ");
    for (int j = 0; j < N; j++) { // Ecriture des chiffres des colonnes
        printf(" %d", j+1);
    } printf("\n");

    printf("  --");
    for (int j = 0; j < N; j++) { // Ecriture d'une ligne de séparation
        printf("--");
    } printf("\n");

    for (i = 0; i < N; i++) {       // Pour Chaque ligne
        printf("   ");
		for (j = 0; j < N; j++) {   // Pour chaque case au sein de cette ligne
			valeur = Demineur.Grille[i][j];

            if (!is_DeMasked(valeur) && !is_Marked(valeur))
				printf(" x");

            else if (is_Marked(valeur))
				printf(" !");

            else if (is_DeMasked(valeur))
				printf(" %d", valeur - 128);  // On enlève 128 pour effacer l'effet du bit de poids fort

			else
				printf("Erreur");
		}
		printf(" | %d\n", i+1); // Fin de ligne
	}
}

int Lecture_cellule (int *line, int *col) {
    printf("Ecrire la ligne puis un espace, puis la colonne :");
	scanf("%d %d", line, col);
    (*line)--;	
	(*col)--;
    return Demineur.Grille [*line][*col];
}

int Drapeau_ajoute() { // Rajoute un drapeau
    int line, col, valeur;
    valeur = Lecture_cellule(&line, &col);  // Mettre le Lecture_cellule dans le Drapeau_ajoute pour créer un M(x,y)

    if (!is_DeMasked(valeur) && !is_Marked(valeur)) { // La case est masquée et non marquée
        if (is_Mined(valeur)) {
            Demineur.Grille [line][col] += 32; // Case minée désormais marquée, valeur +=32 (96)
            Demineur.nb_BOMB -= 1; // Une mine a été trouvée;
            return 1;
        }
        else {
            Demineur.Grille[line][col] += 32; // Case non minée masquée désormais marquée : valeur +=32 (32-40)
            return 1;
        }
    }
    else if (is_Marked(valeur)) { // La case a déja été marquée, l'utilisateur veut donc retirer le drapeau, (Octet:32-40)
            Drapeau_retire(line, col, valeur); // valeur -=32, la fonction Drapeau_retire va effectuer le chemin inverse
        }
	else
		return 0;						// error
}

int Drapeau_retire (int line, int col, int valeur) { // Retire un drapeau

    if (is_Mined(valeur)) {             // Si la case marquée était une bombe
        Demineur.Grille[line][col] -= 32; // Désormais case minée, non marquée : valeur -= 32 (64)
        Demineur.nb_BOMB += 1;            // La mine n'est plus considérée comme étant trouvé.
        return 1;
    }
    else {                             // Si la case marquée n'était pas une bombe
		Demineur.Grille[line][col] -= 32; // Case non minée, non marquée : valeur -= 32 (0-8)
		return 1;
	}
        return 0;
}

int Demasque_case () { // Démasque la case sélectionnée
    int line, col, valeur;
    valeur = Lecture_cellule(&line, &col); // Mettre le Lecture_cellule dans le Demasque_case pour créer un D(x,y)

    if (!is_DeMasked(valeur)) {                  // La case est masquée, Elle peut etre vide ou non, et minée ou non.

        if (valeur == 0 || valeur == 32) // La case est vide et non minée => propagation éventuelle évaluée grâce à l'appel de fonction
            propagation_recursive(line, col);

        else if (is_Mined(valeur))               // La case est minée, on termine le jeu via l'appel à la fonction Fin_du_jeu
            Fin_du_jeu();

        else                                   // Le reste : On le démasque
            Demineur.Grille[line][col] += 128;     // Démasquage de la case
    }
    else                                        // Las case était déja démasquée
        return 0;
}

int propagation_recursive (int line, int col) { // Propage récursivement le démasquage au case vide dans le voisinnage
    int valeur = Demineur.Grille[line][col], i;
    int lignes [8], colonnes[8];

    if (valeur!=0)
        return 0; // Erreur, la case est censé être vide

    Demineur.Grille[line][col] += 128; // Démasquage de la cellule vide : valeur += 128

	lignes[0] = line - 1;	colonnes[0] = col + 1;
	lignes[1] = line;		colonnes[1] = col + 1;
	lignes[2] = line + 1;	colonnes[2] = col + 1;
	lignes[3] = line - 1;	colonnes[3] = col;
	lignes[4] = line + 1;	colonnes[4] = col;
	lignes[5] = line - 1;	colonnes[5] = col - 1;
	lignes[6] = line;		colonnes[6] = col - 1;
	lignes[7] = line + 1;	colonnes[7] = col - 1;

    for (i=0; i<8; i++) {

        valeur = Demineur.Grille [lignes[i]] [colonnes[i]];

        if ((lignes[i] >= 0 && lignes[i] < N) && (colonnes[i] >= 0 && colonnes[i] < N)) { // La case adjacente se situe dans le tableau
                if (valeur !=0 && !is_DeMasked(valeur))  // La case adjacente est chifrée
                    Demineur.Grille[lignes[i]][colonnes[i]] += 128; // Démasquage de la case adjacente chiffrée : +=128
               
                else if (valeur == 0 || valeur == 32) // La case adjacente est vide
                    propagation_recursive (lignes[i], colonnes[i]); // Appel récursif pour appliquer la même fonction à l'actuelle case adjacente.
        }
    }
    return 1;
}

void Fin_du_jeu () { // Permet de terminer le jeu
	printf("FIN DU JEU\n");
	if (Demineur.nb_BOMB == 0) {
		system("cls");
		Aff_Grille();
		printf("C'est gagné !!\n");
	}
	else
        printf("BOOM! vous avez perdu!");

	printf("\n Appuyer sur une touche afin de quitter\n");
	fflush(stdin);
	getchar();
	exit(0);
}

void Cpt_temps (time_t *fin, time_t debut) {
    time(fin);
    printf("%d secondes\n", (int) difftime(*fin, debut));
}

#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define N 10

int is_DeMasked (unsigned char x);

int is_Mined (unsigned char x);

int is_Marked (unsigned char x);

int Init_Grille ();

void Aff_Grille ();

int Lecture_cellule (int *line, int *col);

int Drapeau_ajoute();

int Drapeau_retire (int line, int col, int valeur);

int Demasque_case ();

int propagation_recursive (int line, int col);

void Fin_du_jeu ();

void Cpt_temps (time_t *fin, time_t debut);











#endif
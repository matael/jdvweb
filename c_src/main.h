#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED


#include <iostream>
#include <string>
#include <fstream> // gestion de fichiers
#include <ctime> // bibliothèque obligatoire pour tirer un nombre au hasard
#include <cstdlib> // bibliothèque obligatoire pour tirer un nombre au hasard


// constantes. Repose sur le boléen-ASCII
#define CEL_VIE 49
#define CEL_MORT 48
#define MATRICE_TRAITEE "/srv/simplelife/Matrice.JDV"
#define MATRICE_SAUVEGARDE "/srv/simplelife/Sauvegarde.JDV"
#define FILE_ERR "Erreur.txt"
// longueur et largeur de matrice. Changer ça pour modifier la taille de matrice traitée dans Matrice.JDV. Ne pas aller en deçà de 4.
const int TailleL = 60;
const int TailleC = 60;

// constante des règles inhérentes au JDV. Ne modifier qu'en connaissance de cause.
const int LIM_ETOUFF = 4;
const int LIM_ISOL = 1;
const int VAL_CREA = 3;
const int VAL_NEUTRE = 2;
enum ValRetour{NORMAL = 1, AIE = 0};

using namespace std;

// fonctions       NOTE : l'appel des trois première dans cet ordre est le squelette du code : on li, on traite, on sauvegarde.
int lireMatriceJDV(string chaine[]); // Place dans chaine le contenu de Matrice.JDV
void TraiterMatriceJDV(string tabl[]); // Traitement de la matrice envoyée en argument. Gère la surcouche et le passage de phase.
void SauverMatriceJDV(string tabl[]); // sauvegarder la matrice dans Matrice.JDV

// fonctions alternatives
void RemplirMatrice(string tab[]);

// fonctions utilisées par la fonction TraiterMatriceJDV.
string MatriceToString(string tabl[]); // renvois la matrice en string.
int equivCellule(string tabl[], int i, int u); // renvois l'état de la cellule (y,x) en fonction de ses voisines. (tabl doit être surcouchée)
void GererCoucheRecursive(string chaine2[], string chaine[]); // initialise la surcouche de chaine2, et la remplie avec chaine.

// fonction de sondage.
void affichageMatrice(string chaine[], int TaiL = TailleL, int TaiC = TailleC); // affiche la matrice dans le canal de sortie standard
void EcritureErreur(string erreur); // insère l'erreur envoyée en arguement dans le fichier FILE_ERR

#endif // MAIN_H_INCLUDED



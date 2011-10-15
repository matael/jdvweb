#include "main.h"



int main()
{
    string tabl[TailleL];
    if(lireMatriceJDV(tabl) == NORMAL)
        TraiterMatriceJDV(tabl);
    else
        RemplirMatrice(tabl);
    SauverMatriceJDV(tabl);
    return 0;
}


int lireMatriceJDV(string chaine[]) // retourne une valeur traduisant l'action à faire
{
    string ligne("");
    ifstream fil(MATRICE_TRAITEE, ios::in);
    if(!fil)
    {
        return AIE;
    }
    bool estVide = true;
    for(int i = 0; i < TailleL; i++)
    {
        getline(fil, ligne);
        chaine[i] = ligne;
        ligne = "";
        for(int u = 0; u < TailleC && estVide == true; u++)
        {
            if(chaine[i][u] == 49)
                estVide = false;
        }
    }

    ofstream Save(MATRICE_SAUVEGARDE);
    if(!Save)
    {
        return AIE;
    }
    for(int i = 0; i < TailleL; i++)
    {
        Save << chaine[i];
        Save << endl;
    }

    // suppression des matrice traitées pour éviter des problèmes de surcharge
    fil.close();
    remove(MATRICE_TRAITEE);
    Save.close();

    if(estVide)
        return AIE;
    else
        return NORMAL;
}


void TraiterMatriceJDV(string chaine[])
{
    string Phase[TailleL], chaine2[TailleL+2];
    // on initialise chaine2
    for(int i = 0; i < TailleL+2; i++)
    {
        for(int u = 0; u < TailleC+2; u++)
            chaine2[i] += 48;
    }

    // on gère la couche récursive de chaine2
    GererCoucheRecursive(chaine2, chaine);

    // maintenant, Phase va être traité
    for(int i = 1; i < TailleL+1; i++)
    {
        for(int u = 1; u < TailleC+1; u++)
            Phase[i-1] += equivCellule(chaine2, i, u);
    }
    // maintenant que Phase contient le tableau traité sans couche extérieure, on le met dans chaine !
    for(int i = 0; i < TailleL; i++)
    {
        for(int u = 0; u < TailleC; u++)
            chaine[i][u] = Phase[i][u];
    }
}


void GererCoucheRecursive(string chaine2[], string chaine[])
{
    // on met chaine dans chaine2, en décalé de 1 case en y et en x
    for(int i = 0; i < TailleL; i++)
    {
        for(int u = 0; u < TailleC; u++)
            chaine2[i+1][u+1] = chaine[i][u];
    }

    // on commence par la première ligne (excepté extrêmes)
    for(int i = 1; i < TailleL; i++)
        chaine2[0][i] = chaine[TailleL-1][i-1];

    // dernière ligne (excepté extrêmes)
    for(int i = 1; i < TailleL; i++)
        chaine2[TailleL+1][i] = chaine[0][i-1];

    // ligne de gauche (excepté extrêmes)
    for(int i = 1; i < TailleC; i++)
        chaine2[i][0] = chaine[i-1][TailleC-1];

    // ligne de droite (excepté extrêmes)
    for(int i = 1; i < TailleC; i++)
        chaine2[i][TailleC+1] = chaine[i-1][0];

    // gestion des quatre coins
    chaine2[0][0] = chaine[TailleL-1][TailleC-1];
    chaine2[TailleL-1][0] = chaine[0][TailleC-1];
    chaine2[0][TailleC-1] = chaine[TailleL-1][0];
    chaine2[TailleL-1][TailleC-1] = chaine[0][0];

} // fin de fonction GererCoucheRecursive()


int equivCellule(string tabl[], int y, int x)
{
    int nb(0);// représente le nombre de cellule vivantes autour de la case considérée
    // les fonctions sont optimisées pour être utilisées dans tabl.


        if(tabl[y-1][x] == 49) // si la case haut est habitée, alors on incrémente nb
            nb++;
        if(tabl[y-1][x+1] == 49) // si la case haut-droite est habitée, alors on incrémente nb
            nb++;
        if(tabl[y][x+1] == 49) // si la case droite est habitée, alors on incrémente nb
            nb++;
        if(tabl[y+1][x+1] == 49) // si la case bas-droite est habitée, alors on incrémente nb
            nb++;
        if(tabl[y+1][x] == 49) // si la case bas est habitée, alors on incrémente nb
            nb++;
        if(tabl[y+1][x-1] == 49) // si la case bas-gauche est habitée, alors on incrémente nb
            nb++;
        if(tabl[y][x-1] == 49) // si la case gauche est habitée, alors on incrémente nb
            nb++;
        if(tabl[y-1][x-1] == 49) // si la case haut-gauche est habitée, alors on incrémente nb
            nb++;

        // on agit alors dans Phase, en fonction de nb.
    if(nb >= LIM_ETOUFF) // nb >= 4, donc cellule meurt d'étouffement
        return CEL_MORT;
    if(nb == VAL_CREA) // nb = 3
        return CEL_VIE;
    if(nb <= LIM_ISOL) // nb <= 1
        return CEL_MORT;
    else // nb = 2
        return tabl[y][x];
} // fin de fonction equivCellule()


void affichageMatrice(string chaine[], int TaiL, int TaiC)
{
    for(int i = 0; i < TaiL; i++)
    {
        for(int u = 0; u < TaiC; u++)
            cout << chaine[i][u];
        cout << endl;
    }
}


void SauverMatriceJDV(string tabl[])
{
    ofstream test(MATRICE_TRAITEE);
    if(test)
    {
        for(int i = 0; i < TailleL; i++)
        {
            test << tabl[i];
            test << endl;
        }
    }
    else
        EcritureErreur("La matrice de traitement n'a pas été ouverte");
    test.close();
}


void RemplirMatrice(string tab[])
{
    srand(time(0));
    int nbAleatoire(0);
    for(int i = 0; i < TailleL; i++)
    {
        for(int u = 0; u < TailleC; u++)
        {
            nbAleatoire = rand() % 3; // nb aléatoire entre 0 et 1
            if(nbAleatoire == 0) // une chance sur tois d'avoir une cellule vivante.
                tab[i] += 49; // nbAleatoire est jouté à tab en ASCII.
            else
                tab[i] += 48;
        }
    }
}


void EcritureErreur(string erreur)
{
    ofstream err(FILE_ERR, ios::app);
    err << endl << erreur << endl;
    err.close();
}




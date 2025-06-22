#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//fonction qui va afficher la grille

void affiche_grid(char grid[3][3]){
    
    printf("\n ----BIENVENUE SUR TIC TAC TOE----\n");

        // Boucle pour parcourir les lignes de la grille (i de 0 à 2)
    for(int i = 0; i < 3; i++){

        // Affiche la ligne supérieure pour chaque case (---|---|---)
        printf("---|---|---\n");

        // Affiche le contenu de chaque case pour la ligne actuelle
        for(int j = 0; j < 3; j++){

            // Affiche une barre verticale avant chaque case et le contenu de la case
            printf(" %c ", grid[i][j]);

            // Affiche une barre verticale après la dernière case de la ligne

            if (j < 2) { // Pour ne pas afficher une barre en trop à la fin de la ligne
                printf("|");
            }
        }
        printf("\n");
    }
     printf("---|---|---\n");// Affiche la dernière ligne inférieure de la grille

}


//fonction qui initialise la grid

char initialise(char grid[3][3]){
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        grid[i][j] = ' '; // Initialise toutes les cases à vide
    }
}
}

//fonnction qui verifie la victoire

char verifie_victoire(char grid[3][3]){

    // Vérification des lignes horizontales

    for (int i = 0; i < 3; i++) {
        // Si les trois cases de la ligne sont identiques et non vides
        if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] && grid[i][0] != ' ') {
            return grid[i][0]; // Retourne le caractère du joueur gagnant
        }
    }

    // Vérification des colonnes verticales

    for (int j = 0; j < 3; j++) {
        // Si les trois cases de la colonne sont identiques et non vides
        if (grid[0][j] == grid[1][j] && grid[1][j] == grid[2][j] && grid[0][j] != ' ') {
            return grid[0][j]; // Retourne le caractère du joueur gagnant
        }
    }

    // Vérification premiere diagonale

    if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[0][0] != ' ') {
        return grid[0][0]; // Retourne le caractère du joueur gagnant
    }

    // Vérification deuxieme diagonale
    if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0] && grid[0][2] != ' ') {
        return grid[0][2]; // Retourne le caractère du joueur gagnant
    }
    return ' '; // Aucun gagnant pour l'instant, retourne un espace

}

//fonction qui verifie l'égalité

bool verifieEgalite(char grid[3][3]){
    for(int i=0; i<3; i++){
         for (int j = 0; j < 3; j++) {
            if (grid[i][j] == ' ') {
                return false; // il reste au moins une case vide
            }
        }
    }
    return true; // toutes les cases sont remplies donc match nil
}
    
void Jouer(){

    char grid[3][3];
    char player;
    bool finpartie;
    char gagnant;
    int tour;
    
    do{

    initialise(grid); //pour commencer la partie
    char player = 'X';
    bool finpartie= false;
    char gagnant = ' ';
    int tour = 0; //on sait qu'une partie a 09 tours

    
    while(!finpartie){

        affiche_grid(grid);
        int ligne, colonne;
        printf("Joueur %c, entrer la position ligne et colonne \n", player); //ligne+colonne
        scanf("%d %d", &ligne, &colonne);
        //tjrs ajuster pour une sorte de convertion en lamgage machine
        ligne--;
        colonne--;

         // validation et application du tour

        if (ligne >= 0 && ligne < 3 && colonne >= 0 && colonne < 3 && grid[ligne][colonne] == ' ') {
                grid[ligne][colonne] = player;
                tour++; // incrémenter seulement si le coup est valide
            } else {
                printf("Coup invalide, reessayer.\n");
                continue; // redemander au même joueur
            }

            gagnant = verifie_victoire(grid);
            if (gagnant != ' ') {
                affiche_grid(grid);
                printf("Le joueur %c a gagne !\n", gagnant);
                finpartie = true;
            } else if (verifieEgalite(grid)) { // toutes les cases sont remplies
                affiche_grid(grid);
                printf("Match nul !\n");
                finpartie = true;
            }
        
            // Changer de joueur si la partie n'est pas terminée et pas de gagnant/nul
            if (!finpartie) {
                if (player == 'X') {
                    player = 'O';
                } else {
                    player = 'X';
                }
            }
        }

        char rejouer;
        printf("Voulez-vous rejouer ? (o/n) : ");
        
        if (rejouer == 'o' || rejouer == 'O') {// l'espace avant %c est important pour le caractère newline laissé par le précédent scanf
        scanf(" %c", &rejouer);
            finpartie = false; // permet de boucler à nouveau dans main
        } else {
            finpartie = true; // arrête la boucle dans main
        }

    } while (!finpartie); // boucle externe pour rejouer
}

int main (){
    Jouer();
    return 0;
}
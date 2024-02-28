#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int SIZE = 3;
const char EMPTY = '-';
const char COMPUTER = 'X';
const char HUMAN = 'O';

// Définition de la classe Morpion
class Morpion {
public:
    void jouer();
    
private:
    char plateau[SIZE][SIZE];
    int minimax(char joueur);
    bool estPlein();
    bool estGagnant(char joueur);
    void afficherPlateau();
};

// Fonction pour jouer au jeu
void Morpion::jouer() {
    // Initialisation du plateau
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            plateau[i][j] = EMPTY;
        }
    }

    char tour = COMPUTER;
    int ligne, colonne;

    // Boucle principale du jeu
    while (!estPlein()) {
        afficherPlateau();
        
        if (tour == COMPUTER) {
            int meilleurScore = INT_MIN;
            int meilleurCoup = -1;
            
            // Recherche du meilleur coup pour l'ordinateur
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    if (plateau[i][j] == EMPTY) {
                        plateau[i][j] = COMPUTER;
                        int score = minimax(HUMAN);
                        plateau[i][j] = EMPTY;

                        if (score > meilleurScore) {
                            meilleurScore = score;
                            meilleurCoup = i * SIZE + j;
                        }
                    }
                }
            }
            
            ligne = meilleurCoup / SIZE;
            colonne = meilleurCoup % SIZE;
        } else {
            // Tour du joueur humain
            cout << "Entrez la ligne et la colonne pour placer votre symbole (de 0 à 2) : ";
            cin >> ligne >> colonne;
        }
        
        // Mettre à jour le plateau avec le coup effectué
        plateau[ligne][colonne] = tour;
        
        // Vérifier s'il y a un gagnant
        if (estGagnant(tour)) {
            afficherPlateau();
            if (tour == COMPUTER)
                cout << "L'ordinateur a gagné !" << endl;
            else
                cout << "Vous avez gagné !" << endl;
            return;
        }
        
        // Changer de joueur
        tour = (tour == COMPUTER) ? HUMAN : COMPUTER;
    }

    // Si aucun gagnant et le plateau est plein, c'est une égalité
    afficherPlateau();
    cout << "Match nul !" << endl;
}

// Fonction MinMax récursive
int Morpion::minimax(char joueur) {
    // Base case: Si le jeu est terminé, retourner le score
    if (estGagnant(COMPUTER)) return 1;
    if (estGagnant(HUMAN)) return -1;
    if (estPlein()) return 0;
    
    // Si c'est le tour de l'ordinateur, chercher le meilleur score
    if (joueur == COMPUTER) {
        int meilleurScore = INT_MIN;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (plateau[i][j] == EMPTY) {
                    plateau[i][j] = COMPUTER;
                    int score = minimax(HUMAN);
                    plateau[i][j] = EMPTY;
                    meilleurScore = max(meilleurScore, score);
                }
            }
        }
        return meilleurScore;
    } else { // Si c'est le tour du joueur humain, chercher le pire score
        int pireScore = INT_MAX;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (plateau[i][j] == EMPTY) {
                    plateau[i][j] = HUMAN;
                    int score = minimax(COMPUTER);
                    plateau[i][j] = EMPTY;
                    pireScore = min(pireScore, score);
                }
            }
        }
        return pireScore;
    }
}

// Fonction pour vérifier si le plateau est plein
bool Morpion::estPlein() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (plateau[i][j] == EMPTY)
                return false;
        }
    }
    return true;
}

// Fonction pour vérifier s'il y a un gagnant
bool Morpion::estGagnant(char joueur) {
    // Vérification des lignes et des colonnes
    for (int i = 0; i < SIZE; ++i) {
        if (plateau[i][0] == joueur && plateau[i][1] == joueur && plateau[i][2] == joueur)
            return true;
        if (plateau[0][i] == joueur && plateau[1][i] == joueur && plateau[2][i] == joueur)
            return true;
    }
    // Vérification des diagonales
    if (plateau[0][0] == joueur && plateau[1][1] == joueur && plateau[2][2] == joueur)
        return true;
    if (plateau[0][2] == joueur && plateau[1][1] == joueur && plateau[2][0] == joueur)
        return true;
    return false;
}

// Fonction pour afficher le plateau de jeu
void Morpion::afficherPlateau() {
    cout << "Plateau actuel :" << endl;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << plateau[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    Morpion jeu;
    jeu.jouer();
    return 0;
}

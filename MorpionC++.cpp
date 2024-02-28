#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

const int SIZE = 3;
const char EMPTY = '-';
const char COMPUTER = 'X';
const char HUMAN = 'O';

class Morpion {
public:
    void jouer(const char* nomFichier);
    
private:
    char plateau[SIZE][SIZE];
    int minimax(char joueur);
    bool estPlein();
    bool estGagnant(char joueur);
    void afficherPlateau();
};

void Morpion::jouer(const char* nomFichier) {
    ifstream fichier(nomFichier);
    if (!fichier) {
        cerr << "Erreur: Impossible d'ouvrir le fichier." << endl;
        return;
    }

    vector<vector<char>> grilles;
    string ligne;
    while (getline(fichier, ligne)) {
        vector<char> grille;
        for (char c : ligne) {
            if (c != ' ')
                grille.push_back(c);
        }
        if (grille.size() == SIZE * SIZE)
            grilles.push_back(grille);
    }

    fichier.close();

    for (auto& grille : grilles) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                plateau[i][j] = grille[i * SIZE + j];
            }
        }

        afficherPlateau();

        int score = minimax(COMPUTER);

        if (score > 0)
            cout << "L'ordinateur a gagné !" << endl;
        else if (score < 0)
            cout << "Le joueur humain a gagné !" << endl;
        else
            cout << "Match nul !" << endl;

        cout << endl;
    }
}

int Morpion::minimax(char joueur) {
    if (estGagnant(COMPUTER)) return 1;
    if (estGagnant(HUMAN)) return -1;
    if (estPlein()) return 0;

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
    } else {
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

bool Morpion::estPlein() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (plateau[i][j] == EMPTY)
                return false;
        }
    }
    return true;
}

bool Morpion::estGagnant(char joueur) {
    for (int i = 0; i < SIZE; ++i) {
        if (plateau[i][0] == joueur && plateau[i][1] == joueur && plateau[i][2] == joueur)
            return true;
        if (plateau[0][i] == joueur && plateau[1][i] == joueur && plateau[2][i] == joueur)
            return true;
    }
    if (plateau[0][0] == joueur && plateau[1][1] == joueur && plateau[2][2] == joueur)
        return true;
    if (plateau[0][2] == joueur && plateau[1][1] == joueur && plateau[2][0] == joueur)
        return true;
    return false;
}

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

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <nom_fichier>" << endl;
        return 1;
    }

    Morpion jeu;
    jeu.jouer(argv[1]);
    return 0;
}

def afficher_grille(grille):
    for i in range(0, len(grille), 3):
        print(grille[i:i+3])

def lire_grilles_depuis_fichier(nom_fichier):
    grilles = []
    with open(nom_fichier, 'r') as file:
        for line in file:
            grille = [c for c in line] 
            grilles.append(grille)
    return grilles

def minmax(grille, profondeur, joueur_actuel):
    scores = {
        "X": 1,
        "O": -1,
        "": 0
    }
    score = evaluer_grille(grille)
    if score is not None:
        return score
    if joueur_actuel == "X":
        meilleur_score = -float("inf")
        for i in range(9):
            if grille[i] == "":
                grille[i] = joueur_actuel
                score = minmax(grille, profondeur + 1, "O")
                grille[i] = ""
                meilleur_score = max(meilleur_score, score)
        return meilleur_score
    else:
        meilleur_score = float("inf")
        for i in range(9):
            if grille[i] == "":
                grille[i] = joueur_actuel
                score = minmax(grille, profondeur + 1, "X")
                grille[i] = ""
                meilleur_score = min(meilleur_score, score)
        return meilleur_score

def evaluer_grille(grille):
    # Évaluation basique pour le tic-tac-toe
    lignes = [grille[i:i+3] for i in range(0, 9, 3)]
    colonnes = [[grille[j] for j in range(i, 9, 3)] for i in range(3)]
    diagonales = [[grille[0], grille[4], grille[8]], [grille[2], grille[4], grille[6]]]
    
    for ligne in lignes + colonnes + diagonales:
        if ligne.count("X") == 3:
            return 1
        elif ligne.count("O") == 3:
            return -1
    if grille.count("") == 0:
        return 0
    return None

# Lecture des grilles depuis le fichier
nom_fichier = "dataset.txt"
grilles = lire_grilles_depuis_fichier(nom_fichier)

# Test de l'algorithme Minimax sur chaque grille
for i, grille in enumerate(grilles, 1):
    print(f"Grille {i}:")
    afficher_grille(grille)
    score = minmax(grille, 0, "X")
    print("Score optimal pour le joueur X:", score)
    print()

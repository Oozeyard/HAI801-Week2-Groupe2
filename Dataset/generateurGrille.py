def generate_tic_tac_toe_boards(board, player, all_boards):
	# Vérifier si la grille est pleine (c'est-à-dire s'il y a un match nul)
    if " " not in board:
        all_boards.append(board)
        return

    # Parcourir chaque case de la grille
    for i in range(9):
        if board[i] == " ":  # Vérifier si la case est vide
            new_board = list(board)  # Créer une nouvelle grille basée sur l'ancienne
            new_board[i] = player  # Placer le symbole du joueur dans la case
            #if new_board not in all_boards:

            all_boards.append("".join(new_board))  # Ajouter la nouvelle grille à la liste
            # Changer de joueur pour le prochain coup
            next_player = "X" if player == "O" else "O"
            # Rappel récursif pour générer les grilles possibles après ce coup
            generate_tic_tac_toe_boards("".join(new_board), next_player, all_boards)

# Fonction pour générer toutes les grilles possibles pour le Tic Tac Toe
def generate_all_possible_boards():
	all_boards = []
	# Commencer avec une grille vide et le premier joueur (X)
	generate_tic_tac_toe_boards(" " * 9, "X", all_boards)
	return all_boards

# Tester la fonction
all_possible_boards = generate_all_possible_boards()
for board in all_possible_boards:
	print(board)

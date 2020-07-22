# filler

*Le jeu de Filler consiste à faire s'affronter 2 joueurs sur un plateau. Ils doivent tour à tour placer une pièce fournis par une vm tant que cela est possible.
Le joueur occupant le plus de place sur le plateau à la fin de la partie l'emporte.*

## Strategie du joueur
Il va d'abord s'étendre vers les 4 coins du plateau, priorisant ceux plus proches des dernières pièces posées par l'adversaire.
Puis remplir les espaces aux alentours de l'autre joueur.
Il dispose également d'une strtégie de remplissage, lorsque l'adversaire est inactif, qui consiste simplement à placer les pièces dans le premier emplacement libre
depuis le coin supérieur gauche du plateau.

# CPPMicroProj-Agriculture
Un micro-jeu en C++ basé sur la chance autour du thème de l'agriculture et de sa potentielle considération comme la plus grande erreur de l'humanité.

# But du jeu
Le but du jeu est de gagner le plus de points possible en utilisant des cartes qui représentent des actions agricoles. Chaque carte a un nombre de dés à lancer, et le score est la somme des résultats des dés. Des cartes outils peuvent être utilisées pour améliorer le score.

# Ancrage au thème
Le hasard de chaque carte ressource représente les aléas de la production d'un agriculteur, tandis que les cartes outils représentent les innovations qui peuvent améliorer la production.
Le jeu souligne le fait que l'agriculture n'est pas une science exacte, mais plutôt un domaine où le hasard joue un rôle important, où la rémunération des agriculteurs en dépend.

# Comment générer le jeu ?
- Ouvrez un terminal dans CardProject
- Tapez cmake .
- Faites la touche entrée
- Tapez cmake --build . --config Release
- Faites la touche entrée 
- Si tout va bien, le jeu se lance

# Comment jouer ?
Le joueur dispose de 5 cartes tirées aléatoirement au début du jeu. À chaque tour, il peut choisir de jouer une carte ressource ou une carte outil. Les cartes ressources sont utilisées pour lancer des dés et accumuler des points, tandis que les cartes outils peuvent être utilisées pour améliorer le score des cartes ressources.
Lorsqu'une carte est jouée, elle est retirée de la main du joueur et une nouvelle carte est tirée du paquet. Le jeu se termine lorsque le joueur a dépassé le quota de points nécessaire, ou alors lorsqu'il a dépassé le coût maximal.
Le jeu est sous la forme d'un point & click.

# Design et optimisations
- Utilisation de SFML pour l'affichage et la gestion des inputs.
- PugiXML est utilisé pour permettre une customisation simple et rapide des cartes et niveaux.
- Les cartes et les niveaux sont générés dynamiquement à partir de fichiers XML, à l'aide du Design Pattern Factory.
- Les états du jeu (en cours, victoire et défaite) sont gérés par un State Design Pattern (State Machine simple).
- La pioche est un vecteur de nom de cartes, et les cartes sont créées dynamiquement à partir de ces noms, permettant de ne pas avoir à créer un grand nombre de carte pour créer la pioche.
- La classe Card est abstraite, facilitant l'implémentation et l'ajout de différent types de cartes (Resource, tool, etc..)

# Screenshot
![screen](https://github.com/user-attachments/assets/bb15a6a5-02c6-42c2-b09d-cf335c68d752)


# Diagramme de classe
![diagramme_classe](https://github.com/user-attachments/assets/0783c5a2-715a-43f9-a818-2aa9f833dec4)


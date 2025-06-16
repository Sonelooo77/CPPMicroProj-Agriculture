# CPPMicroProj-Agriculture
Un micro-jeu en C++ bas� sur la chance autour du th�me de l'agriculture et de sa potentielle consid�ration comme la plus grande erreur de l'humanit�.

# But du jeu
Le but du jeu est de gagner le plus de points possible en utilisant des cartes qui repr�sentent des actions agricoles. Chaque carte a un nombre de d�s � lancer, et le score est la somme des r�sultats des d�s. Des cartes outils peuvent �tre utilis�es pour am�liorer le score.

# Ancrage au th�me
Le hasard de chaque carte ressource repr�sente les al�as de la production d'un agriculteur, tandis que les cartes outils repr�sentent les innovations qui peuvent am�liorer la production.
Le jeu souligne le fait que l'agriculture n'est pas une science exacte, mais plut�t un domaine o� le hasard joue un r�le important, o� la r�mun�ration des agriculteurs en d�pend.

# Comment jouer ?
Le joueur dispose de 5 cartes tir�es al�atoirement au d�but du jeu. � chaque tour, il peut choisir de jouer une carte ressource ou une carte outil. Les cartes ressources sont utilis�es pour lancer des d�s et accumuler des points, tandis que les cartes outils peuvent �tre utilis�es pour am�liorer le score des cartes ressources.
Lorsqu'une carte est jou�e, elle est retir�e de la main du joueur et une nouvelle carte est tir�e du paquet. Le jeu se termine lorsque le joueur a d�pass� le quota de points n�cessaire, ou alors lorsqu'il a d�pass� le co�t maximal.
Le jeu est sous la forme d'un point & click.

# Design et optimisations
- Utilisation de SFML pour l'affichage et la gestion des inputs.
- PugiXML est utilis� pour permettre une customisation simple et rapide des cartes et niveaux.
- Les cartes et les niveaux sont g�n�r�s dynamiquement � partir de fichiers XML, � l'aide du Design Pattern Factory.
- La pioche est un vecteur de nom de cartes, et les cartes sont cr��es dynamiquement � partir de ces noms, permettant de ne pas avoir � cr�er un grand nombre de carte pour cr�er la pioche.
- La classe Card est abstraite, facilitant l'impl�mentation et l'ajout de diff�rent types de cartes (Resource, tool, etc..)

# Diagramme de classe
![Diagramme de classe]()
# Space Corridor

Jeu 2D développé en C avec SDL2, conçu pour **Linux**. Le joueur pilote un vaisseau, évite les obstacles et les ovnis, puis atteint la ligne d'arrivée.

## Prérequis

Le projet est prévu pour fonctionner sous Linux.

- GCC
- GNU Make
- SDL2
- SDL2_ttf

Installation des dépendances sous Debian / Ubuntu :

```bash
sudo apt update
sudo apt install build-essential libsdl2-dev libsdl2-ttf-dev
```

## Compilation

Depuis le dossier du projet :

```bash
make spacecorridor
```

Pour repartir d'une compilation propre :

```bash
make clean
make spacecorridor
```

## Lancement

Lancer le jeu depuis le dossier du projet.

```bash
./spacecorridor
```

Les images et la police sont chargées avec des chemins relatifs. Si le jeu ne trouve pas les ressources, vérifiez que le terminal se trouve bien dans le dossier du projet.

## Contrôles

| Touche | Action |
|---|---|
| `Espace` | Démarrer le jeu / tirer un missile |
| `Flèches gauche/droite` | Déplacer le vaisseau |
| `Q` / `D` | Déplacer le vaisseau |
| `Z` / `Flèche haut` | Accélérer |
| `S` / `Flèche bas` | Ralentir |
| `Échap` | Quitter |

## Structure

```text
.
├── main.c              # Boucle principale et gestion des événements
├── logique.c/.h        # Logique du jeu et collisions
├── affichage.c/.h      # Affichage et gestion des ressources
├── sdl2-light.c/.h     # Fonctions utilitaires SDL2
├── sdl2-ttf-light.c/.h # Fonctions utilitaires SDL2_ttf
├── constantes.h        # Constantes du jeu
├── ressources/         # Images et police
└── Makefile            # Compilation
```

## Nettoyage

```bash
make clean
```

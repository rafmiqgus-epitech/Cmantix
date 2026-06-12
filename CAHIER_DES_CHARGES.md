# Cahier des charges — Cmantix

## 1. Présentation du projet

### 1.1 Contexte

Cmantix est une reproduction du jeu en ligne **Cémantix** développée en C.
Le joueur doit deviner un mot secret en proposant des mots. Pour chaque proposition, le jeu affiche un score de similarité sémantique (basé sur des vecteurs de mots) indiquant à quel point le mot proposé est proche du mot cible.

### 1.2 Objectifs

- Recréer l'expérience complète de Cémantix dans un terminal
- Utiliser des word embeddings (FastText français) pour calculer la similarité sémantique
- Concevoir un format binaire personnalisé (`.cvec`) pour un chargement rapide des vecteurs
- Proposer une interface utilisateur fluide via ncurses

### 1.3 Public cible

Tout utilisateur francophone disposant d'un terminal Unix/Linux.

---

## 2. Description fonctionnelle

### 2.1 Règles du jeu

- Au lancement, le programme sélectionne un mot secret parmi un vocabulaire de ~100 000 mots français.
- Le joueur propose un mot à chaque tour.
- Le programme calcule la **similarité cosinus** entre le vecteur du mot proposé et celui du mot secret.
- Un score (température) est affiché, de 0 (très éloigné) à 1000 (identique).
- Le joueur gagne lorsqu'il trouve le mot exact.
- L'historique des propositions est affiché, trié par score de similarité.

### 2.2 Fonctionnalités principales

| Fonctionnalité | Description |
|----------------|-------------|
| Deviner un mot | Le joueur saisit un mot et reçoit un score de similarité |
| Historique des propositions | Liste triée des mots déjà proposés avec leurs scores |
| Indicateur de progression | Barre ou jauge visuelle de la proximité |
| Mot du jour | Un mot différent chaque jour (basé sur la date) |
| Gestion des mots invalides | Message clair si le mot n'est pas dans le vocabulaire |

### 2.3 Fonctionnalités secondaires (optionnelles)

| Fonctionnalité | Description |
|----------------|-------------|
| Statistiques | Nombre de parties jouées, moyenne de tentatives |
| Indices | Possibilité de demander un indice (première lettre, nombre de lettres) |
| Mode libre | Jouer avec un mot aléatoire (pas lié à la date) |
| Sauvegarde | Reprendre une partie en cours |

---

## 3. Architecture technique

### 3.1 Vue d'ensemble

```
FastText .vec ──→ vec2bin ──→ .cvec ──→ Cmantix (ncurses)
  (texte)        (outil)    (binaire)     (jeu)
```

### 3.2 Modules du jeu

```
src/
├── main.c          # Point d'entrée
├── game/           # Logique de jeu (mot secret, score, victoire)
├── word2vec/       # Chargement des vecteurs, calcul de similarité
├── ui/             # Interface ncurses (affichage, saisie)
└── utils/          # Fonctions utilitaires (chaînes, mémoire)
```

| Module | Responsabilité |
|--------|----------------|
| `game/` | Sélection du mot secret, gestion des tours, historique des propositions, conditions de victoire |
| `word2vec/` | Chargement du fichier `.cvec`, table de hachage des mots, calcul de la similarité cosinus |
| `ui/` | Initialisation ncurses, affichage du tableau de scores, saisie utilisateur, couleurs |
| `utils/` | Manipulation de chaînes, gestion mémoire, opérations sur fichiers |

### 3.3 Outil vec2bin

Outil séparé situé dans `vec2bin/` qui convertit les fichiers texte FastText (`.vec`) en format binaire personnalisé (`.cvec`).

### 3.4 Format binaire .cvec

Format en 4 sections :

1. **Header** (16 octets) : magic number, version, nombre de mots, dimensions
2. **Table d'index** (12 octets × N) : offset, longueur, index du vecteur
3. **Pool de chaînes** (taille variable) : tous les mots concaténés
4. **Données vectorielles** (1200 octets × N) : tableaux de float32

Spécification complète : `vec2bin/FORMAT.md`

### 3.5 Dépendances

| Dépendance | Usage |
|------------|-------|
| ncurses | Interface terminal |
| libm | Fonctions mathématiques (sqrt pour la similarité cosinus) |
| FastText cc.fr.300.vec | Vecteurs de mots français (source de données) |

### 3.6 Compilation

- Compilateur : clang
- Flags : `-Wall -Wextra -g3`
- Build system : Makefiles séparés (projet principal + vec2bin)

---

## 4. Contraintes techniques

| Contrainte | Détail |
|------------|--------|
| Langage | C (standard C99 ou supérieur) |
| Plateforme | Linux |
| Mémoire | ~120 Mo RAM pour 100 000 vecteurs de 300 dimensions |
| Fichier de données | ~300 Mo pour le fichier `.cvec` (100k mots) |
| Temps de chargement | < 5 secondes pour charger les vecteurs en mémoire |

---

## 5. Étapes de développement

### Phase 1 — Fondations (vec2bin + chargement)

**Objectif :** Pouvoir convertir et charger des vecteurs de mots.

- [ ] Implémenter le convertisseur vec2bin complet
  - [ ] Parsing du fichier `.vec` (header + lignes de mots)
  - [ ] Construction des buffers (index, string pool, vecteurs)
  - [ ] Écriture du fichier `.cvec`
  - [ ] Validation et tests avec des petits fichiers
- [ ] Implémenter le chargeur `.cvec` dans `src/word2vec/`
  - [ ] Lecture et validation du header
  - [ ] Construction de la table de hachage (mot → vecteur)
  - [ ] Fonction de calcul de similarité cosinus

**Livrable :** Un programme capable de convertir un `.vec` en `.cvec`, puis de charger ce `.cvec` et de calculer la similarité entre deux mots.

---

### Phase 2 — Logique de jeu

**Objectif :** Le jeu fonctionne en mode texte basique (sans ncurses).

- [ ] Sélection du mot secret (basé sur la date pour le mode "mot du jour")
- [ ] Boucle de jeu principale (saisie → calcul → affichage)
- [ ] Historique des propositions trié par score
- [ ] Détection de la victoire
- [ ] Gestion des mots non reconnus

**Livrable :** Une version jouable en terminal avec `printf`/`scanf`.

---

### Phase 3 — Interface ncurses

**Objectif :** Expérience utilisateur agréable dans le terminal.

- [ ] Initialisation de ncurses (fenêtres, couleurs)
- [ ] Zone de saisie pour les propositions
- [ ] Tableau d'historique avec scores et couleurs
- [ ] Barre de progression visuelle
- [ ] Gestion des redimensionnements de terminal

**Livrable :** Le jeu complet avec une interface ncurses fonctionnelle.

---

### Phase 4 — Finalisation et extras

**Objectif :** Polish et fonctionnalités optionnelles.

- [ ] Mode libre (mot aléatoire)
- [ ] Système d'indices
- [ ] Statistiques de jeu
- [ ] Sauvegarde/reprise de partie
- [ ] Optimisations (mmap si nécessaire)

**Livrable :** Version finale du jeu avec fonctionnalités bonus.

---

## 6. Jalons (milestones)

| Jalon | Description | Critère de validation |
|-------|-------------|----------------------|
| **M1** | vec2bin fonctionnel | `./vec2bin input.vec output.cvec` produit un fichier `.cvec` valide |
| **M2** | Chargement des vecteurs | Le programme charge un `.cvec` et calcule la similarité entre deux mots donnés |
| **M3** | Prototype jouable | Le jeu fonctionne en mode texte basique (printf/scanf) |
| **M4** | Interface ncurses | Le jeu est jouable avec une interface terminal complète |
| **M5** | Version finale | Fonctionnalités bonus implémentées, code nettoyé |

---

## 7. Critères de qualité

- **Pas de fuites mémoire** : validation avec valgrind
- **Gestion des erreurs** : messages clairs pour les cas d'erreur (fichier manquant, format invalide, mot inconnu)
- **Code modulaire** : séparation claire des responsabilités entre modules
- **Compilation propre** : aucun warning avec `-Wall -Wextra`

# Cub3D

**Cub3D** est un mini-moteur 3D en C basé sur le concept du **ray-casting**, inspiré du célèbre jeu *Wolfenstein 3D*.  
Développé avec **miniLibX**, il affiche une vue à la première personne dans un labyrinthe en 2.5D.

Ce projet m’a permis de combiner :  
✅ Mathématiques appliquées (trigonométrie, DDA)  
✅ Programmation graphique (textures / events / window management)  
✅ Parsing robuste d’un fichier de scène  
✅ Gestion clavier & interactions fluides

---

## 🎮 Fonctionnalités

- Déplacement FPS :
  - `W` / `A` / `S` / `D` : avancer / gauche / reculer / droite
  - `←` / `→` : rotation de la caméra
- Fermeture propre avec `ESC` ou la croix fenêtre
- Projection 3D réaliste basée sur Ray-Casting
- Textures selon la face du mur touchée (N / S / E / W)
- Couleurs sol & plafond indépendantes

---

## 🧩 Ray-Casting (résumé)

Pour chaque colonne de pixels :
- Calcul de l’angle du rayon
- Avancement dans la carte avec **DDA**
- Collision détectée → distance → hauteur de la colonne
- Texture appliquée selon la direction du mur

> Optimisation : correction du **fish-eye effect**

---

## 📂 Format `.cub` supporté

Informations obligatoires, dans n’importe quel ordre :
NO ./path_north.xpm
SO ./path_south.xpm
WE ./path_west.xpm
EA ./path_east.xpm

F 220,100,0
C 225,30,0

Puis la carte :
111111
100001
10N001
111111

✅ Map fermée  
✅ Une seule position joueur (N/S/E/W)  

En cas d’erreur →  Error
<message explicite>

---

## 🧱 Architecture technique

*(Adapte avec tes fichiers réels)*

- Parsing de la scène
- Validation de map (fermeture, caractères autorisés…)
- Moteur de ray-casting
- Mouvement + collision
- MiniLibX renderer (images + textures)
- Gestion événements & redimensionnement

---

## 🛠 Compilation

```sh
make
./cub3D maps/map.cub

make clean
make fclean
make re
```

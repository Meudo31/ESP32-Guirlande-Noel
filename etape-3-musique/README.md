# Étape 3 : la guirlande danse sur la musique

On ajoute un petit micro numérique INMP441 et trois effets qui suivent la musique, en plus des 8 effets de l'étape 1 :

- **VU-mètre** : la guirlande se remplit depuis le milieu, du vert au rouge, selon le volume.
- **Pulsation** : toute la guirlande flashe sur chaque coup de basse (grosse caisse), avec une nouvelle couleur à chaque fois.
- **Étincelles** : des points de couleur d'autant plus nombreux que c'est fort, et une gerbe dorée sur les coups de basse.

Tout le reste de l'étape 2 est conservé (page web, programmation, bouton). La page affiche en plus un curseur « Sensibilité du micro ». Le gain s'adapte tout seul au volume de la pièce : ça doit marcher aussi bien sur un chant de Noël doux que sur du métal.

Le code compile avec PlatformIO (ESP32 DevKit, framework Arduino, FastLED) mais n'a pas encore été testé sur une vraie guirlande.

## Câblage

Celui de l'étape 1, plus le micro :

| Broche de l'INMP441 | Vers l'ESP32 |
| --- | --- |
| VDD | **3V3** (surtout pas 5 V) |
| GND | GND |
| SCK | GPIO26 |
| WS | GPIO25 |
| SD | GPIO33 |
| L/R | GND (canal gauche) |

Place le micro hors du boîtier ou face à un trou, loin de l'alimentation, qui peut bourdonner.

## Mise en route

1. Copie `include/config.example.h` en `include/config.h` (il contient les broches du micro en plus de l'étape 2), puis remplis le Wi-Fi.
2. Lance `pio run -t upload`, puis `pio device monitor`. Au démarrage, tu dois lire « Micro INMP441 prêt ».
3. Sur la page web, choisis un effet « Musique : … » et lance de la musique à côté.

## Comment ça marche

- `src/micro.h` lit le son 16 000 fois par seconde et en tire deux mesures : le volume global, et l'énergie des graves (un filtre ne garde que ce qui est en dessous de 150 Hz environ). Un coup de basse, c'est quand les graves dépassent d'un coup leur moyenne de la dernière seconde.
- `src/musique.h` contient les trois effets, sur le même modèle que `effets.h`.
- La sensibilité (1 à 20) agit à la fois sur l'amplitude du VU-mètre et sur le seuil de détection des coups.

## Points à vérifier ensemble

- **Rien ne bouge en mode musique** : avec certains lots d'INMP441, le canal est inversé. Mets `MICRO_CANAL_GAUCHE` à 0 dans `config.h`.
- **Les coups ne tombent pas en rythme** : monte ou baisse la sensibilité. Les seuils (`seuil`, `150`, `180 ms`) dans `micro.h` seront à ajuster ensemble sur de la vraie musique.
- **Tout flashe en permanence** : le micro capte peut-être le bourdonnement de l'alimentation ; éloigne-le ou baisse la sensibilité.

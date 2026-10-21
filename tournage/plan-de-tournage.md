# Plan de tournage n°2 : la guirlande de Noël connectée

Méthode générale et légende (H, V, É, ★) : voir [methode-de-tournage.md](methode-de-tournage.md).

## L'essentiel

- **Titre proposé** : « J'ai fabriqué une guirlande de Noël qui danse sur la musique (ESP32) »
- **Promesse** : une guirlande pilotée du téléphone, qui s'allume toute seule et réagit à la musique, pour 40 €.
- **Durée visée** : 10 à 12 min. Les 3 étapes deviennent 3 chapitres.
- **Calendrier** : les recherches « guirlande Noël » montent de mi-novembre à mi-décembre. Publie la longue **entre le 15 et le 25 novembre**, et tourne au plus tard début novembre. Les Shorts peuvent continuer à tourner jusqu'à Noël, et tu peux en garder 2 ou 3 de réserve pour décembre.
- **À avoir prêt avant de tourner** : les 3 étapes qui marchent, un sapin (même petit) ou une fenêtre à décorer, une enceinte, 2 ou 3 musiques **libres de droits** (Bibliothèque audio YouTube), une pièce qu'on peut plonger dans le noir.
- **Réglage caméra** : exposition manuelle, ISO bas, luminosité des LED réduite le temps du tournage (`LUMINOSITE` à 50-100 au lieu de 150 dans le code), balance des blancs fixe (environ 3200 K pour garder le doré).

## Script de la longue

| Temps | Chapitre | Ce qu'on voit | Ce que tu dis (voix off, à adapter) |
| --- | --- | --- | --- |
| 0:00 | Accroche | P01, P02 | « Cette guirlande danse sur la musique, s'allume toute seule à 17 h, et se pilote du téléphone. Elle m'a coûté 40 euros, et tu peux la faire ce week-end. » |
| 0:20 | Le projet | P03 | Les 3 étapes : les effets au bouton, le téléphone, la musique. Le code est en description. |
| 0:45 | Le matériel | P04 à P06 | La guirlande WS2811 (« chaque LED a sa propre puce »), l'ESP32, l'alimentation, le 74AHCT125. Insiste sur le **5 V**. |
| 2:00 | Étape 1 : les effets | P07 à P15 | Câblage, pourquoi le 74AHCT125 (montrer le bug sans lui), le condensateur, la limite de courant, le fichier `effets.h`, les 8 effets en démonstration. |
| 5:00 | Créer son propre effet | P16, P17 | Tu modifies un effet en direct, par exemple les couleurs de ton club ou de ton pays. |
| 6:00 | Étape 2 : le téléphone | P18 à P22 | La page guirlande.local, effets, couleur, luminosité, la programmation horaire. |
| 8:00 | Étape 3 : la musique | P23 à P28 | Le micro INMP441, le VU-mètre, le flash sur les basses, les étincelles. |
| 10:00 | Installation | P29, P30 | Le boîtier, la guirlande sur le sapin ou à la fenêtre. |
| 10:30 | Démo finale | P31, P32 | Lumière éteinte, musique, la guirlande danse. Laisse 20 secondes sans parler. |
| 11:00 | Fin | P33 | Teaser du bonus (étoile de sapin, guirlandes synchronisées) et appel à l'abonnement. |

## Liste des plans

| N° | Plan | Type | Note |
| --- | --- | --- | --- |
| P01 | Sapin dans le noir, la musique démarre, la guirlande pulse sur les basses | ★ H+V | Le plan qui vend la vidéo. Fais-en plusieurs prises sur plusieurs musiques |
| P02 | Main qui touche le téléphone, la guirlande change de couleur | ★ H+V | Téléphone et guirlande dans le même cadre |
| P03 | Les 3 étapes en schéma ou en 3 plans rapides | H | |
| P04 | Guirlande sortie du sachet, déroulée sur l'établi | H | |
| P05 | Gros plan d'une LED, la petite puce visible | ★ H+V | Macro du téléphone |
| P06 | Toutes les pièces posées une à une | H | Comme pour la boîte aux lettres |
| P07 | Câblage sur plaque d'essai en accéléré | H | Vue au-dessus |
| P08 | Gros plan du 74AHCT125 inséré | H | |
| P09 | **Sans** le 74AHCT125 : couleurs folles, pixels qui clignotent (si ça arrive) | ★ H+V | Si le bug n'apparaît pas, montre juste la différence de tension au multimètre (3,3 V contre 5 V) |
| P10 | Pose du condensateur 1000 µF au départ de la guirlande | H | |
| P11 | `effets.h` dans VS Code, défilement des fonctions | É | |
| P12 | Téléversement | É | |
| P13 | Premier allumage : le scintillement doré | ★ H+V | |
| P14 | Appuis sur le bouton : les 8 effets l'un après l'autre (5 s chacun) | H+V | Tourne-les tous en V, ils servent de « B-roll » partout |
| P15 | Appui long : extinction en fondu | H | |
| P16 | Modification d'un effet en direct dans le code | É | Par exemple les couleurs de ton équipe ou de ton pays |
| P17 | Le nouvel effet s'affiche sur la guirlande | ★ H+V | |
| P18 | La page guirlande.local s'ouvre sur le téléphone | É | Enregistrement d'écran du téléphone |
| P19 | Curseur de luminosité, la guirlande suit en direct | ★ H+V | Téléphone et guirlande dans le même cadre |
| P20 | Choix d'une couleur au nuancier | H+V | |
| P21 | Réglage de l'heure d'allumage | É | |
| P22 | Plan fixe sur la fenêtre, l'horloge passe 17 h, la guirlande s'allume seule | ★ H+V | Mets une horloge visible ou une incrustation de l'heure |
| P23 | Micro INMP441 en gros plan à côté d'une pièce | H | |
| P24 | Câblage du micro | H | |
| P25 | VU-mètre : tu parles ou tapes dans les mains, les LED montent | ★ H+V | |
| P26 | Flash sur les coups de basse | ★ H+V | Musique très rythmée |
| P27 | Étincelles sur une musique douce | H+V | |
| P28 | Moniteur série avec les niveaux du micro | É | |
| P29 | Le montage rangé dans le boîtier | H | |
| P30 | Installation de la guirlande sur le sapin ou la fenêtre, en accéléré | H | |
| P31 | Démo finale : plan large, lumière éteinte, musique | ★ H+V | Au moins 1 minute continue, de deux angles |
| P32 | Détails : reflets dans les boules, visages qui regardent (si quelqu'un est d'accord) | H | Plans d'ambiance |
| P33 | Étoile de sapin ou deuxième guirlande, même en simple aperçu | H | Teaser du bonus |

## Les 5 Shorts

| N° | Accroche (2 premières secondes) | Plans | Déroulé |
| --- | --- | --- | --- |
| S1 | « Ma guirlande de Noël danse sur la musique » | P01, P26, P31 | Le Short vitrine : le résultat, puis « un ESP32 et un micro à 3 € ». À publier en premier. |
| S2 | « 8 effets de Noël, un seul bouton » | P13, P14 | Défilé rapide des 8 effets, rythmé sur la musique. Short court (20-30 s), très bon en boucle. |
| S3 | « Je pilote ma guirlande depuis mon téléphone, sans appli » | P02, P18, P19, P20 | La page web guirlande.local, sans abonnement ni appli à installer. |
| S4 | « Ta guirlande fait n'importe quoi ? Voici la pièce à 1 € qui manque » | P09, P08, P13 | Le 74AHCT125 : problème puis solution. Short pédagogique, idéal pour les recherches. |
| S5 | « Elle s'allume toute seule à 17 h » | P22, P21, P31 | La programmation horaire. Peut aussi devenir « Ma guirlande aux couleurs de [ton équipe] » avec P16-P17. |

**Shorts de réserve pour décembre** (si tu as le temps de les monter) : « Comment fabriquer ton propre effet en 10 lignes » (P16-P17), « Guirlande du commerce contre guirlande ESP32 ».

## Checklist du jour J

- Pièce sombre, rideaux tirés pour les plans de démo ; lumière de l'établi pour les plans de câblage.
- Musique libre de droits uniquement (sinon la vidéo sera démonétisée ou bloquée).
- Luminosité des LED réduite pour le tournage, à remettre ensuite.
- Le nom du Wi-Fi et l'adresse IP masqués si ton réseau est visible.

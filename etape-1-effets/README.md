# Étape 1 : les effets, au bouton

La guirlande s'allume sur un scintillement doré. Un appui court sur le bouton passe à l'effet suivant, un appui long (1 seconde) l'éteint ou la rallume en fondu. Pas de Wi-Fi à cette étape.

Les 8 effets : couleur unie (blanc chaud), scintillement doré, sucre d'orge (rayures rouges et blanches qui défilent), arc-en-ciel, bougies, neige, rouge et vert, confettis. Ils sont tous dans `src/effets.h`, un effet par fonction : c'est le fichier à montrer dans la vidéo pour expliquer comment on en crée un.

Le code compile avec PlatformIO (ESP32 DevKit, framework Arduino, FastLED) mais n'a pas encore été testé sur une vraie guirlande.

## Câblage

L'ESP32 sort un signal de 3,3 V alors que la guirlande attend du 5 V : ça marche parfois sans rien, mais souvent avec des couleurs folles ou des pixels qui clignotent. Le 74AHCT125 remet le signal à 5 V proprement.

| De | Vers |
| --- | --- |
| Alimentation 5 V, borne + | Fil + de la guirlande (souvent rouge), broche **VIN** (ou 5V) de l'ESP32, broche 14 (VCC) du 74AHCT125 |
| Alimentation 5 V, borne - | Fil - de la guirlande (souvent blanc ou bleu), **GND** de l'ESP32, broche 7 (GND) du 74AHCT125 |
| Condensateur 1000 µF | Entre + et - au départ de la guirlande, patte marquée « - » sur le - |
| GPIO16 de l'ESP32 | Broche 2 (1A) du 74AHCT125 |
| Broche 3 (1Y) du 74AHCT125 | Résistance 330 Ω, puis fil de données de la guirlande (souvent vert) |
| Broche 1 (1OE) du 74AHCT125 | GND (active la sortie utilisée) |
| Broches 4, 10 et 13 du 74AHCT125 | 5 V (désactive les trois sorties inutilisées) |
| Bouton poussoir | Entre GPIO4 et GND |

Points importants :

- **Le sens de la guirlande compte** : le signal entre d'un seul côté. Cherche la flèche sur les pixels ou l'inscription DIN / IN ; c'est en général le connecteur femelle.
- **Les masses doivent être communes** : le GND de l'alimentation, de l'ESP32 et de la guirlande sont reliés.
- **Couleurs inversées** (rouge à la place de vert) : change `ORDRE_COULEURS` en haut de `src/main.cpp` (`RGB`, `GRB` ou `BRG`).
- **Courant** : 50 pixels en blanc à fond tirent jusqu'à 3 A. Le code limite le courant à `LIMITE_MA` (2,5 A) ; garde cette valeur sous la capacité de ton alimentation.
- **Au-delà de 100 LED** : le courant chute le long des fils et le bout de la guirlande vire au jaune. Ramène un second fil + et - depuis l'alimentation jusqu'au bout de la guirlande (injection de courant).
- **Pendant le téléversement**, débranche le fil 5 V qui va sur VIN, garde le GND relié : on évite ainsi que l'USB du PC et l'alimentation se battent.

## Mise en route

1. Règle en haut de `src/main.cpp` le nombre de LED (`NB_LEDS`) et le type de guirlande si ce n'est pas une WS2811 de 50 pixels.
2. Branche l'ESP32 en USB et lance `pio run -t upload`, puis `pio device monitor`. Si le téléversement échoue, maintiens le bouton BOOT de la carte au début de l'envoi.
3. Rebranche le 5 V sur VIN : la guirlande scintille. Le moniteur série affiche le nom de chaque effet quand tu appuies sur le bouton.

## Points à vérifier ensemble

- **Premier pixel qui clignote ou couleurs aléatoires** : c'est presque toujours le signal de données. Vérifie le 74AHCT125, la résistance et que le GND est bien commun.
- **Vitesse des effets** : elle est réglée à l'œil, à ajuster quand on verra la vraie guirlande (les délais sont dans `src/effets.h`).
- **Luminosité** : 150 sur 255 par défaut (`LUMINOSITE`). En intérieur, c'est souvent déjà trop ; ça se règlera depuis le téléphone à l'étape 2.

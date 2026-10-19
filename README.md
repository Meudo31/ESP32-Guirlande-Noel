# Guirlande de Noël connectée

Une guirlande de pixels pilotée par un ESP32 : des effets de Noël au bouton, puis une télécommande sur le téléphone avec allumage programmé, puis des effets qui dansent sur la musique. Le projet avance par étapes, du plus simple au plus complet ; chaque étape est un projet PlatformIO autonome et peut faire l'objet d'une vidéo.

| Étape | Dossier | Ce que ça fait | Achat en plus |
| --- | --- | --- | --- |
| 1 | [etape-1-effets](etape-1-effets) | 8 effets de Noël, un bouton pour passer de l'un à l'autre | tout le matériel de base |
| 2 | [etape-2-wifi](etape-2-wifi) | Page web sur le téléphone (effet, couleur, luminosité), allumage et extinction à heure fixe, réglages gardés en mémoire | rien |
| 3 | [etape-3-musique](etape-3-musique) | Micro : VU-mètre, flash sur les coups de basse, étincelles | micro INMP441 |
| Bonus | [bonus](bonus) | Étoile de sapin, plusieurs guirlandes synchronisées, Home Assistant | selon l'idée |

Les trois étapes utilisent le même câblage ; l'étape 3 ajoute seulement le micro. Le code compile avec PlatformIO (ESP32 DevKit, framework Arduino, bibliothèque FastLED) mais n'a pas encore été testé sur une vraie guirlande.

## Liste d'achat par étape

Prix approximatifs, constatés plus bas sur AliExpress que sur Amazon ; chaque étape réutilise ce qui a été acheté avant. Les liens ouvrent une recherche, pas un vendeur précis : prends un article bien noté.

### Étape 1 (environ 35 à 50 €)

| Pièce | Prix approx. | Recherche |
| --- | --- | --- |
| ESP32 DevKit V1 (ESP32-WROOM-32, 38 broches, USB-C) | 5 à 8 € | [Amazon](https://www.amazon.fr/s?k=ESP32+DevKit+V1+WROOM-32+USB-C) · [AliExpress](https://fr.aliexpress.com/w/wholesale-ESP32-DevKit-V1-WROOM-32.html) |
| Guirlande de pixels WS2811, 12 mm, **5 V**, 50 LED, étanche IP68 | 12 à 20 € | [Amazon](https://www.amazon.fr/s?k=guirlande+pixel+WS2811+12mm+5V+50) · [AliExpress](https://fr.aliexpress.com/w/wholesale-WS2811-12mm-5V-pixel-string.html) |
| Alimentation 5 V 4 A (bloc secteur à jack) | 8 à 12 € | [Amazon](https://www.amazon.fr/s?k=alimentation+5V+4A+jack) · [AliExpress](https://fr.aliexpress.com/w/wholesale-power-supply-5V-4A.html) |
| Adaptateur jack femelle vers bornier à vis | 1 à 2 € | [Amazon](https://www.amazon.fr/s?k=adaptateur+jack+femelle+bornier+5.5x2.1) · [AliExpress](https://fr.aliexpress.com/w/wholesale-DC-jack-female-terminal-5.5x2.1.html) |
| Circuit 74AHCT125 (boîtier DIP-14), pour passer le signal de 3,3 V à 5 V | 1 à 2 € | [Amazon](https://www.amazon.fr/s?k=74AHCT125) · [AliExpress](https://fr.aliexpress.com/w/wholesale-74AHCT125-DIP.html) |
| Condensateur 1000 µF, 10 V ou plus | moins d'1 € | [Amazon](https://www.amazon.fr/s?k=condensateur+1000uF+16V) · [AliExpress](https://fr.aliexpress.com/w/wholesale-1000uF-16V-capacitor.html) |
| Résistance 330 Ω | moins d'1 € | (dans tout kit de résistances) |
| Bouton poussoir 12 mm | 1 € | [Amazon](https://www.amazon.fr/s?k=bouton+poussoir+12mm) · [AliExpress](https://fr.aliexpress.com/w/wholesale-push-button-12mm.html) |
| Plaque d'essai + fils Dupont (si pas déjà dans ton kit) | 3 à 5 € | [Amazon](https://www.amazon.fr/s?k=breadboard+fils+dupont) · [AliExpress](https://fr.aliexpress.com/w/wholesale-breadboard-dupont-wire.html) |
| Petit boîtier pour l'électronique | 2 à 4 € | [Amazon](https://www.amazon.fr/s?k=boitier+electronique+plastique+petit) · [AliExpress](https://fr.aliexpress.com/w/wholesale-plastic-project-box.html) |

**Variante gros sapin ou façade** : à la place de la guirlande, une bande **WS2812B 5 V, 60 LED/m** (5 m = 300 LED, 15 à 25 €, [Amazon](https://www.amazon.fr/s?k=bande+WS2812B+5V+60+LED+5m) · [AliExpress](https://fr.aliexpress.com/w/wholesale-WS2812B-5V-60-led-5m.html)) avec une alimentation **5 V 10 A** (15 à 20 €). Dans le code : `NB_LEDS 300`, `TYPE_LEDS WS2812B`, `ORDRE_COULEURS GRB`, `LIMITE_MA 8000`, et une seconde arrivée de courant au bout de la bande (voir l'étape 1).

Prends bien du **5 V** : les guirlandes WS2811 existent aussi en 12 V, qui ne se branchent pas comme ici.

### Étape 2 (rien à acheter)

Tout se passe dans le code : il suffit d'un Wi-Fi 2,4 GHz à portée de la guirlande.

### Étape 3 (environ 2 à 4 € en plus)

| Pièce | Prix approx. | Recherche |
| --- | --- | --- |
| Micro numérique I2S INMP441 (module) | 2 à 4 € | [Amazon](https://www.amazon.fr/s?k=INMP441) · [AliExpress](https://fr.aliexpress.com/w/wholesale-INMP441.html) |

### Bonus

| Pièce | Prix approx. | Recherche |
| --- | --- | --- |
| Anneau WS2812B de 16 ou 24 LED (étoile de sapin) | 3 à 6 € | [Amazon](https://www.amazon.fr/s?k=anneau+WS2812B+24+LED) · [AliExpress](https://fr.aliexpress.com/w/wholesale-WS2812B-ring-24.html) |
| Seconde guirlande + second ESP32 (guirlandes synchronisées) | 20 à 30 € | voir l'étape 1 |

## Mise en route

Chaque dossier a son propre README avec le câblage et la mise en route. À l'étape 1, les réglages (nombre de LED, type de guirlande) sont en haut de `src/main.cpp`. Aux étapes 2 et 3 : copier `include/config.example.h` en `include/config.h`, remplir le Wi-Fi et les réglages de la guirlande, puis `pio run -t upload` depuis le dossier de l'étape. Le fichier `config.h` est exclu du dépôt.

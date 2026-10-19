# Étape 2 : la télécommande sur le téléphone

La guirlande se connecte au Wi-Fi et affiche sa propre page web, à ouvrir sur le téléphone à l'adresse **http://guirlande.local**. On y allume et on éteint la guirlande, on choisit l'effet, la couleur unie et la luminosité. Une programmation horaire l'allume et l'éteint toute seule (par exemple de 17 h à 23 h 30), avec l'heure prise sur Internet. Les réglages restent en mémoire après une coupure de courant.

Le bouton de l'étape 1 marche toujours, même si le Wi-Fi est coupé.

Le code compile avec PlatformIO (ESP32 DevKit, framework Arduino, FastLED) mais n'a pas encore été testé sur une vraie guirlande.

## Câblage

Exactement celui de l'étape 1, rien à ajouter.

## Mise en route

1. Copie `include/config.example.h` en `include/config.h`, puis remplis le Wi-Fi et, si besoin, le nombre et le type de LED (ces réglages ont quitté `main.cpp` pour `config.h` à cette étape).
2. Lance `pio run -t upload`, puis `pio device monitor`. Une fois connectée, la guirlande affiche son adresse : `http://guirlande.local ou http://192.168.x.x`.
3. Ouvre l'adresse sur le téléphone, connecté au même Wi-Fi. Astuce : « Ajouter à l'écran d'accueil » donne une vraie icône d'appli.
4. Pour la programmation, coche « Allumer et éteindre tout seul », choisis les heures et appuie sur Enregistrer.

## Comment ça marche

- `src/page.h` contient la page web (HTML, CSS et un peu de JavaScript), stockée dans l'ESP32.
- La page parle à la guirlande par deux adresses : `/etat` renvoie les réglages actuels, `/reglage?effet=3&lum=120` les modifie. On peut donc aussi piloter la guirlande depuis n'importe quel outil capable d'ouvrir une adresse web.
- La programmation n'agit qu'au moment où on entre dans la plage horaire ou qu'on en sort : si tu rallumes la guirlande à la main à minuit, elle reste allumée jusqu'au prochain horaire.
- Les réglages sont écrits en mémoire 3 secondes après la dernière modification, pour ne pas user la mémoire flash quand on fait glisser le curseur de luminosité.

## Points à vérifier ensemble

- **guirlande.local ne s'ouvre pas** : certains téléphones Android ne connaissent pas les adresses en `.local`. Utilise l'adresse IP affichée dans le moniteur série, et fixe-la dans ta box pour qu'elle ne change pas.
- **Wi-Fi 2,4 GHz uniquement** : l'ESP32 ne voit pas les réseaux 5 GHz.
- **Heure** : elle arrive quelques secondes après la connexion au Wi-Fi. Tant qu'elle n'est pas là, la page affiche « Heure pas encore reçue » et la programmation attend.

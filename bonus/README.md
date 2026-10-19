# Bonus

Ces améliorations seront codées après les étapes 1 à 3. Voici comment on les fera ; chacune peut faire une vidéo courte.

## Étoile de sapin

Un anneau WS2812B de 16 ou 24 LED en haut du sapin, branché **à la suite** de la guirlande : sa broche DIN va sur la sortie de données du dernier pixel, et on augmente `NB_LEDS` d'autant. Le code saura que les dernières LED sont l'étoile et lui donnera son propre effet (étoile dorée qui tourne, par exemple) pendant que la guirlande garde le sien. Attention : l'anneau est en GRB alors que beaucoup de guirlandes WS2811 sont en RGB, il faudra corriger les couleurs dans le code.

## Plusieurs guirlandes synchronisées

Une guirlande sur le sapin, une autre à la fenêtre, qui changent d'effet en même temps. Chaque guirlande a son ESP32 ; elles se parlent en **ESP-NOW**, la liaison directe entre ESP32, sans passer par la box. Celle qui a le micro peut envoyer les coups de basse aux autres, pour que toute la maison danse sur la même musique.

## Home Assistant et assistants vocaux

En ajoutant MQTT, la guirlande apparaît dans Home Assistant comme une lampe : allumage par la voix, scénarios (« quand le soleil se couche »), etc.

## Compte à rebours de Noël

Un effet spécial qui se déclenche tout seul le 24 décembre à minuit grâce à l'heure Internet de l'étape 2, et une page qui affiche les jours restants jusqu'à Noël.

## Mise à jour sans fil

Pour ne plus démonter le boîtier : la mise à jour par le Wi-Fi (OTA). Le programme de l'étape 3 occupe déjà 86 % de la mémoire prévue ; il faudra changer le partage de la mémoire de l'ESP32 (`board_build.partitions = min_spiffs.csv` dans `platformio.ini`) pour avoir la place de recevoir la nouvelle version.

## Comparaison avec WLED

WLED est un programme tout fait pour piloter des LED depuis un ESP32. Une vidéo « J'ai fait mon propre WLED » peut comparer les deux : ce que WLED fait de plus, et ce qu'on gagne à tout comprendre de son propre code.

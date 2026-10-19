// Copier ce fichier en config.h et remplir les valeurs.
// config.h ne doit jamais être publié (il contient le mot de passe Wi-Fi).
#pragma once

#define WIFI_SSID       "NomDeTonWifi"
#define WIFI_MOTDEPASSE "MotDePasseWifi"

// Nom de la guirlande sur le réseau : la page s'ouvre sur http://guirlande.local
#define NOM_RESEAU      "guirlande"

// Fuseau horaire pour la programmation (ici : France, heure d'été automatique)
#define FUSEAU_HORAIRE  "CET-1CEST,M3.5.0,M10.5.0/3"
#define SERVEUR_NTP     "pool.ntp.org"

// ---------- Matériel ----------
#define BROCHE_DONNEES  16      // vers l'entrée DIN de la guirlande, à travers le 74AHCT125
#define BROCHE_BOUTON   4       // bouton poussoir entre GPIO4 et GND
#define NB_LEDS         50      // nombre de pixels de la guirlande
#define TYPE_LEDS       WS2811  // WS2811 pour une guirlande à pixels, WS2812B pour une bande
#define ORDRE_COULEURS  RGB     // guirlande WS2811 : souvent RGB ; bande WS2812B : GRB
#define LIMITE_MA       2500    // courant maximal, à garder sous la capacité de l'alimentation 5 V

// Guirlande de Noël - étape 1 : les effets, pilotés par un bouton
//
// Fonctionnement :
//  - La guirlande s'allume sur le premier effet.
//  - Appui court sur le bouton : effet suivant.
//  - Appui long (1 seconde) : éteindre ou rallumer.
//
// Pas de Wi-Fi à cette étape, donc pas de config.h : les réglages sont juste en dessous.

#include <Arduino.h>
#include <FastLED.h>
#include "effets.h"

// ---------- Réglages ----------
#define BROCHE_DONNEES  16      // vers l'entrée DIN de la guirlande, à travers le 74AHCT125
#define BROCHE_BOUTON   4       // bouton poussoir entre GPIO4 et GND
#define NB_LEDS         50      // nombre de pixels de la guirlande
#define TYPE_LEDS       WS2811  // WS2811 pour une guirlande à pixels, WS2812B pour une bande
#define ORDRE_COULEURS  RGB     // guirlande WS2811 : souvent RGB ; bande WS2812B : GRB
#define LUMINOSITE      150     // 0 à 255
#define LIMITE_MA       2500    // courant maximal autorisé, à garder sous la capacité de l'alimentation 5 V

#define APPUI_LONG_MS   1000
#define ANTIREBOND_MS   30

CRGB leds[NB_LEDS];
uint8_t effetCourant = SCINTILLEMENT;
bool allumee = true;

// ---------- Bouton ----------
bool etatBouton = HIGH;          // HIGH = relâché (résistance de tirage interne)
uint32_t dernierChangement = 0;
uint32_t debutAppui = 0;
bool appuiLongTraite = false;

void lireBouton() {
  bool lecture = digitalRead(BROCHE_BOUTON);
  uint32_t maintenant = millis();

  if (lecture != etatBouton && maintenant - dernierChangement > ANTIREBOND_MS) {
    dernierChangement = maintenant;
    etatBouton = lecture;
    if (etatBouton == LOW) {
      debutAppui = maintenant;
      appuiLongTraite = false;
    } else if (!appuiLongTraite && allumee) {
      effetCourant = (effetCourant + 1) % NB_EFFETS;
      Serial.printf("Effet : %s\n", NOMS_EFFETS[effetCourant]);
    }
  }

  if (etatBouton == LOW && !appuiLongTraite && maintenant - debutAppui > APPUI_LONG_MS) {
    appuiLongTraite = true;
    allumee = !allumee;
    Serial.println(allumee ? "Guirlande allumée" : "Guirlande éteinte");
  }
}

// ---------- Programme ----------
void setup() {
  Serial.begin(115200);
  pinMode(BROCHE_BOUTON, INPUT_PULLUP);

  FastLED.addLeds<TYPE_LEDS, BROCHE_DONNEES, ORDRE_COULEURS>(leds, NB_LEDS);
  FastLED.setBrightness(LUMINOSITE);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, LIMITE_MA);
  FastLED.clear(true);

  random16_add_entropy(esp_random());
  Serial.printf("Guirlande prête : %d LED, effet %s\n", NB_LEDS, NOMS_EFFETS[effetCourant]);
}

void loop() {
  lireBouton();

  EVERY_N_MILLISECONDS(16) {  // environ 60 images par seconde
    if (allumee) {
      dessinerEffet(effetCourant, leds, NB_LEDS, BLANC_CHAUD);
    } else {
      fadeToBlackBy(leds, NB_LEDS, 20);  // extinction en fondu
    }
    FastLED.show();
  }
}

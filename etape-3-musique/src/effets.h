// Guirlande de Noël - les effets lumineux
//
// Fichier identique dans les trois étapes. Chaque effet dessine une image dans le tableau leds ;
// il est appelé environ 60 fois par seconde et se base sur millis() pour garder la même vitesse
// quel que soit le nombre de LED.

#pragma once
#include <FastLED.h>

enum Effet : uint8_t {
  COULEUR_UNIE,
  SCINTILLEMENT,
  SUCRE_ORGE,
  ARC_EN_CIEL,
  BOUGIES,
  NEIGE,
  ROUGE_VERT,
  CONFETTIS,
  NB_EFFETS
};

const char* const NOMS_EFFETS[NB_EFFETS] = {
  "Couleur unie", "Scintillement doré", "Sucre d'orge", "Arc-en-ciel",
  "Bougies", "Neige", "Rouge et vert", "Confettis"
};

// Blanc chaud, proche d'une guirlande à ampoules classique
const CRGB BLANC_CHAUD = CRGB(255, 150, 50);

// Fond doré tamisé, avec des éclats qui s'allument au hasard puis s'estompent
static void effetScintillement(CRGB* leds, uint16_t n) {
  const CRGB fond = CRGB(40, 22, 0);
  for (uint16_t i = 0; i < n; i++) leds[i] = blend(leds[i], fond, 12);
  if (random8() < 80) leds[random16(n)] = CRGB(255, 200, 80);
}

// Rayures rouges et blanches qui défilent
static void effetSucreOrge(CRGB* leds, uint16_t n) {
  const uint8_t largeur = 4;
  uint32_t decalage = millis() / 120;
  for (uint16_t i = 0; i < n; i++) {
    leds[i] = ((i + decalage) / largeur) % 2 ? CRGB::Red : CRGB::White;
  }
}

// Arc-en-ciel qui tourne lentement
static void effetArcEnCiel(CRGB* leds, uint16_t n) {
  uint8_t ecart = max(1, 256 / n);
  fill_rainbow(leds, n, millis() / 30, ecart);
}

// Chaque LED vacille comme une flamme, indépendamment des autres
static void effetBougies(CRGB* leds, uint16_t n) {
  uint32_t t = millis() / 3;
  for (uint16_t i = 0; i < n; i++) {
    uint8_t vacillement = inoise8(i * 60, t);
    leds[i] = CRGB(255, 110, 15);
    leds[i].nscale8(qadd8(scale8(vacillement, 200), 40));
  }
}

// Nuit bleutée et flocons blancs qui apparaissent puis fondent
static void effetNeige(CRGB* leds, uint16_t n) {
  const CRGB nuit = CRGB(0, 0, 25);
  for (uint16_t i = 0; i < n; i++) leds[i] = blend(leds[i], nuit, 25);
  if (random8() < 50) leds[random16(n)] = CRGB::White;
}

// LED rouges et vertes alternées qui respirent, et échangent leur place toutes les 2 secondes
static void effetRougeVert(CRGB* leds, uint16_t n) {
  uint8_t lumiere = beatsin8(12, 50, 255);
  uint8_t phase = (millis() / 2000) % 2;
  for (uint16_t i = 0; i < n; i++) {
    leds[i] = ((i + phase) % 2) ? CRGB::Red : CRGB::Green;
    leds[i].nscale8(lumiere);
  }
}

// Points de toutes les couleurs qui s'allument au hasard
static void effetConfettis(CRGB* leds, uint16_t n) {
  fadeToBlackBy(leds, n, 10);
  if (random8() < 120) leds[random16(n)] += CHSV(random8(), 200, 255);
}

// Dessine une image de l'effet demandé. couleur ne sert qu'à l'effet COULEUR_UNIE.
static void dessinerEffet(uint8_t effet, CRGB* leds, uint16_t n, CRGB couleur) {
  switch (effet) {
    case COULEUR_UNIE:  fill_solid(leds, n, couleur); break;
    case SCINTILLEMENT: effetScintillement(leds, n); break;
    case SUCRE_ORGE:    effetSucreOrge(leds, n); break;
    case ARC_EN_CIEL:   effetArcEnCiel(leds, n); break;
    case BOUGIES:       effetBougies(leds, n); break;
    case NEIGE:         effetNeige(leds, n); break;
    case ROUGE_VERT:    effetRougeVert(leds, n); break;
    case CONFETTIS:     effetConfettis(leds, n); break;
    default:            fill_solid(leds, n, CRGB::Black); break;
  }
}

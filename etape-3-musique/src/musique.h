// Guirlande de Noël - les effets qui suivent la musique

#pragma once
#include <FastLED.h>
#include "micro.h"

enum EffetMusique : uint8_t {
  VU_METRE,
  PULSATION,
  ETINCELLES,
  NB_EFFETS_MUSIQUE
};

const char* const NOMS_EFFETS_MUSIQUE[NB_EFFETS_MUSIQUE] = {
  "Musique : VU-mètre", "Musique : pulsation", "Musique : étincelles"
};

// La guirlande se remplit depuis le milieu, du vert au rouge, selon le volume
static void effetVuMetre(CRGB* leds, uint16_t n) {
  fadeToBlackBy(leds, n, 40);
  uint16_t milieu = n / 2;
  uint16_t longueur = son.volume * milieu;
  for (uint16_t i = 0; i < longueur; i++) {
    CRGB couleur = CHSV(96 - (i * 96 / max<uint16_t>(milieu, 1)), 255, 255);  // vert vers rouge
    if (milieu + i < n) leds[milieu + i] = couleur;
    if (milieu >= i + 1) leds[milieu - 1 - i] = couleur;
  }
}

// Toute la guirlande flashe sur chaque coup de basse, et change de couleur à chaque fois
static void effetPulsation(CRGB* leds, uint16_t n) {
  static uint8_t teinte = 0;
  if (son.coup) {
    teinte += 40;
    fill_solid(leds, n, CHSV(teinte, 255, 255));
  } else {
    fadeToBlackBy(leds, n, 18);
  }
}

// Des étincelles d'autant plus nombreuses que la musique est forte, une gerbe dorée sur chaque coup
static void effetEtincelles(CRGB* leds, uint16_t n) {
  fadeToBlackBy(leds, n, 25);
  uint8_t nombre = son.volume * 6;
  for (uint8_t i = 0; i < nombre; i++) leds[random16(n)] += CHSV(random8(), 180, 255);
  if (son.coup) {
    for (uint8_t i = 0; i < n / 5; i++) leds[random16(n)] = CRGB(255, 180, 40);
  }
}

static void dessinerEffetMusique(uint8_t effet, CRGB* leds, uint16_t n) {
  switch (effet) {
    case VU_METRE:   effetVuMetre(leds, n); break;
    case PULSATION:  effetPulsation(leds, n); break;
    case ETINCELLES: effetEtincelles(leds, n); break;
    default:         fill_solid(leds, n, CRGB::Black); break;
  }
}

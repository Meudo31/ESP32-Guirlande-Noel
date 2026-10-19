// Guirlande de Noël - écoute de la musique avec le micro INMP441
//
// Le micro numérique INMP441 envoie le son par le bus I2S. On en tire deux mesures :
//  - le volume global (pour le VU-mètre) ;
//  - les coups de basse (grosse caisse), repérés quand le volume des graves saute d'un coup.
// Le gain s'adapte tout seul : la guirlande réagit aussi bien à un chant de Noël doux qu'à du métal.

#pragma once
#include <Arduino.h>
#include <driver/i2s.h>
#include "config.h"

#define MICRO_PORT        I2S_NUM_0
#define MICRO_FREQUENCE   16000
#define MICRO_BLOC        256     // échantillons lus à chaque fois (16 ms de son)

struct Son {
  float volume = 0;      // 0 à 1 environ, après gain automatique
  bool coup = false;     // passe à vrai sur un coup de basse ; la boucle principale le remet à faux après l'avoir affiché
};

Son son;
static int32_t tamponMicro[MICRO_BLOC];
static float continu = 0;          // composante continue du micro, à retirer
static float grave = 0;            // filtre passe-bas pour isoler les graves
static float plafond = 2000;       // volume maximal récent, pour le gain automatique
static float moyenneGraves = 0;    // énergie moyenne des graves sur la dernière seconde
static uint32_t dernierCoup = 0;

bool demarrerMicro() {
  i2s_config_t config = {};
  config.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX);
  config.sample_rate = MICRO_FREQUENCE;
  config.bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT;
  config.channel_format = MICRO_CANAL_GAUCHE ? I2S_CHANNEL_FMT_ONLY_LEFT : I2S_CHANNEL_FMT_ONLY_RIGHT;
  config.communication_format = I2S_COMM_FORMAT_STAND_I2S;
  config.intr_alloc_flags = ESP_INTR_FLAG_LEVEL1;
  config.dma_buf_count = 4;
  config.dma_buf_len = MICRO_BLOC;

  i2s_pin_config_t broches = {};
  broches.mck_io_num = I2S_PIN_NO_CHANGE;
  broches.bck_io_num = BROCHE_MICRO_SCK;
  broches.ws_io_num = BROCHE_MICRO_WS;
  broches.data_out_num = I2S_PIN_NO_CHANGE;
  broches.data_in_num = BROCHE_MICRO_SD;

  if (i2s_driver_install(MICRO_PORT, &config, 0, nullptr) != ESP_OK) return false;
  if (i2s_set_pin(MICRO_PORT, &broches) != ESP_OK) return false;
  return true;
}

// À appeler à chaque tour de boucle. sensibilite : 1 (peu réactif) à 20 (très réactif).
void ecouterMicro(uint8_t sensibilite) {
  size_t octetsLus = 0;
  i2s_read(MICRO_PORT, tamponMicro, sizeof(tamponMicro), &octetsLus, 0);  // 0 = ne pas attendre
  size_t n = octetsLus / sizeof(int32_t);
  if (n == 0) return;

  float sommeTout = 0, sommeGraves = 0;
  for (size_t i = 0; i < n; i++) {
    float x = tamponMicro[i] >> 14;      // l'INMP441 envoie 24 bits calés à gauche dans 32 bits
    continu += 0.001f * (x - continu);
    x -= continu;
    grave += 0.06f * (x - grave);        // passe-bas vers 150 Hz : basse et grosse caisse
    sommeTout += x * x;
    sommeGraves += grave * grave;
  }
  float volume = sqrtf(sommeTout / n);
  float energieGraves = sqrtf(sommeGraves / n);

  // Gain automatique : le plafond suit les pics et redescend lentement
  plafond = max(volume, plafond * 0.998f);
  plafond = max(plafond, 300.0f);        // en dessous, c'est le bruit de fond de la pièce
  float cible = constrain(volume / plafond * sensibilite / 8.0f, 0.0f, 1.0f);
  son.volume += (cible > son.volume ? 0.6f : 0.1f) * (cible - son.volume);  // monte vite, retombe doucement

  // Coup de basse : les graves dépassent nettement leur moyenne récente
  float seuil = 1.0f + 6.0f / sensibilite;
  if (energieGraves > moyenneGraves * seuil && energieGraves > 150 && millis() - dernierCoup > 180) {
    son.coup = true;
    dernierCoup = millis();
  }
  moyenneGraves += 0.02f * (energieGraves - moyenneGraves);
}

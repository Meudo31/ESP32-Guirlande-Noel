// Guirlande de Noël - étape 2 : télécommande sur le téléphone et programmation horaire
//
// Fonctionnement :
//  - La guirlande se connecte au Wi-Fi et sert une page web sur http://guirlande.local
//    (ou sur son adresse IP, affichée dans le moniteur série).
//  - La page permet d'allumer, d'éteindre, de choisir l'effet, la couleur et la luminosité.
//  - Programmation : allumage et extinction automatiques à heure fixe (heure prise sur Internet).
//  - Les réglages sont gardés en mémoire et retrouvés après une coupure de courant.
//  - Le bouton de l'étape 1 marche toujours, même sans Wi-Fi.

#include <Arduino.h>
#include <FastLED.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Preferences.h>
#include <time.h>
#include "config.h"
#include "effets.h"
#include "page.h"

#define APPUI_LONG_MS     1000
#define ANTIREBOND_MS     30
#define DELAI_SAUVEGARDE  3000  // on attend que les réglages ne bougent plus avant d'écrire en mémoire

CRGB leds[NB_LEDS];
WebServer serveur(80);
Preferences memoire;

struct Reglages {
  bool allumee = true;
  uint8_t effet = SCINTILLEMENT;
  uint8_t luminosite = 150;
  uint32_t couleur = 0xFF9632;   // blanc chaud
  bool programmation = false;
  uint16_t debut = 17 * 60;      // en minutes depuis minuit
  uint16_t fin = 23 * 60 + 30;
} reglages;

bool aSauvegarder = false;
uint32_t derniereModif = 0;
int8_t etaitDansPlage = -1;      // -1 = pas encore vérifié depuis le dernier changement d'horaires

// ---------- Mémoire ----------
void chargerReglages() {
  memoire.begin("guirlande", true);
  reglages.allumee       = memoire.getBool("allumee", reglages.allumee);
  reglages.effet         = memoire.getUChar("effet", reglages.effet);
  reglages.luminosite    = memoire.getUChar("lum", reglages.luminosite);
  reglages.couleur       = memoire.getUInt("couleur", reglages.couleur);
  reglages.programmation = memoire.getBool("prog", reglages.programmation);
  reglages.debut         = memoire.getUShort("debut", reglages.debut);
  reglages.fin           = memoire.getUShort("fin", reglages.fin);
  memoire.end();
  if (reglages.effet >= NB_EFFETS) reglages.effet = 0;
}

void sauvegarderReglages() {
  memoire.begin("guirlande", false);
  memoire.putBool("allumee", reglages.allumee);
  memoire.putUChar("effet", reglages.effet);
  memoire.putUChar("lum", reglages.luminosite);
  memoire.putUInt("couleur", reglages.couleur);
  memoire.putBool("prog", reglages.programmation);
  memoire.putUShort("debut", reglages.debut);
  memoire.putUShort("fin", reglages.fin);
  memoire.end();
  Serial.println("Réglages sauvegardés");
}

void marquerModifie() {
  aSauvegarder = true;
  derniereModif = millis();
}

// ---------- Heure et programmation ----------
bool heureLocale(struct tm& t) {
  return getLocalTime(&t, 0);  // 0 = ne pas attendre si l'heure n'est pas encore arrivée
}

void verifierProgrammation() {
  struct tm t;
  if (!reglages.programmation || !heureLocale(t)) return;

  uint16_t minutes = t.tm_hour * 60 + t.tm_min;
  bool dansPlage = (reglages.debut <= reglages.fin)
      ? (minutes >= reglages.debut && minutes < reglages.fin)
      : (minutes >= reglages.debut || minutes < reglages.fin);  // plage qui passe minuit

  // On n'agit qu'au changement de plage : un allumage à la main en dehors des horaires reste respecté
  if (dansPlage != etaitDansPlage) {
    etaitDansPlage = dansPlage;
    reglages.allumee = dansPlage;
    marquerModifie();
    Serial.println(dansPlage ? "Programmation : allumage" : "Programmation : extinction");
  }
}

String texteHeure(uint16_t minutes) {
  char texte[6];
  snprintf(texte, sizeof(texte), "%02d:%02d", minutes / 60, minutes % 60);
  return texte;
}

bool lireHeure(const String& texte, uint16_t& minutes) {
  int h, m;
  if (sscanf(texte.c_str(), "%d:%d", &h, &m) != 2 || h < 0 || h > 23 || m < 0 || m > 59) return false;
  minutes = h * 60 + m;
  return true;
}

// ---------- Serveur web ----------
String etatJson() {
  String json = "{";
  json += "\"allumee\":" + String(reglages.allumee ? 1 : 0);
  json += ",\"effet\":" + String(reglages.effet);
  json += ",\"lum\":" + String(reglages.luminosite);
  char couleur[7];
  snprintf(couleur, sizeof(couleur), "%06x", reglages.couleur);
  json += ",\"couleur\":\"" + String(couleur) + "\"";
  json += ",\"auto\":" + String(reglages.programmation ? "true" : "false");
  json += ",\"debut\":\"" + texteHeure(reglages.debut) + "\"";
  json += ",\"fin\":\"" + texteHeure(reglages.fin) + "\"";
  struct tm t;
  if (heureLocale(t)) json += ",\"heure\":\"" + texteHeure(t.tm_hour * 60 + t.tm_min) + "\"";
  json += ",\"effets\":[";
  for (uint8_t i = 0; i < NB_EFFETS; i++) {
    if (i) json += ",";
    json += "\"" + String(NOMS_EFFETS[i]) + "\"";
  }
  json += "]}";
  return json;
}

void pageAccueil() {
  serveur.send_P(200, "text/html; charset=utf-8", PAGE_HTML);
}

void pageEtat() {
  serveur.send(200, "application/json", etatJson());
}

// Exemple : /reglage?effet=3&lum=120&couleur=ff0000&allumee=1&auto=1&debut=17:00&fin=23:30
void pageReglage() {
  if (serveur.hasArg("allumee")) reglages.allumee = serveur.arg("allumee").toInt() != 0;
  if (serveur.hasArg("effet")) {
    int effet = serveur.arg("effet").toInt();
    if (effet >= 0 && effet < NB_EFFETS) reglages.effet = effet;
  }
  if (serveur.hasArg("lum")) reglages.luminosite = constrain(serveur.arg("lum").toInt(), 5, 255);
  if (serveur.hasArg("couleur")) reglages.couleur = strtoul(serveur.arg("couleur").c_str(), nullptr, 16) & 0xFFFFFF;
  if (serveur.hasArg("auto")) {
    reglages.programmation = serveur.arg("auto").toInt() != 0;
    etaitDansPlage = -1;  // appliquer les horaires tout de suite
  }
  if (serveur.hasArg("debut")) lireHeure(serveur.arg("debut"), reglages.debut);
  if (serveur.hasArg("fin")) lireHeure(serveur.arg("fin"), reglages.fin);

  marquerModifie();
  verifierProgrammation();
  serveur.send(200, "application/json", etatJson());
}

// ---------- Wi-Fi ----------
bool mdnsDemarre = false;

void surveillerWifi() {
  bool connecte = WiFi.status() == WL_CONNECTED;
  if (connecte && !mdnsDemarre) {
    mdnsDemarre = MDNS.begin(NOM_RESEAU);
    if (mdnsDemarre) MDNS.addService("http", "tcp", 80);
    Serial.printf("Wi-Fi connecté : http://%s.local ou http://%s\n", NOM_RESEAU, WiFi.localIP().toString().c_str());
  } else if (!connecte && mdnsDemarre) {
    MDNS.end();
    mdnsDemarre = false;
    Serial.println("Wi-Fi perdu, reconnexion en cours");
  }
}

// ---------- Bouton ----------
bool etatBouton = HIGH;
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
    } else if (!appuiLongTraite && reglages.allumee) {
      reglages.effet = (reglages.effet + 1) % NB_EFFETS;
      Serial.printf("Effet : %s\n", NOMS_EFFETS[reglages.effet]);
      marquerModifie();
    }
  }

  if (etatBouton == LOW && !appuiLongTraite && maintenant - debutAppui > APPUI_LONG_MS) {
    appuiLongTraite = true;
    reglages.allumee = !reglages.allumee;
    Serial.println(reglages.allumee ? "Guirlande allumée" : "Guirlande éteinte");
    marquerModifie();
  }
}

// ---------- Programme ----------
void setup() {
  Serial.begin(115200);
  pinMode(BROCHE_BOUTON, INPUT_PULLUP);
  chargerReglages();

  FastLED.addLeds<TYPE_LEDS, BROCHE_DONNEES, ORDRE_COULEURS>(leds, NB_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, LIMITE_MA);
  FastLED.clear(true);
  random16_add_entropy(esp_random());

  // Connexion sans attendre : la guirlande s'allume même si le Wi-Fi ne répond pas
  WiFi.mode(WIFI_STA);
  WiFi.setHostname(NOM_RESEAU);
  WiFi.setAutoReconnect(true);
  WiFi.begin(WIFI_SSID, WIFI_MOTDEPASSE);
  configTzTime(FUSEAU_HORAIRE, SERVEUR_NTP);

  serveur.on("/", pageAccueil);
  serveur.on("/etat", pageEtat);
  serveur.on("/reglage", pageReglage);
  serveur.begin();

  Serial.printf("Guirlande prête : %d LED, effet %s\n", NB_LEDS, NOMS_EFFETS[reglages.effet]);
}

void loop() {
  serveur.handleClient();
  lireBouton();

  EVERY_N_SECONDS(1) {
    surveillerWifi();
    verifierProgrammation();
  }

  if (aSauvegarder && millis() - derniereModif > DELAI_SAUVEGARDE) {
    aSauvegarder = false;
    sauvegarderReglages();
  }

  EVERY_N_MILLISECONDS(16) {
    if (reglages.allumee) {
      dessinerEffet(reglages.effet, leds, NB_LEDS, CRGB(reglages.couleur));
    } else {
      fadeToBlackBy(leds, NB_LEDS, 20);
    }
    FastLED.setBrightness(reglages.luminosite);
    FastLED.show();
  }
}

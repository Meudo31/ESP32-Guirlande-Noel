// Guirlande de Noël - la page web de la télécommande
//
// Fichier identique aux étapes 2 et 3. La liste des effets vient de /etat, et le réglage
// de sensibilité du micro n'apparaît que si la guirlande en a un (étape 3).

#pragma once
#include <Arduino.h>

const char PAGE_HTML[] PROGMEM = R"rawliteral(<!DOCTYPE html>
<html lang="fr">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Guirlande de Noël</title>
<style>
  body { font-family: system-ui, sans-serif; background: #10161f; color: #f2f2f2; margin: 0; padding: 16px; }
  h1 { font-size: 1.4em; margin: 0 0 4px; }
  .heure { color: #9aa4b2; margin-bottom: 16px; }
  section { background: #1b2430; border-radius: 12px; padding: 14px; margin-bottom: 14px; }
  h2 { font-size: 1em; margin: 0 0 10px; color: #ffcf6e; }
  button { font-size: 1em; border: 0; border-radius: 10px; padding: 12px; color: #f2f2f2; background: #2c3a4d; }
  .grille { display: grid; grid-template-columns: repeat(auto-fill, minmax(140px, 1fr)); gap: 8px; }
  .actif { background: #c0392b; }
  #interrupteur { width: 100%; font-size: 1.2em; }
  .ligne { display: flex; align-items: center; gap: 10px; margin: 8px 0; }
  input[type=range] { flex: 1; }
  input[type=color] { width: 60px; height: 40px; border: 0; background: none; }
  input[type=time] { font-size: 1em; padding: 6px; border-radius: 8px; border: 0; }
</style>
</head>
<body>
<h1>🎄 Guirlande de Noël</h1>
<div class="heure" id="heure"></div>

<section>
  <button id="interrupteur" onclick="envoyer({allumee: etat.allumee ? 0 : 1})">…</button>
</section>

<section>
  <h2>Effets</h2>
  <div class="grille" id="effets"></div>
</section>

<section>
  <h2>Réglages</h2>
  <div class="ligne">Luminosité
    <input type="range" id="lum" min="5" max="255" onchange="envoyer({lum: this.value})">
  </div>
  <div class="ligne">Couleur unie
    <input type="color" id="couleur" onchange="envoyer({couleur: this.value.substring(1), effet: 0})">
  </div>
  <div class="ligne" id="ligneSens" hidden>Sensibilité du micro
    <input type="range" id="sens" min="1" max="20" onchange="envoyer({sens: this.value})">
  </div>
</section>

<section>
  <h2>Programmation</h2>
  <div class="ligne"><label><input type="checkbox" id="auto"> Allumer et éteindre tout seul</label></div>
  <div class="ligne">De <input type="time" id="debut"> à <input type="time" id="fin"></div>
  <button onclick="envoyer({auto: document.getElementById('auto').checked ? 1 : 0,
    debut: document.getElementById('debut').value, fin: document.getElementById('fin').value})">Enregistrer</button>
</section>

<script>
let etat = {};

async function envoyer(params) {
  const reponse = await fetch('/reglage?' + new URLSearchParams(params));
  afficher(await reponse.json());
}

function afficher(e) {
  etat = e;
  document.getElementById('heure').textContent = e.heure ? 'Heure de la guirlande : ' + e.heure : 'Heure pas encore reçue';
  const inter = document.getElementById('interrupteur');
  inter.textContent = e.allumee ? 'Éteindre' : 'Allumer';
  inter.className = e.allumee ? '' : 'actif';

  const zone = document.getElementById('effets');
  zone.innerHTML = '';
  e.effets.forEach((nom, i) => {
    const b = document.createElement('button');
    b.textContent = nom;
    if (i === e.effet) b.className = 'actif';
    b.onclick = () => envoyer({effet: i, allumee: 1});
    zone.appendChild(b);
  });

  document.getElementById('lum').value = e.lum;
  document.getElementById('couleur').value = '#' + e.couleur;
  if (e.sens !== undefined) {
    document.getElementById('ligneSens').hidden = false;
    document.getElementById('sens').value = e.sens;
  }
  document.getElementById('auto').checked = e.auto;
  document.getElementById('debut').value = e.debut;
  document.getElementById('fin').value = e.fin;
}

fetch('/etat').then(r => r.json()).then(afficher);
</script>
</body>
</html>
)rawliteral";

# Script détaillé : la guirlande de Noël connectée

Texte complet de la vidéo longue et des 5 Shorts, à lire en voix off. Les numéros de plans (P01, P02…) renvoient à la liste de plans de [plan-de-tournage.md](plan-de-tournage.md).

**Comment lire ce script**
- **À L'ÉCRAN** : les plans à monter sous la voix.
- **TEXTE** : ce qui s'affiche en surimpression.
- **VOIX** : le texte à lire. Il est écrit pour être dit, pas lu : change les mots qui ne te ressemblent pas, garde le rythme.
- `[pause]` : une respiration de 1 à 2 s où on laisse l'image et le son des LED parler.
- Débit visé : 150 mots par minute environ, soit une vidéo de 11 à 12 min.

---

## VIDÉO LONGUE

**Titre** : J'ai fabriqué une guirlande de Noël qui danse sur la musique (ESP32)
**Miniature** : sapin dans le noir, guirlande en plein flash multicolore, téléphone au premier plan, texte « ELLE DANSE ! » en gros.

### 0:00 · Accroche (20 s)

**À L'ÉCRAN** : P01 (sapin dans le noir, la musique démarre, la guirlande pulse sur les basses), puis P02 (doigt sur le téléphone, la guirlande change de couleur), puis P22 en accéléré (17 h, elle s'allume seule).
**TEXTE** : 40 €

**VOIX** :
> Cette guirlande danse sur la musique. [pause] Elle se pilote depuis mon téléphone, sans application à installer. Et tous les soirs à 17 heures, elle s'allume toute seule. [pause] Elle m'a coûté 40 euros, et à la fin de cette vidéo, tu sauras fabriquer la même.

### 0:20 · Le projet (25 s)

**À L'ÉCRAN** : P03 (les 3 étapes), musique de fond légère.
**TEXTE** : 1 · Les effets au bouton / 2 · Le téléphone / 3 · La musique

**VOIX** :
> Salut, c’est [ton prénom], et bienvenue sur Bidouille Connectée. Aujourd'hui, on fait ça en trois étapes. Un : des effets de Noël qu'on change avec un simple bouton. Deux : on pilote tout depuis le téléphone, avec une programmation horaire. Et trois : on ajoute un petit micro pour que la guirlande réagisse à la musique. Chaque étape marche toute seule, donc tu peux t'arrêter où tu veux. Tout le code est gratuit, le lien est en description.

### 0:45 · Le matériel (1 min 15)

**À L'ÉCRAN** : P04 (guirlande déroulée), P05 (macro d'une LED), P06 (pièces posées une à une). Chaque pièce s'affiche avec son prix.

**VOIX** :
> Commençons par la pièce principale : une guirlande de pixels WS2811. [pause] Vu de loin, ça ressemble à une guirlande normale. Mais regarde de près : dans chaque boule, il y a une petite puce. Ça veut dire qu'on peut donner une couleur différente à chacune des 50 LED, indépendamment des autres. Compte entre 12 et 20 euros.
>
> Attention à un piège : prends-la bien en **5 volts**. Elles existent aussi en 12 volts, et celles-là ne se branchent pas comme dans cette vidéo.
>
> Pour la piloter, un ESP32, la carte qu'on adore sur cette chaîne : Wi-Fi, Bluetooth, et 5 à 8 euros. Ensuite, une alimentation 5 volts 4 ampères, avec un petit adaptateur jack vers bornier à vis.
>
> Et puis trois petites pièces qui font toute la différence : un circuit 74AHCT125, je t'explique dans une minute à quoi il sert, un condensateur de 1000 microfarads et une résistance de 330 ohms. Ajoute un bouton poussoir, une plaque d'essai et un petit boîtier. Au total, entre 35 et 50 euros selon où tu achètes. La liste complète avec les liens est en description.

### 2:00 · Étape 1 : le câblage (1 min 30)

**À L'ÉCRAN** : P07 (câblage en accéléré, vue de dessus), P08 (le 74AHCT125 en gros plan), P09 (le bug sans le 74AHCT125, ou le multimètre 3,3 V / 5 V), P10 (le condensateur).
**TEXTE** : un schéma de câblage simplifié en incrustation, puis « 3,3 V ≠ 5 V » sur P09.

**VOIX** :
> On passe au câblage. L'alimentation 5 volts alimente trois choses en même temps : la guirlande, l'ESP32 par sa broche VIN, et notre petit circuit. Et toutes les masses sont reliées ensemble. C'est la règle numéro un avec les LED : si les masses ne sont pas communes, rien ne marche.
>
> Maintenant, ce fameux 74AHCT125. [pause] Le problème, c'est que l'ESP32 parle en 3,3 volts, alors que la guirlande attend un signal de 5 volts. Parfois ça passe quand même. Mais souvent, ça donne… ça. [pause sur P09] Des couleurs folles, des pixels qui clignotent. Ce circuit à un euro remonte simplement le signal à 5 volts. On entre sur la broche 2, on ressort sur la broche 3, et on passe par la résistance de 330 ohms avant d'aller sur le fil de données de la guirlande.
>
> Dernier détail : le condensateur, entre le plus et le moins, au départ de la guirlande. Il amortit le pic de courant à l'allumage. Respecte bien le sens : la patte marquée « moins » va sur le moins.
>
> Et vérifie le sens de la guirlande : le signal n'entre que d'un côté. Cherche une petite flèche ou l'inscription « DIN ». C'est en général le connecteur femelle.

### 3:30 · Étape 1 : le code et les 8 effets (1 min 30)

**À L'ÉCRAN** : P11 (`effets.h` dans VS Code), P12 (téléversement), P13 (premier allumage doré), P14 (les 8 effets au bouton), P15 (extinction en fondu).
**TEXTE** : le nom de chaque effet quand il apparaît.

**VOIX** :
> Côté code, j'utilise PlatformIO et la bibliothèque FastLED. Tout ce qui est réglable est en haut du fichier : le nombre de LED, le type de guirlande, la luminosité. Et il y a une sécurité importante : une limite de courant. 50 LED en blanc à fond, c'est jusqu'à 3 ampères. Le code bride à 2,5 ampères pour ne jamais dépasser ce que l'alimentation peut fournir.
>
> Petite astuce au téléversement : débranche le fil 5 volts qui va sur VIN et garde juste la masse. Comme ça, l'USB de l'ordinateur et l'alimentation ne se battent pas.
>
> On téléverse… [pause] et voilà le premier allumage. Un scintillement doré. [pause]
>
> Un appui sur le bouton, et on passe à l'effet suivant. Il y en a huit : le blanc chaud, comme une guirlande classique ; le scintillement doré ; le sucre d'orge, des rayures rouges et blanches qui défilent ; l'arc-en-ciel ; les bougies, où chaque LED vacille comme une flamme ; la neige, avec des flocons qui apparaissent et fondent sur une nuit bleue ; le rouge et vert qui respire ; et les confettis. [pause] Et un appui long d'une seconde éteint la guirlande en fondu.

### 5:00 · Créer son propre effet (1 min)

**À L'ÉCRAN** : P16 (modification d'un effet en direct dans le code), P17 (le nouvel effet s'affiche).

**VOIX** :
> Ce que j'aime dans ce projet, c'est que tous les effets sont dans un seul fichier, effets point h, avec une fonction par effet. Chaque fonction dessine une image, et elle est appelée 60 fois par seconde. Donc pour créer ton effet, tu copies une fonction et tu changes les couleurs.
>
> Allez, on essaie en direct. Je prends le sucre d'orge, et au lieu du rouge et du blanc, je mets [tes couleurs : celles de ton équipe, de ton pays, de ta moto]. On téléverse… [pause] et voilà. Dix secondes de modification, et j'ai une guirlande à mes couleurs. Si tu crées un effet sympa, montre-le-moi en commentaire, je mettrai les meilleurs dans le code.

### 6:00 · Étape 2 : le téléphone (2 min)

**À L'ÉCRAN** : P18 (la page guirlande.local s'ouvre), P19 (curseur de luminosité, la guirlande suit), P20 (nuancier), P21 (réglage de l'heure), P22 (17 h, la guirlande s'allume seule).
**TEXTE** : http://guirlande.local

**VOIX** :
> Étape deux : on se débarrasse du bouton. Et bonne nouvelle, il n'y a rien à acheter, ni à câbler. Tout se passe dans le code. [pause]
>
> On met le nom et le mot de passe du Wi-Fi dans le fichier config point h, on téléverse, et la guirlande crée sa propre page web. Sur le téléphone, j'ouvre l'adresse guirlande point local… et voilà ma télécommande. [pause]
>
> Je peux choisir l'effet, choisir une couleur… et régler la luminosité. Regarde, la guirlande suit le curseur en direct. [pause sur P19]
>
> Petite astuce : dans le navigateur, « Ajouter à l'écran d'accueil ». Et là, tu as une vraie icône, comme une appli. Sauf qu'il n'y a rien à installer, pas de compte, pas d'abonnement, et aucune donnée qui part sur un serveur à l'autre bout du monde.
>
> Et le meilleur : la programmation. Je coche « Allumer et éteindre tout seul », je choisis 17 heures et 23 heures 30, et j'enregistre. L'ESP32 récupère l'heure sur Internet tout seul. [pause sur P22] Et à 17 heures pile… elle s'allume toute seule.
>
> Les réglages restent en mémoire même après une coupure de courant. Et le bouton de l'étape un marche toujours, même si le Wi-Fi tombe.
>
> Si l'adresse guirlande point local ne s'ouvre pas sur ton téléphone, ça arrive sur certains Android, utilise l'adresse IP affichée dans le moniteur série. Et n'oublie pas : l'ESP32 ne voit que le Wi-Fi 2,4 gigahertz.

### 8:00 · Étape 3 : la musique (2 min)

**À L'ÉCRAN** : P23 (micro à côté d'une pièce), P24 (câblage du micro), P28 (moniteur série), P25 (VU-mètre), P26 (flash sur les basses), P27 (étincelles).
**TEXTE** : INMP441 · 3 € ; puis le nom de chaque effet musical.

**VOIX** :
> Et maintenant, la partie que je préfère. [pause] Ce minuscule module, c'est un micro numérique, l'INMP441. Environ 3 euros. Six fils à brancher, et attention : on l'alimente en 3,3 volts, surtout pas en 5.
>
> Le micro écoute le son 16 000 fois par seconde. Le code en tire deux informations : le volume global, et l'énergie des graves, tout ce qui est en dessous de 150 hertz environ. Quand les graves dépassent d'un coup leur moyenne, c'est un coup de grosse caisse. [pause]
>
> Ça donne trois nouveaux effets. Le VU-mètre : la guirlande se remplit depuis le milieu, du vert au rouge, selon le volume. [pause sur P25] La pulsation : toute la guirlande flashe sur chaque coup de basse, avec une nouvelle couleur à chaque fois. [laisser 4-5 s sur P26] Et les étincelles : plus c'est fort, plus il y a de points de couleur, avec une gerbe dorée sur chaque coup. [pause sur P27]
>
> Le gain s'adapte tout seul au volume de la pièce. Donc ça marche aussi bien sur un chant de Noël tout doux… que sur du métal. Et si ça ne réagit pas assez, il y a un curseur « Sensibilité » sur la page du téléphone.

### 10:00 · Installation (30 s)

**À L'ÉCRAN** : P29 (montage dans le boîtier), P30 (installation sur le sapin en accéléré).

**VOIX** :
> Il ne reste plus qu'à tout ranger dans le boîtier. Un conseil : place le micro face à un trou, et loin de l'alimentation, qui peut bourdonner. Et si tu passes à plus de 100 LED, ramène un second fil plus et moins jusqu'au bout de la guirlande, sinon les dernières LED tirent sur le jaune.

### 10:30 · Démo finale (40 s)

**À L'ÉCRAN** : P31 (plan large, lumière éteinte, musique), P32 (reflets dans les boules). Musique libre de droits plein volume.

**VOIX** :
> Allez, on éteint la lumière. [ne plus parler pendant 20 à 30 s, laisser la musique et la guirlande]

### 11:10 · Fin (30 s)

**À L'ÉCRAN** : P33 (aperçu de l'étoile de sapin ou d'une seconde guirlande), puis écran de fin YouTube (vidéo suivante + abonnement).

**VOIX** :
> Et ce n'est pas fini. J'ai déjà des idées pour la suite : une étoile en haut du sapin qui a son propre effet, plusieurs guirlandes dans la maison qui dansent en même temps, et un compte à rebours spécial pour le 24 décembre à minuit. Dis-moi en commentaire laquelle tu veux voir en premier.
>
> Tout le code et la liste du matériel sont en description. Si la vidéo t'a plu, abonne-toi pour la suite. Allez, à la prochaine, et joyeux Noël en avance !

### Description YouTube (à coller)

```
Une guirlande de Noël qui danse sur la musique, se pilote du téléphone et s'allume toute seule, avec un ESP32 et ~40 €.

💻 Code complet (gratuit) : https://github.com/Meudo31/ESP32-Guirlande-Noel
🛒 Liste du matériel : dans le README du dépôt

⏱️ Chapitres
0:00 Le résultat
0:20 Le projet en 3 étapes
0:45 Le matériel
2:00 Étape 1 : le câblage
3:30 Étape 1 : les 8 effets
5:00 Créer son propre effet
6:00 Étape 2 : piloter depuis le téléphone
8:00 Étape 3 : la guirlande danse sur la musique
10:00 Installation
10:30 Démo finale
11:10 Et ensuite ?

#ESP32 #Noël #DIY #FastLED #Domotique
```

Mets à jour les minutages au montage : YouTube exige que le premier chapitre soit à 0:00 et qu'il y en ait au moins trois.

---

## LES 5 SHORTS

Format : 9:16, 30 à 60 s, sous-titres incrustés (CapCut), musique libre de droits. Chaque Short est relié à la longue par la fonction « Vidéo associée ».

### S1 · « Ma guirlande de Noël danse sur la musique » (35 s)

| Temps | À l'écran | Voix | Texte |
| --- | --- | --- | --- |
| 0-2 s | P01 vertical, en plein flash | « Ma guirlande de Noël danse sur la musique. » | ELLE DANSE 🎄 |
| 2-10 s | P26 vertical | « Chaque coup de basse, elle flashe dans une nouvelle couleur. » | |
| 10-18 s | P23 (micro à côté d'une pièce) | « Le secret ? Un micro à 3 euros et un ESP32. » | INMP441 · 3 € |
| 18-30 s | P31 vertical | [musique seule] | |
| 30-35 s | P02 vertical | « Le tuto complet est dans la vidéo associée. » | Tuto complet ⬇️ |

### S2 · « 8 effets de Noël, un seul bouton » (25 s)

| Temps | À l'écran | Voix | Texte |
| --- | --- | --- | --- |
| 0-2 s | P13 vertical (premier allumage) | « 8 effets de Noël. Un seul bouton. » | 8 EFFETS · 1 BOUTON |
| 2-22 s | P14 vertical : chaque effet 2,5 s, coupe sur le temps de la musique, gros plan du doigt sur le bouton entre deux | [musique seule] | Nom de chaque effet : Blanc chaud, Scintillement, Sucre d'orge, Arc-en-ciel, Bougies, Neige, Rouge & vert, Confettis |
| 22-25 s | Retour au scintillement doré | « Lequel tu gardes ? » | Lequel tu gardes ? 👇 |

Ce Short court est fait pour tourner en boucle : la fin doit raccorder avec le début (même effet doré). La question finale pousse aux commentaires.

### S3 · « Je pilote ma guirlande depuis mon téléphone, sans appli » (40 s)

| Temps | À l'écran | Voix | Texte |
| --- | --- | --- | --- |
| 0-3 s | P02 vertical | « Je pilote ma guirlande depuis mon téléphone. Sans appli. » | SANS APPLI 📱 |
| 3-12 s | P18 (page guirlande.local) | « C'est la guirlande elle-même qui crée cette page web. Un ESP32, et c'est tout. » | guirlande.local |
| 12-22 s | P19 vertical | « Luminosité… [pause] couleur… [pause] effet. » | |
| 22-32 s | P21 puis P22 | « Et je l'ai programmée : tous les soirs à 17 heures, elle s'allume toute seule. » | 17:00 ⏰ |
| 32-40 s | P31 | « Pas de compte, pas d'abonnement. Le tuto est dans la vidéo associée. » | Tuto complet ⬇️ |

### S4 · « Ta guirlande fait n'importe quoi ? Voici la pièce à 1 € qui manque » (40 s)

| Temps | À l'écran | Voix | Texte |
| --- | --- | --- | --- |
| 0-3 s | P09 vertical (pixels fous) | « Ta guirlande LED fait n'importe quoi ? » | 😵 BUG ? |
| 3-12 s | P09, multimètre | « Ton ESP32 envoie un signal de 3,3 volts. Ta guirlande, elle, attend du 5 volts. Parfois ça passe… souvent non. » | 3,3 V ≠ 5 V |
| 12-25 s | P08 | « La solution : ce circuit à un euro, le 74AHCT125. Il remonte le signal à 5 volts, proprement. » | 74AHCT125 · 1 € |
| 25-35 s | P13 vertical | « Et voilà. Plus un seul pixel qui clignote. » | ✅ |
| 35-40 s | P14 | « Tout le câblage est dans la vidéo associée. » | Tuto complet ⬇️ |

Short pédagogique : mets « 74AHCT125 », « WS2811 » et « ESP32 » dans le titre et la description, ce sont des mots recherchés.

### S5 · « Elle s'allume toute seule à 17 h » (30 s)

| Temps | À l'écran | Voix | Texte |
| --- | --- | --- | --- |
| 0-3 s | P22 vertical : 16:59, fenêtre éteinte | « Regarde l'heure. » | 16:59 |
| 3-8 s | P22 : 17:00, la guirlande s'allume | [silence, juste le son de la pièce] | 17:00 ✨ |
| 8-20 s | P21 | « Je l'ai programmée depuis mon téléphone. Elle prend l'heure sur Internet, s'allume à 17 heures et s'éteint à 23 heures 30. Toute seule, tous les soirs. » | |
| 20-30 s | P31 | « Un ESP32 et 40 euros. Le tuto est dans la vidéo associée. » | Tuto complet ⬇️ |

**Variante de S5** si tu as tourné P16-P17 : « Ma guirlande aux couleurs de [ton équipe] ». Voix : « J'ai codé ma guirlande aux couleurs de [ton équipe]. Dix secondes de code, regarde. » Puis P16, P17 et la question « Quelles couleurs tu mettrais ? ».

---

## Avant d'enregistrer la voix

- Lis le script à voix haute une fois sans enregistrer, en barrant les phrases qui accrochent.
- Enregistre section par section, 2 ou 3 prises de chacune ; garde la meilleure au montage.
- Sourire en parlant s'entend : surtout sur l'accroche et la fin.
- Si un effet ou une fonction change pendant la mise au point (vitesse, nom, couleur), adapte la phrase correspondante avant d'enregistrer.

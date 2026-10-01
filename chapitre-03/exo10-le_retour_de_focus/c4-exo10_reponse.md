# Exo 10 : Le retour de focus

## Ce que j'ai fait

Je pars de l'accumulateur de l'exo 9 : le rappel sur `NkMouseRawEvent`
ajoute les déplacements dans `accX` et `accY`, et la boucle consomme le
total une fois par image, juste après `PollEvents()`, puis remet
l'accumulateur à zéro.

J'ai ajouté deux rappels, `NkWindowFocusLostEvent` et
`NkWindowFocusGainedEvent`, qui mettent à jour un booléen `aLeFocus`.
Un interrupteur `REMISE_A_ZERO_SANS_FOCUS` décide si l'accumulateur est
remis à zéro quand la fenêtre n'a pas le focus :

- **Version A** : `REMISE_A_ZERO_SANS_FOCUS = true` (avec remise à zéro)
- **Version B** : `REMISE_A_ZERO_SANS_FOCUS = false` (sans)

Chaque image est écrite dans `serie.txt` (copiée en `serie_A.txt` et
`serie_B.txt`) avec quatre valeurs : `focus`, `brut` (valeur fournie par
le kit), `acc` (total consommé par mon accumulateur) et `evts` (nombre de
`NkMouseRawEvent` reçus pendant l'image).

Gestes, identiques dans les deux essais : clic dans la fenêtre, souris
pendant 3 secondes, clic ailleurs, souris pendant dix secondes, retour
dans la fenêtre, quelques mouvements, puis Échap.

## Résultats mesurés

| | Version A (avec remise à zéro) | Version B (sans) |
|---|---|---|
| Images au total | 1991 | 947 |
| Images sans focus | 611 | 416 |
| Sans focus, avec événements bruts | 300 | non relevé |
| Sans focus, avec `acc` non nul | 0 | 301 |
| `brut` au retour du focus | 1 puis 0 | 1 puis 0 |

Retour de focus, version A :

```
1500 : focus=0 brut=1 acc=0 evts=0
1501 : focus=1 brut=0 acc=0 evts=1
```

Retour de focus, version B :

```
778 : focus=0 brut=1 acc=1 evts=1
779 : focus=1 brut=0 acc=0 evts=1
```

Premières images sans focus avec `acc` non nul, version B :

```
382 : focus=0 brut=-3 acc=-3 evts=4
383 : focus=0 brut=-1 acc=-4 evts=2
384 : focus=0 brut=-5 acc=-17 evts=4
385 : focus=0 brut=-5 acc=-9 evts=2
386 : focus=0 brut=-4 acc=-18 evts=4
```

## Ce que j'observe

1. Le kit livre des `NkMouseRawEvent` même quand la fenêtre n'a pas le
   focus : 300 images sur 611 en version A. Ces événements portent de
   vrais déplacements : en version B, `acc` atteint -17 et -18 sur des
   images sans focus.
2. Avec la remise à zéro (A), ces déplacements n'atteignent jamais
   l'accumulateur (`acc=0` sur toutes les images sans focus). Sans elle
   (B), 301 images sans focus ont un `acc` non nul : la souris bougée
   dans une autre fenêtre fait tourner la vue de celle-ci.
3. Dans les deux versions, `brut` repasse à 0 au retour du focus, et
   `acc` ne reçoit pas de gros total à ce moment-là, car la boucle
   consomme l'accumulateur à chaque image.
4. Sans événement, `brut` reste figé à 1 pendant tout le temps sans
   focus (images 1496 à 1500 en A, 774 à 778 en B), alors que `acc`
   retombe à 0. Cela confirme le défaut décrit dans le chapitre : la
   variable du kit n'est jamais remise à zéro, d'où l'accumulateur
   personnel.


*Limites : un seul essai par version, fait à la main.*
# Exo 7 : Le pointeur caché

## Ce que j'ai fait

J'ai caché le curseur avec `fenetre.ShowMouse(false)` et je l'ai confiné dans la zone client avec `fenetre.ClipMouseToClient(true)`. À chaque image (pause de 16 ms par tour), j'affiche quatre valeurs :

- la position : `NkInput.MouseX()` et `NkInput.MouseY()`
- le delta brut : `NkInput.MouseRawDeltaX()` et `NkInput.MouseRawDeltaY()`

Avant de quitter, je rends la souris au système avec `ClipMouseToClient(false)` et `ShowMouse(true)`. Le header du kit prévient que le confinement survit au programme s'il n'est pas relâché.

Test : j'ai poussé la souris contre chaque bord (gauche, droite, haut, bas) et dans les coins, en continuant à bouger après avoir touché le bord. J'ai fait deux essais.

## Les deux séries au bord

Format : `x y | rawDX rawDY`

**Bord gauche** (essai 1) : `x` s'arrête à 0, `rawDX` continue.

```
x=66  y=398 | rawDX=-4  rawDY=-3
x=39  y=381 | rawDX=-7  rawDY=-4
x=14  y=360 | rawDX=-5  rawDY=-5
x=0   y=341 | rawDX=-3  rawDY=-4
x=0   y=325 | rawDX=-5  rawDY=-1
x=0   y=321 | rawDX=-19 rawDY=0
x=0   y=319 | rawDX=-18 rawDY=0
x=0   y=314 | rawDX=-6  rawDY=-1
```

**Coin haut-gauche** (essai 1) : `x` et `y` sont bloqués à 0, `rawDY` continue.

```
x=0 y=168 | rawDX=-4 rawDY=-26
x=0 y=0   | rawDX=-2 rawDY=-30
x=0 y=0   | rawDX=-3 rawDY=-26
x=0 y=0   | rawDX=-2 rawDY=-20
x=0 y=0   | rawDX=-3 rawDY=-19
x=0 y=0   | rawDX=-2 rawDY=-13
x=0 y=0   | rawDX=-2 rawDY=-8
x=0 y=0   | rawDX=0  rawDY=-4
```

**Coin bas-droit** (essai 1) : `x` bloqué à 1193 et `y` à 702, les deux deltas continuent.

```
x=725  y=607 | rawDX=38 rawDY=10
x=1168 y=702 | rawDX=44 rawDY=11
x=1193 y=702 | rawDX=30 rawDY=18
x=1193 y=702 | rawDX=17 rawDY=27
x=1193 y=702 | rawDX=5  rawDY=38
x=1193 y=702 | rawDX=2  rawDY=39
```

**Bord droit** (essai 2) : `x` reste à 1193 avec `rawDX` positif.

```
x=1148 y=653 | rawDX=6 rawDY=-1
x=1193 y=643 | rawDX=8 rawDY=-2
x=1193 y=621 | rawDX=6 rawDY=-5
x=1193 y=592 | rawDX=6 rawDY=-4
x=1193 y=570 | rawDX=3 rawDY=-5
```

## Ce que je constate

- **La position (x, y) s'arrête.** Sur l'ensemble du test, `x` va de 0 à 1193 et `y` de 0 à 702 (zone d'environ 1194 x 703). Elle n'en sort jamais, et au bord elle reste figée même si la main continue de bouger. La position est bornée par le confinement.
- **Le rawDelta continue de bouger.** Contre le bord, `rawDX` vaut -19 puis -18 avec `x=0`, et `rawDY` descend de -30 à -4 dans le coin. Il continue d'indiquer dans quelle direction et de combien la souris bouge.

## Pourquoi c'est le rawDelta qu'il faut

Quand le curseur est caché et confiné, on se sert de la souris pour bouger une caméra ou viser (jeu à la première personne), et non pour pointer quelque chose à l'écran. Il faut alors pouvoir tourner sans fin dans le même sens.

- **La position perd l'information au bord.** Dans le coin, `x=0 y=0` ne dit plus rien : je ne peux pas savoir si la main a bougé de 2 ou de 30 unités. Avec la position, la caméra s'arrêterait de tourner dès que le curseur touche le bord.
- **Le rawDelta décrit le mouvement de la souris, pas un endroit de l'écran.** Il est le même qu'on soit au milieu de la fenêtre ou contre le bord, donc la caméra peut tourner sans limite.
- **Le kit fait le même choix dans sa propre documentation.** Les exemples du header de `NkEventDispatcher.h` calculent la rotation de la caméra avec `NkInput.MouseRawDeltaX()` et `MouseRawDeltaY()`, pas avec `MouseX()`.

La position reste utile pour tout ce qui vise un endroit de l'écran (menus, boutons, clics). Le choix dépend de ce qu'on veut : un endroit ou un mouvement.

## Observations que je n'ai pas expliquées

- **Le rawDelta ne revient pas toujours à 0 quand la souris s'arrête.** Il reste parfois bloqué à ±1 : `x=1193 y=123 | rawDX=0 rawDY=1` se répète sur plus de cent images, alors que la souris ne bouge plus. Ailleurs, au repos, j'obtiens bien `rawDX=0 rawDY=0`. Je pense que la dernière valeur est conservée quand aucun nouvel événement n'arrive, mais je ne l'ai pas vérifié. Conséquence possible : si on additionne le delta image après image, ces ±1 créeraient une dérive lente.
- **Le déplacement en pixels n'est pas proportionnel au rawDelta.** Un `rawDX` de 44 donne un saut de 443 pixels (de 725 à 1168), un `rawDX` de 23 un saut de 180 pixels. Ça ressemble à l'accélération du pointeur de Windows, qui s'applique à la position mais pas au delta brut. C'est une hypothèse, pas une mesure.

*Limites : deux essais faits à la main. Les valeurs exactes changent à chaque essai, mais le comportement (position figée au bord, delta qui continue) s'est reproduit à chaque bord.*
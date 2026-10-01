# Exo 8 : Le défaut, reproduit

## Ce que j'ai fait

À chaque image (pause de 16 ms par tour), j'affiche `NkInput.MouseRawDeltaX()` et rien d'autre. Je n'accumule rien moi-même : la valeur lue est celle que le kit fournit.

Test : je clique sur la fenêtre, je bouge la souris de gauche à droite pendant quelques secondes, puis je pose la main sur la table sans plus y toucher, jusqu'à ce que j'appuie sur Échap. Le programme a tourné 558 images.

## Les vingt lignes qui suivent l'arrêt

Juste avant l'arrêt, le mouvement se termine ainsi : image 308 : `rawDX=2`, image 309 : `rawDX=1`. À partir de l'image 310, la valeur ne bouge plus. Voici les vingt images 310 à 329 :

```
image 310 : rawDX=-1
image 311 : rawDX=-1
image 312 : rawDX=-1
image 313 : rawDX=-1
image 314 : rawDX=-1
image 315 : rawDX=-1
image 316 : rawDX=-1
image 317 : rawDX=-1
image 318 : rawDX=-1
image 319 : rawDX=-1
image 320 : rawDX=-1
image 321 : rawDX=-1
image 322 : rawDX=-1
image 323 : rawDX=-1
image 324 : rawDX=-1
image 325 : rawDX=-1
image 326 : rawDX=-1
image 327 : rawDX=-1
image 328 : rawDX=-1
image 329 : rawDX=-1
```

Cela ne s'arrête pas là : les images 330 à 558 (229 images de plus) affichent aussi `rawDX=-1`. Au total, la valeur reste à -1 pendant 249 images, soit au moins 4 secondes, jusqu'à ce que je ferme le programme.

## Ce que ces lignes prouvent

Quand la main s'arrête, `rawDeltaX` ne revient pas à 0 : il reste figé à -1 à chaque image, de sorte qu'un programme qui l'additionnerait image après image verrait sa valeur dériver sans fin (ici de -249 unités en 249 images).

## Observations complémentaires

- **Le défaut n'est pas systématique.** À d'autres moments du même test, la valeur est retombée à 0 : après un arrêt à l'image 128, elle est restée à -1 pendant 12 images (129 à 140), puis est passée à 0 pour 32 images (141 à 172). Après d'autres arrêts, elle est restée à 1 pendant 12 images (95 à 106). Le défaut apparaît donc à certains arrêts et pas à d'autres.
- **La valeur figée n'est pas un vrai mouvement.** À l'exo 7, `y` restait à 123 pendant que `rawDY` valait 1 sur plus de cent images. La position ne changeait pas, donc le delta ne décrivait pas un déplacement réel.
- **Hypothèse (non vérifiée, je n'ai pas lu le code du kit).** Quand plus aucun événement de souris n'arrive, le kit ne remettrait pas le delta à zéro : il garderait la dernière valeur reçue. Cela expliquerait qu'elle reste identique pendant des centaines d'images.
- **Conséquence pratique.** Il ne faut pas faire confiance à `MouseRawDeltaX()` comme à un « mouvement depuis la dernière image » sans précaution : par exemple l'accumuler tel quel pour une caméra ferait tourner la vue toute seule après l'arrêt de la main.

*Limites : un seul essai à la main. La valeur figée (-1 ici, +1 ou +2 ailleurs) et la durée varient d'un essai à l'autre. C'est le comportement (valeur non nulle qui persiste sans mouvement) qui compte.*
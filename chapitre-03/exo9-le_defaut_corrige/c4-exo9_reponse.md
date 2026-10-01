# Exo 9 : Le défaut, corrigé

## Ce que j'ai fait

J'ai écrit l'accumulateur en deux parties.

- **Le rappel** sur `NkMouseRawEvent` (abonné avec `AddEventCallbackGuard`) ajoute à deux totaux : `accX += ev->GetDeltaX()` et `accY += ev->GetDeltaY()`. Il compte aussi les événements reçus.
- **La consommation**, une fois par image juste après `PollEvents()` : je copie le total dans une variable, puis je remets l'accumulateur à zéro.

À chaque image (pause de 16 ms par tour), j'écris dans un fichier trois valeurs :

- `brut` : `NkInput.MouseRawDeltaX()`, la valeur fournie par le kit, comme à l'exo 8
- `acc` : le total X consommé par mon accumulateur
- `evts` : le nombre de `NkMouseRawEvent` reçus pendant cette image

Test : le même qu'à l'exo 8. Je clique sur la fenêtre, je bouge la souris de gauche à droite, puis je pose la main sans plus y toucher jusqu'à Échap.

## Bilan de l'essai

- 687 images
- 749 événements `NkMouseRawEvent` reçus (donc plus d'événements que d'images : plusieurs arrivent dans la même image et mon accumulateur les additionne)
- somme des totaux consommés sur X : 935

## Les deux séries côte à côte

Le dernier événement reçu est à l'image 394. Voici les dix images avant et les vingt images qui suivent l'arrêt (395 à 414).

```
image | brut | acc | evts
 385  |  0   |  0  |  1
 386  |  0   |  0  |  1
 387  |  0   |  0  |  2
 388  |  0   |  0  |  1
 389  |  0   |  0  |  1
 390  |  0   |  0  |  2
 391  |  0   |  1  |  2
 392  |  2   |  2  |  2
 393  |  0   |  0  |  1
 394  |  1   |  1  |  1     <- dernier événement reçu
 395  |  1   |  0  |  0
 396  |  1   |  0  |  0
 397  |  1   |  0  |  0
 398  |  1   |  0  |  0
 399  |  1   |  0  |  0
 400  |  1   |  0  |  0
 401  |  1   |  0  |  0
 402  |  1   |  0  |  0
 403  |  1   |  0  |  0
 404  |  1   |  0  |  0
 405  |  1   |  0  |  0
 406  |  1   |  0  |  0
 407  |  1   |  0  |  0
 408  |  1   |  0  |  0
 409  |  1   |  0  |  0
 410  |  1   |  0  |  0
 411  |  1   |  0  |  0
 412  |  1   |  0  |  0
 413  |  1   |  0  |  0
 414  |  1   |  0  |  0
```

Cela ne s'arrête pas à l'image 414 : jusqu'à la fin du programme (image 687), toutes les lignes sont `brut=1 acc=0 evts=0`. Soit 293 images de suite (395 à 687), au moins 4,7 secondes.

## Ce que je constate

- **La valeur du kit ne retombe pas à 0.** Après l'arrêt, `brut` reste à 1 pendant 293 images alors qu'aucun événement n'arrive (`evts=0` à chaque image).
- **Mon accumulateur retombe à 0.** Dès l'image 395, `acc=0`, et il y reste : une image sans événement apporte un total nul, donc pas de mouvement.
- **La dérive, chiffrée.** Si j'additionnais `brut` image après image, je gagnerais +1 à chaque image sans mouvement : +293 entre les images 395 et 687. Avec `acc`, la dérive est de 0.
- **Conclusion.** `acc` mesure bien ce qui s'est passé depuis la dernière image, alors que `brut` garde une valeur périmée. C'est cet accumulateur qu'il faut brancher sur une caméra.

## Observations que je n'ai pas expliquées

- **Image 391 : `brut=0` mais `acc=1`** (avec 2 événements reçus). Le kit et l'accumulateur ne donnent pas la même valeur pendant le mouvement. Aux images 392 et 394, ils sont d'accord (2 et 2, 1 et 1). Je n'ai pas d'explication vérifiée.
- **Images 385 à 390 : des événements arrivent mais `acc=0`.** Mon accumulateur ne suit que l'axe X : ces événements ne bougent peut-être que sur Y, ou leur delta X est nul. Je n'ai pas vérifié.
- **Hypothèse (non vérifiée, je n'ai pas lu le code du kit).** Quand plus aucun événement n'arrive, le kit garde la dernière valeur lue au lieu de la remettre à zéro. Les chiffres vont dans ce sens (valeur identique, aucun événement), mais ils ne prouvent pas le mécanisme.
- **Fil d'exécution.** Mon accumulateur n'a pas de verrou. Je suppose que le rappel est appelé dans `PollEvents()`, donc dans le même fil que la boucle. Les résultats sont cohérents avec cela (`acc` non nul seulement quand `evts` l'est aussi), mais je ne l'ai pas vérifié dans le kit.

*Limites : un seul essai à la main, avec une seule série d'arrêt exploitée (la dernière). Les valeurs exactes changent d'un essai à l'autre.*
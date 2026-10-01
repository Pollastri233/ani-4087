# Exo 5 : La taille qui change

## Ce que j'ai fait

J'écoute `NkWindowResizeEvent` avec `AddEventCallbackGuard`. À chaque événement, j'incrémente un compteur et j'affiche la nouvelle taille avec `NK_FOUNDATION_LOG_INFO("#%d : %u x %u", ...)`, à partir de `GetWidth()` et `GetHeight()`. Le programme se ferme avec la croix ou la touche Échap. Les messages apparaissent bien dans PowerShell.

J'ai fait deux essais : un redimensionnement lent (je tire doucement sur un bord pendant quelques secondes) et un redimensionnement brusque (je tire vite sur le bord, avec des allers-retours).

## Série 1 : redimensionnement lent (32 événements)

Format : `numéro : largeur x hauteur`

```
1 : 1218 x 759    2 : 1196 x 703    3 : 1220 x 759    4 : 1198 x 703
5 : 1226 x 759    6 : 1204 x 703    7 : 1228 x 759    8 : 1206 x 703
9 : 1230 x 759   10 : 1208 x 703   11 : 1232 x 759   12 : 1210 x 703
13 : 1236 x 759  14 : 1214 x 703   15 : 1241 x 759   16 : 1219 x 703
17 : 1243 x 759  18 : 1221 x 703   19 : 1247 x 759   20 : 1225 x 703
21 : 1249 x 759  22 : 1227 x 703   23 : 1251 x 759   24 : 1229 x 703
25 : 1253 x 759  26 : 1231 x 703   27 : 1254 x 759   28 : 1232 x 703
29 : 1256 x 759  30 : 1234 x 703   31 : 1257 x 759   32 : 1235 x 703
```

**Ce que j'observe :**

- La hauteur ne change pas (759 et 703). Seule la largeur varie.
- La largeur monte régulièrement, de 1218 à 1257, soit 39 pixels en tout.
- D'un événement à l'autre, la taille change de très peu : 2 à 6 pixels. Le glissement est découpé en toutes petites étapes, et l'allure est une courbe lisse et progressive.
- Il n'y a aucune répétition : chaque événement apporte une taille nouvelle.

## Série 2 : redimensionnement brusque (208 événements)

```
1 : 1219 x 759    2 : 1197 x 703    3 : 1247 x 759    4 : 1225 x 703
5 : 1258 x 759    6 : 1236 x 703    7 : 1288 x 759    8 : 1266 x 703
9 : 1306 x 759   10 : 1284 x 703   11 : 1316 x 759   12 : 1294 x 703
13 : 1370 x 759  14 : 1348 x 703   15 : 1413 x 759   16 : 1391 x 703
17 : 1453 x 759  18 : 1431 x 703   19 : 1486 x 759   20 : 1464 x 703
21 : 1499 x 759  22 : 1477 x 703   23 : 1503 x 759   24 : 1481 x 703
25 : 1506 x 759  26 : 1484 x 703   27 : 1511 x 759   28 : 1489 x 703
29 : 1514 x 759  30 : 1492 x 703   31 : 1527 x 759   32 : 1505 x 703
33 : 1532 x 759  34 : 1510 x 703   35 : 1542 x 759   36 : 1520 x 703
37 : 1542 x 759  38 : 1540 x 759   39 : 1518 x 703   40 : 1521 x 759
41 : 1499 x 703  42 : 1493 x 759   43 : 1471 x 703   44 : 1432 x 759
45 : 1410 x 703  46 : 1395 x 759   47 : 1373 x 703   48 : 1365 x 759
49 : 1343 x 703  50 : 1361 x 759   51 : 1339 x 703   52 : 1365 x 759
53 : 1343 x 703  54 : 1367 x 759   55 : 1345 x 703   56 : 1369 x 759
57 : 1347 x 703  58 : 1371 x 759   59 : 1349 x 703   60 : 1375 x 759
61 : 1353 x 703  62 : 1397 x 759   63 : 1375 x 703   64 : 1419 x 759
65 : 1397 x 703  66 : 1442 x 759   67 : 1420 x 703   68 : 1459 x 759
69 : 1437 x 703  70 : 1471 x 759   71 : 1449 x 703   72 : 1484 x 759
73 : 1462 x 703  74 : 1509 x 759   75 : 1487 x 703   76 : 1537 x 759
77 : 1515 x 703  78 : 1555 x 759   79 : 1533 x 703   80 : 1563 x 759
81 : 1541 x 703  82 : 1569 x 759   83 : 1547 x 703   84 : 1574 x 759
85 : 1552 x 703  86 : 1575 x 759   87 : 1553 x 703
88 à 208 : 1575 x 759   (121 événements identiques)
```

**Ce que j'observe :**

- La largeur varie beaucoup plus : elle monte jusqu'à 1542, redescend jusqu'à 1339, puis remonte jusqu'à 1575. C'est un geste rapide avec un aller-retour.
- Les écarts entre deux événements sont grands : 28, 30, 54, 43, 40 pixels contre 2 à 6 en lent. La courbe est en escalier, avec des sauts.
- Une fois la taille stabilisée à 1575 x 759, le programme reçoit encore 121 événements (de #88 à #208), tous avec exactement la même taille. Aucune nouvelle taille n'est arrivée, mais l'événement est quand même envoyé.
- Il y a quelques irrégularités, par exemple #37 (1542) puis #38 (1540), qui rompent l'alternance habituelle.

## Un motif commun aux deux séries

Dans les deux séries, les valeurs alternent : les événements impairs ont une hauteur de 759, les pairs une hauteur de 703, avec un écart constant d'environ 22 pixels en largeur et 56 en hauteur.

**Hypothèse (non vérifiée, je n'ai pas lu le code du kit)** : à chaque cran, le kit enverrait deux événements, l'un avec la taille de la fenêtre entière (bordures et barre de titre comprises) et l'autre avec la taille de la zone intérieure. Les écarts constants vont dans ce sens, mais je n'ai pas de preuve.

## Conclusion sur le nombre d'événements reçus

1. **Le nombre d'événements ne correspond pas au nombre de tailles différentes.** En lent, 32 événements pour 39 pixels de variation. En brusque, 208 événements, dont 121 qui répètent la même taille.
2. **Il dépend du geste et de sa durée**, pas de la taille finale. Plus on reste longtemps en train de tenir le bord, plus on reçoit d'événements, même si la taille ne bouge plus.
3. **Il n'est pas prévisible** : un geste lent donne beaucoup de petits changements, un geste brusque donne des grands sauts, des allers-retours et des répétitions.
4. **Conséquence pour un programme** : il ne faut pas supposer un événement par nouvelle taille ni refaire un travail coûteux (recréer des ressources graphiques, par exemple) à chaque événement. Il vaut mieux mémoriser la dernière taille reçue, ignorer les événements qui répètent la même taille, et appliquer le changement une seule fois.

*Limites : une seule exécution par série, et les chiffres exacts changent à chaque essai. C'est la tendance (beaucoup d'événements, répétitions, sauts) qui est à retenir.*
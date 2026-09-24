# Exercice 3 — Les deux configurations

## Les quatre nombres

| Configuration | Temps de build | Taille de l'exécutable |
|---|---|---|
| Debug | 0.45s | 45608 octets |
| Release | 0.34s | 45608 octets |

## Observations

Les deux exécutables ont exactement la même taille (45608 octets), ce qui est
contre-intuitif à première vue : on s'attend généralement à ce que Release
produise un binaire plus petit grâce aux optimisations et à l'absence de
symboles de debug. Avec un programme aussi réduit qu'un `main` qui retourne 0,
il n'y a ni code à optimiser ni symboles de debug substantiels à retirer, donc
la différence entre les deux configurations n'apparaît pas sur la taille du
binaire pour ce cas minimal.

Le temps de build est en revanche légèrement plus court en Release (0.34s
contre 0.45s), un écart qui reste dans la marge d'un programme aussi simple.

## Sortie complète de `jenga build` (Debug)

```
Configuration: Debug
Target:        Windows x86_64
Toolchain:     mingw

Build Order (1 projects):
  1. MaSalle [WINDOWED_APP]

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\MaSalle\MaSalle.exe

✓ Build Successful   Time: 0.45s

BUILD COMPLETED
Projects Built:  1/1
Time:           0.45s
Status:         ✓ SUCCESS
```

## Sortie complète de `jenga build --config Release`

```
Configuration: Release
Target:        Windows x86_64
Toolchain:     mingw

Build Order (1 projects):
  1. MaSalle [WINDOWED_APP]

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Release-Windows\MaSalle\MaSalle.exe

✓ Build Successful   Time: 0.33s

BUILD COMPLETED
Projects Built:  1/1
Time:           0.34s
Status:         ✓ SUCCESS
```
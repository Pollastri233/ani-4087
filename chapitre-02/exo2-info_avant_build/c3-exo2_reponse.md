# Exercice 2 — Info avant build

## Sortie de `jenga info -v`

```
[Loader] Loading workspace from C:\Users\HP PC\Desktop\projet\ani-4087\chapitre-02\exo2-info_avant_build\ma_salle.jenga
[Loader] Workspace 'MaSalleWks' post-processed.
========================= Jenga Workspace: MaSalleWks ==========================

Location: C:\Users\HP PC\Desktop\projet\ani-4087\chapitre-02\exo2-info_avant_build
Entry file: C:\Users\HP PC\Desktop\projet\ani-4087\chapitre-02\exo2-info_avant_build\ma_salle.jenga
Configurations: Debug, Release
Platforms: Windows
Target OSes: 
Target Architectures: 


Projects
------------------------------------------------------------
Name      Kind          Language   Test   External
==================================================
MaSalle   WindowedApp   C++        No     No


Available Toolchains
------------------------------------------------------------
Name       Family   Target OS   Arch     Env  
==============================================
host-gcc   gcc      Windows     x86_64   mingw
mingw      gcc      Windows     x86_64   mingw


Daemon
------------------------------------------------------------
Status: Not running


System
------------------------------------------------------------
Host OS: Windows
Host Architecture: x86_64
Host Environment: msvc
Host Triple: x86_64-pc-windows-msvc
Python: 3.13.5 (tags/v3.13.5:6cb20a2, Jun 11 2025, 16:15:46) [MSC v.1943 64 bit (AMD64)]
Jenga version: 2.8.0
```

## Ce que jenga info révèle

Le fichier `ma_salle.jenga` déclare explicitement le workspace, les configurations
(Debug/Release), et un projet `MaSalle` en `windowedapp`, C++17. `jenga info -v`
révèle plusieurs informations que ce fichier ne dit jamais :

- **La plateforme cible** (`Platforms: Windows`) est déduite automatiquement de
  la machine sur laquelle Jenga s'exécute, et non déclarée dans le fichier de
  projet.

- **Les toolchains disponibles** : deux chaînes de compilation GCC/mingw
  (`host-gcc` et `mingw`) sont détectées sur le système, sans qu'aucune ligne
  du `.jenga` ne les mentionne.

- **Un écart entre l'environnement hôte et la toolchain utilisée** : la section
  System indique `Host Environment: msvc`, l'environnement natif de la machine.
  Pourtant, seules des toolchains GCC/mingw apparaissent dans la liste
  disponible, et c'est bien mingw qui est utilisé au build (confirmé par la
  sortie de `jenga build` à l'exercice précédent). Cela montre que Jenga ne
  choisit pas la toolchain en fonction de l'environnement natif, mais parmi ce
  qu'il a effectivement su détecter et configurer sur la machine — msvc n'étant
  apparemment pas installé ou pas détecté ici.

- **Des informations d'environnement d'exécution** (version de Python, version
  de Jenga, état du daemon) qui n'ont pas de raison d'être dans un fichier de
  projet, puisqu'elles décrivent l'outil lui-même plutôt que ce qu'on construit.

En résumé, le fichier `.jenga` décrit *ce qu'on veut construire*, tandis que
`jenga info` décrit *avec quoi et sur quoi* cela va effectivement être
construit — une information dépendante de la machine, jamais figée dans le
fichier de projet.
# Exercice 1 — Le projet minimal

## Fichier .jenga

```python
from Jenga import *

with workspace("MaSalleWks", location="."):
    configurations(["Debug", "Release"])

    with project("MaSalle"):
        windowedapp()
        language("C++")
        cppdialect("C++17")
        location(".")
        files(["src/**.cpp"])
```

## src/main.cpp

```cpp
int main()
{
    return 0;
}



## Sortie de `jenga build`

```
PS C:\Users\HP PC\Desktop\projet\ani-4087\chapitre-02\exo1-le_projet_minimal> jenga build

Loading workspace...

Configuration: Debug
Target:        Windows x86_64
Toolchain:     mingw

Build Order (1 projects):
  1. MaSalle [WINDOWED_APP]

Project: MaSalle                    Kind: WINDOWED_APP

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: build\Bin\Debug-Windows\MaSalle\MaSalle.exe

✓ Build Successful   Time: 4.64s

BUILD COMPLETED
Projects Built:  1/1
Time:           4.65s
Status:         ✓ SUCCESS
```
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
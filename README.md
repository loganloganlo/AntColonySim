# AntColonySim

Ant colony simulation game built in **C++** using [Raylib](https://www.raylib.com/).

## Features
- Foragers gather food
- Workers defend the nest
- Predators hunt ants
- Nest spawns larva on death
- Expandable ecosystem

## Build Instructions
1. Open `Learning.sln` in Visual Studio 2022
2. Set build to **x64 → Debug** or **x64 → Release**
3. Make sure Raylib is installed and linked in:
   - C/C++ → General → Additional Include Directories
   - Linker → General → Additional Library Directories
   - Linker → Input → Additional Dependencies (`raylib.lib`)
4. Copy `raylib.dll` into your `Debug/` or `Release/` folder

## License
MIT License – see [LICENSE.txt](LICENSE.txt)

# Quoridor Project

This is a **C implementation** of the board game **Quoridor** for **two players**.  
The project includes two-player game logic, playing against a **smart computer**, game save/load functionality, and spells & rewards mechanics.

## Features
- ASCII board display  
- Two-player game or player vs **smart computer**  
- Save and load game state (`SaveGame.dat`)  
- Apply **spells and rewards**    

## Project Structure

```
ProjectRoot/
├── data/
│   └── SaveGame.dat
├── include/
│   ├── aih.h
│   ├── game.h
│   ├── magic.h
│   ├── movement.h
│   ├── player.h
│   ├── save.h
│   ├── ui.h
│   └── wall.h
├── src/
│   ├── ai.c
│   ├── magic.c
│   ├── main.c
│   ├── movement.c
│   ├── player.c
│   ├── save.c
│   ├── ui.c
│   └── wall.c
└── GAME.exe
```

## Installation & Run
To compile and run the project on Windows:
```bash
gcc -I include src/*.c -o GAME.exe
./GAME.exe

## Team Members
-salma naderi
-farhad alizade



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
.
├── data/
│   └── SaveGame.dat      # Saved game file
├── include/              # Header files
│   ├── aih.h             # Smart computer AI functions
│   ├── game.h            # Main game structures and enums
│   ├── magic.h           # Spells and rewards definitions
│   ├── movement.h        # Player movement validation
│   ├── player.h          # Player struct and functions
│   ├── save.h            # Save/load game (in binary)
│   ├── ui.h              # Board display and user input
│   └── wall.h            # Wall placement and validation
├── src/
│   ├── ai.c              # Computer AI logic
│   ├── magic.c           # Implementing spell effects
│   ├── main.c            # Main function, menu
│   ├── movement.c        # Movement rules implementation
│   ├── player.c          # Player actions implementation
│   ├── save.c            # Save/load game implementation
│   ├── ui.c              # Board rendering and input
│   └── wall.c            # Wall rules and validation
└── GAME.exe              # Compiled executable
```

## Installation & Run
To compile and run the project on Windows:
```bash
gcc -I include src/*.c -o GAME.exe
./GAME.exe
```

## Team Members
-salma naderi

-farhad alizade



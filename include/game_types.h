#ifndef GAME_TYPES_H
#define GAME_TYPES_H

#define MAX_WALLS 100


enum GameStatus { NOT_IMPELEMENTED, MOVE_AGAIN, NEXT_MOVE, Player_Win, TIE };

enum MoveStatus { MOVE_NOT_IMPELEMENTED, OUT_OF_BOARD, CANNOT_PASS_WALL, JUMP, VALID_MOVE };

enum Direction { UP, DOWN, LEFT, RIGHT };

enum DiagonalMove { UP_RIGHT, UP_LEFT, DOWN_RIGHT, DOWN_LEFT };

enum ComputerAction { COMPUTER_MOVE, COMPUTER_WALL };

enum MagicCategory { POSITIVE_MAGIC, NEGETIVE_MAGIC };

enum MagicEffect
{
    NONE_EFFECT,
    NEG_REMOVE_ALL_WALLS,
    NEG_REDUCE_WALLS,
    NEG_BLOCK_PLAYER,
    POS_INCREASE_WALLS,
    POS_TAKEN_WALLS,
};

enum winner { NO_WINNER, PLAYER1_WIN, PLAYER2_WIN };

enum WallDirection { HORIZONTAL, VERTICAL };

enum WallStatus { WALL_CONFLICT, INVALID_WALL, VALIDATE_WALL };


struct Wall
{
    int owner;
    int x;
    int y;
    enum WallDirection dir;
};

struct Player
{
    char name[20];
    int x;
    int y;
    int canwall;
    int currentEffect;
    int blockTurns;
    enum MagicEffect activeEffect;
};

struct Game
{
    int pathflag;
    int turnCounter;
    int dim;
    int wall_count;
    int gameMode;
    int currentTurn;
    int currentPlayer;
    struct Player player1;
    struct Player player2;
    struct Wall walls[MAX_WALLS];
};

#endif

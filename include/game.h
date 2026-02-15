#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>


enum GameStatus
{
    NOT_IMPELEMENTED,
    MOVE_AGAIN,
    NEXT_MOVE,
    Player_Win,
    TIE,
};

enum WallDirection
{
    HORIZONTAL,
    VERTICAL,
};

enum MagicEffect
{
    NONE_EFFECT,
    NEG_REMOVE_ALL_WALLS,
    NEG_REDUCE_WALLS,
    NEG_BLOCK_PLAYER,
    POS_INCREASE_WALLS,
    POS_TAKEN_WALLS,
};

enum MoveStatus
{
    MOVE_NOT_IMPELEMENTED,
    OUT_OF_BOARD,
    CANNOT_PASS_WALL,
    JUMP,
    VALID_MOVE,
};

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

enum DiagonalMove
{
    UP_RIGHT,
    UP_LEFT,
    DOWN_RIGHT,
    DOWN_LEFT,
};

enum ComputerAction
{
    COMPUTER_MOVE,
    COMPUTER_WALL,
};

enum MagicCategory
{
    POSITIVE_MAGIC,
    NEGETIVE_MAGIC,
};

enum winner
{
    NO_WINNER,
    PLAYER1_WIN,
    PLAYER2_WIN
};

enum WallStatus
{
    WALL_CONFLICT,
    INVALID_WALL,
    VALIDATE_WALL,
};

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
    struct Wall walls[100];
};

struct Player constructPlayer(int x, int y, int wallcount, char name[]);

struct Game constructGame(struct Player player_1, struct Player player_2, int dimention);
//=======================
enum MoveStatus validateMove(struct Player *player, struct Game *gameBoard, enum Direction direction, int *out_x, int *out_y);

enum GameStatus action(struct Game *game, struct Player *player, enum Direction direction);

enum winner checkwinner(struct Game *game);

enum Direction getArrowKey();

enum Direction readArrowKey(char Arrow);

enum WallStatus checkWall(struct Game *game, int x, int y, char d);
//=======================
int hasHorizontalWall(struct Game *game, int x, int y);

int hasVerticalWall(struct Game *game, int x, int y);

int isPlayerBlocking(struct Player *other, int x, int y);

void addWall(struct Game *game, int x, int y, char d, int owner);

void printGameBoard(struct Game *game);

void checkPath(struct Game *game, int x, int y, int player, int visited[10][10]);


#endif

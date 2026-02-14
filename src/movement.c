#include "game.h"
#include "wall.h"
#include "movement.h"


void checkPath(struct Game *game, int x, int y, int player, int visited[10][10])
{
    if (game->pathflag)
        return;

    if (x < 0 || x >= game->dim || y < 0 || y >= game->dim)
        return;

    if (visited[x][y])
        return;

    if (player == 1 && y == game->dim - 1)
    {
        game->pathflag = 1;
        return;
    }
    if (player == 2 && y == 0)
    {
        game->pathflag = 1;
        return;
    }

    visited[x][y] = 1;

    if (!hasHorizontalWall(game, x, y))
        checkPath(game, x, y - 1, player, visited);
    if (!hasHorizontalWall(game, x, y + 1))
        checkPath(game, x, y + 1, player, visited);
    if (!hasVerticalWall(game, x, y))
        checkPath(game, x - 1, y, player, visited);
    if (!hasVerticalWall(game, x + 1, y))
        checkPath(game, x + 1, y, player, visited);
}

int isPlayerBlocking(struct Player *other, int x, int y)
{
    return (other->x == x && other->y == y);
}

int hasWallBehindPlayer(struct Game *game, enum Direction dir, int x, int y)
{
    switch (dir)
    {
    case UP:
        return hasHorizontalWall(game, x, y);
    case DOWN:
        return hasHorizontalWall(game, x, y + 1);
    case LEFT:
        return hasVerticalWall(game, x, y);
    case RIGHT:
        return hasVerticalWall(game, x + 1, y);
    }
    return 1;
}

int canDiagonalLeft(struct Game *game, enum Direction dir, int x, int y)
{
    switch (dir)
    {
    case UP:
        return !hasVerticalWall(game, x, y);
    case DOWN:
        return !hasVerticalWall(game, x, y + 1);
    case LEFT:
        return !hasHorizontalWall(game, x - 1, y);
    case RIGHT:
        return !hasHorizontalWall(game, x, y);
    }
    return 0;
}

int canDiagonalRight(struct Game *game, enum Direction dir, int x, int y)
{
    switch (dir)
    {
    case UP:
        return !hasVerticalWall(game, x + 1, y);
    case DOWN:
        return !hasVerticalWall(game, x + 1, y + 1);
    case LEFT:
        return !hasHorizontalWall(game, x - 1, y + 1);
    case RIGHT:
        return !hasHorizontalWall(game, x, y + 1);
    }
    return 0;
}


void directJumpTarget(enum Direction dir, int x, int y, int *out_x, int *out_y)
{
    *out_x = x;
    *out_y = y;
    switch (dir)
    {
    case UP:
        (*out_y)--;
        break;
    case DOWN:
        (*out_y)++;
        break;
    case LEFT:
        (*out_x)--;
        break;
    case RIGHT:
        (*out_x)++;
        break;
    }
}

void diagonalJumpTarget(enum Direction dir, enum DiagonalMove diag, int x, int y, int *out_x, int *out_y)
{
    *out_x = x;
    *out_y = y;

    switch (diag)
    {
    case UP_LEFT:
        (*out_x)--;
        break;
    case UP_RIGHT:
        (*out_x)++;
        break;
    case DOWN_LEFT:
        (*out_y)++;
        break;
    case DOWN_RIGHT:
        (*out_y)++;
        break;
    }
}

enum DiagonalMove forcedDiagonal(enum Direction dir, int left)
{
    switch (dir)
    {
    case UP:
        return left ? UP_LEFT : UP_RIGHT;
    case DOWN:
        return left ? DOWN_LEFT : DOWN_RIGHT;
    case LEFT:
        return left ? UP_LEFT : DOWN_LEFT;
    case RIGHT:
        return left ? UP_RIGHT : DOWN_RIGHT;
    }
    return UP_LEFT;
}


enum MoveStatus checkJump(struct Player *player, struct Player *otherPlayer, struct Game *game, enum Direction direction, int x, int y, int *out_x, int *out_y)
{
    if (otherPlayer->x != x || otherPlayer->y != y)
    {
        *out_x = x;
        *out_y = y;
        return VALID_MOVE;
    }

    if (!hasWallBehindPlayer(game, direction, x, y))
    {
        directJumpTarget(direction, x, y, out_x, out_y);
        if (*out_x < 0 || *out_x >= game->dim || *out_y < 0 || *out_y >= game->dim)
            return OUT_OF_BOARD;

        return JUMP;
    }

    int jump_from_x = otherPlayer->x;
    int jump_from_y = otherPlayer->y;
    int left = canDiagonalLeft(game, direction, jump_from_x, jump_from_y);
    int right = canDiagonalRight(game, direction, jump_from_x, jump_from_y);

    if (!left && !right)
        return CANNOT_PASS_WALL;

    enum DiagonalMove diag;
    if (left && right)
    {
        diag = UP_LEFT;
    }
    else
        diag = forcedDiagonal(direction, left);

    diagonalJumpTarget(direction, diag, jump_from_x, jump_from_y, out_x, out_y);

    if (*out_x < 0 || *out_x >= game->dim || *out_y < 0 || *out_y >= game->dim)
        return OUT_OF_BOARD;
    return JUMP;
}


enum MoveStatus validateMove(struct Player *player, struct Game *gameBoard, enum Direction direction, int *out_x, int *out_y)
{
    int next_x_move = player->x;
    int next_y_move = player->y;

    struct Player *otherPlayer = (player == &gameBoard->player1) ? &gameBoard->player2 : &gameBoard->player1;

    switch (direction)
    {
    case UP:
        if (hasHorizontalWall(gameBoard, player->x, player->y))
            return CANNOT_PASS_WALL;
        next_y_move--;
        break;

    case DOWN:
        if (hasHorizontalWall(gameBoard, player->x, player->y + 1))
            return CANNOT_PASS_WALL;
        next_y_move++;
        break;

    case LEFT:
        if (hasVerticalWall(gameBoard, player->x, player->y))
            return CANNOT_PASS_WALL;
        next_x_move--;
        break;

    case RIGHT:
        if (hasVerticalWall(gameBoard, player->x + 1, player->y))
            return CANNOT_PASS_WALL;
        next_x_move++;
        break;
    }
    if (next_x_move < 0 || next_x_move >= gameBoard->dim || next_y_move < 0 || next_y_move >= gameBoard->dim)
        return OUT_OF_BOARD;

    return checkJump(player, otherPlayer, gameBoard, direction, next_x_move, next_y_move, out_x, out_y);
};


enum winner checkwinner(struct Game *game)
{
    if (game->player1.y == game->dim - 1)
        return PLAYER1_WIN;
    if (game->player2.y == 0)
        return PLAYER2_WIN;
    return NO_WINNER;
}

enum GameStatus action(struct Game *game, struct Player *player, enum Direction direction)
{
    int out_x, out_y;
    enum MoveStatus move_status = validateMove(player, game, direction, &out_x, &out_y);
    switch (move_status)
    {

    case VALID_MOVE:
    case JUMP:
        player->x = out_x;
        player->y = out_y;
        return NEXT_MOVE;

    case OUT_OF_BOARD:
    case CANNOT_PASS_WALL:
        return MOVE_AGAIN;

    case MOVE_NOT_IMPELEMENTED:
    default:
        return NOT_IMPELEMENTED;
    }

    return NOT_IMPELEMENTED;
}

void switchTurn(struct Game *game)
{
    game->currentPlayer ^= 1;
}


enum Direction readArrowKey(char Arrow)
{
    switch (Arrow)
    {
    case 72:
        return UP;
    case 80:
        return DOWN;
    case 77:
        return RIGHT;
    case 75:
        return LEFT;
    }

    return -1;
};

enum Direction getArrowKey()
{
    int ch = getch();

    if (ch == 0 || ch == 224)
    {
        int arrow = getch();
        return readArrowKey(arrow);
    }
    return -1;
};

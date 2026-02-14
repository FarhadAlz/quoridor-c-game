#include "game.h"
#include "wall.h"

enum WallStatus checkWall(struct Game *game, int x, int y, char d)
{
    switch (d)
    {
    case 'H':
        if (x < 0 || x >= game->dim - 1 || y < 0 || y >= game->dim)
            return INVALID_WALL;

        for (int i = 0; i < game->wall_count; i++)
        {
            if (game->walls[i].dir == HORIZONTAL)
                if (y == game->walls[i].y &&
                    (x == game->walls[i].x || x == game->walls[i].x - 1 || x == game->walls[i].x + 1))
                    return WALL_CONFLICT;
        }
        break;

    case 'V':
        if (y < 0 || y >= game->dim - 1 || x < 0 || x >= game->dim)
            return INVALID_WALL;

        for (int i = 0; i < game->wall_count; i++)
        {
            if (game->walls[i].dir == VERTICAL)
                if (x == game->walls[i].x &&
                    (y == game->walls[i].y || y == game->walls[i].y - 1 || y == game->walls[i].y + 1))
                    return WALL_CONFLICT;
        }
        break;

    default:
        return INVALID_WALL;
    }
    return VALIDATE_WALL;
};

void addWall(struct Game *game, int x, int y, char d, int owner)
{
    int flag1 = 0, flag2 = 0;
    enum WallStatus status = checkWall(game, x, y, d);
    if (status != VALIDATE_WALL)
        return;
    struct Wall wall;
    wall.x = x;
    wall.y = y;
    wall.owner = owner;
    wall.dir = (d == 'H') ? HORIZONTAL : VERTICAL;
    game->walls[game->wall_count++] = wall;

    game->pathflag = 0;
    int visited[10][10] = {0};
    checkPath(game, game->player2.x, game->player2.y, 2, visited);
    flag2 = game->pathflag;
    game->pathflag = 0;
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            visited[i][j] = 0;
    checkPath(game, game->player1.x, game->player1.y, 1, visited);
    flag1 = game->pathflag;

    if (!flag1 || !flag2)
    {
        game->wall_count--;
        printf("cannot place wall\n");
    }
}

int hasHorizontalWall(struct Game *game, int x, int y)
{
    if (x < 0 || x > game->dim || y < 0 || y > game->dim)
        return 1;

    for (int i = 0; i < game->wall_count; i++)
    {
        if (game->walls[i].dir == HORIZONTAL && game->walls[i].y == y && (game->walls[i].x == x || game->walls[i].x == x - 1))
            return 1;
    }
    return 0;
}

int hasVerticalWall(struct Game *game, int x, int y)
{
    if (x < 0 || x > game->dim || y < 0 || y > game->dim)
        return 1;

    for (int i = 0; i < game->wall_count; i++)
    {
        if (game->walls[i].dir == VERTICAL && game->walls[i].x == x && (game->walls[i].y == y || game->walls[i].y == y - 1))
            return 1;
    }
    return 0;
}

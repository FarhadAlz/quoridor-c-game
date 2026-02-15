#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "game.h"
#include "movement.h"
#include "wall.h"
#include "ai.h"

int evaluateGame(struct Game *game)
{
    int myDist = bfsShortestPath(game, game->player2.x, game->player2.y, 2);
    int oppDist = bfsShortestPath(game, game->player1.x, game->player1.y, 1);

    int wallFactor = game->player2.canwall - game->player1.canwall;
    return oppDist - myDist + wallFactor;
}

enum ComputerAction computerDecideAction(struct Game *game, struct Player *computer, struct Player *opponent)
{
    int myDist = bfsShortestPath(game, computer->x, computer->y, (computer == &game->player1) ? 1 : 2);
    int oppDist = bfsShortestPath(game, opponent->x, opponent->y, (opponent == &game->player1) ? 1 : 2);

    if (myDist > oppDist || computer->canwall <= 0)
        return COMPUTER_MOVE;
    else
        return COMPUTER_WALL;
}

int bfsShortestPath(struct Game *game, int startX, int startY, int player)
{
    int visited[10][10] = {0};
    int dist[10][10];
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            dist[i][j] = INT_MAX;

    typedef struct
    {
        int x, y;
    } Node;

    Node queue[100];
    int front = 0, back = 0;

    queue[back++] = (Node){startX, startY};
    visited[startY][startX] = 1;
    dist[startY][startX] = 0;

    while (front < back)
    {
        Node cur = queue[front++];
        int x = cur.x;
        int y = cur.y;
        int d = dist[y][x];

        if (y > 0 && !hasHorizontalWall(game, x, y) && !visited[y - 1][x])
        {
            visited[y - 1][x] = 1;
            dist[y - 1][x] = d + 1;
            queue[back++] = (Node){x, y - 1};
        }
        if (y < game->dim - 1 && !hasHorizontalWall(game, x, y + 1) && !visited[y + 1][x])
        {
            visited[y + 1][x] = 1;
            dist[y + 1][x] = d + 1;
            queue[back++] = (Node){x, y + 1};
        }
        if (x > 0 && !hasVerticalWall(game, x, y) && !visited[y][x - 1])
        {
            visited[y][x - 1] = 1;
            dist[y][x - 1] = d + 1;
            queue[back++] = (Node){x - 1, y};
        }
        if (x < game->dim - 1 && !hasVerticalWall(game, x + 1, y) && !visited[y][x + 1])
        {
            visited[y][x + 1] = 1;
            dist[y][x + 1] = d + 1;
            queue[back++] = (Node){x + 1, y};
        }
    }

    int shortest = INT_MAX;
    if (player == 1)
    {
        for (int i = 0; i < game->dim; i++)
        {
            if (dist[game->dim - 1][i] < shortest)
                shortest = dist[game->dim - 1][i];
        }
    }
    else
    {
        for (int i = 0; i < game->dim; i++)
        {
            if (dist[0][i] < shortest)
                shortest = dist[0][i];
        }
    }

    return shortest;
}

void computerSmartMove(struct Game *game, struct Player *computer)
{
    int best_x = computer->x;
    int best_y = computer->y;
    int playerNum = (computer == &game->player1) ? 1 : 2;
    int best_dist = bfsShortestPath(game, computer->x, computer->y, playerNum);

    int dest_x, dest_y;
    enum Direction dirs[4] = {UP, DOWN, LEFT, RIGHT};

    for (int i = 0; i < 4; i++)
    {
        enum MoveStatus status = validateMove(computer, game, dirs[i], &dest_x, &dest_y);
        if (status == VALID_MOVE || status == JUMP)
        {
            int dist = bfsShortestPath(game, dest_x, dest_y, (computer == &game->player1) ? 1 : 2);
            if (dist < best_dist)
            {
                best_dist = dist;
                best_x = dest_x;
                best_y = dest_y;
            }
        }
    }

    computer->x = best_x;
    computer->y = best_y;
}

void computerPlaceWall(struct Game *game, struct Player *computer)
{
    struct Player *opponent = &game->player1;

    int ox = opponent->x;
    int oy = opponent->y;

    int bestDist = bfsShortestPath(game,ox,oy,1);

    enum Direction bestDir;
    int dest_x,dest_y;

    enum Direction dirs[4] = {UP, DOWN, LEFT, RIGHT};

    for(int i = 0;i < 4;i++)
    {
        enum MoveStatus status = validateMove(opponent,game,dirs[i],&dest_x,&dest_y);

        if(status = VALID_MOVE)
        {
            int dist = bfsShortestPath(game,dest_x,dest_y,1);

            if(dist < bestDist)
            {
                bestDist = dist;
                bestDir = dirs[i];
            }
        }
    }

    int pre = game->wall_count;

    switch(bestDir)
    {
        case UP   : addWall(game,ox,oy,'H',2);      break;
        case DOWN : addWall(game,ox,oy+1,'H',2);    break;
        case LEFT : addWall(game,ox,oy,'H',2);      break;
        case RIGHT: addWall(game,ox+1,oy,'H',2);    break;
    }
    if(game->wall_count > pre)
        computer->canwall--;

    else
    computerSmartMove(game,computer);
}
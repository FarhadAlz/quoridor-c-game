#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "game.h"
#include "movement.h"
#include "wall.h"
#include "ai.h"


enum ComputerAction randomComputerAction(struct Player *computer)
{
    if (computer->canwall <= 0)
        return COMPUTER_MOVE;

    return rand() % 2;
}


void computerMove(struct Game *game, struct Player *computer)
{
    int valid_count = 0;
    int dest_x, dest_y;
    enum Direction computer_dir[4] = {UP, DOWN, LEFT, RIGHT};
    enum Direction valid_move[4];

    for(int i=0;i<4;i++)
    {
        enum MoveStatus status = validateMove(computer, game, computer_dir[i], &dest_x, &dest_y);
        if(status == VALID_MOVE || status == JUMP)
            valid_move[valid_count++] = computer_dir[i];
    }

    if(valid_count == 0)
        return; 

    for(int i=0;i<valid_count;i++)
    {
        if(valid_move[i] == UP)
        {
            enum Direction chosen = valid_move[i];
            validateMove(computer, game, chosen, &dest_x, &dest_y);
            computer->x = dest_x;
            computer->y = dest_y;
            return;
        }
    }

    enum Direction chosen = valid_move[rand() % valid_count];
    validateMove(computer, game, chosen, &dest_x, &dest_y);
    computer->x = dest_x;
    computer->y = dest_y;
}


void computerPlaceWall(struct Game *game, struct Player *computer)
{
    int dimention = game->dim;
    int wallPlaced = 0;

    for(int attempts = 0; attempts < 20 && !wallPlaced; attempts++)
    {
        int x = rand() % (dimention - 1);
        int y = rand() % (dimention - 1);
        char dir = (rand() % 2) ? 'H' : 'V';
        int pre_count = game->wall_count;

        addWall(game, x, y, dir, 2);
        if(game->wall_count > pre_count)
        {
            wallPlaced = 1;
            computer->canwall--;
        }
    }

    if(!wallPlaced)
    {
        printf("Computer could not place a wall, will move instead.\n");
        computerMove(game, computer);
    }
}

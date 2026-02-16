#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#include "game.h"
#include "player.h"
#include "magic.h"
#include "movement.h"
#include "wall.h"
#include "ai.h"
#include "save.h"
#include "ui.h"

void printGameBoard(struct Game *game)
{
    system("cls");
    for (int row = 0; row < 10; row++)
    {
        printf("....");
    }
    printf(".\n");

    for (int j = 0; j < 10; j++)
    {
        for (int i = 0; i <= 10; i++)
        {
            if (hasVerticalWall(game, i, j))
                printf("| ");
            else
                printf(": ");
            if (i == game->player1.x && j == game->player1.y)
            {
                printf("%C ", 31);
            }
            else if (i == game->player2.x && j == game->player2.y)
            {
                printf("%c ", 30);
            }
            else
            {
                printf("  ");
            }
        }
        printf("\n");
        for (int i = 0; i < 10; i++)
        {
            if (hasHorizontalWall(game, i, j + 1))
                printf("====");
            else
                printf("....");
        }
        printf(".\n");
    }
}

void selectActionPlayer(struct Game *game, struct Player *player)
{
    if (player->blockTurns > 0)
    {
        printf("Player %s is blocked for this turn!\n", player->name);
        player->blockTurns--;
        getch();
        return;
    }

    int validAction = 0;
    int selection;

    while (!validAction)
    {
        printf("%s turn:\n", player->name);
        printf("Choose Action:\n1- Move\n2- Place wall\n3- Save game\n");

        scanf("%d", &selection);

        if (selection == 1)
        {
            while (1)
            {
                enum Direction dir;
                do
                {
                    dir = getArrowKey();
                } while (dir == -1);

                enum GameStatus status = action(game, player, dir);
                if (status == NEXT_MOVE || status == JUMP)
                {
                    validAction = 1;
                    break;
                }
                else
                {
                    printf("Invalid move! Try again.\n");
                    break;
                }
            }
        }
        else if (selection == 2)
        {
            if (player->canwall <= 0)
            {
                printf("No walls left for Player %s\n", player->name);
                getch();
                continue;
            }

            int x, y;
            char d;
            scanf("%d %d %c", &x, &y, &d);
            int PreWallCount = game->wall_count;
            addWall(game, y, x, d, game->currentPlayer + 1);
            if (game->wall_count > PreWallCount)
            {
                player->canwall--;
                validAction = 1;
            }
            else
            {
                printf("Cannot place wall! Choose another action.\n");
                continue;
            }
        }
        else if (selection == 3)
        {
            game->currentTurn = game->turnCounter;
            saveGame(game);

            int saveOptions;
            printf("Pick one option:\n1- Save and Continue\n2- Save and Quit\n");
            do
            {
                scanf("%d", &saveOptions);
            } while (saveOptions != 1 && saveOptions != 2);

            if (saveOptions == 1)
            {
                printf("Game saved! Continue your turn.\n");
                continue;
            }
            else if (saveOptions == 2)
            {
                printf("Game saved and Quit.\n");
                exit(0);
            }
        }
        else
        {
            printf("Invalid selection! Try again.\n");
        }
    }
}

void withComputer(struct Game *game)
{
    game->turnCounter = -1;
    struct Player *computer = &game->player2;

    while (checkwinner(game) == NO_WINNER)
    {
        printGameBoard(game);

        game->currentPlayer = 0;
        game->turnCounter++;
        magicBox(game, &game->player1, &game->player2);
        selectActionPlayer(game, &game->player1);

        if (checkwinner(game) != NO_WINNER)
            break;

        printGameBoard(game);
        game->currentPlayer = 1;
        game->turnCounter++;

        if (computer->blockTurns > 0)
        {
            printf("Computer is blocked for this turn!\n");
            computer->blockTurns--;
            Sleep(1000);
            continue;
        }

        enum ComputerAction actiontype = computerDecideAction(game, computer, &game->player1);
        Sleep(1000);
        if (actiontype == COMPUTER_MOVE)
            computerSmartMove(game, computer);
        else
            computerPlaceWall(game, computer);
    }

    printGameBoard(game);
    enum winner w = checkwinner(game);
    if (w == PLAYER1_WIN)
        printf("Congratulations! You win :))\n");
    else
        printf("GAME OVER, Computer wins!\n");
    remove("data/SaveGame.dat");
    exit(0);
}

void withPlayer(struct Game *game)
{
    game->turnCounter = -1;
    while (checkwinner(game) == NO_WINNER)
    {
        printGameBoard(game);

        game->currentPlayer = 0;
        game->turnCounter++;
        magicBox(game, &game->player1, &game->player2);
        selectActionPlayer(game, &game->player1);

        if (checkwinner(game) != NO_WINNER)
            break;

        printGameBoard(game);
        game->currentPlayer = 1;
        game->turnCounter++;
        selectActionPlayer(game, &game->player2);
    }

    printGameBoard(game);
    struct Player *winner = (checkwinner(game) == PLAYER1_WIN) ? &game->player1 : &game->player2;
    printf("Congratulations %s, you win :))", winner->name);
    remove("data/SaveGame.dat");
}

void choosePlayer()
{
    char name1[30], name2[30];
    int choose, wallcounter, dim = 10;

    printf("Choose one option:\n1- Player VS Player\n2- Player VS Computer\n");
    do
    {
        scanf("%d", &choose);
    } while (choose != 1 && choose != 2);

    printf("Set the number of walls limit: ");
    scanf("%d", &wallcounter);

    if (choose == 1)
    {
        printf("Enter player1 name:\n");
        scanf("%s", name1);
        printf("Enter player2 name:\n");
        scanf("%s", name2);
        struct Game game = constructGame(constructPlayer(0, 0, wallcounter, name1),
                                         constructPlayer(0, dim - 1, wallcounter, name2),
                                         dim);
        withPlayer(&game);
    }
    else
    {
        printf("Enter player1 name:\n");
        scanf("%s", name1);
        strcpy(name2, "computer");
        struct Game game = constructGame(constructPlayer(0, 0, wallcounter, name1),
                                         constructPlayer(0, dim - 1, wallcounter, name2),
                                         dim);
        withComputer(&game);
    }
}

void welcome()
{
    struct Game game;
    int choice, loaded;

    while (1)
    {
        system("cls");
        printf("Welcome to <<Quoridor>>\n");
        printf("Prefer?\n1- New Game\n2- Load Game\n");
        scanf("%d", &choice);

        if (choice == 1)
        {
            choosePlayer();
            continue;
        }
        else if (choice == 2)
        {
            loaded = loadGame(&game);
            if (loaded)
            {
                printf("Game Loaded Successfully!\n");
                game.turnCounter = game.currentTurn;
                Sleep(800);
                (game.gameMode == 1) ? withPlayer(&game) : withComputer(&game);
                break;
            }
            else
            {
                printf("NO save file found! Please start a New Game.\n");
                Sleep(1000);
                continue;
            }
        }
        else
        {
            printf("Invalid option! Try again.\n");
            Sleep(1000);
        }
    }
}

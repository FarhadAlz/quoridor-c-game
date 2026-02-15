#include "game.h"
#include "save.h"

int loadGame(struct Game *game)
{
    FILE *fp = fopen("data/SaveGame.dat", "rb");

    if (!fp)
        return 0;

    fread(game, sizeof(struct Game), 1, fp);
    fclose(fp);

    return 1;
}

void saveGame(struct Game *game)
{
    FILE *fp = fopen("data/SaveGame.dat", "wb");

    if (!fp)
    {
        printf("Error Saving File!\n");
        return;
    }

    fwrite(game, sizeof(struct Game), 1, fp);
    fclose(fp);

    printf("Game saved successfully!\n");
}

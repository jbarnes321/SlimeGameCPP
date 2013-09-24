#include "Game/SlimeController.h"

int main()
{
    SlimePtr game(new SlimeGame());

    game->start();

    return 0;
}


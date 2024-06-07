#include <stdlib.h>
#include <time.h>
#include "game.h"


int main()
{
    game game;
    srand(time(NULL));
    game.run();
    return 0;
}
#include "Game.hpp"
#include "HardcodedStrings.hpp"

int main(int argc, char *argv[])
{
    Game app(800, 600, 60, AppName);

    app.run();
    return 0;
}
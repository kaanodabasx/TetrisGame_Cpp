#include <raylib.h>
#include "pages.h"

int main()
{
    bgcolor = newBlack;
    buttoncolor = newDarkPurple;
    textcolor = GOLD;

    music = LoadMusicStream("Sounds/music.mp3");
    menu();
    UnloadMusicStream(music);

    return 0;
}

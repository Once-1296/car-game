#include"support.h"
int main()
{
    std::srand(static_cast<unsigned>(time(NULL)));
    support game;
    //game loop
    while (game.running())
    {
        //Update
        game.update();
        //Render
        game.render();



    }
	return 0;
}
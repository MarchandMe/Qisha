#include "appmain.h"

void appmain::run()
{
	init();
	loop();
}

void appmain::init()
{
	InitWindow(screenWidth, screenHeight, "QISHA");
	SetTargetFPS(60);
	//set st vars
	Qisha.Scale = 100;
	Qisha.BaseSize = screenWidth / 100;
	Qisha.BaseSpd = screenHeight / 100;
	Qisha.PosX = screenWidth / 2;
	Qisha.PosY = screenHeight / 2;

    Qisha.CharCol = BLACK;
}

void appmain::loop()
{
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        Qisha.Spd = Qisha.BaseSpd*(105-Qisha.Scale)/40;
        //std::cout << Qisha.Spd <<std::endl;
        if (IsKeyDown(KEY_RIGHT)) Qisha.PosX += Qisha.Spd;
        if (IsKeyDown(KEY_LEFT)) Qisha.PosX -= Qisha.Spd;
        if (IsKeyDown(KEY_UP)) Qisha.PosY -= Qisha.Spd;
        if (IsKeyDown(KEY_DOWN)) Qisha.PosY += Qisha.Spd;

        //atk
        if (IsKeyReleased(KEY_SPACE)&&(duration_cast<ms>(Clock::now()-Qisha.LastAtk)>Qisha.AtkCooldown) && (Qisha.Scale >10))
        {
            Qisha.Scale -= 10;
            Qisha.LastAtk = Clock::now();
        }
        else if ((duration_cast<ms>(Clock::now() - Qisha.LastAtk) > Qisha.ScaleCooldown)&&(Qisha.Scale<100))
        {
            Qisha.Scale += 0.1;
            
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BkgCol);

        //draw scale bar txt
        DrawText((std::to_string(Qisha.Scale)).c_str(), 10, 10, 20, DARKGRAY);

        //draw char
        DrawCircle(Qisha.PosX, Qisha.PosY, Qisha.BaseSize*Qisha.Scale/10, Qisha.CharCol);

        //draw atk

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

}

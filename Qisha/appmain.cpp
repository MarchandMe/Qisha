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
        Qisha.Spd = Qisha.BaseSpd * (105 - Qisha.Scale) / 40;
        //std::cout << Qisha.Spd <<std::endl;
        if (IsKeyDown(KEY_RIGHT)) Qisha.PosX += Qisha.Spd;
        if (IsKeyDown(KEY_LEFT)) Qisha.PosX -= Qisha.Spd;
        if (IsKeyDown(KEY_UP)) Qisha.PosY -= Qisha.Spd;
        if (IsKeyDown(KEY_DOWN)) Qisha.PosY += Qisha.Spd;

        //if still, recover energy
        if (!IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_UP) && !IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && (Qisha.Scale < 100) && (duration_cast<ms>(Clock::now() - Qisha.LastAtk)) > ms(500)) Qisha.Scale += 0.3;
        //atk
        if (IsKeyReleased(KEY_SPACE) && (duration_cast<ms>(Clock::now() - Qisha.LastAtk) > Qisha.AtkCooldown) && (Qisha.Scale > 10))
        {
            Qisha.Scale -= 10;
            Qisha.LastAtk = Clock::now();
        }
        else if ((duration_cast<ms>(Clock::now() - Qisha.LastAtk) > Qisha.ScaleCooldown) && (Qisha.Scale < 100))
        {
            Qisha.Scale += 0.2;

        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BkgCol);

        //draw char
        DrawCircle(Qisha.PosX, Qisha.PosY, Qisha.BaseSize * Qisha.Scale / 20, Qisha.CharCol);

        //draw atk
        //currently just a ring of fire
        if ((duration_cast<ms>(Clock::now() - Qisha.LastAtk)) < ms(200)) {
            Vector2 center = { Qisha.PosX, Qisha.PosY };
            DrawRing(center, Qisha.BaseSize * Qisha.Scale / 10 + 10, Qisha.BaseSize * Qisha.Scale / 10 + 15, 0, 360.0f, 0, DARKGREEN);
        }
        //draw UI
        //draw scale bar txt
        DrawText((std::to_string(Qisha.Scale)).c_str(), 10, 10, 20, DARKGRAY);
        DrawRectangle(1700, 200, 30, 600, BLACK);//bar
        DrawRectangle(1700, 200, 30, 600*((100-Qisha.Scale)/100), RED);//bkg

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

}

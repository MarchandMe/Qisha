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

    bool mode = 0;
    //
    gravity = 5;

	//set st vars
	Qisha.Scale = 40;//smaller starting size &higher spd
    Qisha.BaseSize = 9;
	Qisha.BaseSpd = 36;
	Qisha.PosX = screenWidth / 2;
	Qisha.PosY = screenHeight / 2;
    Qisha.Jmpheight = 20;
    Qisha.CharCol = BLACK;

    //create floor
    floor.disp = { 0,900,1800,100 };
    floor.hitbox = { 0,900,1800,100 };
}


void appmain::title()
{
    BeginDrawing();

    ClearBackground(BkgCol);
        //draw title screen
        DrawText("QISHA", 200, 200, 300, BLACK);
        DrawText("The Scales of Justice", 200, 450, 100, BLACK);
        DrawText("Press Enter to Start", 1000, 700, 50, BLACK);
        //return;
    EndDrawing();
}

void appmain::loop()
{
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //TITLE
        if (ifTitle)
        {

            title();
            if (IsKeyPressed(KEY_ENTER)) ifTitle = false;
            else continue;
        }
        
        //GAME
        // Update
        //----------------------------------------------------------------------------------
        
        //get mouse dir
        Vector2 MousePos = GetMousePosition();
        
        Qisha.Spd = Qisha.BaseSpd * (105 - Qisha.Scale) / 400;
        //std::cout << Qisha.Spd <<std::endl;
        if (IsKeyDown(KEY_RIGHT)) Qisha.PosX += Qisha.Spd;
        if (IsKeyDown(KEY_LEFT)) Qisha.PosX -= Qisha.Spd;
        if (IsKeyReleased(KEY_UP)) Qisha.PosY -= Qisha.Spd*Qisha.Jmpheight;
        //if (IsKeyDown(KEY_DOWN)) Qisha.PosY += Qisha.Spd;

        //move to gravity
        //chk floor htbox
        if ((Qisha.PosY+(Qisha.BaseSize * Qisha.Scale / 20)) <= floor.hitbox.y) Qisha.PosY += gravity;

        //if still, recover energy
        //if (!IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_UP) && !IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && (Qisha.Scale < 100) && (duration_cast<ms>(Clock::now() - Qisha.LastAtk)) > ms(500)) Qisha.Scale += 0.3;
        //atk
        if (IsKeyDown(KEY_SPACE) && (duration_cast<ms>(Clock::now() - Qisha.LastAtk) > Qisha.AtkCooldown) && (Qisha.Scale > 10))
        {
            Qisha.Scale -= 10;
            Qisha.LastAtk = Clock::now();
            std::shared_ptr<projectile> new_proj(new projectile());
            new_proj->PosX = Qisha.PosX;
            new_proj->PosY = Qisha.PosY;
            new_proj->Atk = new_proj->BaseAtk * (1 / Qisha.Scale);
            new_proj->Spd = new_proj->BaseSpd * (1 / Qisha.Scale);
            Vector2 cpos = { Qisha.PosX, Qisha.PosY };
            new_proj->Dir = Vector2Angle(cpos, MousePos); //TODO: &VITAL: FIX ANGLE SHOT AT!!!!
            projs.emplace_back(new_proj);
        }
        else if ((duration_cast<ms>(Clock::now() - Qisha.LastAtk) > Qisha.ScaleCooldown) && (Qisha.Scale < 100))
        {
            //Qisha.Scale += 0.2;
            Qisha.Scale += 0;

        }

        //Handle Atks
        for (std::shared_ptr<projectile> p : projs) 
        {
            //tbd::handle destruction and damage
            //move all
            float totalmov = p->Spd;
            p->PosX += cos(p->Dir)*totalmov;
            p->PosY += sin(p->Dir)*totalmov;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BkgCol);

        //draw floor
        DrawRectangleRec(floor.disp, BLACK);

        //draw char
        DrawCircle(Qisha.PosX, Qisha.PosY, Qisha.BaseSize * Qisha.Scale / 20, Qisha.CharCol);


        //draw atk
        //currently just a ring of fire
        if ((duration_cast<ms>(Clock::now() - Qisha.LastAtk)) < ms(200)) {
            Vector2 center = { Qisha.PosX, Qisha.PosY };
            DrawRing(center, Qisha.BaseSize * Qisha.Scale / 10 + 10, Qisha.BaseSize * Qisha.Scale / 10 + 15, 0, 360.0f, 0, DARKGREEN);
        }
        for (std::shared_ptr<projectile> p : projs)
        {
            DrawCircle(p->PosX, p->PosY, p->Size, Qisha.CharCol);
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
/*
void appmain::moveChar(float dist, float dir)
{
    //chk collision detection
    for (std::shared_ptr<object> ob : obj)
    {
        if () {
            return;
        }
    }
    Qisha.PosX += cos(dir) * dist;
    Qisha.PosY += sin(dir) * dist;
    
}
*/
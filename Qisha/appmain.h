#pragma once
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <memory>
#include <cmath>

using Clock = std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::duration_cast;
//using std::chrono::milliseconds;
typedef std::chrono::milliseconds ms;
using namespace std::literals::chrono_literals;
using std::string;
using std::vector;

struct mainchar {
	//to scale
	//const float minSpd = 0.5;
	//const float maxSpd = 50;	
	int health;
	float Scale; //from 1-100
	ms ScaleCooldown = ms(2000);//in ms
	int BaseSize;//size
	float BaseSpd;
	float Jmpheight;

	int PosX,PosY;
	float Spd;

	int AtkRng;
	ms AtkCooldown = ms(500);//in ms;
	time_point<Clock> LastAtk;

	Color CharCol;
};

struct projectile {
	int PosX, PosY;
	int Size = 15;
	float BaseSpd = 10;
	float BaseAtk = 10;
	float Spd;
	float Atk;
	float Dir;

};

enum hiteffect {
	STOP,
};

struct object {
	Rectangle disp;
	Rectangle hitbox;
	hiteffect eff = STOP;
};

class appmain
{
private:
	mainchar Qisha;
	object floor;

	float gravity;
	const int screenHeight = 1000;
	const int screenWidth = 1800;
	const Color BkgCol = WHITE;
	std::vector<std::shared_ptr<projectile>> projs;
	std::vector<std::shared_ptr<object>> obj;

	bool ifTitle = true;

private:
	void init();
	void title();
	void loop();

	void moveChar(float dist, float dir); //to check for collision detection
public:
	void run();
};


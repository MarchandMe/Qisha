#pragma once
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <chrono>
#include <string>

using Clock = std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::duration_cast;
//using std::chrono::milliseconds;
typedef std::chrono::milliseconds ms;
using namespace std::literals::chrono_literals;
using std::string;

struct mainchar {
	//to scale
	//const float minSpd = 0.5;
	//const float maxSpd = 50;	
	int health;
	float Scale; //from 1-100
	ms ScaleCooldown = ms(2000);//in ms
	int BaseSize;//size
	float BaseSpd;

	int PosX,PosY;
	float Spd;

	int AtkRng;
	ms AtkCooldown = ms(500);//in ms;
	time_point<Clock> LastAtk;

	Color CharCol;
};

class appmain
{
private:
	mainchar Qisha;
	const int screenHeight = 1000;
	const int screenWidth = 1800;
	const Color BkgCol = WHITE;
public:
	void run();
	void init();
	void loop();
};


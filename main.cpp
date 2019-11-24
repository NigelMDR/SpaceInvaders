/**
 *
 * 	By: Nigel
 *	ECE 231 c++
 *	First Written on November 16
 *
* */


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <stdbool.h>
#include <iostream>
#include <math.h>

extern "C"
{
#include "gfx.h"
#include "drawShapes.h"

/** 
 *	drawCharacters.h and drawCharacters.c
 *	by: Shuyang Li and Adam Goins
 *	for CSE 20211
 *	First written on November 20, 2013
 **/
#include "drawCharacters.h"
}

#define CENTER_X 325
#define CENTER_Y 325

#define MIN_GRID_WIDTH 50   //Including boundary walls.
#define MIN_GRID_HEIGHT 50  //Including boundary walls.
#define MAX_GRID_WIDTH 600  //Including boundary walls.
#define MAX_GRID_HEIGHT 600  //Including boundray walls.

#define WINDOW_HEIGHT 650
#define WINDOW_WIDTH 650

#define SPACE_MOVE 20
#define CHAR_SIZE 50

bool debug = false;
void openGraphics();
void drawString(int x, int y, const std::string& str); 
void draw_circle(int xc, int yc, int radius);

class ObjStruct
{
	std::string _Name;
	size_t _X;
	size_t _Y;
	size_t _H; // length
	size_t _T; // Theta

	public:

	ObjStruct( std::string name, size_t x, size_t y, size_t h, size_t t )
	{
		_Name = name;
		_X = x;
		_Y = y;
		_H = h;
		_T = t;
	}
	// updates Onject by redrawing said object
	void updateObject()
	{
		if(_Name == "PLAYER")
		{
			gfx_clear();
			gfx_color(250,0,250);
			ds_Triangle(_X,_Y,CHAR_SIZE);
			gfx_color(0,250,255);
			ds_TriangleAngle(_X,_Y,CHAR_SIZE-3,-390);
			gfx_color(0,250,255);
			ds_TriangleAngle(_X,_Y,CHAR_SIZE-3,390);

		}
		if(_Name == "BULLET")
		{
			ds_Square(_X,_Y,9);
		}
		if(_Name == "ALIEN")
		{
			_T +=15;
			_X +=15;
			if(!inRange(_X))
			{
				_X = 55;
			}
			ds_SquareAngle(_X,_Y,_H + 30,_T);
			DrawAlien();
		}
	}

	void DrawPLayer(int x, int y) // use this to initially draw PLAYER
	{
		ds_Triangle(x,y,CHAR_SIZE);
	}
	
	void DrawAlien() // use this to initially draw ALIEN
	{
		gfx_color(255, 255, 0);
		draw_circle(_X, _Y, _H);
	
		gfx_color(0, 255, 0);
		draw_circle(_X, _Y, _H - 5);
	
		gfx_color(0, 255, 255);
		draw_circle(_X, _Y, _H - 10);
	
		gfx_color(255, 0, 255);
		draw_circle(_X, _Y, _H - 15);
	}
	
	bool inRange( size_t coordinates) // SET WALL
	{
		if( coordinates > MAX_GRID_WIDTH || coordinates > MAX_GRID_HEIGHT
		 || coordinates < MIN_GRID_WIDTH || coordinates < MIN_GRID_HEIGHT)
			return false;
		return true;
	}

	void MoveDown()
	{
		if( inRange(_Y + SPACE_MOVE) )
		{
			_Y += SPACE_MOVE;
			updateObject();
		}
	}
	void MoveUp()  // swap UP & DOWN for inverted controls
	{
		if( inRange(_Y - SPACE_MOVE) )
		{
			_Y -= SPACE_MOVE;
			updateObject();
		}
	}
	void MoveLeft()
	{
		if( inRange(_X - SPACE_MOVE) )
		{	
			_X -= SPACE_MOVE;
			updateObject();

		}
	}
	void MoveRight()
	{
		if( inRange(_X + SPACE_MOVE) )
		{
			_X += SPACE_MOVE;
			updateObject();
		}
	}
	size_t getX()
	{
		return _X;
	}
	size_t getY()
	{
		return _Y;
	}
};

ObjStruct Player = {"PLAYER", 325,550,50,0};
ObjStruct Bullet = {"BULLET", 325,325,3,0};
ObjStruct Alien = {"ALIEN", 325,100,20,0};

void draw_polygon(int *x, int *y, int n, bool closed = false)
{
	for (int i = 0; i < n - 1; i ++)
		gfx_line(x[i],y[i],x[i+1],y[i+1]);
	if (closed)
		gfx_line(x[0],y[0],x[n-1],y[n-1]);
}
void draw_circle(int xc, int yc, int radius)
{
	int x[18];
	int y[18];
	for (int i = 0; i < 18; i++)
	{
		double angle = i*20.0*3.14159/180.0;
		x[i] = xc + cos(angle)*radius;
		y[i] = yc + sin(angle)*radius;
	}

	draw_polygon(x, y, 18, true);
}

/*
bool isDead()
{
	
}
*/

void drawGameMenu()
{
	ds_Square(CENTER_X,CENTER_Y,625);
	ds_Square(CENTER_X,CENTER_Y,594);
}

void drawString(int x, int y, const std::string& str) 
{
        int width = 50;

        // shadowing the outer x
        int locx = x;

        for ( int i = 0; str[i] != 0; i++) 
	{
                dc_drawCharacter(locx, y, str[i]);
                locx += width;
                locx += width / 5;
        }
}


/*
   =============
   main function
   =============
*/

int main() 
{
//	ObjStruct Player = {"PLAYER", 325,325,50,0};
//	ObjStruct Bullet = {"BULLET", 325,325,3,0};
	openGraphics();
	drawGameMenu();
	while(true)
	{
		drawGameMenu();
		if (gfx_event_waiting())
		{
		
			Player.updateObject();
	                int button = gfx_wait();
			std::cout << button << std::endl;
                        // up arrow
                        if (button == 82 || button == 65362) Player.MoveUp();// Player.updateObject(); WORKS
                        // down arrow
                        if (button == 84 || button == 65364) Player.MoveDown();// Player.updateObject();
                        // left arroow
                        if (button == 81 || button == 65361) Player.MoveLeft();// Player.updateObject();
                        // right arroow
			if (button == 83 || button == 65363) Player.MoveRight();// Player.updateObject(); WORKS
			// Spacebar 
			if (button == 32 || button == 65363) 
			Bullet = {"BULLET",Player.getX(),Player.getY(),50,0};
				Bullet.MoveUp();
			Alien.updateObject();
		}
	}
}

void openGraphics()
{
	gfx_open(WINDOW_WIDTH, WINDOW_HEIGHT, " Space Invaders ");
}

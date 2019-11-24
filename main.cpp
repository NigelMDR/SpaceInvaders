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

// NEEDS Work
#define MIN_GRID_WIDTH 50   //Including boundary walls.okay
#define MIN_GRID_HEIGHT 54  //Including boundary walls.
#define MAX_GRID_WIDTH 600  //Including boundary walls.okay
#define MAX_GRID_HEIGHT 600  //Including boundray walls.

#define WINDOW_HEIGHT 650
#define WINDOW_WIDTH 650

#define SPACE_MOVE 15
#define CHAR_SIZE 50

//#define WINDOW_HEIGHT 800 
//#define WINDOW_WIDTH 800 
#define MAX_ITERATIONS 100

bool debug = false;
void openGraphics();
void drawString(int x, int y, const std::string& str); 
void draw_circle(int xc, int yc, int radius);
void DrawMandelbrot();

class ObjStruct
{
	std::string _Name;
	size_t _X;
	size_t _Y;
	size_t _H; // length
	size_t _T; // Theta

	public:
	bool _Life;

	ObjStruct( std::string name, size_t x, size_t y, size_t h, size_t t )
	{
		_Name = name;
		_X = x;
		_Y = y;
		_H = h;
		_T = t;
		_Life = true;
	}
	// MUST ADD!
/*
	~ObjStruct()
	{
		
	}
*/
	// updates Onject by redrawing said object
	void updateObject()
	{
		if(!_Life)
		{
			return;
		}

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
		if(_Name == "ALIEN_B")
		{
			_Y +=15;
			ds_Square(_X,_Y,1);
			ds_Square(_X,_Y,2);
			ds_Square(_X,_Y,3);
			ds_Square(_X,_Y,4);
			ds_Square(_X,_Y,5);
		}
		if(_Name == "BULLET")
		{
			_Y -=15;
			ds_Square(_X,_Y,1);
			ds_Square(_X,_Y,2);
			ds_Square(_X,_Y,3);
			ds_Square(_X,_Y,4);
			ds_Square(_X,_Y,5);
		}
		if(_Name == "ALIEN")
		{
			if(!_Life)
			{
				clear();
				return;
			}

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
			if(_Name == "PLAYER")
			{
				if(_Y  < 400)
				{
					return;
				}
			}
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

	void clear()
	{
		gfx_clear();
	}

	bool isDead(class ObjStruct& Bullet)
	{
		size_t BulletMin_X = Bullet.getX() - 2;
		size_t BulletMax_X = Bullet.getX() + 2;
		size_t BulletMin_Y = Bullet.getY() - 2;
		size_t BulletMax_Y = Bullet.getY() + 2;
		
		size_t ObjMin_X = _X - 20;
		size_t ObjMax_X = _X + 20;
		size_t ObjMin_Y = _Y - 20;
		size_t ObjMax_Y = _Y + 20;

		if( BulletMin_X > ObjMin_X && BulletMin_X < ObjMax_X && BulletMax_X < ObjMax_X && BulletMax_X > ObjMin_X &&
	   	    BulletMin_Y > ObjMin_Y && BulletMin_Y < ObjMax_Y && BulletMax_Y < ObjMax_Y && BulletMax_Y > ObjMin_Y)
		{
			std::cout << " I'M DEAD :  " << _Name <<  std::endl;
			_Life = false;
			return true;
		}
		return false;
	}

};

ObjStruct Player = {"PLAYER", 325,550,50,0};
ObjStruct Bullet = {"BULLET", 325,562,3,0};
ObjStruct Alien = {"ALIEN", 325,100,20,0};
ObjStruct Alien2 = {"ALIEN", 225,100,20,0};
ObjStruct Alien3 = {"ALIEN", 425,100,20,0};
ObjStruct AlienBullet = {"ALIEN_B",0,0,50,0};
ObjStruct AlienBullet2 = {"ALIEN_B",0,0,50,0};
ObjStruct AlienBullet3 = {"ALIEN_B",0,0,50,0};

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

bool isDead(class ObjStruct& Obj, class ObjStruct& Bullet)
{
	size_t BulletMin_X = Bullet.getX() - 2;
	size_t BulletMax_X = Bullet.getX() + 2;
	size_t BulletMin_Y = Bullet.getY() - 2;
	size_t BulletMax_Y = Bullet.getY() + 2;
	
	size_t ObjMin_X = Obj.getX() - 20;
	size_t ObjMax_X = Obj.getX() + 20;
	size_t ObjMin_Y = Obj.getY() - 20;
	size_t ObjMax_Y = Obj.getY() + 20;

	if( BulletMin_X > ObjMin_X && BulletMin_X < ObjMax_X && BulletMax_X < ObjMax_X && BulletMax_X > ObjMin_X &&
   	    BulletMin_Y > ObjMin_Y && BulletMin_Y < ObjMax_Y && BulletMax_Y < ObjMax_Y && BulletMax_Y > ObjMin_Y)
	{
		std::cout << " I'M DEAD " << std::endl;
		Obj._Life = false;
		return true;
	}
	return false;
}

void drawString(int x, int y, char str[]) 
{
        int width = 50;

        // shadowing the outer x
        int locx = x;
        for ( int n = 0; str[n] != 0; n++) 
	{
		dc_drawCharacter(locx, y, str[n]);
                locx += width;
                locx += width / 5;
        }
}

void drawGameMenu()
{
	DrawMandelbrot();
	char space[14] = "SPACE";
	gfx_color(250,250,250);
	drawString(150,200,space);	

	char invaders[14] = "IVADERS";
	gfx_color(250,250,250);
	drawString(150,350,invaders);	

	gfx_color(250, 250, 250);
	ds_Square(CENTER_X,CENTER_Y,625);
	gfx_color(250, 250, 250);
	ds_Square(CENTER_X,CENTER_Y,594);
}

void showGame()
{
	gfx_color(250, 250, 250);
	ds_Square(CENTER_X,CENTER_Y,625);
	gfx_color(250, 250, 250);
	ds_Square(CENTER_X,CENTER_Y,594);
}

bool GameOver()
{
	if( Alien._Life || Alien2._Life || Alien3._Life )
		return false;
	char test[10] = "WINNER";
	drawString(CENTER_X,CENTER_Y,test);
	return true;
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
	size_t n = 2.5;
	n += 35.34;
	std::cout << n << std::endl;
	openGraphics();
	drawGameMenu();

	while(true)
	{
		showGame();	
	//	drawGameMenu();
		if (gfx_event_waiting())
		{
			Player.updateObject();
	                int button = gfx_wait();
			
			std::cout << button << std::endl;
                        // up arrow
                        if (button == 82 || button == 65362) Player.MoveUp();// Player.updateObject(); 
                        // down arrow
                        if (button == 84 || button == 65364) Player.MoveDown();// Player.updateObject();
                        // left arroow
                        if (button == 81 || button == 65361) Player.MoveLeft();// Player.updateObject();
                        // right arroow
			if (button == 83 || button == 65363) Player.MoveRight();// Player.updateObject(); 
			// Spacebar 
			if (button == 32 || button == 65363) 
			Bullet = {"BULLET",Player.getX(),Player.getY(),50,0};
				Bullet.updateObject();
			if(!Alien.isDead(Bullet))
			{
				Alien.updateObject();
				if (button == 32 && Alien._Life) 
				AlienBullet = {"ALIEN_B",Alien.getX(),Alien.getY(),50,0};
					AlienBullet.updateObject();
			}
			if(!Alien2.isDead(Bullet))
			{
				Alien2.updateObject();
				if (button == 32 && Alien2._Life) 
				AlienBullet2 = {"ALIEN_B",Alien2.getX(),Alien2.getY(),50,0};
					AlienBullet2.updateObject();
			}
			if(!Alien3.isDead(Bullet))
			{
				Alien3.updateObject();
				if (button == 32 && Alien3._Life) 
				AlienBullet3 = {"ALIEN_B",Alien3.getX(),Alien3.getY(),50,0};
					AlienBullet3.updateObject();
			}
			if( !Alien._Life && !Alien2._Life && !Alien3._Life )
			{
				char winner[10] = "WINNER";
				gfx_color(23,500,200);
				drawString(150,200,winner);
			}
			if( Player.isDead(AlienBullet))
			{
				char loser[10] = "LOSER";
				gfx_color(23,500,200);
				drawString(150,200,loser);
				usleep(1000000);
				//if (button == 'x' || button == 'q')
				//		break;
			}
				
		}
	}

}

void openGraphics()
{
	gfx_open(WINDOW_WIDTH, WINDOW_HEIGHT, " Space Invaders ");
}

void DrawMandelbrot()
{
	for (int x = 0; x < WINDOW_WIDTH; x ++) 
	{ 
		for(int y = 0; y < WINDOW_HEIGHT; y++) 
		{ 
			int n = 0; int z = 0; double a = 0; double b = 0; 
			a = ((x - 400) * .005); b = ((y - 400) * .005); 
			double ca = a; double cb = b; 
			while (n < MAX_ITERATIONS) 
			{ 
				double aa = (a*a) - (b*b); 
				double bb = 2*a*b; a = aa + ca; 
				b = bb + cb; 
				if (abs(a+b) > 16.0) 
				{ break; } 
				n++; 
			} 
			double red = n*n*n % 255; double green = (n * 3/2) % 256;    // change color 
			double blue = n / 2 % 255; 
			gfx_color(red, green, blue); gfx_point(x,y); 
		} 
	}
}

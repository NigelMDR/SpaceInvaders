/**
 *
 * 	By: Nigel
 *	ECE 231 c++
 *	First Written on November 16
 *
* */

#include <vector>
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

// #define LIFE_COUNT 3

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
	ObjStruct()
	{
		_Life = true;
	}

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
		if(!_Life)  // swaped with botom if statement
		{
			return;
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

		if(_Name == "PLAYER")
		{
			gfx_clear();
			DrawPLayer();
		}
		if(_Name == "ALIEN_B")
		{
			_Y +=15;
			gfx_color(255,100,0);
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

			//_T +=15;
			_X +=15;
			if(!inRange(_X))
			{
				_X = 55;
			}
			//ds_SquareAngle(_X,_Y,_H + 30,_T);
			DrawAlien();
		}
	}

	void DrawPLayer() // use this to initially draw PLAYER
	{
			gfx_color(0,250,255);
			ds_TriangleAngle(_X,_Y,CHAR_SIZE-3,-390);
			gfx_color(0,250,255);
			ds_TriangleAngle(_X,_Y,CHAR_SIZE-15.6,-390);
			gfx_color(0,250,255);
			ds_TriangleAngle(_X,_Y,CHAR_SIZE-15.6*2,-390);
			
			gfx_color(0,255,255);
			ds_TriangleAngle(_X,_Y,CHAR_SIZE-3,390);
			gfx_color(0,255,255);
			ds_TriangleAngle(_X,_Y,CHAR_SIZE-15.6,390);
			gfx_color(0,255,255);
			ds_TriangleAngle(_X,_Y,CHAR_SIZE-15.6*2,390);
			
			gfx_color(255,0,0);
			ds_Triangle(_X,_Y,CHAR_SIZE);
			
			gfx_color(255,0,0);
			ds_Triangle(_X,_Y,CHAR_SIZE - 5);
			gfx_color(255,0,0);
			ds_Triangle(_X,_Y,CHAR_SIZE - 5*2);
			gfx_color(255,0,0);
			ds_Triangle(_X,_Y,CHAR_SIZE - 5*3);
			gfx_color(255,0,0);
			ds_Triangle(_X,_Y,CHAR_SIZE - 5*4);
			gfx_color(255,0,0);
			ds_Triangle(_X,_Y,CHAR_SIZE - 5*5);
			gfx_color(250,0,0);
			ds_Triangle(_X,_Y,CHAR_SIZE - 5*6);
			gfx_color(250,0,0);
			ds_Triangle(_X,_Y,CHAR_SIZE - 5*7);
			gfx_color(255,0,0);
			ds_Triangle(_X,_Y,CHAR_SIZE - 5*8);
			gfx_color(0,255,255);
			ds_Triangle(_X,_Y,CHAR_SIZE - 5*9);
			
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
				if(_Y  < 580)
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
        int width = 50;  // WINNER, LOSER, NAME

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

	char invaders[14] = "INVADERS";
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
	ds_Square(CENTER_X,CENTER_Y,635);
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
//

	std::vector<ObjStruct> AliensBullets(100);
	ObjStruct AlienBullet = {"ALIEN_B",0,0,50,0};
	ObjStruct AlienBullet1 = {"ALIEN_B",0,0,50,0};
	ObjStruct AlienBullet2 = {"ALIEN_B",0,0,50,0};
	ObjStruct AlienBullet3 = {"ALIEN_B",0,0,50,0};
	ObjStruct AlienBullet4 = {"ALIEN_B",0,0,50,0};
	ObjStruct AlienBullet5 = {"ALIEN_B",0,0,50,0};
	ObjStruct AlienBullet6 = {"ALIEN_B",0,0,50,0};
	ObjStruct AlienBullet7 = {"ALIEN_B",0,0,50,0};
	
	AliensBullets.push_back(AlienBullet);
	AliensBullets.push_back(AlienBullet1);
	AliensBullets.push_back(AlienBullet2);
	AliensBullets.push_back(AlienBullet3);
	AliensBullets.push_back(AlienBullet4);
	AliensBullets.push_back(AlienBullet5);
	AliensBullets.push_back(AlienBullet6);
	AliensBullets.push_back(AlienBullet7);

	std::vector<ObjStruct> Aliens(100);
	ObjStruct Alien = {"ALIEN", WINDOW_WIDTH/2,100,20,0};
	ObjStruct Alien2 = {"ALIEN", WINDOW_WIDTH/2 + 75,100,20,0};
	ObjStruct Alien3 = {"ALIEN", WINDOW_WIDTH/2 - 75,100,20,0};
	
	ObjStruct Alien4 = {"ALIEN", WINDOW_WIDTH/2 + 75*2,100,20,0};
	ObjStruct Alien5 = {"ALIEN", WINDOW_WIDTH/2 - 75*2,100,20,0};
	
	ObjStruct Alien6 = {"ALIEN", WINDOW_WIDTH/2 - 75*3,100,20,0};
	ObjStruct Alien7 = {"ALIEN", WINDOW_WIDTH/2 + 75*3,100,20,0};
	
	Aliens.push_back(Alien);
	Aliens.push_back(Alien2);
	Aliens.push_back(Alien3);
	Aliens.push_back(Alien4);
	Aliens.push_back(Alien5);
	Aliens.push_back(Alien6);
	Aliens.push_back(Alien7);


	std::vector<ObjStruct> Bullets02(100);
	ObjStruct Bullet1 = {"BULLET", 5,6,7,0};
	ObjStruct Bullet2 = {"BULLET", 0,0,0,0};
	ObjStruct Bullet3 = {"BULLET", 0,0,0,0};
	ObjStruct Bullet4 = {"BULLET", 0,0,0,0};
	ObjStruct Bullet5 = {"BULLET", 0,0,0,0};
	ObjStruct Bullet6 = {"BULLET", 0,0,0,0};
	ObjStruct Bullet7 = {"BULLET", 0,0,0,0};
	ObjStruct Bullet8 = {"BULLET", 0,0,0,0};
	ObjStruct Bullet9 = {"BULLET", 0,0,0,0};
	ObjStruct Bullet10 = {"BULLET", 0,0,0,0};
	ObjStruct Bullet11 = {"BULLET", 0,0,0,0};
	ObjStruct Bullet12 = {"BULLET", 0,0,0,0};
	ObjStruct Bullet13 = {"BULLET", 0,0,0,0};
	ObjStruct Bullet14 = {"BULLET", 0,0,0,0};
	ObjStruct Bullet15 = {"BULLET", 0,0,0,0};
	ObjStruct Bullet16 = {"BULLET", 0,0,0,0};
	ObjStruct Bullet17 = {"BULLET", 0,0,0,0};
	ObjStruct Bullet18 = {"BULLET", 0,0,0,0};
	ObjStruct Bullet19 = {"BULLET", 0,0,0,0};

	Bullets02.push_back(Bullet1);
	Bullets02.push_back(Bullet2);
	Bullets02.push_back(Bullet3);
	Bullets02.push_back(Bullet4);
	Bullets02.push_back(Bullet5);
	Bullets02.push_back(Bullet6);
	Bullets02.push_back(Bullet7);
	Bullets02.push_back(Bullet8);
	Bullets02.push_back(Bullet9);
	Bullets02.push_back(Bullet10);
	Bullets02.push_back(Bullet11);
	Bullets02.push_back(Bullet12);
	Bullets02.push_back(Bullet13);
	Bullets02.push_back(Bullet14);
	Bullets02.push_back(Bullet15);
	Bullets02.push_back(Bullet16);
	Bullets02.push_back(Bullet17);
	Bullets02.push_back(Bullet18);
	Bullets02.push_back(Bullet19);

	size_t n = 2.5;
	n += 35.34;
	int BulletNum = 0;
	int LIFE_COUNT = 3;  
	std::cout << n << std::endl;
	openGraphics();
	drawGameMenu();
	int Count = 0;

	Alien.DrawAlien();
	Alien2.DrawAlien();
	Alien3.DrawAlien();
	Alien4.DrawAlien();
	Alien5.DrawAlien();
	Alien6.DrawAlien();
	Alien7.DrawAlien();

	while(true)
	{
		if(BulletNum == 19)
			BulletNum = 0;
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
			{
				Bullets02[BulletNum] = {"BULLET",Player.getX(),Player.getY(),50,0};
				BulletNum ++;
			}
			//Bullets02[BulletNum-10].MoveUp();
			//Bullets02[BulletNum-9].MoveUp();
			//Bullets02[BulletNum-8].MoveUp();
			//Bullets02[BulletNum-7].MoveUp();
			//Bullets02[BulletNum-6].MoveUp();
			//Bullets02[BulletNum-5].MoveUp();
			//Bullets02[BulletNum-4].MoveUp();  // controll NUMBER of BUllets that player has.
			//Bullets02[BulletNum-3].MoveUp();
			Bullets02[BulletNum-2].MoveUp();
			Bullets02[BulletNum-1].MoveUp();
			Bullets02[BulletNum].MoveUp();

			std::cout<< BulletNum << std::endl;
			
			for(int num = 0; num < Bullets02.size(); num++)
				Alien.isDead(Bullets02[num]);
			for(int num = 0; num < Bullets02.size(); num++)
				Alien2.isDead(Bullets02[num]);
			for(int num = 0; num < Bullets02.size(); num++)
				Alien3.isDead(Bullets02[num]);
		
			// Collision Detection and Alien Movement 
			for(int NUM = 0; NUM < Aliens.size(); NUM++)
			{
				Aliens[NUM].updateObject();
				if(Aliens[NUM]._Life && Count == 5)
					AliensBullets[NUM] = {"ALIEN_B",Aliens[NUM].getX(),Aliens[NUM].getY(),50,0};
				for(int SEC = 0; SEC < Bullets02.size(); SEC++)
				{
					Aliens[NUM].isDead(Bullets02[SEC]);	
					// should delete the bullet if it hits its target add later no
				}	
				AliensBullets[NUM].updateObject();

			}
			/*
			for(int NUM = 0; NUM < Aliens.size() && NUM < Bullets02.size(); NUM++)
			{
				for(int SEC = 0; SEC < Bullets02.size(); SEC++)
				{
					Aliens[NUM].isDead(Bullets02[SEC]);
				}
			}
			*/
			

			/*
			if(!Alien.isDead(Bullet))
			{
				Alien.updateObject();
				if (Alien._Life && Count == 15) 
				AlienBullet = {"ALIEN_B",Alien.getX(),Alien.getY(),50,0};
					AlienBullet.updateObject();
			}
			if(!Alien2.isDead(Bullet))
			{
				Alien2.updateObject();
				if (Alien2._Life && Count == 15) 
				AlienBullet2 = {"ALIEN_B",Alien2.getX(),Alien2.getY(),50,0};
					AlienBullet2.updateObject();
			}
			if(!Alien3.isDead(Bullet))
			{
				Alien3.updateObject();
				if (Alien3._Life && Count == 15) 
				AlienBullet3 = {"ALIEN_B",Alien3.getX(),Alien3.getY(),50,0};
					AlienBullet3.updateObject();
			}
			*/
			int AllDead_Y_N = 0;
			for(int NUM = 0; NUM < Aliens.size(); NUM ++)
			{
				if(!Aliens[NUM]._Life)
				{
					AllDead_Y_N ++;
					std::cout << "    " <<  AllDead_Y_N << " NUM of dead Aliens " <<std::endl;
					if(AllDead_Y_N == 7)  // 7 is the number of Aliens Size is 107.
					{
						char winner[10] = "WINNER";
						gfx_color(23,500,200);
						drawString(150,200,winner);
					}
				}
			}
			
			for(int NUM = 0; NUM < AliensBullets.size(); NUM++)
			{
				Player.isDead(AliensBullets[NUM]);
			}

			/*
			Player.isDead(AlienBullet);
			Player.isDead(AlienBullet2);
			Player.isDead(AlienBullet3);
			*/
			if(!Player._Life)
			{
				LIFE_COUNT --;
				if(LIFE_COUNT == 0)
				{
					char loser[10] = "LOSER";
					gfx_color(23,500,200);
					drawString(150,200,loser);
					int button = gfx_wait();
					if (button == 'x' || button == 'q')
							break;
					usleep(9999999); // if Player Lost He can NO longer die
			
				}
				else 
					Player._Life = true;
			}

			if(Count == 32)    // Alien Bullet Time
				Count = 0;
			Count ++;
				
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

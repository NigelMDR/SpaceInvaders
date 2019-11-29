/**
 *
 * 	By: Nigel
 *	ECE 231 c++
 *	First Written on November 16
 *	Game has been Updated and is working 
 *	Have some issues with Memory allocation
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
#define MIN_GRID_HEIGHT 54  //Including boundary walls.okay
#define MAX_GRID_WIDTH 600  //Including boundary walls.okay
#define MAX_GRID_HEIGHT 600  //Including boundray walls.okay

#define WINDOW_HEIGHT 650
#define WINDOW_WIDTH 650

#define SPACE_MOVE 15
#define CHAR_SIZE 50

// #define LIFE_COUNT 3

#define MAX_ITERATIONS 100

bool debug = false;
void openGraphics();
void drawString(int x, int y, const std::string& str); 
void draw_circle(int xc, int yc, int radius);
void DrawMandelbrot();
void draw_polygon(int *x, int *y, int n, bool);
void draw_circle(int xc, int yc, int radius);
bool isDead(class ObjStruct& Obj, class ObjStruct& Bullet);
void drawString(int x, int y, char str[]);
void drawGameMenu();
void showGame();
bool GameOver();
void GameInstructions();

#include "Bullet.h"
#include "Player.h"
#include "Alien.h"


/*
   =============
   main function
   =============
*/

int main() 
{
	Player Player = {"PLAYER", 325,500,50,0};
	
	std::vector<Bullet> AliensBullets(0);
	Bullet AlienBullet = {"ALIEN_B",0,0,50,0};
	Bullet AlienBullet1 = {"ALIEN_B",0,0,50,0};
	Bullet AlienBullet2 = {"ALIEN_B",0,0,50,0};
	Bullet AlienBullet3 = {"ALIEN_B",0,0,50,0};
	Bullet AlienBullet4 = {"ALIEN_B",0,0,50,0};
	Bullet AlienBullet5 = {"ALIEN_B",0,0,50,0};
	Bullet AlienBullet6 = {"ALIEN_B",0,0,50,0};
	Bullet AlienBullet7 = {"ALIEN_B",0,0,50,0};
	
	AliensBullets.push_back(AlienBullet);
	AliensBullets.push_back(AlienBullet1);
	AliensBullets.push_back(AlienBullet2);
	AliensBullets.push_back(AlienBullet3);
	AliensBullets.push_back(AlienBullet4);
	AliensBullets.push_back(AlienBullet5);
	AliensBullets.push_back(AlienBullet6);
	AliensBullets.push_back(AlienBullet7);

	std::vector<Alien> Aliens(0);
	Alien Alien1 = {"ALIEN", WINDOW_WIDTH/2,100,20,0};
	Alien Alien2 = {"ALIEN", WINDOW_WIDTH/2 + 75,100,20,0};
	Alien Alien3 = {"ALIEN", WINDOW_WIDTH/2 - 75,100,20,0};
	
	Alien Alien4 = {"ALIEN", WINDOW_WIDTH/2 + 75*2,100,20,0};
	Alien Alien5 = {"ALIEN", WINDOW_WIDTH/2 - 75*2,100,20,0};
	
	Alien Alien6 = {"ALIEN", WINDOW_WIDTH/2 - 75*3,100,20,0};
	Alien Alien7 = {"ALIEN", WINDOW_WIDTH/2 + 75*3,100,20,0};
	
	Aliens.push_back(Alien1);
	Aliens.push_back(Alien2);
	Aliens.push_back(Alien3);
	Aliens.push_back(Alien4);
	Aliens.push_back(Alien5);
	Aliens.push_back(Alien6);
	Aliens.push_back(Alien7);

	std::vector<Bullet>  Bullets02(0);
	Bullet Bullet1 = {"BULLET", 5,6,7,0};
	Bullet Bullet2 = {"BULLET", 0,0,0,0};
	Bullet Bullet3 = {"BULLET", 0,0,0,0};
	Bullet Bullet4 = {"BULLET", 0,0,0,0};
	Bullet Bullet5 = {"BULLET", 0,0,0,0};
	Bullet Bullet6 = {"BULLET", 0,0,0,0};
	Bullet Bullet7 = {"BULLET", 0,0,0,0};
	Bullet Bullet8 = {"BULLET", 0,0,0,0};
	Bullet Bullet9 = {"BULLET", 0,0,0,0};
	Bullet Bullet10 = {"BULLET", 0,0,0,0};
	Bullet Bullet11 = {"BULLET", 0,0,0,0};
	Bullet Bullet12 = {"BULLET", 0,0,0,0};
	Bullet Bullet13 = {"BULLET", 0,0,0,0};
	Bullet Bullet14 = {"BULLET", 0,0,0,0};
	Bullet Bullet15 = {"BULLET", 0,0,0,0};
	Bullet Bullet16 = {"BULLET", 0,0,0,0};
	Bullet Bullet17 = {"BULLET", 0,0,0,0};
	Bullet Bullet18 = {"BULLET", 0,0,0,0};
	Bullet Bullet19 = {"BULLET", 0,0,0,0};

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
	if(debug)
		std::cout << n << std::endl;
	//GameInstructions();
	openGraphics();
	drawGameMenu();
	int Count = 0;
	
	Alien1.DrawAlien();
	Alien2.DrawAlien();
	Alien3.DrawAlien();
	Alien4.DrawAlien();
	Alien5.DrawAlien();
	Alien6.DrawAlien();
	Alien7.DrawAlien();
	
	int playerOp = gfx_wait();
		

/**
 *
 *	Looking Good Needs, Game Menu only shows up for 10sec
 *
 **/
	while(true)
	{
		if (playerOp == 113)
			break;
		
		if(BulletNum == 19)
			BulletNum = 0;
		showGame();	
		if (gfx_event_waiting())
		{
			Player.updateObject();
	                int button = gfx_wait();
			if(debug)	
				std::cout << button << std::endl;
			if (button == 114 || button == 113)
				break;
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

		}

		else
		{

			gfx_clear();
			if(debug)
				std::cout<< BulletNum << std::endl;
			
			Player.updateObject();
			//Bullets02[BulletNum-10].MoveUp();
			//Bullets02[BulletNum-9].MoveUp();
			//Bullets02[BulletNum-8].MoveUp();
			//Bullets02[BulletNum-7].MoveUp();
			//Bullets02[BulletNum-6].MoveUp();
			//Bullets02[BulletNum-5].MoveUp();
			//Bullets02[BulletNum-4].MoveUp();  // control NUMBER of BUllets that player has.
			//Bullets02[BulletNum-3].MoveUp();
			Bullets02[BulletNum-2].MoveUp();
			Bullets02[BulletNum-1].MoveUp();
			Bullets02[BulletNum].MoveUp();
			
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
			int AllDead_Y_N = 0;
			for(int NUM = 0; NUM < Aliens.size(); NUM ++)
			{
				if(!Aliens[NUM]._Life)
				{
					AllDead_Y_N ++;
					if(debug)
						std::cout << "    " <<  AllDead_Y_N << " NUM of dead Aliens " <<std::endl;
					if(AllDead_Y_N == 7)  // 7 is the number of Aliens Size is 107.
					{
						char winner[10] = "WINNER";
						gfx_color(23,500,200);
						drawString(150,200,winner);
						int BUTTON = gfx_wait();
						if (BUTTON == 114 || BUTTON == 113) // button q and w
						{
							break;
						}
						
						if (BUTTON == 99)   // button c
						{
							system("^C");  // doesn't Work, IDK how, should close window
							system("./main"); // opends a new Window
						}
					}
				}
			}
			
			for(int NUM = 0; NUM < AliensBullets.size(); NUM++)
			{
				Player.isDead(AliensBullets[NUM]);
			}
			usleep(10);
			if(!Player._Life)
			{
				LIFE_COUNT --;
				if(debug)
					std::cout << " NUM of Lives: " << LIFE_COUNT << std::endl;
				if(LIFE_COUNT <= 0)
				{
					char loser[10] = "Game Over";
					gfx_color(23,500,200);
					drawString(50,200,loser);
					int BUTTON = gfx_wait();
					if (BUTTON == 114 || BUTTON == 113) // button q and w
					{
						break;
					}
					
					if (BUTTON == 99)   // button c
					{
						system("^C");  // doesn't Work IDK how
						system("./main"); // opends a new Window
					}
					
					//usleep(9999999); // if Player Lost He can NO longer die
			
				}
				else 
					Player._Life = true;
			}
			
			if(Count == 32)    // Alien Bullet Time
				Count = 0;
			Count ++;	
			usleep(99999);
			
		}
		
	}

}

void GameInstructions()
{
/*
	std::cout << "\n \n	The object of the game is to shoot the invaders with your laser base while\n "
		     "	avoiding their shots and preventing an invasion. Eliminating the Invaders is\n "
		     "	a further objective and one that must be prioritized against your continued\n "
		     "	survival. Each game screen starts with one row of seven (7) invaders. The\n "
		     "	invaders randomly fire down the screen from the center of their bodies.\n\n\n " 
		     "	<< Don't fail your mission!\n"
		     "	<< Shoot using the Space Bar. Only two Bullets at any given time\n"
	             "	<< Move using the Arrow Key.\n \n \n";       
*/    

	std::cout  <<"\n\n" << "<<	Press any key to play \n"
			       "<<	Player has 3 Lives\n"
		               "<<	Press _c_ to Play Again \n"
		               "<<	Press _q_ to Quit at any point\n\n\n"; 

	gfx_color(255, 255, 255);
	ds_Rectangle(173, 555, 96, 185); // Play Hit Box
	ds_Rectangle(498, 555, 96, 185); // QUIT Hit Box

	char name[6] = "Space";
	char name2[9] = "Invaders";

	dc_updateHeight(90);
	gfx_color(51,255,255);
	dc_drawString(50,150,name);
	gfx_color(255,128,0);
	dc_drawString(48,148,name);
	gfx_color(255,255,255);
	dc_drawString(46,146,name);
	
	gfx_color(51,255,255);
	dc_drawString(180,250,name2);
	gfx_color(255,128,0);
	dc_drawString(178,248,name2);
	gfx_color(255,255,255);
	dc_drawString(178,246,name2);

	gfx_color(255,255,0);
	dc_updateHeight(75);
	char play[5] = "PLAY";
	char quit[5] = "QUIT";

	dc_drawString(88,515,play);
	gfx_color(51,255,255);
	dc_drawString(413,515,quit);
/*
	gfx_color(255,255,255);
	dc_updateHeight(25);
	char Writter[10] = "By Nigel";
	dc_drawString(50,40,Writter);
*/
	dc_updateHeight(50);
             
}
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
/*	char space[14] = "SPACE";
	gfx_color(250,250,250);
	drawString(150,200,space);	

	char invaders[14] = "INVADERS";
	gfx_color(250,250,250);
	drawString(150,350,invaders);	
*/
	GameInstructions();
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
/*
bool GameOver()
{
	if( Alien._Life || Alien2._Life || Alien3._Life )
		return false;
	char test[10] = "WINNER";
	drawString(CENTER_X,CENTER_Y,test);
	return true;
}
*/
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
			a = ((x - 400) * .01); b = ((y - 400) * .01); 
			double ca = a; double cb = b; 
			while (n < MAX_ITERATIONS) 
			{ 
				double aa = (a*a) - (b*b); 
				double bb = 2*a*b; a = aa - ca; 
				b = bb + cb; 
				if ( b*b + -1*a*a > 16.0) 
				{ break; } 
				n++; 
			} 
			double red = n*n*n % 255; double green = (n * 3/2) % 256;    // change color 
			double blue = n / 2 % 255; 
			gfx_color(red, green, blue); gfx_point(x,y); 
		} 
	}
}

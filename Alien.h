/**
 *
 * 	By: Nigel
 *	ECE 231 c++
 *	First Written on November 16
 *	Two Lives / 2 Bullets 
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

class Alien
{
	std::string _Name;
	size_t _X;
	size_t _Y;
	size_t _H; // length
	size_t _T; // Theta

	public:
	bool _Life;

	Alien()
	{
		_Life = true;
	}

	Alien( std::string name, size_t x, size_t y, size_t h, size_t t )
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
	~Alien()
	{
		
	}
*/

	// updates Onject by redrawing said object
	void updateObject()
	{
		if(!_Life)  // swaped with botom if statement
		{
			// clear();
			return;
		}

		_X += 15;
		if(!inRange(_X))
		{
			_X = 55;
		}
		DrawAlien();
		
	}
	
	void DrawAlien() 
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
	
	bool inRange( size_t coordinates) 
	{
		if( coordinates > MAX_GRID_WIDTH || coordinates > MAX_GRID_HEIGHT
		 || coordinates < MIN_GRID_WIDTH || coordinates < MIN_GRID_HEIGHT)
			return false;
		return true;
	}
/*	
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
*/
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

	bool isDead(class Alien& Bullet)
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
			if(debug)
				std::cout << " I'M DEAD :  " << _Name <<  std::endl;
			_Life = false;
			return true;
		}
		return false;
	}

	bool isDead(class Bullet& Bullet)
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
			if(debug)
				std::cout << " I'M DEAD :  " << _Name <<  std::endl;
			_Life = false;
			return true;
		}
		return false;
	}

};

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

class Bullet
{
	std::string _Name;
	size_t _X;
	size_t _Y;
	size_t _H; // length
	size_t _T; // Theta

	public:
	bool _Life;

	Bullet()
	{
		_Life = true;
	}

	Bullet( std::string name, size_t x, size_t y, size_t h, size_t t )
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
	~Bullet()
	{
		
	}
*/
	// updates Object by redrawing said object
	void updateObject()
	{
		if(!_Life)  // swaped with botom if statement
		{
			clear();
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
	}
	
	bool inRange( size_t coordinates) 
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
/*
	bool isDead(class Alien& obj)
	{
		size_t BulletMin_X = obj.getX() - 2;
		size_t BulletMax_X = obj.getX() + 2;
		size_t BulletMin_Y = obj.getY() - 2;
		size_t BulletMax_Y = obj.getY() + 2;
		
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
*/
};

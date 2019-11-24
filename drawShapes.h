/*
 *
 *
 *
 *
 *
 *
 */

#include <math.h>
#include "gfx.h"

void ds_Triangle(int x, int y, int len) 
{
	int theta = 0;
	gfx_line( x + (len/2)*cos(theta), y - (len/2)*sin(theta), x - (len/2)*sin(theta), y - (len/2)*cos(theta));
	gfx_line( x - (len/2)*sin(theta), y - (len/2)*cos(theta), x - (len/2)*cos(theta), y + (len/2)*sin(theta));
	gfx_line( x - (len/2)*cos(theta), y + (len/2)*sin(theta), x + (len/2)*cos(theta), y - (len/2)*sin(theta));
}

void ds_TriangleAngle(int x, int y, int len, int theta) 
{
	gfx_line( x + (len/2)*cos(theta), y - (len/2)*sin(theta), x - (len/2)*sin(theta), y - (len/2)*cos(theta));
	gfx_line( x - (len/2)*sin(theta), y - (len/2)*cos(theta), x - (len/2)*cos(theta), y + (len/2)*sin(theta));
	gfx_line( x - (len/2)*cos(theta), y + (len/2)*sin(theta), x + (len/2)*cos(theta), y - (len/2)*sin(theta));
}

void ds_Circle(int h, int k, int radii)
{
	float n = 0;
	while(n < 99999)
	{
		gfx_point( h + (radii * cos(n)) ,  k + (radii * sin(n)));
		n ++;
	}
}

// not working ! 
void ds_Arch(int h, int k, int radii, char *dir)
{
	float n = 0;
	while( n < 99999 )
	{
		gfx_point( h + (radii * cos(n)) ,  k + (radii * sin(n)));
		n ++;
	}
	
}

// draw square (x,y) coordinates center
void ds_Square(int x, int y, int len)
{
	int theta = 180;
	gfx_line( x + (len/2), y + (len/2), x + (len/2), y - (len/2));
	gfx_line( x + (len/2), y - (len/2), x - (len/2), y - (len/2));
	gfx_line( x - (len/2), y - (len/2), x - (len/2), y + (len/2));
	gfx_line( x - (len/2), y + (len/2), x + (len/2), y + (len/2));
}


void ds_Rhombus(int x, int y, int len)
{
	int theta = 0;
	gfx_line( x + (len/2)*sin(theta), y + (len/2)*cos(theta), x + (len/2)*cos(theta), y - (len/2)*sin(theta));
	gfx_line( x + (len/2)*cos(theta), y - (len/2)*sin(theta), x - (len/2)*sin(theta), y - (len/2)*cos(theta));
	gfx_line( x - (len/2)*sin(theta), y - (len/2)*cos(theta), x - (len/2)*cos(theta), y + (len/2)*sin(theta));
	gfx_line( x - (len/2)*cos(theta), y + (len/2)*sin(theta), x + (len/2)*sin(theta), y + (len/2)*cos(theta));
}

// rotate square from (0 to 150) = ( Rhombus to Square )
void ds_SquareAngle(int x, int y, int len, int theta)
{
	gfx_line( x + (len/2)*sin(theta), y + (len/2)*cos(theta), x + (len/2)*cos(theta), y - (len/2)*sin(theta));
	gfx_line( x + (len/2)*cos(theta), y - (len/2)*sin(theta), x - (len/2)*sin(theta), y - (len/2)*cos(theta));
	gfx_line( x - (len/2)*sin(theta), y - (len/2)*cos(theta), x - (len/2)*cos(theta), y + (len/2)*sin(theta));
	gfx_line( x - (len/2)*cos(theta), y + (len/2)*sin(theta), x + (len/2)*sin(theta), y + (len/2)*cos(theta));
}

void ds_Nonagon();
void ds_Octagon();
void ds_Heptagon();
void ds_Hexagon();
void ds_Scalene_triangle();
void ds_Right_triangle();
void ds_Parallelogram();
void ds_Pentagon();
void ds_Oval();
void ds_Heart();
void ds_Cross();
void ds_Arrow();
void ds_Cube();
void ds_Cylinder();
void ds_Star();
void ds_Crescent();



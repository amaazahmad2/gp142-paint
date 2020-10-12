
/*
 * CSE/ENGR 142 GP142_Demo
 *
 * 1/25/95
 * Author(s):         Larry Ruzzo
 * Email Address(s):  ruzzo@cs.washington.edu
 *
 * This program is a demo of some of the features of
 * GP142 --- the CSE/ENGR 142 Graphics Package.
 * It includes simple drawing commands, keyboard and mouse
 * interaction, and a simple animation.
 *
 * Revision history:
 * 11/18/97 Dan Boren  - Removed calls to obsolete function GP142_undo()
 *
 */
#pragma once
#include "GP142.h"
#include <stdio.h>
#include <math.h>
#include"shape.h"
#include"circle.h"
#include"text.h"
#include"polygon.h"
#include"rectangle.h"
#include"curve.h"
#include"line.h"
#include"oval.h"
#include<typeinfo>
#include"colorPoint.h";
#include<fstream>
#define PI 3.1415926535
#define ANIMATE_MSG "Select \"Animate\"\nOn the \"Run\" Menu"
#define TEXT_SIZE 20

#include <vector>
using namespace std;

//floodfill with 4 directions
void fillColor4Directions(int x, int y, int currentAppliedColor, int currentSelectedColor)
{
	if (getPixelColor(x, y) != currentAppliedColor)
		return;
	else if (currentSelectedColor == currentAppliedColor)
		return;
	else if (x < -698)
		return;
	else if (y < -293)
		return;

	GP142_pixelXY(currentSelectedColor, x, y);
	//GP142_flush();

	fillColor4Directions(x + 1, y, currentAppliedColor, currentSelectedColor);
	//GP142_flush();
	fillColor4Directions(x - 1, y, currentAppliedColor, currentSelectedColor);
	//GP142_flush();
	fillColor4Directions(x, y + 1, currentAppliedColor, currentSelectedColor);
	//GP142_flush();
	fillColor4Directions(x, y - 1, currentAppliedColor, currentSelectedColor);
	
}


//function for eraser
void eraser(point &p, vector<shape*>&allShapes)
{
	bool shape_contains_this_point = false;

	shape *shapeToBeDeleted = nullptr;
	int indexOfShapeToBeDeleted;
	for (int i = allShapes.size() - 1; i >= 0; i--)
	{
		if (allShapes[i]->contains(p) == true)
		{
			shape_contains_this_point = true;
			shapeToBeDeleted = allShapes[i];
			indexOfShapeToBeDeleted = i;
			break;
		}
	}


	if (shape_contains_this_point == false)
	{
		fillColor4Directions(p.x, p.y, getPixelColor(p.x, p.y), WHITE);
	}

	if (shapeToBeDeleted == nullptr)
		return;

	string shapeName = typeid(*(shapeToBeDeleted)).name();
	int minX = shapeToBeDeleted->Points[0].x;
	int maxX = shapeToBeDeleted->Points[0].x;
	int minY = shapeToBeDeleted->Points[0].y;
	int maxY = shapeToBeDeleted->Points[0].y;

	if (shapeName == "class line" || shapeName == "class curve")
	{
		shapeToBeDeleted->color = WHITE;
		shapeToBeDeleted->draw();

		allShapes.erase(allShapes.begin() + indexOfShapeToBeDeleted);
		for (int i = 0; i < allShapes.size(); i++)
			allShapes[i]->draw();

		return;
	}
	else if (shapeName == "class circle")
	{
		int radius = sqrt(pow(shapeToBeDeleted->Points[1].x - shapeToBeDeleted->Points[0].x, 2) + pow(shapeToBeDeleted->Points[1].y - shapeToBeDeleted->Points[0].y, 2));
		maxX = shapeToBeDeleted->Points[0].x + radius;
		minX = shapeToBeDeleted->Points[0].x - radius;

		maxY = shapeToBeDeleted->Points[0].y + radius;
		minY = shapeToBeDeleted->Points[0].y - radius;

		
	}
	else if (shapeName == "class text")
	{
		shapeToBeDeleted->color = WHITE;
		for(int i=0; i<10; i++)
			shapeToBeDeleted->draw();

		allShapes.erase(allShapes.begin() + indexOfShapeToBeDeleted);
		for (int i = 0; i < allShapes.size(); i++)
			allShapes[i]->draw();

		return;
	}
	else
	{
		

		for (int i = 0; i < shapeToBeDeleted->numOfPoints; i++)
		{
			if (shapeToBeDeleted->Points[i].x > maxX)
				maxX = shapeToBeDeleted->Points[i].x;

			if (shapeToBeDeleted->Points[i].x < minX)
				minX = shapeToBeDeleted->Points[i].x;

			if (shapeToBeDeleted->Points[i].y > maxY)
				maxY = shapeToBeDeleted->Points[i].y;

			if (shapeToBeDeleted->Points[i].y < minY)
				minY = shapeToBeDeleted->Points[i].y;
		}
	}
	//GP142_rectangleXY(BLACK, minX, minY, maxX, maxY, 2);
	//GP142_flush();
	shapeToBeDeleted->color = WHITE;
	shapeToBeDeleted->draw();
	GP142_flush();

	point tempPoint;
	//bool pointFoundInAnotherShape = false;
	for (int x = minX; x <= maxX; x++)
	{
		for (int y = minY; y <= maxY; y++)
		{
			//pointFoundInAnotherShape = false;
			tempPoint = { x,y };

			if (shapeToBeDeleted->contains(tempPoint) == true && x > -700 && y > -295)
			{
				if (indexOfShapeToBeDeleted == 0)
				{
					GP142_pixelXY(WHITE, x, y);
				}
				
				for (int i = indexOfShapeToBeDeleted - 1; i >= 0; i--)
				{
					
						if (allShapes[i]->contains(tempPoint) == false)
						{
							GP142_pixelXY(WHITE, x, y);
							
							break;
						}
						
				}
				//GP142_flush();
			}
				//GP142_pixelXY(WHITE, x, y);
			/*{
				for (int i = 0; i < allShapes.size(); i++)
				{
					if (i == indexOfShapeToBeDeleted)
						continue;

					if (allShapes[i]->contains(tempPoint) == true)
					{
						pointFoundInAnotherShape = true;
						break;
					}
				}
			}*/

			//if (pointFoundInAnotherShape == true)
			//	continue;
			//else
			//{
				//GP142_pixelXY(WHITE, x, y);
			//}
		}
	}
	allShapes.erase(allShapes.begin() + indexOfShapeToBeDeleted);
	for (int i = 0; i < allShapes.size(); i++)
	{
		//typeid(*(shapeToBeDeleted)).name();
		shapeName = typeid((*(allShapes[i]))).name();
		if (shapeName != "class colorPoint")
		{
			allShapes[i]->draw();
		}
	}
		

}

//UI before opening the canvas
void begin(bool &load, int&quit)
{
	GP142_clear(); //for white color

	GP142_rectangleXY(BLACK, -400, -50, 400, 50, 1); //interface
	GP142_lineXY(BLACK, 0, -50, 0, 50, 2);
	GP142_textXY(BLACK, -300, -40, 80, "NEW");
	GP142_textXY(BLACK, 100, -40, 80, "LOAD");

	int mouse_x, mouse_y;
	char key_pressed;
	int cl;
	bool flag = false;
	while (flag == false)
	{
		cl = GP142_await_event(&mouse_x, &mouse_y, &key_pressed);
		if (cl == 4)
		{
			quit = 1;
			flag = true;
		}
		else if (mouse_x < 0 && mouse_x > -400 && mouse_y > -50 && mouse_y < 50)
		{
			load = false;
			return;
		}
		else if (mouse_x > 0 && mouse_x < 400 && mouse_y > -50 && mouse_y < 50)
		{
			load = true;
			return;
		}
	}
	

}

//floodfill with 8 directions
void fillColor8Directions(int x, int y, int currentAppliedColor, int currentSelectedColor)
{
	if (getPixelColor(x, y) != currentAppliedColor)
		return;
	else if (currentSelectedColor == currentAppliedColor)
		return;

	GP142_pixelXY(currentSelectedColor, x, y);
	//GP142_flush();

	fillColor8Directions(x + 1, y, currentAppliedColor, currentSelectedColor);
	fillColor8Directions(x - 1, y, currentAppliedColor, currentSelectedColor);

	fillColor8Directions(x, y + 1, currentAppliedColor, currentSelectedColor);

	fillColor8Directions(x, y - 1, currentAppliedColor, currentSelectedColor);

	fillColor8Directions(x + 1, y+1, currentAppliedColor, currentSelectedColor);
	fillColor8Directions(x + 1, y-1, currentAppliedColor, currentSelectedColor);
	fillColor8Directions(x - 1, y+1, currentAppliedColor, currentSelectedColor);
	fillColor8Directions(x - 1, y-1, currentAppliedColor, currentSelectedColor);
}




//fill color using scan line algo
void fillColorWithScanLine(int x, int y, int currentAppliedColor, int currentSeletedColor)
{
	if (currentAppliedColor == currentSeletedColor)
		return;

	int tempx = x, tempy = y, extremeLeftX = x, extremeRightX = x, midX = x;


	while (getPixelColor(midX, tempy) == currentAppliedColor)
	{
		extremeLeftX = midX;
		extremeRightX = midX;
		while (getPixelColor(extremeLeftX, tempy) == currentAppliedColor)
		{
			extremeLeftX--;
		}

		while (getPixelColor(extremeRightX, tempy) == currentAppliedColor)
		{
			extremeRightX++;
		}

		midX = (extremeRightX + extremeLeftX) / 2;
		for (int i = midX; i < extremeRightX; i++)
		{
			GP142_pixelXY(currentSeletedColor, i, tempy);

		}
		//GP142_flush();

		for (int i = midX; i > extremeLeftX; i--)
		{
			GP142_pixelXY(currentSeletedColor, i, tempy);

		}
		//GP142_flush();

		tempy++;
	}

	tempy = y - 1;
	midX = x;

	while (getPixelColor(midX, tempy) == currentAppliedColor)
	{
		extremeLeftX = midX;
		extremeRightX = midX;
		while (getPixelColor(extremeLeftX, tempy) == currentAppliedColor)
		{
			extremeLeftX--;
		}

		while (getPixelColor(extremeRightX, tempy) == currentAppliedColor)
		{
			extremeRightX++;
		}

		midX = (extremeRightX + extremeLeftX) / 2;
		for (int i = midX; i < extremeRightX; i++)
		{
			GP142_pixelXY(currentSeletedColor, i, tempy);

		}
		//GP142_flush();

		for (int i = midX; i > extremeLeftX; i--)
		{
			GP142_pixelXY(currentSeletedColor, i, tempy);

		}
		//GP142_flush();

		tempy--;
	}

	//fillColor2(x - 1, y, currentAppliedColor, currentSeletedColor);
	//fillColor2(x + 1, y, currentAppliedColor, currentSeletedColor);
}

//checkClick returns the shape selected and changes the color of selected shape  in panel 
int checkClick(int& mouse_x, int& mouse_y, int &currentShape, int &currentSelectedColor)
{
	if (mouse_x >= -761 && mouse_x <= -700) //click inside tool panel
	{
		if (mouse_y >= 295)//clear all
		{
			GP142_textXY(RED, -755, 330, 15, "CLEAR \n   ALL"); //1st box
			currentShape = 0;
			return 0;
		}
		else if (mouse_y >= 221) //circle
		{
			GP142_circleXY(RED, -730, 268, 18);//2nd box - circle
			GP142_circleXY(WHITE, -730, 268, 16);
			GP142_textXY(RED, -749, 226, 11, "CIRCLE");
			GP142_flush();
			currentShape = 1;
			return 1;
		}
		else if (mouse_y >= 148) //oval
		{
			GP142_ovalXY(RED, -749, 205, -710, 185, 2); //3rd box - oval
			GP142_textXY(RED, -745, 150, 11, "OVAL");
			currentShape = 2;
			return 1;
		}
		else if (mouse_y >= 73.8) //solid line
		{
			GP142_lineXY(RED, -752, 135, -710, 115, 2);//4th box - solid line
			GP142_textXY(RED, -745, 90, 11, "SOLID \n LINE");
			currentShape = 3;
			return 1;
		}
		else if (mouse_y >= 0) //dotted line
		{
			drawDottedLine(RED, -750, 60, -710, 40);//5th box - dotted line
			GP142_textXY(RED, -749, 20, 11, "DOTTED \n   LINE");
			currentShape = 4;
			return 1;
		}
		else if (mouse_y >= -73.8) //curve
		{
			GP142_lineXY(RED, -755, -20, -750, -15, 2); //6th box - curve
			GP142_lineXY(RED, -750, -15, -718, -25, 2);
			GP142_lineXY(RED, -718, -25, -710, -20, 2);
			GP142_textXY(RED, -749, -60, 11, "CURVE");
			currentShape = 5;
			return 1;
		}
		else if (mouse_y >= -148) //rectangle
		{
			GP142_rectangleXY(RED, -750, -90, -710, -110, 2); //7th box - rectangle
			GP142_textXY(RED, -758, -135, 9, "RECTANGLE");
			currentShape = 6;
			return 1;
		}
		else if (mouse_y >= -221) //polygon
		{
			GP142_lineXY(RED, -745, -155, -725, -155, 2); //8th box - polygon
			GP142_lineXY(RED, -725, -155, -710, -170, 2);
			GP142_lineXY(RED, -710, -170, -750, -175, 2);
			GP142_lineXY(RED, -750, -175, -745, -155, 2);
			GP142_textXY(RED, -757, -200, 11, "  N-SIDED \n POLYGON");
			currentShape = 7;
			return 1;
		}
		else if (mouse_y >= -295) // text
		{
			GP142_textXY(RED, -741, -267, 40, "T"); //9th box - text
			GP142_textXY(RED, -743, -285, 11, "TEXT");
			currentShape = 8;
			return 1;
		}
		else if (mouse_y >= -331) //save
		{
			GP142_textXY(RED, -747, -320, 13, "SAVE");
			return 2;
		}
		else if (mouse_y >= -369) //quit
		{
			return 3;
		}
	}

	else if (mouse_y <= -295 && mouse_y >= -370) //click 1st 2 options inside color panel
	{
		if (mouse_x <= -537) //eraser
		{
			currentShape = 9;
			GP142_textXY(RED, -650, -330, 16, "ERASER");
			GP142_rectangleXY(RED, -630, -340, -600, -360, 2);
			return 1;
		}
		else if (mouse_x <= -375) //bucket
		{
			currentShape = 10;
			GP142_textXY(RED, -490, -330, 16, "BUCKET");
			GP142_lineXY(RED, -470, -340, -470, -360, 2);
			GP142_lineXY(RED, -440, -340, -440, -360, 2);
			GP142_lineXY(RED, -470, -360, -440, -360, 2);
			GP142_ovalXY(RED, -470, -340, -440, -350, 2);
			return 1;
		}
		else if (mouse_x <= -132 && mouse_x > -213 && mouse_y >= -332)
		{

			currentSelectedColor = 23;
		}
		else if (mouse_x <= -132 && mouse_x > -213 && mouse_y < -332)
		{
			currentSelectedColor = 22;
		}
		else if (mouse_x <= -51 && mouse_y >= -332)
		{
			currentSelectedColor = 21;
		}
		else if (mouse_x <= -51 && mouse_y < -332)
		{
			currentSelectedColor = 20;
		}
		else if (mouse_x <= 30 && mouse_y >= -332)
		{
			currentSelectedColor = 19;
		}
		else if (mouse_x <= 30 && mouse_y < -332)
		{
			currentSelectedColor = 18;
		}
		else if (mouse_x <= 111 && mouse_y >= -332)
		{
			currentSelectedColor = 17;
		}
		else if (mouse_x <= 111 && mouse_y < -332)
		{
			currentSelectedColor = 16;
		}
		else if (mouse_x <= 192 && mouse_y >= -332)
		{
			currentSelectedColor = 15;
		}
		else if (mouse_x <= 192 && mouse_y < -332)
		{
			currentSelectedColor = 14;
		}
		else if (mouse_x <= 273 && mouse_y >= -332)
		{
			currentSelectedColor = 13;
		}
		else if (mouse_x <= 273 && mouse_y < -332)
		{
			currentSelectedColor = 12;
		}
		else if (mouse_x <= 354 && mouse_y >= -332)
		{
			currentSelectedColor = 11;
		}
		else if (mouse_x <= 354 && mouse_y < -332)
		{
			currentSelectedColor = 10;
		}
		else if (mouse_x <= 435 && mouse_y >= -332)
		{
			currentSelectedColor = 9;
		}
		else if (mouse_x <= 435 && mouse_y < -332)
		{
			currentSelectedColor = 8;
		}
		else if (mouse_x <= 516 && mouse_y >= -332)
		{
			currentSelectedColor = 7;
		}
		else if (mouse_x <= 516 && mouse_y < -332)
		{
			currentSelectedColor = 6;
		}
		else if (mouse_x <= 597 && mouse_y >= -332)
		{
			currentSelectedColor = 5;
		}
		else if (mouse_x <= 597 && mouse_y < -332)
		{
			currentSelectedColor = 4;
		}
		else if (mouse_x <= 678 && mouse_y >= -332)
		{
			currentSelectedColor = 3;
		}
		else if (mouse_x <= 678 && mouse_y < -332)
		{
			currentSelectedColor = 2;
		}
		else if (mouse_x <= 760 && mouse_y >= -332)
		{
			currentSelectedColor = 1;
		}
		else if (mouse_x <= 760 && mouse_y < -332)
		{
			currentSelectedColor = 0;
		}

		return 4;
	}

	else
		return 99; //click on canvas

}

//function to fill the currentColor box
void fillCurrentColorBox(int currentAppliedColor, int currentSelectedColor)
{

	for (int x = -374, y = -333; y > -368; y--)
	{
		GP142_lineXY(currentSelectedColor, -374, y, -218, y, 2);
	}

}

//draws the tool panel on the left
void drawToolPanel()
{
	//BASIC FRAME
	GP142_rectangleXY(BLACK, -761, 369, -700, -369, 3);
	GP142_lineXY(BLACK, -761, 295, -700, 295, 2);
	GP142_lineXY(BLACK, -761, 221, -700, 221, 2);
	GP142_lineXY(BLACK, -761, 148, -700, 148, 2);
	GP142_lineXY(BLACK, -761, 73.8, -700, 73.8, 2);
	GP142_lineXY(BLACK, -761, 0, -700, 0, 2);
	GP142_lineXY(BLACK, -761, -73.8, -700, -73.8, 2);
	GP142_lineXY(BLACK, -761, -148, -700, -148, 2);
	GP142_lineXY(BLACK, -761, -221, -700, -221, 2);
	GP142_lineXY(BLACK, -761, -295, -700, -295, 2);
	GP142_lineXY(BLACK, -761, -331, -700, -331, 2);

	//OPTIONS INSIDE THE BOXES
	GP142_textXY(BLACK, -755, 330, 15, "CLEAR \n   ALL"); //1st box

	GP142_circleXY(BLACK, -730, 268, 18);//2nd box - circle
	GP142_circleXY(WHITE, -730, 268, 16);
	GP142_textXY(BLACK, -749, 226, 11, "CIRCLE");

	GP142_ovalXY(BLACK, -749, 205, -710, 185, 2); //3rd box - oval
	GP142_textXY(BLACK, -745, 150, 11, "OVAL");

	GP142_lineXY(BLACK, -752, 135, -710, 115, 2);//4th box - solid line
	GP142_textXY(BLACK, -745, 90, 11, "SOLID \n LINE");

	drawDottedLine(BLACK, -750, 60, -710, 40);//5th box - dotted line
	GP142_textXY(BLACK, -749, 20, 11, "DOTTED \n   LINE");

	GP142_lineXY(BLACK, -755, -20, -750, -15, 2); //6th box - curve
	GP142_lineXY(BLACK, -750, -15, -718, -25, 2);
	GP142_lineXY(BLACK, -718, -25, -710, -20, 2);
	GP142_textXY(BLACK, -749, -60, 11, "CURVE");

	GP142_rectangleXY(BLACK, -750, -90, -710, -110, 2); //7th box - rectangle
	GP142_textXY(BLACK, -758, -135, 9, "RECTANGLE");

	GP142_lineXY(BLACK, -745, -155, -725, -155, 2); //8th box - polygon
	GP142_lineXY(BLACK, -725, -155, -710, -170, 2);
	GP142_lineXY(BLACK, -710, -170, -750, -175, 2);
	GP142_lineXY(BLACK, -750, -175, -745, -155, 2);
	GP142_textXY(BLACK, -757, -200, 11, "  N-SIDED \n POLYGON");

	GP142_textXY(BLACK, -741, -267, 40, "T"); //9th box - text
	GP142_textXY(BLACK, -743, -285, 11, "TEXT");

	GP142_textXY(BLACK, -747, -320, 13, "SAVE");
	GP142_textXY(BLACK, -747, -360, 13, "QUIT");


}

//draws the color panel n the bottom
void drawLeftColorPanel()
{
	//BASIC FRAME   
	GP142_rectangleXY(BLACK, -700, -295, 760, -369, 3);
	GP142_lineXY(BLACK, -537, -295, -537, -370, 2);
	GP142_lineXY(BLACK, -375, -295, -375, -370, 2);
	GP142_lineXY(BLACK, -213, -295, -213, -370, 8);
	GP142_lineXY(BLACK, -132, -295, -132, -370, 2);
	GP142_lineXY(BLACK, -51, -295, -51, -370, 2);
	GP142_lineXY(BLACK, 30, -295, 30, -370, 2);
	GP142_lineXY(BLACK, 111, -295, 111, -370, 2);
	GP142_lineXY(BLACK, 192, -295, 192, -370, 2);
	GP142_lineXY(BLACK, 273, -295, 273, -370, 2);
	GP142_lineXY(BLACK, 354, -295, 354, -370, 2);
	GP142_lineXY(BLACK, 435, -295, 435, -370, 2);
	GP142_lineXY(BLACK, 516, -295, 516, -370, 2);
	GP142_lineXY(BLACK, 597, -295, 597, -370, 2);
	GP142_lineXY(BLACK, 678, -295, 678, -370, 2);

	GP142_lineXY(BLACK, -375, -332, 760, -332, 2);

	//eraser
	GP142_textXY(BLACK, -650, -330, 16, "ERASER");
	GP142_rectangleXY(BLACK, -630, -340, -600, -360, 2);

	//bucket
	GP142_textXY(BLACK, -490, -330, 16, "BUCKET");
	GP142_lineXY(BLACK, -470, -340, -470, -360, 2);
	GP142_lineXY(BLACK, -440, -340, -440, -360, 2);
	GP142_lineXY(BLACK, -470, -360, -440, -360, 2);
	GP142_ovalXY(BLACK, -470, -340, -440, -350, 2);

	//colorfill
	GP142_textXY(BLACK, -360, -330, 16, "CURRENT COLOR");


}
void drawRightColorPanel()
{
	//right color panel
	for (int i = 23, j = -200; i >= 0; i = i - 2, j = j + 80)
	{
		fillColorWithScanLine(j, -330, WHITE, i);
		fillColorWithScanLine(j, -340, WHITE, i - 1);
	}
}

//creates and adds the required object in allShapes and calls its draw
void performAction(int currentShape, int previousColor, int currentColor, int mouse_x, int mouse_y, vector<shape*>&allShapes)
{
	if (mouse_x < -700 || mouse_y < -295)
		return;

	if (currentShape == 1)
	{
		allShapes.push_back(new circle(currentColor, mouse_x, mouse_y));
		allShapes[allShapes.size() - 1]->draw();
	}
	else if (currentShape == 2)
	{
		allShapes.push_back(new oval(currentColor, mouse_x, mouse_y));
		allShapes[allShapes.size() - 1]->draw();
	}
	else if (currentShape == 3)
	{
		allShapes.push_back(new line(currentColor, 1, mouse_x, mouse_y));
		allShapes[allShapes.size() - 1]->draw();
	}
	else if (currentShape == 4)
	{
		allShapes.push_back(new line(currentColor, 0, mouse_x, mouse_y));
		allShapes[allShapes.size() - 1]->draw();
	}
	else if (currentShape == 5)
	{
		allShapes.push_back(new curve(currentColor, 1, mouse_x, mouse_y));
		allShapes[allShapes.size() - 1]->draw();
	}
	else if (currentShape == 6)
	{
		allShapes.push_back(new rectangle(currentColor, mouse_x, mouse_y));
		allShapes[allShapes.size() - 1]->draw();
	}
	else if (currentShape == 7)
	{
		allShapes.push_back(new polygon(currentColor, mouse_x, mouse_y));
		allShapes[allShapes.size() - 1]->draw();
	}
	else if (currentShape == 8)
	{
		allShapes.push_back(new text(currentColor, mouse_x, mouse_y));
		allShapes[allShapes.size() - 1]->draw();
	}
	else if (currentShape == 9) //eraser
	{
		point temp = { mouse_x, mouse_y };
		/*for (int i = allShapes.size() - 1; i >= 0; i--)
		{
			if (allShapes[i]->contains(temp) == true)
			{
				allShapes[i]->color = WHITE;
				allShapes[i]->draw();
				allShapes.erase(allShapes.begin() + i);

				break;
			}
		}*/

		eraser(temp, allShapes);
	}
	else if (currentShape == 10) //bucket
	{
		string str;
		point tempPoint = { mouse_x, mouse_y };
		colorPoint* cp = new colorPoint(mouse_x, mouse_y, currentColor);
		for (int i = allShapes.size() - 1; i >= 0; i--)
		{
			str = typeid(*(allShapes[i])).name();
			if ((str == "class line" || str == "class curve") && allShapes[i]->contains(tempPoint) == true)
			{
				fillColor8Directions(mouse_x, mouse_y, previousColor, currentColor);
				allShapes[i]->color = currentColor;
				allShapes.push_back(cp);
				return;
			}
			else if (str == "class text" && allShapes[i]->contains(tempPoint) == true)
			{
				allShapes[i]->color = currentColor;
				allShapes[i]->draw();
				allShapes.push_back(cp);
				return;
			}
			else if (str == "class circle" && allShapes[i]->contains(tempPoint) == true)
			{
				fillColor4Directions(mouse_x, mouse_y, previousColor, currentColor);
				allShapes.push_back(cp);
				return;
			}
			else if (allShapes[i]->contains(tempPoint) == true)
			{
				fillColor4Directions(mouse_x, mouse_y, previousColor, currentColor);
				allShapes.push_back(cp);
				return;
			}
		}

		fillColor4Directions(mouse_x, mouse_y, previousColor, currentColor);
		allShapes.push_back(cp);
		
		
	

	}
}

//for saving and serialization
void save(vector<shape*>&allShapes, string &filepath)
{
	ofstream file(filepath, ios::out);
	for (int i = 0; i < allShapes.size(); i++)
	{
		allShapes[i]->serialize(file);
	}
	file << "End";

}
void LLoad(vector<shape*>&allShapes, string &filepath)
{
	ifstream file(filepath, ios::in);
	char buff[50] = "\0";

	while(strcmp(buff,"End") != 0) {

		file >> buff;
		file.get();

		if (strcmp(buff,"circle") == 0){
	
			circle* myc = new circle;
			myc->deserialize(filepath, file);
			allShapes.push_back(myc);
		}
		else if (strcmp(buff, "polygon") == 0) {

			polygon* myc = new polygon;
			myc->deserialize(filepath, file);
			allShapes.push_back(myc);
		}
		else if (strcmp(buff, "colorpoint") == 0) {

			colorPoint* myc = new colorPoint;
			myc->deserialize(filepath, file);
			allShapes.push_back(myc);
		}
		else if (strcmp(buff, "oval") == 0) {

			oval* myc = new oval;
			myc->deserialize(filepath, file);
			allShapes.push_back(myc);
		}
		else if (strcmp(buff, "line") == 0) {

			line* myc = new line;
			myc->deserialize(filepath, file);
			allShapes.push_back(myc);
		}
		else if (strcmp(buff, "rectangle") == 0)
		{
			rectangle* myc = new rectangle;
			myc->deserialize(filepath, file);
			allShapes.push_back(myc);
		}
		else if (strcmp(buff, "text") == 0) {

			text* myc = new text;
			myc->deserialize(filepath, file);
			allShapes.push_back(myc);
		}
		
	}

	for (int i = 0; i < allShapes.size(); i++)
	{
		allShapes[i]->draw();
		GP142_flush();
	}
}






/******************************************************************************
 *
 * The Main Program
 * ----------------
 *
 * The main program takes care of initialization and cleanup, and the high-level
 * control of all actions in the program, but most of the detail work is
 * relegated to sub-functions, so that the structure of main stays clear and
 * simple.
 *
 */
int main(void)
{

	//std::vector<int> abc(5);
	int quit = 0;           /* has user signaled quit yet?                      */
	int mouse_x, mouse_y;
	char key_pressed;
	bool load = false;
	GP142_open();           /* Open and initialize the GP142 Graphics Window    */
	begin(load,quit);


	int pcount = 0;
	int points[4];

	point tempPoint;
	int clickResult, currentShape = 0;
	int currentSelectedColor = BLACK, previousSelectedColor = WHITE;
	int tempCurrentSelectedColor;
	vector < shape* > allShapes;
	GP142_clear();
	//turnScreenWhite(WHITE, 0, 0);
	//text c1(WHITE);
	drawToolPanel();
	drawLeftColorPanel();
	drawRightColorPanel();
	fillCurrentColorBox(WHITE, BLACK);
	string filepath = "amazfile.txt";


	if (load == true)
	{
		LLoad(allShapes, filepath);
	}

	//The Event Loop  
	while (quit == 0) {

		switch (GP142_await_event(&mouse_x, &mouse_y, &key_pressed)) {
		case GP142_QUIT:
			quit = 1;   // set flag to terminate loop                
			break;

		case GP142_MOUSE:
			//GP142_clear();


			clickResult = checkClick(mouse_x, mouse_y, currentShape, currentSelectedColor);
			if (clickResult == 0) //clear all clicked
			{
				GP142_clear();
				drawToolPanel();
				drawLeftColorPanel();
				drawRightColorPanel();
				fillCurrentColorBox(WHITE, BLACK);
				currentSelectedColor = BLACK;
				allShapes.clear();
			}
			else if (clickResult == 1) //a shape or eraser/bucket selected
			{
				GP142_flush();
				drawToolPanel();
				drawLeftColorPanel();
				GP142_flush();
			}
			else if (clickResult == 2) //save selected
			{
				save(allShapes, filepath);
			}
			else if (clickResult == 3)  // quit selected
				quit = 1;
			else if (clickResult == 4) //color selected
			{
				GP142_flush();
				fillCurrentColorBox(previousSelectedColor, currentSelectedColor);
				GP142_flush();
				previousSelectedColor = currentSelectedColor;

			}
			else if (clickResult == 99)
			{
				performAction(currentShape, getPixelColor(mouse_x, mouse_y), currentSelectedColor, mouse_x, mouse_y, allShapes);

			}


			checkClick(mouse_x, mouse_y, currentShape, currentSelectedColor);



			//GP142_flush();
			break;



		case GP142_KBD:
			
		default:
			break;
		}



	}






	GP142_close();          /* Clean up and close graphics window           */
	allShapes.clear();
	return 0;
}








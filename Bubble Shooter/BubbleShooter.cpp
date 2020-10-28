#include<stdio.h>
#include<stdlib.h>
# include "iGraphics.h"
#define screenWidth 1000
#define screenHight 700

int b1x=200, b1y=350; // orginal bubble
int b2x=700, b2y=350; // red bubble

bool musicOn = true;
int aimx=500,aimy=350; // Shooter Initial Position
int hit=0; // score
int miss=10; // Life
int sts=0; //start
char scr[10],bull[10];

void bubble1();

void iDraw()
{
	if (sts==0)//start page
	{
		iClear();
		iPauseTimer(0);
		iShowBMP(0,0,"bg.bmp");
		iSetColor(255,0,0);
		iText(350, 500, "'Welcome to 'Bubble Shooter!'", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(0,0,0);
		iText(440, 400, "Press 'P' to Play", GLUT_BITMAP_HELVETICA_18);
		iSetColor(139,0,0);
		iText(200, 340, "Shoot the Bubble to make score. If you shoot the Red Bubble, you will die.");
		iText(250, 300, "Hold down Right Button to move target and use Left Button to Shoot.");
	}

	if (sts==1)//game starts
	{
		iClear();
		iShowBMP(0,0,"uw.bmp");
		iSetColor(255,193,204);
		iFilledCircle(b1x,b1y,50,10000);
		iSetColor(255,0,0);
	    iFilledCircle(b2x,b2y,55,10000);
		iSetColor(255,255,255);
		iCircle(aimx,aimy,15);
		iCircle(aimx,aimy,3);
		iFilledRectangle(aimx-2,aimy-25,3,50); // Vertical Line of Shooter
		iFilledRectangle(aimx-25,aimy-2,50,3); // Horizontal Line of Shooter
		iSetColor(128,255,0);
		sprintf(scr,"Score: %d",hit);
		iText(10,675,scr,GLUT_BITMAP_TIMES_ROMAN_24);
		sprintf(bull,"Bullet: %d",miss);
		iText(900,675,bull,GLUT_BITMAP_TIMES_ROMAN_24);
		iResumeTimer(0); // Game Start / Continues
	}

	if (sts == 2)//game ends
	{
		iPauseTimer(0);
		iClear();
		iShowBMP(0,0,"eg.bmp");
		iSetColor(255,0,0);
		iText(360, 400, "Opps!!! You Shoot the Red Bubble", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(128,255,0);
		sprintf(scr,"Score: %d",hit); // Score
		iText(480,350,scr,GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(255,255,255);
		iText(380, 300, "Press 'R' to retry or press 'Q' to quit", GLUT_BITMAP_HELVETICA_18);
	}

	if (miss <= 0 )//life
	{
		iPauseTimer(0);
		iClear();
		iShowBMP(0,0,"uw.bmp");
		iSetColor(255,0,0);
		iText(460, 400, "No Bullet!!", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(128,255,0);
		sprintf(scr,"Score: %d",hit); // Score
		iText(480,350,scr,GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(255,255,255);
		iText(380, 300, "Press 'R' to retry or press 'Q' to quit", GLUT_BITMAP_HELVETICA_18);
	}
}

void iMouseMove(int mx, int my)
{
	aimx = mx;
	aimy = my;
}

void iMouse(int button, int state, int mx, int my)
{
	if(sts==1)
	{
	    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	    {
			aimx = mx;
			aimy = my;
	    }
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (aimx>b1x-30 && aimx<b1x+50) && (aimy>b1y-30 && aimy<b1y+50)) // Hit inside the bubble
		{
			hit++; // Score Increases
			if (hit % 10 == 0)
			{
				miss = miss + 5;
				iSetTimer(10000, bubble1) + 1000;
			}
		}
		else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (aimx>b2x-30 && aimx<b2x+50) && (aimy>b2y-30 && aimy<b2y+50))  // Hit inside red bubble
		{
			sts=2; // Retry or Quit
		}
		else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && ((aimx<b1x-30 || aimx>b1x+50) || (aimy<b1y-30 || aimy>b1y+50) 
		|| (aimx<b2x-30 || aimx>b2x+50) || (aimy<b2y-30 || aimy>b2y+50))) // Hit outside red apple
		{
			miss--; // Life Decreases
		}
	}
}

void iKeyboard(unsigned char key)
{
	if(key == 'p' || key == 'P') // Game Starts
	{
		sts=1;
		hit=0; // Score Initially Zero
		//miss=6; // For retry
	}
	if(key == 'r' || key == 'R')
	{
		sts=1;
		hit=0; // Score Initially Zero
		miss=10; // For retry
	}
	if(key=='q' || key == 'Q') // Game Stops
	{
		exit(0);
	}
}

void iSpecialKeyboard(unsigned char key)
{
	if(key == GLUT_KEY_END)
	{
		if (musicOn)
		{
			musicOn = false;
			PlaySound(0,0,0);
		}
		else
		{
			musicOn = true;
			PlaySound("music\\TSN.wav",NULL,SND_LOOP|SND_ASYNC);
		}
	}
}

void bubble1 ()
{
	b1x = rand () % 900;
	b1y = rand () % 600;
	b2x = rand () % 900;
	b2y = rand () % 600;
}

int main()
{
	if (musicOn)
	{
		PlaySound("music\\TSN.wav",NULL,SND_LOOP|SND_ASYNC);
	}
	iSetTimer(10000, bubble1);
	iInitialize(screenWidth, screenHight, "Bubble Shooter");
	return 0;
}	
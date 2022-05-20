//#include<iostream>
#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<string.h>
#include"mouse.cpp"
#include"textbox.h"
int main()
{
	int gd=4,gm=0;
	char a;
	int i,j=0,k=0;
	textBox mainBox;
	initgraph(&gd,&gm,"C:\\turboc3\\bgi");
	setbkcolor(BLUE);
	setcolor(GREEN);
	//showmouse()
	mainBox.drawBox(0,10,getmaxx(),getmaxy()-10);
	//The infinite loop
	mainBox.setTextMode(2);
	mainBox.setbgColor(WHITE);
	mainBox.setTextColor(GREEN);
	showmouse();
	for(i=0;i<=500;)
	{
		mainBox.blinkCur();
		mouse(&click,&msX,&msY);
		//printf("X=%d\tY=%d\tClick=%d\n",msX,msY,click);
		//delay(100);
		if(click!=0)
		{
			mainBox.mouseHandle();
		}
		if(kbhit()!=0)
		{
			a=getch();
			i++;
			if(*key_state==4&&a==4)
			mainBox.setTextMode(i%2);
			else
			mainBox.writeText(a);
		}
	}
	getch();
	return 0;

}


#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
#include<graphics.h>
void refresh(void);
union REGS in,out;
char title[512]="Untitled.txt";
int X_cursor=0,Y_cursor=15;
int button,x,y;
int loopval0,loopval1,loopval2;
int savevalue=0,scrollpos=0,defsize=3,deffont=2;
char ch[2];
int tempfile[10000];//={'\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n','\n'};
int defcolor=5,openvalue=0,mode=1;
int count=0,change=0;
int i=0,NC=0,NVL=0,NHL=0,NCV=0,scle=464,upositio=15,tweak=0,NVLC=0;
void calculus(int mod)
{
	int c=0,d=0,e=0,f=0,p=0,q=0;
	//For wrap mode
	if(mod==1)
	{
	      for(;;)
		{
			if(620-p<(textwidth("W")+1))
			{
				p=0;
				q=q+textheight("w")+3;
			}
			if(tempfile[c]!='\n'&&tempfile[c]!='\t')
			{
				p=p+textwidth("W")+1;
			}
			else if(tempfile[c]=='\t')
			{
				if(620-p<5*(textwidth("W")+1))
				{
					p=0;
					q=q+textheight("W")+3;
				}
				else
				p=p+5*(textwidth("W")+1);
			}
			else if(tempfile[c]=='\n')
			{
				p=0;
				q=q+textheight("W")+3;
			}
			if(tempfile[c]=='\0')
			break;
			c++;
		}
		NC=c;
		NVL=q/(textheight("W")+3);
		p=0;
		c=0;
		q=0;
		if(NVL>=40)
		{
		 for(;;)
		 {
			if(620-p<(textwidth("W")+1))
			{
				p=0;
				q=q+textheight("w")+3;
			}
			if(tempfile[c]!='\n'&&tempfile[c]!='\t')
			{
				p=p+textwidth("W")+1;
			}
			else if(tempfile[c]=='\t')
			{
				if(620-p<5*(textwidth("W")+1))
				{
					p=0;
					q=q+textheight("W")+3;
				}
				else
				p=p+5*(textwidth("W")+1);
			}
			else if(tempfile[c]=='\n')
			{
				p=0;
				q=q+textheight("W")+3;
			}
			if(q/(textheight("W")+3)==(NVL-38))
			break;
			c++;
		}
		if(tweak==1&&NVL>40)
		{
			q=0;
			p=0;
			c=NCV;
			for(;;)
		 {
			if(620-p<(textwidth("W")+1))
			{
				p=0;
				q=q+textheight("w")+3;
			}
			if(tempfile[c]!='\n'&&tempfile[c]!='\t')
			{
				p=p+textwidth("W")+1;
			}
			else if(tempfile[c]=='\t')
			{
				if(620-p<5*(textwidth("W")+1))
				{
					p=0;
					q=q+textheight("W")+3;
				}
				else
				p=p+5*(textwidth("W")+1);
			}
			else if(tempfile[c]=='\n')
			{
				p=0;
				q=q+textheight("W")+3;
			}
			if(q/(textheight("W")+3)==NVL-38-(upositio-y))
			{
			       //	printf("%d %d",q,c);
				NCV=c;
				break;
			}
			c--;

			if(q/(textheight("W")+3)==NVL-38-(upositio-y))
			break;

		}
	       }
	       }
	       if(tweak!=1)
	       {
		if(tempfile[c]=='\n')
		NCV=c+1;
		else
		NCV=c;
		if(NVL>=40&&upositio!=q/(textheight("W")+3));
		upositio=15+NVL-38;
		//printf("%d",upositio);
		scle=479-q/(textheight("W")+3);
	       }
	}
	//For unwrapped mode
	//printf("%d",NVL);
}
int uposition()
{
	calculus(mode);
	return upositio;
}
int sclen()
{
	calculus(mode);
	return scle;
}
void beep()
{
	int i;
	for(i=2000;i<2100;i++)
	{
		sound(i);
		delay(1);
	}
	nosound();
}
int scrollfun()
{
	unsigned long int i;
       //	for(i=0;fgetc(tmp)!=EOF;i++);
       return 0;
}
void showmouse()
{
	in.x.ax=1;
	int86(0x33,&in,&out);

}
void CLKnBTN(int *BTN,int *X,int *Y)
{
	in.x.ax=3;
	int86(51,&in,&out);
	*BTN=out.x.bx;
	*X=out.x.cx;
	*Y=out.x.dx;
}
void hidems()
{
	in.x.ax=2;
	int86(0x33,&in,&out);
}
void disptext()
{
	//for deleting cursor before displaying character
	for(loopval0=0;loopval0<=0;loopval0++)
	{
		for(loopval1=0;loopval1<=textheight("|");loopval1++)
			putpixel(X_cursor+loopval0,Y_cursor+loopval1,WHITE);
	}
	//For cursor exceeding the limit area
	if(X_cursor>=(620/textwidth("W"))*textwidth("W")&&ch[0]!=8)
	{
		Y_cursor=Y_cursor+textheight("W")+3;
		X_cursor=0;
		//NVL++;
	}
	//For displaying characters except enter,tab and backspace
	if(ch[0]!=13&&ch[0]!=10&&ch[0]!='\t'&&ch[0]!=8)
	{
		setcolor(defcolor);
		outtextxy(X_cursor,Y_cursor,ch);
		X_cursor=X_cursor+textwidth(ch)+1;
	}
	//For displaying enter(or newline)
	else if(ch[0]==13||ch[0]==10)
	{
		Y_cursor=Y_cursor+textheight("W")+3;
		X_cursor=0;
		//NVL++;
	}
	//For displaying horizontal tab
	else if(ch[0]=='\t')
	{
		if(X_cursor>620-5*textwidth("W"))
		{
			Y_cursor=Y_cursor+textheight("W")+3;
			X_cursor=0;
			//NVL++;
		}
		else
			X_cursor=X_cursor+5*(textwidth("W")+1);
	}
	//for backspace
	else if(ch[0]==8&&(Y_cursor>15||X_cursor>=0))
	{
		count--;
		tempfile[count]='\0';
		refresh();
		if(count!=0)
		count--;
		//count--;
		//erasing the character
	       /*	if((X_cursor>(textwidth("W")/2)||Y_cursor>15)&&X_cursor!=0&&tempfile[count-1]!='\t'&&tempfile[count-1]!='\n')
		{
			X_cursor=X_cursor-1;
			for(loopval0=0;loopval0<=textwidth("W");loopval0++)
			{
				for(loopval1=0;loopval1<=textheight("|");loopval1++)
					putpixel(X_cursor-loopval0,Y_cursor+loopval1,WHITE);
			}
				X_cursor=X_cursor-textwidth("W");
		}
		else //if(X_cursor==0&&Y_cursor>15)
		{

			if(X_cursor==0)
			{
				Y_cursor=Y_cursor-textheight("W")-3;
				X_cursor=(620/(textwidth("W")+1))*(textwidth("W")+1)+textwidth("W")+1;
				if(tempfile[count]='\n'||(tempfile[count]='\t'&&X_cursor!=0))
				{
				for(;;)
				{
					X_cursor=X_cursor-1;
					for(loopval2=Y_cursor;loopval2<=Y_cursor+textheight("W");)
					{
						loopval2++;
						if(getpixel(X_cursor,loopval2)==defcolor||X_cursor==0)
						break;
					}
					if(getpixel(X_cursor,loopval2)==defcolor||X_cursor==0)
					break;
				}
				if(X_cursor!=0)
				X_cursor=(X_cursor/(textwidth("W")+1))*(textwidth("W")+1)+textwidth("W")+1;
				//NVL--;
				}
			}
			else if(tempfile[count-1]=='\t'&&X_cursor!=0)
			{
				if(X_cursor!=0)
				{
					X_cursor=X_cursor-5*(textwidth("W")+1);
				}
			}


		}*/

		//count--;
		//calculus(mode);
		//NCV=NCV-1;
		//if((NVL)>40&&X_cursor==0)
		//{
		//	refresh();
		  //	count--;
		//}
	}
	//for undisplaying the upper character
	//calculus(mode);
	//NCV=NCV-1;
	if((Y_cursor-15)/(textheight("W")+3)>=40&&ch[0]!=8&&tweak==0)
	{
		refresh();
		count--;
	}
}
void refresh()
{
	static int temp;
	int points[20] = {0,12,639,12,639,479,0,479,0,12};
	int pointscr[20] = {624,0,639,0,639,10,624,10,624,0};
	//cleardevice();
	//Start making windows
	setbkcolor(BLUE);
	setcolor(WHITE);
	outtextxy(2,2,"N");
	outtextxy(17,2,"FILE");
	outtextxy(62,2,"EDIT");
	outtextxy(107,2,"FORMAT");
	outtextxy(167,2,"ABOUT");
	setcolor(BLACK);
	fillpoly(5,points);
	setcolor(WHITE);
	fillpoly(5,pointscr);
	setcolor(RED);
	outtextxy(getmaxx()-10,2,"X");
	//for scroll
	line(629,12,629,479);
	//End of windows making and start of mouses and clicks
	//Pointer
	showmouse();
	setcolor(WHITE);
	//Title display
	outtextxy(250,2,title);
	//Clicks and Location
	CLKnBTN(&button,&x,&y);
	//Rewinding cursors and pointers for location feed
	//calling calculus() for finding NVL or NHL
	hidems();
	if((Y_cursor-15)/(textheight("W")+3)>=40&&ch[0]!=8&&tweak==0)
	{
		calculus(mode);
		count=NCV;
	}
	else if(ch[0]==8&&NVL>=40&&tweak==0)
	{
		calculus(mode);
		count=NCV;
	}
	else
	count=0;
	X_cursor=0;
	Y_cursor=15;
	//for unsaved file
	temp=count;
	if(tweak==1)
	{
	       //	printf("it's okay");
		//calculus(mode);
		count=NCV;
		//	printf("%d",count);
	}
	if(savevalue==0)
	{
		for(;tempfile[count]!='\0';)
		{
			ch[0]=tempfile[count];
			if((Y_cursor-15)/(textheight("W")+3)>=40)
			break;
			//Y_cursor=Y_cursor-textheight("W")-3;
			disptext();
			count++;
		}
		if(tempfile[count]!='\0')
			count--;

	}
	//for scrollbutton
	if(tweak==0)
	{
	       //	printf("%d",upositio);
		line(630,uposition(),639,uposition());
		line(630,(uposition()+sclen()),639,(uposition()+sclen()));
	}
	if(tweak==1)
	{
		line(630,upositio,639,upositio);
		line(630,upositio+scle,639,upositio+scle);
	}
	showmouse();
}
void main()
{
	int gd=DETECT,gm,errorcode;
	int defsize=3;
	unsigned long int i=0,a;
	int aboutdd[20]={152,12,233,12,233,45,152,45,152,12};
	int filedd[20]={0,12,80,12,80,90,0,90,0,12};
	int editdd[20]={52,12,132,12,132,90,52,90,52,12};
	int formatdd[20]={97,12,177,12,177,180,97,180,97,12};
	int unsavealert[20] = {219,189,419,189,419,289,219,289,219,189};
	int yes[20]={279,269,309,269,309,284,279,284,279,269};
	int no[20]={314,269,344,269,344,284,314,284,314,269};
	int cancel[20]={349,269,409,269,409,284,349,284,349,269};
	int topalert[20]={219,189,219,200,419,200,419,189,219,189};
	int redcross[20]={405,189,419,189,419,200,405,200,405,189};
	int open[20]={295,269,335,269,335,284,295,284,295,269};
	int box[20]={80,89,419,89,419,289,80,289,80,89};
	int opensave[20]={80,89,419,89,419,100,80,100,80,89};
	int redcross_a[20]={405,89,419,89,419,100,405,100,405,89};
	int box_a[20]={84,117,415,117,415,266,84,266,84,117};
	ch[1]=0;
	initgraph(&gd,&gm,"C:\\Turboc3\\BGI");
	errorcode=graphresult();
	if(errorcode!=0)
	{
		printf("FATAL ERROR! \nGraphics card not initialized");
		getch();
		exit(0);
	}
	clrscr();
	refresh();
	//The undefined loop
	for(;!(button==1&&x>624&&x<639&&y<10);)
	{
		//for scroll botton
		//setfillstyle(2,5);
		//floodfill(635,(uposition()+sclen())/2,5);
		//setfillstyle(1,15);
		//for blinking cursor
		if(i==100)
		{
			for(loopval0=0;loopval0<=0;loopval0++)
			{
				for(loopval1=0;loopval1<=textheight("|");loopval1++)
				putpixel(X_cursor+loopval0,Y_cursor+loopval1,WHITE);
			}
		}
		if(i>=200)
		{
			for(loopval0=0;loopval0<=0;loopval0++)
			{
				for(loopval1=0;loopval1<=textheight("|");loopval1++)
				putpixel(X_cursor+loopval0,Y_cursor+loopval1,GREEN);
			}
			i=0;
		}
		//for scroll
		//settextstyle(deffont,HORZ_DIR,defsize);
		//scrollbtn[20]={

		//For text input
		fflush(stdin);
		if(kbhit()!=0)
		{
			if(tweak==1)
			{
				tweak=0;
				refresh();
			}
			ch[0]=getch();
			if(ch[0]==13)
			ch[0]=10;
			if(ch[0]!=8)
			tempfile[count]=ch[0];
			if(X_cursor==0&&Y_cursor==15&&ch[0]==8)
			beep();
			else
			{
				if(ch[0]=='\n')
				{
					for(a=count-1;;a--)
					{
						if(tempfile[a]!=' '&&tempfile[a]!='\t')
						break;
					}
					count=a+1;

				}
				hidems();
				if((Y_cursor-15)/(textheight("W")+3)>=40)
				Y_cursor=Y_cursor-textheight("W")-3;
				disptext();
				showmouse();
			}
			if(ch[0]!=8)
			count++;
			change++;
		}
		CLKnBTN(&button,&x,&y);
		//for scroll
		if(button==1&&x>=630&&x<639)
		{
			showmouse();
			CLKnBTN(&button,&x,&y);
			//calculus(mode);
			if(y>=upositio&&button==1)
			for(;;)
			{
				showmouse();
				CLKnBTN(&button,&x,&y);
				if(button!=1)
				{
					//upositio=y;
					//printf("%d\n",upositio);
					tweak=1;
					calculus(mode);
					hidems();
					upositio=y;
					refresh();
					break;
				}
				if(button!=1)
				break;
			}
		}
		//Dropdown For file
		if(button==1&&x>10&&x<60&&y>=0&&y<=10)
		{
		    hidems();
		    delay(100);
		    setcolor(GREEN);
		    fillpoly(5,filedd);
		    line(10,12,10,90);
		    outtextxy(12,15,"New");
		    outtextxy(12,30,"OPEN");
		    outtextxy(12,45,"SAVE");
		    outtextxy(12,60,"SAVE AS");
		    outtextxy(12,75,"EXIT");
		    showmouse();
		    for(;x>0&&x<80&&y<90;)
		    {
			CLKnBTN(&button,&x,&y);
			if(button==1&&x>10&&y>12&&y<30)
			{
				  hidems();
				  refresh();
				  delay(100);
				  showmouse();
				  if(change!=0)
				  {
					//Warning window
					hidems();
					refresh();
					beep();
					setcolor(8);
					fillpoly(5,unsavealert);
					setfillstyle(1,BLUE);
					fillpoly(5,topalert);
					setfillstyle(1,7);
					fillpoly(5,no);
					fillpoly(5,yes);
					fillpoly(5,cancel);
					setfillstyle(1,RED);
					fillpoly(5,redcross);
					//floodfill(217,198,5);
					line(405,189,405,200);
					//floodfill(407,192,5);
					setfillstyle(1,15);
					setcolor(WHITE);
					outtextxy(409,192,"X");
					setcolor(GREEN);
					outtextxy(283,273,"Yes");
					setcolor(RED);
					outtextxy(323,273,"No");
					setcolor(6);
					outtextxy(356,273,"Cancel");
					setcolor(RED);
					outtextxy(220,205,"FILE NOT SAVED!");
					settextstyle(0,HORIZ_DIR,1);
					setcolor(8);
					outtextxy(220,225,"Do you wish to save?");
					setcolor(WHITE);
					outtextxy(220,191,"Warning!");
				       //End of making warning window
					for(;;)
					{

					      CLKnBTN(&button,&x,&y);
					      showmouse();
					     // if(button==1)
					      {
						if(button==1&&y>269&&y<284&&x>279&&x<309)
						{
							hidems();
							refresh();
							outtextxy(100,100,"Duplicated punch");
							delay(2000);
							//change=0;//only for checking
							break;
						}

					      }//	&&((x>279&&x<309)||(x>314&&x<354)||(x>
						if(change==0)
						break;
					}
				  }

				}
			else if(button==1&&x>10&&y>30&&y<45)
			{
				  hidems();
				  refresh();
				  delay(100);
				  showmouse();
				  if(change!=0)
				  {
					//Open window
					hidems();
					refresh();
					beep();
					setcolor(8);
					fillpoly(5,box);
					setcolor(8);
					fillpoly(5,box_a);
					setfillstyle(1,BLUE);
					fillpoly(5,opensave);
					setfillstyle(1,7);
					fillpoly(5,open);
					fillpoly(5,cancel);
					setfillstyle(1,RED);
					fillpoly(5,redcross_a);
					//floodfill(217,198,5);
					line(405,89,405,100);
					//floodfill(407,192,5);
					setfillstyle(1,15);
					setcolor(WHITE);
					outtextxy(409,91,"X");
					setcolor(GREEN);
					outtextxy(300,273,"Open");
					setcolor(6);
					outtextxy(356,273,"Cancel");
					setcolor(RED);
					outtextxy(85,105,"FILE DIRECTORY");
					setcolor(WHITE);
					outtextxy(82,92," Open File");
				       //End of making open window
					for(;;)
					{

					      CLKnBTN(&button,&x,&y);
					      showmouse();
					     // if(button==1)
					      {
						if(button==1&&y>269&&y<284&&x>279&&x<309)
						{
							hidems();
							refresh();
							outtextxy(100,100,"Duplicated punch");
							delay(2000);
							change=0;//only for checking
							break;
						}

					      }//	&&((x>279&&x<309)||(x>314&&x<354)||(x>
						if(change==0)
						break;
					}
				  }

				}
			else if(button==1&&x>10&&y>45&&y<75)
			{
				  hidems();
				  refresh();
				  delay(100);
				  showmouse();
				  if(change!=0)
				  {
					//Save window
					hidems();
					refresh();
					beep();
					setcolor(8);
					fillpoly(5,box);
					setcolor(8);
					fillpoly(5,box_a);
					setfillstyle(1,BLUE);
					fillpoly(5,opensave);
					setfillstyle(1,7);
					fillpoly(5,open);
					fillpoly(5,cancel);
					setfillstyle(1,RED);
					fillpoly(5,redcross_a);
					//floodfill(217,198,5);
					line(405,89,405,100);
					//floodfill(407,192,5);
					setfillstyle(1,15);
					setcolor(WHITE);
					outtextxy(409,91,"X");
					setcolor(GREEN);
					outtextxy(300,273,"Save");
					setcolor(6);
					outtextxy(356,273,"Cancel");
					setcolor(RED);
					outtextxy(85,105,"FILE DIRECTORY");
					setcolor(WHITE);
					outtextxy(82,92," Save File");
				       //End of making save window
					for(;;)
					{

					      CLKnBTN(&button,&x,&y);
					      showmouse();
					     // if(button==1)
					      {
						if(button==1&&y>269&&y<284&&x>279&&x<309)
						{
							hidems();
							refresh();
							outtextxy(100,100,"Duplicated punch");
							delay(2000);
							change=0;//only for checking
							break;
						}

					      }//	&&((x>279&&x<309)||(x>314&&x<354)||(x>
						if(change==0)
						break;
					}
				  }

				}
		    }
		    hidems();
		    refresh();
		}
		//For edit
		if(button==1&&x>62&&x<105&&y>=0&&y<=10)
		{
		    hidems();
		    delay(100);
		    setcolor(11);
		    fillpoly(5,editdd);
		    line(62,12,62,90);
		    outtextxy(62,15,"CUT");
		    outtextxy(62,30,"COPY");
		    outtextxy(62,45,"PASTE");
		    outtextxy(62,60,"FIND");
		    outtextxy(62,75,"REPLACE");
		    showmouse();
		    for(;x>52&&x<132&&y<90;)
		    {
			CLKnBTN(&button,&x,&y);
		    }
		  hidems();
		  refresh();
		}
		//For FORMAT
		if(button==1&&x>107&&x<160&&y>=0&&y<=10)
		{
		    hidems();
		    delay(100);
		    setcolor(BLUE);
		    fillpoly(5,formatdd);
		    line(105,12,105,180);
		    settextstyle(0,HORIZ_DIR,1);
		    outtextxy(107,15,"SIZE");
		    settextstyle(deffont,HORIZ_DIR,1);
		    outtextxy(107,30,"sample");
		    settextstyle(deffont,HORIZ_DIR,2);
		    outtextxy(107,45,"sample");
		    settextstyle(deffont,HORIZ_DIR,3);
		    outtextxy(107,60,"sample");
		    settextstyle(deffont,HORIZ_DIR,4);
		    outtextxy(107,75,"sample");
		    settextstyle(deffont,HORIZ_DIR,5);
		    outtextxy(107,90,"sample");
		    settextstyle(deffont,HORIZ_DIR,6);
		    outtextxy(107,105,"sample");
		    settextstyle(0,HORIZ_DIR,1);
		    outtextxy(107,130,"Fonts");
		    settextstyle(0,HORIZ_DIR,1);
		    outtextxy(107,145,"sample");
		    settextstyle(2,HORIZ_DIR,1);
		    outtextxy(107,160,"Sample");
		    settextstyle(0,HORIZ_DIR,1);
		    showmouse();
		    for(;x>97&&x<177&&y<180;)
		    {
			CLKnBTN(&button,&x,&y);
		    }
		    hidems();
		    refresh();
		}
		//For About
		if(button==1&&x>167&&x<215&&y>=0&&y<=10)
		{
		refresh();
		hidems();
		delay(100);
		showmouse();
		setcolor(11);
		fillpoly(5,aboutdd);
		line(167,12,167,45);
		outtextxy(167,15,"HELP");
		outtextxy(167,30,"ABOUT US");
		for(;x>152&&x<233&&y<45;)
		 {
			CLKnBTN(&button,&x,&y);
			if(button==1&&x>167&&y>12&&y<30)
			{
				  hidems();
				  refresh();
				  delay(100);
				  showmouse();
				  if(change!=0)
				  {
					//Help window
					hidems();
					refresh();
					beep();
					setcolor(8);
					fillpoly(5,unsavealert);
					setfillstyle(1,BLUE);
					fillpoly(5,topalert);
					setfillstyle(1,7);
					fillpoly(5,cancel);
					setfillstyle(1,RED);
					fillpoly(5,redcross);
					//floodfill(217,198,5);
					line(405,189,405,200);
					//floodfill(407,192,5);
					setfillstyle(1,15);
					setcolor(WHITE);
					outtextxy(409,192,"X");
					setcolor(6);
					outtextxy(356,273,"Cancel");
					settextstyle(0,HORIZ_DIR,1);
					setcolor(8);
					outtextxy(220,225," No comment.");
					setcolor(WHITE);
					outtextxy(220,191," Help");
				       //End of making help window
					for(;;)
					{

					      CLKnBTN(&button,&x,&y);
					      showmouse();
					     // if(button==1)
					      {
						if(button==1&&y>269&&y<284&&x>279&&x<309)
						{
							hidems();
							refresh();
							outtextxy(100,100,"Duplicated punch");
							delay(2000);
							change=0;//only for checking
							break;
						}

					      }//	&&((x>279&&x<309)||(x>314&&x<354)||(x>
						if(change==0)
						break;
					}
				  }

				}
			if(button==1&&x>167&&y>30&&y<45)
			{
				  hidems();
				  refresh();
				  delay(100);
				  showmouse();
				  if(change!=0)
				  {
					//About us window
					hidems();
					refresh();
					beep();
					setcolor(8);
					fillpoly(5,unsavealert);
					setfillstyle(1,BLUE);
					fillpoly(5,topalert);
					setfillstyle(1,7);
					fillpoly(5,cancel);
					setfillstyle(1,RED);
					fillpoly(5,redcross);
					//floodfill(217,198,5);
					line(405,189,405,200);
					//floodfill(407,192,5);
					setfillstyle(1,15);
					setcolor(WHITE);
					outtextxy(409,192,"X");
					setcolor(6);
					outtextxy(356,273,"Cancel");
					settextstyle(0,HORIZ_DIR,1);
					setcolor(RED);
					outtextxy(220,208," Developed By:");
					setcolor(8);
					outtextxy(220,225," Yadav");
					setcolor(8);
					outtextxy(220,240," Sirish");
					setcolor(8);
					outtextxy(220,255," Pawan");
					setcolor(WHITE);
					outtextxy(220,191," About us");
				       //End of About us window
					for(;;)
					{

					      CLKnBTN(&button,&x,&y);
					      showmouse();
					     // if(button==1)
					      {
						if(button==1&&y>269&&y<284&&x>279&&x<309)
						{
							hidems();
							refresh();
							outtextxy(100,100,"Duplicated punch");
							delay(2000);
							change=0;//only for checking
							break;
						}

					      }//	&&((x>279&&x<309)||(x>314&&x<354)||(x>
						if(change==0)
						break;
					}
				  }

				}


		 }
		refresh();
		}

		i++;
	}
	closegraph();
	printf("GoodBye");
	getch();
}
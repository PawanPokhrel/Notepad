#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<string.h>
#include"mouse.cpp"
#include"textbox.h"
//char h[]="k";
class window{
	char name[100];
	char mainButton[20][50];
	char mainDrop[20][20][50];
	char fieldButton[20][50];
	int corfieldButton[41];
	//class textBox fieldtextbox;
	int numDrop[20];
	int numMainButton,numfieldButton,numfieldTextbox,numtextArea;
	//char *fieldButton,*fieldtextbox,*fieldtextArea;
	int X,Y,length,breadth,*corfieldButtons,*corfieldtextBox,*corfieldtextArea;
	int topColor,bgColor;
	unsigned int Handle[81][5],stuffsTotal;
	public:
		void drawWindow(int,int,int,int);
		void setfieldtextBox(char *,int *,int);
		void setmainButton(char *,int);
		void setfieldButton(char *,int *,int);
		void drawfieldButton();
		void mouseHandle();
		void drawDrop(int);
		void setmainDrop(char *,int,int);
		void setTopColor(int);
		int Wclick(int,int);
		void setmainButton(int);
		void setname(char *);
		window();
};
void main()
{
	int gd=DETECT,gm;
	int a;
	initgraph(&gd,&gm,"C:\\turboc3\\bgi");
	if(graphresult()!=0)
	{
		printf("Graphics not initialized");
		getch();
	}
	//class textBox p;
	class window mainWindow;
	char mainWindow_mainButton[4][50]={"File","Edit","Format","About"};
	char fileDrop[5][50]={"New","Open","Save","Save As","Exit"};
	char editDrop[5][50]={"Cut","Copy","Paste","Find","Replace"};
	char formatDrop[6][50]={"Wrapped","Unwrapped","RED","GREEN","WHITE","BLUE"};
	char aboutDrop[2][50]={"Help","Creators"};
	char fieldButton[2][50]={"Hello","Matters and the universe are same"};
	int corfieldButton[4]={50,50,100,100};
	char main_window_name[]="Main Window";
	//initgraph(&gd,&gm,"C:\\turboc3\\bgi");
	mainWindow.setmainButton(mainWindow_mainButton[0],4);
	mainWindow.setmainDrop(fileDrop[0],0,5);
	mainWindow.setmainDrop(editDrop[0],1,5);
	mainWindow.setmainDrop(formatDrop[0],2,6);
	mainWindow.setmainDrop(aboutDrop[0],3,2);
	mainWindow.setfieldButton(fieldButton[0],corfieldButton,2);
	mainWindow.setname(main_window_name);
	//printf("\n\n\n");
	mainWindow.drawWindow(0,0,400,400);//getmaxx(),getmaxy());
	//getch();
	//p.drawBox(0,0,200,200);
	showmouse();
	//if(getch()=='a')
	  //	mainWindow.drawfieldButton();
	//else
	  //	mainWindow.drawDrop(3);
	//mouse(&click,&msX,&msY);
	int i;
	a=1;
	for(;;)
	{
		mouse(&click,&msX,&msY);
		if(click==1)
		{
		  a=mainWindow.Wclick(msX,msY);
		  switch(a)
		  {
		     case 0:
		     {
			hidems();
			mainWindow.drawDrop(0);
			delay(100);
			showmouse();
			for(;a!=-1;)
			{
			  mouse(&click,&msX,&msY);
			  if(click==1)
			  {
			     a=mainWindow.Wclick(msX,msY);
			     switch(a)
			     {
			       case 1:
			       {

			       }
			       case 2:
			       {

			       }
			       case 3:
			       {

			       }
			       case 4:
			       {

			       }
			     }
			  }
			}
		     }
		     clearviewport();
		     mainWindow.drawWindow(0,0,400,400);
		     break;
		     case 100:
		     {
			for(;a!=-1;)
			{
			  mainWindow.drawDrop(1);
			  showmouse();
			  mouse(&click,&msX,&msY);
			  if(click==1)
			  {
			     a=mainWindow.Wclick(msX,msY);
			     switch(a)
			     case 101:
			     {

			     }
			  }
			}
		     }
		  }

		}
		showmouse();
	}
	if(a==0)
		mainWindow.drawDrop(0);
	getch();
}
void window::drawWindow(int x,int y,int len,int heig)
{
	int i,j,m=0,k=0,l=0;
	X=x;
	Y=y;
	length=len;
	breadth=heig;
	//Setting up the view port
	setviewport(x,y,x+len,y+heig,1);
	//For drawing outer rectangle
	setcolor(topColor);
	setfillstyle(1,bgColor);
	rectangle(x,y+10,x+len,y+heig);
	bar3d(x+1,y+10,x+len,y+heig,1,1);
	//For Top
	setfillstyle(1,topColor);
	bar3d(x,y,x+len,y+10,1,1);
	//For cross Bar
	setcolor(WHITE);
	setfillstyle(1,WHITE);
	bar3d(x+len-13,y,x+len-2,y+8,1,1);
	setcolor(5);
	outtextxy(x+len-10,y+1,"X");
	//For name of Window
	setcolor(WHITE);
	outtextxy(x+3,y+1,name);
	//For main Buttons
	setcolor(WHITE);
	moveto(x+3,Y+12);
	setfillstyle(1,7);
	setcolor(7);
	bar3d(X+2,Y+10,X+length-2,Y+20,0,0);
	j=0;
	setcolor(WHITE);
	for(i=0;i<numMainButton;i++)
	{
		Handle[i+k][1]=X+2+j;
		Handle[i+k][2]=10;
		Handle[i+k][3]=X+2+j+textwidth(mainButton[i])+textwidth(h)-3;
		Handle[i+k][4]=20;
		k=k+numDrop[i];
		outtext(mainButton[i]);
		outtext(" ");
		j=j+textwidth(mainButton[i])+textwidth(h);
		line(X+2+j-3,Y+10,X+2+j-3,Y+20);

	}
	//Setting up the Handle parameters
	j=0;
	k=0;
	for(i=0;i<numMainButton;i++)
	{

		Handle[i+k][0]=i*100;
		m=strlen(mainDrop[i][j]);
		for(j=0;j<numDrop[i];j++)
		{
			if(strlen(mainDrop[i][j])>m)
				m=strlen(mainDrop[i][j]);
		}
		for(j=1;j<=numDrop[i];j++)
		{
			Handle[i+j+k][0]=i*100+j;
			Handle[i+j+k][1]=k*textwidth(h);
			Handle[i+j+k][2]=Y+20+(j-1)*(textwidth(h)+3);
			Handle[i+j+k][3]=(k+m)*(textwidth(h));
			Handle[i+j+k][4]=Y+20+j*(textheight(h)+3);
		}
		j=0;
		k=k+numDrop[i];
	}
	m=i;
	stuffsTotal=k+i;
	for(i=0,j=0;i<corfieldButton[0];i++,j=j+2)
	{
		Handle[i+stuffsTotal][0]=m*100+i;
		Handle[i+stuffsTotal][1]=corfieldButton[j+1];
		Handle[i+stuffsTotal][2]=corfieldButton[j+2];
		Handle[i+stuffsTotal][3]=corfieldButton[j+1]+textwidth(h)*strlen(fieldButton[i]);
		Handle[i+stuffsTotal][4]=corfieldButton[j+2]+textheight(h);
	}
       //	for(j=0;j<(stuffsTotal+i);j++)
	//{
	  //	printf("Handle %d=[(%d,%d),(%d,%d)]\n",Handle[j][0],Handle[j][1],Handle[j][2],Handle[j][3],Handle[j][4]);
	//}
	stuffsTotal=stuffsTotal+i;
	//getch();
}
void window::window()
{
	topColor=BLUE;
	bgColor=WHITE;
	strcpy(name,"New Window");
	numMainButton=0;
}
void window::setmainButton(char *p,int n)
{
	numMainButton=n;
	int i=0,j,k=0;
	for(j=0;;)
	{

		mainButton[i][j]=(*(p+k));
		j++;
		if((k+1)%50==0)
		{
			i++;
			//mainButton[i][j]=0;
			j=0;
			//printf("%s",mainButton[i-1]);
		}
		if(i==n)
			break;
		k++;
	}
	//getch();
}
void window::setmainDrop(char *p,int a,int n)
{
	numDrop[a]=n;
	int i=0,j,k=0;
	for(j=0;;)
	{

		mainDrop[a][i][j]=(*(p+k));
		j++;
		if((k+1)%50==0)
		{
			i++;
			//mainButton[i][j]=0;
			j=0;
			//printf("%s",mainButton[i-1]);
		}
		if(i==n)
			break;
		k++;
	}
}
void window::drawDrop(int a)
{
	int i;
	int m=strlen(mainDrop[a][0]);
	int x1=0,y1,x2,y2,y;
	for(i=0;i<numDrop[a];i++)
	{
		if(strlen(mainDrop[a][i])>m)
			m=strlen(mainDrop[a][i]);
	}
	for(i=0;i<a;i++)
	{
		x1=x1+strlen(mainButton[i])+1;
	}
	x1=X+x1*textwidth(h);
	x2=x1+m*textwidth(h)+5;
	y1=Y+20;
	y2=Y+20+(textheight(h)+3)*numDrop[a];
	y=2;
	setviewport(x1,y1,x2,y2,1);
	setcolor(7);
	setfillstyle(13,7);
	bar3d(3,1,x2-x1,y2-y1,1,1);
	setcolor(WHITE);
	for(i=0;i<numDrop[a];i++)
	{
		outtextxy(5,y,mainDrop[a][i]);
		y=y+textheight(h)+3;
	}
}
void window::setfieldButton(char *p,int *q,int n)
{
	corfieldButton[0]=n;
	int i=0,j,k=0;
	for(j=0;;)
	{

		fieldButton[i][j]=(*(p+k));
		j++;
		if((k+1)%50==0)
		{
			i++;
			//mainButton[i][j]=0;
			j=0;
			//printf("%s",mainButton[i-1]);
		}
		if(i==n)
			break;
		k++;
	}
	for(j=0;j<2*n;j++)
	{
		corfieldButton[j+1]=*(q+j);
	}

}
void window::drawfieldButton()
{
	int i,j;
	setfillstyle(1,8);
	for(i=0,j=1;i<corfieldButton[0];i++,j=j+2)
	{
		setcolor(7);
		bar3d(corfieldButton[j],corfieldButton[j+1],corfieldButton[j]+textwidth(fieldButton[i])+3,corfieldButton[j+1]+textheight(h)+5,1,1);
		setcolor(WHITE);
		outtextxy(corfieldButton[j]+3,corfieldButton[j+1]+3,fieldButton[i]);
	}
}
void window::setname(char *p)
{
	strcpy(name,p);
}
int window::Wclick(int x,int y)
{
	int i;
	for(i=0;i<stuffsTotal;i++)
	{
		//mouse(&click,&msX,&msY);
		//printf
		if(x>Handle[i][1]&&x<=Handle[i][3]&&y>Handle[i][2]&&y<=Handle[i][4])
		{
			return (Handle[i][0]);
		}
	}
	return -1;
}


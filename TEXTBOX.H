#define NOSCROLL 1
#define WRAPPED 1
#define UNWRAPPED 2
char h[]="k";
unsigned char far *key_state=(unsigned char far*)0x00400017;;
class textBox{
	long unsigned int length,height;//textbox position and size
	long unsigned int pHscroll,pVscroll,lenHscroll,lenVscroll;//Scroll bar position and length
	long unsigned int N,NVmax,NHmax,NLVmax,NLHmax,NVline,NHline;//Line attributes
	int msX,msY,clickL,clickR;//Position of mouse
	char text[10000],tempText[10000];//Text length
	int Hfactor,Vfactor;
	int pText;//Text position
	int textMode;//Text Mode
	int textColor,bgColor;//Colors
	public:
		void drawBox(int,int,int,int,int);
		void drawBox(int,int,int,int);
		void writeText(char);
		void selText();
		void setTextMode(int);
		void setTextColor(int);
		void setbgColor(int);
		void Nline();
		void scroll();
		void changedispline();
		int curTp(int,int);
		void pCursor(int);
		void disptext();
		void disptext(int,int);
		textBox();
		void mouseHandle();
		int Hlen(int);
		void blinkCur();
		long unsigned int curX,curY,dispHline,dispVline,X,Y;//Cursor's position
};
void textBox::setTextColor(int a)
{
	if(a>=0&&a<=15&&a!=bgColor)
	textColor=a;
	setcolor(textColor);
}
void textBox::setbgColor(int a)
{
	if(a>=0&&a<=15&&a!=textColor)
	bgColor=a;
	setfillstyle(1,bgColor);
}
void textBox::setTextMode(int a)
{
	int i;
	if(a==1||a==2)
		textMode=a;
	curX=1;
	curY=1;
	pText=0;
	for(i=0;text[i]!=0;i++)
	{
		pCursor(text[i]);
		pText++;
	}
	changedispline();
	scroll();
	disptext();
}
void textBox::mouseHandle()
{
	int curx,cury;
	//printf("We are inside");
	mouse(&click,&msX,&msY);
	if(click==1&&msX>=X&&msY>=Y&&msX<X+length-10&&msY<Y+height-10)
	{
		mouse(&click,&msX,&msY);
		//printf("We are  here");
		curx=dispHline+(msX-X)/(textwidth(h)+1)+1;
		//delay(10);
		cury=dispVline+(msY-Y)/(textheight(h)+3)+1;
	}
	if(curx>Hlen(cury)+1&&cury<=NVline)
	{
		curX=Hlen(cury)+1;
		curY=cury;
	}
	else if(cury<=NVline)
	{
		curX=curx;
		curY=cury;
	}
	pText=curTp(curX,curY);
	delay(100);
	//Text selection using mouse
	if(click==1&&*key_state==4)
	{
		for(;click==1;)
		{
			mouse(&click,&msX,&msY);
			if(msY>=Y&&msY<=(textheight(h)+3)/2&&dispVline>0)
			{
				dispVline--;
				dispHline=0;
			}
			else if(msY>=Y-10-(textheight(h)+3)/2&&dispVline<NVline&&msY<Y+height-10)
			{
				dispVline++;
				dispHline=0;
			}
			cury=dispVline+(msY-Y)/(textheight(h)+3)+1;
			if(msX>=X&&msX<=(textwidth(h)+1)/2&&dispHline>0)
			{
				dispHline--;
			}
			else if(msX>=X+length-10-(textwidth(h)+1)/2&&dispHline+NHmax<Hlen(cury))
			{
				dispHline++;
				//printf("There we go");
			}
			curx=dispHline+(msX-X)/(textwidth(h)+1)+1;
			//delay(10);
			if(curx>Hlen(cury)+1&&cury<=NVline)
			{
				curx=Hlen(cury)+1;
			}
			else if(cury<=NVline)
			{

				curx=curx;
				cury=cury;
			}
			//delay(100);
			hidems();
			if(curTp(curx,cury)>curTp(curX,curY))
				disptext(curTp(curX,curY),curTp(curx,cury));
			else
				disptext(curTp(curx,cury),curTp(curX,curY));
			showmouse();
		}
		int i,j,k,m,l;
		m=curTp(curX,curY);
		l=curTp(curx,cury);
		j=curx;
		k=cury;
		char a;
		a=getch();
		if(a==0)
		{
			a=getch();
			if(a==83)
			{
				if(m>l)
				{
					for(i=l;i<=N;i++)
					{
						text[i]=text[i+(m-l)];
					}
					curX=j;
					curY=k;
					pText=curTp(curX,curY);
				}
				else
				{
					for(i=m;i<=N;i++)
					{
						text[i]=text[i+(l-m)];
					}
				}
			}
		}
		else
		{
			if(*key_state==4&&(a==24||a==3))
			{
				if(m>l)
				{
					for(i=l;i<m;i++)
					{
						tempText[i-l]=text[i];
					}
					tempText[i-l]=0;
				}
				else
				{
					for(i=m;i<l;i++)
					{
						tempText[i-m]=text[i];
					}
					tempText[i-m]=0;
				}
			}
		}
		if(a!=3)
		{
			if(m>l)
			{
				for(i=l;i<=N;i++)
				{
					text[i]=text[i+m-l];
				}
				curX=j;
				curY=k;
				pText=curTp(curX,curY);
			}
			else
			{
				for(i=m;i<=N;i++)
				{
					text[i]=text[i+l-m];
				}
			}
		}
		if(*key_state!=4)
			writeText(a);
		else if(a==22&&tempText[0]!=0)
		{
			i=strlen(tempText);
			for(m=N+i;m>=pText+i;m--)
			{
				text[m]=text[m-i];
			}
			for(i=0;tempText[i]!=0;i++)
			{
				text[pText]=tempText[i];
				pText++;
				pCursor(tempText[i]);
			}
		}
	}
	if(click==1&&msX>=X+length-10&&msX<=X+length&&msY>=pVscroll&&msY<=pVscroll+lenVscroll)
	{
		int p,q;
		p=msX;
		q=msY;
		for(;click==1;)
		{
			mouse(&click,&msX,&msY);
			p=dispVline;
			if(click==1&&msX>=X+length-10&&msX<=X+length&&msY>=Y&&msY<=pVscroll+lenVscroll&&dispVline>0)
			{
				mouse(&click,&msX,&msY);
				if(NVline<NHmax)
					dispVline=0;
				else if(NVline>NHmax&&NVline<NHmax+NLVmax&&(dispVline>0||msY-Y>0))
				{
					dispVline=(msY-pVscroll)/Vfactor;
					//printf("--%d",dispVline);
				}
			}
			scroll();
			delay(100);
			if(p!=dispVline)
			{
				disptext();
			}
		}
	}
	changedispline();
	disptext();
	blinkCur();
	//delay(100);
}
void textBox::blinkCur()
{
	static int j=0,k;
	int i;
	if(j==10000)
		{
			for(j=X+(curX-1-dispHline)*(textwidth(h)+1)+1;j<X+(curX-1-dispHline)*(textwidth(h)+1)+2;j++)
			{
				for(k=Y+(curY-1-dispVline)*(textheight(h)+3)+1;k<=Y+(curY-dispVline)*(textheight(h)+3)-2;k++)
				{
					putpixel(j,k,9);
				}
			}
			j=0;
		}
		if(j==5000)
		{
			for(j=X+(curX-1-dispHline)*(textwidth(h)+1)+1;j<X+(curX-1-dispHline)*(textwidth(h)+1)+2;j++)
			{
				for(k=Y+(curY-1-dispVline)*(textheight(h)+3)+1;k<=Y+(curY-dispVline)*(textheight(h)+3)-2;k++)
				{
					putpixel(j,k,15);
				}
			}
			j=5001;
		}
		j++;
}
void textBox::drawBox(int x,int y,int len,int width,int sm)
{
	int i;
	length=len;
	height=width;
	X=x;
	Y=y;
	lenVscroll=height-10;
	lenHscroll=length-10;
	pVscroll=Y;
	pHscroll=X;
	dispHline=0;
	dispVline=0;
	rectangle(X,Y,X+length,Y+width);
	rectangle(X,Y+width,X+length,Y+width);
	//Maximum no of horizontal and vertical lines inside text box
	bar3d(X,Y,X+length-10,Y+height-10,1,1);
	NHmax=lenHscroll/(textwidth(h)+1);
	NVmax=lenVscroll/(textheight(h)+3);
	//Maximum number of lines before scroll bar stops squeezing
	i=lenVscroll;
	NLVmax=1;
	NLHmax=0;
	while(i-10>10)
	{
		i=i-Vfactor;
		NLVmax++;
	}
	i=lenHscroll;
	while(i-10>10)
	{
		i=i-Hfactor;
		NLHmax++;
	}
}
void textBox::drawBox(int x,int y,int len,int width)
{
	int i;
	length=len;
	height=width;
	X=x;
	Y=y;
	lenVscroll=height-10;
	lenHscroll=length-10;
	pVscroll=Y;
	pHscroll=X;
	curX=1;
	curY=1;
	dispHline=0;
	dispVline=0;
	Hfactor=lenHscroll/100;
	Vfactor=lenVscroll/100;
	setcolor(4);
	rectangle(X,Y,X+length,Y+width);
	rectangle(X,Y+width-10,X+length-10,Y+width);
	rectangle(X+length-10,Y,X+length,Y+width-10);
	//Maximum no of horizontal and vertical lines inside text box
	bar3d(X,Y,X+length-10,Y+height-10,1,1);
	NHmax=lenHscroll/(textwidth(h)+1);
	NVmax=lenVscroll/(textheight(h)+3);
	//Maximum number of lines before scroll bar stops squeezing
	i=lenVscroll;
	NLVmax=1;
	NLHmax=0;
	int j=1;
	while(i-Vfactor>=10)
	{
		i=i-Vfactor;
		j++;
		//printf("%d",NLVmax);
	}
	NLVmax=j;
	//printf("NVmax= %d,NLVmax= %d",NLVmax,NVmax);
	i=lenHscroll;
	while(i-Hfactor>=10)
	{
		i=i-Hfactor;
		NLHmax++;
	}
	//printf("NLHmax=%d",NLHmax);
}
void textBox::selText()
{
   char a;
   int i=curTp(curX,curY);
   int j=curX,k=curY,m,l;
   if(textMode==UNWRAPPED)
   {
	for(;*key_state==2;)
	{
		if(kbhit()!=0)
		{
			if((a=getch())==0)
			{
				a=getch();
				if(a==75)
				{
					if(j!=1)
						j=j-1;
					else if(k!=1)
					{
						k=k-1;
						j=Hlen(k)+1;
					}
					i=curTp(j,k);
				}
				else if(a==77&&N!=0&&text[i]!=0)//For Right Arrow
				{
					if(j-1==Hlen(k)&&k+1<=NVline)
					{
						k=k+1;
						j=1;
					}
					else if(j-1!=Hlen(k))
						j=j+1;
					i=curTp(j,k);
				}
			}
			if(j>NHmax)
			dispHline=j-NHmax;
			else
			dispHline=0;
			if(k>NVmax)
			dispVline=k-NVmax;
			else
			dispVline=0;
			if(i>curTp(curX,curY))
				disptext(curTp(curX,curY),i);
			else
				disptext(i,curTp(curX,curY));
		}
	}
   }
   else
   {
	for(;*key_state==2;)
	{
	    if(kbhit!=0)
	    {
	      if((a=getch())==0)
	      {
		a=getch();
		if(a==75)//Left arrow
		{
			if(j!=1)
				j=j-1;
			else if(k!=1)
			{
				k=k-1;
				j=Hlen(k)+1;
			}
			i=curTp(j,k);
		}
		else if(a==77&&N!=0&&i<N)//Right arrow
		{
			if(j-1==Hlen(curY)&&k+1<=NVline)
			{
				k=k+1;
				j=1;
			}
			else if(j-1!=Hlen(k))
				j=j+1;
			i=curTp(j,k);
		}
	      }
	    if(k>NVmax)
		dispVline=k-NVmax;
	    else
		dispVline=0;
		if(i>curTp(curX,curY))
			disptext(curTp(curX,curY),i);
		else
			disptext(i,curTp(curX,curY));

	    }
	}
   }
   m=curTp(curX,curY);
   l=curTp(j,k);
   a=getch();
   //For deleting the selected characters
   //For delete
   if(a==0)
   {       a=getch();
	if(a==83)
	{
	    if(m>l)
	    {
		for(i=l;i<=N;i++)
		{
		       text[i]=text[i+(m-l)];
		}
		curX=j;
		curY=k;
		pText=curTp(curX,curY);
	    }
	    else
	    {
		for(i=m;i<=N;i++)
		{
			text[i]=text[i+(l-m)];
		}
	    }
	}
   }
   else
   {
       if(*key_state==4&&(a==24||a==3))
       {
	if(m>l)
	{
		for(i=l;i<m;i++)
		{
			tempText[i-l]=text[i];
		}
		tempText[i-l]=0;
	}
	else
	{
		for(i=m;i<l;i++)
		{
			tempText[i-m]=text[i];
		}
		tempText[i-m]=0;
	}
       }
       if(a!=3)
       {
	if(m>l)
	{
		for(i=l;i<=N;i++)
		{
			text[i]=text[i+m-l];
		}
		curX=j;
		curY=k;
		pText=curTp(curX,curY);
	}
       else
       {
		for(i=m;i<=N;i++)
		{
		       text[i]=text[i+l-m];
		}
       }
       if(*key_state!=4)
		writeText(a);
       else if(a==22&&tempText[0]!=0)
       {
		i=strlen(tempText);
		for(m=N+i;m>=pText+i;m--)
		{
			text[m]=text[m-i];
		}
		for(i=0;tempText[i]!=0;i++)
		{
			text[pText]=tempText[i];
			pText++;
			pCursor(tempText[i]);
		}
       }
       }
   }
   disptext();
}
void textBox::writeText(char a)
{
	int k;

		    if(a!=0&&*key_state!=4)
		    {
			if(a==13)
			{
				a=10;
			}
			if(a==8)
			{
				int k;
				Nline();
				if(curX!=1||curY!=1&&a==8)
				{
					pCursor(a);
					if(textMode==WRAPPED)
					{
						pText--;
					}
					else
					pText--;
				}
				for(k=pText;k<=N;k++)
				{

					text[k]=text[k+1];
				}
			}
			else
			{
				Nline();
				int k,l;
				if(a!='\t')
				{
					for(l=N;l>=pText;l--)
						text[l]=text[l-1];
					text[pText]=a;
					pText++;
					pCursor(a);
					text[N+1]=0;
				}
				else
				{
					for(k=0;k<4;k++)
					{
						for(l=N;l>=pText+k;l--)
							text[l]=text[l-1];
						text[pText+k]=' ';
						pCursor(' ');
						Nline();
					}
					text[N+4]=0;
					pText=pText+k;
				}
			}
		    }
		    else if(a==0)
		    {
			a=getch();
			int m;
			m=a+100;
			Nline();
			if(m==183&&text[pText]!=0)
			{
				int k;
				for(k=pText;k<=N;k++)
				{
					text[k]=text[k+1];
				}
				if(m==183)
				{
					pCursor(m);
				}
			}
			else if(*key_state==2)
			{
				selText();
			}

			else
				pCursor(m);
		    }
		    else if(*key_state==4&&(a==1||a==22))
		    {
			if(a==1)
			{
				char p;
				disptext(0,N);
				p=getch();
				if(p!=0&&*key_state!=4)
				{
					for(k=0;k<=N;k++)
					{
						text[k]=0;
					}
					pText=0;
					if(p!=9)
					{
						text[0]=p;
						pText++;
						curX=2;
						curY=1;
					}
					else
					{
						curX=1;
						curY=1;
					}
				}
				else if(p==3||p==24||p==22)
				{
					if(p==3)
					{
						for(k=0;k<=N+1;k++)
						{
							tempText[k]=text[k];
						}
					}
					else if(p==24)
					{
						for(k=0;k<=N;k++)
						{
							tempText[k]=text[k];
							text[k]=0;
						}
						curX=1;
						curY=1;
						pText=0;
					}
					else if(strlen(tempText)!=0)
					{
						pText=0;
						for(k=0;k<strlen(tempText);k++)
						{
							text[k]=tempText[k];
							pCursor(tempText[k]);
							pText++;
						}
						pText=pText;
						text[k]=0;
					}
				}
			}
			else if(a==22&&tempText[0]!=0)
			{
				int i,m;
				i=strlen(tempText);
				for(m=N+i;m>=pText+i;m--)
				{
					text[m]=text[m-i];
				}
				for(i=0;tempText[i]!=0;i++)
				{
					text[pText]=tempText[i];
					pText++;
					pCursor(tempText[i]);
				}
				changedispline();
			}


		    }
		    scroll();
		    disptext();
}
void textBox::disptext()
{
	Nline();
	bar3d(X,Y,X+length-10,Y+height-10,1,1);
	static char q[100][100]={0};
	unsigned char p[100][100];
	int i,NVL,Hin,j,Hout;
	unsigned char a[2];
	int x,y;
	x=X+1;
	y=Y+1;
	a[1]=0;
	NVL=0;
	Hin=0;
	for(i=0;i<NVmax+dispVline;i++)
	{
		for(j=0;j<NHmax;j++)
		{
			p[i][j]=' ';
		}
	}
if(textMode==UNWRAPPED)
{
	x=X+1;
	y=Y+1;
	for(i=0;;)
	{
		if(text[i]=='\n'||text[i]==0)
		{
			if(NVL>=dispVline){
			for(j=0;j<=NHmax;j++)
			{
				if((Hin+dispHline+j)<i)
					p[NVL-dispVline][j]=text[Hin+dispHline+j];
				else
					p[NVL-dispVline][j]=' ';
			}
		 }
			Hin=i+1;
			NVL++;
		}
		if(text[i]==0)
			break;
		i++;
	}
	for(i=0;i<NVmax;i++)
	{
		for(j=0;j<NHmax;j++)
		{
			a[0]=p[i][j];
   			outtextxy(x,y,a);
			if(dispVline==84)
			printf("%c",a[0]);
			//outextxy(x,y,h);
			x=x+textwidth(h)+1;
		}
		y=y+textheight(h)+3;
		x=X+1;
	}
}
else
{
	int m=0;
	for(i=0;;)
	{
		if(text[i]!='\n'&&text[i]!=0)
		{
			p[NVL-dispVline][m]=text[i];
			m++;
		}
		if(m+1==NHmax||text[i]=='\n')
		{
			NVL++;
			if(text[i+1]=='\n'&&m+1==NHmax)
				i=i+1;
			m=0;
		}
		i++;
		if(text[i]==0)
			break;
	}
	x=X+1;
	y=Y+1;
	for(i=0;i<NVmax;i++)
	{
		for(j=0;j<NHmax;j++)
		{
			a[0]=p[i][j];
			outtextxy(x,y,a);
			//outextxy(x,y,h);
			x=x+textwidth(h)+1;
		}
		y=y+textheight(h)+3;
		x=X+1;
	}
}
}
void textBox::Nline()
{
	NVline=0;
	NHline=1;
	int i=0,m=0;
	N=0;
	if(textMode==UNWRAPPED)
	{
		for(;;)
		{
			if(text[i]=='\n'||text[i]==0)
			{
				NVline++;
				m=i-m;
				if(m>NHline)
				{
					NHline=m;
				}
				m=i;
			}
			if(text[i]==0)
			break;
			i++;
		}
		N=i;
	}
	//printf("NVline=%d",NVline);
	else
	{
		for(;;)
		{
			if(m+1==NHmax||text[i]=='\n'||text[i]==0)
			{
				NVline++;
				if(m+1==NHmax&&text[i+1]=='\n')
					i=i+1;
				m=0;
			}
			if(text[i]==0)
			break;
			i++;
			m++;
		}
		N=i;
	}
	//printf("%d",NLVmax);
}
void textBox::pCursor(int a)
{
if(textMode==UNWRAPPED)
{
	if(a==8)//Backspace
	{   if(curX==1){
			curY=curY-1;
			curX=Hlen(curY)+1;
		}
		else
			curX=curX-1;
	}
	else if(a==10)//Newline
	{
		curY=curY+1;
		curX=1;
	}
	else if(a==183)//Delete
	{
		curX=curX;
		curY=curY;
	}
	else if(a==172&&curY!=1)//For Upward Arrow
	{
		curY=curY-1;
		if(curX>Hlen(curY))
		{
			curX=Hlen(curY)+1;
		}
		else
			curX=curX;
		pText=curTp(curX,curY);
	}
	else if(a==180&&curY+1<=NVline)//For Downwaard Arrow
	{
		curY=curY+1;
		if(curX>Hlen(curY))
		{
			curX=Hlen(curY)+1;
		}
		else
			curX=curX;
		pText=curTp(curX,curY);
	}
	else if(a==175)//Left arrow
	{
		if(curX!=1)
			curX=curX-1;
		else if(curY!=1)
		{
			curY=curY-1;
			curX=Hlen(curY)+1;
		}
		pText=curTp(curX,curY);
	}
	else if(a==177&&N!=0&&text[pText]!=0)//For Right Arrow
	{
		if(curX-1==Hlen(curY)&&curY+1<=NVline)
		{
			curY=curY+1;
			curX=1;
		}
		else if(curX-1!=Hlen(curY))
			curX=curX+1;
		pText=curTp(curX,curY);
	}
	else if((a>=97&&a<=122)||(a>=65&&a<=90)||a==32)//Displayable characters
	curX=curX+1;
	changedispline();
}
/*For Wrapped Mode*/
else
{
	if(a==8)//Backspace
	{   if(curX==1||(curY!=1&&curX==2&&text[pText-2]!='\n')){
			curY=curY-1;
			curX=Hlen(curY)+1;
		}
		else
			curX=curX-1;
	}
	else if(a==10)//Newline
	{
		curY=curY+1;
		curX=1;
	}
	else if(a==183)//Delete
	{
		curX=curX;
		curY=curY;
	}
	else if(a==172&&curY!=1)//For Upward Arrow
	{
		curY=curY-1;
		if(curX>Hlen(curY))
		{
			curX=Hlen(curY)+1;
		}
		else
			curX=curX;
		pText=curTp(curX,curY);
	}
	else if(a==180&&curY+1<=NVline)//For Downwaard Arrow
	{
		curY=curY+1;
		if(curX>Hlen(curY))
		{
			curX=Hlen(curY)+1;
		}
		else
			curX=curX;
		pText=curTp(curX,curY);
	}
	else if(a==175)//Left arrow
	{
		if(curX!=1)
			curX=curX-1;
		else if(curY!=1)
		{
			curY=curY-1;
			curX=Hlen(curY)+1;
		}
		pText=curTp(curX,curY);
	}
	else if(a==177&&N!=0&&pText<N)//Right arrow
	{
		if(curX-1==Hlen(curY)&&curY+1<=NVline)
		{
			curY=curY+1;
			curX=1;
		}
		else if(curX-1!=Hlen(curY))
			curX=curX+1;
		pText=curTp(curX,curY);
	}
	else if(a!=180&&a!=172&&a!=177&&a!=175)//Displayable characters
	{
		if(curX>=NHmax)
		{
			if(a!=10)
			curX=2;
			else
			curX=1;
			curY=curY+1;
		}
		else
			curX=curX+1;

	}
	changedispline();
}
}
textBox::textBox()
{
	int i;
	pText=0;
	text[pText]=0;
	for(i=0;i<10000;i++)
		text[i]=0;
	textMode=1;
	bgColor=GREEN;
	textColor=WHITE;
	curX=1;
	dispVline=0;
	dispHline=0;
	curY=1;
	N=0;
}
void textBox::changedispline()
{
	static int b=0;
	if(textMode==2)
	{
	if(curX-dispHline==NHmax+1)
	{
		dispHline++;
	}
	else if(curX-dispHline==0)
	{
  		dispHline--;
	}
	else if(curX==1)
	{
		dispHline=0;
	}
	else if(curX==Hlen(curY)+1)
	{
		if(curX>NHmax)
		{
			dispHline=curX-NHmax;
		}
		else
			dispHline=0;
	}
	}
	else
		dispHline=0;
 	if((curY-dispVline)==NVmax+1)
	{
		dispVline++;
	}
	else if(curY-dispVline==0)
	{
		dispVline--;
	}
}
int textBox::Hlen(int a)
{
	int i=0,NVL=0,Hin=0;
if(textMode==UNWRAPPED)
{
	for(;;)
	{
		if(text[i]=='\n'||text[i]==0||i==0)
		{
			if(NVL==a-1)
			{
				if(i==0)
				Hin=0;
				else
				Hin=i+1;
			}
			NVL++;
		}
		if(NVL>a)
		{
			return (i-Hin);
		}
		i++;
	}
}
else
{
	int m=0;
	i=0;
	for(;;)
	{
		if(m+1==NHmax||i==0||text[i]=='\n'||text[i]==0)
		{
			if(m+1==NHmax&&text[i+1]=='\n')
			{
				i=i+1;
			}
			if(NVL==a-1)
			{
				if(i==0)
					Hin=0;
				else if(m+1==NHmax)
					Hin=i;
				else
					Hin=i+1;
			}
				m=0;
			NVL++;
		}
		if(NVL>a)
		{
			return(i-Hin);
		}
		i++;
		m++;
	}
}
}
void textBox::scroll()
{
	static int p=lenVscroll,q=pVscroll,r=lenHscroll,s=pHscroll;
	static int w=0;
	//For Length of Vertical scroll
	//printf("%d",pText);
	if(NVline>NVmax&&NVline<NLVmax+NVmax)
	{
   		lenVscroll=height-10-(NVline-NVmax)*Vfactor;
	}
	else if(NVline>=NVmax+NLVmax)
	{
		lenVscroll=10;
	}
	//For Length of Horizontal scroll
	if(NHline>NHmax&&NHline<NHmax+NLHmax)
	{
		lenHscroll=length-10-(NHline-NHmax)*Hfactor;
		//printf("Here we go %d",lenHscroll);
	}
	if(NHline>=NHmax+NLHmax)
	{
		lenHscroll=10;
	}
	//For Vertical scroll position
	if(NVline<NLVmax+NVmax)
	{
		pVscroll=Y+dispVline*Vfactor;
	}
	else if(NVline>=NLVmax+NVmax)
	{
		pVscroll=Y+(curY*Vfactor*NLVmax)/NVline;
	}
	//For Horizontal scroll position
	if(NHline<NLHmax+NHmax)
	{
		pHscroll=X+dispHline*Hfactor;
	}
	else if(NHline>=NLHmax+NHmax)
	{
		if(dispHline==0)
		pHscroll=X;
		else
			pHscroll=X+((curX-1)*Hfactor*NLHmax)/(NHline);
	}
	//Scroll box coordinates
	int Vscroll[]={X+length-10,Y,X+length,Y,X+length,Y+height-10,X+length-10,Y+height-10,X+length-10,Y};
	int Hscroll[]={X,Y+height-10,X+length-10,Y+height-10,X+length-10,Y+height,X,Y+height,X,Y+height-10};
	if(p!=lenVscroll||q!=pVscroll||w==0)
	{
		setfillstyle(1,bgColor);
		fillpoly(5,Vscroll);
		setfillstyle(1,7);
		setcolor(3);
		bar3d(X+length-10,pVscroll,X+length,pVscroll+lenVscroll,1,1);
		setfillstyle(1,bgColor);
		p=lenVscroll;
		q=pVscroll;
	}
	if(w==0||r!=lenHscroll||s!=pHscroll)
	{
		setfillstyle(1,bgColor);
		fillpoly(5,Hscroll);
		setfillstyle(1,7);
		setcolor(3);
  		bar3d(pHscroll,Y+height-10,pHscroll+lenHscroll,Y+height,1,1);
		setfillstyle(1,bgColor);
		r=lenHscroll;
		s=pHscroll;
  	}
	w++;
	setcolor(textColor);
	printf("%d",dispVline);

}
int textBox::curTp(int a,int b)
{
	int i=0,m=0;
if(textMode==UNWRAPPED)
{
	for(;m<b;)
	{
		if(text[i]=='\n'||i==0)
		{
			m++;
		}
		i++;
		if(text[i]==0)
			break;
	}
	if(i==1)
		i=0;
	return (i+a-1);
}
else
{
	int j=0;
	for(;m<b;)
	{
		if(j+1==NHmax||text[i]=='\n'||i==0)
		{
			m++;
			if(j+1==NHmax&&text[i+1]=='\n')
				i=i+1;
			if(m!=b)
			j=0;
		}
		i++;
		j++;
	}
	if(j==NHmax)
		i=i-1;
	if(i==1)
		i=0;
	return(i+a-1);
}
}
void textBox::disptext(int r,int q)
{
	unsigned char p[100][100];
	int i,NVL,Hin,j,Hout;
	unsigned char a[2];
	int x,y;
	x=X+1;
	y=Y+1;
	a[1]=0;
	NVL=0;
	Hin=0;
	//setcolor(bgColor);
	for(i=0;i<NVmax;i++)
	{
		for(j=0;j<NHmax;j++)
		{
			p[i][j]=' ';
		}
	}
	//setcolor(textColor);
	x=X+1;
	y=Y+1;
if(textMode==UNWRAPPED)
{
	//For displaying the selected characters
	j=0;
	NVL=0;
	x=X+1;
	y=Y+1;
	for(i=0;;)
	{
		if(text[i]=='\n'||text[i]==0)
		{
			if(NVL>=dispVline){
			for(j=0;j<=NHmax;j++)
			{
				if((Hin+dispHline+j)<q&&(Hin+dispHline+j)>=r)
					p[NVL-dispVline][j]=219;
			}
			}
			Hin=i+1;
			NVL++;
		}
		if(text[i]==0)
		break;
		i++;
	}
	for(i=0;i<NVmax;i++)
	{
		for(j=0;j<NHmax;j++)
		{
			if(p[i][j]==219)
			{
				a[0]=219;
				setcolor(RED);
				outtextxy(x,y,a);
			}
			else
			{
				a[0]=219;
				setcolor(bgColor);
				outtextxy(x,y,a);
			}
			x=x+textwidth(h)+1;
		}
		y=y+textheight(h)+3;
		x=X+1;
	}
	//End of display of selected characters
	//For displaying the other characters
	NVL=0;
	Hin=0;
	j=0;
	x=X+1;
	y=Y+1;
	for(i=0;;)
	{
		if(text[i]=='\n'||text[i]==0)
		{
			if(NVL>=dispVline){
			for(j=0;j<=NHmax;j++)
			{
				if((Hin+dispHline+j)<i)
					p[NVL-dispVline][j]=text[Hin+dispHline+j];
				else
					p[NVL-dispVline][j]=' ';
			}
			}
			Hin=i+1;
			NVL++;
		}
		if(text[i]==0)
		break;
		i++;
	}
	setcolor(textColor);
	for(i=0;i<NVmax;i++)
	{
		for(j=0;j<NHmax;j++)
		{
		       a[0]=p[i][j];
		       outtextxy(x,y,a);
		       x=x+textwidth(h)+1;
		}

		y=y+textheight(h)+3;
		x=X+1;
	}

}
//For Wrapped Mode
else
{
	int m=0;
	NVL=0;
	for(i=0;;)
	{
		if(text[i]!='\n'&&text[i]!=0)
		{
			if(i>=r&&i<q)
			p[NVL-dispVline][m]=219;
			else
			p[NVL-dispHline][m]=' ';
			m++;
		}
		if(m+1==NHmax||text[i]=='\n')
		{
			NVL++;
			if(text[i+1]=='\n'&&m+1==NHmax)
				i=i+1;
			m=0;
		}
		i++;
		if(text[i]==0)
			break;
	}
	for(i=0;i<NVmax;i++)
	{
		for(j=0;j<NHmax;j++)
		{
			if(p[i][j]==219)
			{
				setcolor(RED);
				a[0]=219;
				outtextxy(x,y,a);
			}
			else
			{
				setcolor(bgColor);
				a[0]=219;
				outtextxy(x,y,a);
			}
			x=x+textwidth(h)+1;
		}
		y=y+textheight(h)+3;
		x=X+1;
	}
	m=0;
	NVL=0;
	for(i=0;;)
	{
		if(text[i]!='\n'&&text[i]!=0)
		{
			p[NVL-dispVline][m]=text[i];
			m++;
		}
		if(m+1==NHmax||text[i]=='\n')
		{
			NVL++;
			if(text[i+1]=='\n'&&m+1==NHmax)
				i=i+1;
			m=0;
		}
		i++;
		if(text[i]==0)
			break;
	}
	x=X+1;
	y=Y+1;
	setcolor(textColor);
	for(i=0;i<NVmax;i++)
	{
		for(j=0;j<NHmax;j++)
		{
			a[0]=p[i][j];
			outtextxy(x,y,a);
			x=x+textwidth(h)+1;
		}
		y=y+textheight(h)+3;
		x=X+1;
	}

}
}


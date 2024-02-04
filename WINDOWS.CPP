#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
#include<dir.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<fcntl.h>
#include<process.h>

void BrowserFrame();
void SubBrowserFrame();
void Header();
void FilePopupMenu();
void RightButtonPopUpMenu(int x,int y);
void Drive();
void EnteringDrive(int,int);
void DriveBox(int,int,int,int,int,int,int,int);
void HighlightedDriveColor();
void Back();
void PopUpMenu(int,int);
void createFolderBox();
void createDeleteBox();
void HelpPopupMenu();
void createHelpBox();
void EditPopupMenu();
void ScrollDown();
void ScrollUp();
void BFrame();

char DriveSpecifier[][50]={"C:","D:","E:","F:","G:","H:","I:","J:","K:","L:","M:","N:","O:","P:"};
char creFol[][50]={"C:","D:","E:","F:","G:","H:","I:","J:","K:","L:","M:","N:","O:","P:"};
char FolderSpecifier[100][100];
int D,fol,FolderNo=100,BackValue=0,enter=0,EnterValue=100;
int click1=0,click2=0,click3=0,page=0,scroll=0;

//**************************/// Mouse Pointer \\\***************************//
void MouseReset()
{
	union REGS r;
	r.x.ax=0;
	int86(0x33,&r,&r);
	if(int(r.x.ax)!=-1)
	{
		printf("Hardware failure !");
		exit(1);
	}
}

void MouseOn()
{
	union REGS r;
	r.x.ax=1;
	int86(0x33,&r,&r);
}

void MouseOff()
{
	union REGS r;
	r.x.ax=2;
	int86(0x33,&r,&r);
}

void GetPosition(int *x,int *y)
{
	union REGS r;
	r.x.ax=3;
	int86(0x33,&r,&r);
	*x=r.x.cx;
	*y=r.x.dx;
}

int LeftButtonPressed()
{
	union REGS r;
	r.x.ax=3;
	int86(0x33,&r,&r);
	return(r.x.bx & 1);
}

int RightButtonPressed()
{
	union REGS r;
	r.x.ax=3;
	int86(0x33,&r,&r);
	return(r.x.bx & 2);
}
//***********************/// END OF MOUSE POINTER \\\ **********************//

//******************************/// FOLDER \\\******************************//
int FileAndFolder(char spec[][50])
{
	int i=0,k=110;
	DIR *dirp = opendir(spec[FolderNo]);
	int errno=0;
	struct dirent * dp;
	fol=0;

	while (dirp)
	{
		errno = 0;
		if ((dp = readdir(dirp)) != NULL)
		{
			if(strcmp(dp->d_name,".")==0||strcmp(dp->d_name,"..")==0);

			else
			{
				strcpy(FolderSpecifier[i],dp->d_name);
				setcolor(4);
				settextstyle(2,0,5);
				outtextxy(160,k,FolderSpecifier[i]);
				fol++;
				i++;
				k+=15;
			}
		}

		else
		{
			if (errno == 0)
			{
				closedir(dirp);
				return 0;
			}
			closedir(dirp);
			return -1;
		}
	}
return 0;
}
//***************************/// END OF FOLDER \\\**************************//

void button_border(int x1,int y1,int x2,int y2,int col)
  {
	int first_color,second_color;
	if(col==15)
	  {
	      first_color=15;
	      second_color=0;
	  }
	else
	  {
	      first_color=0;
	      second_color=15;
	  }
	setcolor(first_color);
	line(x1,y1,x2,y1);
	line(x1,y1,x1,y2);
	setcolor(second_color);
	line(x2,y1,x2,y2);
	line(x1,y2,x2,y2);

}

void permission()
  {
     setcolor(7);
     rectangle(200,125,495,283);
     setfillstyle(1,15);
     bar(201,126,494,282);
     setfillstyle(1,1);
     bar(201,126,494,140);
     settextstyle(SMALL_FONT,HORIZ_DIR,4);
     setcolor(7);
     outtextxy(210,127,"User Account Control");
     line(201,141,494,141);
     line(201,175,494,175);
     setfillstyle(1,9);
     bar(201,142,494,175);
     settextstyle(SMALL_FONT,HORIZ_DIR,5);
     setcolor(0);
     outtextxy(210,142,"Do you want to allow this program");
     settextstyle(SMALL_FONT,HORIZ_DIR,5);
     outtextxy(210,156,"to make changes to this computer?");

     settextstyle(SMALL_FONT,HORIZ_DIR,4);
     outtextxy(220,185,"Project Name : WINDOWS EXPLORER ");
     outtextxy(220,220,"Devoloper    :  RASEL AHAMMED");
     setfillstyle(1,7);
     bar(370,260,420,275);
     settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
     outtextxy(385,265,"Yes");
     button_border(370,260,420,275,15);
     setfillstyle(1,7);
     bar(425,260,475,275);
     outtextxy(445,265,"No");
     button_border(425,260,475,275,15);

}

void shed_box(int x1, int y1, int x2, int y2, int color, int pattern,int condition, int thick){
  int i,left,right,top,bottom;

  setfillstyle(1,0);// Outside color
  bar(x1-1,y1-1,x2+1,y2+1);

  if(condition== 1){
	left = top =    WHITE;
	right =bottom = DARKGRAY;
  }

  if(condition ==0){
	 left = top =  DARKGRAY;
	 right =bottom= WHITE;
  }

  if(condition == 2){
	 left = top = DARKGRAY; // WHITE;
	 right =bottom =LIGHTBLUE;
  }

  if(condition == 3){
	 left = top =   LIGHTBLUE;
	 right =bottom =DARKGRAY;//WHITE;
  }

  setfillstyle(pattern,color); // Inside bar
  bar(x1,y1,x2,y2);

  setcolor(top);
  for(i=0;i<thick;i++)
	  line(x1+i,y1+i,x2-i,y1+i);// TOP

  setcolor(left);
  for(i=0;i<thick;i++)
	  line(x1+i,y1+i,x1+i,y2-i);//LEFT

  setcolor(right);
  for(i=0;i<thick;i++)
	  line(x2-i,y1+i,x2-i,y2-i);// RIGHT

  setcolor(bottom);
  for(i=0;i<thick;i++)
	  line(x1+i,y2-i,x2-i,y2-i);// BOTTOM

}

void welcome()
  {

	int n,d=0,x=0,i=1;
	char *ch[]={"W","E","L","C","O","M","E","T","O"," "," "," "," "," ","T","H","E"," "," "," ","W","I","N","D","O","W","S"," "," "," ","E","X","P","l","O","R","E","R"};

	setbkcolor(LIGHTBLUE);

	cleardevice();
	shed_box(2,2,635,475,2,10,1,10);
	setbkcolor(0);
	shed_box(80,30,560,60,0,0,1,10);
	setcolor(2);
	outtextxy(130,43, "MAWLANA BHASHANI SCIENCE & TECHNOLOGY UNIVERSITY");

	for(n=0;n<7;++n)
	{
	  for(i=0;i<200;++i)
	  {
		setcolor(i);
		outtextxy(450-i+x,100,ch[n]);
		delay(1);
		setcolor(0);
		outtextxy(450-i+x,100,ch[n]);
	  }
	setcolor(14);
	outtextxy(450-i+x,100,ch[n]);
	x=x+20;
	}

	d=0;
	for(n=8;n<9;++n)
	{
	  for(i=0;i<250;++i)
	  {
		setcolor(i);
		outtextxy(570-i,150,ch[n]);
		delay(1);
		setcolor(0);
		outtextxy(570-i,150,ch[n]);
	  }
	setcolor(14);
	outtextxy(570-i,150,ch[n]);
	d=d+20;
	}

	for(n=7;n<8;++n)
	{
	  for(i=0;i<250;++i)
	  {
		setcolor(i);
		outtextxy(55+i,150,ch[n]);
		delay(1);
		setcolor(0);
		outtextxy(55+i,150,ch[n]);
	  }
	setcolor(14);
	outtextxy(55+i,150,ch[n]);
	d=d+20;
	}

	d=0;
	for(n=9;n<=37;++n)
	{
	  for(i=80;i<150;++i)
	  {
		setcolor(i);
		outtextxy(280-i+d,200,ch[n]);
		delay(1);
		setcolor(0);
		outtextxy(280-i+d,200,ch[n]);
	  }
	setcolor(14);
	outtextxy(280-i+d,200,ch[n]);
	d=d+10;
	}

	shed_box(260,270,400,300,0,0,1,10);
	setcolor(2);
	outtextxy(287,283,"SUBMITED BY");
	shed_box(200,320,455,395,0,0,1,10);
	setcolor(2);
	outtextxy(256,335,"Rasel Ahammed");
	outtextxy(252,345,"Roll NO.: CE-11020");
	outtextxy(240,355,"2nd Year 1st Semester");
	outtextxy(215,365,"Software Development Project");
	outtextxy(246,375,"Course Code: CSE-2112");

	setcolor(2);
        //delay(10000);
        while(!kbhit())
        {
          setcolor(2);
          outtextxy(226,430,"Press any key to continue.....");
          delay(500);
          setcolor(0);
          outtextxy(226,430,"Press any key to continue.....");
          delay(500);
	}
        getch();
       //background_design();

}

void main()
{
	int driver=DETECT,mode;
	int x,y,value1,value2,value3,hold=0;
	char *p;

	initgraph(&driver,&mode,"c:\\tc\\bgi");
	permission();
	MouseOn();

	while(1)
	{
		if(LeftButtonPressed())
		{
			GetPosition(&x,&y);
			if(x>=370&&y>=260&&x<=420&&y<=275)
			{
				MouseOff();
				welcome();
				MouseOn();
				goto first;
			}

			if(x>=425&&y>=260&&x<=475&&y<=275)
			exit(1);
		}
	}

	first:

	MouseOff();
	BrowserFrame();
	MouseReset();
	Drive();
	MouseOn();

	Header();
	while(1)
	{
		HighlightedDriveColor();
		if(LeftButtonPressed())
		{
			GetPosition(&x,&y);

			if(x>=617&&x<=637&&y>=1&&y<=13)
			exit(1);

			if(x>=6&&y>=16&&x<=256&&y<=30)
			PopUpMenu(x,y);

			else
			{
				MouseOff();
				SubBrowserFrame();
				MouseOn();
			}

			if(x>=147&&y>=87&&x<=638&&y<=478)
			EnteringDrive(x,y);

			if(enter==1)
			{
				enter=0;
				page++;
				goto second;
			}

			else
			goto first;
		}
	}

	second:

	Header();
	while(1)
	{
		MouseOn();
		if(LeftButtonPressed())
		{
			GetPosition(&x,&y);

			if(x>=617&&x<=637&&y>=1&&y<=13)
			exit(1);

			if(x>=619&&y>=454&&x<=639&&y<=475)
			{
				hold=1;
				ScrollDown();
			}

			if(x>=619&&y>=89&&x<=639&&y<=110)
			{
				hold=1;
				ScrollUp();
			}
			//else
			//{
				if(x>=50&&y>=45&&x<=120&&y<=80)
				{
					scroll=0;
					Back();
					hold=1;
				}
				if(BackValue==1)
				{
					BackValue=0;
					goto first;
				}
			//}

			if(x>=6&&y>=16&&x<=256&&y<=30)
			{
				hold=1;
				PopUpMenu(x,y);
			}

			if(hold==0)
			{
				MouseOff();
				SubBrowserFrame();
				settextstyle(2,0,5);
				setcolor(4);
				outtextxy(405,62,DriveSpecifier[FolderNo]);
				MouseOn();
			}

			for(int i=1,pos=0;i<=fol;i++,pos+=15)
			{
				if(x>=160&&y>=110+pos&&x<=190&&y<=125+pos-2)
				{
					value1=((y+scroll*15)-110)/15;

					strcat(DriveSpecifier[FolderNo],FolderSpecifier[value1]);
					strcat(creFol[FolderNo],FolderSpecifier[value1]);
					MouseOff();
					BrowserFrame();
					settextstyle(2,0,5);
					setcolor(4);
					outtextxy(405,62,DriveSpecifier[FolderNo]);
					strcat(DriveSpecifier[FolderNo],"\\");
					strcat(creFol[FolderNo],"/");

					/*if(strstr(FolderSpecifier[value1],".txt"))
					{
						system(creFol[FolderNo]);
					}*/

					Header();
					FileAndFolder(DriveSpecifier);
					MouseReset();
					MouseOn();
					page++;
					break;
				}
			}
		}
	}
}

void ScrollDown()
{
	int i,k=110,FolNo;

	if(fol-scroll>=25)
	{
		scroll++;

		BFrame();
		setcolor(4);
		settextstyle(2,0,5);
		for(i=scroll;i<=fol;i++,k+=15)
		outtextxy(160,k,FolderSpecifier[i]);
	}
}

void ScrollUp()
{
	int i,k=110;

	if(scroll>0)
	{
		scroll--;
		BFrame();
		setcolor(4);
		settextstyle(2,0,5);
		for(i=scroll;i<=fol;i++,k+=15)
		outtextxy(160,k,FolderSpecifier[i]);
	}
}

void BFrame()
{
	setfillstyle(1,7);
	bar(147,87,638,478);

	setcolor(3);
	rectangle(619,89,639,110);       //ScrollUpBox
	setfillstyle(1,8);
	bar(620,90,638,109);
	line(622,102,630,92);
	line(623,102,631,92);
	line(630,92,638,102);
	line(629,93,637,101);

	rectangle(619,454,639,475);     //ScrollDownBox
	bar(620,455,638,474);
	line(620,460,630,470);
	line(621,459,631,469);
	line(630,470,638,460);
	line(629,469,638,459);

}

void BrowserFrame()
{
	setcolor(7);
	rectangle(0,0,getmaxx(),getmaxy());

	setfillstyle(1,9);
	bar(1,1,638,13);
	line(1,14,638,14);

	setfillstyle(1,4);
	bar(618,2,636,12);
	line(621,5,633,10);
	line(633,5,621,10);

	setfillstyle(11,1);
	bar(1,15,638,30);
	bar(1,31,638,85);
	setcolor(7);
	line(0,32,638,32);

	setfillstyle(11,1);
	bar(1,86,145,478);
	line(146,86,146,638);
	line(1,86,638,86);
	setfillstyle(1,7);
	bar(147,87,638,478);

	rectangle(50,45,120,80);	  //BACK BUTTON
	settextstyle(1,0,3);
	outtextxy(57,47,"BACK");

	bar(400,60,630,80);	   	//ADDRESS BUTTON

	setcolor(3);
	rectangle(619,89,639,110);       //ScrollUpBox
	setfillstyle(1,8);
	bar(620,90,638,109);
	line(622,102,630,92);
	line(623,102,631,92);
	line(630,92,638,102);
	line(629,93,637,101);

	rectangle(619,454,639,475);     //ScrollDownBox
	bar(620,455,638,474);
	line(620,460,630,470);
	line(621,459,631,469);
	line(630,470,638,460);
	line(629,469,638,459);
}

void SubBrowserFrame()
{
	setcolor(7);
	rectangle(0,0,getmaxx(),getmaxy());

	setfillstyle(11,1);
	bar(1,33,380,85);
	setcolor(7);
	line(0,32,638,32);

	rectangle(50,45,120,80);	  //BACK BUTTON
	settextstyle(1,0,3);
	outtextxy(57,47,"BACK");

	setfillstyle(1,7);
	bar(400,60,630,80);               //ADDRESS BAR

}

void Header()
{
	settextstyle(SMALL_FONT,HORIZ_DIR,4);
	DriveBox(6,16,34,30,8,1,4,1);
	outtextxy(10,17,"File");
	DriveBox(41,16,68,30,8,1,4,1);
	outtextxy(45,17,"Edit");
	DriveBox(75,16,105,30,8,1,4,1);
	outtextxy(80,17,"View");
	DriveBox(112,16,176,30,8,1,4,1);
	outtextxy(117,17,"Favorites");
	DriveBox(183,16,220,30,8,1,4,1);
	outtextxy(188,17,"Tools");
	DriveBox(228,16,256,30,8,1,4,1);
	outtextxy(232,17,"Help");
}

void PopUpMenu(int x,int y)
{
	if(x>=6&&y>=16&&x<=34&&y<=30)
	{
		click1++;
		MouseOff();

		if(click1%2==1)
		FilePopupMenu();
		settextstyle(2,0,5);
		setcolor(4);
		outtextxy(405,62,DriveSpecifier[FolderNo]);
		Header();
		MouseReset();
		MouseOn();
	}

	if(x>=228&&y>=16&&x<=256&&y<=30)
	{
		click2++;
		MouseOff();

		if(click2%2==1)
		HelpPopupMenu();
		MouseReset();
		MouseOn();
	}

	if(x>=41&&y>=16&&x<=68&&y<=30)
	{
		click3++;
		MouseOff();

		if(click3%2==1)
		EditPopupMenu();

		MouseReset();
		MouseOn();
	}

	while(1)
	{
		if(LeftButtonPressed())
		{
			GetPosition(&x,&y);

			if(x>=617&&x<=637&&y>=1&&y<=13)
			exit(1);

			if(x>=20&&y>=55&&x<=50&&y<=70&&click1!=0)
			exit(1);

			if(x>=20&&y>=35&&x<=50&&y<=70&&click1!=0)
			createFolderBox();

			if(x>=238&&y>=35&&x<=300&&y<=87&&click2!=0)
			createHelpBox();

			if(x>=55&&y>=35&&x<=90&&y<=50&&click3!=0)
			createDeleteBox();

			else
			{
				click1=0; click2=0;
				MouseOff();
				SubBrowserFrame();
				Header();
				MouseOn();
				break;
			}
		}
	}
}

void createHelpBox()
{
	int x,y;

	MouseOff();
	setfillstyle(1,8);
	bar(200,200,500,300);
	settextstyle(SMALL_FONT,HORIZ_DIR,5);
	outtextxy(240,220,"Contact with RASEL AHAMMED.");
	DriveBox(320,260,370,290,7,1,1,5);
	outtextxy(335,265,"OK");
	MouseOn();

	while(1)
	{
		if(LeftButtonPressed())
		{
			GetPosition(&x,&y);

			if(x>=320&&y>=260&&x<=370&&y<=290)
			{
				MouseOff();
				BrowserFrame();
				Header();

				if(page==0)
				Drive();

				else
				FileAndFolder(DriveSpecifier);

				MouseOn();
				break;
			}
		}
	}
}

void createDeleteBox()
{
	char ch[20];
	int x,y;

	MouseOff();
	setfillstyle(1,8);
	bar(200,200,500,300);
	settextstyle(SMALL_FONT,HORIZ_DIR,5);
	outtextxy(220,224,"Folder name : ");
	DriveBox(320,260,370,290,7,1,1,5);
	outtextxy(335,265,"OK");

	DriveBox(400,260,460,290,7,1,1,5);
	outtextxy(410,265,"CANCEL");

	MouseReset();
	MouseOn();
	gotoxy(42,15);
	gets(ch);

	while(1)
	{
		if(LeftButtonPressed())
		{
			GetPosition(&x,&y);

			if(x>=320&&y>=260&&x<=370&&y<=290)
			{
				strcat(creFol[FolderNo],ch);
				rmdir(creFol[FolderNo]);
				system("dir/p");
				MouseOff();
				BrowserFrame();
				Header();

				if(page==0)
				Drive();

				else
				FileAndFolder(DriveSpecifier);

				MouseOn();
				break;
			}

			if(x>=400&&y>=260&&x<=460&&y<=290)
			{
				MouseOff();
				BrowserFrame();
				Header();

				if(page==0)
				Drive();

				else
				FileAndFolder(DriveSpecifier);

				MouseOn();
				break;
			}
		}
	}
}

void createFolderBox()
{
	char ch[20];
	int x,y;

	MouseOff();
	setfillstyle(1,8);
	bar(200,200,500,300);
	settextstyle(SMALL_FONT,HORIZ_DIR,5);
	outtextxy(220,224,"Folder name : ");
	DriveBox(320,260,370,290,7,1,1,5);
	outtextxy(330,265,"SAVE");

	DriveBox(400,260,460,290,7,1,1,5);
	outtextxy(410,265,"CANCEL");

	MouseReset();
	MouseOn();
	gotoxy(42,15);
	gets(ch);

	while(1)
	{
		if(LeftButtonPressed())
		{
			GetPosition(&x,&y);

			if(x>=320&&y>=260&&x<=370&&y<=290)
			{
				strcat(creFol[FolderNo],ch);
				mkdir(creFol[FolderNo]);
				system("dir/p");
				MouseOff();
				BrowserFrame();
				Header();

				if(page==0)
				Drive();

				else
				FileAndFolder(DriveSpecifier);

				MouseOn();
				break;
			}

			if(x>=400&&y>=260&&x<=460&&y<=290)
			{
				MouseOff();
				BrowserFrame();
				Header();

				if(page==0)
				Drive();

				else
				FileAndFolder(DriveSpecifier);

				MouseOn();
				break;
			}
		}
	}
}

void FilePopupMenu()
{
	setcolor(7);
	rectangle(7,32,115,81);
	setfillstyle(1,8);
	bar(8,33,114,80);
	setcolor(10);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
	outtextxy(20,35,"New...");
	outtextxy(20,55,"Quit");
	MouseOff();
	MouseOn();
}

void EditPopupMenu()
{
	setcolor(7);
	rectangle(40,32,140,71);
	setfillstyle(1,8);
	bar(41,33,139,70);
	setcolor(10);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
	outtextxy(55,35,"Delete");
	MouseOff();
	MouseOn();
}

void HelpPopupMenu()
{
	setcolor(7);
	rectangle(228,32,351,71);
	setfillstyle(1,8);
	bar(229,33,350,70);
	setcolor(10);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
	outtextxy(238,35,"Contact");
	MouseOff();
	MouseOn();
}

void Drive()
{
	int save, disk, disks;

	/* save original drive */
	save = getdisk();

	/* print the drive letters available */

	setcolor(14);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
	outtextxy(170,110,"DRIVES.................");
	line(170,135,400,135);

	for (disk = 0,D = 0;disk < 26;++disk)
	{
		setdisk(disk);
		if (disk == getdisk())
		D++;

		settextstyle(SMALL_FONT,HORIZ_DIR,5);
		if(D==1)
		{
			DriveBox(190,160,280,195,7,1,1,5);
			setcolor(15);
			outtextxy(200,170,"DRIVE (C:)");
		}
		if(D==2)
		{
			DriveBox(340,160,430,195,7,1,1,5);
			setcolor(15);
			outtextxy(350,170,"DRIVE (D:)");
		}
		if(D==3)
		{
			DriveBox(490,160,580,195,7,1,1,5);
			setcolor(15);
			outtextxy(500,170,"DRIVE (E:)");
		}
		if(D==4)
		{
			DriveBox(190,260,280,295,7,1,1,5);
			setcolor(15);
			outtextxy(200,270,"DRIVE (F:)");
		}
		if(D==5)
		{
			DriveBox(340,260,430,295,7,1,1,5);
			setcolor(15);
			outtextxy(350,270,"DRIVE (G:)");
		}
		if(D==6)
		{
			DriveBox(490,260,580,295,7,1,1,5);
			setcolor(15);
			outtextxy(500,270,"DRIVE (H:)");
		}
		if(D==7)
		{
			DriveBox(190,360,280,395,7,1,1,5);
			setcolor(15);
			outtextxy(200,370,"DRIVE (I:)");
		}
		if(D==8)
		{
			DriveBox(340,360,430,395,7,1,1,5);
			setcolor(15);
			outtextxy(350,370,"DRIVE (J:)");
		}
		if(D==9)
		{
			DriveBox(490,360,580,395,7,1,1,5);
			setcolor(15);
			outtextxy(500,370,"DRIVE (K:)");
		}
		if(D==10)
		{
			DriveBox(190,460,280,495,7,1,1,5);
			setcolor(15);
			outtextxy(200,480,"DRIVE (L:)");
		}
	}
	setdisk(save);
}

void DriveBox(int x1, int y1, int x2, int y2, int color, int pattern,int condition, int thick)
{
	int i,left,right,top,bottom;

	setfillstyle(1,0);	// Outside color
	bar(x1-1,y1-1,x2+1,y2+1);

	if(condition == 0)
	{
		left = top =  DARKGRAY;
		right =bottom= WHITE;
	}

	if(condition == 1)
	{
		left = top = WHITE;
		right =bottom = DARKGRAY;
	}

	if(condition == 2)
	{
		left = top = DARKGRAY; // WHITE
		right =bottom =LIGHTBLUE;
	}

	if(condition == 3)
	{
		left = top =   LIGHTBLUE;
		right =bottom = DARKGRAY; //WHITE
	}

	if(condition == 4)
	{
		left = top =  LIGHTBLUE;
		right =bottom = WHITE;
	}

	setfillstyle(pattern,color); 		// Inside bar
	bar(x1,y1,x2,y2);

	setcolor(top);
	for(i=0;i<=thick;i++)
	line(x1+i-1,y1+i-1,x2-i-1,y1+i-1);	// TOP

	setcolor(left);
	for(i=0;i<=thick;i++)
	line(x1+i-1,y1+i-1,x1+i-1,y2-i-1);	//LEFT

	setcolor(right);
	for(i=0;i<=thick;i++)
	line(x2-i+1,y1+i-2,x2-i+1,y2-i+1);	// RIGHT

	setcolor(bottom);
	for(i=0;i<=thick;i++)
	line(x1+i-2,y2-i+1,x2-i+1,y2-i+1);	// BOTTOM
}

void EnteringDrive(int x,int y)
{
	if(x>=190&&y>=160&&x<=280&&y<=195)
	{
		EnterValue=0;
		FolderNo=0;
	}
	if(x>=340&&y>=160&&x<=430&&y<=195)
	{
		EnterValue=1;
		FolderNo=1;
	}
	if(x>=490&&y>=160&&x<=580&&y<=195)
	{
		EnterValue=2;
		FolderNo=2;
	}
	if(x>=190&&y>=260&&x<=280&&y<=295)
	{
		EnterValue=3;
		FolderNo=3;
	}
	if(x>=340&&y>=260&&x<=430&&y<=295)
	{
		EnterValue=4;
		FolderNo=4;
	}
	if(x>=490&&y>=260&&x<=580&&y<=295)
	{
		EnterValue=5;
		FolderNo=5;
	}
	if(x>=190&&y>=360&&x<=280&&y<=395)
	{
		EnterValue=6;
		FolderNo=6;
	}
	if(x>=340&&y>=360&&x<=430&&y<=395)
	{
		EnterValue=7;
		FolderNo=7;
	}

	if(EnterValue+1<=D)
	{
		MouseOff();
		BrowserFrame();
		settextstyle(2,0,5);
		setcolor(4);
		outtextxy(405,62,DriveSpecifier[FolderNo]);
		strcat(DriveSpecifier[FolderNo],"\\");
		strcat(creFol[FolderNo],"/");
		FileAndFolder(DriveSpecifier);
		MouseOn();
		EnterValue=100;
		enter=1;
	}
}

void Back()
{
	int i,l,len;
	len=strlen(DriveSpecifier[FolderNo]);

	if(len==3)
	{
		page=0;
		MouseOff();
		BFrame();
		Drive();
		BackValue=1;
		DriveSpecifier[FolderNo][len-1]='\0';
		creFol[FolderNo][len-1]='\0';
		goto last;
	}

	else
	{
		page--;
		DriveSpecifier[FolderNo][len-1]='\0';
		creFol[FolderNo][len-1]='\0';
		for(i=len-2;DriveSpecifier[FolderNo][i]!=92;i--);
		DriveSpecifier[FolderNo][i]='\0';

		for(i=len-2;creFol[FolderNo][i]!=47;i--);
		creFol[FolderNo][i]='\0';

		MouseOff();
		BrowserFrame();
		settextstyle(2,0,5);
		setcolor(4);
		outtextxy(405,62,DriveSpecifier[FolderNo]);

		strcat(DriveSpecifier[FolderNo],"\\");
		strcat(creFol[FolderNo],"/");

		FileAndFolder(DriveSpecifier);
	}       Header();
		MouseOn();
	last:
	MouseOn();
}

void HighlightedDriveColor()
{
	int x,y,d=1;
	GetPosition(&x,&y);

	if(x>=190&&y>=160&&x<=280&&y<=195&&d<=D)
	{
		setcolor(14);
		rectangle(189,159,281,196);
		rectangle(195,165,275,190);
	}

	else
	{
		setcolor(7);
		rectangle(189,159,281,196);
		rectangle(195,165,275,190);
	}

	d=2;
	if(x>=340&&y>=160&&x<=430&&y<=195&&d<=D)
	{
		setcolor(14);
		rectangle(339,159,431,196);
		rectangle(345,165,425,190);
	}

	else
	{
		setcolor(7);
		rectangle(339,159,431,196);
		rectangle(345,165,425,190);
	}

	d=3;
	if(x>=490&&y>=160&&x<=580&&y<=195&&d<=D)
	{
		setcolor(14);
		rectangle(489,159,581,196);
		rectangle(495,165,575,190);
	}

	else
	{
		setcolor(7);
		rectangle(489,159,581,196);
		rectangle(495,165,575,190);
	}

	d=4;
	if(x>=190&&y>=260&&x<=280&&y<=295&&d<=D)
	{
		setcolor(14);
		rectangle(189,259,281,296);
		rectangle(195,265,275,290);
	}

	else
	{
		setcolor(7);
		rectangle(189,259,281,296);
		rectangle(195,265,275,290);
	}

	d=5;
	if(x>=340&&y>=260&&x<=430&&y<=295&&d<=D)
	{
		setcolor(14);
		rectangle(339,259,431,296);
		rectangle(345,265,425,290);
	}

	else
	{
		setcolor(7);
		rectangle(339,259,431,296);
		rectangle(345,265,425,290);
	}

	d=6;
	if(x>=490&&y>=260&&x<=580&&y<=295&&d<=D)
	{
		setcolor(14);
		rectangle(489,259,581,296);
		rectangle(495,265,575,290);
	}

	else
	{
		setcolor(7);
		rectangle(489,259,581,296);
		rectangle(495,265,575,290);
	}

	d=7;
	if(x>=190&&y>=360&&x<=280&&y<=395&&d<=D)
	{
		setcolor(14);
		rectangle(189,359,281,396);
		rectangle(195,365,275,390);
	}

	else
	{
		setcolor(7);
		rectangle(189,359,281,396);
		rectangle(195,365,275,390);
	}

	d=8;
	if(x>=340&&y>=360&&x<=430&&y<=395&&d<=D)
	{
		setcolor(14);
		rectangle(339,359,431,396);
		rectangle(345,365,425,390);
	}

	else
	{
		setcolor(7);
		rectangle(339,359,431,396);
		rectangle(345,365,425,390);
	}

	d=9;
	if(x>=490&&y>=360&&x<=580&&y<=395&&d<=D)
	{
		setcolor(14);
		rectangle(489,359,581,396);
		rectangle(495,365,575,390);
	}

	else
	{
		setcolor(7);
		rectangle(489,359,581,396);
		rectangle(495,365,575,390);
	}
}
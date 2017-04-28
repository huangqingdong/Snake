#define N 200
#include <process.h>
#include <dos.h>
#include <conio.h>
#include<graphics.h>
#include<malloc.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define Key_DOWN 0x5000
#define Key_UP 0x4800
#define Key_ESC 0x011b
#define Key_ALT_F 0x2100
#define Key_ALT_X 0x2d00
#define Key_ENTER 0x1c0d
#define IMAGE_SIZE 10
/*游戏*/
#define LEFT 0x4b00
#define RIGHT 0x4d00
#define DOWN 0x5000
#define UP 0x4800
#define ESC 0x011b
#define filename "c:\\tc\\save.txt"
int i,key;
int score=0;/*得分*/
int gamespeed=50;/*游戏速度自己调整*/
int start=1;
int Level=1;
char y;

struct Food
{
   int x;/*食物的横坐标*/
   int y;/*食物的纵坐标*/
   int x1;
   int y1;

   int yes;/*yes=1:需要显示食物，yes=0:屏幕已经有食物存在。yes判断是否要出现食物的变量*/
}food;/*食物的结构体*/

struct Snake
{
   int x[N];/*X坐标*/
   int y[N];/*y坐标*/
   int node;/*蛇的节数*/
   int direction;/*蛇移动方向*/
   int life;/* 蛇的生命,0活着,1死亡*/
}snake;
/*结束游戏*/
struct person
{
	int score;
	char name[20];

}per[5];

void box(int startx,int starty,int high,int width);
int menuslist();
void putstar(void);
void win1();
void startpage();

void autoPlay();
void autoPlayGame();
void voice();

/*游戏函数*/

void Init(void);/*图形驱动*/
void Close(void);/*图形结束*/
void DrawK(void);/*开始画面*/
void GameOver(void);/*结束游戏*/
void GamePlay(void);/*玩游戏具体过程*/
void PrScore(void);/*输出成绩*/
void save(void);/*保存游戏记录*/
void readfile(void);/*读取游戏记录*/
void startplay(void);/*开始*/
void newstart(void);/*开始新游戏*/
void paihb();/*排行榜*/
void comparescore(struct person des);/*比较排行榜分数*/
void initscorefiles();/*初始化分数*/
void writefiles(struct person *tmp);/*将分数写入文件中*/
void readfiles();/*从文件中读取分数*/

main()
{
startpage();
menuslist();/*主菜单*/
getch();
}

int menuslist()
{
int i,key,x,y,l;


char *menu[] = {"Play","Level","Rank","Continu","Auto"};
/* 主菜单各项 */
char *menu1[] = {"Play","","Level","","Rank","","Continue","","Auto"};
char *red[] = { "P","L","R","C","A"}; /* 加上红色热键 */
/*char *f[] = {"Load file", "Save file", "Print", "Modify ", "Quit"};*/
/* File 项的子菜单 */
char *level[]={"Low","Midum","High"};

char buf[16*10*2],buf1[16*10*2]; /* 定义保存文本的缓冲区 */
l=0;

while(1)
			{
			textbackground(BLUE);
			clrscr();
			textmode(C80);
			window(25,5,35,20);/* 定义显示主菜单的窗口 */
			textbackground(LIGHTGRAY);
			textcolor(BLACK);
			clrscr();

			gotoxy(5,5);
					for(i=0,l=0;i<5;i++)
					{
					x=wherex(); /* 得到当前光标的坐标 */
					y=wherey();
					cprintf("%s",menu[i]); /* 显示各菜单项 */
					 /*l=strlen(menu[i]); 得到菜单项的长度 */
					gotoxy(x,y);
					textcolor(RED);
					cprintf("%s",red[i]); /* 在主菜单项各头字符写上红字符 */
					y=y+2;
					gotoxy(x,y);
					textcolor(BLACK); /* 为显示下一个菜单项移动光标 */
					}
					gettext(29,9,45,11,buf);
			gotoxy(5,5);
			key=bioskey(0);
y=5;

					while ((key=bioskey(0))!=Key_ALT_X) /* 等待选择下拉菜单项*/
								{

								if ((key==Key_UP)||(key==Key_DOWN))
											{
												puttext(29,y+4,45,y+6,buf); /* 恢复原先的项 */
												if (key==Key_UP)
												y=y==5?13:y-2;
												else
												y=y==13?5:y+2;
												gettext(29,y+4,45,y+6,buf);/*保存要压上光条的子菜单项*/
												textbackground(BLACK);
												textcolor(WHITE);
												gotoxy(5,y);
												cprintf("%s",menu1[y-5]); /* 产生黑条压在所选项上 */


												gotoxy(5,y);

											}
								else

								if (key==Key_ENTER)/* 若是回车键,判断是哪一子菜单按的回
								车，在此没有相应的特殊处理*/
										{
													switch ( y )
															{
														case 5: /* 是子菜单项第一项:Play */
														
													i=1;
													startplay();
													
														break;

														case 7: /* Level */
														textbackground(BLACK);
														textcolor(WHITE);
														gotoxy(29,45);
														cprintf("%s",menu[1]);
														window(36,9,43,14);
														textbackground(LIGHTGRAY);
														textcolor(BLACK);
														clrscr();
														for(i=0;i<3;i++)
															{
															l=l+2;
															gotoxy(2,l);
															cprintf("%s",level[i]);
															}
														gettext(36,10,43,11,buf1);
														gotoxy(2,2);


															y=2;
															while ((key=bioskey(0))!=Key_ALT_X) /* 等待选择下拉菜单项*/
																	{
																	if ((key==Key_UP)||(key==Key_DOWN))
																			{
																			puttext(36,y+8,43,y+9,buf1); /* 恢复原先的项 */
																			if (key==Key_UP)
																			y=y==2?6:y-2;
																			else
																			y=y==6?2:y+2;
																			gettext(36,y+8,43,y+9,buf1);/*保存要压上光条的子菜单项*/
																			textbackground(BLACK);
																			textcolor(WHITE);
																			gotoxy(2,y);
																			cprintf("%s",level[y/2-1]); /* 产生黑条压在所选项上 */
																			gotoxy(2,y);
																			}									
																	else
																	if (key==Key_ENTER)
																			{
																					switch(y)
																					{
																							case 2:
																								Level=1;
																						
																								break;
																							case 4:
																								Level=2;
																								break;
																							case 6:
																								Level=3;
																								break;
																							default:
																								break;
																					}
																			}
																
																else
																if (key==Key_ESC)
																break; /* 是Esc 键,返回主菜单 */
																}
														case 9: /*Rank*/
														paihb();
														break;
														case 11: /* Continue游戏记录 */
														start=0;
														startplay();
														getch();
														break;
														case 13:/*自动游戏*/
														autoPlayGame();
												default:
													break;
															}


									    }
								else
								if (key==Key_ESC)
								break; /* 是Esc 键,返回主菜单   */
								}
							/*if (key==Key_ALT_X) exit(0);
							break;*/
							}
							return;

}
/*开始页面*/
void startpage()
{int driver=DETECT;
int mode,color;
void *pt_addr;
int x,y,maxy,maxx,midy,midx,i;
unsigned size;
initgraph(&driver,&mode,"c:\\tc\\bgi");
maxx=getmaxx();
maxy=getmaxy();
midx=maxx/2;
x=0;
midy=y=maxy/2;
win1();
settextstyle(TRIPLEX_FONT,HORIZ_DIR,4);
settextjustify(CENTER_TEXT,CENTER_TEXT);
outtextxy(midx,400,"WELCONME TO SNAKE WORLD");
setbkcolor(BLACK);
setcolor(RED);
setlinestyle(SOLID_LINE,0,THICK_WIDTH);
ellipse(midx,midy,130,50,160,30);
setlinestyle(SOLID_LINE,0,NORM_WIDTH);
size=imagesize(x,y-IMAGE_SIZE,x+(4*IMAGE_SIZE),y+IMAGE_SIZE);
pt_addr=malloc(size);
getimage(x,y-IMAGE_SIZE,x+(4*IMAGE_SIZE),y+IMAGE_SIZE,pt_addr);
putstar();
setcolor(BLUE);
setlinestyle(SOLID_LINE,0,NORM_WIDTH);
rectangle(0,0,maxx,maxy);
while(!kbhit())
{
putstar();
setcolor(RED);
setlinestyle(SOLID_LINE,0,THICK_WIDTH);
ellipse(midx,midy,130,50,160,30);
setcolor(BLACK);
ellipse(midx,midy,130,50,160,30);
for(i=0;i<=13;i++)
{
setcolor(i%2==0?LIGHTBLUE:BLACK);
ellipse(midx,midy,0,360,100-8*i,100);
setcolor(LIGHTBLUE);
ellipse(midx,midy,0,360,100,100-8*i);
}
}



free(pt_addr);
closegraph();
return;
}
void win1()
{
	setcolor(8);
	setfillstyle(SOLID_FILL,8);
	bar3d(0,0,639,479,0,0);
	setcolor(0);
	setfillstyle(SOLID_FILL,0);
	bar3d(189,44,494,214,0,0);
	setcolor(1);
	setfillstyle(SOLID_FILL,1);
	bar3d(159,59,479,239,0,0);
	setcolor(14);
   settextjustify(LEFT_TEXT,TOP_TEXT);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
	settextjustify(LEFT_TEXT,TOP_TEXT);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,8);
	outtextxy(216,64,"SNAKE");
}
void putstar(void)/*画星星*/
{
int seed=1858;
int i,dotx,doty,h,w,color,maxcolor;
maxcolor=getmaxcolor();/*得到当前模式和最多颜色数*/
w=getmaxx();
h=getmaxy();
srand(seed);
for(i=0;i<250;++i)
{
dotx=i+random(w-1);
doty=i+random(h-1);
color=random(maxcolor);
setcolor(color);
putpixel(dotx,doty,color);/*用点表示小星*/
circle(dotx+1,doty+1,1);/*用圆表示大星*/
}
srand(seed);
}
/*开始页面结束*/


/*图形驱动*/
void Init(void)
{
   int gd=DETECT,gm;
   initgraph(&gd,&gm,"c:\\tc\\bgi");
   cleardevice();/*清除图形屏幕*/
}
/*开始画面，左上角坐标为（50，40），右下角坐标为（610，460）的围墙*/
void DrawK(void)
{
   setbkcolor(LIGHTBLUE);/*设置背景色蓝色*/
   setcolor(11);/*设置前景颜色*/
   setlinestyle(SOLID_LINE,0,THICK_WIDTH);/*设置线型：设置当前画线宽度和类型*/
   for(i=0;i<=640;i+=10)/*画围墙*/
   {
      rectangle(i,40,i+10,49); /*上边：rectangle画一个矩形*/
   }

}

/*玩游戏具体过程*/
void GamePlay(void)
{
	if(start==1)
   newstart();
else
	{
   readfile();
   score=(snake.node-2)*10;
   PrScore();
	}
   randomize();/*随机数发生器*/
   PrScore();

   while(1)/*可以重复玩游戏,压ESC键结束*/
   {
			  while(!kbhit())/*kbhit是一个函数，可以用来检查当前是否有键盘输入,在没有按键的情况下,蛇自己移动身体*/
			  {
						  if(food.yes==1)/*需要出现新食物*/
						  {
							  food.x=rand()%400+60;
							  food.y=rand()%350+60;
							  /* food.x1=rand()%400+60;
							  food.y1=rand()%350+60;*/
							  while(food.x%10!=0)/*食物随机出现后必须让食物能够在整格内,这样才可以让蛇吃到*/
						  food.x++;
							  while(food.y%10!=0)
						  food.y++;
						  food.yes=0;/*画面上有食物了,就要将yes置0*/
						  }
							  if(food.yes==0)/*画面上有食物了就要显示*/
							  {
								           voice();
										  setcolor(GREEN);/*设置食物前景色。*/
										  rectangle(food.x,food.y,food.x+10,food.y-10);/*设置食物颜色*/
										 /* rectangle(food.x1,food.y1,food.x1+10,food.y1-10);设置食物颜色*/
							  }
						 for(i=snake.node-1;i>0;i--)/*蛇的每个环节往前移动,也就是贪吃蛇的关键算法*/
						 {
							snake.x[i]=snake.x[i-1];
							snake.y[i]=snake.y[i-1];
						 }
			   /*1,2,3,4表示右,左,上,下四个方向,通过这个判断来移动蛇头*/
					  switch(snake.direction)
					  {
						 case 1:
							 if(snake.x[0]==630)
							  snake.x[0]=0;
						     else
							 snake.x[0]+=10;
						 break;/*右*/
						 case 2:
							  if(snake.x[0]==0)
							  snake.x[0]=630;
						     else
							 snake.x[0]-=10;
							 break;/*左*/
						 case 3:
							  if(snake.y[0]==60)
							 snake.y[0]=480;/*上*/
                          else
							   snake.y[0]-=10;
						 break;
						 case 4:
							 if(snake.y[0]==470)
							 snake.y[0]=60;
						 else
						 snake.y[0]+=10;break;/*下*/
					  }


				  for(i=3;i<snake.node;i++)/*从蛇的第四节开始判断是否撞到自己了，因为蛇头为两节，第三节不可能拐过来*/
				  {
					 if(snake.x[i]==snake.x[0]&&snake.y[i]==snake.y[0])
					 {
							   GameOver();/*显示失败*/
							   snake.life=1;/*0为活着，1为挂掉*/
							   break;
					 }
				   }
				 if(snake.x[0]==food.x&&snake.y[0]==food.y)/*吃到食物以后*/
					 {
							   setcolor(0);/*把画面上的食物东西去掉*/
							   rectangle(food.x,food.y,food.x+10,food.y-10);
						snake.x[snake.node]=-20;snake.y[snake.node]=-20;
							  /*新的一节先放在看不见的位置,下次循环就取前一节的位置*/
						snake.node++;/*蛇的身体长一节*/
						food.yes=1;/*画面上需要出现新的食物*/
						score+=10;
						PrScore();/*输出新得分*/
					 }
				 setcolor(4);/*画出蛇*/
				 for(i=0;i<snake.node;i++)
					rectangle(snake.x[i],snake.y[i],snake.x[i]+10,
							   snake.y[i]-10);
				 delay(gamespeed);
				 setcolor(0);/*用黑色去除蛇的的最后一节*/
				 rectangle(snake.x[snake.node-1],snake.y[snake.node-1],
				 snake.x[snake.node-1]+10,snake.y[snake.node-1]-10);
		      }  /*endwhile（！kbhit）*/




		if(snake.life==1)/*如果蛇死就跳出循环*/
			break;
		key=bioskey(0);/*接收按键：bioskey直接使用BIOS服务的键盘接口。*/
		if(key==ESC)/*按ESC键返回主菜单*/
	   {
		   window(36,5,60,20);
		   gotoxy(0,10);
		   printf("Save Game?(Y/N)");
		   scanf("%s",&y);
		   clrscr();
			   if(y=='Y'||y=='y')
				   save();
			   else
				   exit(0);
	   }
		else
		   if(key==UP&&snake.direction!=4)
	/*判断是否往相反的方向移动*/
			snake.direction=3;
		   else
	   if(key==RIGHT&&snake.direction!=2)
		  snake.direction=1;
	   else
		  if(key==LEFT&&snake.direction!=1)
	  snake.direction=2;
		  else
	  if(key==DOWN&&snake.direction!=3)
		 snake.direction=4;
	   }/*endwhile(1)*/
}

void newstart()
{
	   food.yes=1;/*1表示需要出现新食物,0表示已经存在食物*/
  /*活着*/
   snake.direction=1;/*方向往右*/
   snake.x[0]=100;/*蛇头*/
   snake.y[0]=100;
   snake.x[1]=110;/*第二节*/
   snake.y[1]=100;
   snake.node=2;/*节数*/
    snake.life=0;
   PrScore();/*输出得分*/
}

/*游戏结束*/
void GameOver(void)
{
	struct person curperson;
    cleardevice();
    PrScore();
   setcolor(RED);
   settextstyle(0,0,4);
   outtextxy(200,200,"GAME OVER");


/*输入名字*/

	readfiles();
	if(score>per[4].score)
	{
		setfillstyle(1,9);
		bar(14,14,447,419);
		 settextstyle(0,0,2);
		outtextxy(5,5,"refueling! you score enter the board!");
		outtextxy(5,20,"please enter your name");
		gotoxy(5,100);
		printf(":                  ");
		gotoxy(5,100);
		scanf("%s",curperson.name);
		curperson.score=score;
		comparescore(curperson);
		writefiles(per);
	}
	else outtextxy(100,100,"you score is not enough on the board!");
	paihb();



   getch();
}

/*输出成绩*/
void PrScore(void)
{
   char str[100];

   setfillstyle(SOLID_FILL,YELLOW);
   bar(50,15,500,35);
   setcolor(6);
   settextstyle(0,0,2);

   if(Level==1)
	   sprintf(str,"score:%d LEVEL:LOW",score);
   else if(Level==2)
		sprintf(str,"score:%d LEVEL:MID",score);
   else if(Level==3)
		sprintf(str,"score:%d LEVEL:HIG",score);
   outtextxy(55,20,str);
}



void readfiles()
{
	FILE *fpread;
	if((fpread=fopen(filename,"ab+"))==NULL)
	{printf("can't open the file person.txt!");

	exit(0);

	}
	getch();
	if(fgetc(fpread)==EOF)
		initscorefiles();
         rewind(fpread);
		 fread(per,sizeof(struct person),5,fpread);
		 fclose(fpread);
}
void writefiles(struct person *tmp)
{
	FILE *fpwrite;
	if((fpwrite=fopen(filename,"wb+"))==NULL)
	{
		printf("can't open the file person.txt!");
	exit(0);

	}
	fwrite(tmp,sizeof(struct person),5,fpwrite);
	fclose(fpwrite);
}
void initscorefiles()
{
	int i;
	struct person a[5];
	for(i=0;i<5;i++)
	{
		a[i].score=0;
		strcpy(a[i].name,"nobody");
	}
	writefiles(a);
}


void comparescore(struct person des)
{
	int i,j;
	for(i=0;i<5;i++)
	{
		if(des.score>=per[i].score)
		{
			if(i<5)
			{for(j=4;j>=i+1;j--)
				per[j]=per[j-1];
			}
			per[i]=des;
			break;
		}
	}
}
void paihb()/*排行榜*/
{
	int i;
	char string[10];
	readfiles();
	 settextstyle(0,0,2);
	setfillstyle(1,9);
	bar(200,150,405,300);
	outtextxy(200,100,"highest board");

	outtextxy(200,150,"name    score");
	for(i=0;i<5;i++)
	{
		setcolor(4);
	outtextxy(200,200+i*30,per[i].name);/*姓名*/
	itoa(per[i].score,string,10);
	setcolor(14);
	outtextxy(350,200+i*30,string);/*分数*/
	}
	getch();
}



/****************************保存游戏记录*****************************************/
void save()
{
	FILE *fpwrite;
	if((fpwrite=fopen(filename,"w"))==NULL)
	{
		printf("can't save the file save.txt!");
	exit(0);

	}

	fprintf(fpwrite,"%d %d %d %d %d\n",food.yes,food.x,food.y,snake.node,snake.direction);
	for(i=0;i<=snake.node;i++)
	fprintf(fpwrite,"%d %d\n",snake.x[i],snake.y[i]);
	fclose(fpwrite);

}
/****************************读取游戏记录*****************************************/
void readfile()
{
	FILE *fpread;
	if((fpread=fopen(filename,"r"))==NULL)
	{
    printf("can't read the file person.txt!");
	exit(0);
	}
	fscanf(fpread,"%d %d %d %d %d\n",&food.yes,&food.x,&food.y,&snake.node,&snake.direction);
	/*printf("%d %d %d %d %d\n",&food.yes,&food.x,&food.y,&snake.node,&snake.direction);*/
	for(i=0;i<snake.node;i++)
	fscanf(fpread,"%d%d\n",&snake.x[i],&snake.y[i]);
	fclose(fpread);
}


/*图形结束*/
void Close(void)
{
    getch();
    closegraph();
}
void startplay()
{
	  Init();/*图形驱动*/
   DrawK();/*开始画面*/
   GamePlay();/*玩游戏具体过程*/
   Close();/*图形结束*/
}


void autoPlayGame()
{
	  Init();/*图形驱动*/
   DrawK();/*开始画面*/
   autoPlay();/*玩游戏具体过程*/
   Close();/*图形结束*/
}

/**************自动游戏******************/
void autoPlay(void)
{
   randomize();/*随机数发生器*/
   food.yes=1;/*1表示需要出现新食物,0表示已经存在食物*/
   snake.life=0;/*活着*/
   snake.direction=1;/*方向往右*/
   snake.x[0]=100;/*蛇头*/
   snake.y[0]=100;
   snake.x[1]=110;/*第二节*/
   snake.y[1]=100;
   snake.node=2;/*节数*/
   PrScore();/*输出得分*/
   while(1)/*可以重复玩游戏,压ESC键结束*/
   {
			  while(!kbhit())/*kbhit是一个函数，可以用来检查当前是否有键盘输入,在没有按键的情况下,蛇自己移动身体*/
			  {

				  if(snake.x[0]-food.x<0)
					snake.direction=1;
				  else if(snake.x[0]-food.x>0)
					  snake.direction=2;
					if(snake.y[0]-food.y<0)
					snake.direction=4;
				  else if(snake.y[0]-food.y>0)
					  snake.direction=3;

						  if(food.yes==1)/*需要出现新食物*/
						  {
							  food.x=rand()%400+60;
							  food.y=rand()%350+60;
							  /* food.x1=rand()%400+60;
							  food.y1=rand()%350+60;
							  */
							  while(food.x%10!=0)/*食物随机出现后必须让食物能够在整格内,这样才可以让蛇吃到*/
						  food.x++;
							  while(food.y%10!=0)
						  food.y++;
						  food.yes=0;/*画面上有食物了,就要将yes置0*/
						  }
							  if(food.yes==0)/*画面上有食物了就要显示*/
							  {
										  setcolor(GREEN);/*设置食物前景色。*/
										  rectangle(food.x,food.y,food.x+10,food.y-10);/*设置食物颜色*/
							  }
						 for(i=snake.node-1;i>0;i--)/*蛇的每个环节往前移动,也就是贪吃蛇的关键算法*/
						 {
							snake.x[i]=snake.x[i-1];
							snake.y[i]=snake.y[i-1];
						 }
			   /*1,2,3,4表示右,左,上,下四个方向,通过这个判断来移动蛇头*/
					  switch(snake.direction)
					  {
						 case 1:
							 if(snake.x[0]==630)
							  snake.x[0]=0;
						     else
							 snake.x[0]+=10;
						 break;/*右*/
						 case 2:
							  if(snake.x[0]==0)
							  snake.x[0]=630;
						     else
							 snake.x[0]-=10;
							 break;/*左*/
						 case 3:
							  if(snake.y[0]==60)
							 snake.y[0]=480;/*上*/
                          else
							   snake.y[0]-=10;
						 break;
						 case 4:
							 if(snake.y[0]==470)
							 snake.y[0]=60;
						 else
						 snake.y[0]+=10;break;/*下*/
					  }
				  for(i=3;i<snake.node;i++)/*从蛇的第四节开始判断是否撞到自己了，因为蛇头为两节，第三节不可能拐过来*/
				  {
					 if(snake.x[i]==snake.x[0]&&snake.y[i]==snake.y[0])
					 {
							   GameOver();/*显示失败*/
							   snake.life=1;/*0为活着，1为挂掉*/
							   break;
					 }
				   }
				 if(snake.x[0]==food.x&&snake.y[0]==food.y)/*吃到食物以后*/
					 {
							   setcolor(0);/*把画面上的食物东西去掉*/
							   rectangle(food.x,food.y,food.x+10,food.y-10);
						snake.x[snake.node]=-20;snake.y[snake.node]=-20;
							  /*新的一节先放在看不见的位置,下次循环就取前一节的位置*/
						snake.node++;/*蛇的身体长一节*/
						food.yes=1;/*画面上需要出现新的食物*/
						score+=10;
						PrScore();/*输出新得分*/
					 }
				 setcolor(4);/*画出蛇*/
				 for(i=0;i<snake.node;i++)
					rectangle(snake.x[i],snake.y[i],snake.x[i]+10,
							   snake.y[i]-10);
				 delay(gamespeed);
				 setcolor(0);/*用黑色去除蛇的的最后一节*/
				 rectangle(snake.x[snake.node-1],snake.y[snake.node-1],
				 snake.x[snake.node-1]+10,snake.y[snake.node-1]-10);
		      }  /*endwhile（！kbhit）*/




		if(snake.life==1)/*如果蛇死就跳出循环*/
			break;
		key=bioskey(0);/*接收按键：bioskey直接使用BIOS服务的键盘接口。*/
		if(key==ESC)/*按ESC键退出*/
		   break;


	   }/*endwhile(1)*/
}



void voice(void)
{
	int freq;
for(freq=50;freq<5000;freq+=50)
{
sound(freq);
delay(1);
}
}


void saveGame()
{

}
void playBack()
{


}






#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dos.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#define H 32
#define W 64
/*
last edition note:
- Ghots doesn't disappear from spawn	(solved, they were spawing +1 in y scale, not in setted position)
- Ghots passing trough wall if they spawned next to it (solved, same case as ^)
- Prev receiving not allowed values (If they pass through each other they delete a point)
- If the ghost is setted to spawn in 30,(around 20 or 22+) they doesn't move)
*/


void display(void);
int assign(char**);

char ggrade[H][W];
char grade[H][W] = {
{"################################################################"},
{"#                                                              #"},
{"#              ####################################            #"},
{"#                                                              #"},
{"#    ######                                          ######    #"},
{"#        ##        8                         8       ##        #"},
{"#        ##                                          ##        #"},
{"#        ##                     @                    ##        #"},
{"#     8  ##        ##                       ##       ##  8     #"},
{"#        ##        ##                       ##       ##        #"},
{"#        ##        ##                       ##       ##        #"},
{"#        ##        ##                       ##       ##        #"},
{"#    ######        ###########################       ######    #"},
{"#        ##        ##                       ##       ##        #"},
{"#        ##        ##           8           ##       ##        #"},
{"#        ##        ##                       ##       ##        #"},
{"#        ##        ##                       ##       ##        #"},
{"#     8  ##                     8                    ##  8     #"},
{"#        ##                                          ##        #"},
{"#        ##                                          ##        #"},
{"#    ######                     8                    ######    #"},
{"#                                                              #"},
{"#              ####################################            #"},
{"#                                                              #"},
{"#                                                              #"},
{"#             ##              ##              ##               #"},
{"#     8       ##      8       ##       8      ##        8      #"},
{"#             ##              ##              ##               #"},
{"#      ##################################################      #"},
{"#                                                              #"},
{"#                                                              #"},
{"################################################################"},
};

char *gvisor = ggrade[0];
char *visor = grade[0];
int lastmove;
int state = 1;
unsigned int p[2] = {3,24};
unsigned int score = 0;
static int g2[20][2];
int goal;
int total;

void position(void)
{
	int x, y;
	int px,py;
	
	for(int i = 0,v = 0; i < H * W; ++i)
		{
			if(*(visor+i) == ' ')
				{
				*(visor+i) = '*';	
				++goal;							
				}
				
			if(*(visor+i) != '8')
				*(gvisor+i) = *(visor+i);
			
			if(*(visor+i) == '8'){
				*(gvisor+i) = '*';
					++total;
				g2[v][0] = y - 1;
				g2[v++][1] = i % 64;
				}
				
		if((i % 64) == 0)
			++y;
		if(*(visor+i) == '@')
			{
			p[0] = y - 1;
			p[1] = i % 64;	
			}
	}
}

void input(void)
{
	int c;

	if(kbhit())	
		{
			c = getch();
		if(c == 75 || c == 72 || c == 77 || c == 80)
			lastmove = c;
			}
}
void color(int d)
{
	//Gets the cursor in the terminal ( HANDLE, type to hold mouse location)
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), d);
}

void moving(void)
{
			switch(lastmove)
			{
			case 75:
				if(grade[p[0]][p[1]-1] == '#')
						break;
						
				if(grade[p[0]][p[1]-1] == '*')
					++score;
				else if(grade[p[0]][p[1]-1]  == '8')
					{
						state = FALSE;
						break;
					}
					
					ggrade[p[0]][p[1]] = ' ';
					grade[p[0]][p[1]--] = ' ';
					grade[p[0]][p[1]] = '@';	
				break;
			case 77:
					if(grade[p[0]][p[1]+1] == '#')
						break;
						 
				if(grade[p[0]][p[1]+1] == '*')
					++score;
				else if(grade[p[0]][p[1]+1]  == '8')
					{
						state = FALSE;
						break;
					}
					
					ggrade[p[0]][p[1]] = ' ';
					grade[p[0]][p[1]++] = ' ';
					grade[p[0]][p[1]] = '@';	
				break;
			case 80:
					if(grade[p[0]+1][p[1]] == '#')
						break;
						
				if(grade[p[0]+1][p[1]] == '*')
					++score;			
				else if(grade[p[0]+1][p[1]] == '8')
					{
						state = FALSE;
						break;
					}			
					ggrade[p[0]][p[1]] = ' ';
					grade[p[0]++][p[1]] = ' ';
					grade[p[0]][p[1]] = '@';	
				break;
			case 72:
					if(grade[p[0]-1][p[1]] == '#')
						break;
						
				if(grade[p[0]-1][p[1]] == '*')
					++score;	
				else if(grade[p[0]-1][p[1]]  == '8')
					{
						state = FALSE;
						break;
					}					
					ggrade[p[0]][p[1]] = ' ';
					grade[p[0]--][p[1]] = ' ';
					grade[p[0]][p[1]] = '@';	
				break;
	
			}
}

void g_move(void)
{
	srand(1);
    time_t t1;
	char prev;
	srand ((unsigned) time (&t1));
	for(int i = 0; (g2[i][0] != 0) && (g2[i][1] != 0); ++i)
	{
	int r = rand() % 5;
		switch(r){
		case 1:	
				if(grade[g2[i][0]+1][g2[i][1]] == '#')
					break;
				else {
			prev = (grade[g2[i][0]+1][g2[i][1]] == '8') ? ggrade[g2[i][0]+1][g2[i][1]] : grade[g2[i][0]+1][g2[i][1]];
			grade[g2[i][0]+1][g2[i][1]] = '8';
			grade[g2[i][0]++][g2[i][1]] = prev;
			}
			break;
		case 2:
				if(grade[g2[i][0]-1][g2[i][1]] == '#')
					break;
				else {
			prev = (grade[g2[i][0]-1][g2[i][1]] == '8') ? ggrade[g2[i][0]-1][g2[i][1]]: grade[g2[i][0]-1][g2[i][1]];
			grade[g2[i][0]-1][g2[i][1]] = '8';
			grade[g2[i][0]--][g2[i][1]] = prev;
					}
			break;
		case 3:
				if(grade[g2[i][0]][g2[i][1]+1] == '#')
					break;
				else {
			prev = (grade[g2[i][0]][g2[i][1]+1] == '8') ? ggrade[g2[i][0]][g2[i][1]+1] : grade[g2[i][0]][g2[i][1]+1];
			grade[g2[i][0]][g2[i][1]+1] = '8';
			grade[g2[i][0]][g2[i][1]++] = prev;
					}
			break;
		case 4:
				if(grade[g2[i][0]][g2[i][1]-1] == '#')
					break;
				else {
		prev = (grade[g2[i][0]][g2[i][1]-1] == '8') ? ggrade[g2[i][0]][g2[i][1]-1] : grade[g2[i][0]][g2[i][1]-1];
		grade[g2[i][0]][g2[i][1]-1] = '8';
		grade[g2[i][0]][g2[i][1]--] = prev;
				}
			break;
		default:
			break;
		}
	}
	
}

//Move the cursors to 0,0 position, then writting the next frame without deleting the previous one (prevent blink)
void cposition(int x, int y)
{
   COORD coord = { x, y };
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void check_state(void)
{
	if(score == goal)
	{
			system("cls");
			printf("\n\n\n\n\n\t\t\t\t\tYOU WIN!!\n\n\n\n\n");
		state = FALSE;
			}	else for(int i = 0; g2[i][0] != 0; ++i ){
						if((p[0] == g2[i][0]) && (p[1] == g2[i][1]))
					{
					system("cls");
					printf("\n\n\n\n\n\t\t\t\t\tYOU LOST!!\n\n\n\n\n");
					state = FALSE;
					}
				}
}

void display(void)
{
	char *text = visor;
	for(int i = 1; i <= H; ++i)
	{
		printf("\t\t\t\t\t\t");
		for(int h = 0; h <= W-1; ++h)
		{

			switch(*(text+h)){
				case '#':
					color(9);
				break;
				case '8':
					color(4);
				break;
				case '@':
					color(14);
				break;
			}

			printf("%c",*(text+h));
		color(7);
		}
		text += 64;
		printf("\n");
	}
}

int main()
{
	position();
//	g_move();
//		display();
	while(state)
	{
		display();
		input();	
		moving();	
		g_move();
		printf("\n\t\t\t\t\t\tYOUR TOTAL SCORE: %d",score);
//		Sleep(10);
		cposition(0,0);
		check_state();
	}
}

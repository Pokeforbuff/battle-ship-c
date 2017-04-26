#include<stdio.h>
#include<curses.h>
int active_row=4;
int active_col=4;
int remNodes[]={2,3,3,4,5}; //Used to track if ship destroyed
char* shipNames[]={"Destroyer","Submarine","Cruiser","Battleship","Carrier"};
char letters[]={'A','B','C','D','E','F','G','H','I','J'};
WINDOW* logWindow;
WINDOW* targeterWindow;
int playerTargetMap[10][10]={
	{0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,5,0,1,0,0},
    {0,0,0,0,0,5,0,1,0,0},  // 1: Destroyer
    {0,0,0,0,0,5,0,0,0,0},  // 2: Submarine
 	{0,0,0,0,0,5,0,0,0,0},  // 3: Cruiser
    {4,4,4,4,0,5,0,0,0,0},  // 4: Battleship
    {0,0,0,0,0,0,0,0,0,0},  // 5: Carrier
    {0,2,0,0,0,0,0,0,0,0},
    {0,2,0,0,0,3,3,3,0,0},
    {0,2,0,0,0,0,0,0,0,0}
};
int playerShootMap[10][10];
void generateTargetMap(){
	wclear(targeterWindow);
	wprintw(targeterWindow,"   1 2 3 4 5 6 7 8 9 10\n\n");
	for(int i=0;i<10;i++){
		wprintw(targeterWindow,"%c ",letters[i]);
		for(int j=0;j<10;j++){
			if(i==active_row && j==active_col)
				wprintw(targeterWindow," +");
			else if(playerShootMap[i][j]==1)
				wprintw(targeterWindow," x");
			else wprintw(targeterWindow," o");
	    }
	  wprintw(targeterWindow,"\n");
	}	
	wrefresh(targeterWindow);
}
void shoot(){
	if(playerTargetMap[active_row][active_col]!=0){
		playerShootMap[active_row][active_col]=1;
		remNodes[playerTargetMap[active_row][active_col]-1]-=1;
		wprintw(logWindow,"\nAt %c-%d: Successfully damaged the %s",letters[active_row],active_col+1,shipNames[playerTargetMap[active_row][active_col]-1]);
		playerTargetMap[active_row][active_col]=0;
	}	
	else {
		wprintw(logWindow,"\nAt %c-%d: Failed to hit any target",letters[active_row],active_col+1);
	}
	wrefresh(logWindow);
	generateTargetMap();
}
int main(){
	initscr();
	noecho();
	curs_set(0);
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++)
			playerShootMap[i][j]=0;
	}	
	refresh();
	targeterWindow=newwin(25,25,2,2);
	logWindow=newwin(60,60,2,30);
	generateTargetMap();
	wprintw(logWindow,"\n");
	wrefresh(logWindow);
	char input;
	while(1){	
		input=getch();
		if (input == '\033') {
    		getch();
    		switch(getch()) { 
        		case 'A':
            		if(active_row==0)
						active_row=9;
					else active_row--;
					generateTargetMap();
            		break;
        		case 'B':
            		if(active_row==9)
						active_row=0;
					else active_row++;
					generateTargetMap();
            		break;
        		case 'C':
            		if(active_col==9)
						active_col=0;
					else active_col++;
					generateTargetMap();
            		break;
        		case 'D':
        		    if(active_col==0)
						active_col=9;
					else active_col--;
					generateTargetMap();
            		break;
    		}
		} 
		else if (input==' '){
			shoot();
		}
	}
	endwin();
	return 0;
}
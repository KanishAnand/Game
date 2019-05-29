#include<stdio.h>
#include<ncurses.h>
#include<unistd.h>
#include<stdlib.h>
//#define ANSI_COLOR_RED  "\x1b[31m"
int main(){
	int flag=0,x=15,y=10,i=0,c=93,d=26,delay=25000,j=0,a=100,b=28,count=0;
	
	initscr();					//first screen to start game...
	curs_set(false);
	// colour the text
	mvprintw(18,68,"START");
	getch();
	clear();

	initscr();
	noecho();
	curs_set(false);
	nodelay(stdscr,TRUE);  //this is to prevent getch() for waiting for input
	char p = getch();
	while(true) {
		nodelay(stdscr,TRUE);
		clear(); //this clears previous screen i.e removes previous position of ball
		if(flag == 1){
			a = rand();
			b = rand();
			b %= 36;
			a %= 120;
			flag=0;
			c = a - a%10;
			d = b - b%6;
		}

		mvprintw(b,a,"W");   //(y,x);
		mvprintw(y,x,"*");
		mvprintw(d,c,"-_-");
		//142 x
		//37 y
		p = getch();
		if(p == 67) {                    //right
			i = 1;
			j = 0;
			if(count == 0){
				count = 1;
			}
		}
		else if(p == 68){
			i = -1;			//left
			j = 0;
			if(count == 2){
				count = 3;
			}
		}
		else if(p == 65){
			j = -1;			//up
			i = 0;
			if(count == 3){
				count = 0;
				flag=1;
			}
		}
		else if(p == 66){
			j = 1;			//down
			i = 0;
			if(count == 1){
				count = 2;
				flag=1;
			}
		} 
		x += i;
		y += j;
		if(j == 0){
			delay=25000;      //done to make speed equal in both  vertical and hz direction
		}
		else{
			delay=33000;
		}
		if( (x == c && y == d) || x == 142 || y == 37|| x == 0|| y == 0){
			nodelay(stdscr,FALSE);
			clear();
			initscr();
			mvprintw(15,65,"OUT");
			mvprintw(20,55,"WANT TO PLAY AGAIN ? => y / n");
			char ans;
			ans = getch();
			while(ans != 'y' && ans != 'n'){
				mvprintw(25,55,"CHOOSE VALID KEY FROM : y/n");
				ans = getch();
			}
			if(ans == 'y'){
				a = 100;
				b = 28;
				x = 15;
				y = 10;
				c = 93;
				d = 26;
				count=0;
				flag=0;
				i=0;
				j=0;
				continue;
			}
			else{
				break;
			}
			/*else{
				mvprintw(28,71,"choose valid key");
			}*/
		}
		
		if(x == a && y == b){
			nodelay(stdscr,FALSE);
			clear();
			initscr();
			mvprintw(15,71,"YOU WON");
			getch();
			break;
		}
		usleep(delay);  //like delay hold on screen otherwise we are unable to see ball due to clear action i.e very fast execution of lop
	}
	endwin();   		// to restore previous terminal setting
	printf("\n");
	return 0;
}

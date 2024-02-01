#include <iostream>
#include "clui.h"
using namespace std;

int timesec;
bool EXIT = false;
short int playerone;
short int playertwo;
bool gameover = true;
short int width = 30;
short int height = 15;
short int snake_speed;
int number_of_players;
short int color_choosen[10];
short int windorow = get_window_rows();
short int windocol = get_window_cols();
short int colornumber3[10]={110,0,64,27,255,255,184,255,0,0};
short int colornumber1[10]={245,194,70,2,3,3,128,251,255,255};
short int colornumber2[10]={100,0,255,156,200,11,9,0,255,111};
char color_names[10][12] = {"light_red" , "red" ,"light_green" ,"green", "light_blue", "blue" , "purple" , "pink" , "yellow" , "orange"};

struct point{
	short int x;
	short int y;
}apple , bomb;
struct snake{
	point head;
	short int dir;
	short int tail_lenght;
	point tail[20];
}snake1,snake2;
struct players{
	char name[20];
	short int score;
	short int color;
	short int color1;
	short int color2;
	short int color3;
}player_list[10]={{'\0',0},{'\0',0},{'\0',0},{'\0',0},{'\0',0},{'\0',0},{'\0',0},{'\0',0},{'\0',0},{'\0',0},};

void start_game(void);

void num_to_color(int color , players&playernum){
	if(color == 1){
		playernum.color1=245;
		playernum.color2=100;
		playernum.color3=110;
	}
	else if(color == 2){
		playernum.color1=194;
		playernum.color2=0;
		playernum.color3=0;
	}
	else if(color == 3){
		playernum.color1=70;
		playernum.color2=255;
		playernum.color3=64;
	}
	else if(color == 4){
		playernum.color1=2;
		playernum.color2=156;
		playernum.color3=27;
	}
	else if(color == 5){
		playernum.color1=3;
		playernum.color2=200;
		playernum.color3=255;
	}
	else if(color == 6){
		playernum.color1=3;
		playernum.color2=11;
		playernum.color3=225;
	}
	else if(color == 7){
		playernum.color1=128;
		playernum.color2=9;
		playernum.color3=184;
	}
	else if(color == 8){
		playernum.color1=251;
		playernum.color2=0;
		playernum.color3=255;
	}
	else if(color== 9){
		playernum.color1=255;
		playernum.color2=255;
		playernum.color3=0;
	}
	else if(color== 10){
		playernum.color1=255;
		playernum.color2=111;
		playernum.color3=0;
	}
}

int length(char*str){
	int i =0 ;
	while(str[i] != '\0'){
		i++ ;
	}
	return i ;
}

void swapplayer(players &first , players &second){
	if(first.score < second.score){
		int tool= length(first.name);
		char  temp[tool];
		for(int k = 0 ; k <tool+1 ; k++){
			temp[k]=first.name[k];
		}
		for(int k = 0 ; k <20 ;k++){
			first.name[k]=second.name[k];
		}
		for(int k = 0 ; k <tool+1;k++){
			second.name[k]=temp[k];
		}
		int temp2 = first.score;
		first.score = second.score;
		second.score = temp2 ;
		temp2 = first.color1;
		first.color1 = second.color1;
		second.color1=temp2;
		temp2 = first.color2;
		first.color2 = second.color2;
		second.color2=temp2;
		temp2 = first.color3;
		first.color3 = second.color3;
		second.color3=temp2;
		temp2 = first.color;
		first.color = second.color;
		second.color = first.color;
	}
}

char menu(void){
	clear_screen();
	cout<<"\n"<<"ENTER NUMBER YOU WANT :"<<endl;
	cout<<"-------------------------\n"<<endl;
	cout<<"1_START GAME"<<endl;
	cout<<"2_SCORE TABLE"<<endl;
	cout<<"3_SWITCH USERS"<<endl;
	cout<<"4_EXIT THE GAME"<<endl;
	cout<<"\n"<<"ENTER NUMBER : ";
    save_cursor();
	cursor_to_pos(windorow -15 , 1);
	change_color_rgb(0,255,0);
	for(int i = 0 ; i < windocol ; i ++){
		cout<<"_";
	}
	cout<<"RULES :"<<endl;
	cout<<"1_MAXIMUM PLAYERS ARE 10 !"<<endl;
	cout<<"2_PLAYER ONE MOVES WITH [w,a,s,d] , AND PLAYER TWO MOVES WITH [up , down , left , right]"<<endl;
	cout<<"3_YOU SHOULD EAT APPLE '@' TO REACH 10 SCORE ;)"<<endl;
	cout<<"4_YOU SHOULD'NT HIT THE WALLS OR BOMB '#' OR SNAKE ! IT COST 20 SCORE AND END THE GAME :( "<<endl;
	cout<<"FOR A BETTER PLAYING , MUXIMIZE THE SCREEN , GOODLUCK :)";
	restore_cursor();
	reset_color();
	char menureturn ;
	cin>>menureturn;
	while(menureturn <48 || menureturn>52){
		cout<<"ENTER A NUMBER BETWEEN 1 AND 4 :";
		cin>>menureturn;
	}
	return menureturn ;
}

int choose_players(void){
	if(number_of_players<2){
		cout<<"MAKE PLAYER FIRST !"<<endl;
		return 0;
	}
	for(int i = 0 ; i < number_of_players ; i++){
		change_color_rgb(player_list[i].color1, player_list[i].color2, player_list[i].color3);
		cout<<i+1<<"_"<<player_list[i].name<<endl;
		reset_color();
	}
	cout<<"PLAYER ONE , CHOOSE : ";
	cin>>playerone;
	clear_screen();
	for(int i = 0 ; i < number_of_players ; i++){
		change_color_rgb(player_list[i].color1, player_list[i].color2, player_list[i].color3);
		if(i+1==playerone){
		cout<<i+1<<"_"<<player_list[i].name<<"    CHOOSED !"<<endl;
		}
		else{
			cout<<i+1<<"_"<<player_list[i].name<<endl;
		}
		reset_color();
	}
	cout<<"PLAYER TWO , CHOOSE : ";
	cin>>playertwo;
	while(playertwo==playerone){
		cout<<"ENTER AGAIN !"<<endl;
		cin>>playertwo;
	}
	start_game();
	return 0;
}

short int speed_change(void){
	short int speed;
	cout<<"SELECT THE SNAKES SPEED :\n1_SLOW\n2_MEDIUM\n3_FAST"<<endl;
	cin>>speed;
	switch(speed){
		case 1 :
			return 60;
			break;
		case 2:
			return 45 ;
			break ;
		case 3:
			return 30 ;
			break;
		default:
			cout<<"\nENTER 1 OR 2 OR 3 !"<<endl;
			return speed_change();
	}
}

void updating_game(void){
	point temp , temp2;
	if(snake1.dir!=0){
		temp.x = snake1.tail[0].x ;
		temp.y = snake1.tail[0].y ;
		snake1.tail[0].x = snake1.head.x;
		snake1.tail[0].y = snake1.head.y;
		for(int i = 1 ; i < snake1.tail_lenght;i++){
			temp2.x = snake1.tail[i].x ;
			temp2.y = snake1.tail[i].y ;
			snake1.tail[i].x = temp.x ;
			snake1.tail[i].y = temp.y ;
			temp.x = temp2.x; 
			temp.y = temp2.y ;
		}
	}
	if(snake2.dir!=0){
		temp.x = snake2.tail[0].x ;
		temp.y = snake2.tail[0].y ;
		snake2.tail[0].x = snake2.head.x;
		snake2.tail[0].y = snake2.head.y;
		for(int i = 1 ; i < snake2.tail_lenght;i++){
			temp2.x = snake2.tail[i].x ;
			temp2.y = snake2.tail[i].y ;
			snake2.tail[i].x = temp.x ;
			snake2.tail[i].y = temp.y ;
			temp.x = temp2.x; 
			temp.y = temp2.y ;
		}
	}
	switch(snake1.dir) {
		case 3 :
			snake1.head.y -=1;
			break;
		case 4 :
			snake1.head.y +=1;
			break;
		case 1:
			snake1.head.x -=1;
			break;
		case 2:
			snake1.head.x +=1;
	}
	switch(snake2.dir) {
		case 3 :
			snake2.head.y -=1;
			break;
		case 4 :
			snake2.head.y +=1;
			break;
		case 1:
			snake2.head.x -=1;
			break;
		case 2:
			snake2.head.x +=1;
	}
	if(snake1.head.x>=width || snake1.head.x<0 ||snake1.head.y<0||snake1.head.y>=height){
		player_list[playerone-1].score -=20;
		gameover = false ;
	}
	if (snake1.head.x==apple.x && snake1.head.y == apple.y) { 
		player_list[playerone-1].score += 10; 
		apple.x = rand() % width; 
		apple.y = rand() % height; 
		snake1.tail_lenght+=1; 
	} 
	if(snake1.head.x==bomb.x && snake1.head.y==bomb.y){
		player_list[playerone-1].score -=20;
		gameover = false ;
	}
	for (int i = 0; i < snake1.tail_lenght ; i++) { 
		if (snake1.tail[i].x == snake1.head.x && snake1.tail[i].y == snake1.head.y){ 
			player_list[playerone-1].score -=20;
			gameover=false; 
		}
		if(snake2.head.x==snake1.tail[i].x && snake2.head.y==snake1.tail[i].y){
			player_list[playertwo-1].score -=20;
			gameover=false ;
		}
	} 
	if(snake2.head.x>=width || snake2.head.x<0 ||snake2.head.y<0||snake2.head.y>=height){
		player_list[playertwo-1].score -=20;
		gameover = false ;
	}
	if (snake2.head.x==apple.x && snake2.head.y == apple.y) { 
		player_list[playertwo-1].score += 10; 
		apple.x = rand() % width; 
		apple.y = rand() % height; 
		snake2.tail_lenght+=1; 
	} 
	if(snake2.head.x==bomb.x && snake2.head.y==bomb.y){
		player_list[playertwo-1].score -=20;
		gameover = false ;
	}
	for (int i = 0; i < snake2.tail_lenght ; i++) { 
		if (snake2.tail[i].x == snake2.head.x && snake2.tail[i].y == snake2.head.y){ 
			player_list[playertwo-1].score -=20;
			gameover=false; 
		}
		if(snake1.head.x==snake2.tail[i].x && snake1.head.y==snake2.tail[i].y){
			player_list[playerone-1].score -=20;
			gameover=false ;
		}
	} 
}

void screen_build(void){
	clear_screen();
	for(int i = 0 ; i < width+1 ; i ++){
		cout<<"_";
	}
	cout<<endl;
	for(int i = 0 ; i < height ; i++){
		for(int j = 0 ; j<width+1 ; j++){
			if(j==0){
				cout<<"|";
			}
			else if(j==width){
				cout<<"|";
			}
			else if(snake1.head.x==j && snake1.head.y==i){
				change_color_rgb(player_list[playerone-1].color1, player_list[playerone-1].color2,player_list[playerone-1].color3);
				cout<<"O";
				reset_color() ;
			}
			else if(snake2.head.x==j && snake2.head.y==i){
				change_color_rgb(player_list[playertwo-1].color1, player_list[playertwo-1].color2,player_list[playertwo-1].color3);
				cout<<"O";
				reset_color() ;
			}
			else if(apple.x==j && apple.y==i){
				change_color_rgb(0,255,76);
				cout<<"@";
				reset_color();
			}
			else if (bomb.x==j && bomb.y==i){
				change_color_rgb(196,27,27);
				cout<<"#";
				reset_color();
			}
			else {
			bool fasele = true;
			for(int k = 0 ; k < snake1.tail_lenght ; k++){
				if(snake1.tail[k].x == j && snake1.tail[k].y == i){
					change_color_rgb(player_list[playerone-1].color1,player_list[playerone-1].color2,player_list[playerone-1].color3);
					cout<<"o";						
					reset_color();
					fasele = false ;
				}
			}
			for(int k = 0 ; k < snake2.tail_lenght ; k++){
				if(snake2.tail[k].x==j && snake2.tail[k].y==i){
					change_color_rgb(player_list[playertwo-1].color1,player_list[playertwo-1].color2,player_list[playertwo-1].color3);
					cout<<"o";
					reset_color();
					fasele = false ;
				}
			}
			if(fasele){
				cout<<" ";
			}
			}
		}
		cout<<endl;
	}
	cout<<"|" ;
    for (int i = 0; i < width-1; i++){
		cout << "_"; 
	}
	cout<<"|" ;
    cout << endl; 
	save_cursor();
	cursor_to_pos(windorow-10,1);
	change_color_rgb(255,0,80);
	for(int i = 0 ; i < windocol;i++){
	cout<<"_";
	}
	reset_color();
	change_color_rgb(player_list[playerone-1].color1,player_list[playerone-1].color2,player_list[playerone-1].color3);
	cout<<"\nPLAYER ONE'S SCORE : "<<player_list[playerone-1].score<<endl;
	reset_color();
	change_color_rgb(player_list[playertwo-1].color1,player_list[playertwo-1].color2,player_list[playertwo-1].color3);
	cout<<"PLAYER TWO'S SCORE : "<<player_list[playertwo-1].score<<endl;
	reset_color();
	change_color_rgb(255,0,80);
	short int mintime = (timesec /1000)/60;
	short sectime = (timesec/1000)%60;
	cout<<"TIME REMAIN "<<mintime<<" : "<<sectime;
	reset_color();
	cout<<"\n\nPRESS 'Esc' TO END GAME !";
	cout<<"\nPRESS 'x' TO STOP !";
	restore_cursor();
}

void inputs(void){
	if(is_keyboard_hit()){
		switch(getch()){
			case 'w' :
				snake1.dir=3;
				break;
			case 'a' :
				snake1.dir=1;
				break;
			case 's' :
				snake1.dir =4 ;
				break;
			case 'd' :
				snake1.dir=2;
				break;
			case 72 :
				snake2.dir=3;
				break;
			case 75 :
				snake2.dir=1;
				break;
			case 80 :
				snake2.dir=4;
				break;
			case 77 :
				snake2.dir=2;
				break;
			case 'x' :
				snake2.dir=0;
				snake1.dir=0;
				break;
			case 27 :
				gameover = false;
				break;
		}
	}
}

void start_game(void){
	clear_screen();
	snake_speed = speed_change() ;
	gameover = true ;
	snake1.dir=0;
	snake2.dir=0;
	snake1.head.x = width/2 -2 ;
	snake2.head.x = width/2 +2 ;
	snake1.head.y = height/2 -2 ;
	snake2.head.y = height/2 -2;
	snake1.tail_lenght=3;
	snake2.tail_lenght=3;
	for(int z =0 ; z <3 ; z++){
		snake1.tail[z].x=snake1.head.x;
		snake1.tail[z].y=snake1.head.y+z+1;
	}
	for(int z =0 ; z <3 ; z++){
		snake2.tail[z].x=snake2.head.x;
		snake2.tail[z].y=snake2.head.y+z+1;
	}
	snake1.dir = 0 ;
	snake2.dir = 0 ;
	apple.x = rand() % width ;
	apple.y = rand() % height ;
	bomb.x = rand() % width ;
	bomb.y = rand() % height ;
	timesec = 120000;
	while(gameover){
		screen_build();
		inputs();
		inputs();
		updating_game();
		delay(snake_speed);
		if(snake1.dir!=0 || snake2.dir!=0){
			timesec-=snake_speed*3;
		}
		if(timesec<0){
			gameover = false;
		}
	}
	screen_build();
	if(timesec<0){
		save_cursor();
		cursor_to_pos(windorow-16,10);
		change_background_color(6);
		change_color_rgb(0,0,0);
		cout<<"TIME IS UP !";
		reset_color();
		restore_cursor();
	}
	else{
		save_cursor();
		cursor_to_pos(windorow-16,10);
		change_background_color(6);
		change_color_rgb(0,0,0);
		cout<<"GAME OVER !";
		reset_color();
		restore_cursor();	
	}
	delay(5000);
}

void starter(void){
	clear_screen();
	if(number_of_players>8){
		cout<<"THERE IS ALREADY PLAYERS , YOU CAN'T MAKE TWO MORE PLAYERS"<<endl;
		choose_players();
	}
	else{
		number_of_players +=2 ;
		cout<<"PLAYER NUMBER "<<number_of_players-1<<" ENTER NAME :";
		cin>>player_list[number_of_players-2].name;
		cout<<"\nENTER A COLOR : \n";
		playerone = number_of_players-1;
		playertwo = number_of_players;
		for(int j = 0 ; j<10 ; j++){
			change_color_rgb(colornumber1[j], colornumber2[j], colornumber3[j]);
			if(color_choosen[j]==1){
				cout<<j+1<<"_"<<color_names[j]<<"     CHOSEN !"<<endl;
			}
			else{
				cout<<j+1<<"_"<<color_names[j]<<endl;
			}
	   		reset_color();
			}
		cin>>player_list[number_of_players-2].color;
		while(color_choosen[player_list[number_of_players-2].color-1]==1){
			cout<<"THE COLOR "<<player_list[number_of_players-2].color<<" IS CHOOSEN ! ENTER AGAIN :";
			cin>>player_list[number_of_players-2].color;
		}
		color_choosen[player_list[number_of_players-2].color-1]=1;
		num_to_color(player_list[number_of_players-2].color , player_list[playerone-1]);
		cout<<"\nPLAYER NUMBER "<<number_of_players<<" ENTER NAME :";
		cin>>player_list[number_of_players-1].name;
		cout<<"\nENTER A COLOR :"<<endl;
			for(int j = 0 ; j<10 ; j++){
				change_color_rgb(colornumber1[j], colornumber2[j], colornumber3[j]);
				if(color_choosen[j]==1){
					cout<<j+1<<"_"<<color_names[j]<<"     CHOSEN !"<<endl;
				}
				else{
					cout<<j+1<<"_"<<color_names[j]<<endl;
				}
				reset_color();
			}
		cin>>player_list[number_of_players-1].color;
		while(color_choosen[player_list[number_of_players-1].color-1]==1){
			cout<<"THE COLOR "<<player_list[number_of_players-1].color<<" IS CHOOSEN ! ENTER AGAIN :";
			cin>>player_list[number_of_players-1].color;
		}
		color_choosen[player_list[number_of_players-1].color-1]=1;
		num_to_color(player_list[number_of_players-1].color , player_list[playertwo-1]);
	}
	start_game();
}

int score_table(void){
	clear_screen() ;
	if(number_of_players==0){
		save_cursor();
		cursor_to_pos(windorow/2,windocol/2);
		change_color_rgb(255, 0, 13);
		cout<<"THERE IS NO PLAYER YET !"<<endl;
	    reset_color();
		restore_cursor();
		delay(3000);
		clear_screen();
		return 0 ;
	}
	for(int i = 0 ; i < number_of_players ; i++){
		for(int j =i+1;j<number_of_players ; j++){
			swapplayer(player_list[i],player_list[j]);
		}
	}
	cout<<"      PLAYER      |       SCORE       "<<endl;
	cout<<"--------------------------------------"<<endl;
	for(int i = 0 ; i < number_of_players ; i++){
		int fas = (20 - length(player_list[i].name)) ;
		if(fas%2!=0){
			for(int j = 0 ;j < fas/2 ; j ++){
				cout<<" ";
			}
		}
		else{
			for(int j = 0 ;j < (fas/2)-1 ; j ++){
				cout<<" ";
			}
		}
		change_color_rgb(player_list[i].color1, player_list[i].color2, player_list[i].color3);
		cout<<player_list[i].name;
	    reset_color();
		for(int j = 0 ;j < (fas/2)-1 ; j ++){
			cout<<" ";
		}
		cout<<"|";
		cout<<"         ";
		change_color_rgb(player_list[i].color1, player_list[i].color2, player_list[i].color3);
		cout<<player_list[i].score <<endl;
		reset_color();
	}
	bool khoroj = false ;
	cout<<"\n\nPRESS ANY KEY TO EXIT !!!"<<endl;
	while(!khoroj){
		if(getch()){
			khoroj=true;
		}
	}
}
void delet_player(players list[] ){
	cout<<"WICH ONE YOU WANT TO DELETE ?"<<endl;
	for(int i = 0 ; i < number_of_players ; i++){
		change_color_rgb(player_list[i].color1, player_list[i].color2, player_list[i].color3);
		cout<<i+1<<"_"<<player_list[i].name<<endl;
		reset_color();
	}
	short int delnum;
	cin>>delnum ;
	player_list[delnum-1].score=0;
	color_choosen[player_list[delnum-1].color-1]=0;
	for(int i = delnum-1 ; i<number_of_players-1 ;i++){
		short int j = i+1 ;
			int tool= length(player_list[i].name);
			char  temp[tool];
			for(int k = 0 ; k <tool+1 ; k++){
				temp[k]=player_list[i].name[k];
			}
			for(int k = 0 ; k <20 ;k++){
				player_list[i].name[k]=player_list[j].name[k];
			}
			for(int k = 0 ; k <tool+1;k++){
				player_list[j].name[k]=temp[k];
			}
			int temp2 = player_list[i].score;
			player_list[i].score = player_list[j].score;
			player_list[j].score = temp2 ;
			temp2 = player_list[i].color1;
			player_list[i].color1 = player_list[j].color1;
			player_list[j].color1=temp2;
			temp2 = player_list[i].color2;
			player_list[i].color2 = player_list[j].color2;
			player_list[j].color2=temp2;
			temp2 = player_list[i].color3;
			player_list[i].color3 = player_list[j].color3;
			player_list[j].color3=temp2;
			temp2 = player_list[i].color;
			player_list[i].color = player_list[j].color;
			player_list[j].color = player_list[i].color;
	}
	number_of_players -=1;
}

void user_change(void){
	clear_screen() ;
	if(number_of_players==0){
		cout<<"THERE IS NO PLAYER , YOU SHOUD ADD PLAYERS !"<<endl;
		cout<<"ENTER NUMBER OF PLAYERS : ";
		cin>>number_of_players;
		for(int i = 0 ; i < number_of_players ; i++){
			cout<<"PLAYER NUMBER "<<i+1<<" NAME :"<<endl;
			cin>>player_list[i].name ;
			cout<<"ENTER THE COLOR YOU WANT : "<<endl;
			for(int j = 0 ; j<10 ; j++){
				change_color_rgb(colornumber1[j], colornumber2[j], colornumber3[j]);
				if(color_choosen[j]==1){
					cout<<j+1<<"_"<<color_names[j]<<"     CHOSEN !"<<endl;
				}
				else{
					cout<<j+1<<"_"<<color_names[j]<<endl;
				}
				reset_color();
			}
			cin>>player_list[i].color;
			while(color_choosen[player_list[i].color-1]==1){
				cout<<"THE COLOR "<<player_list[i].color<<" IS CHOOSEN ! ENTER AGAIN :";
				cin>>player_list[i].color;
			}
			while(player_list[i].color>10 || player_list[i].color<1){
				cout<<"ENTER NUMBER BETWEEN 1 AND 10 !"<<endl;
				cin>>player_list[i].color;
			}
			color_choosen[player_list[i].color-1]=1;
			num_to_color(player_list[i].color , player_list[i]);
			clear_screen();
		}
	}
	else{
		short int number_choosen;
		cout<<"WHAT DO YOU WANT ?"<<endl;
		cout<<"1_CHOOSE PLAYER AND PLAY"<<endl;
		cout<<"2_ADD PLAYERS"<<endl;
		cout<<"3_DELET PLAYERS"<<endl;
		cin>>number_choosen;
		switch(number_choosen){
			case 1 :
				choose_players();
				menu();
				break;
			case 2 :
				short int plnum;
				cout<<"ENTER NUMBER OF PLAYERS :";
				cin>>plnum;
				for(int i = 0 ; i < plnum ; i++){
					cout<<"PLAYER NUMBER "<<i+number_of_players+1<<" NAME :";
					cin>>player_list[number_of_players+i].name;
					cout<<"ENTER THE COLOR YOU WANT : "<<endl;
					for(int j = 0 ; j<10 ; j++){
						change_color_rgb(colornumber1[j], colornumber2[j], colornumber3[j]);
						if(color_choosen[j]==1){
							cout<<j+1<<"_"<<color_names[j]<<"     CHOSEN !"<<endl;
						}
						else{
							cout<<j+1<<"_"<<color_names[j]<<endl;
						}
						reset_color();
					}
					cin>>player_list[number_of_players+1].color;
					while(color_choosen[player_list[number_of_players+1].color-1]==1){
						cout<<"THE COLOR "<<player_list[number_of_players+1].color<<" IS CHOOSEN ! ENTER AGAIN :";
						cin>>player_list[number_of_players+1].color;
					}
					while(player_list[number_of_players+1].color>10 || player_list[number_of_players+1].color<1){
						cout<<"ENTER NUMBER BETWEEN 1 AND 10 !"<<endl;
						cin>>player_list[number_of_players+1].color;
					}
					color_choosen[player_list[number_of_players+1].color-1]=1;
					num_to_color(player_list[number_of_players+1].color , player_list[i+number_of_players]);
					clear_screen();
				}
				number_of_players += plnum;
				break;
			case 3 :
				delet_player(player_list);
				break ;	
		}
	}
}

int main(){
	init_clui();
	clear_screen();
	cout<<"\n"<<"Welcome to snake game !"<<endl;
	while(!EXIT){
		switch(menu()){
			case '1' :
				starter();
				clear_screen();
				break ;
			case '2' :
				score_table();
				break ;
			case '3' :
				user_change();
				clear_screen();
				break ;
			case '4' :
				clear_screen();
				EXIT = true ;
		}
	}
    return 0 ;
}
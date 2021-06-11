#include <stdio.h>
#include <windows.h>
#include <conio.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ENTER 13

#define EMPTY 0
#define BALL 1
#define USER 2
#define SUCCESS  3
#define GOAL  4
#define WALL  5

int position_x;
int position_y;
int next_position_x;
int next_position_y;
int double_next_position_x;
int double_next_position_y;
int pre_position = EMPTY;

int moves = 0, score=0, request=0, end=0;

int map[10][10] = {
	5,5,5,5,5,5,5,5,5,5,
	5,0,5,4,5,0,0,0,0,5,
	5,0,5,0,5,0,0,0,0,5,
	5,0,5,0,5,5,5,5,5,5,
	5,5,5,1,0,1,4,0,0,5,
	5,4,0,1,2,1,5,5,5,5,
	5,5,5,5,5,0,5,0,0,5,
	5,0,0,0,5,0,5,0,0,5,
	5,0,0,0,5,4,5,0,0,5,
	5,5,5,5,5,5,5,5,5,5
};

void map_print() {
	score = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			switch (map[i][j]){
				case 0 :
					printf("  ");
					break;
				case 1 :
					printf("≠");
					break;
				case 2:
					printf("佻");
					position_x = i;
					position_y = j;
					break;
				case 3:
					printf("≒");
					score++;
					break;
				case 4:
					printf("∞");
					break;
				case 5:
					printf("十");
					break;
			}
		}
		printf("\n");
	}
}

char update_next_position(int key) {
	if (key == UP) {
		double_next_position_x = position_x - 2;
		double_next_position_y = position_y;

		next_position_x = position_x - 1;
		next_position_y = position_y;
	}
	if (key == DOWN) {
		double_next_position_x = position_x + 2;
		double_next_position_y = position_y;

		next_position_x = position_x + 1;
		next_position_y = position_y;
	}
	if (key == RIGHT) {
		double_next_position_y = position_y + 2;
		double_next_position_x = position_x;

		next_position_y = position_y + 1;
		next_position_x = position_x;
	}
	if (key == LEFT) {
		double_next_position_y = position_y - 2;
		double_next_position_x = position_x;

		next_position_y = position_y - 1;
		next_position_x = position_x;
	}
}

void simple_move_next() {
	moves++;
	map[position_x][position_y] = pre_position;
	pre_position = EMPTY;
	if (map[next_position_x][next_position_y] != BALL) {
		pre_position = map[next_position_x][next_position_y];
	}
	if (map[next_position_x][next_position_y] == SUCCESS) {
		pre_position = GOAL;
	}
	map[next_position_x][next_position_y] = USER;
}

void update_double_next( int state) {
	//update block type
	map[double_next_position_x][double_next_position_y] = state;
	simple_move_next();
}
int return_next_block() {
	//return block type
	return map[next_position_x][next_position_y];
}

int return_double_next_block() {
	//return block type
	return map[double_next_position_x][double_next_position_y];
}

void control_move() {
	if (return_next_block() == BALL || return_next_block() == SUCCESS) {
		if (return_double_next_block() == EMPTY) {
			update_double_next(BALL);
		}
		if (return_double_next_block() == GOAL) {
			update_double_next(SUCCESS);
		}
	}
	
	if (return_next_block() == EMPTY || return_next_block() == GOAL) {
		simple_move_next();
	}
}

void move() {
	int key;
	key = _getch();
	switch (key) {
		case LEFT:
			update_next_position(LEFT);
			control_move(LEFT);
			break;
		case RIGHT:
			update_next_position(RIGHT);
			control_move(RIGHT);
			break;
		case UP:
			update_next_position(UP);
			control_move(UP);
			break;
		case DOWN:
			update_next_position(DOWN);
			control_move(DOWN);
			break;
		case ENTER:
			end = 1;
			break;
	}
}

void set_start() {
	request = 0;
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			position_x = x;
			position_y = y;

			if (map[x][y] == GOAL) {
				request++;
			}
		}
	}
}

void printfMiddleLine(const char* ap_string, int space_count) {
	printf("早%-*s早\n", space_count, ap_string);
}

void main() {
	set_start();
	while (1) {
		map_print();
		printf("\nPRESS ENTER TO EXIT");
		printf("\nposition: %d  %d", position_x, position_y);
		printf("\nmoves: %d", moves);
		printf("\nscore: %d/%d", score,request);
		if (score == request || end) {
			break;
		}
		move();
		system("cls");
	}
	system("cls");
	
	int i;
	printf("忙");
	for (i = 0; i < 30; i++) printf("式");
	printf("忖\n");
	printfMiddleLine("", 30);
	printfMiddleLine("          GAME CLEAR", 30);
	printfMiddleLine("", 30);

	printf("戌");
	for (i = 0; i < 30; i++) printf("式");
	printf("戎\n");
}
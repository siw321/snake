#include "lib.h"
#include <Windows.h>
#include <stdio.h>
#include <string.h>

int width = 100;
int height = 52;
int glyph_size = 13;

int stop = 0;

struct snake
{
	int head[2];
	int tail[100][2];
	int len;
};

struct food
{
	int x;
	int y;
};

struct snake snake1;
struct food food1;

int create() {
	olc_fill(0, 0, width, height, '+', FG_RED);
	snake1.head[0] = width / 2;
	snake1.head[1] = height / 2;
	snake1.tail[0][0] = width / 2 + 1;
	snake1.tail[0][1] = height / 2;
	snake1.len = 2;
	food1.x = (rand() + 1) % (width - 1);
	food1.y = (rand() + 1) % (height - 1);
	return 1;
}

void eat(int pos[2])
{
	if (snake1.head[0] == food1.x && snake1.head[1] == food1.y)
	{
		snake1.len++;
		food1.x = (rand() + 1) % (width - 1);
		food1.y = (rand() + 1) % (height - 1);
	}
	return;
}

void check_col(int head[2], int tail[2]){
	if (head[0] == tail[0] && head[1] == tail[1])
	{
		stop = 1;
	}
	else if (head[0] == width - 1 || head[0] == 1 || head[1] == height - 1 || head[1] == 1)
	{
		stop = 1;
	}
	return;
}

void move(int dir)
{
	int pos[2];
	pos[0] = snake1.head[0];
	pos[1] = snake1.head[1];
	if (dir == 1)
	{
		snake1.head[1]--;
	}
	else if (dir == 2)
	{
		snake1.head[1]++;
	}
	else if (dir == 3)
	{
		snake1.head[0]++;
	}
	else if (dir == 4)
	{
		snake1.head[0]--;
	}
	int tmp;
	for (int i = 0; i < snake1.len - 1; i++)
	{
		tmp = snake1.tail[i][0];
		snake1.tail[i][0] = pos[0];
		pos[0] = tmp;
		tmp = snake1.tail[i][1];
		snake1.tail[i][1] = pos[1];
		pos[1] = tmp;
	}
	eat(pos);
	for (int i = 0; i < snake1.len - 1; i++)
	{
		check_col(snake1.head, snake1.tail[i]);
	}
	return;
}

void handle_input(float time_elapsed) {
	if (olc_get_key(0x1B).held) { // Esc
		stop = 1;
	}
	if (olc_get_key(VK_UP).pressed) {
		move(1);
	}
	else if (olc_get_key(VK_DOWN).pressed) {
		move(2);
	}
	else if (olc_get_key(VK_RIGHT).pressed) {
		move(3);
	}
	else if (olc_get_key(VK_LEFT).pressed) {
		move(4);
	}
}

int update(float time_elapsed) {
	handle_input(time_elapsed);
	if (stop) {
		olc_draw_string(width / 2 - 4, height / 2, "GAME OVER", FG_RED);
		return 0;
	}
	olc_fill(1, 1, width - 1, height - 1, ' ', FG_BLACK);
	olc_draw(snake1.head[0], snake1.head[1], '@', FG_BLUE);
	olc_draw(food1.x, food1.y, '$', FG_GREEN);
	for (int i = 0; i < snake1.len - 1; i++)
	{
		olc_draw(snake1.tail[i][0], snake1.tail[i][1], '#', FG_BLUE);
	}
	return 1;
}

int main() {
	if (olc_initialize(width, height, glyph_size, glyph_size) == 0) {
		fprintf(stderr, "Cannot initialize olc");
		return 0;
	}
	olc_register_create(&create);
	olc_register_update(&update);

	olc_start(); // block until update return 0
	olc_deinitialize();

	return 0;
}

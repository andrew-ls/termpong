/*
 * This file is part of termpong.
 *
 * Copyright (c) 2019 Andrew Steel <copyright@andrewsteel.net>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * The GNU General Public License Version 3 only:
 *
 * This is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License Version 3
 * as published by the Free Software Foundation.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this file. If not, see <https://www.gnu.org/licenses/>.
 */

#include <curses.h>

/*
 * Draws a rectangle to a curses window, using half-height characters to double
 * the vertical resolution.
 */
void draw_rect (WINDOW *window, int rect_y, int rect_x, int rect_height, int rect_width)
{
	#define HEIGHT_RATIO 2

	for (int x_index = 0; x_index < rect_width; x_index++) {
		for (int y_index = 0; y_index < rect_height; y_index++) {

			wmove(window, (rect_y + y_index) / HEIGHT_RATIO, rect_x + x_index);

			if ((rect_y + y_index) == 0 || ! ((rect_y + y_index) % HEIGHT_RATIO)) {
				if (rect_height - y_index >= HEIGHT_RATIO) {
					waddch(window, ':'); /* full */
					y_index++;
				}
				else {
					waddch(window, '`'); /* top-half */
				}
			}
			else {
				waddch(window, ','); /* bottom-half */
			}

		}
	}
}

int main (void)
{
	#define BALL_HEIGHT 1
	#define BALL_WIDTH 1
	#define FIELD_WIDTH 80
	#define FIELD_HEIGHT 50
	#define PADDLE_HEIGHT 8
	#define PADDLE_WIDTH 1

	double ball_coord_x = (FIELD_WIDTH / 2.0) - (BALL_WIDTH / 2.0);
	double ball_coord_y = (FIELD_HEIGHT / 2.0) - (BALL_HEIGHT / 2.0);
	double ball_speed_x = -20.0;
	double ball_speed_y = 0.0;

	double paddle_l_coord_x = 8.0;
	double paddle_l_coord_y = (FIELD_HEIGHT / 2.0) - (PADDLE_HEIGHT / 2.0);

	double paddle_r_coord_x = FIELD_WIDTH - PADDLE_WIDTH - 8.0;
	double paddle_r_coord_y = (FIELD_HEIGHT / 2.0) - (PADDLE_HEIGHT / 2.0);

	int score_1 = 0;
	int score_2 = 0;

	/*
	 * Initialize curses.
	 */
	initscr();
	noecho();
	curs_set(0);

	/*
	 * Create window to represent playing field.
	 */
	WINDOW *field = newwin(FIELD_HEIGHT, FIELD_WIDTH, 0, 0);

	/*
	 * Draw paddles and ball to playing field window.
	 */
	draw_rect(field,
		(int) paddle_l_coord_y,
		(int) paddle_l_coord_x,
		PADDLE_HEIGHT,
		PADDLE_WIDTH
	);
	draw_rect(field,
		(int) paddle_r_coord_y,
		(int) paddle_r_coord_x,
		PADDLE_HEIGHT,
		PADDLE_WIDTH
	);
	draw_rect(field,
		(int) ball_coord_y,
		(int) ball_coord_x,
		BALL_HEIGHT,
		BALL_WIDTH
	);

	/*
	 * Render playing field window, loop until SIGINT, then terminate curses.
	 */
	wrefresh(field);
	while (1) {}
	endwin();
}

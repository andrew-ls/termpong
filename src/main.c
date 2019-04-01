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
#include <locale.h>
#include <stdbool.h>
#include <stdlib.h>
#include "gfx/char.h"
#include "lib/math.h"
#include "mgr/input.h"
#include "mgr/time.h"

int main (void)
{
	#define BALL_HEIGHT 1
	#define BALL_WIDTH 1
	#define FIELD_WIDTH 80
	#define FIELD_HEIGHT 50
	#define PADDLE_FRICTION 40.0
	#define PADDLE_HEIGHT 8
	#define PADDLE_MOVESPEED 40.0
	#define PADDLE_WIDTH 1

	double ball_coord_x = (FIELD_WIDTH / 2.0) - (BALL_WIDTH / 2.0);
	double ball_coord_y = (FIELD_HEIGHT / 2.0) - (BALL_HEIGHT / 2.0);
	double ball_speed_x = -20.0;
	double ball_speed_y = 0.0;
	bool ball_passed_paddle = false;

	double paddle_l_coord_x = 8.0;
	double paddle_l_coord_y = (FIELD_HEIGHT / 2.0) - (PADDLE_HEIGHT / 2.0);
	double paddle_l_speed_y = 0.0;

	double paddle_r_coord_x = FIELD_WIDTH - PADDLE_WIDTH - 8.0;
	double paddle_r_coord_y = (FIELD_HEIGHT / 2.0) - (PADDLE_HEIGHT / 2.0);
	double paddle_r_speed_y = 0.0;

	int score_1 = 0;
	int score_2 = 0;

	/*
	 * Initialize curses.
	 */
	setlocale(LC_ALL, "C.UTF8");
	initscr();
	noecho();
	curs_set(0);
	cbreak(); /* Sets input mode to be raw with signals (e.g. SIGINT) */
	nodelay(stdscr, true); /* Makes `getch` non-blocking */
	keypad(stdscr, true); /* Enables keypad translation */
	meta(stdscr, true); /* Force 8 bits for input */

	/*
	 * Create window to represent playing field.
	 */
	WINDOW *field = newwin(FIELD_HEIGHT, FIELD_WIDTH, 0, 0);

	/*
	 * Loop game ticks until SIGINT, then terminate curses.
	 */
	while (1) {
		/*
		 * Poll current input state.
		 */
		input_clear();
		input_poll();
		if (input_find(KEY_F(1))) {
			endwin();
			exit(0);
		}

		/*
		 * Perform a game tick.
		 * The first game tick will have a time delta of 0.
		 */
		time_tick();

		/*
		 * Apply a speed to the right paddle with arrow key input.
		 */
		{
			bool input_down = input_find(KEY_DOWN);
			bool input_up = input_find(KEY_UP);
			if (input_down && !input_up) {
				paddle_r_speed_y = PADDLE_MOVESPEED;
			}
			else if (input_up && !input_down) {
				paddle_r_speed_y = -PADDLE_MOVESPEED;
			}
		}

		/*
		 * Move paddles, scaled by the time delta for this game tick.
		 * Additionally apply a frictional force to slow the paddle down.
		 */
		paddle_l_coord_y += paddle_l_speed_y * time_delta();
		paddle_r_coord_y += paddle_r_speed_y * time_delta();
		paddle_l_speed_y = APPROACH(
			paddle_l_speed_y,
			PADDLE_FRICTION * time_delta(),
			0.0
		);
		paddle_r_speed_y = APPROACH(
			paddle_r_speed_y,
			PADDLE_FRICTION * time_delta(),
			0.0
		);

		/*
		 * Move ball, scaled by the time delta for this game tick.
		 */
		ball_coord_x += ball_speed_x * time_delta();
		ball_coord_y += ball_speed_y * time_delta();

		/*
		 * Bounce the ball off the walls.
		 */
		if (ball_coord_y < 0) {
			/*
			 * The ball's movement beyond the field is added to the rebound.
			 */
			ball_coord_y = 0 - ball_coord_y;
			ball_speed_y *= -1;
		}
		else if (ball_coord_y + BALL_HEIGHT > FIELD_HEIGHT) {
			ball_coord_y = (FIELD_HEIGHT * 2) - ball_coord_y - BALL_HEIGHT;
			ball_speed_y *= -1;
		}

		/*
		 * Bounce the ball off the paddles.
		 */
		if (! ball_passed_paddle) {
			if (ball_coord_x < paddle_l_coord_x + PADDLE_WIDTH) {
				if (
					ball_coord_y > paddle_l_coord_y
					&& ball_coord_y + BALL_HEIGHT
						< paddle_l_coord_y + PADDLE_HEIGHT
				) {
					/*
					 * The ball's movement beyond the paddle is added to the
					 * rebound.
					 */
					ball_coord_x = (paddle_l_coord_x + PADDLE_WIDTH) * 2
						- ball_coord_x;
					ball_speed_x *= -1;
				}
				else {
					ball_passed_paddle = true;
				}
			}
			else if (ball_coord_x + BALL_WIDTH > paddle_r_coord_x) {
				if (
					ball_coord_y > paddle_r_coord_y
					&& ball_coord_y + BALL_HEIGHT
						< paddle_r_coord_y + PADDLE_HEIGHT
				) {
					ball_coord_x = (paddle_r_coord_x - BALL_WIDTH) * 2
						- ball_coord_x;
					ball_speed_x *= -1;
				}
				else {
					ball_passed_paddle = true;
				}
			}
		}

		/*
		 * Draw paddles and ball to playing field window.
		 */
		werase(field);
		char_drawrect(field,
			ROUND(paddle_l_coord_y),
			ROUND(paddle_l_coord_x),
			PADDLE_HEIGHT,
			PADDLE_WIDTH
		);
		char_drawrect(field,
			ROUND(paddle_r_coord_y),
			ROUND(paddle_r_coord_x),
			PADDLE_HEIGHT,
			PADDLE_WIDTH
		);
		char_drawrect(field,
			ROUND(ball_coord_y),
			ROUND(ball_coord_x),
			BALL_HEIGHT,
			BALL_WIDTH
		);
		wrefresh(field);
	}
	endwin();
}

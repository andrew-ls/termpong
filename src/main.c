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
#include "obj/kind/Ball.h"
#include "obj/kind/Field.h"
#include "obj/kind/Paddle.h"

void game_draw (void);
void game_exit (int status);
void game_init (void);
void game_round_new (void);
void game_tick (void);

Ball *ball;
bool collision_ball_passed_paddle;
Field *field;
Paddle *paddle_l;
Paddle *paddle_r;
unsigned int score_l = 0;
unsigned int score_r = 0;

void game_draw (void)
{
	werase(Field_getWindow(field));
	Field_drawScore(field, score_l, FIELD_SCORE_POS_L);
	Field_drawScore(field, score_r, FIELD_SCORE_POS_R);
	char_drawrect(Field_getWindow(field),
		ROUND(Paddle_getY(paddle_l)),
		ROUND(Paddle_getX(paddle_l)),
		(int) Paddle_getHeight(paddle_l),
		(int) Paddle_getWidth(paddle_l)
	);
	char_drawrect(Field_getWindow(field),
		ROUND(Paddle_getY(paddle_r)),
		ROUND(Paddle_getX(paddle_r)),
		(int) Paddle_getHeight(paddle_r),
		(int) Paddle_getWidth(paddle_r)
	);
	char_drawrect(Field_getWindow(field),
		ROUND(Ball_getY(ball)),
		ROUND(Ball_getX(ball)),
		(int) Ball_getHeight(ball),
		(int) Ball_getWidth(ball)
	);
	wrefresh(Field_getWindow(field));
}

void game_exit (int status)
{
	endwin();
	exit(status);
}

void game_init (void)
{
	/*
	 * Initialize curses.
	 */
	initscr();
	noecho();
	curs_set(0);
	cbreak(); /* Sets input mode to be raw with signals (e.g. SIGINT) */
	nodelay(stdscr, true); /* Makes `getch` non-blocking */
	keypad(stdscr, true); /* Enables keypad translation */
	meta(stdscr, true); /* Force 8 bits for input */

	field = Field__new();
	ball = Ball__new(field);
	paddle_l = Paddle__new(field);
	paddle_r = Paddle__new(field);
	score_l = 0;
	score_r = 0;

	game_round_new();
}

void game_round_new (void)
{
	collision_ball_passed_paddle = false;
	Ball_translocate(ball,
		(Field_getWidth(field) / 2.0) - (Ball_getWidth(ball) / 2.0),
		(Field_getHeight(field) / 2.0) - (Ball_getHeight(ball) / 2.0));
	Ball_propel(ball, -20.0, 0.0);
	Paddle_translocate(paddle_l,
		8.0,
		(Field_getHeight(field) / 2.0) - (Paddle_getHeight(paddle_l) / 2.0));
	Paddle_translocate(paddle_r,
		Field_getWidth(field) - Paddle_getWidth(paddle_r) - 8.0,
		(Field_getHeight(field) / 2.0) - (Paddle_getHeight(paddle_l) / 2.0));
}

void game_tick (void)
{
	input_clear();
	input_poll();
	if (input_find(KEY_F(1))) {
		game_exit(0);
	}
	time_tick(); /* The first time tick will have a delta of 0. */

	/*
	 * Apply a speed to the right paddle with arrow key input.
	 */
	{
		bool input_down = input_find(KEY_DOWN);
		bool input_up = input_find(KEY_UP);
		if (input_down && !input_up) {
			Paddle_move(paddle_r, PADDLE_DIR_DOWN);
		}
		else if (input_up && !input_down) {
			Paddle_move(paddle_r, PADDLE_DIR_UP);
		}
	}

	/*
	 * Move ball and paddles, scaled by the time delta for this game tick.
	 * Additionally apply a frictional force to slow the paddle down.
	 */
	Ball_translate(ball, time_delta());
	Paddle_translate(paddle_l, time_delta());
	Paddle_translate(paddle_r, time_delta());
	Paddle_applyFriction(paddle_l, PADDLE_FRICTION, time_delta());
	Paddle_applyFriction(paddle_r, PADDLE_FRICTION, time_delta());

	/*
	 * When the ball passes the field's left and right sides,
	 */
	if (Ball_getX(ball) < 0.0) {
		score_r += 1;
		game_round_new();
		return;
	}
	else if (Ball_getX(ball) + Ball_getWidth(ball) > Field_getWidth(field)) {
		score_l += 1;
		game_round_new();
		return;
	}

	/*_________________________________________________________________
	 /                                                                 \
	 |  Bounce the ball off the walls.                                 |
	 |  The ball's movement beyond the field is added to the rebound.  |
	 \__   ____________________________________________________________/
	    \*/
	if (Ball_getY(ball) < 0.0) {
		Ball_translocate(ball, Ball_getX(ball), 0 - Ball_getY(ball));
		Ball_propel(ball, Ball_getXSpeed(ball), -Ball_getYSpeed(ball));
	}
	else if (Ball_getY(ball) + Ball_getHeight(ball) > Field_getHeight(field)) {
		Ball_translocate(ball,
			Ball_getX(ball),
			(Field_getHeight(field) * 2)
				- Ball_getY(ball) - Ball_getHeight(ball));
		Ball_propel(ball, Ball_getXSpeed(ball), -Ball_getYSpeed(ball));
	}

	/*
	 * Bounce the ball off the paddles.
	 * The ball's movement beyond the paddle is added to the rebound.
	 */
	if (!collision_ball_passed_paddle) {
		if (Ball_getX(ball)
			< Paddle_getX(paddle_l) + Paddle_getWidth(paddle_l)
		) {
			if (
				Ball_getY(ball) > Paddle_getY(paddle_l)
				&& Ball_getY(ball) + Ball_getHeight(ball)
					< Paddle_getY(paddle_l) + Paddle_getHeight(paddle_l)
			) {
				Ball_translocate(ball,
					(Paddle_getX(paddle_l) + Paddle_getWidth(paddle_l)) * 2
						- Ball_getX(ball),
					Ball_getY(ball));
				Ball_propel(ball,
					-Ball_getXSpeed(ball),
					Ball_getYSpeed(ball));
			}
			else {
				collision_ball_passed_paddle = true;
			}
		}
		else if (Ball_getX(ball) + Ball_getWidth(ball)
			> Paddle_getX(paddle_r)
		) {
			if (
				Ball_getY(ball) > Paddle_getY(paddle_r)
				&& Ball_getY(ball) + Ball_getHeight(ball)
					< Paddle_getY(paddle_r) + Paddle_getHeight(paddle_r)
			) {
				Ball_translocate(ball,
					(Paddle_getX(paddle_r) - Ball_getWidth(ball)) * 2
						- Ball_getX(ball),
					Ball_getY(ball));
				Ball_propel(ball,
					-Ball_getXSpeed(ball),
					Ball_getYSpeed(ball));
			}
			else {
				collision_ball_passed_paddle = true;
			}
		}
	}
}

int main (void)
{
	setlocale(LC_ALL, "C.UTF8");
	game_init();
	while (1) {
		game_tick();
		game_draw();
	}
	game_exit(0);
}

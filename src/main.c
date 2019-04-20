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
void game_exit ();
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
		ROUND(Coord_getY(paddle_l->coord)),
		ROUND(Coord_getX(paddle_l->coord)),
		(int) Size_getHeight(paddle_l->size),
		(int) Size_getWidth(paddle_l->size)
	);
	char_drawrect(Field_getWindow(field),
		ROUND(Coord_getY(paddle_r->coord)),
		ROUND(Coord_getX(paddle_r->coord)),
		(int) Size_getHeight(paddle_r->size),
		(int) Size_getWidth(paddle_r->size)
	);
	char_drawrect(Field_getWindow(field),
		ROUND(Coord_getY(ball->coord)),
		ROUND(Coord_getX(ball->coord)),
		(int) Size_getHeight(ball->size),
		(int) Size_getWidth(ball->size)
	);
	wrefresh(Field_getWindow(field));
}

void game_exit (void)
{
	endwin();
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
	ball = Ball__new(field->size);
	paddle_l = Paddle__new(field->size);
	paddle_r = Paddle__new(field->size);
	score_l = 0;
	score_r = 0;

	game_round_new();
}

void game_round_new (void)
{
	collision_ball_passed_paddle = false;
	Coord_translocate(ball->coord,
		(Size_getWidth(field->size) / 2.0)
			- (Size_getWidth(ball->size) / 2.0),
		(Size_getHeight(field->size) / 2.0)
			- (Size_getHeight(ball->size) / 2.0));
	Speed_propel(ball->speed, -20.0, 0.0);
	Coord_translocate(paddle_l->coord,
		8.0,
		(Size_getHeight(field->size) / 2.0)
			- (Size_getHeight(paddle_l->size) / 2.0));
	Coord_translocate(paddle_r->coord,
		Size_getWidth(field->size) - Size_getWidth(paddle_r->size) - 8.0,
		(Size_getHeight(field->size) / 2.0)
			- (Size_getHeight(paddle_l->size) / 2.0));
}

void game_tick (void)
{
	input_clear();
	input_poll();
	if (input_find(KEY_F(1))) {
		exit(0);
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
	Speed_translate(ball->speed, time_delta());
	Speed_translate(paddle_l->speed, time_delta());
	Speed_translate(paddle_r->speed, time_delta());
	Paddle_applyFriction(paddle_l, PADDLE_FRICTION, time_delta());
	Paddle_applyFriction(paddle_r, PADDLE_FRICTION, time_delta());

	/*
	 * When the ball passes the field's left and right sides,
	 */
	if (Coord_getX(ball->coord) < 0.0) {
		score_r += 1;
		game_round_new();
		return;
	}
	else if (
		Coord_getX(ball->coord) + Size_getWidth(ball->size)
			> Size_getWidth(field->size)
	) {
		score_l += 1;
		game_round_new();
		return;
	}

	/*
	 * Bounce the ball off the walls.
	 * The ball's movement beyond the field is added to the rebound.
	 */
	if (Coord_getY(ball->coord) < 0.0) {
		Coord_translocate(ball->coord,
			Coord_getX(ball->coord),
			0 - Coord_getY(ball->coord));
		Speed_propel(ball->speed,
			Speed_getXSpeed(ball->speed),
			-Speed_getYSpeed(ball->speed));
	}
	else if (
		Coord_getY(ball->coord) + Size_getHeight(ball->size)
			> Size_getHeight(field->size)
	) {
		Coord_translocate(ball->coord,
			Coord_getX(ball->coord),
			(Size_getHeight(field->size) * 2)
				- Coord_getY(ball->coord) - Size_getHeight(ball->size));
		Speed_propel(ball->speed,
			Speed_getXSpeed(ball->speed),
			-Speed_getYSpeed(ball->speed));
	}

	/*
	 * Bounce the ball off the paddles.
	 * The ball's movement beyond the paddle is added to the rebound.
	 */
	if (!collision_ball_passed_paddle) {
		if (Coord_getX(ball->coord)
			< Coord_getX(paddle_l->coord) + Size_getWidth(paddle_l->size)
		) {
			if (
				Coord_getY(ball->coord) > Coord_getY(paddle_l->coord)
				&& Coord_getY(ball->coord) + Size_getHeight(ball->size)
					< Coord_getY(paddle_l->coord)
						+ Size_getHeight(paddle_l->size)
			) {
				Coord_translocate(ball->coord,
					(Coord_getX(paddle_l->coord)
						+ Size_getWidth(paddle_l->size))
						* 2 - Coord_getX(ball->coord),
					Coord_getY(ball->coord));
				Speed_propel(ball->speed,
					-Speed_getXSpeed(ball->speed),
					Speed_getYSpeed(ball->speed));
			}
			else {
				collision_ball_passed_paddle = true;
			}
		}
		else if (Coord_getX(ball->coord) + Size_getWidth(ball->size)
			> Coord_getX(paddle_r->coord)
		) {
			if (
				Coord_getY(ball->coord) > Coord_getY(paddle_r->coord)
				&& Coord_getY(ball->coord) + Size_getHeight(ball->size)
					< Coord_getY(paddle_r->coord)
						+ Size_getHeight(paddle_r->size)
			) {
				Coord_translocate(ball->coord,
					(Coord_getX(paddle_r->coord) - Size_getWidth(ball->size))
						* 2 - Coord_getX(ball->coord),
					Coord_getY(ball->coord));
				Speed_propel(ball->speed,
					-Speed_getXSpeed(ball->speed),
					Speed_getYSpeed(ball->speed));
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
	atexit(game_exit);
	while (1) {
		game_tick();
		game_draw();
	}
	exit(0);
}

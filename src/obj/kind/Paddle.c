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

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "lib/math.h"
#include "lib/stack.h"
#include "obj/ifix/Coord.h"
#include "obj/ifix/Size.h"
#include "obj/ifix/Speed.h"
#include "obj/kind/Field.h"

#include "./Paddle.h"

struct stack *Paddles = NULL;

struct Paddle {
	Coord *coord;
	Field *field;
	double momentum;
	Size *size;
	Speed *speed;
};
Paddle *Paddle__delete (Paddle *this)
{
	Coord__delete(this->coord);
	Size__delete(this->size);
	Speed__delete(this->speed);
	free(this);
	Paddles = stack_pop(stack_find(Paddles, this));
	return NULL;
}
Paddle *Paddle__new (Field *field)
{
	Paddle *this = malloc(sizeof(*this));
	if (this) {
		*this = (Paddle) {
			.coord = Coord__new(),
			.field = field,
			.momentum = 0.0,
			.size = Size__new(),
			.speed = Speed__new(),
		};
		Paddle_resize(this, PADDLE_SIZE_WIDTH, PADDLE_SIZE_HEIGHT);
		Paddles = stack_push(Paddles, this);
	}
	return this;
}

/* Interface: Coord */
inline double Paddle_getX (Paddle *this) { return Coord_getX(this->coord); }
inline double Paddle_getY (Paddle *this) { return Coord_getY(this->coord); }
inline void Paddle_shift (Paddle *this, double x, double y) { Coord_shift(this->coord, x, y); }
inline void Paddle_translocate (Paddle *this, double x, double y) { Coord_translocate(this->coord, x, y); }

/* Interface: Size */
inline double Paddle_getHeight (Paddle *this) { return Size_getHeight(this->size); }
inline double Paddle_getWidth (Paddle *this) { return Size_getWidth(this->size); }
inline void Paddle_resize (Paddle *this, double width, double height) { Size_resize(this->size, width, height); }

/* Interface: Speed */
inline void Paddle_accelerate (Paddle *this, double x, double y) { Speed_accelerate(this->speed, x, y); }
inline double Paddle_getXSpeed (Paddle *this) { return Speed_getXSpeed(this->speed); }
inline double Paddle_getYSpeed (Paddle *this) { return Speed_getYSpeed(this->speed); }
inline void Paddle_propel (Paddle *this, double x, double y) { Speed_propel(this->speed, x, y); }
void Paddle_translate (Paddle *this, double mult) {
	Speed_translate(this->speed, mult, this, Paddle_shift);

	/*
	 * Confine paddles to the bounds of their field.
	 */
	{
		bool blocked = false;
		double y = Paddle_getY(this);
		if (y < PADDLE_MARGIN) {
			Paddle_translocate(this, Paddle_getX(this), PADDLE_MARGIN);
			blocked = true;
		}
		else if (
			y + Paddle_getHeight(this)
				> Field_getHeight(this->field) - PADDLE_MARGIN
		) {
			Paddle_translocate(this,
				Paddle_getX(this),
				Field_getHeight(this->field) - PADDLE_MARGIN
					- Paddle_getHeight(this));
			blocked = true;
		}
		if (blocked) {
			Paddle_propel(this, 0.0, 0.0);
			this->momentum = 0.0;
		}
	}
}

void Paddle_applyFriction (Paddle *this, double friction, double mult)
{
	double force = friction * mult;
	if (this->momentum > 0.0) {
		this->momentum -= force;
		if (this->momentum < 0.0) {
			force = FABS(this->momentum);
			this->momentum = 0.0;
		}
		else {
			force = 0.0;
		}
		if (this->momentum > PADDLE_MOMENTUM_MAX) {
			this->momentum = PADDLE_MOMENTUM_MAX;
		}
	}
	if (force > 0.0) {
		Paddle_propel(this,
			0.0,
			APPROACH(Paddle_getYSpeed(this), force, 0.0));
	}
}

void Paddle_move (Paddle *this, int direction)
{
	double accel = PADDLE_MOVE_BASIC;
	double currspeed = Paddle_getYSpeed(this);
	double currspeed_abs = FABS(currspeed);
	direction = SGN(direction);
	if ((currspeed > 0.0) == (direction > 0.0)) {
		this->momentum += PADDLE_MOMENTUM_BASIC;
		if (currspeed_abs > PADDLE_MOVE_THRESHOLD_BOOST) {
			accel += PADDLE_MOVE_BOOST;
			this->momentum += PADDLE_MOMENTUM_BOOST;
		}
		if (this->momentum > PADDLE_MOMENTUM_MAX) {
			this->momentum = PADDLE_MOMENTUM_MAX;
		}
	}
	else if (currspeed_abs > PADDLE_MOVE_THRESHOLD_REVERSAL) {
		accel = currspeed_abs;
		this->momentum = 0.0;
	}
	Paddle_propel(this, 0.0,
		APPROACH(currspeed, accel, PADDLE_MOVE_MAX * direction));
}

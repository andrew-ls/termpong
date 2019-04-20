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
#include "obj/role/Coord.h"
#include "obj/role/Private.h"
#include "obj/role/Size.h"
#include "obj/role/Speed.h"

#include "./Paddle.h"
void Paddle_translate (Paddle *this, double x, double y);
void Paddle_translate_continuation (void *this, double x, double y);
struct private {
	Size *bounds;
	double momentum;
};

struct stack *Paddles = NULL;

Paddle *Paddle__delete (Paddle *this)
{
	Coord__delete(this->coord);
	Private__delete(this->private);
	Size__delete(this->size);
	Speed__delete(this->speed);
	free(this);
	Paddles = stack_pop(stack_find(Paddles, this));
	return NULL;
}

Paddle *Paddle__new (Size *bounds)
{
	Paddle *this = malloc(sizeof(*this));
	if (this) {
		*this = (Paddle) {
			.coord = Coord__new(this, (struct Coord__callbacks) {}),
			.private = Private__new(this, sizeof(struct private)),
			.size = Size__new(this, (struct Size__callbacks) {}),
			.speed = Speed__new(this, (struct Speed__callbacks) {
				.translate = Paddle_translate_continuation,
			}),
		};

		*((struct private *) (this->private)) = (struct private) {
			.bounds = bounds,
			.momentum = 0.0,
		};
		Size_resize(this->size, PADDLE_SIZE_WIDTH, PADDLE_SIZE_HEIGHT);
		Paddles = stack_push(Paddles, this);
	}
	return this;
}

void Paddle_applyFriction (Paddle *this, double friction, double mult)
{
	struct private *private = this->private;

	double force = friction * mult;
	if (private->momentum > 0.0) {
		private->momentum -= force;
		if (private->momentum < 0.0) {
			force = FABS(private->momentum);
			private->momentum = 0.0;
		}
		else {
			force = 0.0;
		}
		if (private->momentum > PADDLE_MOMENTUM_MAX) {
			private->momentum = PADDLE_MOMENTUM_MAX;
		}
	}
	if (force > 0.0) {
		Speed_propel(this->speed,
			0.0,
			APPROACH(Speed_getYSpeed(this->speed), force, 0.0));
	}
}

void Paddle_move (Paddle *this, int direction)
{
	struct private *private = this->private;

	double accel = PADDLE_MOVE_BASIC;
	double currspeed = Speed_getYSpeed(this->speed);
	double currspeed_abs = FABS(currspeed);
	direction = SGN(direction);
	if ((currspeed > 0.0) == (direction > 0.0)) {
		private->momentum += PADDLE_MOMENTUM_BASIC;
		if (currspeed_abs > PADDLE_MOVE_THRESHOLD_BOOST) {
			accel += PADDLE_MOVE_BOOST;
			private->momentum += PADDLE_MOMENTUM_BOOST;
		}
		if (private->momentum > PADDLE_MOMENTUM_MAX) {
			private->momentum = PADDLE_MOMENTUM_MAX;
		}
	}
	else if (currspeed_abs > PADDLE_MOVE_THRESHOLD_REVERSAL) {
		accel = currspeed_abs;
		private->momentum = 0.0;
	}
	Speed_propel(this->speed, 0.0,
		APPROACH(currspeed, accel, PADDLE_MOVE_MAX * direction));
}

void Paddle_translate (Paddle *this, double x, double y)
{
	Coord_shift(this->coord, x, y);

	/*
	 * Confine paddles to their bounds.
	 */
	{
		struct private *private = this->private;

		bool blocked = false;
		double y = Coord_getY(this->coord);
		if (y < PADDLE_MARGIN) {
			Coord_translocate(this->coord,
				Coord_getX(this->coord),
				PADDLE_MARGIN);
			blocked = true;
		}
		else if (
			y + Size_getHeight(this->size)
				> Size_getHeight(private->bounds) - PADDLE_MARGIN
		) {
			Coord_translocate(this->coord,
				Coord_getX(this->coord),
				Size_getHeight(private->bounds) - PADDLE_MARGIN
					- Size_getHeight(this->size));
			blocked = true;
		}
		if (blocked) {
			Speed_propel(this->speed, 0.0, 0.0);
			private->momentum = 0.0;
		}
	}
}
void Paddle_translate_continuation (void *this, double x, double y)
{
	Paddle_translate((Paddle *) this, x, y);
}

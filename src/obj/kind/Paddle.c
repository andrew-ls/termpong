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

#include <stdlib.h>

#include "../../lib/math.h"
#include "../ifix/Coord.h"
#include "../ifix/Size.h"
#include "../ifix/Speed.h"

#include "./Paddle.h"

struct Paddle {
	Coord *coord;
	Size *size;
	Speed *speed;
};
void Paddle__delete (Paddle *this)
{
	Coord__delete(this->coord);
	Size__delete(this->size);
	Speed__delete(this->speed);
	free(this);
	return;
}
Paddle *Paddle__new (void)
{
	Paddle *this = malloc(sizeof(*this));
	this->coord = Coord__new();
	this->size = Size__new();
	this->speed = Speed__new();
	Paddle_resize(this, PADDLE_SIZE_WIDTH, PADDLE_SIZE_HEIGHT);
	return this;
}

/* Interface: Coord */
double Paddle_getX (Paddle *this) { return Coord_getX(this->coord); }
double Paddle_getY (Paddle *this) { return Coord_getY(this->coord); }
void Paddle_shift (Paddle *this, double x, double y) { Coord_shift(this->coord, x, y); }
void Paddle_translocate (Paddle *this, double x, double y) { Coord_translocate(this->coord, x, y); }

/* Interface: Size */
double Paddle_getHeight (Paddle *this) { return Size_getHeight(this->size); }
double Paddle_getWidth (Paddle *this) { return Size_getWidth(this->size); }
void Paddle_resize (Paddle *this, double width, double height) { Size_resize(this->size, width, height); }

/* Interface: Speed */
void Paddle_accelerate (Paddle *this, double x, double y) { Speed_accelerate(this->speed, x, y); }
double Paddle_getXSpeed (Paddle *this) { return Speed_getXSpeed(this->speed); }
double Paddle_getYSpeed (Paddle *this) { return Speed_getYSpeed(this->speed); }
void Paddle_propel (Paddle *this, double x, double y) { Speed_propel(this->speed, x, y); }
void Paddle_translate (Paddle *this, double mult) { Speed_translate(this->speed, mult, this, Paddle_shift); }

void Paddle_applyFriction (Paddle *this, double friction, double mult)
{
	Paddle_propel(this,
		0.0,
		APPROACH(Paddle_getYSpeed(this), friction * mult, 0.0));
}

void Paddle_move (Paddle *this, int direction)
{
	if (direction < 0) {
		Paddle_propel(this, 0.0, -PADDLE_MOVESPEED);
	}
	else {
		Paddle_propel(this, 0.0, PADDLE_MOVESPEED);
	}
}

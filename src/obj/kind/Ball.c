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

#include <stddef.h>
#include <stdlib.h>

#include "../ifix/Coord.h"
#include "../ifix/Size.h"
#include "../ifix/Speed.h"
#include "obj/kind/Field.h"

#include "./Ball.h"

struct Ball {
	Coord *coord;
	Field *field;
	Size *size;
	Speed *speed;
};
Ball *Ball__delete (Ball *this)
{
	Coord__delete(this->coord);
	Size__delete(this->size);
	Speed__delete(this->speed);
	free(this);
	return NULL;
}
Ball *Ball__new (Field *field)
{
	Ball *this = malloc(sizeof(*this));
	if (this) {
		*this = (Ball) {
			.coord = Coord__new(),
			.field = field,
			.size = Size__new(),
			.speed = Speed__new(),
		};
		Ball_resize(this, BALL_SIZE_WIDTH, BALL_SIZE_HEIGHT);
	}
	return this;
}

/* Interface: Coord */
double Ball_getX (Ball *this) { return Coord_getX(this->coord); }
double Ball_getY (Ball *this) { return Coord_getY(this->coord); }
void Ball_shift (Ball *this, double x, double y) { Coord_shift(this->coord, x, y); }
void Ball_translocate (Ball *this, double x, double y) { Coord_translocate(this->coord, x, y); }

/* Interface: Size */
double Ball_getHeight (Ball *this) { return Size_getHeight(this->size); }
double Ball_getWidth (Ball *this) { return Size_getWidth(this->size); }
void Ball_resize (Ball *this, double width, double height) { Size_resize(this->size, width, height); }

/* Interface: Speed */
void Ball_accelerate (Ball *this, double x, double y) { Speed_accelerate(this->speed, x, y); }
double Ball_getXSpeed (Ball *this) { return Speed_getXSpeed(this->speed); }
double Ball_getYSpeed (Ball *this) { return Speed_getYSpeed(this->speed); }
void Ball_propel (Ball *this, double x, double y) { Speed_propel(this->speed, x, y); }
void Ball_translate (Ball *this, double mult) { Speed_translate(this->speed, mult, this, Ball_shift); }

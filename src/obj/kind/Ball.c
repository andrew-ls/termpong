/*
 * This file is part of termpong.
 *
 * Copyright (c) 2019,2022 Andrew Steel <copyright@andrewsteel.net>
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
#include "lib/stack.h"
#include "obj/role/Coord.h"
#include "obj/role/Private.h"
#include "obj/role/Size.h"
#include "obj/role/Speed.h"
#include "obj/kind/Field.h"

#include "./Ball.h"
void Ball_translate (Ball *this, double x, double y);
struct private {
	Size *bounds;
};
static void Speed_callback_translate (void *assignee, double x, double y);

struct stack *Balls = NULL;

void Ball__delete (Ball *this)
{
	Coord__delete(this->coord);
	Private__delete(this->private);
	Size__delete(this->size);
	Speed__delete(this->speed);
	Balls = stack_pop(stack_find(Balls, this));
	free(this);
}

Ball *Ball__new (Size *bounds)
{
	Ball *this = malloc(sizeof(*this));
	if (this) {
		*this = (Ball) {
			.coord = Coord__new(this, (struct Coord__callbacks) {}),
			.private = Private__new(this, sizeof(struct private)),
			.size = Size__new(this, (struct Size__callbacks) {}),
			.speed = Speed__new(this, (struct Speed__callbacks) {
				.translate = Speed_callback_translate,
			}),
		};

		*((struct private *) (this->private)) = (struct private) {
			.bounds = bounds,
		};
		Size_resize(this->size, BALL_SIZE_WIDTH, BALL_SIZE_HEIGHT);
		Balls = stack_push(Balls, this);

		return this;
	}

	return NULL;
}

void Ball_translate (Ball *assignee, double x, double y)
{
	Ball *this = assignee;
	Coord_shift(this->coord, x, y);
}

static void Speed_callback_translate (void *assignee, double x, double y)
{
	Ball_translate((Ball *) assignee, x, y);
}

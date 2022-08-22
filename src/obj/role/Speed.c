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

#include "./Speed.h"
struct Speed {
	void *assignee;
	struct Speed__callbacks callbacks;
	double x;
	double y;
};

struct stack *Speeds = NULL;

void Speed__delete (Speed *this)
{
	Speeds = stack_pop(stack_find(Speeds, this));
	free(this);
}

Speed *Speed__new (void *assignee, struct Speed__callbacks callbacks)
{
	Speed *this = malloc(sizeof(*this));
	if (this) {
		*this = (Speed) {
			.assignee = assignee,
			.callbacks = callbacks,
			.x = 0.0,
			.y = 0.0,
		};
		Speeds = stack_push(Speeds, this);

		return this;
	}

	return NULL;
}

void Speed_accelerate (Speed *this, double x, double y)
{
	this->x += x;
	this->y += y;
}

double Speed_getXSpeed (Speed *this)
{
	return this->x;
}

double Speed_getYSpeed (Speed *this)
{
	return this->y;
}

void Speed_propel (Speed *this, double x, double y)
{
	this->x = x;
	this->y = y;
}

void Speed_translate (Speed *this, double mult)
{
	if (this->callbacks.translate) {
		this->callbacks.translate(this->assignee,
			this->x * mult,
			this->y * mult);
	}
}

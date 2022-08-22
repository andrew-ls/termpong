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

#include "./Size.h"
struct Size {
	void *assignee;
	struct Size__callbacks callbacks;
	double height;
	double width;
};

struct stack *Sizes = NULL;

void Size__delete (Size *this)
{
	Sizes = stack_pop(stack_find(Sizes, this));
	free(this);
}

Size *Size__new (void *assignee, struct Size__callbacks callbacks)
{
	Size *this = malloc(sizeof(*this));
	if (this) {
		*this = (Size) {
			.assignee = assignee,
			.callbacks = callbacks,
			.height = 0.0,
			.width = 0.0,
		};
		Sizes = stack_push(Sizes, this);

		return this;
	}

	return NULL;
}

double Size_getHeight (Size *this)
{
	return this->height;
}

double Size_getWidth (Size *this)
{
	return this->width;
}

void Size_resize (Size *this, double width, double height)
{
	this->width = width;
	this->height = height;
}

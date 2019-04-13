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

#include "./Size.h"

struct Size {
	double height;
	double width;
};
Size *Size__delete (Size *this)
{
	free(this);
	return NULL;
}
Size *Size__new (void)
{
	Size *this = malloc(sizeof(*this));
	if (this) {
		*this = (Size) {
			.height = 0.0,
			.width = 0.0,
		};
	}
	return this;
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

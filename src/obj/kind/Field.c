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
#include <stddef.h>
#include <stdlib.h>
#include "obj/ifix/Size.h"

#include "./Field.h"

struct Field {
	Size *size;
	WINDOW *window;
};
Field *Field__delete (Field *this)
{
	Size__delete(this->size);
	delwin(this->window);
	free(this);
	return NULL;
}
Field *Field__new (void)
{
	Field *this = malloc(sizeof(*this));
	this->size = Size__new();
	this->window = NULL;
	Field_resize(this, (int) FIELD_SIZE_WIDTH, FIELD_SIZE_HEIGHT);
	return this;
}

/* Interface: Size */
double Field_getHeight (Field *this) { return Size_getHeight(this->size); }
double Field_getWidth (Field *this) { return Size_getWidth(this->size); }
void Field_resize (Field *this, double width, double height) {
	delwin(this->window);
	this->window = newwin((int) height, (int) width, 0, 0);
	Size_resize(this->size, width, height);
}

WINDOW *Field_getWindow (Field *this)
{
	return this->window;
}

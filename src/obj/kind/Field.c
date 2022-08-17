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

#include <curses.h>
#include <stddef.h>
#include <stdlib.h>
#include "gfx/char.h"
#include "lib/stack.h"
#include "obj/role/Private.h"
#include "obj/role/Size.h"

#include "./Field.h"
void Field_resize (Field *this, double width, double height);
struct private {
	WINDOW *window;
};

struct stack *Fields = NULL;

Field *Field__delete (Field *this)
{
	Private__delete(this->private);
	Size__delete(this->size);
	delwin(((struct private *) (this->private))->window);
	Fields = stack_pop(stack_find(Fields, this));
	free(this);
	return NULL;
}

Field *Field__new (void)
{
	Field *this = malloc(sizeof(*this));
	if (this) {
		*this = (Field) {
			.private = Private__new(this, sizeof(struct private)),
			.size = Size__new(this, (struct Size__callbacks) {}),
		};

		*((struct private *) (this->private)) = (struct private) {
			.window = NULL,
		};
		Field_resize(this, FIELD_SIZE_WIDTH, FIELD_SIZE_HEIGHT);
		Fields = stack_push(Fields, this);

		return this;
	}

	return NULL;
}

void Field_drawScore (Field *this, unsigned int score, int position)
{
	int len = snprintf(NULL, 0, "%u", score);
	char *str = malloc(len + 1);
	int pos_x = (position == FIELD_SCORE_POS_L)
		? 2
		: (int) Size_getWidth(this->size) - len - 2;
	int pos_y = 1;
	snprintf(str, len + 1, "%u", score);
	char_drawstr(Field_getWindow(this), pos_y, pos_x, str);
	free(str);
}

WINDOW *Field_getWindow (Field *this)
{
	return ((struct private *) (this->private))->window;
}

void Field_resize (Field *this, double width, double height) {
	struct private *private = this->private;
	delwin(private->window);
	private->window = newwin((int) height, (int) width, 0, 0);
	Size_resize(this->size, width, height);
}

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

#ifndef INCLUDE_OBJ_KIND_FIELD_H
#define INCLUDE_OBJ_KIND_FIELD_H

#include <curses.h>
#include "lib/stack.h"
#include "obj/role/Private.h"
#include "obj/role/Size.h"

#define FIELD_SIZE_HEIGHT 50.0
#define FIELD_SIZE_WIDTH 80.0

enum {
	FIELD_SCORE_POS_L,
	FIELD_SCORE_POS_R,
};

/*
 * Instances.
 */
extern struct stack *Fields;

/*
 * Object.
 */
struct Field {
	Private *private;
	Size *size;
};
typedef struct Field Field;

/*
 * Destructor.
 */
void Field__delete (Field *this);

/*
 * Constructor.
 */
Field *Field__new (void);

/*
 * Draws a score to the field in one of two positions defined by
 * `FIELD_SCORE_POS_*`.
 */
void Field_drawScore (Field *this, unsigned int score, int position);

/*
 * Returns the curses window the field is representing.
 */
WINDOW *Field_getWindow (Field *this);

#endif

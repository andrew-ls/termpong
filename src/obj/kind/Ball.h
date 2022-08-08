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

#ifndef INCLUDE_OBJ_KIND_BALL_H
#define INCLUDE_OBJ_KIND_BALL_H

#include "lib/stack.h"
#include "obj/role/Coord.h"
#include "obj/role/Private.h"
#include "obj/role/Size.h"
#include "obj/role/Speed.h"

#define BALL_SIZE_HEIGHT 1.0
#define BALL_SIZE_WIDTH 1.0

/*
 * Instances.
 */
extern struct stack *Balls;

/*
 * Object.
 */
struct Ball {
	Coord *coord;
	Private *private;
	Size *size;
	Speed *speed;
};
typedef struct Ball Ball;

/*
 * Destructor.
 */
Ball *Ball__delete (Ball *this);

/*
 * Constructor.
 */
Ball *Ball__new (Size *bounds);

#endif

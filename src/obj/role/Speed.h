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

#ifndef INCLUDE_OBJ_ROLE_SPEED_H
#define INCLUDE_OBJ_ROLE_SPEED_H

#include "lib/stack.h"

/*
 * Instances.
 */
extern struct stack *Speeds;

/*
 * Type.
 */
typedef struct Speed Speed;

/*
 * Callbacks.
 */
struct Speed__callbacks {
	void (*translate)(void *assignee, double x, double y);
};

/*
 * Destructor.
 */
void Speed__delete (Speed *this);

/*
 * Constructor.
 */
Speed *Speed__new (void *assignee, struct Speed__callbacks callbacks);

/*
 * Adds to the current speed.
 */
void Speed_accelerate (Speed *this, double x, double y);

/*
 * Returns the current X speed.
 */
double Speed_getXSpeed (Speed *this);

/*
 * Returns the current Y speed.
 */
double Speed_getYSpeed (Speed *this);

/*
 * Applies absolute speed values.
 */
void Speed_propel (Speed *this, double x, double y);

/*
 * Translates the current X and Y speeds (multiplied) to relative X and Y
 * coordinates, applying them to the `translate` callback.
 */
void Speed_translate (Speed *this, double mult);

#endif

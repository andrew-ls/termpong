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

#ifndef INCLUDE_OBJ_ROLE_SIZE_H
#define INCLUDE_OBJ_ROLE_SIZE_H

#include "lib/stack.h"

/*
 * Instances.
 */
struct stack *Sizes;

/*
 * Type.
 */
typedef struct Size Size;

/*
 * Callbacks.
 */
struct Size__callbacks {};

/*
 * Destructor.
 */
Size *Size__delete (Size *this);

/*
 * Constructor.
 */
Size *Size__new (void *assignee, struct Size__callbacks callbacks);

/*
 * Returns the current height.
 */
double Size_getHeight (Size *this);

/*
 * Returns the current width.
 */
double Size_getWidth (Size *this);

/*
 * Resizes.
 */
void Size_resize (Size *this, double width, double height);

#endif

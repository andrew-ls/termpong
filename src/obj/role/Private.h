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

#ifndef INCLUDE_OBJ_ROLE_PRIVATE_H
#define INCLUDE_OBJ_ROLE_PRIVATE_H

/*
 * A role for private storage unique to the assignee.
 * The Private role is special, in that the assignee defines and manages the
 * data pointed to: this should be a file scope struct, also named `private`.
 * To access the members within this struct, the Private role pointer must be
 * cast to a struct pointer, e.g.: ((struct private *) (this->private))->member
 * Alternatively, assign a variable: struct private *private = this->private
 */

#include <stddef.h>
#include "lib/stack.h"

/*
 * Type.
 */
typedef void Private;

/*
 * Destructor.
 */
Private *Private__delete (Private *this);

/*
 * Constructor.
 * This will allocate memory for the assignee's private storage struct;
 * the `size` parameter refers to the size of this (in bytes).
 */
Private *Private__new (void *assignee, size_t size);

#endif

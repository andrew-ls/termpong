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

#ifndef INCLUDE_OBJ_IFIX_SIZE_H
#define INCLUDE_OBJ_IFIX_SIZE_H

typedef struct Size Size;
Size *Size__delete (Size *this);
Size *Size__new (void);

/*
 * Implementation:
 * double ?_getHeight (? *this);
 *
 * Returns the current height.
 */
double Size_getHeight (Size *this);

/*
 * Implementation:
 * double ?_getWidth (? *this);
 *
 * Returns the current width.
 */
double Size_getWidth (Size *this);

/*
 * Implementation:
 * void ?_resize (? *this, double width, double height);
 *
 * Resizes.
 */
void Size_resize (Size *this, double width, double height);

#endif

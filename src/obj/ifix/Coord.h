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

#ifndef INCLUDE_OBJ_IFIX_COORD_H
#define INCLUDE_OBJ_IFIX_COORD_H

#include "lib/stack.h"

/* Instances */
struct stack *Coords;

/* Base */
typedef struct Coord Coord;
Coord *Coord__delete (Coord *this);
Coord *Coord__new (void);

/*
 * Implementation:
 * double ?_getX (? *this);
 *
 * Get the current X coordinate.
 */
double Coord_getX (Coord *this);

/*
 * Implementation:
 * double ?_getY (? *this);
 *
 * Get the current Y coordinate.
 */
double Coord_getY (Coord *this);

/*
 * Implementation:
 * void ?_shift (? *this, double x, double y);
 *
 * Repositions relatively.
 */
void Coord_shift (Coord *this, double x, double y);

/*
 * Implementation:
 * void ?_translocate (? *this, double x, double y);
 *
 * Repositions absolutely.
 */
void Coord_translocate (Coord *this, double x, double y);

#endif

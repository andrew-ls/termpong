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

#ifndef INCLUDE_OBJ_KIND_BALL_H
#define INCLUDE_OBJ_KIND_BALL_H

#define BALL_SIZE_HEIGHT 1.0
#define BALL_SIZE_WIDTH 1.0

typedef struct Ball Ball;
Ball *Ball__delete (Ball *this);
Ball *Ball__new (void);

/* Interface: Coord */
double Ball_getX (Ball *this);
double Ball_getY (Ball *this);
void Ball_shift (Ball *this, double x, double y);
void Ball_translocate (Ball *this, double x, double y);

/* Interface: Size */
double Ball_getHeight (Ball *this);
double Ball_getWidth (Ball *this);
void Ball_resize (Ball *this, double width, double height);

/* Interface: Speed */
void Ball_accelerate (Ball *this, double x, double y);
double Ball_getXSpeed (Ball *this);
double Ball_getYSpeed (Ball *this);
void Ball_propel (Ball *this, double x, double y);
void Ball_translate (Ball *this, double mult);

#endif

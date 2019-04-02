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

#ifndef INCLUDE_OBJ_IFIX_SPEED_H
#define INCLUDE_OBJ_IFIX_SPEED_H

typedef struct Speed Speed;
void Speed__delete (Speed *this);
Speed *Speed__new (void);

/*
 * Implementation:
 * void ?_accelerate (? *this, double x, double y);
 *
 * Adds to the current speed.
 */
void Speed_accelerate (Speed *this, double x, double y);

/*
 * Implementation:
 * double ?_getXSpeed (? *this);
 *
 * Returns the current X speed.
 */
double Speed_getXSpeed (Speed *this);

/*
 * Implementation:
 * double ?_getYSpeed (? *this);
 *
 * Returns the current Y speed.
 */
double Speed_getYSpeed (Speed *this);

/*
 * Implementation:
 * void ?_propel (? *this, double x, double y);
 *
 * Applies absolute speed values.
 */
void Speed_propel (Speed *this, double x, double y);

/*
 * Implementation:
 * void ?_translate (? *this, double mult);
 *
 * Translates the current X and Y speeds (multiplied) to relative X and Y
 * coordinates, applied to a translator instance using a translation function.
 */
void Speed_translate (Speed *this,
	double mult,
	void *translator,
	void (*translation)());

#endif

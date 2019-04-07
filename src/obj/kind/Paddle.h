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

#ifndef INCLUDE_OBJ_KIND_PADDLE_H
#define INCLUDE_OBJ_KIND_PADDLE_H

#define PADDLE_DIR_DOWN 1
#define PADDLE_DIR_UP -1
#define PADDLE_FRICTION 30.0
#define PADDLE_MOMENTUM_BASIC 2.5
#define PADDLE_MOMENTUM_BOOST 5.0
#define PADDLE_MOMENTUM_MAX 7.5
#define PADDLE_MOVE_BASIC 15.0
#define PADDLE_MOVE_BOOST 5.0
#define PADDLE_MOVE_MAX 50.0
#define PADDLE_MOVE_THRESHOLD_BOOST 10.0
#define PADDLE_MOVE_THRESHOLD_REVERSAL 2.0
#define PADDLE_SIZE_HEIGHT 8.0
#define PADDLE_SIZE_WIDTH 1.0

typedef struct Paddle Paddle;
void Paddle__delete (Paddle *this);
Paddle *Paddle__new (void);

/* Interface: Coord */
double Paddle_getX (Paddle *this);
double Paddle_getY (Paddle *this);
void Paddle_shift (Paddle *this, double x, double y);
void Paddle_translocate (Paddle *this, double x, double y);

/* Interface: Size */
double Paddle_getHeight (Paddle *this);
double Paddle_getWidth (Paddle *this);
void Paddle_resize (Paddle *this, double width, double height);

/* Interface: Speed */
void Paddle_accelerate (Paddle *this, double x, double y);
double Paddle_getXSpeed (Paddle *this);
double Paddle_getYSpeed (Paddle *this);
void Paddle_propel (Paddle *this, double x, double y);
void Paddle_translate (Paddle *this, double mult);

/*
 * Reduces the current speed.
 */
void Paddle_applyFriction (Paddle *this, double friction, double mult);

/*
 * Move up (-1) or down (1).
 */
void Paddle_move (Paddle *this, int direction);

#endif

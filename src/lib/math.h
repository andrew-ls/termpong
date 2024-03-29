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

#ifndef INCLUDE_LIB_MATH_H
#define INCLUDE_LIB_MATH_H

#include <math.h>
#include <stdlib.h>

/*
 * Returns the absolute value of an integer.
 */
#define ABS(value) abs(value)

/*
 * Converges an initial value towards a limit by a certain amount. The result
 * will not exceed the bound of the limit in the direction of the convergence.
 */
#define APPROACH(initial, delta, limit) \
	((initial) < (limit)) \
		? FMIN(((initial) + (delta)), (limit)) \
		: FMAX(((initial) - (delta)), (limit))

/*
 * Returns the absolute value of a double.
 */
#define FABS(value) fabs(value)

/*
 * Returns the greatest integer that is not greater than x.
 */
#define FLOOR(x) floor(x)

/*
 * Returns the largest of two numbers.
 */
#define FMAX(x, y) fmax((x), (y))

/*
 * Returns the smallest of two numbers.
 */
#define FMIN(x, y) fmin((x), (y))

/*
 * Returns the common logarithm of a double.
 */
#define LG(x) log10(x)

/*
 * Round up or down to the nearest integral number.
 */
#define ROUND(x) round(x)

/*
 * Get the sign of a number.
 */
#define SGN(x) copysign(1.0, (x))

#endif

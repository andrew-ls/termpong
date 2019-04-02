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

#include <stdlib.h>

#include "./Coord.h"

struct Coord {
	double x;
	double y;
};
void Coord__delete (Coord *this)
{
	free(this);
	return;
}
Coord *Coord__new (void)
{
	Coord *this = malloc(sizeof(*this));
	this->x = 0.0;
	this->y = 0.0;
	return this;
}

double Coord_getX (Coord *this)
{
	return this->x;
}

double Coord_getY (Coord *this)
{
	return this->y;
}

void Coord_shift (Coord *this, double x, double y)
{
	this->x += x;
	this->y += y;
}

void Coord_translocate (Coord *this, double x, double y)
{
	this->x = x;
	this->y = y;
}

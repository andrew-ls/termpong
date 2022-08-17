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

#include <stddef.h>
#include <stdlib.h>
#include "lib/stack.h"

#include "./Private.h"

struct stack *Privates = NULL;

Private *Private__delete (Private *this)
{
	Privates = stack_pop(stack_find(Privates, this));
	free(this);
	return NULL;
}

Private *Private__new (void *parent, size_t size)
{
	Private *this = malloc(size);
	if (this) {
		Privates = stack_push(Privates, this);

		return this;
	}

	return NULL;
}

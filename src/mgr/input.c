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

#include <curses.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "lib/stack.h"
#include "lib/util.h"

#include "./input.h"
struct stack *input_state;

void input_clear (void)
{
	while (input_state) {
		free(input_state->body);
		input_state = stack_pop(input_state);
	}
}

bool input_find (int input)
{
	return stack_existsval(input_state, &input, iequals);
}

void input_poll (void)
{
	int ch;
	while ((ch = getch()) != ERR) {
		int *ch_p = malloc(sizeof(ch));
		if (ch_p) {
			*ch_p = ch;
			input_state = stack_push(input_state, ch_p);
		}
	}
}

/*
 * The current frame's list of inputs.
 */
struct stack *input_state = NULL;

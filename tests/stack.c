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

#include <stddef.h>
#include <stdio.h>
#include "lib/stack.h"

/*
 * Expected output:
 * 1
 * 3
 * 3
 * 7
 */
int main (void)
{
	int int_1 = 1;
	int int_3 = 3;
	int int_7 = 7;
	struct stack *teststack;
	teststack = stack_push(NULL, &int_7);
	teststack = stack_push(teststack, &int_3);
	teststack = stack_push(teststack, &int_3);
	teststack = stack_push(teststack, &int_1);
	for (; teststack != NULL; teststack = stack_pop(teststack) ) {
		printf("%i\n", *((int *) (teststack->body)));
	}
}

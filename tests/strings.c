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

#include <stdio.h>
#include "lib/strings.h"

/*
 * Expected output:
 * 1
 * 1
 * 9
 * 10
 * 10
 * 10
 */
void main (void)
{
	printf("%i\n", digits(0));
	printf("%i\n", digits(1));
	printf("%i\n", digits(999999999));
	printf("%i\n", digits(3294967296));
	printf("%i\n", digits(3294967297));
	printf("%i\n", digits(4294967295));
}

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

void draw_rect (WINDOW *, int, int, int, int);

/*
 * Draws a rectangle to a curses window, using half-height characters to double
 * the vertical resolution.
 */
void draw_rect (
	WINDOW *window,
	int rect_y,
	int rect_x,
	int rect_height,
	int rect_width
)
{
	#define HEIGHT_RATIO 2

	for (int x_index = 0; x_index < rect_width; x_index++) {
		for (int y_index = 0; y_index < rect_height; y_index++) {

			wmove(window, (rect_y + y_index) / HEIGHT_RATIO, rect_x + x_index);

			if (
				(rect_y + y_index) == 0
				|| ! ((rect_y + y_index) % HEIGHT_RATIO)
			) {
				if (rect_height - y_index >= HEIGHT_RATIO) {
					waddch(window, ':'); /* full */
					y_index++;
				}
				else {
					waddch(window, '`'); /* top-half */
				}
			}
			else {
				waddch(window, ','); /* bottom-half */
			}

		}
	}
}

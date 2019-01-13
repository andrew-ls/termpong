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

int main (void)
{
	#define BALL_HEIGHT 1
	#define BALL_WIDTH 1
	#define FIELD_WIDTH 80
	#define FIELD_HEIGHT 50
	#define PADDLE_HEIGHT 8
	#define PADDLE_WIDTH 1

	double ball_coord_x = (FIELD_WIDTH / 2.0) - (BALL_WIDTH / 2.0);
	double ball_coord_y = (FIELD_HEIGHT / 2.0) - (BALL_HEIGHT / 2.0);
	double ball_speed_x = -20.0;
	double ball_speed_y = 0.0;

	double paddle_l_coord_x = 8.0;
	double paddle_l_coord_y = (FIELD_HEIGHT / 2.0) - (PADDLE_HEIGHT / 2.0);

	double paddle_r_coord_x = FIELD_WIDTH - PADDLE_WIDTH - 8.0;
	double paddle_r_coord_y = (FIELD_HEIGHT / 2.0) - (PADDLE_HEIGHT / 2.0);

	int score_1 = 0;
	int score_2 = 0;

	printf("%s: %f\n%s: %f\n%s: %f\n%s: %f\n%s: %f\n%s: %f\n%s: %f\n%s: %f\n%s: %i\n%s: %i\n",
		"ball_coord_x", ball_coord_x,
		"ball_coord_y", ball_coord_y,
		"ball_speed_x", ball_speed_x,
		"ball_speed_y", ball_speed_y,
		"paddle_l_coord_x", paddle_l_coord_x,
		"paddle_l_coord_y", paddle_l_coord_y,
		"paddle_r_coord_x", paddle_r_coord_x,
		"paddle_r_coord_y", paddle_r_coord_y,
		"score_1", score_1,
		"score_2", score_2
	);
}

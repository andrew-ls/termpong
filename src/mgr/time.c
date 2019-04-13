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

/*
 * Enable POSIX 2008 features.
 * (from <time.h>: struct timespec, clock_* functions, ...)
 */
#define _XOPEN_SOURCE 700

#include <time.h>

#include "./time.h"
struct timespec currtime;
double dt;
struct timespec timespec_compare (struct timespec *, struct timespec *);

#define NANOSECOND_AS_SECOND 1.0 / 1000000000
#define NANOSECONDS_INA_SECOND 1000000000

/*
 * Stores the current time, as of the last tick.
 */
struct timespec currtime = {
	.tv_sec = 0,
	.tv_nsec = 0,
};

/*
 * Stores the time delta (in seconds) between the current and previous tick.
 */
double dt = 0.0;

double time_delta (void)
{
	return dt;
}

void time_tick (void)
{
	/*
	 * Initialize currtime if not yet set to a time.
	 * This results in the first tick having a time delta of 0.
	 */
	if (currtime.tv_sec == 0 && currtime.tv_nsec == 0) {
		clock_gettime(CLOCK_REALTIME, &currtime);
		return;
	}

	struct timespec newtime;
	clock_gettime(CLOCK_REALTIME, &newtime);

	struct timespec timediff = timespec_compare(&newtime, &currtime);
	currtime = newtime;

	/*
	 * time_t may be represented by a long int on some systems.
	 * This will result in overflow if the number of seconds since the last tick
	 * exceeds the maximum representable positive number for a long int
	 * - 2,147,483,647 - divided by the number of nanoseconds in a second
	 * - 1,000,000,000 - which effectively limits the maximum tick length to
	 * 2.147... seconds.
	 *
	 * The following code presents the issue, forcing seconds into
	 * a 32-bit representation:
	 * 	#include <stdint.h>
	 * 	#include <stdio.h>
	 * 	int32_t seconds = 3;
	 * 	double overflow = 0.000000001 * (seconds * 1000000000);
	 * 	printf("%f", overflow);
	 * 	// Desired: 3.000000,
	 * 	// Output: -1.294967.
	 */
	dt = NANOSECOND_AS_SECOND * (
		(timediff.tv_sec * NANOSECONDS_INA_SECOND) + timediff.tv_nsec
	);
}

/*
 * Returns a timespec representing the difference between 2 timespecs.
 */
struct timespec timespec_compare (
	struct timespec *timespec_1,
	struct timespec *timespec_2
)
{
	return (struct timespec) {
		.tv_sec = timespec_1->tv_sec - timespec_2->tv_sec,
		.tv_nsec = timespec_1->tv_nsec - timespec_2->tv_nsec,
	};
}

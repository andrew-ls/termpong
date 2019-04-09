
#!/bin/sh

# This file is part of termpong.
#
# Copyright (c) 2019 Andrew Steel <copyright@andrewsteel.net>
#
# SPDX-License-Identifier: GPL-3.0-only
#
# The GNU General Public License Version 3 only:
#
# This is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License Version 3
# as published by the Free Software Foundation.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this file. If not, see <https://www.gnu.org/licenses/>.

ROOT="$(cd "$(dirname "${0}")"; pwd)/.."
OBJECT="${ROOT}/tests/strings.o"

if \
	command c99 \
		-o "${OBJECT}" \
		-l 'm' \
		-I "${ROOT}/src" \
		"${ROOT}/tests/strings.c" \
		"${ROOT}/src/lib/strings.c" \
		;
then
	EXPECTED="$(
		printf '%s\n' \
			'1' \
			'1' \
			'9' \
			'10' \
			'10' \
			'10'
	)"
	OUTPUT="$("${OBJECT}")"
	rm "${OBJECT}"
	if test "${OUTPUT}" = "${EXPECTED}"; then
		printf '%s\n' 'SUCCESS'
		exit 0
	else
		printf '%s\n' \
			'FAILURE:' \
			'  Expected:' \
			"    $(printf '%s ' ${EXPECTED})" \
			'  Received:' \
			"    $(printf '%s ' ${OUTPUT})"
		exit 1
	fi
else
	exit 2
fi

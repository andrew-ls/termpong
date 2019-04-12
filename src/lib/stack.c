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

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "./stack.h"

struct stack *stack_find (struct stack *node, void *pointer)
{
	while (node) {
		if (node->body == pointer) {
			return node;
		}
		else {
			node = node->next;
		}
	}
	return NULL;
}

struct stack *stack_findval (
	struct stack *node,
	void *value,
	bool (*comparison)())
{
	while (node) {
		if (comparison(node->body, value)) {
			return node;
		}
		else {
			node = node->next;
		}
	}
	return NULL;
}

struct stack *stack_pop (struct stack *node)
{
	struct stack *nextnode = node->next;
	free(node);
	return nextnode;
}

struct stack *stack_push (struct stack *next, void *body)
{
	struct stack *newnode = malloc(sizeof(*newnode));
	if (newnode) {
		newnode->next = next;
		newnode->body = body;
	}
	return newnode;
}

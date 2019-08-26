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
#include <stdio.h>
#include <stdlib.h>

#include "./stack.h"
struct stack *stack_gethead (struct stack *);
bool stack_ishead (struct stack *);

struct stack *stack_find (struct stack *node, void *pointer)
{
	return node
		? node->body == pointer
			? node
			: stack_find(node->next, pointer)
		: NULL;
}

struct stack *stack_findval (
	struct stack *node,
	void *value,
	bool (*comparison)())
{
	return node
		? comparison(node->body, value)
			? node
			: stack_findval(node->next, value, comparison)
		: NULL;
}

struct stack *stack_gethead (struct stack *node)
{
	return node
		? stack_ishead(node)
			? node
			: stack_gethead(node->prev)
		: NULL;
}

inline bool stack_ishead (struct stack *node)
{
	return node->prev == NULL;
}

struct stack *stack_pop (struct stack *node)
{
	if (node) {
		struct stack *headnode;
		if (stack_ishead(node)) {
			if (node->next) {
				node->next->prev = NULL;
			}
			headnode = node->next;
		}
		else {
			node->prev->next = node->next;
			headnode = stack_gethead(node->prev);
		}
		free(node);
		return headnode;
	}
	else {
		return NULL;
	}
}

void stack_print (struct stack *node)
{
	for (int i = 0; node; i++, node = node->next) {
		printf("\n");
		printf("%i: %p\n", i, (void *) node);
		printf("PREV: %p\n", (void *) node->prev);
		printf("NEXT: %p\n", (void *) node->next);
		printf("BODY: %p\n", (void *) node->body);
	}
}

struct stack *stack_push (struct stack *next, void *body)
{
	struct stack *newnode = malloc(sizeof(*newnode));
	if (newnode) {
		*newnode = (struct stack) {
			.prev = NULL,
			.next = next,
			.body = body,
		};
		if (next) {
			next->prev = newnode;
		}
	}
	return newnode;
}

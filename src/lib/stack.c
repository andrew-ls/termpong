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
 * This is a very simple implementation of a stack with no internal maintenance:
 * the consumer must track the current head node of the stack and always has
 * access to its body until popped, whereupon it receives the next node
 * (unlike other implementations where the consumer tracks the stack itself,
 * only receiving the head node's body when popped from the stack).
 *
 * Below is a visual representation of a stack containing 3 nodes;
 * lines with an arrow head represent pointers:
 *
 *   HEAD                  TAIL
 * ┌──────┐   ┌──────┐   ┌──────┐
 * │ next ────> next ────> next ────> NULL
 * ├──────┤   ├──────┤   ├──────┤
 * │ body ──┐ │ body ──┐ │ body ──┐
 * └──────┘ │ └──────┘ │ └──────┘ │
 *          │          │          │
 * ┌──────┐ │ ┌──────┐ │ ┌──────┐ │
 * │ ???? <─┘ │ ???? <─┘ │ ???? <─┘
 * └──────┘   └──────┘   └──────┘
 */

#include <stddef.h>
#include <stdlib.h>

#include "./stack.h"

/*
 * Removes a node from memory, returning the next node (or NULL).
 */
struct stack *stack_pop (struct stack *node)
{
	struct stack *nextnode = node->next;
	free(node);
	return nextnode;
}

/*
 * Creates and returns a new stack node in memory, which is the new head node.
 * Use NULL for `next` if this is a new stack.
 */
struct stack *stack_push (struct stack *next, void *body)
{
	struct stack *newnode = malloc(sizeof(*newnode));
	if (newnode) {
		newnode->next = next;
		newnode->body = body;
	}
	return newnode;
}

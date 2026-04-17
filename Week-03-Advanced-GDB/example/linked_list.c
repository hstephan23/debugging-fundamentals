/*
 * linked_list.c — for practising Python pretty-printers and custom GDB
 * commands.
 *
 * Build:  make linked_list
 * Run:    gdb ./linked_list
 *         (gdb) source printers.py
 *         (gdb) break breakpoint_here
 *         (gdb) run
 *         (gdb) p *head           # your pretty-printer formats this nicely
 *         (gdb) plist head        # your custom 'plist' command walks the list
 */
#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};

static struct node *push(struct node *head, int v)
{
    struct node *n = malloc(sizeof *n);
    n->value = v;
    n->next  = head;
    return n;
}

/* GDB will break on this no-op; good place to inspect the list. */
static void breakpoint_here(struct node *head) { (void)head; }

int main(void)
{
    struct node *head = NULL;
    for (int i = 1; i <= 5; i++) head = push(head, i * 10);

    breakpoint_here(head);

    for (struct node *p = head; p; ) {
        struct node *n = p->next;
        free(p);
        p = n;
    }
    return 0;
}

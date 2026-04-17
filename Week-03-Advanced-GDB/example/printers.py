"""
printers.py — a tiny GDB Python pretty-printer and custom command for the
`struct node` linked list in linked_list.c.

Load inside GDB with:
    (gdb) source printers.py

Then:
    (gdb) p *head          # uses NodePrinter
    (gdb) plist head       # custom command that walks the list
"""

import gdb


class NodePrinter:
    def __init__(self, val):
        self.val = val

    def to_string(self):
        # gdb.Value fields are accessed like a dict
        return f"Node(value={int(self.val['value'])}, next={self.val['next']})"


def _node_lookup(val):
    t = val.type.unqualified().strip_typedefs()
    if t.code == gdb.TYPE_CODE_STRUCT and t.tag == "node":
        return NodePrinter(val)
    return None


gdb.pretty_printers.append(_node_lookup)


class PrintList(gdb.Command):
    """plist HEAD — walk a struct-node linked list and print each value."""

    def __init__(self):
        super().__init__("plist", gdb.COMMAND_USER)

    def invoke(self, arg, from_tty):
        head = gdb.parse_and_eval(arg)
        i = 0
        while int(head) != 0:
            print(f"  [{i}] {int(head.dereference()['value'])}")
            head = head.dereference()['next']
            i += 1
        print(f"  ({i} nodes)")


PrintList()
print("printers.py loaded — try 'p *head' and 'plist head'")

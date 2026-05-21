#!/usr/bin/env bash
# enable-cores.sh — a quick reference for enabling core dumps on Linux.
#
# Source this (don't execute) if you want the ulimit change to apply to your
# current shell:  . ./enable-cores.sh

set -u

echo "== current core settings =="
ulimit -c
cat /proc/sys/kernel/core_pattern 2>/dev/null || true

echo
echo "== enabling cores for this shell =="
ulimit -c unlimited
echo "ulimit -c -> $(ulimit -c)"

echo
echo "== where cores will go =="
pat=$(cat /proc/sys/kernel/core_pattern 2>/dev/null || echo "(no /proc)")
echo "core_pattern: $pat"

case "$pat" in
    \|*)
        echo "  (piped to a core handler — probably systemd-coredump.)"
        echo "  retrieve with:  coredumpctl list | tail"
        echo "                  coredumpctl info"
        echo "                  coredumpctl gdb"
        ;;
    *)
        echo "  cores will be written to current working directory as '$pat'."
        echo "  tip: set  echo 'core.%e.%p.%t' | sudo tee /proc/sys/kernel/core_pattern"
        echo "  for per-PID, per-exe filenames."
        ;;
esac

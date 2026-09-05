#!/usr/bin/env bash

found=$(grep -rnE '\b(new|delete)\b' core/src | grep -v '= delete' | grep -v '//')

if [ -n "$found" ]; then
    echo "Found raw new/delete:"
    echo "$found"
    exit 1
else
    echo "Clean - no raw new/delete found."
    exit 0
fi
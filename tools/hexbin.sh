#!/usr/bin/env bash
grep -E '^[0-9A-Fa-f]+$' | xxd -r -p

#!/usr/bin/env bash

python3 test.py &
pid=$!
sleep 7200 # two hours
if kill -0 $pid; then kill -TERM $pid; echo "too long"; fi
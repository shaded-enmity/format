#!/usr/bin/bash

echo "Timing using 'format.format()':"
time python ./test.py

echo "Timing using 'S.format()':"
time python ./test_regular.py

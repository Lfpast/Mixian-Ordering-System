#!/bin/sh
# Portable runner for all tests
set -e
EXE="./system"
if [ -f "./system.exe" ]; then
  EXE="./system.exe"
fi
for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24; do
  echo "Running test case $i"
  $EXE --mode test --testcase $i
done

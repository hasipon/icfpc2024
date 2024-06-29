#!/bin/bash

name="inada1"
for i in $(seq 1 21); do
  gtimeout 10 ./cmake-build-release/inada1 ../problems/lambdaman/${i}.txt 2>/dev/null > ../solutions/lambdaman/${i}-${name}.txt 
done

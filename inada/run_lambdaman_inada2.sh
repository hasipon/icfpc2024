#!/bin/bash

name="inada2"
for i in $(seq 18 21); do
  ./cmake-build-release/inada2 ../problems/lambdaman/${i}.txt 2>/dev/null > ../solutions/lambdaman/${i}-${name}.txt 
done

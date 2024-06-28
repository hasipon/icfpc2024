#!/bin/bash

name="hasi1"
for i in $(seq 1 21); do
  gtimeout 10 ./a.out < ../problems/lambdaman/${i}.txt > ../solutions/lambdaman/${i}-${name}.txt 
done

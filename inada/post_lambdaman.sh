#!/bin/bash

name="inada1"
i=$1
echo "solve lambdaman$i $(cat ../solutions/lambdaman/${i}-${name}.txt)" | python3 a.py

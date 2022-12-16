#!/bin/bash

for n in {10000..1000000..5000}; 
do
    ../debug/test-rb-tree $n 10 random_char.txt
done
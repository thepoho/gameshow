#!/bin/bash
gcc -o lamp_matrix lamp_matrix.c -lwiringPi -std=c99 
echo "RUNNING" 
./lamp_matrix

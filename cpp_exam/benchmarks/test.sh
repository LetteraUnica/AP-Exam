#!/bin/bash
mkdir results
c++ -O3 -std=c++14 -o benchmark.x benchmark.cc
./benchmark.x
python analisys.py

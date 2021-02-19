#!/bin/bash
mkdir results
c++ -O3 -std=c++14 benchmark.cc
./a.out
python analisys.py
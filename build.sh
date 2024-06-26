#!/bin/bash

dst=/tmp
path=example

flags=(-I include -m64 -std=c++26 -s -Wall -O3)
executables=(fuple lists reflect fmp member_info visitor invocable_name)

for bin in ${executables[@]}; do
      g++ "${flags[@]}" -o ${dst}/${bin} ${path}/${bin}.cpp
done

echo Please check the executables at ${dst}

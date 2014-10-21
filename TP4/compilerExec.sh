#!/bin/bash

g++ -c src/main.cpp -o src/main.o -I /usr/include/opencv -I include
g++ src/main.o -o bin/exe -lopencv_core -lopencv_imgproc -lopencv_highgui
./bin/exe 
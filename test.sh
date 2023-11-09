#!bash

make ; ./generator_linux $1 |  ./lem-in -v | tee res | grep '#'

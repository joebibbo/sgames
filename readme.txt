This is a some code to solve the following problem:

Problem 1:
	Given a list of people with their birth and end years (all between 1900 and 2000), find the year 
	with the most number of people alive.

The solution is written in C++-0x11. It can be run in Windows or Mac, with a more recent toolchain.

genfixup.cpp   - builds to an executable. It will read 'names' and create the final dataset 'names_'
population.cpp - builds to an executable. It reads 'names_' and return the answer to the problem above.


To build:

mac: clang++ -std=c++0x -stdlib=libc++ population.cpp -o population
win: cl population.cpp
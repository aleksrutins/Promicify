install:
	cp -t /usr/include promicify.h
test:
	clang++ -std=c++14 test.cc -o test
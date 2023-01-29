all: run

run: a.out
	./a.out > tmp.md

a.out: *.cpp *.hpp
	c++ -g *.cpp

clean:
	rm a.out

re: clean all

run: a.out
	./a.out > tmp.md

debug deb: a.out
	valgrind ./a.out > tmp.md

a.out: *.cpp *.hpp
	c++ -g *.cpp

clean:
	rm a.out

re: clean all

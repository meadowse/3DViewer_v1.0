APP = build/3DViewer_v1.app
CC+FLAGS = gcc -std=c11 -Wall -Wextra -Werror
GCOVFLAGS = -L. --coverage
CHECK_FLAGS = -lcheck

all: install tests clean

build:
	mkdir build
	cd ./build/ && qmake ../GUI && make

install: uninstall build
	@mkdir $(HOME)/Desktop/3DViewer_v1
	@cp -rf $(APP) $(HOME)/Desktop/3DViewer_v1/
	make clean

uninstall: clean
	@rm -rf $(HOME)/Desktop/3DViewer_v1

dvi:
	open dvi.tex

dist:
	rm -rf Archive_3DViewer_v1.0/
	mkdir Archive_3DViewer_v1.0/
	mkdir Archive_3DViewer_v1.0/src
	cp Makefile GUI/*.c GUI/*.h GUI/*.pro GUI/*.cpp GUI/*.ui GUI/*.user Archive_3DViewer_v1.0/src/
	tar cvzf Archive_3DViewer_v1.0.tgz Archive_3DViewer_v1.0/
	mv Archive_3DViewer_v1.0.tgz $(HOME)/Desktop/
	rm -rf Archive_3DViewer_v1.0/

tests:
	checkmk clean_mode=1 GUI/test.check > GUI/test.c
	gcc -Wall -Werror -Wextra GUI/viewer.c GUI/test.c -lcheck
	rm GUI/test.c
	./a.out

gcov_report:
	rm -f *.g*
	checkmk clean_mode=1 GUI/test.check > GUI/test.c
	gcc -Wall -Werror -Wextra GUI/viewer.c GUI/test.c -lcheck --coverage
	./a.out
	lcov -t a.out -o rep.info -c -d .
	genhtml -o report rep.info
	rm GUI/test.c
	open ./report/index.html
	rm -rf *.gcda *.gcno *.info

3DViewer_v1.o:
	$(CC+FLAGS) -c *.c

linters:
	clang-format -n GUI/*.c
	clang-format -n GUI/*.h

clean:
	rm -rf *.o *.a
	rm -rf *.gcda *.gcno *.info
	rm -rf s21_test report
	rm -rf s21_calc s21_test
	rm -rf ./build*
	rm -rf a.out

leaks:
	CK_FORK=no leaks --atExit -- ./a.out

rebuild: clean uninstall all

reinstall: clean uninstall install
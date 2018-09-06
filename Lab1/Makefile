demo: driver.c lex.yy.c demo.tab.c demo.tab.h
	gcc -o demo driver.c demo.tab.c lex.yy.c

demo.tab.c demo.tab.h:	demo.y
	bison -d demo.y

lex.yy.c: demo.l demo.tab.h
	flex demo.l

clean:
	rm demo demo.tab.c lex.yy.c demo.tab.h
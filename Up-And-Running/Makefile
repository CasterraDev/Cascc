comp1: cg.c expression.c gen.c interpret.c main.c scan.c asttree.c
		cc -o comp1 -g cg.c expression.c gen.c interpret.c main.c scan.c asttree.c

clean:
		rm -f comp1 *.s *.o out

test: comp1
	./comp1 input1
	cc -o out out.s
	./out
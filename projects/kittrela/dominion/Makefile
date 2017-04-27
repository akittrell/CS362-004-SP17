CFLAGS = -Wall -fpic -coverage -lm

default: unittestresults.out

unittestresults.out: unittest1.c dominion.c rngs.c assertTrue.c
	echo "Result for running unittest1:" > unittestresults.out
	gcc -o unittest1 dominion.c rngs.c unittest1.c assertTrue.c $(CFLAGS)
	unittest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
	echo "Result for running unittest2:" > unittestresults.out
	gcc -o unittest2 dominion.c rngs.c unittest2.c assertTrue.c $(CFLAGS)
	unittest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
clean:
	rm -f unittestresults.out
	
cleanall:
	rm -f unittestresults.out unittest1 unittest2*.gcda *.gcno *.gcov
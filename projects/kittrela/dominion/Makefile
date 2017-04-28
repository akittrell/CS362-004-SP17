CFLAGS = -Wall -fpic -coverage -lm

default: unittestresults.out

unittestresults.out: unittest1.c unittest2.c unittest3.c unittest4.c dominion.c rngs.c assertTrue.c
	echo "Result for running unittest1:" > unittestresults.out
	gcc -o unittest1 unittest1.c dominion.c rngs.c assertTrue.c $(CFLAGS)
	unittest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
	echo "Result for running unittest2:" >> unittestresults.out
	gcc -o unittest2 unittest2.c dominion.c rngs.c assertTrue.c $(CFLAGS)
	unittest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
	echo "Result for running unittest3:" >> unittestresults.out
	gcc -o unittest3 unittest3.c dominion.c rngs.c assertTrue.c $(CFLAGS)
	unittest3 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
	echo "Result for running unittest4:" >> unittestresults.out
	gcc -o unittest4 unittest4.c dominion.c rngs.c assertTrue.c $(CFLAGS)
	unittest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
clean:
	rm -f unittestresults.out
	
cleanall:
	rm -f unittestresults.out unittest1 unittest2 unittest3 unittest4 *.gcda *.gcno *.gcov
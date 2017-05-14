CFLAGS = -Wall -fpic -fprofile-arcs -ftest-coverage -coverage -lm

default: unittestresults.out

unittestresults.out: randomtestadventurer.c dominion.c rngs.c assertTrue.c
	echo "Result for running Random Test Adventure:" > randomtestadventurer.out
	gcc -o randomtestadventurer randomtestadventurer.c dominion.c rngs.c assertTrue.c $(CFLAGS)
	randomtestadventurer >> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	echo
	gcov dominion.c -b -f >> randomtestadventurer.out
	
	echo "Result for running randomtestcard1:" > randomtestcard1.out
	gcc -o randomtestcard1 randomtestcard1.c dominion.c rngs.c assertTrue.c $(CFLAGS)
	randomtestcard1 >> randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out
	echo
	gcov dominion.c -b -f >> randomtestcard1.out

	echo "Result for running randomtestcard2:" > randomtestcard2.out
	gcc -o randomtestcard2 randomtestcard2.c dominion.c rngs.c assertTrue.c $(CFLAGS)
	randomtestcard2 >> randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out
	echo
	gcov dominion.c -b -f >> randomtestcard2.out
clean:
	rm -f randomtestcard1.out randomtestadventurer.out randomtestcard2
	
cleanall:
	rm -f randomtestcard1.out randomtestadventurer.out randomtestadventurer randomtestcard1 randomtestcard2 *.gcda *.gcno *.gcov
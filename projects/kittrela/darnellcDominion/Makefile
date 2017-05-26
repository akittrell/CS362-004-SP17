default: unittestresults.out

unittestresults.out: unittest1.c unittest2.c unittest3.c unittest4.c dominion.c rngs.c assertTrue.c
	echo "Result for running unittest1:" > unittestresults.out
	gcc -o unittest1 unittest1.c dominion.c rngs.c assertTrue.c
	./unittest1 >> unittestresults.out

	
	echo "Result for running unittest2:" >> unittestresults.out
	gcc -o unittest2 unittest2.c dominion.c rngs.c assertTrue.c
	./unittest2 >> unittestresults.out
	
	echo "Result for running unittest3:" >> unittestresults.out
	gcc -o unittest3 unittest3.c dominion.c rngs.c assertTrue.c
	./unittest3 >> unittestresults.out
	
	echo "Result for running unittest4:" >> unittestresults.out
	gcc -o unittest4 unittest4.c dominion.c rngs.c assertTrue.c
	./unittest4 >> unittestresults.out
	
	echo "Result for running cardtest1:" >> unittestresults.out
	gcc -o cardtest1 cardtest1.c dominion.c rngs.c assertTrue.c
	./cardtest1 >> unittestresults.out
	
	echo "Result for running cardtest2:" >> unittestresults.out
	gcc -o cardtest2 cardtest2.c dominion.c rngs.c assertTrue.c
	./cardtest2 >> unittestresults.out
	
	echo "Result for running cardtest3:" >> unittestresults.out
	gcc -o cardtest3 cardtest3.c dominion.c rngs.c assertTrue.c
	./cardtest3 >> unittestresults.out
	
	echo "Result for running cardtest4:" >> unittestresults.out
	gcc -o cardtest4 cardtest4.c dominion.c rngs.c assertTrue.c
	./cardtest4 >> unittestresults.out

	# cannot run the following without infinite while loop	
#	echo "Result for running randomtestadventurer:" >> unittestresults.out
#	gcc -o randomtestadventurer randomtestadventurer.c dominion.c rngs.c assertTrue.c
#	./randomtestadventurer >> unittestresults.out
	
	echo "Result for running randomtestcard1:" >> unittestresults.out
	gcc -o randomtestcard1 randomtestcard1.c dominion.c rngs.c assertTrue.c
	./randomtestcard1 >> unittestresults.out
	
	echo "Result for running randomtestcard2:" >> unittestresults.out
	gcc -o randomtestcard2 randomtestcard2.c dominion.c rngs.c assertTrue.c
	./randomtestcard2 >> unittestresults.out

clean:
	rm -f unittestresults.out
	
cleanall:
	rm -f unittestresults.out ./unittest1 ./unittest2 ./unittest3 ./unittest4 ./cardtest1 ./cardtest2 ./cardtest3 ./cardtest4 ./randomtestadventurer ./randomtestcard1 ./randomtestcard2 *.gcda *.gcno *.gcov
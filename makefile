PokemonsBattles:  MainSecond.o  BattleByCategory.o LinkedList.o MaxHeap.o  Pokemon.o
	gcc MainSecond.o BattleByCategory.o LinkedList.o MaxHeap.o  Pokemon.o -o PokemonsBattles

BattleByCategory.o: BattleByCategory.c BattleByCategory.h LinkedList.h MaxHeap.h Defs.h
	gcc -c BattleByCategory.c

LinkedList.o: LinkedList.c LinkedList.h Defs.h
	gcc -c LinkedList.c
	
MaxHeap.o: MaxHeap.c MaxHeap.h Defs.h
	gcc -c MaxHeap.c
	
MainSecond.o: MainSecond.c Defs.h BattleByCategory.h LinkedList.h MaxHeap.h  Pokemon.h Defs.h
	gcc -c MainSecond.c

clean:
	rm -f *.o PokemonsBattles

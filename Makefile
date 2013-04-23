OBJ = main.o gen_rand_array.o heap_sort.o quick_sort.o
ita: $(OBJ)
	cc -g $(OBJ) -o ita

main.o:main.c

gen_rand_array.o:./randomize/gen_rand_array.c ./randomize/gen_rand_array.h
	cc -c ./randomize/gen_rand_array.c 

heap_sort.o:./sorts/heap_sort/heap_sort.c ./sorts/heap_sort/heap_sort.h
	cc -c ./sorts/heap_sort/heap_sort.c 

quick_sort.o:./sorts/quick_sort/quick_sort.c ./sorts/quick_sort/quick_sort.h
	cc -c ./sorts/quick_sort/quick_sort.c

clean:
	rm ita *.o

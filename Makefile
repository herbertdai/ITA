OBJ = main.o gen_rand_array.o heap_sort.o quick_sort.o normal_sort.o binary_tree.o

ita: $(OBJ)
	cc -g $(OBJ) -o ita

main.o:main.c

gen_rand_array.o:
	cc -c ./randomize/gen_rand_array.c 

heap_sort.o:
	cc -c ./sorts/heap_sort/heap_sort.c 

quick_sort.o:
	cc -c ./sorts/quick_sort/quick_sort.c

normal_sort.o:
	cc -c ./sorts/normal_sort.c

binary_tree.o:
	cc -c ./BSTree/binary_tree.c

clean:
	rm ita *.o

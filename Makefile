struct: structSize.c
	gcc -Wall -ggdb -std=c99 structSize.c -o structSize	
	./structSize

data: data.c
	gcc -Wall -ggdb -std=c99 data.c -o data	
	./data

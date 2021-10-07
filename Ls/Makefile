
CC=gcc
CC_OPT=-g3 -fsanitize=address -Wall -Werror -Wextra
OUTPUT=my_ls

all: ${OUTPUT}

${OUTPUT}: main.o my_ls.o my_func.o get_opt.o user_out.o memory.o
	${CC} ${CC_OPT} main.o my_ls.o my_func.o get_opt.o user_out.o memory.o -o ${OUTPUT}

main.o: main.c
	${CC} ${CC_OPT} -c main.c

my_ls.o: my_ls.c
	${CC} ${CC_OPT} -c my_ls.c

my_func.o: my_func.c
	${CC} ${CC_OPT} -c my_func.c

get_opt.o: get_opt.c
	${CC} ${CC_OPT} -c get_opt.c

user_out.o: user_out.c
	${CC} ${CC_OPT} -c user_out.c

memory.o: memory.c
	${CC} ${CC_OPT} -c memory.c

clean:
	rm *.o ${OUTPUT}
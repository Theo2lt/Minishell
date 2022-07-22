
NAME =	minishell

CC =	gcc

DEL =	/bin/rm -f

SRCS = utilslibft.c ./main.c ./lexer_first.c ./lexer_second.c expand_init.c remplace_expand.c\

LIB =  -L/usr/include -lreadline

OBJS    = ${SRCS:.c=.o}

CFLAGS    = -Wall -Werror -Wextra -g3
CC        = gcc

RM        = rm -f

all:    ${NAME}

$(NAME):	${OBJS}
		${CC} ${CFLAGS} ${OBJS} ${LIB} -o ${NAME}

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
		${RM} ${OBJS}

fclean:        clean
			${RM} ${NAME}
	
re:	fclean all
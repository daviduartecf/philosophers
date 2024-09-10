CC = cc -g
NAME = philo
FT_PRINTF = ft_printf/libftprintf.a
FLAGS = -Wall -Werror -Wextra
SRCS = src/main.c src/init.c src/utils.c src/time_utils.c src/check_deaths.c src/parsing_philos.c src/quit_program.c src/routines.c
OBJS = ${SRCS:.c=.o}

all: ${NAME}

${FT_PRINTF}:
	@make --silent -C ft_printf

${NAME}: ${OBJS} ${FT_PRINTF}
	@echo "\033[0;32mCompiling program...\033[0m"
	@${CC} ${OBJS} ${FT_PRINTF} ${FLAGS} -o ${NAME}
	@echo "\033[0;32mphilo successfully compiled.\033[0m"

%.o: %.c
	@${CC} -c $< -o $@ -Wall -Werror -Wextra

clean:
	@rm -f ${OBJS}
	@make --no-print-directory -C ft_printf/ fclean

fclean:	clean
	@rm ${NAME}

re: fclean all


.PHONY : all clean fclean re

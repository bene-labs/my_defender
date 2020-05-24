##
## EPITECH PROJECT, 2019
## Makefile My_Defender
## File description:
## makes my_defender
##

SRC	=	src/main.c					\
		src/create_objects/create_objects.c		\
		src/create_objects/create_towers.c		\
		src/map/generate_map.c				\
		src/create_objects/create_enemies.c		\
		src/movement/move_enemies.c			\
		src/movement/animate_enemies.c			\
		src/cleanup.c					\
		src/towers/build_menus.c			\
		src/towers/druid.c				\
		src/towers/mage_tower.c				\
		src/towers/tavern.c				\
		src/handle_randomness.c				\
		src/collision/handle_collision.c		\
		src/list_help_functions.c			\
		src/score.c					\
		src/movement/enemy_attack.c			\
		src/player_stats.c				\
		src/create_objects/handle_enemy_waves.c		\
		src/towers/additional_tower_ui.c		\
		src/towers/stone_tower.c			\
		src/str_functions.c				\
		src/menu/main_menu.c				\
		src/main_gameplay.c				\
		src/create_objects/create_menu_objects.c	\
		src/menu/settings.c				\
		src/menu/buttons.c				\
		src/my_printf/disp_stdarg.c			\
		src/my_printf/disp_stdarg2.c			\
		src/my_printf/disp_stdarg3.c			\
		src/my_printf/disp_stdarg4.c			\
		src/my_printf/my_putstr.c			\
		src/my_printf/my_putchar.c			\
		src/my_printf/my_put_nbr.c			\
		src/my_printf/my_put_nbr_base.c			\
		src/my_printf/my_printf.c			\
		src/my_printf/my_strlen.c			\
		src/my_printf/my_getnbr.c

OBJ	=	$(SRC:.c=.o)

RM	=	rm -rf

NAME	=	my_defender

CFLAGS	+=    -W -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) -l csfml-window -l csfml-graphics -l csfml-system -l csfml-audio -lm

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all  clean fclean re

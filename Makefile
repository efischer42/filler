CC = clang

NAME = efischer.filler

CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror
DFLAGS += -fsanitize=address,undefined -g3

PATHSRCS = srcs/
SRCS += main.c
SRCS += state_machine.c
SRCS += get_player.c
SRCS += get_map.c
SRCS += get_piece.c
SRCS += opponent_heat_map.c
SRCS += player_heat_map.c
SRCS += play.c

PATHOBJS = objs/
OBJS = $(patsubst %.c, $(PATHOBJS)%.o, $(SRCS))

INCLUDES = includes/
HEAD += filler.h

PATHLIB = libft/
LIBINCLUDES = $(PATHLIB)includes
LIBFT = $(PATHLIB)libft.a

vpath %.c $(PATHSRCS)
vpath %.h $(INCLUDES)

all: $(NAME)

$(NAME): $(LIBFT) $(PATHOBJS) $(OBJS)
	$(CC) $(CFLAGS) $(DFLAGS) $(OBJS) $(LIBFT) -o $@

$(LIBFT): FORCE
	$(MAKE) -C $(PATHLIB)

$(OBJS): $(PATHOBJS)%.o: %.c $(HEAD) Makefile
	$(CC) -c $(CFLAGS) $(DFLAGS) $< -I $(INCLUDES) -I $(LIBINCLUDES) -o $@

$(PATHOBJS):
	@mkdir $@

clean:
	$(RM) $(OBJS)
	$(RM) -R $(PATHOBJS)
	$(MAKE) clean -C $(PATHLIB)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(PATHLIB) 

re: fclean all

FORCE:

.PHONY: all clean fclean re FORCE

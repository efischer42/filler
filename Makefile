CC = clang

NAME = efischer.filler

CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror
DFLAGS += -fsanitize=address,undefined
DFLSGS += -g3

PATHSRCS = srcs/
SRCS += main.c
SRCS += state_machine.c
SRCS += lexer_parser.c
SRCS += get_input.c
SRCS += lexer.c
SRCS += get_word.c
SRCS += parser.c
SRCS += get_player.c
SRCS += get_dimensions.c
SRCS += check_index.c
SRCS += get_map.c
SRCS += generate_map.c
SRCS += fill_map.c
SRCS += fill_line.c
SRCS += set_objectives.c
SRCS += path.c
SRCS += set_dir.c
SRCS += get_piece.c
SRCS += generate_piece.c
SRCS += fill_piece.c
SRCS += play.c
SRCS += del.c
SRCS += debug.c
SRCS += debug_map.c

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

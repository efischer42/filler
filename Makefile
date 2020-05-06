CC = clang

NAME = efischer.filler

CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror
DFLAGS += -fsanitize=address,undefined
DFLSGS += -g3

PATHSRCS = srcs/
SRCS += check_index.c
SRCS += del.c
SRCS += error.c
SRCS += fill_line.c
SRCS += fill_map.c
SRCS += fill_piece.c
SRCS += find_path.c
SRCS += generate_map.c
SRCS += generate_piece.c
SRCS += get_dimensions.c
SRCS += get_map.c
SRCS += get_piece.c
SRCS += get_player.c
SRCS += get_word.c
SRCS += lexer.c
SRCS += lexer_parser.c
SRCS += main.c
SRCS += parser.c
SRCS += path.c
SRCS += piece_placement.c
SRCS += play.c
SRCS += play_turn.c
SRCS += set_dir.c
SRCS += set_objectives.c
SRCS += sort.c
SRCS += debug.c
SRCS += debug_map.c
SRCS += debug_path_lst.c

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

# **************************************************************************** #
#                                                                              #
#                                                     :::       :::     :::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                  +:++:+     +:+  +  +:+      #
#    By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+       #
#                                              +#+    +#+   +#+     +#+        #
#    Created: 2023/10/17 02:01:51 by amahla  #+#      #+#  #+#     #+#         #
#    Updated: 2023/10/25 14:08:04 by amahla           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#NAME	= 	libft_malloc_$(HOSTTYPE).so
NAME	= 	libft_malloc.so
CC		:= 	gcc
CFLAGS	:= 	-Wall -Werror -Wextra
DFLAGS	:= -MMD -MP
LDFLAGS := -shared
LIBDIR 	:= 	libft
TESTDIR	:=	tests
INC		:= 	-I inc -I $(addprefix 	$(LIBDIR)/, $(addprefix libft/, includes))
LIBFT	:= 	-L libft -lft
OUTDIR 	:= 	obj
SRCDIR	:= src
SRC		:= $(addprefix $(SRCDIR)/,	malloc.c			\
									free.c				\
									realloc.c			\
									calloc.c			\
									show_alloc_mem.c	)
OBJ		:= $(SRC:.c=.o)
DEP 	:= $(SRC:.c=.d)
RM		:= rm -rf


ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif


all		: $(NAME)

$(OUTDIR)/%.o	: %.c 
	$(CC) -fPIC $(DFLAGS) $(CFLAGS) $(INC) -o $@ -c $<

$(NAME)	: $(OUTDIR)	$(addprefix $(OUTDIR)/, $(OBJ))
	@$(MAKE) -j -C $(LIBDIR) > /dev/null
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $(addprefix $(OUTDIR)/, $(OBJ)) $(INC) $(LIBFT)

$(OUTDIR)	:
	@mkdir -p $(addprefix $@/, $(SRCDIR))


.PHONY	: all clean fclean re debug run test

debug	: CFLAGS=-g3 -Wall -Werror -Wextra
debug	: all

export_lib	: $(NAME)
	cp libft_malloc.so tests/.

run		: $(NAME)
	$(MAKE) run -C $(TESTDIR)

run_libc	: $(NAME)
	$(MAKE) run_libc -C $(TESTDIR)

clean	:
	@$(MAKE) clean -C $(LIBDIR) > /dev/null
	@$(MAKE) clean -C $(TESTDIR) > /dev/null
	$(RM) $(OUTDIR)

fclean	: clean
	@$(MAKE) fclean -C $(LIBDIR) > /dev/null
	@$(MAKE) fclean -C $(TESTDIR) > /dev/null
	$(RM) $(NAME) libft_malloc.so

re		: fclean
	@$(MAKE) re -C $(LIBDIR) > /dev/null
	$(MAKE) all

-include	$(addprefix $(OUTDIR)/, $(DEP)))

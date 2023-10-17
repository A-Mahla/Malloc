# **************************************************************************** #
#                                                                              #
#                                                     :::       :::     :::    #
#    Makefile                                        :+:       :+: :+: :+:     #
#                                                  +:++:+     +:+  +  +:+      #
#    By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+       #
#                                              +#+    +#+   +#+     +#+        #
#    Created: 2023/10/17 02:01:51 by amahla  #+#      #+#  #+#     #+#         #
#    Updated: 2023/10/17 14:09:40 by amahla ###       ########     ########    #
#                                                                              #
# **************************************************************************** #


#NAME	= 	libft_malloc_$(HOSTTYPE).so
NAME	= 	malloc_$(HOSTTYPE)
CC		:= 	gcc
CFLAGS	:= 	-Wall -Werror -Wextra
DFLAGS	:= -MMD -MP
LIBDIR 	:= 	libft
INC		:= 	-I inc -I $(addprefix 	$(LIBDIR)/, $(addprefix libft/, includes))
LIBFT	:= 	-L libft -lft
OUTDIR 	:= 	obj
SRCDIR	:= src
SRC		:= $(addprefix $(SRCDIR)/,	malloc.c \
									main.c)
OBJ		:= $(SRC:.c=.o)
DEP 	:= $(SRC:.c=.d)
RM		:= rm -rf


ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif


all		: $(NAME)

$(addprefix $(OUTDIR)/, $(SRCDIR))/%.o	: $(SRCDIR)/%.c 
	$(CC) $(DFLAGS) $(CFLAGS) $(INC) -o $@ -c $<

$(NAME) : $(OUTDIR)	$(addprefix $(OUTDIR)/, $(OBJ))
	@$(MAKE) -j -C $(LIBDIR) > /dev/null
	$(CC) $(CFLAGS) -o $@ $(addprefix $(OUTDIR)/, $(OBJ)) $(INC) $(LIBFT)

$(OUTDIR)	:
	@mkdir -p $(addprefix $@/, $(SRCDIR))

.PHONY	: all clean fclean re

clean	:
	@$(MAKE) clean -C $(LIBDIR) > /dev/null
	$(RM) $(OUTDIR)

fclean	: clean
	@$(MAKE) fclean -C $(LIBDIR) > /dev/null
	$(RM) $(NAME)

re		: fclean
	@$(MAKE) re -C $(LIBDIR) > /dev/null
	make all

-include	$(addprefix $(OUTDIR)/, $(DEP)))

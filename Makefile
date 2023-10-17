# **************************************************************************** #
#                                                                              #
#                                                     :::       :::     :::    #
#    Makefile                                        :+:       :+: :+: :+:     #
#                                                  +:++:+     +:+  +  +:+      #
#    By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+       #
#                                              +#+    +#+   +#+     +#+        #
#    Created: 2023/10/17 02:01:51 by amahla  #+#      #+#  #+#     #+#         #
#    Updated: 2023/10/17 02:36:51 by amahla ###       ########     ########    #
#                                                                              #
# **************************************************************************** #


NAME	= 	libft_malloc_$(HOSTTYPE).so
CC		:= 	gcc
CFLAGS	:= 	-Wall -Werror -Wextra
LIBSRC 	:= 	libft
INC		:= 	-I inc -I $(addprefix 	$(LIBSRC)/, includes)
LIBFT	:= 	-L libft -lft
OUTDIR 	:= 	obj
SRC		:= 	
OBJ		:= $(SRC:.c=.o)
RM		:= rm -rf


ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif


all		: $(NAME)

$(OUTDIR)/%o	: $(SRC) 
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(NAME) : 	$(OUTDIR) $(addprefix $(OUTDIR)/, $(OBJ))
	@$(MAKE) -j -C $(LIBSRC) > /dev/null
	$(CC) $(CFLAGS) $@ $(addprefix $(OUTDIR)/, $(OBJ)) $(INC) $(LIBFT)

$(OUTDIR)	:
	@mkdir -p $@

.PHONY	: all clean fclean re

clean	:
	@$(MAKE) clean -C $(LIBSRC) > /dev/null
	$(RM) $(OUTDIR)

fclean	: clean
	@$(MAKE) fclean -C $(LIBSRC) > /dev/null
	$(RM) $(NAME)

re		: fclean
	@$(MAKE) re -C $(LIBSRC) > /dev/null
	make all

-include	$(addprefix $(OUTDIR)/,$(SRS:.c=.d)))

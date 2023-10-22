# **************************************************************************** #
#                                                                              #
#                                                     :::       :::     :::    #
#    Makefile                                        :+:       :+: :+: :+:     #
#                                                  +:++:+     +:+  +  +:+      #
#    By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+       #
#                                              +#+    +#+   +#+     +#+        #
#    Created: 2023/10/17 02:01:51 by amahla  #+#      #+#  #+#     #+#         #
#    Updated: 2023/10/22 22:33:34 by amahla ###       ########     ########    #
#                                                                              #
# **************************************************************************** #

NAME	:= test0 test1 test2 test3 test4 test5 test6
CC		:=	gcc
DFLAGS	:=	-MMD -MP
CFLAGS	:=	-w
OUTDIR 	:=	obj
SRCDIR	:=	src
INC		:=	-I ../inc
LIB		:= -L .. -lft_malloc
SRC0	:=	$(addprefix $(SRCDIR)/,	test0.c)
SRC1	:=	$(addprefix $(SRCDIR)/,	test1.c)
SRC2	:=	$(addprefix $(SRCDIR)/,	test2.c)
SRC3	:=	$(addprefix $(SRCDIR)/,	test3.c)
SRC4	:=	$(addprefix $(SRCDIR)/,	test4.c)
SRC5	:=	$(addprefix $(SRCDIR)/,	test5.c)
SRC6	:=	$(addprefix $(SRCDIR)/,	test6.c)
OBJ0	:=	$(SRC0:.c=.o)
OBJ1	:=	$(SRC1:.c=.o)
OBJ2	:=	$(SRC2:.c=.o)
OBJ3	:=	$(SRC3:.c=.o)
OBJ4	:=	$(SRC4:.c=.o)
OBJ5	:=	$(SRC5:.c=.o)
OBJ6	:=	$(SRC6:.c=.o)
DEP 	:=	$(SRC:.c=.d)
RM		:=	rm -rf


all		:
	$(MAKE) export_lib -C ..
	$(MAKE) $(NAME)

$(OUTDIR)/%.o	: %.c 
	$(CC) $(DFLAGS) $(CFLAGS) $(INC) -o $@ -c $<

test0	: $(OUTDIR)	$(addprefix $(OUTDIR)/, $(OBJ0))
	$(CC) $(CFLAGS) -o $@ $(addprefix $(OUTDIR)/, $(OBJ0)) $(INC)

test1	: $(OUTDIR)	$(addprefix $(OUTDIR)/, $(OBJ1))
	$(CC) $(CFLAGS) -o $@ $(addprefix $(OUTDIR)/, $(OBJ1)) $(INC)

test2	: $(OUTDIR)	$(addprefix $(OUTDIR)/, $(OBJ2))
	$(CC) $(CFLAGS) -o $@ $(addprefix $(OUTDIR)/, $(OBJ2)) $(INC)

test3	: $(OUTDIR)	$(addprefix $(OUTDIR)/, $(OBJ3))
	$(CC) $(CFLAGS) -o $@ $(addprefix $(OUTDIR)/, $(OBJ3)) $(INC)

test4	: $(OUTDIR)	$(addprefix $(OUTDIR)/, $(OBJ4))
	$(CC) $(CFLAGS) -o $@ $(addprefix $(OUTDIR)/, $(OBJ4)) $(INC) $(LIB)

test5	: $(OUTDIR)	$(addprefix $(OUTDIR)/, $(OBJ5))
	$(CC) $(CFLAGS) -o $@ $(addprefix $(OUTDIR)/, $(OBJ5)) $(INC)

test6	: $(OUTDIR)	$(addprefix $(OUTDIR)/, $(OBJ6))
	$(CC) $(CFLAGS) -o $@ $(addprefix $(OUTDIR)/, $(OBJ6)) $(INC) -lpthread

$(OUTDIR)	:
	@mkdir -p $(addprefix $@/, $(SRCDIR))

.PHONY	: all clean fclean re run

run		:
	$(MAKE) export_lib -C ..
	$(MAKE) $(NAME)
	./run_linux.sh /usr/bin/time -v ./test0
	./run_linux.sh /usr/bin/time -v ./test1
	./run_linux.sh /usr/bin/time -v ./test2
	./run_linux.sh ./test3
	./run_linux.sh ./test4
	./run_linux.sh /usr/bin/time -v ./test5
	./run_linux.sh /usr/bin/time -v ./test6

run_libc: $(NAME)
	/usr/bin/time -v ./test0
	/usr/bin/time -v ./test1
	/usr/bin/time -v ./test2
	./test3
	/usr/bin/time -v ./test5
	/usr/bin/time -v ./test6

clean	:
	$(RM) $(OUTDIR)

fclean	: clean
	$(RM) $(NAME) libft_malloc.so

re		: fclean
	make all

-include	$(addprefix $(OUTDIR)/, $(DEP)))

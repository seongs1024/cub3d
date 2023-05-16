#The Target
#For Binary: <name>, For Library: lib<name>.a
NAME		:=	cub3D

#Source Files
SOURCES		:=	main.c \
				error_handler.c \
				getter_color.c getter_img.c getter_map.c getter_player.c \
				utils1.c utils2.c \
				engine.c \
				display.c \
				camera.c \
				texture.c \
				raycaster.c \

#The Directories, Source, Includes, Dependencies
TESTDIR		:=	test
BONUSDIR	:=	bonus
SRCDIR		:=	src
INCDIR		:=	inc
DEPDIR		:=	dep
BLDDIR		:=	obj

#Dependencies
MLXDIR		:= minilibx_opengl_20191021
MLXLIB		:= mlx
MLXFLAG		:= -framework OpenGL -framework AppKit
GNLDIR		:= gnl
GNLLIB		:= gnl
LFDIR		:= libft
LFLIB		:= ft

DEPLIBS		:=	$(GNLLIB) $(MLXLIB) $(LFLIB)
DEPDIRS		:=	$(GNLDIR) $(MLXDIR) $(LFDIR)

#Compiler, Linker, Flags
CC			:=	cc
# DEBUG		:=	-g
# SANITIZE	:=	-fsanitize=address
CFLAGS		:=	-Wall -Wextra -Werror

#-------------------------------------------------------------------------------
#DO NOT EDIT BELOW THIS LINE
#-------------------------------------------------------------------------------
TARGET		:=	$(suffix $(NAME))
CEXT		:=	c
OEXT		:=	o
INC			:=	-I$(INCDIR) $(addprefix -I$(DEPDIR)/, $(DEPDIRS))
LIB			:=	$(addprefix -l, $(DEPLIBS))
LID			:=	$(addprefix -L$(DEPDIR)/, $(DEPDIRS))
SRCS		:=	$(addprefix $(SRCDIR)/,$(SOURCES))
OBJS		:=	$(patsubst $(SRCDIR)/%,$(BLDDIR)/%,$(SRCS:.$(CEXT)=.$(OEXT)))

#Defauilt Make
all: $(NAME)

test: $(NAME)
	./test/test.sh

bonus: 
	@make -C $(BONUSDIR)
	@cp $(BONUSDIR)/$(NAME) ./

#Remake
re: fclean all

#Make the Directories
directories:
	@mkdir -p $(BLDDIR)

#Dependencies
depend:
	@for ddir in $(addprefix $(DEPDIR)/, $(DEPDIRS)); do \
		make -s -C $$ddir; \
	done

#Clean only Objects
clean:
	@for ddir in $(addprefix $(DEPDIR)/, $(DEPDIRS)); do \
		make -s -C $$ddir clean; \
	done
	@$(RM) -rf $(BLDDIR)

#Full Clean, Objects and Binaries
fclean: clean
	@make -s -C $(addprefix $(DEPDIR)/, $(GNLDIR)) fclean
	@make -s -C $(addprefix $(DEPDIR)/, $(LFDIR)) fclean
	@$(RM) -rf $(NAME)

#Link
$(NAME): $(OBJS)
	@for ddir in $(addprefix $(DEPDIR)/, $(DEPDIRS)); do \
		make -s -C $$ddir; \
	done
ifeq ($(TARGET), .a)
	$(AR) -rc $@ $^
else
	$(CC) $(SANITIZE) $(DEBUG) $(INC) -o $(NAME) $^ $(LID) $(LIB) $(MLXFLAG)
endif

#Compile
$(BLDDIR)/%.$(OEXT): $(SRCDIR)/%.$(CEXT) 
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(SANITIZE) $(DEBUG) $(INC) -c -o $@ $<

#Non-File Targets
.PHONY: all re clean fclean bonus directories depend test

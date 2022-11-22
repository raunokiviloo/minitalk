NAME = minitalk
SERVER = server
CLIENT = client

LIBFT = libft/libft.a

DIR_LIB = libft
DIR_SRC = src

SRC_CLIENT = $(DIR_SRC)/client.c
SRC_SERVER = $(DIR_SRC)/server.c
SRC_LIB = $(DIR_LIB)/*.c 

OBJ_LIB = $(DIR_LIB)/*.o

RM = rm -f

CFLAGS = -Wall -Wextra -Werror


all: $(NAME) 

$(NAME): $(LIBFT) $(CLIENT) $(SERVER)
	@echo "Successfully made $(NAME)!"
	
$(LIBFT): $(OBJ_LIB)
	@ar rcs $@ $^ #Create static lib containing libft objects. 

$(OBJ_LIB): $(SRC_LIB)
	@$(MAKE) -s -C $(DIR_LIB) #Runs the makefile in libft subdir
	
$(CLIENT): $(SRC_CLIENT)
	@gcc $(CFLAGS) $^ -Llibft -lft -o client
	
$(SERVER): $(SRC_SERVER)
	@gcc $(CFLAGS) $^ -Llibft -lft -o server

clean:
	@$(RM) $(OBJ_LIB)
	@echo "Objects removed successfully!"

fclean: clean
	@$(RM) $(CLIENT) $(SERVER)
	@echo "Executable removed successfully!"

re:	fclean all

.PHONY:	all, clean, fclean, re

SERVER = server
CLIENT = client

SERVER_SRC = main-core/server.c
CLIENT_SRC = main-core/client.c

SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

LIBFT_PATH = libft/
LIBFT = $(LIBFT_PATH)/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L$(LIBFT_PATH) -lft

all: $(LIBFT) $(SERVER) $(CLIENT)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

$(SERVER): $(SERVER_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o ./$(SERVER) $(SERVER_OBJ) $(LDFLAGS)

$(CLIENT): $(CLIENT_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o ./$(CLIENT) $(CLIENT_OBJ) $(LDFLAGS)

clean:
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ)
	$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	rm -f ./$(SERVER) ./$(CLIENT)
	$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re $(LIBFT)

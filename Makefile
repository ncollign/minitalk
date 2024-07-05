# Nom des exécutables
SERVER = server
CLIENT = client

# Fichiers source
SERVER_SRC = main-core/server.c
CLIENT_SRC = main-core/client.c

# Fichiers objets
SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

# Chemin vers la bibliothèque libft
LIBFT_PATH = libft/
LIBFT = $(LIBFT_PATH)/libft.a

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L$(LIBFT_PATH) -lft

# Règle par défaut
all: $(SERVER) $(CLIENT)

# Compilation du serveur
$(SERVER): $(SERVER_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o ./$(SERVER) $(SERVER_OBJ) $(LDFLAGS)

# Compilation du client
$(CLIENT): $(CLIENT_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o ./$(CLIENT) $(CLIENT_OBJ) $(LDFLAGS)

# Règle pour nettoyer les fichiers objets
clean:
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ)

# Règle pour nettoyer les fichiers objets et les exécutables
fclean: clean
	rm -f ./$(SERVER) ./$(CLIENT)

# Règle pour recompiler tout
re: fclean all

.PHONY: all clean fclean re

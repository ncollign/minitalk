# Nom des exécutables
SERVER = server
CLIENT = client

# Fichiers source
SERVER_SRC = server.c
CLIENT_SRC = client.c

# Fichiers objets
SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Règle par défaut
all: $(SERVER) $(CLIENT)

# Compilation du serveur
$(SERVER): $(SERVER_OBJ)
	$(CC) $(CFLAGS) -o ./$(SERVER) $(SERVER_OBJ)

# Compilation du client
$(CLIENT): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o ./$(CLIENT) $(CLIENT_OBJ)

# Règle pour nettoyer les fichiers objets
clean:
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ)

# Règle pour nettoyer les fichiers objets et les exécutables
fclean: clean
	rm -f ./$(SERVER) ./$(CLIENT)

# Règle pour recompiler tout
re: fclean all

.PHONY: all clean fclean re
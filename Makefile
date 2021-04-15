GAME_LIBS=-lm
CLIENT_LIBS=-lSDL2 -ldl -lGL -lSDL2_image

GAME_INCLUDES=-I./
CLIENT_INCLUDES=-I./glad/include

FLAGS=-g -std=c99 -Wall -Wextra

GAME_SRC=game/*.c game/*/*.c math/*.c utils/*.c
CLIENT_SRC=glad/src/*.c client/main.c client/*/*.c

#lol this is kind of an abomination? idk
anura_client:
	gcc $(FLAGS) $(GAME_LIBS) $(GAME_INCLUDES) $(CLIENT_INCLUDES) $(CLIENT_LIBS) $(GAME_SRC) $(CLIENT_SRC)

anura_client_windows:
	x86_64-w64-mingw32-gcc $(FLAGS) $(GAME_LIBS) $(GAME_INCLUDES) $(CLIENT_INCLUDES) $(CLIENT_LIBS) $(GAME_SRC) $(CLIENT_SRC)

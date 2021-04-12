anura_client:
	gcc -g -lm -lSDL2 -std=c99 -Wall -Wextra -I./ game/*.c game/*/*.c math/*.c utils/*.c client/nographics.c

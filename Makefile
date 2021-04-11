anura_client:
	gcc -g -lm -lSDL2 -std=c99 -Wall -Wextra -I./ lib/*.c math/*.c client/*.c

# philosophers


Replace in the Makefile:
CFLAGS = -Wall -Wextra -Werror
for
CFLAGS = -g -Wall -Wextra -Werror -L. -lpthread -g3 -fsanitize=thread -O3 -march=native

to check for data races and mutex errors

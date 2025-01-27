.PHONY: vt_cat

COMP=gcc
CFLAGS=-c -Wall -Werror -Wextra
# CFLAGS2=-g -fsanitize=address -Wall -Werror -Wextra -std=c11
SOURCES =main.c output.c parser.c ../common/errors.c
OBJECTS =$(SOURCES:.c=.o)
EXECUTABLE =vt_cat

vt_cat:

$(EXECUTABLE): $(OBJECTS)
	$(COMP) $^ -o $@
	make clean_obj
.c.o:
	$(COMP) $(CFLAGS) $< -o $@
clean_obj:
	rm -rf $(OBJECTS)
clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
rebuild:
	make clean s21_cat
test:
	bash test.sh

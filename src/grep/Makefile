.PHONY: vt_grep

COMP=gcc
CFLAGS=-c -Wall -Werror -Wextra
SOURCES =main.c output_grep.c parser_grep.c ../common/errors.c
OBJECTS =$(SOURCES:.c=.o)
EXECUTABLE =vt_grep

vt_grep:

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
	make clean s21_grep
test:
	bash test.sh

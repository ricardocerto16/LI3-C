CC = gcc
CFLAGS = -Wall -std=c11 -g `xml2-config --cflags --libs` 
LIBS = `pkg-config --libs libxml-2.0` `pkg-config --libs glib-2.0`

OBJECTS = obj/program.o obj/avl.o obj/interface.o obj/parser.o \
		  obj/array.o obj/heap.o obj/interpretador.o \

#$(INSTTOOL) -m 755 bin/doxytag    $(INSTALL)/bin

DOC = doc/Doxyfile


program:
	$(CC) $(CFLAGS) program.c src/interface.c src/array.c src/parser.c src/avl.c src/heap.c src/interpretador.c -o program $(LIBS)

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -o $@ -c $<	

obj/program.o: interface.h
obj/avl.o: src/headers/avl.h interface.h src/headers/heap.h
obj/array.o: src/headers/array.h 
obj/heap.o: src/headers/heap.h 
obj/interface.o: interface.h src/headers/parser.h src/headers/avl.h src/headers/heap.h src/headers/array.h src/headers/interpretador.h
obj/interpretador.o: src/headers/interpretador.h src/headers/heap.h src/headers/avl.h \
					 interface.h src/headers/parser.h src/headers/array.h
obj/parser.o: src/headers/avl.h src/headers/heap.h interface.h  


clean:
	rm program

.PHONY: doc
doc:$(OBJECTS)
		doxygen $(DOC)

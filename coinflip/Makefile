CC = gcc
CFLAGS = -g -O2 -Wall -pedantic

PLOTTER = gnuplot
PLOTNAME = makeplot

SOURCES := coinflip.c
SOURCES += bits.c

OBJECTS := $(SOURCES:.c=.o)
DEPENDS := $(SOURCES:.c=.d)

EXEC = cf

all: $(EXEC)

$(EXEC): depends $(OBJECTS)
	$(CC) $(CXXFLAGS) -o $(EXEC) $(OBJECTS)

%.d : %.c
	$(CC) -MM -E $< -o $@

depends: $(DEPENDS)

-include $(DEPENDS)

# Execute the program with default parameters
# and run PLOTTER on the resulting plot file
plot: $(EXEC)
	./$(EXEC) -c -d -n 500 -t "Make Plot" $(PLOTNAME)
	$(PLOTTER) $(PLOTNAME).plot
	rm -f $(PLOTNAME).plot $(PLOTNAME).data

.PHONY: print
print:
	@echo "SOURCES: $(SOURCES)"
	@echo "OBJECTS: $(OBJECTS)"
	@echo "DEPENDS: $(DEPENDS)"

.PHONY: clean
clean:
	@rm -f *.o *.d tags
	@rm -f *.plot *.data *.png
	@rm -f $(EXEC)



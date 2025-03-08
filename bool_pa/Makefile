IDIR = ./include
SDIR = ./src
ODIR = ./obj
BDIR = ./bin

CC = clang
CFLAGS = -I$(IDIR) -fopenmp -O3
LIBS = -lm -lgsl -lgslcblas -lstdc++

_DEPS = pa_class.h ising_class.h functions.h params.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_SRC = main.cpp pa_class.cpp ising_class.cpp functions.cpp
OBJ = $(patsubst %.cpp,$(ODIR)/%.o,$(_SRC))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BDIR)/main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(BDIR)/main *~ core $(IDIR)/*~


#-----------------
#constants

CXXFLAGS=-std=c++11 -Wall -Wextra -pedantic -Wno-long-long -O0 -ggdb -D__PROGTEST__
CLIBS=-lexif
CXX=g++
RM=rm -rf
OBJDIR=obj
SRCDIR=src
DOXY=Doxyfile
BIN=./hajtopet

OBJECTS=$(OBJDIR)/main.o $(OBJDIR)/CCLI.o $(OBJDIR)/CDatabase.o $(OBJDIR)/CDatabaseEntry.o $(OBJDIR)/CException.o $(OBJDIR)/CImage.o $(OBJDIR)/CJPEGImage.o $(OBJDIR)/CMedia.o $(OBJDIR)/CPNGImage.o $(OBJDIR)/CTextFile.o $(OBJDIR)/CUI.o $(OBJDIR)/CVideo.o

#-----------------


#generate final binary and documentation
all: $(OBJECTS) $(DOXY)
	make compile
	make doc


#build all objects and merge them into final binary
compile: $(BIN)


#run program with test input
run: $(BIN)
	$(BIN) < examples/run.txt


#delete all folders with binary files (including documentation)
clean:
	$(RM) $(OBJDIR) doc $(BIN) example-database.txt


#documentation 
doc:
	doxygen $(DOXY)


#final binary
$(BIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(BIN) $(CLIBS)


#object files - general rule
$(OBJDIR)/%o: src/%cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $< 


#dependencies
$(OBJDIR)/CCLI.o: src/CCLI.cpp src/CCLI.h src/CUI.h src/CDatabase.h src/CDatabaseEntry.h src/constants.h src/CException.h

$(OBJDIR)/CDatabase.o: src/CDatabase.cpp src/CDatabase.h src/CDatabaseEntry.h src/CJPEGImage.h src/CImage.h src/CMedia.h src/CPNGImage.h src/CTextFile.h src/constants.h src/CException.h src/CVideo.h

$(OBJDIR)/CDatabaseEntry.o: src/CDatabaseEntry.cpp src/CDatabaseEntry.h

$(OBJDIR)/CException.o: src/CException.cpp src/CException.h

$(OBJDIR)/CImage.o: src/CImage.cpp src/CImage.h src/CMedia.h src/CDatabaseEntry.h

$(OBJDIR)/CJPEGImage.o: src/CJPEGImage.cpp src/CJPEGImage.h src/CImage.h src/CMedia.h src/CDatabaseEntry.h src/constants.h

$(OBJDIR)/CMedia.o: src/CMedia.cpp src/CMedia.h src/CDatabaseEntry.h

$(OBJDIR)/CPNGImage.o: src/CPNGImage.cpp src/CPNGImage.h src/CImage.h src/CMedia.h src/CDatabaseEntry.h src/constants.h

$(OBJDIR)/CTextFile.o: src/CTextFile.cpp src/CTextFile.h src/CDatabaseEntry.h src/constants.h

$(OBJDIR)/CUI.o: src/CUI.cpp src/CUI.h

$(OBJDIR)/CVideo.o: src/CVideo.cpp src/CVideo.h src/CDatabaseEntry.h src/CMedia.h src/constants.h

$(OBJDIR)/main.o: src/main.cpp src/CCLI.h src/CUI.h src/CDatabase.h src/CDatabaseEntry.h src/constants.h



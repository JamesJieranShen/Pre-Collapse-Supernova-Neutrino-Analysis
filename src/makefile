.PHONY:	clean

IDIR =../include
CC=g++
CFLAGS=-I$(IDIR) -g  -std=c++0x

ODIR=obj

_DEPS_HIST = makeHist.h katoRead.h katoReadGLoBES.h spectrumRead.h TwoDtoOneD.h splineFitTH1D.h splineFitTH2D.h clearBins.h fillHistogram.h duneRead.h junoRead.h hyperkRead.h createGlobesFile.h energyIntegral.h 
DEPS_HIST = $(patsubst %,$(IDIR)/%,$(_DEPS_HIST))

_OBJ_HIST = analysis.o makeHist.o katoRead.o katoReadGLoBES.o spectrumRead.o TwoDtoOneD.o splineFitTH1D.o splineFitTH2D.o clearBins.o fillHistogram.o duneRead.o junoRead.o hyperkRead.o createGlobesFile.o energyIntegral.o 
OBJ_HIST = $(patsubst %,$(ODIR)/%,$(_OBJ_HIST))

analysis: $(OBJ_HIST) # default
	g++ -g -o $@.o $^  $(CFLAGS) `root-config --glibs --libs`

$(ODIR)/%.o: %.cpp $(DEPS_HIST)
	mkdir -p $(ODIR);
	$(CC) -c -o $@ $< $(CFLAGS) `root-config --cflags --glibs --libs`

clean:
	rm -r *.o $(ODIR)
CC= g++
CFLAGS= -g3 -O2 -fPIC -Wall
DEMO= demo.exe demoCreateConfig.exe
HEPMCLIBS= -L$(HEPMCLOCATION)lib -lHepMC
PYTHIALIBS= -L$(PYTHIALOCATION)lib -lpythia8 -llhapdfdummy -lpythia8tohepmc

all:
	$(CC) $(CFLAGS) -c demo.cpp -o demo.o -I$(PYTHIALOCATION)include -I$(HEPMCLOCATION)include -I ./src
	$(CC) $(CFLAGS) -c demoCreateConfig.cpp -o demoCreateConfig.o -I$(PYTHIALOCATION)include -I$(HEPMCLOCATION)include -I ./src
	$(CC) demo.o -o demo.exe ./src/libAcerDET.so $(PYTHIALIBS) $(HEPMCLIBS) -Wl,-rpath,$(PYTHIALOCATION)lib -Wl,-rpath,$(HEPMCLOCATION)lib
	$(CC) demoCreateConfig.o -o demoCreateConfig.exe ./src/libAcerDET.so $(PYTHIALIBS) $(HEPMCLIBS) -Wl,-rpath,$(PYTHIALOCATION)lib -Wl,-rpath,$(HEPMCLOCATION)lib

clean:
	rm -f *~ *.o *.exe *.a

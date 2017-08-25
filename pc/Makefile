
ifeq ($(shell uname), Linux)
	USBFLAGS = `libusb-config --cflags`
	USBLIBS = `libusb-config --libs`
	EXE_SUFFIX =
	OSFLAG = -D LINUX
else ifeq ($(shell uname), Darwin)
	USBFLAGS = `libusb-config --cflags`
	USBLIBS = `libusb-config --libs`
	EXE_SUFFIX =
	OSFLAG = -D MAC_OS -D_DARWIN_USE_64_BIT_INODE=1
else
	USBFLAGS = -I C:\tools\mingw64\opt\include -I C:\tools\mingw64\include 
	USBLIBS = -L C:\tools\mingw64\lib -L C:\tools\mingw64\opt\lib -lusb
	EXE_SUFFIX = .exe
	OSFLAG = -D WIN -static-libstdc++ -static-libgcc
endif

LIBS    = $(USBLIBS)
CFLAGS  = $(USBFLAGS) $(LIBS) -O -g $(OSFLAG)

CC=	g++
PROGRAM= send$(EXE_SUFFIX)
SOURCE= send.cpp

all: $(PROGRAM)

$(PROGRAM): $(SOURCE)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(SOURCE) $(USBLIBS)

clean:
	rm -f $(PROGRAM) *.o

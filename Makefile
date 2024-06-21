CFLAGS = -O2
CFLAGS += -I/usr/include/SDL2
CFLAGS += -I/usr/local/include/SDL2
CFLAGS += -I/opt/X11/include
CFLAGS += -DNDEBUG
CPPFLAGS = --std=c++11 ${CFLAGS}
CPP = g++ ${CPPFLAGS}
CC = gcc ${CFLAGS}
OBJECTS = nsf.o
OBJECTS += ppls.o
OBJECTS += sstream.o
OBJECTS += echo.o
OBJECTS += filter.o
OBJECTS += rconv.o
OBJECTS += nes_cpu.o
OBJECTS += nes_bank.o
OBJECTS += nes_mem.o
OBJECTS += nsf2_vectors.o
OBJECTS += ram64k.o
OBJECTS += detect.o
OBJECTS += nes_detect.o
OBJECTS += nsf2_irq.o
OBJECTS += nes_apu.o
OBJECTS += nes_dmc.o
OBJECTS += nes_fds.o
OBJECTS += nes_fme7.o
OBJECTS += nes_mmc5.o
OBJECTS += nes_n106.o
OBJECTS += nes_vrc6.o
OBJECTS += emu2149.o
OBJECTS += emu2212.o

all: nsfplay
	./nsfplay test.nsf

nsfplay: src/cli.cpp src/nsfplay.hpp ${OBJECTS}
	${CPP} -o nsfplay src/cli.cpp ${OBJECTS} -lSDL2

clean:
	rm -f ${OBJECTS}

nsf.o: ./src/xgm/player/nsf/nsf.cpp
	${CPP} -c $<

ppls.o: ./src/xgm/player/nsf/pls/ppls.cpp
	${CPP} -c $<

sstream.o: ./src/xgm/player/nsf/pls/sstream.cpp
	${CPP} -c $<

echo.o: ./src/xgm/devices/Audio/echo.cpp
	${CPP} -c $<

filter.o: ./src/xgm/devices/Audio/filter.cpp
	${CPP} -c $<

rconv.o: ./src/xgm/devices/Audio/rconv.cpp
	${CPP} -c $<

nes_cpu.o: ./src/xgm/devices/CPU/nes_cpu.cpp
	${CPP} -c $<

nes_bank.o: ./src/xgm/devices/Memory/nes_bank.cpp
	${CPP} -c $<

nes_mem.o: ./src/xgm/devices/Memory/nes_mem.cpp
	${CPP} -c $<

nsf2_vectors.o: ./src/xgm/devices/Memory/nsf2_vectors.cpp
	${CPP} -c $<

ram64k.o: ./src/xgm/devices/Memory/ram64k.cpp
	${CPP} -c $<

detect.o: ./src/xgm/devices/Misc/detect.cpp
	${CPP} -c $<

log_cpu.o: ./src/xgm/devices/Misc/log_cpu.cpp
	${CPP} -c $<

nes_detect.o: ./src/xgm/devices/Misc/nes_detect.cpp
	${CPP} -c $<

nsf2_irq.o: ./src/xgm/devices/Misc/nsf2_irq.cpp
	${CPP} -c $<

nes_apu.o: ./src/xgm/devices/Sound/nes_apu.cpp
	${CPP} -c $<

nes_dmc.o: ./src/xgm/devices/Sound/nes_dmc.cpp
	${CPP} -c $<

nes_fds.o: ./src/xgm/devices/Sound/nes_fds.cpp
	${CPP} -c $<

nes_fme7.o: ./src/xgm/devices/Sound/nes_fme7.cpp
	${CPP} -c $<

nes_mmc5.o: ./src/xgm/devices/Sound/nes_mmc5.cpp
	${CPP} -c $<

nes_n106.o: ./src/xgm/devices/Sound/nes_n106.cpp
	${CPP} -c $<

nes_vrc6.o: ./src/xgm/devices/Sound/nes_vrc6.cpp
	${CPP} -c $<

nes_vrc7.o: ./src/xgm/devices/Sound/nes_vrc7.cpp
	${CPP} -c $<

emu2149.o: ./src/xgm/devices/Sound/legacy/emu2149.c
	${CC} -c $<

emu2212.o: ./src/xgm/devices/Sound/legacy/emu2212.c
	${CC} -c $<

emu2413.o: ./src/xgm/devices/Sound/legacy/emu2413.c
	${CC} -c $<

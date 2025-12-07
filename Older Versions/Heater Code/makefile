CC=gcc
CFLAGS=-I.
DEPS = 
OBJ1 = mcp9808.o read_temperature.o
OBJ2 = heater.o start_heater.o
OBJ3 = heater.o stop_heater.o
OBJ4 = mcp3021.o read_battery_voltage.o
OBJ5 = mcp9808.o mcp3021.o allsky_hw_log.o
OBJ6 = heater.o mcp9808.o mcp3021.o allsky_control_loop.o
OBJ7 = heater.o mcp9808.o mcp3021.o allsky_control_oneshot.o
OBJ8 = mcp3021.o read_battery_voltage_to_file.o


EXTRA_LIBS=-lm -lpigpio -lrt

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

read_temp: $(OBJ1)
	$(CC) -o $@ $^ $(CFLAGS) $(EXTRA_LIBS)

start_heater: $(OBJ2)
	$(CC) -o $@ $^ $(CFLAGS) $(EXTRA_LIBS)

stop_heater: $(OBJ3)
	$(CC) -o $@ $^ $(CFLAGS) $(EXTRA_LIBS)

read_battery_voltage: $(OBJ4)
	$(CC) -o $@ $^ $(CFLAGS) $(EXTRA_LIBS)

allsky_hw_log: $(OBJ5)
	$(CC) -o $@ $^ $(CFLAGS) $(EXTRA_LIBS)

allsky_control_loop: $(OBJ6)
	$(CC) -o $@ $^ $(CFLAGS) $(EXTRA_LIBS)

allsky_control_oneshot: $(OBJ7)
	$(CC) -o $@ $^ $(CFLAGS) $(EXTRA_LIBS)

read_battery_voltage_to_file: $(OBJ8)
	$(CC) -o $@ $^ $(CFLAGS) $(EXTRA_LIBS)
	

.PHONY: clean

clean:
	rm -f main $(OBJ1) $(OBJ2)

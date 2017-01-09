CFLAGS=-ldl -g
LDFLAGS=-

all: bf modules

modules: 
	cd mod && $(MAKE) && cp *.so ../modbins

clean: clean-modules
	rm *.o bf modbins/*.so

clean-modules:
	cd mod && $(MAKE) clean

bf: wm.o client.o modules.o emit.o handle.o
	gcc $(CFLAGS) -o $@ $^ -Wl,--export-dynamic

.PHONY: modules clean clean-modules

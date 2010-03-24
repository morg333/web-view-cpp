
SOURCES := $(wildcard *.cpp) $(wildcard *.c)

PRODUCT := cgi

PRODUCT_host := $(addsuffix _host, $(PRODUCT))
PRODUCT_target := $(addsuffix _target, $(PRODUCT))


all:
	g++ $(SOURCES) -o $(PRODUCT_host) -Os
	bfin-uclinux-g++ -Os $(SOURCES) -o $(PRODUCT_target) -elf2flt="-s 4096"
clean: 
	rm -f $(PRODUCT_host)
	rm -f $(PRODUCT_target)

	




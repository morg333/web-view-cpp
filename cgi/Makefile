


SOURCES := $(wildcard *.cpp) $(wildcard *.c)

PRODUCT_host := $(addsuffix _host, $(PRODUCT))
PRODUCT_target := $(addsuffix _target, $(PRODUCT))


all:
	g++ $(SOURCES) -o $(PRODUCT_host) -Os -D'APP_NAME="$(APP_NAME)"'
ifeq '$(CONFIG_BOARD)' 'raspi-cam'
	arm-linux-gnueabihf-g++ -Os $(SOURCES) -o $(PRODUCT_target) -D'APP_NAME="$(APP_NAME)"'
else
	bfin-uclinux-g++ -Os $(SOURCES) -o $(PRODUCT_target) -elf2flt="-s 4096" -D'APP_NAME="$(APP_NAME)"'
endif

clean: 
	rm -f $(PRODUCT_host)
	rm -f $(PRODUCT_target)

	




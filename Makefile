CFLAGS=-Wall -ggdb -I../../lib -I../../lib/cpp
LDFLAGS=-L../../lib ../../lib/cpp/libmosquittopp.so.1 ../../lib/libmosquitto.so.1

.PHONY: all clean

all : mqtt_led_new_state_sub

mqtt_led_new_state_sub : main.o mqtt_led_new_state_sub.o
	${CXX} $^ -o $@ ${LDFLAGS}

main.o : main.cpp
	${CXX} -c $^ -o $@ ${CFLAGS}

mqtt_led_new_state_sub.o : mqtt_led_new_state_sub.cpp
	${CXX} -c $^ -o $@ ${CFLAGS}

clean : 
	-rm -f *.o mqtt_led_new_state_sub

CC = gcc
CFLAGS = -fPIC -shared
INCLUDE = /opt/erlang/lib/erlang/usr/include/
LIBPATH = ../lib/
LIBNAME = splitairconditioning_ethnet_dsj_zhygzdn
TARGET = ../priv/splitairconditioning_ethnet_dsj_zhygzdn_nif.so

$(TARGET) : splitairconditioning_ethnet_dsj_zhygzdn_nif.o nif_util.o
	$(CC) $(CFLAGS) -o $@ $^ -I$(INCLUDE)  -L$(LIBPATH) -l$(LIBNAME)

splitairconditioning_ethnet_dsj_zhygzdn_nif.o : splitairconditioning_ethnet_dsj_zhygzdn_nif.c nif_util.h zjj_dll.h
	$(CC) $(CFLAGS) -I$(INCLUDE) -o $@ -c $<

nif_util.o : nif_util.c nif_util.h
	$(CC) $(CFLAGS) -I$(INCLUDE) -o $@ -c $<

clean :
	rm *.o $(TARGET)

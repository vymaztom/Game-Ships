# @Author: Tomas Vymazal <vymaztom>
# @Date:   2018-10-25T19:02:41+02:00
# @Email:  xvymaz11@vutbr.cz
# @Filename: Makefile
# @Last modified by:   vymaztom
# @Last modified time: 2018-10-29T22:11:17+01:00
# @License: MIT



CC=gcc
FLAGS=-O3 -Wall -ggdb -c

FFILE=files
FOBJECT=objects
CFILES:=main.c gui.c player.c game.c
OBJS:=$(CFILES:%.c=%.o)

define generate_file
	@rm -f objects/*
	@rmdir objects
	@mkdir objects
	@mv $(OBJS) objects
endef


all:$(OBJS)
	$(CC) $(OBJS) -o main
	$(call generate_file)

$(OBJS):$(CFILES)
	$(CC) $(FLAGS) $(CFILES)

run:
	./main

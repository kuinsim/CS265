#
# NOTES:
#		- I'm not in love w/this makefile, but, it works (as is), and has a couple interesting features.
#		- If switching from release to debug (or, vice versa), cleanall first
#

cc := gcc
ccflags = 
EXE := calc
DBG := calc.dbg
SRC := calc.c pushpop.c readtokn.c
OBJS = $(SRC:.c=.o)

.PHONY : clean cleanall debug


$(EXE) : $(OBJS)
	$(cc) $(ccflags) $^ -o $@

debug : ccflags += -DDEBUG -g
debug : $(EXE)

$(OBJS) : calc.h

%.o : %.c
	$(cc) -c $(ccflags) $<

clean :
	-\rm $(OBJS)

cleanall : clean
	-\rm $(EXE)
	-\rm $(DBG)


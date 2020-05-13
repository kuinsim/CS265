#Suin Kim
#6/8/2019

#CS265-005
#Assignment 3
#CD Database

PAGER = less

.PHONY : build clean view

build : cddb
	-@echo "Nothing much to do here. I did this in Python3. Granting execute permission to cddb."
	chmod +x $<

clean :  
	-@echo "Cleaning up all intermediate and resulting files and directories."
	rm sample.db.tmp 

view : 
	-@echo "Displaying source code in pager."
	$(PAGER) cddb 

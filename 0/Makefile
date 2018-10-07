MAIN := main


$(MAIN).exe: $(MAIN).c


%.exe: %.c
	gcc $< -mwindows -o $@


.PHONY: clean
clean:
	rm -f *.exe

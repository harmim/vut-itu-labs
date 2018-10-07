MAIN := main
PAINT := pait
KEYBOARD := keyboard


$(MAIN).exe: $(MAIN).c
$(PAINT).exe: $(PAINT).c
$(KEYBOARD).exe: $(KEYBOARD).c
$(MOUSE).exe: $(MOUSE).c


%.exe: %.c
	gcc $< -mwindows -o $@


.PHONY: clean
clean:
	rm -f *.exe

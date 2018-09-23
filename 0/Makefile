EXECUTABLE := main.exe

$(EXECUTABLE): main.c
	gcc $< -mwindows -o $@

.PHONY: clean
clean:
	rm -f $(EXECUTABLE)

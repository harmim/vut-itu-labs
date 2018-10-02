FILE := ex-design-xharmi00


$(FILE).pdf: $(FILE).tex
	pdflatex $<
	pdflatex $<


.PHONY: clean
clean:
	rm -f $(FILE).aux $(FILE).dvi $(FILE).log $(FILE).ps $(FILE).synctex.gz \
		$(FILE).fls $(FILE).fdb_latexmk $(FILE).out $(FILE).toc

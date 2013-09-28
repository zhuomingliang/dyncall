all: manual.pdf

manual.pdf:
	pdflatex manual.tex
	pdflatex manual.tex

clean:
	for i in pdf aux lof log lol lot out toc; do rm manual.$$i || true; done

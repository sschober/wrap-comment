SOURCES = $(wildcard *.cc)
TARGETS = $(patsubst %.cc,%,$(SOURCES))
CXX     = g++ --std=c++11

.PHONY: install

ALL:	$(TARGETS)

wrap-comment: wrap-comment.cc
align-on: align-on.cc
pad-parent: pad-paren.cc

clean:
	rm -f $(TARGETS)

install:
	cp $(TARGETS) ~/bin/

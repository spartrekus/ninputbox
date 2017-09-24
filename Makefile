
all:
	  tcc  -lncurses -lm ninputbox.c -o ninputbox    

run:
	  tcc  -lncurses -lm ninputbox.c -o ninputbox    ; ./ninputbox 
ed:
	  vim  ninputbox.c 




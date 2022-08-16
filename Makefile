ALLEGRO_VERSION=5.0.10
MINGW_VERSION=4.7.0
FOLDER=C:

FOLDER_NAME=\allegro-$(ALLEGRO_VERSION)-mingw-$(MINGW_VERSION)
PATH_ALLEGRO=$(FOLDER)$(FOLDER_NAME)
LIB_ALLEGRO=\lib\liballegro-$(ALLEGRO_VERSION)-monolith-mt.a
INCLUDE_ALLEGRO=\include

all: tenis.exe

tenis.exe: tenis.o
	gcc -o tenis.exe tenis.o $(PATH_ALLEGRO)$(LIB_ALLEGRO)

tenis.o: tenis.c
	gcc -I $(PATH_ALLEGRO)$(INCLUDE_ALLEGRO) -c tenis.c	


	
	
clean:
	del tenis.o
	del tenis.exe	


COMPILER = g++ -std=c++11
C_COMPILER = gcc
C_SWITCHES = -O -DLINUX -I/usr/X11R6/include -L/usr/X11R6/lib

ALLEGRO_PATH = /usr/include/allegro5
ALLEGRO_LIBRARIES_PATHS = -I $(ALLEGRO_PATH) 

BOX2D_PATH = /usr/local/include/box2d
BOX2D_LIBRARIES_PATHS = -I $(BOX2D_PATH) 

ALLEGRO_LIBRARIES = -I/usr/include/x86_64-linux-gnu -lallegro_image -lallegro_primitives -lallegro_ttf -lallegro_font -lallegro_acodec -lallegro_audio -lallegro
BOX2D_LIBRARIES = -lbox2d
LIBRARIES = $(ALLEGRO_LIBRARIES) $(BOX2D_LIBRARIES)
INCLUDES = $(ALLEGRO_LIBRARIES_PATHS) $(BOX2D_LIBRARIES_PATHS)

main: main.cpp GameObject GameScene Spawner Player Enemy Allegro Vec3
	$(COMPILER) main.cpp GameObject.o Spawner.o Player.o Enemy.o GameScene.o Allegro.o Vec3.o -o main $(LIBRARIES)

debug: main.cpp GameObject GameScene Spawner Player Enemy Allegro Vec3
	$(COMPILER) main.cpp GameObject.o Spawner.o Player.o Enemy.o GameScene.o Allegro.o Vec3.o -g -o main_debug $(LIBRARIES)

Spawner: Spawner.h
	$(COMPILER) $(LIBRARIES)  -c Spawner.cpp

Player: Player.h
	$(COMPILER) $(LIBRARIES)  -c Player.cpp

Enemy: Enemy.h
	$(COMPILER) $(LIBRARIES)  -c Enemy.cpp

GameObject: GameObject.h
	$(COMPILER) $(LIBRARIES)  -c GameObject.cpp

GameScene: GameScene.h 
	$(COMPILER) $(LIBRARIES)  -c GameScene.cpp 

Allegro: Allegro.h
	$(COMPILER) -I/usr/include/x86_64-linux-gnu -lallegro_font -lallegro_image -lallegro_primitives -lallegro $(ALLEGRO_LIBRARIES) -c Allegro.cpp

Vec3: Vec3.hpp
	$(COMPILER) $(LIBRARIES) -c Vec3.cpp

clean:
	rm main *.o

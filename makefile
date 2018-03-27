COMPILER = g++ -std=c++11
C_COMPILER = gcc
C_SWITCHES = -O -DLINUX -I/usr/X11R6/include -L/usr/X11R6/lib
TRILIBDEFS = -DTRILIBRARY -DANSI_DECLARATORS

ALLEGRO_PATH = /usr/local/include/allegro5
ALLEGRO_LIBRARIES_PATHS = -I $(ALLEGRO_PATH) 

BULLET_INCLUDE_PATH = /usr/local/include/bullet
BULLET_LINK_PATH = /usr/local/lib
BULLET_LIBRARIES_PATHS = -I$(BULLET_INCLUDE_PATH) -L$(BULLET_LINK_PATH) -Wl,-rpath=$(BULLET_LINK_PATH)

EIGEN_LIBRARIES = /usr/local/include/eigen3/
BULLET_LIBRARIES = -lBulletDynamics -lBulletCollision -lBulletSoftBody -lLinearMath
ALLEGRO_LIBRARIES = -lallegro -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec
LIBRARIES = $(BULLET_LIBRARIES) $(ALLEGRO_LIBRARIES)
INCLUDE_PATHS = $(BULLET_LIBRARIES_PATHS)

main: main.cpp GameObject GameScene Spawner Player Enemy Allegro SoftBody triangle
	$(COMPILER) $(C_SWITCHES) main.cpp GameObject.o Spawner.o Player.o Enemy.o SoftBody.o GameScene.o Allegro.o triangle.o -o main $(LIBRARIES) $(INCLUDE_PATHS) 

debug: main.cpp GameObject GameScene Spawner Player Enemy Allegro SoftBody triangle
	$(COMPILER) $(C_SWITCHES) main.cpp GameObject.o Spawner.o Player.o Enemy.o SoftBody.o GameScene.o Allegro.o triangle.o -g $(LIBRARIES) $(INCLUDE_PATHS) 

Spawner: Spawner.h
	$(COMPILER) $(LIBRARIES) $(INCLUDE_PATHS) -c Spawner.cpp

Player: Player.h
	$(COMPILER) $(LIBRARIES) $(INCLUDE_PATHS) -c Player.cpp

Enemy: Enemy.h
	$(COMPILER) $(LIBRARIES) $(INCLUDE_PATHS) -c Enemy.cpp

SoftBody: SoftBody.h
	$(COMPILER) $(LIBRARIES) $(INCLUDE_PATHS) -c SoftBody.cpp

GameObject: GameObject.h
	$(COMPILER) $(LIBRARIES) $(INCLUDE_PATHS) -c GameObject.cpp

GameScene: GameScene.h 
	$(COMPILER) $(LIBRARIES) $(INCLUDE_PATHS) -c GameScene.cpp 

Allegro: Allegro.h
	$(COMPILER) $(ALLEGRO_LIBRARIES) -c Allegro.cpp

trilibrary: triangle tricall

triangle: triangle.h
	$(COMPILER) $(C_SWITCHES) $(TRILIBDEFS) -c triangle.cpp 

tricall: tricall.c triangle
	$(C_COMPILER) $(C_SWITCHES) -o tricall tricall.c triangle.o -lm

clean:
	rm main *.o

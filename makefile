COMPILER = g++ -std=c++11
C_COMPILER = gcc
C_SWITCHES = -O -DLINUX -I/usr/X11R6/include -L/usr/X11R6/lib
TRILIBDEFS = -DTRILIBRARY
BULLET_LIBRARIES_PATHS = -I ~/bullet3/include/bullet -L ~/bullet3/lib#/usr/local/include/bullet
ALLEGRO_LIBRARIES_PATHS = -I ~/include/allegro5 -L ~/lib/allegro5#/usr/local/include/allegro5
EIGEN_LIBRARIES = /usr/local/include/eigen3/
BULLET_LIBRARIES = -lBulletDynamics -lBulletCollision -lBulletSoftBody -lLinearMath
ALLEGRO_LIBRARIES = -lallegro -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec
LIBRARIES = $(BULLET_LIBRARIES) $(ALLEGRO_LIBRARIES)
INCLUDE_PATHS = $(BULLET_LIBRARIES_PATHS)


main: main.cpp GameObject GameScene Spawner Player Enemy Allegro SoftBody trilibrary
	$(COMPILER) $(INCLUDE_PATHS) main.cpp GameObject.o Spawner.o Player.o Enemy.o SoftBody.o GameScene.o Allegro.o triangle.o -o main $(LIBRARIES)

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

triangle: triangle.c triangle.h
	$(C_COMPILER) $(C_SWITCHES) $(TRILIBDEFS) -c -o triangle.o triangle.c

tricall: tricall.c triangle
	$(C_COMPILER) $(C_SWITCHES) -o tricall tricall.c triangle.o -lm


clean:
	rm main *.o

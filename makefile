COMPILER = g++ -std=c++11
BULLET_LIBRARIES_PATHS = -I /usr/local/include/bullet
ALLEGRO_LIBRARIES_PATHS = -I /usr/local/include/allegro5
EIGEN_LIBRARIES = /usr/local/include/eigen3/
BULLET_LIBRARIES = -lBulletDynamics -lBulletCollision -lBulletSoftBody -lLinearMath
ALLEGRO_LIBRARIES = -lallegro -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec
LIBRARIES = $(BULLET_LIBRARIES) $(ALLEGRO_LIBRARIES)
INCLUDE_PATHS = $(BULLET_LIBRARIES_PATHS)


main: main.cpp GameObject GameScene Spawner Player Enemy Allegro SoftBody
	$(COMPILER) $(INCLUDE_PATHS) main.cpp GameObject.o Spawner.o Player.o Enemy.o SoftBody.o GameScene.o Allegro.o -o main $(LIBRARIES)

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

clean:
	rm main *.o

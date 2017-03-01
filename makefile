COMPILER = g++ -std=c++11
BULLET_LIBRARIES_PATHS = -I /usr/local/include/bullet
EIGEN_LIBRARIES = /usr/local/include/eigen3/
BULLET_LIBRARIES = -lBulletDynamics -lBulletCollision -lBulletSoftBody -lLinearMath
LIBRARIES = $(BULLET_LIBRARIES)
INCLUDE_PATHS = $(BULLET_LIBRARIES_PATHS)


main: main.cpp GameObject GameScene
	$(COMPILER)  $(INCLUDE_PATHS) main.cpp GameObject.o GameScene.o -o main $(LIBRARIES)

GameObject: GameObject.h
	$(COMPILER) $(LIBRARIES) $(INCLUDE_PATHS) -c GameObject.cpp

GameScene: GameScene.h
	$(COMPILER) $(LIBRARIES) $(INCLUDE_PATHS) -c GameScene.cpp

clean:
	rm main *.o

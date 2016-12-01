#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum {LEFT, RIGHT, UP, DOWN, CENTER} Direction;
typedef enum {SMALL, BASE, FIRE, SSJ} Form;
typedef enum {NONE, JUMP, DIE, GOOMBA, WIN} Sound;

typedef struct Input {
  int x, y;
  bool a, b;
} Input;

typedef struct Image {
  int h, w;
  const unsigned char* pixels;
} Image;

typedef struct Frame {
  int h, w;
  unsigned char* pixels;
  Sound sound;
} Frame;

typedef struct Entity {
  int x, y;
  Image* image;
  bool mirror;
} Entity;

typedef struct Shroom {
	Entity entity;
	int dy;
	bool eaten;
} Shroom;

typedef struct Player {
  Entity entity;
  int dy, dx, vx, vy, hp, refresh;
  bool jumping, sprint;
} Player;

typedef struct Enemy {
  Entity entity;
	int smashCounter, dy;
} Enemy;

typedef struct Block {
  //TODO: smashable, item, smashed, visible, etc.
  Entity entity;
} Block;

typedef struct Scenery {
  Entity entity;
} Scenery;

//Screen Vars
#define SCREEN_H 128
#define SCREEN_W 160

//Input: player input
//Output: next frame (160x128), sound effect
Frame Next_Frame(Input input);

//Input: none
//Output: none
//Initializes a new game
void Init_Game(void);

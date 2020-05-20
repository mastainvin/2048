/*
title : Header of the library shape2d
autor : Mastain Vincent
date : 05/18/2020
*/
#ifndef SHAPE2D_H
#define SHAPE2D_H

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#define SHP_FRAME_PER_SECOND 60

typedef enum SHP_bool
{
	false,
	true
} SHP_bool;

// Structures
typedef struct SHP_Sprite
{
	SDL_Rect background;
	SDL_Color background_color;
	SHP_bool withText;
	char text[100];
	SDL_Color text_color;
	int text_size;
} SHP_Sprite;

// Functions protoype
void SHP_PrintSprite(SHP_Sprite sprite, SDL_Renderer *renderer);
void SHP_Limit_FPS(unsigned int limit);

#endif
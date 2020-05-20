/*
title : Functions of the library shape2d
autor : Mastain Vincent
date : 05/18/2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "shape2d.h"

void SHP_PrintSprite(SHP_Sprite sprite, SDL_Renderer *renderer)
{
	/* display of the rectangle and the text if it exists in its center */

	// rectangle
	if (SDL_SetRenderDrawColor(renderer, sprite.background_color.r, sprite.background_color.g, sprite.background_color.b, 255) != 0)
	{
		printf("Error : SDL_SetRenderDrawColor -> %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	if (SDL_RenderFillRect(renderer, &sprite.background) != 0)
	{
		printf("Error : SDL_SetRenderDrawColor -> %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	// If the text exist we display in the center the text with his color
	if (sprite.withText)
	{
		SDL_Surface *text_surface = NULL;
		SDL_Texture *text_texture = NULL;

		TTF_Font *font = TTF_OpenFont("arial.ttf", sprite.text_size);

		if (font == NULL)
		{
			printf("Error : TTF_OpenFont -> %s\n", TTF_GetError());
			exit(EXIT_FAILURE);
		}
		text_surface = TTF_RenderUTF8_Blended(font, sprite.text, sprite.text_color);
		if (text_surface == NULL)
		{
			printf("Error -> %s\n", TTF_GetError());
			exit(EXIT_FAILURE);
		}
		text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
		SDL_FreeSurface(text_surface);

		if (text_texture == NULL)
		{
			printf("Error : SDL_CreateTextureFromSurface -> %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}

		SDL_Rect text_position;

		if (SDL_QueryTexture(text_texture, NULL, NULL, &text_position.w, &text_position.h) != 0)
		{
			printf("Error : SDL_QueryTexture -> %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		text_position.x = sprite.background.x + (sprite.background.w - text_position.w) / 2;
		text_position.y = sprite.background.y + (sprite.background.h - text_position.h) / 2;

		SDL_RenderCopy(renderer, text_texture, NULL, &text_position);
		TTF_CloseFont(font);
		SDL_DestroyTexture(text_texture);
	}
}

void SHP_Limit_FPS(unsigned int limit)
{
	unsigned int tick = SDL_GetTicks();
	unsigned int period = 1000 / SHP_FRAME_PER_SECOND;

	if (limit > tick + period)
	{
		SDL_Delay(period);
	}
	else
	{
		SDL_Delay(limit - tick);
	}
}
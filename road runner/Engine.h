#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

#include <fstream>
class Engine
{
public:
	Engine(void);
	~Engine(void);

	int init();
	void render();
	void get_input();
	void render_sprite(SDL_Surface* scr,int x, int y);
	SDL_Surface *load_image( const char * filename );
	bool check_collision( SDL_Rect A, SDL_Rect B );

	SDL_PixelFormat * get_format();

	bool quit;
	SDL_Event event;

	int high_score;

	TTF_Font * font;

private:
	SDL_Surface* screen;
	SDL_Rect rect;

};


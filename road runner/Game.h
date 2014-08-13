#pragma once
#include <SDL.h>
#include <SDL_mixer.h>

class Game
{
public:
	Game(void);
	~Game(void);

	void render();
	void loop();
	void events();
	void reset();


	bool gameover;
	int pos;
private:
	int speed;
	SDL_Surface* Lava;
	SDL_Surface* player;
	SDL_Surface* bg;
	SDL_Surface* warning;
	SDL_Surface* Block;

	Mix_Chunk* Jump_Sound;

	bool right;

	int block_type;

	SDL_Color black, white;

	SDL_Rect player_rect;
	SDL_Rect block_rect;
	SDL_Rect Lava_rect;

	int player_speed;
	int jump_force;

	int time_to_block;     

	int bgX;
	int last_time;
};


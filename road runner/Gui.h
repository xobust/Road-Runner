#pragma once
#include <SDL.h>
class Gui
{
public:
	Gui(void);
	~Gui(void);

	void Render_Start_Screen();

	void Render_Menu_screen();

	void Render_howto();

	void Render_Gameover();

	const char * texts [15];

	SDL_Color black, white;
private:
	SDL_Surface* start_screen;
	int last_time;
	
};


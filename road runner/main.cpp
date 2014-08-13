// Line Runner.cpp : main project file.
#include "stdafx.h"
#include "stdafx.h"
#include "Engine.h"
#include "Game.h"
#include "Gui.h"

Game * game;
Gui * gui;
Engine * engine;


int main(int argc, char **argv) {
	engine = new Engine;
	engine->init();
	gui = new Gui;
	gui->Render_Start_Screen();

	game = new Game;

	while (!engine->quit)
	{
		game->reset();
		while(true)
		{
			game->render();
			gui->Render_Menu_screen();

			char str[30];
			sprintf(str, "hig score : %d", engine->high_score);
			engine->render_sprite(TTF_RenderText_Blended(engine->font,str,gui->white), 400,50);

			engine->render();
			engine->get_input();

			if (engine->event.type == SDL_KEYDOWN)
			{
				if (engine->event.key.keysym.sym == SDLK_1)
				{
					engine->render();
					game->render();
					engine->render_sprite(TTF_RenderText_Blended(engine->font,"Ready",gui->white),400,300);
					engine->render();
					SDL_Delay(1000);
					game->render();
					engine->render_sprite(TTF_RenderText_Blended(engine->font,"Set",gui->white),400,300);
					engine->render();
					SDL_Delay(2000);
					break;
				}else if (engine->event.key.keysym.sym == SDLK_2)
				{
					gui->Render_howto();
				}else if (engine->event.key.keysym.sym == SDLK_3)
				{
					engine->quit = true;
					game->gameover = true;
					break;
				}
			}


			SDL_Delay(10);
		}
	while (!game->gameover)
	{

		engine->render();
		engine->get_input();

		game->render();
		game->loop();


		SDL_Delay(10);
	}
	}

    return 0;
}

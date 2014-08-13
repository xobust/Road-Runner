#include "StdAfx.h"
#include "Gui.h"

#include "Engine.h"
#include "Game.h"

#include "fastevents.h"

extern Engine * engine;
extern Game * game;

using namespace std;

Gui::Gui(void)
{
	start_screen = IMG_Load("start_screen.png");


	white.b = 255;
	white.r = 255;
	white.g = 255;

	black.b = 0;
	black.r = 0;
	black.g = 0;


	texts[0] = "Story: ";
	texts[1] = "you're trying to escape from a volcano";
	texts[2] = "you dropped the car key's so you have to go for a run";
	texts[3] = "";
	texts[4] = "";

	texts[5] = "you use the WASD buttons to control the game play";
	texts[6] = "the W button is for jumping,";
	texts[7] = "use the A button to build up speed ";
	texts[8] = "the D Button is designed to give you an extra boost";
	texts[9] = "You use the S button to change track";

	texts[10] = "so now you know the controls lets go over the gameplay";
	texts[11] = "you start by mashing the A button to build up speed";
	texts[12] = "once you got 7000 you can start to combo A and D";
	texts[13] = "as son as you see the warning sign be careful";
	texts[14] = "the goal is to score as many points as possible";

}


Gui::~Gui(void)
{

	SDL_FreeSurface(start_screen);
}

void Gui::Render_Start_Screen()
{
	while(true)
	{
		engine->render_sprite(start_screen,0,0);
		engine->get_input();
		if (engine->event.type == SDL_KEYDOWN)
		if (engine->event.key.keysym.sym == SDLK_a || engine->event.key.keysym.sym == SDLK_d)
		{
			FE_WaitEvent(&engine->event);
			if (engine->event.key.keysym.sym == SDLK_a || engine->event.key.keysym.sym == SDLK_d)
				return;
		}

		engine->render();
		SDL_Delay(10);
	}
}

void Gui::Render_Menu_screen()
{
	engine->render_sprite(TTF_RenderText_Blended(engine->font,"1. Start game",white),400,200);
	engine->render_sprite(TTF_RenderText_Blended(engine->font,"2. credits",black),400,300);
	engine->render_sprite(TTF_RenderText_Blended(engine->font,"3. quit",black),400,400);
}

void Gui::Render_howto()
{
	int i;
	i = 0;

	last_time = SDL_GetTicks();

	SDL_Delay(500);
	while (i < 15)
	{	
		engine->render_sprite(TTF_RenderText_Blended(engine->font,texts[i],black),5,100);
		engine->render_sprite(TTF_RenderText_Blended(engine->font,texts[i+1],black),5,200);
		engine->render_sprite(TTF_RenderText_Blended(engine->font,texts[i+2],black),5,300);
		engine->render_sprite(TTF_RenderText_Blended(engine->font,texts[i+3],black),5,400);
		engine->render_sprite(TTF_RenderText_Blended(engine->font,texts[i+4],black),5,500);

		engine->render();
		engine->get_input();

		if(SDL_GetTicks() > (last_time + 10000) || engine->event.type == SDL_KEYDOWN)
		{
			i +=5;
			last_time = SDL_GetTicks();
		}
		SDL_Delay(100);
	}

	engine->event.key.keysym.sym = SDLK_DELETE;
}

void Gui::Render_Gameover()
{
	if (game->pos >= engine->high_score)
	{
		engine->high_score = game->pos;
		ofstream myfile("m.d");
		if (myfile.is_open())
		{
			myfile << engine->high_score;
			myfile.close();
		}
	}

	while (true)
	{
		game->render();

		if (engine->high_score == game->pos)
		{
			engine->render_sprite(TTF_RenderText_Blended(engine->font,"New Highscore :)",white),400,150);
		}

		engine->render_sprite(TTF_RenderText_Blended(engine->font,"1. retry",white),400,200);
		engine->render_sprite(TTF_RenderText_Blended(engine->font,"2. mainmenu",black),400,300);
		engine->render_sprite(TTF_RenderText_Blended(engine->font,"3. quit ",black),400,400);

		

		engine->render();
		engine->get_input();

		if (engine->event.type == SDL_KEYDOWN)
		{
			switch (engine->event.key.keysym.sym)
			{
			case SDLK_1:
				game->reset();
				engine->render();
				game->render();
				engine->render_sprite(TTF_RenderText_Blended(engine->font,"Ready",white),400,300);
				engine->render();
				SDL_Delay(1000);
				game->render();
				engine->render_sprite(TTF_RenderText_Blended(engine->font,"Set",white),400,300);
				engine->render();
				SDL_Delay(2000);
				return;

			case SDLK_2:
				game->gameover = true;
				SDL_Delay(1000);
				return;

			case SDLK_3:
				game->gameover = true;
				engine->quit = true;
				return;
			

			}
		}


		SDL_Delay(100);
	}
}





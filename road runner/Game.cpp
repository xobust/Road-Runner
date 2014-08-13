#include "StdAfx.h"
#include "Game.h"
#include "Engine.h"
#include "Gui.h"

extern Gui * gui;
extern Engine * engine;

Game::Game(void)
{

	bgX = 0;

	player_speed = 0;
	jump_force = 0;

	white.b = 255;
	white.r = 255;
	white.g = 255;

	black.b = 0;
	black.r = 0;
	black.g = 0;

	right = false;
	

	Lava = engine->load_image("lava.png");
	player = engine->load_image("player.png");
	bg = engine->load_image("bg1.png");
	warning = engine->load_image("warning.png");
	Block = engine->load_image("block.png");

	Jump_Sound = Mix_LoadWAV("jump.wav");

	player_rect.x = 400;
	player_rect.y = 500;
	player_rect.w = player->w;
	player_rect.h = player->h;

	block_rect.x = -10;
	block_rect.y = 500;
	block_rect.w = Block->w;
	block_rect.h = Block->h;

	Lava_rect.x = -400;
	Lava_rect.y = 0;
	Lava_rect.w = Lava->w;
	Lava_rect.h = Lava->h;

	pos = 0;

	last_time = SDL_GetTicks();
	time_to_block = rand()  %10000 + 1000;
	block_type = rand() %3;

	gameover = false;
}

void Game::reset()
{
	player_speed = 0;
	jump_force = 0;

	right = false;

	player_rect.x = 350;
	player_rect.y = 500;

	block_rect.x = -50;
	block_rect.y = 500;

	pos = 0;

	last_time = SDL_GetTicks();
	time_to_block = rand()  %10000 + 1000;
	block_type = rand() %3;

	gameover = false;
}

Game::~Game(void)
{
	SDL_FreeSurface(Lava);
	SDL_FreeSurface(player);
	SDL_FreeSurface(bg);
	SDL_FreeSurface(Block);
	SDL_FreeSurface(warning);
}



void Game::render()
{
	engine->render_sprite(bg,bgX,0);
	engine->render_sprite(bg,bgX + bg->w,0);
	engine->render_sprite(player,player_rect.x,player_rect.y);
	engine->render_sprite(Block,block_rect.x,block_rect.y);
	if (block_type == 2)
		engine->render_sprite(Block,block_rect.x,560);

	engine->render_sprite(Lava,Lava_rect.x,Lava_rect.y);

	if (time_to_block <500)
		engine->render_sprite(warning,700,300);

	if (pos > 0)
	{
		char str[30];
		sprintf(str, "score : %d", pos);
		engine->render_sprite(TTF_RenderText_Blended(engine->font,str,white), 400,100);
		
		if (pos < 500)
		{
			engine->render_sprite(TTF_RenderText_Blended(engine->font,"RUN !",white),400,300);
		}
	
	}

	if (pos > 7000 && pos < 7500)
		engine->render_sprite(TTF_RenderText_Blended(engine->font,"Faster !",white),400,300);

}

void Game::loop()
{
	events();

	if(SDL_GetTicks() > (last_time + 50))
	{
		if (time_to_block <= 0 && time_to_block >= -100)
		{
			block_rect.x = 800;
			block_rect.h = Block->h;
			if (block_type == 0)
				block_rect.y = 500;
			else if (block_type == 1)
				block_rect.y = 560;
			else
			{
				block_rect.y = 500;
				block_rect.h = Block->h	*2;
			}
		}

		if (block_rect.x > - 50)
			block_rect.x -= 30;
		if (time_to_block <= 0 && block_rect.x <= 0)
		{
			time_to_block = (rand()  %(10000 - (pos / 4)) + 500) ;
			block_type = rand() %3;
		}

		time_to_block -= 50 + player_speed / 2;

		if (jump_force ==  0 && player_rect.y <  500)
		{
			player_rect.y += 20;
			player_speed = 10;
		}
		if (player_rect.y >  550 - jump_force)
		{
			player_rect.y -=20;
			player_speed = 20;
		}
		else
			jump_force = 0;

		bgX -= player_speed + 120;

		if (engine->check_collision(player_rect,block_rect))
		{
			player_rect.x = block_rect.x - Block->w;
			pos -= 10;
		}else 
		{
		if (pos < 30000)
			player_speed -= (player_rect.x / 40 + pos / 3000);
		else
			player_speed -= (player_rect.x / 40 + 10);
			

		pos += (player_speed + 120)/ 20 ;

		player_rect.x +=  player_speed / 2;
		}

		if(pos <= 40000 )
			Lava_rect.x = (pos / 100)-400;
		else
			Lava_rect.x = 0;
		
		last_time = SDL_GetTicks();
	}

	if(engine->check_collision(player_rect,Lava_rect))
	{	
		gui->Render_Gameover();
		return;
	}

#pragma region Limitations
	if (jump_force < 0)
	{
		jump_force = 0;
	}
	if (player_speed < -40)
	{
		player_speed = -20;
	}
	if (player_speed > 200)
	{
		player_speed = 100;
	}
	if (player_rect.x < 0)
	{
		player_rect.x = 0;
	}
	if (player_rect.x > 700)
	{
		player_rect.x = 700;
	}
	//If the background has gone too far 
	if( bgX <= -bg->w ) 
	{ //Reset the offset 
		bgX = 0; 
	}
#pragma endregion Limitations

}

void Game::events()
{
	if (engine->event.type == SDL_KEYDOWN)
	{
	if (player_rect.y >= 500)
		{
		if (engine->event.key.keysym.sym == SDLK_a)
		{
			player_speed += 30;
			pos += 10;
			right = true;
		}
		if (engine->event.key.keysym.sym == SDLK_d)
			if (pos > 7000 && right == true)
			{
				player_speed += 40;
				pos += 10;
				right =false;
			}
			else
				player_speed -= 20;

		if (engine->event.key.keysym.sym == SDLK_w)
			if (jump_force == 0)
			{
				jump_force = 130 + player_speed /3;
				Mix_PlayChannel(-1, Jump_Sound, 0);
			}
			if (engine->event.key.keysym.sym == SDLK_s)
			{	
				if (player_rect.y == 500)
					player_rect.y = 550;
				else	
					player_rect.y = 500;
				player_speed -= 10;			
			}

		}
	if (engine->event.key.keysym.sym == SDLK_ESCAPE)
	{
		gui->Render_Gameover();
		return;
	}

		engine->event.key.keysym.sym = SDLK_DELETE;
	}
}



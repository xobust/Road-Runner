#include "StdAfx.h"
#include "Engine.h"

#include "fastevents.h"

using namespace std;



Engine::Engine(void)
{
	high_score = 0;
	quit = false;
}

Engine::~Engine(void)
{
	TTF_CloseFont(font);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

int Engine::init()
{
	if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) != 0 ) {
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return -1;
	}

	FE_Init();

	TTF_Init();

	srand(SDL_GetTicks()); 

	atexit(SDL_Quit);

	font = TTF_OpenFont("PressStart2P.ttf",12);

	SDL_WM_SetCaption("Line runner", "");

	if(Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096) != 0) {
		fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());
		return -3;
	}

	screen = SDL_SetVideoMode(800, 600, 32, SDL_DOUBLEBUF);
	if (!screen)
	{
		printf("Unable to set %ix%i video: %s\n", 800, 600, SDL_GetError());
		return -2;
	}
	ifstream hf("m.d");
	char output[100];
	if (hf.is_open())
	{
		hf >> output;
		high_score = atoi(output);
	}
	hf.close();


	return 0;

}

void Engine::render()
{
	SDL_Flip(screen);
	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 255, 255, 255));
}

void Engine::get_input()
{
	FE_PollEvent(&event);
	
	if (event.type ==  SDL_QUIT)
	{
		exit(0);
	}

}

void Engine::render_sprite( SDL_Surface* scr,int x, int y )
{
	rect.x = x;
	rect.y = y;
	SDL_BlitSurface(scr,NULL,screen,&rect);
}

SDL_PixelFormat * Engine::get_format()
{
	return screen->format;
}

SDL_Surface * Engine::load_image( const char * filename ) { 
	//The image that's loaded 
	SDL_Surface* loadedImage = NULL;
	//The optimized image that will be used 
	SDL_Surface* optimizedImage = NULL; 
	//Load the image 
	loadedImage = IMG_Load( filename ); 
	//If the image loaded 
	if( loadedImage != NULL ) { 
		//Create an optimized image 
		optimizedImage = SDL_DisplayFormat( loadedImage ); 
		//Free the old image 
		SDL_FreeSurface( loadedImage );

		//If the image was optimized just fine 
		if( optimizedImage != NULL ) { 
			//Map the color key 
			Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF );
		
		//Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent 
			SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
		}
	}

	//Return the optimized image 
	return optimizedImage; 
} 

bool Engine::check_collision( SDL_Rect A, SDL_Rect B ) 
{
	//The sides of the rectangles 
	int leftA, leftB; 
	int rightA, rightB; 
	int topA, topB; 
	int bottomA, bottomB; 
	//Calculate the sides of rect A 
	leftA = A.x; 
	rightA = A.x + A.w; 
	topA = A.y; 
	bottomA = A.y + A.h; 
	//Calculate the sides of rect B 
	leftB = B.x; 
	rightB = B.x + B.w; 
	topB = B.y; 
	bottomB = B.y + B.h;

	//If any of the sides from A are outside of B 
	if( bottomA <= topB ) 
	{ 
		return false; 
	} 
	if( topA >= bottomB ) 
	{ 
		return false; 
	} 
	if( rightA <= leftB ) 
	{ 
		  return false; 
	} 
	if( leftA >= rightB ) 
	{ 
		return false; 
	} 
	//If none of the sides from A are outside B 
	return true;
}
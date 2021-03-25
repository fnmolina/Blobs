#ifndef VIEWER_H
#define VIEWER_H
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include "Blob.h"
#include "Food.h"
#include <string>



//display size
#define DISP_W 900
#define DISP_H 570
#define BACKGROUND_VERTICAL_LIMIT 470



using namespace std;


class viewer
{
public:
	viewer();
	~viewer();
	int init_allegro(void);
	void close_allegro(void);
	void refresh(Blob* blobs, int blobMaxRange, Food*food, int foodCount);
	void update_display(void);
	void PrintText(string text);

	ALLEGRO_DISPLAY *display;
	ALLEGRO_BITMAP *background;
	ALLEGRO_BITMAP *food;
	ALLEGRO_BITMAP *baby;
	ALLEGRO_BITMAP *blob;
	ALLEGRO_BITMAP *old;
	ALLEGRO_FONT* font;
	bool error;
};

#endif // !VIEWER_H
#include "viewer.h"
#include "Point.h"
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_color.h>
#include "resources.h"


viewer::viewer() //Inicializo miembros, Constructor NO PUEDE FALLAR.
{
	display = nullptr;
	background = nullptr;
	food = nullptr;
	baby = nullptr;
	blob = nullptr;
	old = nullptr;
	font = nullptr;
	error = false;
}

int viewer::init_allegro() { //Inicialización, si puede fallar, devuelve error y lo cataloga en "error". Booleano devuelve false si no hay error.

	if (al_init()) { //Even if al_init is called outside the viewer for IMGUI, it won't cause problems, this is for the sake of code independency.
		if (al_init_image_addon()) {
			if (al_init_primitives_addon()) { //Same as al_init, this can potentially be used to draw smellradius, direction and bitmap boundaries for debbugging.
				if (al_init_font_addon()) {
					if (al_init_ttf_addon()) {
						//create display
						display = al_create_display(DISP_W, DISP_H);
						if (!!display) {
							//load images
							background = al_load_bitmap(BACKGROUND);
							food = al_load_bitmap(FOOD_SPRT);
							baby = al_load_bitmap(BABY_SPRT);
							blob = al_load_bitmap(BLOB_SPRT);
							old = al_load_bitmap(OLD_SPRT);
							font = al_load_ttf_font(FONT, FONT_SIZE, 0);
							if (!!background && !!food && !!baby && !!blob && !!old && !!font) {
								return error;
							}else { error = true; printf("Failed to load image/s!\n"); }
							al_destroy_display(display);
						}else { error = true; printf("Failed to create display!\n"); }
						al_shutdown_ttf_addon();
					}
					else { error = true; printf("Failed to initialize ttf Add-On!\n"); }
					al_shutdown_font_addon();
				}
				else { error = true; printf("Failed to initialize Font Add_on!\n"); }
				al_shutdown_primitives_addon();
			}
			else { error = true; printf("Failed to initialize primitives Add_on!\n"); }
			al_shutdown_image_addon();
		}
		else { error = true; printf("Failed to initialize image Add-on!\n"); }
	}
	else { error = true; printf("Failed to initialize Allegro!\n"); }
	return error;
}


viewer::~viewer()
{
	close_allegro();
}

void viewer::close_allegro(void)
{
	if (!!background) {
		al_destroy_bitmap(background);
		background = nullptr;
	}
	if (!!food){
		al_destroy_bitmap(food);
		food = nullptr;
	}
	if (!!blob){
		al_destroy_bitmap(blob);
		blob = nullptr;
	}
	if (!!baby){
		al_destroy_bitmap(baby);
		baby = nullptr;
	}
	if (!!old){
		al_destroy_bitmap(old);
		old = nullptr;
	}
	if (!!display) {
		al_destroy_display(display);
		display = nullptr;
	}
	if (!!font) {
		al_destroy_font(font);
		font = nullptr;
	}	
	al_shutdown_ttf_addon();					
	al_shutdown_font_addon();				
	al_shutdown_primitives_addon();			
	al_shutdown_image_addon();	
}

void viewer::update_display(void)
{
	al_flip_display();
}

void viewer::refresh(Blob* blobs, int blobMaxRange, Food*foods,int foodCount)
{
	// funcion a corregir definicion
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_bitmap(background, 0, 0, 0);
	
	//al_draw_bitmap(food, x, y, 0); Draw all the food.
	for (int i = 0; i < foodCount; i++) {
		al_draw_bitmap(food, (foods[i].position.x/*DISP_W*/)-FOOD_BITMAP_SIZE/2, (foods[i].position.y/*DISP_H*/)- FOOD_BITMAP_SIZE / 2, 0);
	}
	//al_draw_bitmap(baby, x, y, 0); Draw all the blobs!
	//al_draw_bitmap(blob, x, y, 0);
	//al_draw_bitmap(old, x, y, 0);
	for (int i = 0; i <= blobMaxRange; i++) {
		switch (blobs[i].etaryGroup) {
		case BABY_BLOB: {
						al_draw_bitmap(baby, (blobs[i].position.x/*DISP_W*/)-BABY_BITMAP_SIZE/2, (blobs[i].position.y/**DISP_H*/)- BABY_BITMAP_SIZE / 2, 0); //los bitmaps se dibujan desde la esquina superior izquierda.
						break;
		}

		case GROWN_BLOB: {
						 al_draw_bitmap(blob, (blobs[i].position.x/**DISP_W*/) - BLOB_BITMAP_SIZE / 2, (blobs[i].position.y/*DISP_H*/) - BLOB_BITMAP_SIZE / 2, 0);
						 break;
		}

		case GOOD_OLD_BLOB: {
			al_draw_bitmap(old, (blobs[i].position.x/*DISP_W*/) - OLD_BITMAP_SIZE / 2, (blobs[i].position.y/*DISP_H*/) - OLD_BITMAP_SIZE / 2, 0);
			break; 
		}

		case DEATH:
			break;//do nothing.
		default:
			break;//do nothing
		}
	}	
}

void viewer::PrintText(string text)
{
	
	al_draw_text(font, al_color_name(FONT_COLOR), ((DISP_W / 2.0)), 0, ALLEGRO_ALIGN_CENTER, "Welcome to Blob Simulation"); //imprime como incrementar
	al_draw_text(font, al_color_name(FONT_COLOR), ((DISP_W / 2.0)), 40, ALLEGRO_ALIGN_CENTER, "2021"); //imprime como decrementar

}
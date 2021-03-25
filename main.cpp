
#include <iostream>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_color.h>
#include <string>
#include <ctime>
#include "imgui.h"
#include "imgui_impl_allegro5.h"
#include "viewer.h"
#include "Resources.h"
#include "World.h"
#include "UserData.h"

#define DEF_MODE 0
#define DEF_INIT_BLOB 5
#define DEF_FOODCNT 10
#define DEF_SPD_MAX 10
#define DEF_SPD_PROP 100
#define DEF_SMLL_RAD 100 
#define DEF_JGGL_LIM 0 
#define DEF_DTH_BBY 0
#define DEF_DTH_BLOB 0
#define DEF_DTH_OLD 0

#define FPS 1

using namespace std;

int main(int argc, char* argv[]) {
	bool err = false;

	// ---------- Inicializacion de Allegro. ----------

	srand((unsigned int)time(NULL));	//Semilla

	struct userData uData = { DEF_MODE, DEF_INIT_BLOB, DEF_FOODCNT, DEF_SPD_MAX, DEF_SPD_PROP,
		DEF_SMLL_RAD, DEF_JGGL_LIM, DEF_DTH_BBY, DEF_DTH_BLOB, DEF_DTH_OLD }; //Valores Default.
	if (al_init()) { //Dear ImGUI lo necesita.

		if (al_init_primitives_addon()) { // Dear ImGui necesita Allegro para poder graficar. Para esto, usa el add-on de primitivas.


			ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
			if (!!queue) {
				if (al_install_keyboard()) {
					al_register_event_source(queue, al_get_keyboard_event_source());
					if (al_install_mouse()) {
						al_register_event_source(queue, al_get_mouse_event_source());
						ALLEGRO_TIMER* timerA = nullptr;
						timerA = al_create_timer(1.0 / FPS);
						if (!!timerA) {


							//ALLEGRO_DISPLAY *display = nullptr;
							//display = al_create_display(DISP_W, DISP_H);
							viewer Screen;
							World blobWorld;

							if (!Screen.init_allegro()) {


								al_register_event_source(queue, al_get_display_event_source(Screen.display));
								al_register_event_source(queue, al_get_timer_event_source(timerA));


								//ALLEGRO_FONT* font = nullptr;
								//font = al_load_ttf_font(FONT, FONT_SIZE, 0);
								// Setup de Dear ImGui
								IMGUI_CHECKVERSION();			// Control de version de Dear ImGui
								ImGui::CreateContext(); ImGui_ImplAllegro5_Init(Screen.display); // Inicializa Dear ImGui
								ImGuiIO& io = ImGui::GetIO();	// Me permite obtener informacion y cambiar parametros del mouse y de teclado.
								ImGui::StyleColorsDark();		// Opcional: cambiar la paleta de colores default por otra

								//Inicializo variables.
								bool running = true;			// true hasta que se cierre el display.
								bool state = false;			// true hasta que se cierre la ventana a la que se asigna.

								//variables auxiliares que usan los widgets	
								bool sim_help = false;
								bool pre_help = false;
								bool refresh = true;




								//IMGUI variables
								ImGuiWindowFlags window_flags = 0;
								window_flags |= ImGuiWindowFlags_NoBackground;
								window_flags |= ImGuiWindowFlags_NoTitleBar;
								window_flags |= ImGuiWindowFlags_NoResize;
								window_flags |= ImGuiWindowFlags_NoCollapse;
								window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
								window_flags |= ImGuiWindowFlags_NoSavedSettings;
								window_flags |= ImGuiWindowFlags_NoMove;
								ImGuiSliderFlags reg_slider = ImGuiSliderFlags_AlwaysClamp;
								ImGuiSliderFlags log_slider = reg_slider | ImGuiSliderFlags_Logarithmic;
								const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
								al_start_timer(timerA);
								while (running)
								{

									ALLEGRO_EVENT ev;
									while (al_get_next_event(queue, &ev))
									{
										ImGui_ImplAllegro5_ProcessEvent(&ev);	// Mandar el evento a Dear ImGui para que lo procese

										if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
											running = false;
										// io.WantCaptureKeyboard devuelve true si el ultimo evento fue de teclado y ademas fue 
										// usado por el usuario para interactuar con las ventanas de Dear Imgui. Por este motivo, 
										// sabemos que no estaba dirigido a nuestra aplicacion principal y no debemos mandarselo a 
										// su dispatcher. Idem para io.WantCaptureMouse y los eventos de mouse
										if ((ev.type == ALLEGRO_EVENT_TIMER) && (blobWorld.food != NULL)) {
											blobWorld.adjustBlobsSpeed(uData.mode, uData.speedMax, uData.speedProb);
											blobWorld.moveBlobs(DISP_W, BACKGROUND_VERTICAL_LIMIT - BABY_BITMAP_SIZE /2, BABY_BITMAP_SIZE, BLOB_BITMAP_SIZE, OLD_BITMAP_SIZE, FOOD_BITMAP_SIZE, uData.smellRadius);
											blobWorld.feedBlobs(DISP_W, BACKGROUND_VERTICAL_LIMIT - BABY_BITMAP_SIZE /2, uData.mode, uData.speedMax, uData.speedProb, BABY_BITMAP_SIZE, BLOB_BITMAP_SIZE, OLD_BITMAP_SIZE, FOOD_BITMAP_SIZE);
											blobWorld.manageFood(uData.foodCount, DISP_W, BACKGROUND_VERTICAL_LIMIT - BABY_BITMAP_SIZE /2);
											blobWorld.blobCollision(BABY_BITMAP_SIZE, BLOB_BITMAP_SIZE, OLD_BITMAP_SIZE, uData.randomJiggleLimit);
											blobWorld.killBlobs(uData.deathProbBabyBlob, uData.deathProbGrownBlob, uData.deathProbOldBlob);
											refresh = true;
										}
										if (!io.WantCaptureKeyboard && !io.WantCaptureMouse)
										{
											// Dispatch a nuestra aplicacion principal 
										}
									}

									// Inicio el frame. Se realiza una vez por cada pantalla que dibujo.
									ImGui_ImplAllegro5_NewFrame();
									ImGui::NewFrame();
									if (state) {

										//If world is not init
										if (!blobWorld.food)
											blobWorld.createWorld(&uData, DISP_W, BACKGROUND_VERTICAL_LIMIT - BABY_BITMAP_SIZE / 2);

										//First set of sliders: speed.
										ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x, main_viewport->WorkPos.y + BACKGROUND_VERTICAL_LIMIT), ImGuiCond_FirstUseEver);
										ImGui::Begin("Speed & Movement sliders:", NULL, window_flags);                          // Create a window for sliders																					
										ImGui::SliderFloat("Blob Speed %", &uData.speedProb, 0.0f, 100.0f, NULL, reg_slider);            // Slider for % speed, int, 0 to 100
										ImGui::SliderFloat("Blob Smell Radius", &uData.smellRadius, 0.0f, 900.0f, NULL, log_slider);				 // Slider for smell radius, int in pixels.
										ImGui::SliderFloat("Merge Random Jiggle", &uData.randomJiggleLimit, 0.0f, 360.0f, NULL, reg_slider);		// Slider for Random Jiggle limit, int in angle.
										//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
										ImGui::End();

										//Second set of sliders: death ratio
										ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 350, main_viewport->WorkPos.y + BACKGROUND_VERTICAL_LIMIT), ImGuiCond_FirstUseEver);
										ImGui::Begin("Death ratios:", NULL, window_flags);
										ImGui::SliderFloat("BabyBlob Death Ratio", &uData.deathProbBabyBlob, 0.000f, 1.000f, NULL, reg_slider);		// Slider for death ratio of baby blobs float 0f to 1f
										ImGui::SliderFloat("Blob Death Ratio", &uData.deathProbGrownBlob, 0.000f, 1.000f, NULL, reg_slider);		   // Slider for death ratio of grown blobs.
										ImGui::SliderFloat("OldBlob Death Ratio", &uData.deathProbOldBlob, 0.000f, 1.000f, NULL, reg_slider);		  // Slider for death ratio of good old blobs.
										ImGui::End();

										//Buttons for help & others
										ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 750, main_viewport->WorkPos.y + 470), ImGuiCond_FirstUseEver);
										ImGui::Begin("Helpful Buttons:", NULL, window_flags);
										if (ImGui::Button("Help"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
											sim_help = true;
										if (ImGui::Button("Stop Simulation"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
											state = false;
										ImGui::End();

										//Simulation help window. Opens when Help button is clicked.
										if (sim_help) {
											ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x, main_viewport->WorkPos.y), ImGuiCond_FirstUseEver);
											ImGui::Begin("About:", &sim_help);
											ImGui::Text("These are instructions on how to use the sliders and what they are for.");
											ImGui::Text("TIP: The sliders at the bottom control the simulation parameters, they can be modified manually or a value can be input by \nCtrl + clicking on them.");
											if (!uData.mode)
												ImGui::Text("\nSpeed %%: \n	Determines how slow or fast blobs move per frame relative to the maximum speed chosen for the simulation. \nMinimum value is set to zero, blobs are immobile, or maxed out at 100%, running at max speed.\nThis is for Mode 1 only.\n");
											ImGui::Text("\nSmell Radius:\n	Determines how far a blob will be able to detect food nearby. In a sense, it determines their sight distance to food. \nWhen a blob sees food, it will change direction to the nearest source and try to consume it before other blobs reach it. \nThe slider can be set from 0, in which blobs move like headless chickens, or 900, in which case they will see all food \non the map.");
											ImGui::Text("\nMerge Random Jiggle:\n		Determines the maximum value of a random number generator which determines blob direction right after a blob merge. \nBlobs will merge with each other if they touch and are the same etary group. Their new direction is a mean taken from \nall blobs merged plus the random jiggle generator. The higher this number, the more random a blobs direction will be \nafter they merge. Its range is 0, completely deterministic, to 360, completely chaotic.");
											ImGui::Text("\nDeath Ratio sliders:\n		These determine the chance of death of each blob group. This can be used to kill all blobs of one or all groups by \nmaxing it at 1, or give all blobs immortality by minimizing it to 0. Please be mindful of the birth to death ratio.");
											ImGui::Text("\nThe help button you just pressed opens this window. It can be closed by clicking on the X at the top right corner. \nWe hope it's served its purpose.\n");
											ImGui::Text("\nCourtesy of Group 3, EDA 2021-S1.");

											ImGui::Text("The Stop Simulation button will erase the current world and all blobs in it permanently,\nallowing the user to go back to the pre-simulation screen and change pre-simulation parameters\n to start a brand new simulation. Be careful, there is no 'are you sure?' window implemented.");
											ImGui::End();
										}

										// Rendering
										ImGui::Render();	//No dibuja! Solamente calcula que es lo que tiene que dibujarse

															// Puedo usar funciones de dibujo de Allegro ademas de las de 
															// ImGui.
															// Todo lo que dibuje antes de ImGui_ImplAllegro5_RenderDrawData
															// va a quedar detras de las ventanas de DearImGui, y todo lo 
															// que dibuje despues va a quedar encima de las ventanas de 
															// DearImGui.


										//Todo lo que dibuje aca va a quedar por detrás de las ventanas de DearImGui
										Screen.refresh(blobWorld.blobs, blobWorld.lastBlob, blobWorld.food, blobWorld.foodInWorld);

										ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());	//Dibuja las ventanas, pero no hace al_flip_display()

																									//Todo lo que dibuje aca va a quedar por encima de las ventanas de DearImGui
										if (refresh) {
											Screen.update_display(); //DearImGui nunca hace al_flip_display()
											refresh = false;
										}
									}
									else {
										if (!!blobWorld.food) { blobWorld.destroyWorld(); } //Si detengo la simulacion se destruye el mundo.

										//Second set of sliders: death ratio
										ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 350, main_viewport->WorkPos.y + 100), ImGuiCond_FirstUseEver);
										ImGui::Begin("Parametros para simulacion:", NULL, window_flags);
										ImGui::SliderInt("Max Speed", &uData.speedMax, 1, 900, NULL, reg_slider);		// Slider for death ratio of baby blobs float 0f to 1f
										ImGui::SliderInt("Initial Blob Count", &uData.initialBlobs, 1, 3000, NULL, reg_slider);		   // Slider for death ratio of grown blobs.
										ImGui::SliderInt("Food Count", &uData.foodCount, 1, 3000, NULL, reg_slider);		  // Slider for death ratio of good old blobs.
										if (ImGui::Button("Mode Switch"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
											uData.mode = !(uData.mode);
										ImGui::SameLine();
										ImGui::Text("Current mode: %d", (uData.mode + 1));
										ImGui::End();


										//Buttons for help & others
										ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + DISP_W / 2, main_viewport->WorkPos.y + BACKGROUND_VERTICAL_LIMIT), ImGuiCond_FirstUseEver);
										ImGui::Begin("Very Helpful Buttons:", NULL, window_flags);
										if (ImGui::Button("?"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
											pre_help = true;
										if (ImGui::Button("Start Simulation"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
											state = true;
										ImGui::End();

										if (pre_help) {
											ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x, main_viewport->WorkPos.y), ImGuiCond_FirstUseEver);
											ImGui::Begin("Initial Simulation Parameters:", &pre_help);
											ImGui::Text("These are instructions on how to use the GUI and what each knob is for.");
											ImGui::Text("TIP: The sliders at control the simulations initial parameters, they can be modified manually or a value can be input by \nCtrl + clicking on them.");
											if (!uData.mode)
												ImGui::Text("\nMax Speed: \n	Determines the maximum overall speed of the blobs when the simulation is set at 100%% speed.\n Minimum value is set to zero, blobs are immobile, or maxed out at 900, crossing the entire background in one step.\nThis is for Mode 1 only.\n");
											ImGui::Text("\nInitial Blob Count:\n	Determines how many blobs will be spawned as the simulation starts, influencing their survivability.\nBlobs can die and will be competing for food, but can also merge. Merging can result in higher death rates however.\nThe slider can be set from 1, in which a lonely blob desperately clings to dear life, or 3000, in which case they will most likely merge and compete for food.");
											ImGui::Text("\nFood Count:\n		Determines the amount of food available at any given moment. Food always respawns as soon as it is eaten, \nSo shortages are permanent but there will always be another piece of food to move towards.\nThe minimum food count is 1, a lucky few blobs will ever see it, or maximized at 3000, plenty of food for everyone,\nor at least one food for each.");
											ImGui::Text("\nMode:\n		This button controls the simulation mode that is chosen for a simulation, mode 1 consists of a singular\nspeed for all blobs, whilst mode 2 randomizes speeds for each given blob instance.");
											ImGui::Text("\nStart Simulation:\n		As should be evident, this button takes the chosen initial parameters and begins the simulation. \nOnce a simulation starts the parameters chosen here will not change until the simulation is stopped, at which point the\n world will be destroyed and returned to this screen, so that new initial values can be chosen.");
											ImGui::Text("\nThe '??' button you just pressed opens this window. It can be closed by clicking on the X at the top right corner. \nWe hope it's served its purpose.\n");
											ImGui::Text("\nCourtesy of Group 3, EDA 2021-S1.");

											//ImGui::Text("The Stop Simulation button will erase the current world and all blobs in it permanently,\nallowing the user to go back to the pre-simulation screen and change pre-simulation parameters\n to start a brand new simulation. Be careful, there is no "are you sure?" window implemented.");
											ImGui::End();
										}

										ImGui::Render();	//No dibuja! Solamente calcula que es lo que tiene que dibujarse
										al_clear_to_color(al_map_rgb(0, 0, 0));
										Screen.PrintText("Welcome to Blob Simulation 2021");
										ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());	//Dibuja las ventanas, pero no hace al_flip_display()
										Screen.update_display(); //DearImGui nunca hace al_flip_display()
									}
								}

								// Cleanup final
								ImGui_ImplAllegro5_Shutdown();
								ImGui::DestroyContext();

								Screen.~viewer();

								//al_destroy_display(display);
							}
							else { err = true; printf("Destroying screen.\n"); Screen.~viewer(); }
						}
						else { cout << "failed to create timer!\n" << endl;	err = true; }
					}
					else { err = true; printf("Failed to install mouse!\n"); }
				}
				else { err = true; printf("Failed to install keyboard!\n"); }
				al_destroy_event_queue(queue);
			}
			else { err = true; printf("Failed to initialize Allegro event queue!\n"); }

			al_shutdown_primitives_addon();
		}
		else { err = true; printf("Failed to initialize primitives Add_on!\n"); }

	}
	else { err = true; printf("Failed to initialize Allegro!\n"); }
	return err;
}
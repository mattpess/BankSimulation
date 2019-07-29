/*
Matthew Pessolano
7/26/2019
BankSimulation.cpp
Purpose: Handles visual display of bank simulation 
*/

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include <random>
#include <time.h>
#include "mappy_A5.h"
#include "Logic.h"

#ifndef So
#define So

int main()
{
	// display dimensions
	const int WIDTH = 1600;
	const int HEIGHT = 480;

	// variables
	bool done = false;
	bool render = false;
	

	// robber variables
	int robX = 34;
	int robY = 8;
	int robDelay = 10;

	// total time spent in simulation; takes sped up time into account
	int totalTime = 0;

	// maximum size for each bank variable
	int maxATM = 10;
	int maxOffice = 10;
	int maxTeller = 8;
	int atmValue = maxATM;
	int tellerValue = maxTeller;
	int officeValue = maxOffice;
	int maxCustomer = 100;
	int customerValue = 30;

	// seed randomness for generating customers
	srand(time(NULL));

	// map name
	char map[] = "bank.fmp";

	// allegro variables
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer;
	ALLEGRO_BITMAP* logo;


	// program init
	if (!al_init())				// initialize Allegro
		return -1;

	display = al_create_display(WIDTH, HEIGHT);			//create our display object

	if (!display)			//test display object
		return -1;

	// install mouse, error if not found
	if (!al_install_mouse()) {
		al_show_native_message_box(display, "Error!", "Failed to initialize the mouse!\n.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return (-1);
	}

	//addon init
	al_install_keyboard();
	al_init_image_addon();
	al_init_primitives_addon();
	// font initialized
	al_init_font_addon();
	al_init_ttf_addon();

	// create input queue
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);
	// register input method and timer
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_start_timer(timer);

	ALLEGRO_FONT* font2 = al_load_font("rb.ttf", 25, 0);
	if (!font2) {
		al_show_native_message_box(NULL, "Error!", "Allegro has failed to initialize font.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	ALLEGRO_FONT* font3 = al_load_font("rb.ttf", 80, 0);
	// check font created
	if (!font3) {
		al_show_native_message_box(NULL, "Error!", "Allegro has failed to initialize font.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	 logo = al_load_bitmap("logo.png");
	 if (!logo) {
		 al_show_native_message_box(display, "Error", "Error", "Failed to load image!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		 al_destroy_display(display);
		 return 0;
	 }
	// if bank objects are not at max size, remove all objects not operational
	// general routine: keep removing bank objects from display until objectSize + amount removed = max size

	while (!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		// mouse left click event
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.button & 1)
			{
				// pull mouse position
				int posX = ev.mouse.x;
				int posY = ev.mouse.y;

				// begin clicked
				if (posX >= 50 && posX <= 786 - 50 && posY >= HEIGHT / 3 && posY <= HEIGHT - 50) {
					done = true;
				}
				// left arrow for atm clicked
				else if (posX >= WIDTH / 2 + 50 && posX <= WIDTH / 2 + 75 && posY >= 100 && posY <= 150) {
					if (atmValue > 1) {
						atmValue--;
					}
				}
				// right arrow for atm clicked
				else if (posX >= WIDTH / 2 + 325 && posX <= WIDTH / 2 + 350 && posY >= 100 && posY <= 150) {
					if (atmValue < maxATM) {
						atmValue++;
					}
				}
				// left arrow for teller clicked
				else if (posX >= WIDTH / 2 + 50 && posX <= WIDTH / 2 + 75 && posY >= 300 && posY <= 350) {
					if (tellerValue > 1) {
						tellerValue--;
					}
				}
				// right arrow for teller clicked
				else if (posX >= WIDTH / 2 + 325 && posX <= WIDTH / 2 + 350 && posY >= 300 && posY <= 350) {
					if (tellerValue < maxTeller) {
						tellerValue++;
					}
				}
				// left arrow for office clicked
				else if (posX >= WIDTH / 2 + 50 + (WIDTH / 4) && posX <= WIDTH / 2 + 75 + (WIDTH / 4) && posY >= 100 && posY <= 150) {
					if (officeValue > 1) {
						officeValue--;
					}
				}
				// right arrow for office clicked
				else if (posX >= WIDTH / 2 + 325 + (WIDTH / 4) && posX <= WIDTH / 2 + 350 + (WIDTH / 4) && posY >= 100 && posY <= 150) {
					if (officeValue < maxOffice) {
						officeValue++;
					}
				}
				// left arrow for customer clicked
				else if (posX >= WIDTH / 2 + 50 + (WIDTH / 4) && posX <= WIDTH / 2 + 75 + (WIDTH / 4) && posY >= 300 && posY <= 350) {
					if (customerValue > 5) {
						customerValue-=5;
					}
				}
				// right arrow for customer clicked
				else if (posX >= WIDTH / 2 + 325 + (WIDTH / 4) && posX <= WIDTH / 2 + 350 + (WIDTH / 4) && posY >= 300 && posY <= 350) {
					if (customerValue < maxCustomer) {
						customerValue+=5;
					}
				}
			}
		}

		// draw to screen
		// logo
		al_draw_bitmap(logo, 5, 5, 0);
		// start button
		al_draw_filled_rounded_rectangle(50, HEIGHT / 3, 786 - 50, HEIGHT - 50, 5, 5, al_map_rgba(77, 99, 135, 255));
		al_draw_text(font3, al_map_rgb(255, 255, 255), (786 / 2), (HEIGHT / 2 + 10) , ALLEGRO_ALIGN_CENTER, "Start Simulation");
		// value changers
		al_draw_triangle(WIDTH / 2 + 50 , 125, WIDTH / 2 + 75, 100, WIDTH / 2 + 75, 150, al_map_rgb(55, 77, 128), 10);
		al_draw_triangle(WIDTH / 2 + 350, 125, WIDTH / 2 + 325, 100, WIDTH / 2 + 325, 150, al_map_rgb(55, 77, 128), 10);
		al_draw_triangle(WIDTH / 2 + 50, 325, WIDTH / 2 + 75, 300, WIDTH / 2 + 75, 350, al_map_rgb(55, 77, 128), 10);
		al_draw_triangle(WIDTH / 2 + 350, 325, WIDTH / 2 + 325, 300, WIDTH / 2 + 325, 350, al_map_rgb(55, 77, 128), 10);
		al_draw_triangle(WIDTH / 2 + 50 + (WIDTH / 4), 125, WIDTH / 2 + 75 + (WIDTH / 4), 100, WIDTH / 2 + 75 + (WIDTH / 4), 150, al_map_rgb(55, 77, 128), 10);
		al_draw_triangle(WIDTH / 2 + 350 + (WIDTH / 4), 125, WIDTH / 2 + 325 + (WIDTH / 4), 100, WIDTH / 2 + 325 + (WIDTH / 4), 150, al_map_rgb(55, 77, 128), 10);
		al_draw_triangle(WIDTH / 2 + 50 + (WIDTH / 4), 325, WIDTH / 2 + 75 + (WIDTH / 4), 300, WIDTH / 2 + 75 + (WIDTH / 4), 350, al_map_rgb(55, 77, 128), 10);
		al_draw_triangle(WIDTH / 2 + 350 + (WIDTH / 4), 325, WIDTH / 2 + 325 + (WIDTH / 4), 300, WIDTH / 2 + 325 + (WIDTH / 4), 350, al_map_rgb(55, 77, 128), 10);
		// text
		al_draw_text(font2, al_map_rgba(199, 199, 199, 222), WIDTH / 2 + 200, 75, ALLEGRO_ALIGN_CENTER, "ATM COUNT");
		al_draw_textf(font2, al_map_rgba(199, 199, 199, 222), WIDTH / 2 + 200, 125, ALLEGRO_ALIGN_CENTER, "%d", atmValue);

		al_draw_text(font2, al_map_rgba(199, 199, 199, 222), WIDTH / 2 + 200, 275, ALLEGRO_ALIGN_CENTER, "TELLER COUNT");
		al_draw_textf(font2, al_map_rgba(199, 199, 199, 222), WIDTH / 2 + 200, 325, ALLEGRO_ALIGN_CENTER, "%d", tellerValue);

		al_draw_text(font2, al_map_rgba(199, 199, 199, 222), WIDTH / 2 + 200 + (WIDTH / 4), 75, ALLEGRO_ALIGN_CENTER, "OFFICE COUNT");
		al_draw_textf(font2, al_map_rgba(199, 199, 199, 222), WIDTH / 2 + 200 + (WIDTH / 4), 125, ALLEGRO_ALIGN_CENTER, "%d", officeValue);

		al_draw_text(font2, al_map_rgba(199, 199, 199, 222), WIDTH / 2 + 200 + (WIDTH / 4), 275, ALLEGRO_ALIGN_CENTER, "CUSTOMER COUNT");
		al_draw_textf(font2, al_map_rgba(199, 199, 199, 222), WIDTH / 2 + 200 + (WIDTH / 4), 325, ALLEGRO_ALIGN_CENTER, "%d", customerValue);

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}

	timer = al_create_timer(1.0 / 60);
	al_start_timer(timer);

	done = false;
	Logic logicHandler(customerValue, atmValue, tellerValue, officeValue);

	// load map and offset of sprite
	int xOff = 0;
	int yOff = 0;
	if (MapLoad(map, 1))
		return -5;

	//draw the background tiles
	MapDrawBG(xOff, yOff, 0, 0, WIDTH - 1, HEIGHT - 1);

	//draw foreground tiles
	MapDrawFG(xOff, yOff, 0, 0, WIDTH - 1, HEIGHT - 1, 0);

	if (logicHandler.getSizeA() < maxATM) {
		int atmTicker = logicHandler.getSizeA();
		while (atmTicker < maxATM) {
			if (atmTicker >= 5) {
				MapSetBlock(36 + ((atmTicker - 5) * 2), 13, 66);
			}
			else {
				MapSetBlock(4 + ((atmTicker) * 2), 13, 66);
			}
			atmTicker++;
		}
	}

	if (logicHandler.getSizeT() < maxTeller) {
		int tellerTicker = logicHandler.getSizeT();
		while (tellerTicker < maxTeller) {
				MapSetBlock(17 + ((tellerTicker) * 2), 12, 66);
			tellerTicker++;
		}
	}

	if (logicHandler.getSizeO() < maxOffice) {
		int officeTicker = logicHandler.getSizeO();
		while (officeTicker < maxOffice) {
			MapSetBlock(9 + ((officeTicker) * 4), 1, 66);
			officeTicker++;
		}
	}

	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));

	// simulation loop
	while (!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		
		// events every tick
		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			logicHandler.newCustomer();
			logicHandler.bankLoop();
			render = true;
		}

		// window closed event
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}

		// mouse left click event
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.button & 1)
			{
				// pull mouse position
				int posX = ev.mouse.x;
				int posY = ev.mouse.y;
				
				// left speed arrow clicked
				if (posX >= WIDTH / 20 * 15 && posX <= WIDTH / 20 * 15.85 && posY >= HEIGHT / 20 * 8.9 && posY <= HEIGHT / 20 * 10.1) {
					logicHandler.changeTime(0);
					cout << "Time decrease." << endl;
				}

				// right speed arrow clicked
				else if (posX >= WIDTH / 20 * 17 && posX <= WIDTH / 20 * 17.9 && posY >= HEIGHT / 20 * 8.9 && posY <= HEIGHT / 20 * 10.1) {
					logicHandler.changeTime(1);
					cout << "Time increase." << endl;
				}

			}
		}
		// render bank display
		if (render && al_is_event_queue_empty(event_queue))
		{
			render = false;
			//draw the background tiles
			MapDrawBG(xOff, yOff, 0, 0, WIDTH, HEIGHT);

			//draw foreground tiles
			MapDrawFG(xOff, yOff, 0, 0, WIDTH, HEIGHT, 0);

			// draw customers in correct places

			//ATM
			if (logicHandler.hasCustomer(1, 0)) {
				MapSetBlock(4, 12, 60);
			}
			else {
				MapSetBlock(4, 12, 66);
			}

			if (logicHandler.hasCustomer(1, 1)) {
				MapSetBlock(6, 12, 60);
			}
			else {
				MapSetBlock(6, 12, 66);
			}

			if (logicHandler.hasCustomer(1, 2)) {
				MapSetBlock(8, 12, 60);
			}
			else {
				MapSetBlock(8, 12, 66);
			}

			if (logicHandler.hasCustomer(1, 3)) {
				MapSetBlock(10, 12, 60);
			}
			else {
				MapSetBlock(10, 12, 66);
			}

			if (logicHandler.hasCustomer(1, 4)) {
				MapSetBlock(12, 12, 60);
			}
			else {
				MapSetBlock(12, 12, 66);
			}

			if (logicHandler.hasCustomer(1, 5)) {
				MapSetBlock(36, 12, 60);
			}
			else {
				MapSetBlock(36, 12, 66);
			}

			if (logicHandler.hasCustomer(1, 6)) {
				MapSetBlock(38, 12, 60);
			}
			else {
				MapSetBlock(38, 12, 66);
			}

			if (logicHandler.hasCustomer(1, 7)) {
				MapSetBlock(40, 12, 60);
			}
			else {
				MapSetBlock(40, 12, 66);
			}

			if (logicHandler.hasCustomer(1, 8)) {
				MapSetBlock(42, 12, 60);
			}
			else {
				MapSetBlock(42, 12, 66);
			}

			if (logicHandler.hasCustomer(1, 9)) {
				MapSetBlock(44, 12, 60);
			}
			else {
				MapSetBlock(44, 12, 66);
			}

			// Tellers
			if (logicHandler.hasCustomer(2, 0)) {
				MapSetBlock(17, 10, 60);
			}
			else {
				MapSetBlock(17, 10, 66);
			}

			if (logicHandler.hasCustomer(2, 1)) {
				MapSetBlock(19, 10, 60);
			}
			else {
				MapSetBlock(19, 10, 66);
			}

			if (logicHandler.hasCustomer(2, 2)) {
				MapSetBlock(21, 10, 60);
			}
			else {
				MapSetBlock(21, 10, 66);
			}

			if (logicHandler.hasCustomer(2, 3)) {
				MapSetBlock(23, 10, 60);
			}
			else {
				MapSetBlock(23, 10, 66);
			}

			if (logicHandler.hasCustomer(2, 4)) {
				MapSetBlock(25, 10, 60);
			}
			else {
				MapSetBlock(25, 10, 66);
			}

			if (logicHandler.hasCustomer(2, 5)) {
				MapSetBlock(27, 10, 60);
			}
			else {
				MapSetBlock(27, 10, 66);
			}

			if (logicHandler.hasCustomer(2, 6)) {
				MapSetBlock(29, 10, 60);
			}
			else {
				MapSetBlock(29, 10, 66);
			}

			if (logicHandler.hasCustomer(2, 7)) {
				MapSetBlock(31, 10, 60);
			}
			else {
				MapSetBlock(31, 10, 66);
			}

			// Office
			if (logicHandler.hasCustomer(3, 0)) {
				MapSetBlock(9, 3, 60);
			}
			else {
				MapSetBlock(9, 3, 66);
			}

			if (logicHandler.hasCustomer(3, 1)) {
				MapSetBlock(13, 3, 60);
			}
			else {
				MapSetBlock(13, 3, 66);
			}

			if (logicHandler.hasCustomer(3, 2)) {
				MapSetBlock(17, 3, 60);
			}
			else {
				MapSetBlock(17, 3, 66);
			}

			if (logicHandler.hasCustomer(3, 3)) {
				MapSetBlock(21, 3, 60);
			}
			else {
				MapSetBlock(21, 3, 66);
			}

			if (logicHandler.hasCustomer(3, 4)) {
				MapSetBlock(25, 3, 60);
			}
			else {
				MapSetBlock(25, 3, 66);
			}

			if (logicHandler.hasCustomer(3, 5)) {
				MapSetBlock(29, 3, 60);
			}
			else {
				MapSetBlock(29, 3, 66);
			}

			if (logicHandler.hasCustomer(3, 6)) {
				MapSetBlock(33, 3, 60);
			}
			else {
				MapSetBlock(33, 3, 66);
			}

			if (logicHandler.hasCustomer(3, 7)) {
				MapSetBlock(37, 3, 60);
			}
			else {
				MapSetBlock(37, 3, 66);
			}

			if (logicHandler.hasCustomer(3, 8)) {
				MapSetBlock(41, 3, 60);
			}
			else {
				MapSetBlock(41, 3, 66);
			}

			if (logicHandler.hasCustomer(3, 9)) {
				MapSetBlock(45, 3, 60);
			}
			else {
				MapSetBlock(45, 3, 66);
			}

			// previous waiting customers cleared
			int x = 4;
			int y = 5;
			while (x < 24) {
				y = 5;
				while (y < 10) {
					MapSetBlock(x, y, 66);
					y++;
				}
				x++;
			} 

			// new waiting customers drawn
			int waitingCustomers = logicHandler.idleCustomers();

			x = 4;
			y = 5;
			while (waitingCustomers > 0 && x < 24) {
				y = 5;
				while (waitingCustomers > 0 && y < 10) {
					MapSetBlock(x, y, 60);
					y++;
					waitingCustomers--;
				}
				x++;
			}

			// text of how many customers served in total
			al_draw_textf(font2, al_map_rgba(199, 199, 199, 222), WIDTH / 20 * 16.5, HEIGHT / 20 * 7, ALLEGRO_ALIGN_CENTER, "Customers helped: %d", logicHandler.getCustServed());
			
			// display to increase/descrease speed of simulation
			al_draw_filled_triangle(WIDTH / 20 * 15.65, HEIGHT / 20 * 9, WIDTH / 20 * 15.65, HEIGHT / 20 * 10, WIDTH / 20 * 15.35, HEIGHT / 20 * 9.5, al_map_rgba(199, 199, 199, 222));
			al_draw_text(font2, al_map_rgba(199, 199, 199, 222), WIDTH / 20 * 16.00, HEIGHT / 20 * 8.8, ALLEGRO_ALIGN_LEFT, "Speed");
			al_draw_filled_triangle(WIDTH / 20 * 17.3, HEIGHT / 20 * 9, WIDTH / 20 * 17.3, HEIGHT / 20 * 10, WIDTH / 20 * 17.65, HEIGHT / 20 * 9.5, al_map_rgba(199, 199, 199, 222));
			
			// display average customer time
			if (logicHandler.getCustServed() > 0) {
				double avTime = (totalTime / 60.0) / (logicHandler.getCustServed());
				al_draw_textf(font2, al_map_rgba(199, 199, 199, 222), WIDTH / 20 * 16.5, HEIGHT / 20 * 10.5, ALLEGRO_ALIGN_CENTER, "Average customer time (seconds): %.3f", avTime);
			}

			// special message displayed if event is happening
			if (logicHandler.powerOff()) {
				al_draw_text(font2, al_map_rgba(199, 199, 199, 222), WIDTH / 20 * 16.5, HEIGHT / 20 * 12.25, ALLEGRO_ALIGN_CENTER, "Power has had an outage!");
			}
			else if (logicHandler.robberOut()) {
				al_draw_text(font2, al_map_rgba(199, 199, 199, 222), WIDTH / 20 * 16.5, HEIGHT / 20 * 12.25, ALLEGRO_ALIGN_CENTER, "Bank robbery in progress!");
			}

			// screen tinted or image displayed based on event
			if (logicHandler.powerOff()) {
				al_draw_filled_rectangle(0, 0, WIDTH, HEIGHT, al_map_rgba(0, 0, 0, 145));
			}
			else if (logicHandler.robberOut()) {
				al_draw_filled_rectangle(0, 0, WIDTH, HEIGHT, al_map_rgba(82, 15, 12, 15));
				if (robDelay == 0) {
					MapSetBlock(robX, robY, 66);
					robX = rand() % 15 + 25;
					robY = rand() % 4 + 5;
					MapSetBlock(robX, robY, 201);
					robDelay = 10;
				}
				else {
					robDelay--;
				}
			}
			else {
				MapSetBlock(robX, robY, 66);
			}

			// new screen drawn to display
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
			
		}

		totalTime += (logicHandler.getScale()) * logicHandler.totalCustomers();

	}

	

	MapFreeMem();
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object

	return 0;
}

#endif

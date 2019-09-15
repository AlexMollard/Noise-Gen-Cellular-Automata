#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <time.h>
#include <random>


Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {

	srand(time(0));

	_2dRenderer = new aie::Renderer2D();

	_GridManager = new GridManager(200, getWindowWidth() ,getWindowHeight());

	_Texture = new aie::Texture("./textures/numbered_grid.tga");

	_Font = new aie::Font("./font/consolas.ttf", 32);
	
	_Timer = 0;

	setBackgroundColour(0.20f, 0.20f, 0.20f);

	return true;
}

void Application2D::shutdown() {
	
	delete _Font;
	delete _Texture;
	delete _2dRenderer;
	delete _GridManager;
}

void Application2D::update(float deltaTime) 
{
	// input example
	aie::Input* input = aie::Input::getInstance();

	// Update GridManager
	_GridManager->Update(input, deltaTime, getWindowWidth(), getWindowHeight());

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw()
{
	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	_2dRenderer->begin();
	
	// Draw GridManager
	_GridManager->Draw(_2dRenderer);

	// done drawing sprites
	_2dRenderer->end();
}
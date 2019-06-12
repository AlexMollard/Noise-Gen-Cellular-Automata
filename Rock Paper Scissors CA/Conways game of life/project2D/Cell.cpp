#include "Cell.h"
#include <iostream>
using namespace std;

Cell::Cell()
{
	_Alive = true;
	_R = 0.0f;
	_G = 0.0f;
	_B = 0.0f;
	_CellX = 0.0f;
	_CellY = 0.0f;
	_Type = '1';
	_ChangeRock = false;
	_ChangePaper = false;
	_ChangeScissors = false;
	_ChangeGun = false;
	_ChangeNuke = false;
}

Cell::~Cell()
{
}

void Cell::Draw(aie::Renderer2D* renderer)
{
}

void Cell::Update(float deltaTime)
{
	if (_Alive && _Type == '1')			// Rock
	{
		_R = 0.7f;
		_G = 0.0f;
		_B = 0.0f;
	}
	else if (_Alive && _Type == '2')	// Paper
	{
		_R = 0.1f;
		_G = 0.1f;
		_B = 0.1f;
	}
	else if (_Alive && _Type == '3')	// Scissors
	{
		_R = 0.0f;
		_G = 0.0f;
		_B = 0.7f;
	}
	else if (_Alive && _Type == '4')	// Gun?
	{
		_R = 0.3f;
		_G = 0.3f;
		_B = 0.3f;
	}
	else if (_Alive && _Type == '5')	// Nuke?
	{
		_R = 0.0f;
		_G = 0.4f;
		_B = 0.0f;
	}

	else if (!_Alive)
	{
		_R = 0.0f;
		_G = 0.0f;
		_B = 0.0f;
	}
}

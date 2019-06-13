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
	_Type = '0';
	_ChangeTree = false;
	_ChangeShallow = false;
	_ChangeDeepWaters = false;
	_ChangeSand = false;
	_ChangeGrass = false;
}

Cell::~Cell()
{
}

void Cell::Draw(aie::Renderer2D* renderer)
{
}

void Cell::Update(float deltaTime)
{
	if (_Alive && _Type == '1')			// Tree
	{
		_R = 0.216f;
		_G = 0.316f;
		_B = 0.204f;
	}
	else if (_Alive && _Type == '2')	// Shallow/Shallow
	{
		_R = 0.329f;
		_G = 0.608f;
		_B = 0.922f;
	}
	else if (_Alive && _Type == '3')	// DeepWater
	{
		_R = 0.0f;
		_G = 0.0f;
		_B = 0.9f;
	}
	else if (_Alive && _Type == '4')	// Sand? 89% red, 87.8% green and 63.1% blue
	{
		_R = 0.89f;
		_G = 0.878f;
		_B = 0.631f;
	}
	else if (_Alive && _Type == '5')	// Grass?	21.6% red, 81.6% green and 20.4% blue.
	{
		_R = 0.216f;
		_G = 0.816f;
		_B = 0.204f;
	}

	else if (!_Alive || _Type == '0')
	{
		_R = 0.0f;
		_G = 0.0f;
		_B = 0.0f;
	}
}

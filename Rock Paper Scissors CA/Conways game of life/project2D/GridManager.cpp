#include "GridManager.h"
#include <iostream>
using namespace std;

GridManager::GridManager(int cellAmount, float windowSizeX, float windowSizeY)
{
	// Set how many cells there are
	_CellTotal = cellAmount;

	// Set window size varibles
	_WindowSizeX = windowSizeX;
	_WindowSizeY = windowSizeY;

	// Set Cell Size
	_CellSizeX = 10;
	_CellSizeY = 10;

	// Set Timer for each generation
	_Timer = 0;

	// Create Cells
	_Cells = new Cell*[_CellTotal];
	for (int i = 0; i < cellAmount; i++)
		_Cells[i] = new Cell[_CellTotal];

	Resize(windowSizeX, windowSizeY);

	// Randomize cells
	for (int x = 0; x < _CellTotal; x++)
	{
		for (int y = 0; y < _CellTotal; y++)
		{
			//int _RandomAlive = rand() % 50;
			//if (_RandomAlive < 25)
				_Cells[x][y].SetAlive(true);
			//else
			//	_Cells[x][y].SetAlive(false);

			if (_Cells[x][y].GetAlive() == true)
			{
				int _RandomType = rand() % 30;
				if (_RandomType < 10)
					_Cells[x][y].SetType('1');
				else if (_RandomType < 20)
					_Cells[x][y].SetType('2');
				else if (_RandomType < 30)
					_Cells[x][y].SetType('3');
			}
		}
	}

	// Glider example
	//_Cells[1][_CellTotal-2].SetAlive(true);
	//_Cells[2][_CellTotal-3].SetAlive(true);
	//_Cells[3][_CellTotal-3].SetAlive(true);
	//_Cells[3][_CellTotal-2].SetAlive(true);
	//_Cells[3][_CellTotal-1].SetAlive(true);
}

void GridManager::Update(aie::Input* input, float deltaTime, float windowWidth, float windowHeight)
{
	_Timer += deltaTime * 10;

	for (int x = 0; x < _CellTotal; x++)
	{
		for (int y = 0; y < _CellTotal; y++)
		{
			_Cells[x][y].Update(deltaTime);
		}
	}

	// Resize Cells
	if (_WindowSizeX != windowWidth || _WindowSizeY != windowHeight)
		Resize(windowWidth, windowHeight);

	if (_Timer > 1)
	{
		CheckNeighbours();
		_Timer = 0;
	}

	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
		{
		// Randomize cells
		for (int x = 0; x < _CellTotal; x++)
		{
			for (int y = 0; y < _CellTotal; y++)
			{
				_Cells[x][y].SetAlive(true);

				if (_Cells[x][y].GetAlive() == true)
				{
					int _RandomType = rand() % 50;
					if (_RandomType < 10)
						_Cells[x][y].SetType('1');
					else if (_RandomType < 20)
						_Cells[x][y].SetType('2');
					else if (_RandomType < 30)
						_Cells[x][y].SetType('3');
					else if (_RandomType < 40)
						_Cells[x][y].SetType('4');
					else if (_RandomType < 50)
						_Cells[x][y].SetType('5');
				}
			}
		}
		}

}

void GridManager::Resize(float windowWidth, float windowHeight)
{
		_WindowSizeX = windowWidth;
		_WindowSizeY = windowHeight;

		// Cell size
		_CellSizeX = _WindowSizeX / _CellTotal;
		_CellSizeY = _WindowSizeY / _CellTotal;

		for (int x = 0; x < _CellTotal; x++)
		{
			for (int y = 0; y < _CellTotal; y++)
			{
				// Cell Postition
				_Cells[x][y].SetPos(x * _CellSizeX, y * _CellSizeY);
			}
		}
}

void GridManager::CheckNeighbours()													   
{																					   
	for (int x = 0; x < _CellTotal; x++)											   
	{
		for (int y = 0; y < _CellTotal; y++)
		{
			int _RockNeighbours = 0;
			int _PaperNeighbours = 0;
			int _ScissorNeighbours = 0;
			int _GunNeighbours = 0;
			int _NukeNeighbours = 0;

			if (x + 1 < _CellTotal && y + 1 < _CellTotal)
			{														 
				if (_Cells[x + 1][y + 1].GetAlive())				  // - | - | X
				{ 													  // - | - | -
					if (_Cells[x + 1][y + 1].GetType() == '1')		  // - | - | -
						_RockNeighbours += 1;
					else if (_Cells[x + 1][y + 1].GetType() == '2')
						_PaperNeighbours += 1;
					else if (_Cells[x + 1][y + 1].GetType() == '3')							 
						_ScissorNeighbours += 1;	
					else if (_Cells[x + 1][y + 1].GetType() == '4')
						_GunNeighbours += 1;
					else if (_Cells[x + 1][y + 1].GetType() == '5')
						_GunNeighbours += 1;
				}																		 
			}

			if (y + 1 < _CellTotal)
			{													  
				if (_Cells[x][y + 1].GetAlive())					  // - | X | -
				{													  // - | - | -
					if (_Cells[x][y + 1].GetType() == '1')		 	  // - | - | -
						_RockNeighbours += 1;
					else if (_Cells[x][y + 1].GetType() == '2')
						_PaperNeighbours += 1;
					else if (_Cells[x][y + 1].GetType() == '3')						
						_ScissorNeighbours += 1;
					else if (_Cells[x][y + 1].GetType() == '4')
						_GunNeighbours += 1;
					else if (_Cells[x][y + 1].GetType() == '5')
						_GunNeighbours += 1;
				}																	 
			}																		 
																					 
			if (x - 1 >= 0 && y + 1 < _CellTotal)
			{														
				if (_Cells[x - 1][y + 1].GetAlive())			  
				{												  
					if (_Cells[x - 1][y + 1].GetType() == '1')
						_RockNeighbours += 1;
					else if (_Cells[x - 1][y + 1].GetType() == '2')
						_PaperNeighbours += 1;
					else if (_Cells[x - 1][y + 1].GetType() == '3')
						_ScissorNeighbours += 1;
					else if (_Cells[x - 1][y + 1].GetType() == '4')
						_GunNeighbours += 1;
					else if (_Cells[x - 1][y + 1].GetType() == '5')
						_NukeNeighbours += 1;
				}
			}

			if (x - 1 >= 0)
			{													  
				if (_Cells[x - 1][y].GetAlive())				  
				{
					if (_Cells[x - 1][y].GetType() == '1')
						_RockNeighbours += 1;
					else if (_Cells[x - 1][y].GetType() == '2')
						_PaperNeighbours += 1;
					else if (_Cells[x - 1][y].GetType() == '3')
						_ScissorNeighbours += 1;
					else if (_Cells[x - 1][y].GetType() == '4')
						_GunNeighbours += 1;
					else if (_Cells[x - 1][y].GetType() == '5')
						_NukeNeighbours += 1;
				}
			}

			if (x + 1 < _CellTotal)
			{													  
				if (_Cells[x + 1][y].GetAlive())				  
				{
					if (_Cells[x + 1][y].GetType() == '1')
						_RockNeighbours += 1;
					else if (_Cells[x + 1][y].GetType() == '2')
						_PaperNeighbours += 1;
					else if (_Cells[x + 1][y].GetType() == '3')
						_ScissorNeighbours += 1;
					else if (_Cells[x + 1][y].GetType() == '4')
						_GunNeighbours += 1;
					else if (_Cells[x + 1][y].GetType() == '5')
						_NukeNeighbours += 1;
				}
			}

			if (x - 1 >= 0 && y - 1 >= 0)
			{													  
				if (_Cells[x - 1][y - 1].GetAlive())			  
				{
					if (_Cells[x - 1][y - 1].GetType() == '1')
						_RockNeighbours += 1;
					else if (_Cells[x - 1][y - 1].GetType() == '2')
						_PaperNeighbours += 1;
					else if (_Cells[x - 1][y - 1].GetType() == '3')
						_ScissorNeighbours += 1;
					else if (_Cells[x - 1][y - 1].GetType() == '4')
						_GunNeighbours += 1;
					else if (_Cells[x - 1][y - 1].GetType() == '5')
						_NukeNeighbours += 1;
				}
			}

			if (y - 1 >= 0)
			{													  
				if (_Cells[x][y - 1].GetAlive())				  
				{
					if (_Cells[x][y - 1].GetType() == '1')
						_RockNeighbours += 1;
					else if (_Cells[x][y - 1].GetType() == '2')
						_PaperNeighbours += 1;
					else if (_Cells[x][y - 1].GetType() == '3')
						_ScissorNeighbours += 1;
					else if (_Cells[x][y - 1].GetType() == '4')
						_GunNeighbours += 1;
					else if (_Cells[x][y - 1].GetType() == '5')
						_NukeNeighbours += 1;
				}
			}


			if (x + 1 < _CellTotal && y - 1 >= 0)
			{													  
				if (_Cells[x + 1][y - 1].GetAlive())			  
				{
					if (_Cells[x + 1][y - 1].GetType() == '1')
						_RockNeighbours += 1;
					else if (_Cells[x + 1][y - 1].GetType() == '2')
						_PaperNeighbours += 1;
					else if (_Cells[x + 1][y - 1].GetType() == '3')
						_ScissorNeighbours += 1;
					else if (_Cells[x + 1][y - 1].GetType() == '4')
						_GunNeighbours += 1;
					else if (_Cells[x + 1][y - 1].GetType() == '5')
						_NukeNeighbours += 1;
				}
			}

			if (_Cells[x][y].GetType() == '1')	//Rock				killed by nuke and paper
			{
				if (_PaperNeighbours > _NukeNeighbours)
				{
					if (_PaperNeighbours > _RockNeighbours - 2 )
					{
						_Cells[x][y].SetChangePaper(true);
					}
				}
				else if (_PaperNeighbours < _NukeNeighbours)
				{
					if (_NukeNeighbours > _RockNeighbours)
					{
						_Cells[x][y].SetChangeNuke(true);
					}
				}
			}
			else if (_Cells[x][y].GetType() == '2') //Paper			 killed by scissors and nuke
			{
				if (_NukeNeighbours > _ScissorNeighbours - 2)
				{
					if (_NukeNeighbours > _PaperNeighbours)
					{
						_Cells[x][y].SetChangeNuke(true);
					}
				}
				else if (_ScissorNeighbours < _ScissorNeighbours)
				{
					if (_ScissorNeighbours > _PaperNeighbours)
					{
						_Cells[x][y].SetChangeScissors(true);
					}
				}
			}
			else if (_Cells[x][y].GetType() == '3') //Scissors		Killed by Rock and Gun
			{
				if (_GunNeighbours > _RockNeighbours)
				{
					if (_GunNeighbours > _ScissorNeighbours - 2)
					{
						_Cells[x][y].SetChangeGun(true);
					}
				}
				else if (_GunNeighbours < _RockNeighbours)
				{
					if (_RockNeighbours > _ScissorNeighbours)
					{
						_Cells[x][y].SetChangeRock(true);
					}
				}
			}
			else if (_Cells[x][y].GetType() == '4') //Gun			Killed by Rock and paper
			{
				if (_PaperNeighbours > _RockNeighbours - 2)
				{
					if (_PaperNeighbours > _GunNeighbours)
					{
						_Cells[x][y].SetChangePaper(true);
					}
				}
				else if (_PaperNeighbours < _RockNeighbours)
				{
					if (_RockNeighbours > _GunNeighbours)
					{
						_Cells[x][y].SetChangeRock(true);
					}
				}
			}
			else if (_Cells[x][y].GetType() == '5') //Nuke		Killed by scissors and gun	
			{
				if (_ScissorNeighbours > _GunNeighbours)
				{
					if (_ScissorNeighbours > _GunNeighbours - 2)
					{
						_Cells[x][y].SetChangeScissors(true);
					}
				}
				else if (_ScissorNeighbours < _GunNeighbours)
				{
					if (_GunNeighbours > _GunNeighbours)
					{
						_Cells[x][y].SetChangeGun(true);
					}
				}
			}
		}
	}

	for (int x = 0; x < _CellTotal; x++)
	{
		for (int y = 0; y < _CellTotal; y++)
		{
			if (_Cells[x][y].GetChangePaper())
			{
				_Cells[x][y].SetType('2');
				_Cells[x][y].SetChangePaper(false);
			}
			else if (_Cells[x][y].GetChangeScissors())
			{
				_Cells[x][y].SetType('3');
				_Cells[x][y].SetChangeScissors(false);
			}
			else if (_Cells[x][y].GetChangeRock())
			{
				_Cells[x][y].SetType('1');
				_Cells[x][y].SetChangeRock(false);
			}
			else if (_Cells[x][y].GetChangeGun())
			{
				_Cells[x][y].SetType('4');
				_Cells[x][y].SetChangeGun(false);
			}
			else if (_Cells[x][y].GetChangeNuke())
			{
				_Cells[x][y].SetType('5');
				_Cells[x][y].SetChangeNuke(false);
			}
		}
	}

}


void GridManager::Draw(aie::Renderer2D* renderer)
{
	for (int x = 0; x < _CellTotal; x++)
	{
		for (int y = 0; y < _CellTotal; y++)
		{
			renderer->setRenderColour(_Cells[x][y].GetR(), _Cells[x][y].GetG(), _Cells[x][y].GetB());
			renderer->drawBox(_Cells[x][y].GetX() + _WindowSizeX / _CellTotal, _Cells[x][y].GetY() + _WindowSizeY / _CellTotal, _CellSizeX, _CellSizeY);
		}
	}
}
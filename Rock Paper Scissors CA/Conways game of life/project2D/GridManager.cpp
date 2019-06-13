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

	// Set Timer and round for each generation
	_Timer = 0;
	_Round = 0;

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
			_Cells[x][y].SetAlive(true);

			if (_Cells[x][y].GetAlive() == true)
			{
				int _RandomType = rand() % 50;
				if (_RandomType < 10)
					_Cells[x][y].SetType('1');	//Tree
				else if (_RandomType < 20)
					_Cells[x][y].SetType('2');	//Shallow
				else if (_RandomType < 25)
					_Cells[x][y].SetType('3');	//DeepWater
				else if (_RandomType < 40)
					_Cells[x][y].SetType('4');	//Sand
				else if (_RandomType < 50)
					_Cells[x][y].SetType('5');	//Grass
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

	if (_Timer > 0.5 && _Round < 40)
	{
		CheckNeighbours();
		_Timer = 0;
		_Round += 1;
	}
	else if(_Round >= 40)
	{
		cout << "Done!" << endl;
	}

	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
		{
		_Round = 0;
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
						_Cells[x][y].SetType('1');	//Tree
					else if (_RandomType < 20)
						_Cells[x][y].SetType('2');	//Shallow
					else if (_RandomType < 25)
						_Cells[x][y].SetType('3');	//DeepWater
					else if (_RandomType < 40)
						_Cells[x][y].SetType('4');	//Sand
					else if (_RandomType < 50)
						_Cells[x][y].SetType('5');	//Grass
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
		_CellSizeX = _WindowSizeX / _CellTotal / 2;
		_CellSizeY = _WindowSizeY / _CellTotal / 2;

		for (int x = 0; x < _CellTotal; x++)
		{
			for (int y = 0; y < _CellTotal; y++)
			{
				// Cell Postition
				_Cells[x][y].SetPos(x * _CellSizeX * 1.5, y * _CellSizeY * 1.5);
			}
		}
}

void GridManager::CheckNeighbours()													   
{																					   
	for (int x = 0; x < _CellTotal; x++)											   
	{
		for (int y = 0; y < _CellTotal; y++)
		{
			int _TreeNeighbours = 0;
			int _ShallowNeighbours = 0;
			int _DeepWaterNeighbours = 0;
			int _SandNeighbours = 0;
			int _GrassNeighbours = 0;

			if (x + 1 < _CellTotal && y + 1 < _CellTotal)
			{														 
				if (_Cells[x + 1][y + 1].GetAlive())				  // - | - | X
				{ 													  // - | - | -
					if (_Cells[x + 1][y + 1].GetType() == '1')		  // - | - | -
						_TreeNeighbours += 1;
					else if (_Cells[x + 1][y + 1].GetType() == '2')
						_ShallowNeighbours += 1;
					else if (_Cells[x + 1][y + 1].GetType() == '3')							 
						_DeepWaterNeighbours += 1;	
					else if (_Cells[x + 1][y + 1].GetType() == '4')
						_SandNeighbours += 1;
					else if (_Cells[x + 1][y + 1].GetType() == '5')
						_SandNeighbours += 1;
				}																		 
			}

			if (y + 1 < _CellTotal)
			{													  
				if (_Cells[x][y + 1].GetAlive())					  // - | X | -
				{													  // - | - | -
					if (_Cells[x][y + 1].GetType() == '1')		 	  // - | - | -
						_TreeNeighbours += 1;
					else if (_Cells[x][y + 1].GetType() == '2')
						_ShallowNeighbours += 1;
					else if (_Cells[x][y + 1].GetType() == '3')						
						_DeepWaterNeighbours += 1;
					else if (_Cells[x][y + 1].GetType() == '4')
						_SandNeighbours += 1;
					else if (_Cells[x][y + 1].GetType() == '5')
						_SandNeighbours += 1;
				}																	 
			}																		 
																					 
			if (x - 1 >= 0 && y + 1 < _CellTotal)
			{														
				if (_Cells[x - 1][y + 1].GetAlive())			  
				{												  
					if (_Cells[x - 1][y + 1].GetType() == '1')
						_TreeNeighbours += 1;
					else if (_Cells[x - 1][y + 1].GetType() == '2')
						_ShallowNeighbours += 1;
					else if (_Cells[x - 1][y + 1].GetType() == '3')
						_DeepWaterNeighbours += 1;
					else if (_Cells[x - 1][y + 1].GetType() == '4')
						_SandNeighbours += 1;
					else if (_Cells[x - 1][y + 1].GetType() == '5')
						_GrassNeighbours += 1;
				}
			}

			if (x - 1 >= 0)
			{													  
				if (_Cells[x - 1][y].GetAlive())				  
				{
					if (_Cells[x - 1][y].GetType() == '1')
						_TreeNeighbours += 1;
					else if (_Cells[x - 1][y].GetType() == '2')
						_ShallowNeighbours += 1;
					else if (_Cells[x - 1][y].GetType() == '3')
						_DeepWaterNeighbours += 1;
					else if (_Cells[x - 1][y].GetType() == '4')
						_SandNeighbours += 1;
					else if (_Cells[x - 1][y].GetType() == '5')
						_GrassNeighbours += 1;
				}
			}

			if (x + 1 < _CellTotal)
			{													  
				if (_Cells[x + 1][y].GetAlive())				  
				{
					if (_Cells[x + 1][y].GetType() == '1')
						_TreeNeighbours += 1;
					else if (_Cells[x + 1][y].GetType() == '2')
						_ShallowNeighbours += 1;
					else if (_Cells[x + 1][y].GetType() == '3')
						_DeepWaterNeighbours += 1;
					else if (_Cells[x + 1][y].GetType() == '4')
						_SandNeighbours += 1;
					else if (_Cells[x + 1][y].GetType() == '5')
						_GrassNeighbours += 1;
				}
			}

			if (x - 1 >= 0 && y - 1 >= 0)
			{													  
				if (_Cells[x - 1][y - 1].GetAlive())			  
				{
					if (_Cells[x - 1][y - 1].GetType() == '1')
						_TreeNeighbours += 1;
					else if (_Cells[x - 1][y - 1].GetType() == '2')
						_ShallowNeighbours += 1;
					else if (_Cells[x - 1][y - 1].GetType() == '3')
						_DeepWaterNeighbours += 1;
					else if (_Cells[x - 1][y - 1].GetType() == '4')
						_SandNeighbours += 1;
					else if (_Cells[x - 1][y - 1].GetType() == '5')
						_GrassNeighbours += 1;
				}
			}

			if (y - 1 >= 0)
			{													  
				if (_Cells[x][y - 1].GetAlive())				  
				{
					if (_Cells[x][y - 1].GetType() == '1')
						_TreeNeighbours += 1;
					else if (_Cells[x][y - 1].GetType() == '2')
						_ShallowNeighbours += 1;
					else if (_Cells[x][y - 1].GetType() == '3')
						_DeepWaterNeighbours += 1;
					else if (_Cells[x][y - 1].GetType() == '4')
						_SandNeighbours += 1;
					else if (_Cells[x][y - 1].GetType() == '5')
						_GrassNeighbours += 1;
				}
			}


			if (x + 1 < _CellTotal && y - 1 >= 0)
			{													  
				if (_Cells[x + 1][y - 1].GetAlive())			  
				{
					if (_Cells[x + 1][y - 1].GetType() == '1')
						_TreeNeighbours += 1;
					else if (_Cells[x + 1][y - 1].GetType() == '2')
						_ShallowNeighbours += 1;
					else if (_Cells[x + 1][y - 1].GetType() == '3')
						_DeepWaterNeighbours += 1;
					else if (_Cells[x + 1][y - 1].GetType() == '4')
						_SandNeighbours += 1;
					else if (_Cells[x + 1][y - 1].GetType() == '5')
						_GrassNeighbours += 1;
				}
			}

			// Food Chain
			if (_ShallowNeighbours > 2 && _GrassNeighbours == 0 && _Cells[x][y].GetType() == '2')
			{
				_Cells[x][y].SetChangeDeepWaters(true);
			}
			else if (_Cells[x][y].GetType() == '4' && _GrassNeighbours > 4)
			{
				_Cells[x][y].SetChangeGrass(true);
			}
			else if (_Cells[x][y].GetType() == '4' && _DeepWaterNeighbours > 5)
			{
				_Cells[x][y].SetChangeDeepWaters(true);
			}
			else if (_Cells[x][y].GetType() == '2' && _DeepWaterNeighbours > 5)
			{
				_Cells[x][y].SetChangeDeepWaters(true);
			}
			else if (_Cells[x][y].GetType() == '4' && _SandNeighbours > 4)
			{
				_Cells[x][y].SetChangeGrass(true);
			}
			else if (_Cells[x][y].GetType() == '4' &&  _ShallowNeighbours < 3)
			{
				_Cells[x][y].SetChangeSand(true);
			}
			else if (_Cells[x][y].GetType() == '3' && _GrassNeighbours > 1)
			{
				_Cells[x][y].SetChangeSand(true);
			}
			else if (_Cells[x][y].GetType() == '5' && _ShallowNeighbours > 2)
			{
				_Cells[x][y].SetChangeSand(true);
			}
			else if (_Cells[x][y].GetType() == '5' && _DeepWaterNeighbours > 3)
			{
				_Cells[x][y].SetChangeDeepWaters(true);
			}
			else if (_Cells[x][y].GetType() == '5' && _GrassNeighbours > 4)
			{
				_Cells[x][y].SetChangeTree(true);
			}
			else if (_Cells[x][y].GetType() == '4' && _SandNeighbours > 5)
			{
				_Cells[x][y].SetChangeGrass(true);
			}
			else if (_Cells[x][y].GetType() == '1')	//Tree				killed by Grass and Shallow
			{
				if (_ShallowNeighbours > _GrassNeighbours)
				{
					if (_ShallowNeighbours > _TreeNeighbours - 2 )
					{
						_Cells[x][y].SetChangeShallow(true);
					}
				}
				else if (_ShallowNeighbours < _GrassNeighbours)
				{
					if (_GrassNeighbours > _TreeNeighbours)
					{
						_Cells[x][y].SetChangeGrass(true);
					}
				}
			}
			else if (_Cells[x][y].GetType() == '2') //Shallow			 killed by DeepWaters and Grass
			{
				if (_GrassNeighbours > _DeepWaterNeighbours - 1)
				{
					if (_GrassNeighbours > _ShallowNeighbours)
					{
						_Cells[x][y].SetChangeGrass(true);
					}
				}
				else if (_DeepWaterNeighbours < _DeepWaterNeighbours)
				{
					if (_DeepWaterNeighbours > _ShallowNeighbours - 2)
					{
						_Cells[x][y].SetChangeDeepWaters(true);
					}
				}
			}
			else if (_Cells[x][y].GetType() == '3') //DeepWater		Killed by Tree and Sand
			{
				if (_ShallowNeighbours > 5)
				{
					_Cells[x][y].SetChangeShallow(true);
				}

				if (_SandNeighbours > _TreeNeighbours)
				{
					if (_SandNeighbours > _DeepWaterNeighbours)
					{
						_Cells[x][y].SetChangeSand(true);
					}
				}
				else if (_SandNeighbours < _TreeNeighbours)
				{
					if (_TreeNeighbours > _DeepWaterNeighbours)
					{
						_Cells[x][y].SetChangeTree(true);
					}
				}
			}
			else if (_Cells[x][y].GetType() == '4') //Sand			Killed by Tree and Shallow
			{
				if (_ShallowNeighbours > _TreeNeighbours - 6)
				{
					if (_ShallowNeighbours > _SandNeighbours)
					{
						_Cells[x][y].SetChangeShallow(true);
					}
				}
				else if (_ShallowNeighbours < _TreeNeighbours)
				{
					if (_TreeNeighbours > _SandNeighbours)
					{
						_Cells[x][y].SetChangeTree(true);
					}
				}
			}
			else if (_Cells[x][y].GetType() == '5') //Grass		Killed by DeepWaters and Sand	
			{

				//if (_DeepWaterNeighbours > _SandNeighbours)
				//{
					if (_DeepWaterNeighbours > _GrassNeighbours - 1 && _GrassNeighbours == 2)
					{
						_Cells[x][y].SetChangeDeepWaters(true);
					}
				//}
				//else if (_DeepWaterNeighbours < _SandNeighbours)
				//{
				//	//if (_SandNeighbours > _SandNeighbours)
				//	//{
				//	//	_Cells[x][y].SetChangeSand(true);
				//	//}
				//}
			}
		}
	}

	for (int x = 0; x < _CellTotal; x++)
	{
		for (int y = 0; y < _CellTotal; y++)
		{
			if (_Cells[x][y].GetChangeShallow())
			{
				_Cells[x][y].SetType('2');
				_Cells[x][y].SetChangeShallow(false);
			}
			else if (_Cells[x][y].GetChangeDeepWaters())
			{
				_Cells[x][y].SetType('3');
				_Cells[x][y].SetChangeDeepWaters(false);
			}
			else if (_Cells[x][y].GetChangeTree())
			{
				_Cells[x][y].SetType('1');
				_Cells[x][y].SetChangeTree(false);
			}
			else if (_Cells[x][y].GetChangeSand())
			{
				_Cells[x][y].SetType('4');
				_Cells[x][y].SetChangeSand(false);
			}
			else if (_Cells[x][y].GetChangeGrass())
			{
				_Cells[x][y].SetType('5');
				_Cells[x][y].SetChangeGrass(false);
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
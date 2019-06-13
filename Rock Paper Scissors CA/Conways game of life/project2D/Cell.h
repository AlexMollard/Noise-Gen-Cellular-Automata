#pragma once
#include <Renderer2D.h>
class Cell
{
public:
	Cell();
	~Cell();

	void Update(float deltaTime);
	void Draw(aie::Renderer2D* renderer);

	// Postition Functions
	void SetPos(float x, float y)		{ _CellX = x;  _CellY = y; };
	float GetX()						{ return _CellX; };
	float GetY()						{ return _CellY; };
	
	// Alive Functions
	bool GetAlive()						{ return _Alive; };
	void SetAlive(bool alive)			{ _Alive = alive; };

	// Death Functions
	bool GetDeath()						{ return _DeathRow; };
	void SetDeath(bool death)			{ _DeathRow = death; };

	// Type Functions
	char GetType()						{ return _Type; };
	void SetType(char type)				{ _Type = type; };

	// Colour Functions
	float GetR()						{ return _R; };
	float GetG()						{ return _G; };
	float GetB()						{ return _B; };

	// Tree Functions
	bool GetChangeTree()				{ return _ChangeTree; };
	void SetChangeTree(bool change)		{ _ChangeTree = change; };

	// Shallow Functions
	bool GetChangeShallow()				{ return _ChangeShallow; };
	void SetChangeShallow(bool change)	{ _ChangeShallow = change; };

	// DeepWaters Functions
	bool GetChangeDeepWaters()			{ return _ChangeDeepWaters; };
	void SetChangeDeepWaters(bool change) { _ChangeDeepWaters = change; };
	
	// Sand Functions
	bool GetChangeSand() { return _ChangeSand; };
	void SetChangeSand(bool change) { _ChangeSand = change; };

	// Grass Functions
	bool GetChangeGrass() { return _ChangeGrass; };
	void SetChangeGrass(bool change) { _ChangeGrass = change; };

private:
	bool _DeathRow;
	bool _Alive;
	float _CellX;
	float _CellY;
	float _R;
	float _G;
	float _B;
	char _Type;		// '1' = Tree, '2' = Shallow, '3' = DeepWaters
	bool _ChangeTree;
	bool _ChangeShallow;
	bool _ChangeDeepWaters;
	bool _ChangeSand;
	bool _ChangeGrass;
};


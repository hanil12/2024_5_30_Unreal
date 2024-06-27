#include "pch.h"
#include "Program.h"

#include "Scene/PaintScene.h"
#include "Scene/CollisionScene.h"

Program::Program()
{
	_scene = make_shared<CollisionScene>();
}

Program::~Program()
{
}

void Program::Update()
{
	_scene->Update();
}

void Program::Render(HDC hdc)
{
	_scene->Render(hdc);
}

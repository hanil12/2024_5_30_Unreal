#include "pch.h"
#include "PaintScene.h"

PaintScene::PaintScene()
{
    _rect = make_shared<Rect>(Vector2(0.0f,0.0f), Vector2(50.0f,50.0f));
    // circle
}

PaintScene::~PaintScene()
{
}

void PaintScene::Update()
{
    _rect->_center = _rect->_center + Vector2(0.5f,0.5f);

    _rect->Update();
}

void PaintScene::Render(HDC hdc)
{
    // 색 입히기 : red
    HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
    SelectObject(hdc, redBrush);

    // 사각형 그리기
    _rect->Render(hdc);

    // 색 입히기 : blue
    HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));
    SelectObject(hdc, blueBrush);

    // 원 그리기
    //Ellipse(hdc, 200, 200, 300, 300);

    // 선 색깔 고르기
    HPEN greenPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
    SelectObject(hdc, greenPen);

    // 선 그리기
    MoveToEx(hdc, 100, 100, nullptr);
    LineTo(hdc, 200, 200);
}

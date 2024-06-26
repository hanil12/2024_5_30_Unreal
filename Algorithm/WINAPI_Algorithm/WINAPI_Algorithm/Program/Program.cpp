#include "pch.h"
#include "Program.h"

Program::Program()
{
}

Program::~Program()
{
}

void Program::Update()
{
    _left += 0.1f;
    _top += 0.1f;
    _right += 0.1f;
    _bottom += 0.1f;
}

void Program::Render(HDC hdc)
{
    // 색 입히기 : red
    HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
    SelectObject(hdc, redBrush);

    // 사각형 그리기
    Rectangle(hdc, _left, _top, _right, _bottom);

    // 색 입히기 : blue
    HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));
    SelectObject(hdc, blueBrush);

    // 원 그리기
    Ellipse(hdc, 200, 200, 300, 300);

    // 선 색깔 고르기
    HPEN greenPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
    SelectObject(hdc, greenPen);

    // 선 그리기
    MoveToEx(hdc, 100, 100, nullptr);
    LineTo(hdc, 200, 200);
}

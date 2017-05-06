#include <iostream>
#include <ctime>
#include "DrawField.h"

DrawField::DrawField() : BaseApp(80, 50)
{
	m_direction = true;
	m_main_field_coord_x = 21;
	m_main_field_coord_y = 16;
	m_info_field_coord_x = m_main_field_coord_x + 6;
	m_info_field_coord_y = 6;
	m_obj_x = 10;
	m_obj_y = 1;

	srand(time(0));

	drawMainInfoField();
}

void DrawField::drawMainInfoField()
{
	for (int x = 0; x <= m_main_field_coord_x; x++) {
		for (int y = 0; y <= m_main_field_coord_y + 1; y++) {
			if ((x == 0 && y <= m_main_field_coord_y)
				|| (x == m_main_field_coord_x && y <= m_main_field_coord_y)
				|| (x <= m_main_field_coord_x && y == 0)
				|| (x <= m_main_field_coord_x && y == m_main_field_coord_y + 1))
				SetChar(x, y, '#');
			else
				SetChar(x, y, '.');
		}
	}
	for (int x = m_main_field_coord_x + 1; x <= m_info_field_coord_x; x++) {
		for (int y = 0; y <= m_info_field_coord_y; y++) {
			if ((x < m_info_field_coord_x && y == 0)
				|| (x == m_info_field_coord_x && y <= m_info_field_coord_y)
				|| (x < m_info_field_coord_x && y == m_info_field_coord_y))
				SetChar(x, y, '#');
			else
				SetChar(x, y, '.');
		}
	}
}


wchar_t getRandSym()
{
	int s = 1 + rand() % 3;
	switch (s)
	{
	case 1:
		return L'@';
	case 2:
		return L'#';
	case 3:
		return L'$';
	}
	return 0;
}

void DrawField::UpdateF(float deltaTime)
{
	static float ourTime = 0.0f;
	static wchar_t nextSym = getRandSym();
	static wchar_t currentSym = nextSym;
	
	ourTime += deltaTime;
	if (ourTime >= 0.5f) {
		SetChar(m_obj_x, m_obj_y, L'.');
		m_obj_y++;

		if (m_obj_y > m_main_field_coord_y)
		{
			m_obj_y = 1;
			currentSym = nextSym;
			nextSym = getRandSym();
			SetChar(m_info_field_coord_x -3 , m_info_field_coord_y - 3, nextSym);
		}

		SetChar(m_obj_x, m_obj_y, currentSym);		

		ourTime = 0.0f;
	}
}
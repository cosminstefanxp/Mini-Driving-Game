#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <stdlib.h>
#include <glut.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "Vector4D.h"
#include <windows.h>


class DrawableString
{
	// VARIABILE
	//-------------------------------------------------
public:
	float x;
	float y;
	LPVOID font;
	char *fullText;
	Vector4D color;
	bool lighted;


	// METODE
	//-------------------------------------------------
public:
	//deseneaza textul
	void draw();

	//seteaza textul
	inline void setText(char* _text)	{free(fullText); fullText=_strdup(_text); }

	//constructorul
	DrawableString(float _x, float _y, LPVOID _font, char* _text, Vector4D _color, bool _lighted);
	~DrawableString(void);
};





#endif
#include "DrawableString.h"

// Here are the fonts:
void* glutFonts[7] = {
    GLUT_BITMAP_9_BY_15,
    GLUT_BITMAP_8_BY_13,
    GLUT_BITMAP_TIMES_ROMAN_10,
    GLUT_BITMAP_TIMES_ROMAN_24,
    GLUT_BITMAP_HELVETICA_10,
    GLUT_BITMAP_HELVETICA_12,
    GLUT_BITMAP_HELVETICA_18
};


DrawableString::DrawableString(float _x, float _y, LPVOID _font, char* _text, Vector4D _color, bool _lighted)
{
	x=_x;
	y=_y;
	font=_font;
	fullText=_strdup(_text);
	color=_color;
	lighted=_lighted;
}

DrawableString::~DrawableString(void)
{
	free(fullText);
}

// Here is the function
void DrawableString::draw()
{
	char* text=fullText;
	glPushMatrix();
    if(!text || !strlen(text)) return;
    //setting the blend
	bool blending = false;
    if(glIsEnabled(GL_BLEND)) blending = true;
    //glEnable(GL_BLEND);
	
	//setting the light
	bool lighting=false;
	if(glIsEnabled(GL_LIGHTING))
		lighting=true;
	if(!lighted)
		glDisable(GL_LIGHTING);

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(color).Array());
    	//setam culoarea
	glColor4fv(color.Array());
	//setam pozitia de raster
	//glRasterPos2f(x,y);
	glRasterPos3f(x,2,y);

	//desenam
	while (*text) {
        glutBitmapCharacter(font, *text);
        text++;
    }
	//resetam
	if(lighting)
		glEnable(GL_LIGHTING);
	
    if(!blending)
		glDisable(GL_BLEND);

	glPopMatrix();
}  


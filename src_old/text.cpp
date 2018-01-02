#include "text.h"
#include <iostream>

using namespace std;

void RenderText(string message, SDL_Color color, int x, int y, int size, SDL_Window* window) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    int m_Width, m_Height;
    SDL_GetWindowSize(window, &m_Width, &m_Height);

    gluOrtho2D(0, m_Width, 0, m_Height); // m_Width and m_Height is the resolution of window
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    TTF_Font * font = TTF_OpenFont("zarbville_nbp.ttf", size);
    if(!font) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        // handle error
    }
    SDL_Surface * sFont = TTF_RenderText_Blended(font, message.c_str(), color);
    // ^This function is returning a null pointer

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sFont->w, sFont->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sFont->pixels);

    glColor3f(1.0,1.0,1.0);
    glBegin(GL_QUADS);
    {
        glTexCoord2f(0,1); glVertex2f(x, y);
        glTexCoord2f(1,1); glVertex2f(x + sFont->w, y);
        glTexCoord2f(1,0); glVertex2f(x + sFont->w, y + sFont->h);
        glTexCoord2f(0,0); glVertex2f(x, y + sFont->h);
    }
    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glDeleteTextures(1, &texture);
    TTF_CloseFont(font);
    SDL_FreeSurface(sFont);
}

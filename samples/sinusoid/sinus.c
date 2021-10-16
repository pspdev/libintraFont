/*
 * sinus.c
 * This file is used to display the PSP's internal font (pgf and bwfon firmware files)
 * intraFont Version 0.31 by BenHur - http://www.psp-programming.com/benhur
 *
 * Rotation support by Geecko
 * Uses parts of pgeFont by InsertWittyName - http://insomniac.0x89.org
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */

#include <intraFont.h>
#include <math.h>

#if defined(__WIN32) || defined(__WIN64)
#include "../libraries/glfw_window.c"
#define FILE_PREFIX ""
#endif

#if defined(_arch_dreamcast)
#include "../libraries/gldc_window.c"
#define FILE_PREFIX "/cd/"
#endif

#if defined(_PSP)
#include "../libraries/psp_window.c"
#define FILE_PREFIX "flash0:/font/"
#endif

#ifndef M_PI
#define M_PI ((float)(3.14159265358979323846))
#endif
#ifndef GU_PI
#define GU_PI ((float)M_PI)
#endif

/* ARGB */
#define WHITE 0xFFFFFFFF
#define GRAY 0xFF7F7F7F
#define BLACK 0xFF000000
#define RED 0xFF0000FF

intraFont* font = NULL;

float x, x2, tmp_angle;
int i;

typedef struct Sinusoid {
  float angle;  // In degrees
  float amplitude;
  float step;
  float speed;
  float speed_inc;
  char str[64];
  int len;
} Sinusoid;

Sinusoid sinus = (Sinusoid){0.f, 35.f, 10.f, 0.f, 0.007f, "intraFont 0.31 - 2009 by BenHur", 31};
Sinusoid sinus2 = (Sinusoid){0.f, 35.f, 10.f, 0.f, 0.007f, "port by mrneo240", 16};

void load(void) {
  intraFontInit();
  /* Dreamcast recommended to use INTRAFONT_CACHE_ASCII as an option but not required */
  font = intraFontLoad(FILE_PREFIX "ltn8.pgf", 0);
  intraFontSetStyle(font, 1.f, 0, 0, 0.f, INTRAFONT_ALIGN_CENTER);
}

void draw(void) {
  // * Draw the sinusoid *

  // Get the x position of the 1st char
  x = 12;  // 240 - intraFontMeasureText(font, sinus.str) / 2;
  x2 = 120;

  // Increment the speed
  if (fabsf(sinus.speed += sinus.speed_inc) > 10.f)
    sinus.speed_inc = -sinus.speed_inc;
  // Increment the angle
  tmp_angle = (sinus.angle += sinus.speed);
  if (sinus.angle > 360.f) sinus.angle -= 360.f;

  // Draw one by one
  for (i = 0; i != sinus.len; i++, tmp_angle += sinus.step) {
    intraFontSetStyle(font, 2.f, WHITE, BLACK, 45.f * cosf(tmp_angle * GU_PI / 180.f), INTRAFONT_ALIGN_LEFT);
    x = intraFontPrintEx(font, x, 80 + sinus.amplitude * sinf(tmp_angle * GU_PI / 180.f), sinus.str + i, 1);
  }

  // Draw one by one
  for (i = 0; i != sinus2.len; i++, tmp_angle += sinus2.step) {
    intraFontSetStyle(font, 2.f, RED, BLACK, 45.f * cosf(tmp_angle * GU_PI / 180.f), INTRAFONT_ALIGN_LEFT);
    x2 = intraFontPrintEx(font, x2, 200 + sinus2.amplitude * sinf(tmp_angle * GU_PI / 180.f), sinus2.str + i, 1);
  }
}

void leave(void) {
  intraFontUnload(font);
  intraFontShutdown();
}

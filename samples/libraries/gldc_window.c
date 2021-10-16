#include <gl.h>
#include <glkos.h>
#include <glu.h>
#include <stdio.h>

extern void load(void);
extern void draw(void);
extern void leave(void);

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void InitGL(void)  // We call this right after our OpenGL window is created.
{
  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
  glDisable(GL_DEPTH_TEST);  // Enables Depth Testing
  glDisable(GL_CULL_FACE);
  glFrontFace(GL_CCW);
  glCullFace(GL_BACK);
  glEnable(GL_BLEND);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();  // Reset The Projection Matrix

  gluOrtho2D(0, 640, 480, 0);
  glMatrixMode(GL_MODELVIEW);
}

/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(void) {
  glViewport(0, 0, 640, 480);  // Reset The Current Viewport And Perspective Transformation

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluOrtho2D(0, 640, 480, 0);
  glMatrixMode(GL_MODELVIEW);
}

void draw_bg(void) {
  const int rect_pos_x = 0;
  const int rect_pos_y = 0;
  const int rect_pos_w = 640;
  const int rect_pos_h = 480;
  float vertex[6 * 3] = {
      rect_pos_x, rect_pos_y + rect_pos_h, 0,
      rect_pos_x + rect_pos_w, rect_pos_y + rect_pos_h, 0,
      rect_pos_x + rect_pos_w, rect_pos_y, 0,
      rect_pos_x + rect_pos_w, rect_pos_y, 0,
      rect_pos_x, rect_pos_y, 0,
      rect_pos_x, rect_pos_y + rect_pos_h, 0};

  unsigned int color_val = 0xFF7F7F7F;
  unsigned int color_arr[6] = {color_val, color_val, color_val, color_val, color_val, color_val};

  glDisable(GL_BLEND);
  glDisable(GL_TEXTURE_2D);

  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glVertexPointer(3, GL_FLOAT, 0, vertex);
  glColorPointer(4, GL_UNSIGNED_BYTE, 0, (uint8_t *)&color_arr[0]);

  glDrawArrays(GL_TRIANGLES, 0, 6);
}

/* The main drawing function. */
void DrawGLScene() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear The Screen And The Depth Buffer
  glLoadIdentity();                                    // Reset The View

  draw_bg();
  draw();

  glKosSwapBuffers();
}

int main(int argc, char **argv) {
  /* Unused */
  (void)argc;
  (void)argv;
  
  glKosInit();

  InitGL();
  ReSizeGLScene();

  load();

  while (1) {
    DrawGLScene();
  }

  leave();

  return 0;
}

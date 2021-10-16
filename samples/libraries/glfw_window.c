#include <windows.h>
#if defined(__MINGW32__) || defined(__linux__)
#include <GLFW/galo.h>
#include <GLFW/glfw3.h>

#include "galo.c"
#endif

#include <stdio.h>
#include <stdlib.h>

extern void load(void);
extern void draw(void);
extern void leave(void);

#define SQUARE_ASPECT (4.0f / 3.0f)

static void error_callback(int error, const char* description) {
  (void)error;
  fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  (void)scancode;
  (void)mods;
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar) {
  GLdouble fW, fH;

  fH = tan(fovY / 360.0 * M_PI) * zNear;
  fW = fH * aspect;

  glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void RNDR_Init(void)  // We call this right after our OpenGL window is created.
{
  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
  glClearDepth(1.0);         // Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LESS);      // The Type Of Depth Test To Do
  glDisable(GL_DEPTH_TEST);  // Enables Depth Testing
  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CW);
  glCullFace(GL_BACK);
  glDisable(GL_BLEND);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();  // Reset The Projection Matrix

  perspectiveGL(45.0f, SQUARE_ASPECT, 0.1f, 100.0f);  // Calculate The Aspect Ratio Of The Window

  glMatrixMode(GL_MODELVIEW);
  glEnableClientState(GL_VERTEX_ARRAY);
}

void UI_Set2D(void) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //glOrtho(0, 640, 480, 0, -1, 1);
  glOrtho(0, 480, 272, 0, -1, 1);
}

int main(void) {
  GLFWwindow* window;

  glfwSetErrorCallback(error_callback);

  if (!glfwInit())
    exit(EXIT_FAILURE);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  //window = glfwCreateWindow(640, 480, "intrafont_universal", NULL, NULL);
  window = glfwCreateWindow(480, 272, "intrafont_universal", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwSetKeyCallback(window, key_callback);
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  RNDR_Init();
  glLoadIdentity();  // Reset The View
  UI_Set2D();

  load();

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear The Screen And The Depth Buffer
    glLoadIdentity();                                    // Reset The View
    UI_Set2D();

    draw();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  leave();
  glfwDestroyWindow(window);

  glfwTerminate();
  exit(EXIT_SUCCESS);
}

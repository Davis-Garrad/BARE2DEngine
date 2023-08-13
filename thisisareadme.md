# BARE2DEngine
A bare game engine for 2D games in OpenGL, using SDL and CEGUI. That pretty much sums it up. 

# Compiling with BARE2D

To link BARE2D, you'll need a linking order something like the below:

```libboost_thread.a
libboost_filesystem.a
libboost_system.a
lua5.3
libBARE2DEngine.a
CEGUIBase-0
CEGUIOpenGLRenderer-0
SDL2
SDL2_mixer
SDL2_ttf
GL
GLU
GLEW
pthread```

Assignment 4: Textures
Breakdown of Project:
Since there were two parts to this project, one cube rendered with a single texture and another cube rendered with 6 different textures,
I have demostrated each part in the two cubes that the program renders to the screen. The cube on the left is rendered using one texture
while the cube on the right is the cube that is rendered with 6 different textures. All textures can be found in the "Resources" folder
under the "Textures" subfolder. Additionally, all shaders can be found in the "Resources" folder under the "Shaders" subfolder. 

The main class that deals with texture initilaztion/creation is the Texture class. In the class, it loads in the image file, tells OpenGL
to create a Texture buffer/object, fills the buffer with the image data, generates a mipmap for the texture, and specifies the desire
texture wrap and filter parameters.

Outside of texture, the Mesh and Cube classes had to be modified to allow for texture mapping and rendering. Specifically, Mesh had all
references of color stripped from its implementation since the texture coordinates will define the coloring of the geometry and Cube was
given new draw calls so that it could bind desired textures while drawing all or pieces of its geometry.

Design:
I kept all keyboard input from prior assignments but removed trackball functionality. For keyboard input, here are all of the 
possible user controls:

	1. A: Rotate the camera towards the left
	2. D: Rotate the camera towards the right
	3. W: Move the camera forwards
	4. S: Move the camera backwards


IMPORTANT NOTE: I created my project in Visual Studios, please let me know if your machine has troubles running the code. Added 
"Release" folder that contains a "build" subfolder that has a runnable windows executable.

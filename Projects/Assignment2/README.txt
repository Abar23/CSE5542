Assignment 2: Viewing

Breakdown of Project:
I copied the code from Assignemnt 1 since it contains the code that creates my scene with the robot. In order to create 
camera movement, I utilized a trackball implementation along with corresponding GLFW window event handling callbacks to
take care of mouse and keyboard input to the program. The implementation for the trackball can be found in "VirtualTrackBall.cpp"
and "VirtualTrackBall.h". The callbacks for GLFW that handle mouse inputs are at the top of "main.cpp". Keyboard input
handling can be found in "Window.cpp". GLFW callbacks are processed when the ProcessUserInput method is called from the window
object in the main loop that runs the program. To create infinite landscape, I created a plane that clips through the near and
far planes of the viewing frustum. When he user moves around the world, the plane follows the camera by mirroring the X and Z
position of the camera. I did not create fog, since implementing fog within OpenGL is much more involved and is only in the 
scope of the WebGL projects that use an large plane since fog can be created with a simple Three.js call.

Design:
"VirtualTrackBall.cpp" and "VirtualTrackBall.h" contain the implementation for the trackball motion that effects the camera. When
the user clicks the left button of the mouse, they can then drag and rotate the camera around in space. For keyboard input, here
are all of the possibel user controls:

	1. A: Rotate the camera towards the left
	2. D: Rotate the camera towards the right
	3. W: Move the camera forwards
	4. S: Move the camera backwards

The user will never reach the end of the environment/edge of the plane since the ground plane always follows the camera as it moves.

Extra Credit:
I was told by professor Chen that if we implement a virtual trackball movement system that it would be extra credit. I don't
know if that is 100% true since it is not stated on the assignment 2 website description. I did, however, create perform all
of the matrix multiplication that controls the movement of the camera, the prespective projection, and the model matrix
operations. These matrices are then passed to uniforms in the shader programs.


IMPORTANT NOTE: I created my project in Visual Studios, please let me know if your machine has troubles running the code. I included
a "Screen Recording" folder that has a video file that shows me running the program from a windows built executable. Added "Release"
folder that contains a "build" folder that has a runnable windows executable.

Assignment 2: Stereoscopic Viewing
==================================

![Stereoscopic Viewing Example]("https://raw.githubusercontent.com/Abar23/CSE5542/master/Projects/Assignment2/Screen%20Recording/Assignment%202%20Build%20Execution.mp4")

Controls
========

"VirtualTrackBall.cpp" and "VirtualTrackBall.h" contain the implementation for the trackball motion that effects the camera. When
the user clicks the left button of the mouse, they can then drag and rotate the camera around in space. For keyboard input, here
are all of the possibel user controls:

* A: Rotate the camera towards the left
* D: Rotate the camera towards the right
* W: Move the camera forwards
* S: Move the camera backwards

The user will never reach the end of the environment/edge of the plane since the ground plane always follows the camera as it 
moves.

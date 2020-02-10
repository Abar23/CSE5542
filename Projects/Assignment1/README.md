Assignment 1: Modeling (geometry and transforms)
===============================================

## Breakdown of Project

In the project folder, there are 6 folders that are pertinent to the project. The 'src' folder contains all the
source code that was created for this project. The "include" folder contains header files for GLM, GLEW, and 
GLFW, which are the external libraries that I used in the project. The "lib" folder contains all necessary
.lib files that the Visual Studios compiler needed for external libraries. The "Resources" folder contains the
fragment and vertex shader code used for rendering the objects in the scene. Finally, there is a "Screenshots"
folder that contains images of my code running on my computer. I have created the "Screenshots" folder in case the
code does not work on another machine, that way it can be seen that the code actually compiles and runs successfully.

## Design

There are three major classes that deal with abstracting OpenGL and windowing code away from the client, those classes are Shader,
Mesh, and Window. The Shader class deals with reading files that contain code for vertex and fragment shaders. Once the files
have been read into the program, the class then compiles, links, and creates a shader program. Additionally, while
it is trying to create a shader program, it will perform intermediary error checking. The Mesh class deals with setting
up vertex buffers, index buffers, and vertex array objects for the corresponding vertex, color, and index data for objects that
are to be drawn to the screen. It also contains draw calls for properly setting the buffer binding and OpenGL rendering modes.
The Window class handles intitialization of GLEW and creates a window using GLFW that the OpenGL context is attached to.

Outside of the abstraction classes, there is the Cone, Cube, Cylinder, Torus, Plane, and Sphere classes that define all
vertex, color, and index data needed to render each object. Each class contains their own parameters that define position, 
color, and the desired amount of subdivisions for triangulation. Below is a brief description of the subdivision 
parameters that each of these classes takes in:
	1. Sphere class takes in the number of stacks and sectors for its triangulation parameters.
	2. Plane class takes in a two parameters called heightSubdivisions and widthSubdivisions that defines the
	dimensions of the triangulation that will be applied to the plane. Essentially, the parameters will create
	a plane that looks like an mxn grid, where m is heightSubdivisions and n is widthSubdivisions 
	3. Cube class takes in a single parameter called faceSubdivions that specifies the nxn subdivision that will 
	be applied to each face. For example, a faceSubdivisions of 4 will create faces that are divided into 4x4 grids 
	of triangles.
	4. Cone class takes in the number of stacks and sectors for its triangulation parameters.
	5. Sphere class takes in the number of stacks and sectors for its triangulation parameters.
	6. Torus class takes in the number of stacks and sectors for its triangulation parameters.

Each of these shape classes are derived from the Shape base class. In the Shape base class, stores the mesh and model matrix
for the objects. In addition, it has methods for drawing and manipulating the model matrix. The main reason that this class
exists is to help reduce the amount of repeated code between the shape derived classes and so that I can take advantage of
polymorphism so that I can construct hierarchical models out of the object of type Shape.

Once all the primitive shape classes inherited the Shape base class, I implemented the HierachicalModel class which stores
a root node object of the ModelNode class. The ModelNode class deals with storing translation, rotation, and scaling information
for the shape primitive that it stores. It also store child pointers to other ModelNode, which creates a basic tree structure
necessary to traverse all components that make up the model hierarchy. The HierarchicalModel class stores the root ModelNode, and
performs tree traversal for drawing the model and deleteing all memory that was allocated for the model.

Finally, the Robot class is a pretty big class that deals with setting up all primitive shapes, hierarchy nodes, and pointers
between the hierarchy nodes in order to setup the arms, legs, and head of the robot. Each leg of the robot is comprised of one 
cone, two spheres, and two cylinders. Each arm of the robot is comprised of two spheres and two cylinders. The head is comprised 
of a cylinder and a torus. The body is just a cube.

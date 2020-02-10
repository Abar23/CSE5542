Assignment 1: Modeling (geometry and transforms)
===============================================

![Primitive Robot](Projects/Assignment1/Screenshots/Robot.PNG)

The goal of this assignment was to generate spheres, cones, toruses, cylinders, and cubes.
These shapes were then plugged into custom made hierarchical modeling system. Utilizing
this modeling system, I generated a wireframe robot.

All of the shapes in this program use parametric equations to generate the vertices. Once
the vertices are created, index numbers are used to allow for rendering using index 
buffers. In addition, the client can pass parameters to the shape constructors that controls
triangulation of the geometry.

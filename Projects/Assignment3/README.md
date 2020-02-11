Assignment 3: L-Systems
=======================

This project utilizes turtle graphics to construct and render 3D l-systems out of cylinders.

Below is the input file layout used to generate the 3D l-systems:

```
<Number of generations>
<Angle in degrees>  
<Length>  
<Boolean to indicate if random behavior is desired>  
<Initial Sentence/Axiom>  
<Expansion Rule>
<Expansion Rule>
.
.
.  
```


The image above is the l-system generated from "Personal Grammar.txt". Below, is the definition of this
l-system using the previously defined input file layout.

```
6 <- Number of generations  
22.5 <- Angle in degrees  
15.0 <- Length  
false <- Randomness boolean  
B <- Initial Sentence/Axiom  
B=BB[+XF][-ZY] <- Expansion Rule  
F=BB[+O][-Y] <- Expansion Rule  
Y=BB[+F][-O] <- Expansion Rule  
O=BB[+F][-Y] <- Expansion Rule  
X=+ <- Expansion Rule  
Z=- <- Expansion Rule  
```

All possible grammars rules that can be used in an l-system input file:

* +: Increment current angle of the l-system by the angle in the l-system file definition

* -: Decrement current angle of the l-system by the angle in the l-system file definition

* [: Save the current state of the turtle

* ]: Restore the current state of the turtle

* b: Move turtle backwards without creating a cylinder for the movement

* X and Z: Do nothing. Usually used for rational/angular control of the l-system

* Capital letters (expect X, Y, Z, B, and O): Move turtle forward and create a green cylinder between the original and new 
    position of the turtle

* B:  Move forward and create a brown cylinder between the original and new position of the turtle

* Y:  Move forward and create a yellow cylinder between the original and new position of the turtle

* O:  Move forward and create a orange cylinder between the original and new position of the turtle

All l-system input files made for this project can found in "Assignment3/Resources/L-Systems" folder.

Controls
========
The camera is placed far enough away from the l-systems that the user can see the entirety of the l-system as it is being rendered
to the screen.

Resued the controls from Assignemnt 2. When the user clicks the left button of the mouse, they can then rotate 
the camera around in space. For keyboard input, here are all of the possible user controls:

* A: Rotate the camera towards the left

* D: Rotate the camera towards the right

* W: Move the camera forwards

* S: Move the camera backwards

Windows Builds
==============

In the project, there are 3 different builds that can be run on a windows machine. 

* Deterministic Tree Build: Generates the l-system defined in "Tree.txt". An image of this l-system can be seen below.
  
![Deterministic Tree](https://github.com/Abar23/CSE5542/blob/master/Projects/Assignment3/Screenshots/Tree.PNG)


* Personnal Grammar Build: Generates the l-system defined in "Personal Grammar.txt". An image of this l-system can be seen below.

![Personal Grammar](https://github.com/Abar23/CSE5542/blob/master/Projects/Assignment3/Screenshots/Personal%20Grammar.PNG)


* Random Tree Build: Generates the l-system defined in "Random Tree.txt". An image of this l-system can be seen below.

![Random Tree](https://github.com/Abar23/CSE5542/blob/master/Projects/Assignment3/Screenshots/Random%20Tree.PNG)

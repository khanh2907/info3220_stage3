Changes to Stage 1 code
=======================

In order to extend the code into Stage 2 I had to make some changes to the existing code. 

Ball
----

The original Ball class was renamed as1Ball. This was changed to allow the definition of
a new Ball class which acts as an adapter to allows as1Ball to be used as a QGraphicsItem. 

ConfigReader
------------

The ConfigReader class was extended to accomodate for additional variables in the configuration
file. 

Dialog
------

The functionality of the original Dialog class has been replaced with TableScene and 
TableView classes which subclass QGraphicsScene and QGraphicsView respectively. 


Coordinate
----------

The coordinate class was modified to get the frame width and height from the 
configuration file rather than storing this within Coordinate. 
An additional constructor was also added for convenience. 


Design decisions
================

As mentioned above the Ball class acts as an adapter to allow as1Ball to be used as a 
QGraphicsItem. Ball inherits from both QGraphicsItem (publicly) and as1Ball (privately), 
making this a use of the Class Adapter design pattern. 

Extension
=========

For the extension I implemented regenerating bricks. Any brick that has previously died
can reappear randomly. Bricks that reappear are given a random number of lives, and are
given a different colour. 

The extension is customisable in terms of:

 * The maximum number of lives a regenerated brick can be given
 * The probability (per frame) that a given dead brick can reappear
 * The colour of the regenerated brick 

While only previously defined bricks can reappear, bricks can be defined as initially 
invisible, and these bricks can 'regenerate'. 

I also added the number of lives that each brick has to the brick. This feature can be 
disabled in the config file. 
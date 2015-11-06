## Camera

### Goals:

1. Use Perlin noise to distort a mesh
2. Control the distortion via the kinect
3. Color the mesh based on color sampled from the camera

#### 1. How it works
 1. Perlin noise is generated with time as a variable.
 2. The kinect finds the position between the user's hands.
 3. The distance from each point to the center of the sphere is scaled by the perlin noise and the hand distance.
 4. Color is sampled from the camera and mapped to the sphere.

#### 2. Issues
 I bit off a little more than I could chew with this one.  


#### 3. What I would change 
 Using perline noise to directly change the position of the mesh vertices worked but ended up looking more "random" than I really wanted.  There was no continuity or relationship between each point.  If I had to do it again I'd try GlSL shaders.
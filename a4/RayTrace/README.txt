README
Justin Guze
Ray Tracer

Feature Overview:
 - Basic Lambertian Shading
 - Full Blinn-Phong Shading
 - Multiple Light Sources
 - Reflection
 - Shadows
 - Soft Shadows
 - Area Lights
 - Point Lights
 - Anti Aliasing with Jittering
 - Obj File Loading
 - Sphere Intersection
 - Triangle Intersection
 - Scene Graph
 - OpenGL view with Camera Movement
 - Pre-loaded with various material types
 - Perfect Mirrors
 - Cubes and Triangle Meshes
 - Bounding Boxes

HOW TO:
	To ray trace an image, simply hit the 'Ray Trace' button. It will show up in the image to the left.
	To change the shading model, select one of the two from the Shade Model UI container.
	To save an image, choose 'Save Image'
	To clear the scene, press 'Clear Scene'
	To load an external obj file, click 'Load OBJ file'
	To move the camera, left-click to rotate, and right-click to zoom.
 
Features:

Basic Lambertian Shading:
	The default option for ray tracing. Does the most basic shading in that it only takes into account diffuse light. This option can be changed in the UI under 'Shade Model'
	and choosing 'Full Shading'

Full Blinn-Phong Shading
	The much more robust shading option can be selected by choosing, under 'Shade Model' the option 'Blinn-Phong Shading'. This encompasses all the light possibilities for a material,
	such as diffusion, ambient, and specular light. This shading model is also the only one to 

Multiple Light Sources
	The code encompasses the use of multiple light sources in the scene.
	
Reflection
	Materials that can reflect light with the appropriate specular coefficient set will reflect rays to obtain colour from other objects that it relfects to. This is implemented
	by reusing the ray intersection and colour code to recursively fire rays until we hit RAY_MAX_DEPTH.

Shadows
	A shadow ray is fired for every intersection point found by a ray. It fires a shadow ray looking for objects between the point and the current light source. 

Soft Shadows
	Soft shadows were implemented to see the full umbra coming from light. This is most notably seen when using area lights.
	
Point Lights
	The most basic kind of light can be handled by the scene.

Area Lights
	Lights that encompass more that one point can be added completely as one object. In reality, it's a randomized set of point lights in the
	area covered by the area light. 

Anti Aliasing with Jittering
	Anti aliasing is added in the ray tracer, along with an option in the UI to increase the amount of rays rays fired per pixel. Note that
	the number of rays grows in an n^2 fashion. Jittering was added by taking a preset random set of numbers, and jittering the pixels each ray
	by those random numbers.
	
Obj File Loading
	An obj file can be loaded into the scene to create a complex triangle mesh that can also be raytraced.

Sphere Intersection
	The easiest kind of intersection

Triangle Intersection
	Reduced to barycentric points, the intersection between a ray and triangle is found.

Scene Graph
	A full fledged scene graph is created to handle all possible objects in the scene along with a transformation
	to avoid creating 100s of primitives. Then, we can add children that are affected by the same matrix transformation
	to create very complex objects easily.

OpenGL with Camera Movement
	You can move the camera around in an OpenGL view that shows the non ray traced objects. Then, by pressing 'Ray Trace' we can
	ray trace the objects from that specific point.

Various Materials
	The code comes preloaded with many different materials to try out. This only affects
	the first object in the scene graph.

Perfect Mirrors
	Objects can be of a type that is a perfect mirror and reflects all light. This also means mirrors in mirrors reflect
	until MAX_DEPTH.

Cubes and Triangle Meshes
	A cube can be created using a preset triangle mesh. Any shape can be created by specifying it in an obj file
	and loading it as a triangle mesh.

Bounding Boxes
	Triangle Meshes created from OBJ files will have bounding boxes associanted with them to increase rendering time


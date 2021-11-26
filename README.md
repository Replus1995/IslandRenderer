# IslandRenderer
## CSC8502 course work

## How to control
* Press O to start/stop camera animation.
* Press L to start/stop day/night loop.
  
## Features
* Compiled with win10 sdk 10.0.19041.0 and build tool v142
* Using defered shading.
* Only calculate shadow for the directional light.
* Have day/night loop.
* Have a camera keyframe animation.
* Using scene graph.
* Using frustum to cull primitives and point lights.
* Draw skybox after combine frame buffers.
* Draw transparent objects after skybox.
* Limited support for GLTF 2.0 (Only reads meshes & materials in file)
* GLTF/GLB loader is base on tinygltf.(https://github.com/syoyo/tinygltf)
* Using Physical Base Rendering.

## New in NCLGL
* SOIL library removed.(Because of conflicting with std_image)
* ReMaterial: Base class for all object materials, contains a shader pointer & shader params.
* RePrimitive: Class for renderable object, contains a Mesh pointer & ReMaterial pointer.
* ReFrustum: Almost the same as Frustum class described in tutorial. 
* ReFrustumObject: Base class for objects in Frustum Culling.
* ReDLight: Directional light class. Conatins light direction, colour, strength & distance(To determine where to place the shadow camera). Contains a Quad primitive to render in defered shading.
* ReSceneNode: Only handles transform, have multiple components.
* ReNodeComponent: Base class for components held by ReSceneNode.
  * RePrimitiveComponent: Contains a RePrimitive pointer. Base class for renderable objects in Scene Graph. Should be added to one ReSceneNode.
  * RePointLightComponent: Contains a RePrimitive pointer for drawing point light in defered shading. Contains light position, colour & radius. Should be added to one ReSceneNode.
* ReFrameBuffer: Base class for using FBO.
  * ReLightBuffer: Contains one light diffuse texture & one light specular texture.
  * ReSceneBuffer: Contains one base colour texture, one normal texture, one emissive texture, one metallic roughness texture & one depth texture.
    * metallic roughness texture: r->metallic, g->roughness, b->ambient occlution
  * ReShadowBuffer: Contains one depth texture.

## Project files
* DayLooper: A class to control strength & direction of directional light, in order to simulate day&night.
* CameraRoute: A class to control camera keyframe animation. 
* PrimitiveLibrary: A class to load some 'common' primitives.
* SceneGenerator: A class to generate the scene graph.
* PrimitiveFilter: A class to cull opaque & transparent objects inside view.
* PointLightFilter: A class to cull point lights inside view.
* ShadowFilter: A class to select objects which should be rendered in shadow pass.(No view culling)
* GLTFPrimitiveMesh: A child class of Mesh to read mesh data in gltf/glb file.
* GLTFLoader: A class to load meshes and materials from a gltf/glb file.
* Materials/*Mat.h: Materials for different objects in scene. 


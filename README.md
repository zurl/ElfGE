The Elf Game Engine
========================

依赖：
stb_image.h(include)  
glfw,glew,assimp(include自行,lib自行)  


开发者手册
### 架构
所有物体是GameObject
GameObject有子物体，继承结构形成树  
每个场景有根物体（不要操作根物体）  

GameObject上有Transform  
Transform提供物体的位移选择缩放  

GameObject上有Component  
GameObject通过Component支持各种效果  

### 内建的Component
Model(物体模型)  
MeshRenderer(渲染器)  
> 一个物体如果想被显示，至少要求Model和Renderer

Lighting(光源)  
Camera(摄像机)  
GameScript(脚本，使用的话请继承他 并override update start)  
### 其他
光照请继承Lighting实现update(Shader)


### LICENSE

MIT
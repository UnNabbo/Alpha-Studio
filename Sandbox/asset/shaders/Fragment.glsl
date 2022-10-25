#type vertex
#version 450 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aNormal; // the position variable has attribute position 0
layout (location = 2) in vec2 aUVs; // the position variable has attribute position 0
layout (location = 3) in vec3 aTangets; // the position variable has attribute position 0
layout (location = 4) in vec3 abitangets; // the position variable has attribute position 0



layout(std140, binding = 0) uniform Camera
{
	mat4 u_ViewProjection;
};

layout (location = 0) out vec3 outColor;

void main()
{
    outColor = aNormal;
    gl_Position = u_ViewProjection * vec4(aPos, 1.0f); // see how we directly give a vec3 to vec4's constructor
}

#type pixel
#version 450 core
layout(location = 0) out vec4 FragColor;

layout (location = 0) in vec3 inColor;

void main()
{
    FragColor = vec4(inColor,1.0f);
} 
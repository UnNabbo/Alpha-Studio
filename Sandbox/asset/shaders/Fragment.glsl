
#type vertex
#version 450 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aNormal; // the position variable has attribute position 0


layout(std140, binding = 0) uniform Camera
{
	mat4 u_ViewProjection;
};


void main()
{
    gl_Position = u_ViewProjection * vec4(aPos * 100, 1.0f); // see how we directly give a vec3 to vec4's constructor
}

#type pixel
#version 450 core
layout(location = 0) out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f,0,0,1.0f);
} 

#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 color;
out vec3 retcolor;
void main()
{
    gl_Position = position;
    retcolor = color;
};

#shader fragment
#version 330 core
#extension GL_ARB_separate_shader_objects : enable
uniform vec4 color;
in vec3 retcolor;
out vec4 FragColor;
//uniform float color;
void main()
{
    // Interpolate color based on Y-coordinate
    FragColor = vec4(retcolor,0);
};
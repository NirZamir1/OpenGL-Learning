#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 color;
void main()
{
    vec4 modifiedPosition = position;
    gl_Position = modifiedPosition;
};

#shader fragment
#version 330 core
#extension GL_ARB_separate_shader_objects : enable
out vec4 FragColor;
uniform float color;
void main()
{
    // Interpolate color based on Y-coordinate
    FragColor = vec4(color, 1.0, 1.0, 1.0);
};
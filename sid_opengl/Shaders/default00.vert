#version 330 core
layout(location=0) in vec3 position;
layout(location=1) in vec3 color;
//layout(location = 2) in vec2 text_coord;
out vec3 fragColor; // New color attribute
//out vec2 texture_coord; // New texture coord attribute
uniform float scale; //scaling factor

//mvp matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	gl_Position = proj*view*model*vec4(position,1.0);
	fragColor = color;
	//texture_coord = text_coord;
};
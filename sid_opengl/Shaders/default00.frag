#version 330 core
in vec3 fragColor;
//in vec2 texture_coord;
out vec4 final_color;

uniform  sampler2D texture_slot;

void main(){
//final_color = texture(texture_slot,texture_coord);
final_color = vec4(fragColor,1.0f);
//final_color = vec4(texture_coord,0.0f, 1.0f);
};
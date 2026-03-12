#version 450

//shader input
layout (location = 0) in vec4 inColor;

//output write
layout (location = 0) out vec4 outFragColor; //same as render attachment from render pass

void main() 
{
	//return red
	outFragColor = inColor;
}
#version 450
#extension GL_EXT_buffer_reference : require

layout (location = 0) out vec4 outColor;
layout (location = 1) out vec2 outUV;

//same as CPU side
struct Vertex 
{
	vec3 position;
	float uv_x;
	vec3 normal;
	float uv_y;
	vec4 color;
}; 

//declare the vertex buffer, (buffer device address)
// we are declaring it not as a normal descriptor SSBO, but a reference type to a buffer layout. 
//buffer_reference means this object is used from buffer address.
layout(buffer_reference, std430) readonly buffer VertexBuffer
{ 
	Vertex vertices[];
};

//push constants block using the prev stucture
layout( push_constant ) uniform constants
{	
	mat4 render_matrix;
	VertexBuffer vertexBuffer; //pointer
} PushConstants;

void main() 
{	
	//load vertex data from device address
	Vertex v = PushConstants.vertexBuffer.vertices[gl_VertexIndex];

	//output data
	gl_Position = PushConstants.render_matrix * vec4(v.position, 1.0f);
	outColor = v.color;
	outUV.x = v.uv_x;
	outUV.y = v.uv_y;
}
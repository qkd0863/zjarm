#version 330 core

//--- in_Position: attribute index 0
//--- in_Color: attribute index 1

layout (location = 0) in vec3 in_Position; //--- 위치 변수: attribute position 0
layout (location = 1) in vec3 vNormal; //--- 컬러 변수: attribute position 1
layout (location = 2) in vec2 vTexCoord;

out vec3 FragPos; //--- 객체의 위치값을 프래그먼트 세이더로 보낸다.
out vec3 Normal; //--- 노멀값을 프래그먼트 세이더로 보낸다.
out vec2 TexCoord;


out vec3 out_Color; //--- 프래그먼트 세이더에게 전달


uniform vec3 Pos;
uniform mat4 transform;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;


void main(void)
{
gl_Position =    projectionTransform*viewTransform*transform*vec4 (in_Position.x+Pos.x, in_Position.y+Pos.y, in_Position.z+Pos.z, 1.0);
//gl_Position =   transform*vec4 (in_Position.x+Pos.x, in_Position.y+Pos.y, in_Position.z+Pos.z, 1.0);

FragPos = vec3(transform * vec4(in_Position, 1.0)); //--- 객체에 대한 조명 계산을 프래그먼트 셰이더에서 한다. 
//--- 따라서 월드공간에 있는 버텍스 값을 프래그먼트 셰이더로 보낸다.
// Normal = vNormal; //--- 노멀값을 프래그먼트 세이더로 보낸다.
  
	Normal = vec3(transform * vec4(vNormal, 1.0));
	TexCoord = vTexCoord;
}
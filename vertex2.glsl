#version 330 core

//--- in_Position: attribute index 0
//--- in_Color: attribute index 1

layout (location = 0) in vec3 in_Position; //--- ��ġ ����: attribute position 0
layout (location = 1) in vec3 vNormal; //--- �÷� ����: attribute position 1
layout (location = 2) in vec2 vTexCoord;

out vec3 FragPos; //--- ��ü�� ��ġ���� �����׸�Ʈ ���̴��� ������.
out vec3 Normal; //--- ��ְ��� �����׸�Ʈ ���̴��� ������.
out vec2 TexCoord;


out vec3 out_Color; //--- �����׸�Ʈ ���̴����� ����


uniform vec3 Pos;
uniform mat4 transform;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;


void main(void)
{
gl_Position =    projectionTransform*viewTransform*transform*vec4 (in_Position.x+Pos.x, in_Position.y+Pos.y, in_Position.z+Pos.z, 1.0);
//gl_Position =   transform*vec4 (in_Position.x+Pos.x, in_Position.y+Pos.y, in_Position.z+Pos.z, 1.0);

FragPos = vec3(transform * vec4(in_Position, 1.0)); //--- ��ü�� ���� ���� ����� �����׸�Ʈ ���̴����� �Ѵ�. 
//--- ���� ��������� �ִ� ���ؽ� ���� �����׸�Ʈ ���̴��� ������.
// Normal = vNormal; //--- ��ְ��� �����׸�Ʈ ���̴��� ������.
  
	Normal = vec3(transform * vec4(vNormal, 1.0));
	TexCoord = vTexCoord;
}
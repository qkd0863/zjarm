#version 330 core
//--- in_Position: attribute index 0
//--- in_Color: attribute index 1
layout (location = 0) in vec3 in_Position; //--- ��ġ ����: attribute position 0
layout (location = 1) in vec3 in_Color; //--- �÷� ����: attribute position 1
out vec3 out_Color; //--- �����׸�Ʈ ���̴����� ����
uniform vec2 Pos;
uniform mat4 transform;

void main(void)
{
gl_Position = transform*vec4 (in_Position.x+Pos.x, in_Position.y+Pos.y, in_Position.z, 1.0);
out_Color = in_Color;
}
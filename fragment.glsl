#version 330 core

in vec3 out_Color; //--- ���ؽ� ���̴����Լ� ���� ����
out vec4 FragColor; //--- ���� ���

void main ()
{
FragColor = vec4 (out_Color, 1.0);
}
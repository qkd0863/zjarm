#include <iostream>
#include <stdlib.h>
#include <time.h>
#include<cstdlib>
#include<ctime>
#include <gl/glew.h> //--- �ʿ��� ������� include
#include<gl/freeglut.h>
#include <gl/freeglut_ext.h>

struct rect
{
	float x1, x2, y1, y2;
	float r, g, b;
	bool draw = false;
	int dir = 1;//1�� 2��
	int updown = 1;//1�� 2��
};

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Drag(int x, int y);
void TimerFunction(int value);
void convert(int x, int y, float* ox, float* oy);




float r = 0, g = 0, b = 0;
int t = 0;
int a = 0;
rect R[5] = { 0, }, comp[5] = { 0, };
bool left_button;
bool ani = true, color = false, size = false, sup = false, diag = false, zig = false;



void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ���� 
{ //--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ ����
	glutInitWindowSize(500, 500); // �������� ũ�� ����
	glutCreateWindow("Example1"); // ������ ����(������ �̸�)
	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";



	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	glutMouseFunc(Mouse);
	glutMotionFunc(Drag);
	glutMainLoop(); // �̺�Ʈ ó�� ���� 
}

GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	glClearColor(0.5, 0.5, 0.5, 1.0f); // �������� ��blue�� �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�


	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�

	for (int i = 4;i >= 0;i--)
	{
		glColor3f(R[i].r, R[i].g, R[i].b);
		if (R[i].draw)
			glRectf(R[i].x1, R[i].y1, R[i].x2, R[i].y2);
	}

	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	srand(unsigned(time(NULL)));

	switch (key)
	{
	case 'a':
		if (diag)
			diag = false;
		else
			diag = true;
		break; //--- ������ ��������� ����
	case 'i':
		if (zig)
			zig = false;
		else
			zig = true;	
		break;
	case 'c':
		if (size)
			size = false;
		else
			size = true;
		break;
	case 'o':
		if (color)
			color = false;
		else
			color = true;
		break;
	case 's':
		if (ani)
			ani = false;
		else
			ani = true;
		break;
	case 'm':
		for (int i = 0;i < 5;i++)
		{
			R[i].x1 = comp[i].x1;
			R[i].x2 = comp[i].x2;
			R[i].y1 = comp[i].y1;
			R[i].y2 = comp[i].y2;
		}
		break;
	case 'r':
		for (int i = 0;i < 5;i++)
		{
			R[i].x1 = 0;R[i].y1 = 0;R[i].x2 = 0;R[i].y2 = 0;
			R[i].draw = false;
		}
		break;
	case 'q':
		exit(1);
		break; //--- ������ ��������� ����
	}
	glutPostRedisplay(); //--- ������ �ٲ� ������ ��� �ݹ� �Լ��� ȣ���Ͽ� ȭ���� refresh �Ѵ�
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		left_button = true;

	if (state == GLUT_UP)
	{
		for (int i = 0;i < 5;i++)
		{
			if (R[i].draw == false)
			{
				convert(x - 12.5, y + 12.5, &R[i].x1, &R[i].y1);
				convert(x + 12.5, y - 12.5, &R[i].x2, &R[i].y2);
				R[i].r = rand() % 255 / (float)255;R[i].g = rand() % 255 / (float)255;R[i].b = rand() % 255 / (float)255;
				R[i].draw = true;

				comp[i].x1 = R[i].x1;
				comp[i].x2 = R[i].x2;
				comp[i].y1 = R[i].y1;
				comp[i].y2 = R[i].y2;
				break;
			}
		}
		left_button = false;
	}
}


void Drag(int x, int y)
{
	float Rx, Ry, Wx, Wy;

	convert(x, y, &Wx, &Wy);
	convert(x, y, &Rx, &Ry);


	if (left_button == true)
	{
		for (int i = 0;i < 5;i++)
		{
			if (R[i].x1 <= Wx && R[i].x2 >= Wx && R[i].y1 <= Wy && R[i].y2 >= Wy)
			{
				convert(x - 12.5, y + 12.5, &R[i].x1, &R[i].y1);
				convert(x + 12.5, y - 12.5, &R[i].x2, &R[i].y2);
				
				break;
			}

		}
	}
	glutPostRedisplay();
}



void convert(int x, int y, float* ox, float* oy)
{
	int w = 500;
	int h = 500;
	*ox = (float)(x - (float)w / 2.0) * (float)(1.0 / (float)(w / 2.0));
	*oy = -(float)(y - (float)h / 2.0) * (float)(1.0 / (float)(h / 2.0));
}




void TimerFunction(int value)
{
	if (ani)
	{
		if (zig)
		{
			for (int i = 0;i < 5;i++)
			{
				if (R[i].x2 >= 1)
					R[i].dir = 2;



				if (R[i].dir == 1)
				{
					if (a < 50)
					{
						R[i].x1 += 0.01;R[i].x2 += 0.01;
						R[i].y1 += 0.01;R[i].y2 += 0.01;
						a++;
					}
					if (a < 100 && a >= 50)
					{
						R[i].x1 += 0.01;R[i].x2 += 0.01;
						R[i].y1 -= 0.01;R[i].y2 -= 0.01;
						a++;
					}
					if (a >= 100)
						a = 0;
				}
				if (R[i].dir == 2)
				{
					if (a < 50)
					{
						R[i].x1 -= 0.01;R[i].x2 -= 0.01;
						R[i].y1 += 0.01;R[i].y2 += 0.01;
						a++;
					}
					if (a < 100 && a >= 50)
					{
						R[i].x1 -= 0.01;R[i].x2 -= 0.01;
						R[i].y1 -= 0.01;R[i].y2 -= 0.01;
						a++;
					}
					if (a >= 100)
						a = 0;
				}
					
			}
		}
		if (diag)
		{
			for (int i = 0;i < 5;i++)
			{
				if (R[i].x2 >= 1)
					R[i].dir = 2;
				if (R[i].x1 <= -1)
					R[i].dir = 1
					;
				if (R[i].y2 >= 1)
					R[i].updown = 2;
				if (R[i].y1 <= -1)
					R[i].updown = 1;

				if (R[i].updown == 1)
				{				
					if (R[i].dir == 1)//���
					{
						R[i].x1 += 0.01;R[i].x2 += 0.01;
						R[i].y1 += 0.01;R[i].y2 += 0.01;
					}
					if (R[i].dir == 2)//�»�
					{
						R[i].x1 -= 0.01;R[i].x2 -= 0.01;
						R[i].y1 += 0.01;R[i].y2 += 0.01;
					}
				}
				if (R[i].updown == 2)
				{
					if (R[i].dir == 1)//����
					{
						R[i].x1 += 0.01;R[i].x2 += 0.01;
						R[i].y1 -= 0.01;R[i].y2 -= 0.01;
					}
					if (R[i].dir == 2)//����
					{
						R[i].x1 -= 0.01;R[i].x2 -= 0.01;
						R[i].y1 -= 0.01;R[i].y2 -= 0.01;
					}
				}

				
			}
		}
		if (size)
		{
			for (int i = 0;i < 5;i++)
			{
				if (abs(R[i].x1 - R[i].x2) < 0.1 && sup == true)
				{
					R[i].x2 += 0.01;
					R[i].y2 += 0.01;
					if (abs(R[i].x1 - R[i].x2) > 0.1)
					{
						sup = false;
					}
				}
				else
				{
					R[i].x2 -= 0.01;
					R[i].y2 -= 0.01;	
					if (abs(R[i].x1 - R[i].x2) < 0.02)
					{
						sup = true;
					}
				}
			}
		}
		if (color)
		{
			for (int i = 0;i < 5;i++)
			{
				R[i].r = rand() % 255 / (float)255;R[i].g = rand() % 255 / (float)255;R[i].b = rand() % 255 / (float)255;
			}
		}
	}

	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}


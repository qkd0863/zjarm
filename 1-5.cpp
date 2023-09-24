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
	float size = 12.5;
};

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Drag(int x, int y);
void TimerFunction(int value);
void convert(int x, int y, float* ox, float* oy);
void coilrect();
void set();



float r = 0, g = 0, b = 0;
int t = 0;
int a = 0;
rect R[40] = { 0, }, er = { 0, };
bool left_button;




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

	set();

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

	for (int i = 0;i <= 40;i++)
	{
		glColor3f(R[i].r, R[i].g, R[i].b);
		if (R[i].draw)
			glRectf(R[i].x1, R[i].y1, R[i].x2, R[i].y2);
	}

	if (er.draw)
	{
		glColor3f(er.r, er.g, er.b);
		glRectf(er.x1, er.y1, er.x2, er.y2);
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

	case 'r':
		set();
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
	{
		left_button = true;
		convert(x - er.size, y + er.size, &er.x1, &er.y1);
		convert(x + er.size, y - er.size, &er.x2, &er.y2);
		er.draw = true;
	}
		

	if (state == GLUT_UP)
	{
		er.draw = false;
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
		er.draw = true;
		convert(x - er.size, y + er.size, &er.x1, &er.y1);
		convert(x + er.size, y - er.size, &er.x2, &er.y2);
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
	coilrect();

	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

void set()
{
	float x, y, Wx, Wy;
	int num = rand() % 20 + 21;

	for (int i = 0;i < num;i++)
	{
		x = rand() % 500;y = rand() % 500;
		convert(x, y, &Wx, &Wy);
		R[i].x1 = Wx;R[i].x2 = Wx + 0.1;
		R[i].y1 = Wy;R[i].y2 = Wy + 0.1;
		R[i].draw = true;

		R[i].r = rand() % 255 / (float)255;R[i].g = rand() % 255 / (float)255;R[i].b = rand() % 255 / (float)255;
	}
	er.r = 0;er.g = 0;er.b = 0;er.size = 12.5;
}


void coilrect()
{
	for (int i = 0;i < 40;i++)
	{
		if (er.x1 <= R[i].x2 && er.x2 >= R[i].x1 && er.y2 > R[i].y1 && er.y1 < R[i].y2 && R[i].draw == true)
		{
			R[i].draw = false;
			er.r = (er.r + R[i].r) / 2.0;er.g = (er.g + R[i].g) / 2.0;er.b = (er.b + R[i].b) / 2.0;
			er.size += 1.0;
		}
	}
}
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
};

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);
void set();



float r = 0, g = 0, b = 0;
int t = 0;
rect R[4] = { 0, };




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
	glutMainLoop(); // �̺�Ʈ ó�� ���� 
}

GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	glClearColor(r, g, b, 1.0f); // �������� ��blue�� �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�

	
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�
	
	glColor3f(R[0].r, R[0].g, R[0].b);
	glRectf(R[0].x1, R[0].y1, R[0].x2, R[0].y2);
	
	glColor3f(R[1].r, R[1].g, R[1].b);
	glRectf(R[1].x1, R[1].y1, R[1].x2, R[1].y2);
	
	glColor3f(R[2].r, R[2].g, R[2].b);
	glRectf(R[2].x1, R[2].y1, R[2].x2, R[2].y2);
	
	glColor3f(R[3].r, R[3].g, R[3].b);
	glRectf(R[3].x1, R[3].y1, R[3].x2, R[3].y2);
	
	

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
	case 'c':
		r = 0; g = 1; b = 1;
		break; //--- ������ û�ϻ����� ����
	case'm':
		r = 1; g = 0; b = 1;
		break;//--- ������ ��ȫ������ ����
	case 'y':
		r = 1; g = 1; b = 0;
		break; //--- ������ ��������� ����
	case 'a':
		r = rand() % 255 / (float)255;
		g = rand() % 255 / (float)255;	
		b = rand() % 255 / (float)255;
		break; //--- ������ ��������� ����
	case 'w':
		r = 1; g = 1; b = 1;
		break; //--- ������ ��������� ����
	case 'k':
		r = 0; g = 0; b = 0;
		break; //--- ������ ��������� ����
	case 't':
		t = 1;
		break; //--- ������ ��������� ����
	case 's':
		t = 0;
		break; //--- ������ ��������� ����
	case 'q':
		exit(1);
		break; //--- ������ ��������� ����
	}
	glutPostRedisplay(); //--- ������ �ٲ� ������ ��� �ݹ� �Լ��� ȣ���Ͽ� ȭ���� refresh �Ѵ�
}


void TimerFunction(int value)
{
	if (t)
	{
		r = rand() % 255 / (float)255;
		g = rand() % 255 / (float)255;
		b = rand() % 255 / (float)255;
	}


	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}


void Mouse(int button, int state, int x, int y)
{
	int comp = y;
	if (comp > 250)
		comp = 500 - comp;
	else
		comp = 500 - y;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		for (int i = 0;i < 4;i++)
		{
			if ((R[i].x1 + 1) * (float)250 <= x && (R[i].x2 + 1) * (float)250 >= x && (R[i].y1 + 1) * (float)250 <= comp && (R[i].y2 + 1) * (float)250 >= comp)
			{
				R[i].r = rand() % 255 / (float)255;R[i].g = rand() % 255 / (float)255;R[i].b = rand() % 255 / (float)255;
				break;
			}

			if (i == 3)
			{
				r = rand() % 255 / (float)255;
				g = rand() % 255 / (float)255;
				b = rand() % 255 / (float)255;
			}
		}
	}


	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		for (int i = 0;i < 4;i++)
		{
			if ((R[i].x1 + 1) * (float)250 <= x && (R[i].x2 + 1) * (float)250 >= x && (R[i].y1 + 1) * (float)250 <= y && (R[i].y2 + 1) * (float)250 >= y)
			{
				for (int j = 0;j < 4;j++)
				{
					if (R[j].x2 - R[j].x1 > 0.2)
					{
						R[j].x1 += (float)50 / 500;R[j].y1 += (float)50 / 500;R[j].x2 -= (float)50 / 500;R[j].y2 -= (float)50 / 500;
					}								
					else
					{
						break;
					}
				}
				break;
			}

			if (i == 3)
			{
				for (int j = 0;j < 4;j++)
				{
					if (R[j].x2 - R[j].x1 < 0.8)
					{
						R[j].x1 -= (float)50 / 500;R[j].y1 -= (float)50 / 500;R[j].x2 += (float)50 / 500;R[j].y2 += (float)50 / 500;
					}				
					else
						break;
				}
			}
		}	
	}
}
void set()
{
	R[0].x1 = 0 + (float)50 / 500;R[0].y1 = 0 + (float)50 / 500;R[0].x2 = 1 - (float)50 / 500;R[0].y2 = 1 - (float)50 / 500;R[0].r = rand() % 255 / (float)255;R[0].g = rand() % 255 / (float)255;R[0].b = rand() % 255 / (float)255;
	R[1].x1 = -1 + (float)50 / 500;R[1].y1 = -1 + (float)50 / 500;R[1].x2 = 0 - (float)50 / 500;R[1].y2 = 0 - (float)50 / 500;R[1].r = rand() % 255 / (float)255;R[1].g = rand() % 255 / (float)255;R[1].b = rand() % 255 / (float)255;
	R[2].x1 = 0 + (float)50 / 500;R[2].y1 = -1 + (float)50 / 500;R[2].x2 = 1 - (float)50 / 500;R[2].y2 = 0 - (float)50 / 500;R[2].r = rand() % 255 / (float)255;R[2].g = rand() % 255 / (float)255;R[2].b = rand() % 255 / (float)255;
	R[3].x1 = -1 + (float)50 / 500;R[3].y1 = 0 + (float)50 / 500;R[3].x2 = 0 - (float)50 / 500;R[3].y2 = 1 - (float)50 / 500;R[3].r = rand() % 255 / (float)255;R[3].g = rand() % 255 / (float)255;R[3].b = rand() % 255 / (float)255;
}
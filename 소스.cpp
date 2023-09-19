#include <iostream>
#include <stdlib.h>
#include <time.h>
#include<cstdlib>
#include<ctime>
#include <gl/glew.h> //--- 필요한 헤더파일 include
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




void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정 
{ //--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정
	glutInitWindowSize(500, 500); // 윈도우의 크기 지정
	glutCreateWindow("Example1"); // 윈도우 생성(윈도우 이름)
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	set();

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	glutMouseFunc(Mouse);
	glutMainLoop(); // 이벤트 처리 시작 
}

GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수
{
	glClearColor(r, g, b, 1.0f); // 바탕색을 ‘blue’ 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	
	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다
	
	glColor3f(R[0].r, R[0].g, R[0].b);
	glRectf(R[0].x1, R[0].y1, R[0].x2, R[0].y2);
	
	glColor3f(R[1].r, R[1].g, R[1].b);
	glRectf(R[1].x1, R[1].y1, R[1].x2, R[1].y2);
	
	glColor3f(R[2].r, R[2].g, R[2].b);
	glRectf(R[2].x1, R[2].y1, R[2].x2, R[2].y2);
	
	glColor3f(R[3].r, R[3].g, R[3].b);
	glRectf(R[3].x1, R[3].y1, R[3].x2, R[3].y2);
	
	

	glutSwapBuffers(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
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
		break; //--- 배경색을 청록색으로 설정
	case'm':
		r = 1; g = 0; b = 1;
		break;//--- 배경색을 자홍색으로 설정
	case 'y':
		r = 1; g = 1; b = 0;
		break; //--- 배경색을 노랑색으로 설정
	case 'a':
		r = rand() % 255 / (float)255;
		g = rand() % 255 / (float)255;	
		b = rand() % 255 / (float)255;
		break; //--- 배경색을 노랑색으로 설정
	case 'w':
		r = 1; g = 1; b = 1;
		break; //--- 배경색을 노랑색으로 설정
	case 'k':
		r = 0; g = 0; b = 0;
		break; //--- 배경색을 노랑색으로 설정
	case 't':
		t = 1;
		break; //--- 배경색을 노랑색으로 설정
	case 's':
		t = 0;
		break; //--- 배경색을 노랑색으로 설정
	case 'q':
		exit(1);
		break; //--- 배경색을 노랑색으로 설정
	}
	glutPostRedisplay(); //--- 배경색이 바뀔 때마다 출력 콜백 함수를 호출하여 화면을 refresh 한다
}


void TimerFunction(int value)
{
	if (t)
	{
		r = rand() % 255 / (float)255;
		g = rand() % 255 / (float)255;
		b = rand() % 255 / (float)255;
	}


	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정
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
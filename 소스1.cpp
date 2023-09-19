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
	bool draw = false;
};

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Drag(int x, int y);
void TimerFunction(int value);
void convert(int x, int y, float* ox, float* oy);

void set();



float r = 0, g = 0, b = 0;
int t = 0;
rect R[5] = { 0, };
bool left_button;




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
	glutMouseFunc(Mouse);
	glutMotionFunc(Drag);
	glutMainLoop(); // 이벤트 처리 시작 
}

GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수
{
	glClearColor(r, g, b, 1.0f); // 바탕색을 ‘blue’ 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기


	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다

	for (int i = 4;i >= 0;i--)
	{
		glColor3f(R[i].r, R[i].g, R[i].b);
		if(R[i].draw)
			glRectf(R[i].x1 , R[i].y1 , R[i].x2 , R[i].y2 );
	}
	
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
	case 'a':
		for (int i = 4;i >= 0;i--)
		{
			if (!R[i].draw)
			{
				R[i].draw = true;
				break;
			}
				
		}
		break; //--- 배경색을 노랑색으로 설정
	case 'q':
		exit(1);
		break; //--- 배경색을 노랑색으로 설정
	}
	glutPostRedisplay(); //--- 배경색이 바뀔 때마다 출력 콜백 함수를 호출하여 화면을 refresh 한다
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		left_button = true;

	if (state == GLUT_UP)
	{
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

void set()
{
	float x, y, Wx, Wy;

	for (int i = 4;i >= 0;i--)
	{
		x = rand() % 500;y = rand() % 500;
		convert(x, y, &Wx, &Wy);
		R[i].x1 = Wx;R[i].x2 = Wx + 0.1;
		R[i].y1 = Wy;R[i].y2 = Wy + 0.1;

		R[i].r = rand() % 255 / (float)255;R[i].g = rand() % 255 / (float)255;R[i].b = rand() % 255 / (float)255;
	}
}

void convert(int x, int y, float* ox, float* oy)
{
	int w = 500;
	int h = 500;
	*ox = (float)(x - (float)w / 2.0) * (float)(1.0 / (float)(w / 2.0));
	*oy = -(float)(y - (float)h / 2.0) * (float)(1.0 / (float)(h / 2.0));
}
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
	bool animation = false;
	float size = 0.001;
	int ani = -1;
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

rect R[5] = { 0, }, ANI[5][8] = { 0, };
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
	glutTimerFunc(100, TimerFunction, 1);
	glutMouseFunc(Mouse);
	glutMainLoop(); // 이벤트 처리 시작 
}

GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수
{
	glClearColor(0.5, 0.5, 0.5, 1.0f); // 바탕색을 ‘blue’ 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기


	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다

	for (int i = 0;i <= 5;i++)
	{
		glColor3f(R[i].r, R[i].g, R[i].b);
		if (R[i].draw && !R[i].animation)
			glRectf(R[i].x1, R[i].y1, R[i].x2, R[i].y2);

		for (int j = 0;j < 8;j++)
		{
			glColor3f(ANI[i][j].r, ANI[i][j].g, ANI[i][j].b);
			if (ANI[i][j].draw && R[i].animation)
				glRectf(ANI[i][j].x1, ANI[i][j].y1, ANI[i][j].x2 - ANI[i][j].size, ANI[i][j].y2 - ANI[i][j].size);
		}
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

	case 'r':
		set();
		break;
	case 'q':
		exit(1);
		break; //--- 배경색을 노랑색으로 설정
	}
	glutPostRedisplay(); //--- 배경색이 바뀔 때마다 출력 콜백 함수를 호출하여 화면을 refresh 한다
}

void Mouse(int button, int state, int x, int y)
{
	float Rx, Ry, Wx, Wy;

	convert(x, y, &Wx, &Wy);
	convert(x, y, &Rx, &Ry);


	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		for (int i = 0;i < 5;i++)
		{
			if (R[i].x1 <= Wx && R[i].x2 >= Wx && R[i].y1 <= Wy && R[i].y2 >= Wy)
			{
				R[i].animation = true;
			}		
		}
	}
	
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
	for (int i = 0;i < 5;i++)
	{
		if (ANI[i][0].x2 - ANI[i][0].x1 - ANI[i][0].size <= 0)
		{
			for (int j = 0;j < 8;j++)
			{
				ANI[i][j].draw = false;
			}
		}


		if (R[i].animation)
		{
			switch (R[i].ani)
			{
			case 1://좌우상하
				ANI[i][0].x1 -= 0.01;ANI[i][0].x2 -= 0.01;

				ANI[i][1].y1 += 0.01;ANI[i][1].y2 += 0.01;

				ANI[i][3].x1 += 0.01;ANI[i][3].x2 += 0.01;
						
				ANI[i][2].y1 -= 0.01;ANI[i][2].y2 -= 0.01;		
				for (int j = 0;j < 4;j++)
				{
					ANI[i][j].size += 0.001;
				}
				break;
			case 2://대각
				ANI[i][0].x1 -= 0.01;ANI[i][0].x2 -= 0.01;
				ANI[i][0].y1 += 0.01;ANI[i][0].y2 += 0.01;

				ANI[i][1].x1 += 0.01;ANI[i][1].x2 += 0.01;
				ANI[i][1].y1 += 0.01;ANI[i][1].y2 += 0.01;

				ANI[i][2].x1 -= 0.01;ANI[i][2].x2 -= 0.01;
				ANI[i][2].y1 -= 0.01;ANI[i][2].y2 -= 0.01;

				ANI[i][3].x1 += 0.01;ANI[i][3].x2 += 0.01;
				ANI[i][3].y1 -= 0.01;ANI[i][3].y2 -= 0.01;
				for (int j = 0;j < 4;j++)
				{
					ANI[i][j].size += 0.001;
				}
				break;
			case 3://8방향
				ANI[i][0].x1 -= 0.01;ANI[i][0].x2 -= 0.01;

				ANI[i][1].y1 += 0.01;ANI[i][1].y2 += 0.01;

				ANI[i][3].x1 += 0.01;ANI[i][3].x2 += 0.01;

				ANI[i][2].y1 -= 0.01;ANI[i][2].y2 -= 0.01;

				ANI[i][4].x1 -= 0.01;ANI[i][4].x2 -= 0.01;
				ANI[i][4].y1 += 0.01;ANI[i][4].y2 += 0.01;

				ANI[i][5].x1 += 0.01;ANI[i][5].x2 += 0.01;
				ANI[i][5].y1 += 0.01;ANI[i][5].y2 += 0.01;

				ANI[i][6].x1 -= 0.01;ANI[i][6].x2 -= 0.01;
				ANI[i][6].y1 -= 0.01;ANI[i][6].y2 -= 0.01;

				ANI[i][7].x1 += 0.01;ANI[i][7].x2 += 0.01;
				ANI[i][7].y1 -= 0.01;ANI[i][7].y2 -= 0.01;
				for (int j = 0;j < 8;j++)
				{
					ANI[i][j].size += 0.001;
				}
				break;
			default:
				break;
			}
		}	
	}

	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정
}

void set()
{
	srand(unsigned(time(NULL)));
	int cnt = 0;
	float x, y, Wx, Wy;
	
	for (int i = 0;i < 5;i++)
	{
		x = rand() % 300+50;y = rand() % 300+50;
		convert(x, y, &Wx, &Wy);
		R[i].x1 = Wx;R[i].x2 = Wx + 0.1;
		R[i].y1 = Wy;R[i].y2 = Wy + 0.1;
		R[i].draw = true;
		R[i].ani = rand() % 3 + 1;
		R[i].r = rand() % 255 / (float)255;R[i].g = rand() % 255 / (float)255;R[i].b = rand() % 255 / (float)255;

		switch (R[i].ani)
		{
		case 1:
			for (int j = 0;j < 4;j++)
			{
				if (ANI[i][j].draw == false)
				{
					ANI[i][j].r = R[i].r;ANI[i][j].g = R[i].g;ANI[i][j].b = R[i].b;
					ANI[i][j].ani = R[i].ani;
					ANI[i][j].draw = true;
				}
			}
			ANI[i][0].x1 = R[i].x1;ANI[i][0].x2 = (R[i].x1 + R[i].x2) / 2.0;
			ANI[i][0].y1 = (R[i].y1 + R[i].y2) / 2.0;ANI[i][0].y2 = R[i].y2;

			ANI[i][1].x1 = (R[i].x1 + R[i].x2) / 2.0;ANI[i][1].x2 = R[i].x2;
			ANI[i][1].y1 = (R[i].y1 + R[i].y2) / 2.0;ANI[i][1].y2 = R[i].y2;

			ANI[i][2].x1 = R[i].x1;ANI[i][2].x2 = (R[i].x1 + R[i].x2) / 2.0;
			ANI[i][2].y1 = R[i].y1;ANI[i][2].y2 = (R[i].y1 + R[i].y2) / 2.0;

			ANI[i][3].x1 = (R[i].x1 + R[i].x2) / 2.0;ANI[i][3].x2 = R[i].x2;
			ANI[i][3].y1 = R[i].y1;ANI[i][3].y2 = (R[i].y1 + R[i].y2) / 2.0;
			break;
		case 2:
			for (int j = 0;j < 4;j++)
			{
				if (ANI[i][j].draw == false)
				{
					ANI[i][j].r = R[i].r;ANI[i][j].g = R[i].g;ANI[i][j].b = R[i].b;
					ANI[i][j].ani = R[i].ani;
					ANI[i][j].draw = true;
				}
			}
			ANI[i][0].x1 = R[i].x1;ANI[i][0].x2 = (R[i].x1 + R[i].x2) / 2.0;
			ANI[i][0].y1 = (R[i].y1 + R[i].y2) / 2.0;ANI[i][0].y2 = R[i].y2;

			ANI[i][1].x1 = (R[i].x1 + R[i].x2) / 2.0;ANI[i][1].x2 = R[i].x2;
			ANI[i][1].y1 = (R[i].y1 + R[i].y2) / 2.0;ANI[i][1].y2 = R[i].y2;

			ANI[i][2].x1 = R[i].x1;ANI[i][2].x2 = (R[i].x1 + R[i].x2) / 2.0;
			ANI[i][2].y1 = R[i].y1;ANI[i][2].y2 = (R[i].y1 + R[i].y2) / 2.0;

			ANI[i][3].x1 = (R[i].x1 + R[i].x2) / 2.0;ANI[i][3].x2 = R[i].x2;
			ANI[i][3].y1 = R[i].y1;ANI[i][3].y2 = (R[i].y1 + R[i].y2) / 2.0;
			break;
		case 3:
			for (int j = 0;j < 8;j++)
			{
				if (ANI[i][j].draw == false)
				{
					ANI[i][j].r = R[i].r;ANI[i][j].g = R[i].g;ANI[i][j].b = R[i].b;
					ANI[i][j].ani = R[i].ani;
					ANI[i][j].draw = true;
				}
			}
			ANI[i][0].x1 = R[i].x1;ANI[i][0].x2 = (R[i].x1 + R[i].x2) / 2.0;
			ANI[i][0].y1 = (R[i].y1 + R[i].y2) / 2.0;ANI[i][0].y2 = R[i].y2;

			ANI[i][1].x1 = (R[i].x1 + R[i].x2) / 2.0;ANI[i][1].x2 = R[i].x2;
			ANI[i][1].y1 = (R[i].y1 + R[i].y2) / 2.0;ANI[i][1].y2 = R[i].y2;

			ANI[i][2].x1 = R[i].x1;ANI[i][2].x2 = (R[i].x1 + R[i].x2) / 2.0;
			ANI[i][2].y1 = R[i].y1;ANI[i][2].y2 = (R[i].y1 + R[i].y2) / 2.0;

			ANI[i][3].x1 = (R[i].x1 + R[i].x2) / 2.0;ANI[i][3].x2 = R[i].x2;
			ANI[i][3].y1 = R[i].y1;ANI[i][3].y2 = (R[i].y1 + R[i].y2) / 2.0;


			ANI[i][4].x1 = R[i].x1;ANI[i][4].x2 = (R[i].x1 + R[i].x2) / 2.0;
			ANI[i][4].y1 = (R[i].y1 + R[i].y2) / 2.0;ANI[i][4].y2 = R[i].y2;

			ANI[i][5].x1 = (R[i].x1 + R[i].x2) / 2.0;ANI[i][5].x2 = R[i].x2;
			ANI[i][5].y1 = (R[i].y1 + R[i].y2) / 2.0;ANI[i][5].y2 = R[i].y2;

			ANI[i][6].x1 = R[i].x1;ANI[i][6].x2 = (R[i].x1 + R[i].x2) / 2.0;
			ANI[i][6].y1 = R[i].y1;ANI[i][6].y2 = (R[i].y1 + R[i].y2) / 2.0;

			ANI[i][7].x1 = (R[i].x1 + R[i].x2) / 2.0;ANI[i][7].x2 = R[i].x2;
			ANI[i][7].y1 = R[i].y1;ANI[i][7].y2 = (R[i].y1 + R[i].y2) / 2.0;
			break;
		default:
			break;
		}
	}
}
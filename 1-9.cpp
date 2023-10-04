#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include<cstdlib>
#include<ctime>
#include <gl/glew.h> //--- �ʿ��� ������� include
#include<gl/freeglut.h>
#include <gl/freeglut_ext.h>

using namespace std;

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
void InitBuffer();
void make_vertexShaders();
void make_fragmentShaders();
void make_shaderProgram();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
char* filetobuf(const char* file);
void settrue(char c);

int Rect[5]{ -1,-1,-1,-1,-1 };
bool give, zig, rectspiral, circlespiral{ false };
bool r[4]={ true,true,true,true }, u[4]={ true, true, true, true};
double x1[5], Y1[5], z1[5];
int k = 0;
float rad = 0.01, t = 0.01;
int c[4] = { 100,100,100,100 };

const GLfloat lineShape[2][3] = { { 0.1, -0.1, 0.0},{ -0.1, -0.1, 0.0 } };

GLfloat triShape[3][3] = { { -0.1, -0.1, 0.0 }, { 0, 0.1, 0.0 }, { 0.1, -0.1, 0.0} };//��
GLfloat triShape2[3][3] = { { -0.1, 0.1, 0.0 }, { -0.1, -0.1, 0.0 }, { 0.1, 0.0, 0.0} };//��
GLfloat triShape3[3][3] = { { -0.1, 0.1, 0.0 }, { 0.1, 0.1, 0.0 }, { 0.0, -0.1, 0.0} };//��
GLfloat triShape4[3][3] = { { 0.1, 0.1, 0.0 }, { 0.1, -0.1, 0.0 }, { -0.1, 0.0, 0.0} };//��
	
const GLfloat RectShape[6][3] = { { -0.2, -0.2, 0.0 }, { -0.2, 0.2, 0.0 }, { 0.2, -0.2, 0.0},
{ -0.2, 0.2, 0.0 },{0.2,0.2,0.0},{0.2,-0.2,0.0}
};

const GLfloat colors[6][3] = { { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 } };

const GLfloat rectcolors[6][3] = {
{ 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 },
{ 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 } };
const GLfloat Poscolor[3] = { 1.0,0.0,1.0 };
const GLfloat linecolor[2][3] = { {1.0,0.0,1.0},{1.0,0.0,1.0 } };

GLfloat Pos[5][3] = { 0, };
GLfloat triPos[5][3] = { 0, };
GLfloat rectPos[5][3] = { 0, };
GLfloat LinePos1[5][3] = { 0, };
GLfloat LinePos2[5][3] = { 0, };
GLfloat LinePos3[5][3] = { 0, };

GLuint vao, vbo[2], TriPosVbo, TriColorVbo, PosVbo[5], ColorVbo, triPosVbo[5], triColor, rectPosVbo[5], rectColor,
linePosVbo[5], lineColorVbo;


GLint width, height;
GLuint shaderProgramID; //--- ���̴� ���α׷� �̸�
GLuint vertexShader; //--- ���ؽ� ���̴� ��ü
GLuint fragmentShader; //--- �����׸�Ʈ ���̴� ��ü







void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ���� 
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example1");
	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	glewInit();
	make_shaderProgram();
	InitBuffer();
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	GLfloat rColor, gColor, bColor;
	rColor = gColor = 0.0;
	bColor = 0.0;
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shaderProgramID);
	glBindVertexArray(vao);





	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position"); //	: 0  Shader�� 'layout (location = 0)' �κ�
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color"); //	: 1

	glEnableVertexAttribArray(PosLocation); // Enable �ʼ�! ����ϰڴ� �ǹ�
	glEnableVertexAttribArray(ColorLocation);

	GLuint changePos = glGetUniformLocation(shaderProgramID, "Pos");



	for (int i = 0; i < 5; ++i)
	{
		if (Rect[i] == 1)
		{
			glUniform2f(changePos, triPos[i][0], triPos[i][1]);
			glBindBuffer(GL_ARRAY_BUFFER, triPosVbo[i]); // VBO Bind
			glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			{
				glBindBuffer(GL_ARRAY_BUFFER, triColor); // VBO Bind
				glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			}
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
	}



	glDisableVertexAttribArray(PosLocation); // Disable �ʼ�!
	glDisableVertexAttribArray(ColorLocation);



	glutSwapBuffers();
	glutPostRedisplay();
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
	case 'f':
		rad = 0.01;
	default:
		settrue(key);
		break;
	case 'q':
		exit(1);
		break;
	}
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	float Rx, Ry, Wx, Wy;

	convert(x, y, &Wx, &Wy);
	convert(x, y, &Rx, &Ry);


	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (k < 4)
		{
			x1[k] = Wx;
			Y1[k] = Wy;
			z1[k] = 0;
			triPos[k][0] = x1[k];
			triPos[k][1] = Y1[k];
			triPos[k][2] = z1[k];
			Rect[k] = 1;
			++k;
		}
	}

	InitBuffer();
}




void convert(int x, int y, float* ox, float* oy)
{
	int w = 800;
	int h = 600;
	*ox = (float)(x - (float)w / 2.0) * (float)(1.0 / (float)(w / 2.0));
	*oy = -(float)(y - (float)h / 2.0) * (float)(1.0 / (float)(h / 2.0));
}




void TimerFunction(int value)
{
	if (give)
	{
		for (int i = 0; i < 4; i++)
		{
			if (r[i])
			{
				if (u[i])
				{
					triPos[i][0] += 0.05f;
					triPos[i][1] += 0.05f;
					glBindBuffer(GL_ARRAY_BUFFER, triPosVbo[i]);
					glBufferData(GL_ARRAY_BUFFER, sizeof(triShape), triShape, GL_DYNAMIC_DRAW);

					if (triPos[i][0] >= 1)
						r[i] = false;
					if (triPos[i][1] >= 1)
						u[i] = false;
				}
				else
				{
					triPos[i][0] += 0.05f;
					triPos[i][1] -= 0.05f;
					glBindBuffer(GL_ARRAY_BUFFER, triPosVbo[i]);
					glBufferData(GL_ARRAY_BUFFER, sizeof(triShape), triShape, GL_DYNAMIC_DRAW);

					if (triPos[i][0] >= 1)
						r[i] = false;
					if (triPos[i][1] <= -1)
						u[i] = true;
				}
			}
			else
			{
				if (u[i])
				{
					triPos[i][0] -= 0.05f;
					triPos[i][1] += 0.05f;
					glBindBuffer(GL_ARRAY_BUFFER, triPosVbo[i]);
					glBufferData(GL_ARRAY_BUFFER, sizeof(triShape), triShape, GL_DYNAMIC_DRAW);

					if (triPos[i][0] <= -1)
						r[i] = true;
					if (triPos[i][1] >= 1)
						u[i] = false;
				}
				else
				{
					triPos[i][0] -= 0.05f;
					triPos[i][1] -= 0.05f;
					glBindBuffer(GL_ARRAY_BUFFER, triPosVbo[i]);
					glBufferData(GL_ARRAY_BUFFER, sizeof(triShape), triShape, GL_DYNAMIC_DRAW);

					if (triPos[i][0] <= -1)
						r[i] = true;
					if (triPos[i][1] <= -1)
						u[i] = true;
				}
			}
			
			
		}
		std::cout << triPos[0][0] << triPos[0][1] << std::endl;
	}
	if (zig)
	{
		for (int i = 0; i < 4; i++)
		{
			if (c[i] >= 5)
			{
				if (r[i])
				{
					triPos[i][0] += 0.05f;
					glBindBuffer(GL_ARRAY_BUFFER, triPosVbo[i]);
					glBufferData(GL_ARRAY_BUFFER, sizeof(triShape2), triShape2, GL_DYNAMIC_DRAW);

					if (triPos[i][0] >= 1)
					{
						r[i] = false;
						c[i] = 0;
					}
				}
				else
				{
					triPos[i][0] -= 0.05f;
					glBindBuffer(GL_ARRAY_BUFFER, triPosVbo[i]);
					glBufferData(GL_ARRAY_BUFFER, sizeof(triShape4), triShape4, GL_DYNAMIC_DRAW);

					if (triPos[i][0] <= -1)
					{
						r[i] = true;
						c[i] = 0;
					}
				}
			}
			else
			{
				if (u[i])
				{
					triPos[i][1] += 0.05f;
					glBindBuffer(GL_ARRAY_BUFFER, triPosVbo[i]);
					glBufferData(GL_ARRAY_BUFFER, sizeof(triShape3), triShape3, GL_DYNAMIC_DRAW);

					if (triPos[i][1] >= 1)
					{
						u[i] = false;					
					}
					c[i]++;
				}
				else
				{
					triPos[i][1] -= 0.05f;
					glBindBuffer(GL_ARRAY_BUFFER, triPosVbo[i]);
					glBufferData(GL_ARRAY_BUFFER, sizeof(triShape), triShape, GL_DYNAMIC_DRAW);

					if (triPos[i][1] <= -1)
					{
						u[i] = true;				
					}
					c[i]++;
				}
			}
		}	
	}
	if (rectspiral)
	{
		
	}
	if (circlespiral)
	{
		for (int i = 0; i < 4; i++)
		{
			triPos[i][0] += cos(t) / 100.0 * rad;
			triPos[i][1] += sin(t) / 100.0 * rad;
			glBindBuffer(GL_ARRAY_BUFFER, triPosVbo[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(triShape), triShape, GL_DYNAMIC_DRAW);
			t += 0.1;

			if (t >= 3.141592 * 2)
				t = 0;

			rad += 0.1;
		}
	}

	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}


GLchar* vertexSource, * fragmentSource; //--- �ҽ��ڵ� ���� ����

void make_vertexShaders()
{
	vertexSource = filetobuf("vertex.glsl");
	//--- ���ؽ� ���̴� ��ü �����
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
	//--- ���ؽ� ���̴� �������ϱ�
	glCompileShader(vertexShader);
	//--- �������� ����� ���� ���� ���: ���� üũ
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		cerr << "ERROR: vertex shader ������ ����\n" << errorLog << endl;
		return;
	}
}

void make_fragmentShaders()
{
	fragmentSource = filetobuf("fragment.glsl");
	//--- �����׸�Ʈ ���̴� ��ü �����
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
	//--- �����׸�Ʈ ���̴� ������
	glCompileShader(fragmentShader);
	//--- �������� ����� ���� ���� ���: ������ ���� üũ
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		cerr << "ERROR: fragment shader ������ ����\n" << errorLog << endl;
		return;
	}
}


void make_shaderProgram()
{
	make_vertexShaders(); //--- ���ؽ� ���̴� �����
	make_fragmentShaders(); //--- �����׸�Ʈ ���̴� �����
	//-- shader Program
	shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexShader);
	glAttachShader(shaderProgramID, fragmentShader);
	glLinkProgram(shaderProgramID);
	//--- ���̴� �����ϱ�
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//--- Shader Program ����ϱ�
	glUseProgram(shaderProgramID);
}



char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb"); // Open file for reading
	if (!fptr) // Return NULL on failure
		return NULL;
	fseek(fptr, 0, SEEK_END); // Seek to the end of the file
	length = ftell(fptr); // Find out how many bytes into the file we are
	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator
	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file
	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer
	fclose(fptr); // Close the file
	buf[length] = 0; // Null terminator
	return buf; // Return the buffer
}



void InitBuffer()
{
	

	for (int i = 0; i < 4; ++i)
	{
		glGenBuffers(1, &triPosVbo[i]);
		glBindBuffer(GL_ARRAY_BUFFER, triPosVbo[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triShape), triShape, GL_DYNAMIC_DRAW);
		glGenBuffers(1, &triColor);
		glBindBuffer(GL_ARRAY_BUFFER, triColor);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	}
}


void settrue(char c)
{
	switch (c)
	{
	case 'a':
		give = true;
		zig = false;
		rectspiral = false;
		circlespiral = false;
		break;
	case 's':
		give = false;
		zig = true;
		rectspiral = false;
		circlespiral = false;
		break;
	case 'd':
		give = false;
		zig = false;
		rectspiral = true;
		circlespiral = false;
		break;
	case 'f':
		give = false;
		zig = false;
		rectspiral = false;
		circlespiral = true;
		break;
	default:
		break;
	}
}
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



double x1[5], Y1[5], z1[5];
float mx = 0, my = 0;
bool left_button;
bool c1 = false, c2 = false, c3 = false, c4 = false, rect = false;


GLfloat lineShape1[2][3] = { { -0.1, 0.1, 0.0},{ 0.1, 0.1, 0.0 } };
GLfloat lineShape2[2][3] = { { 0.1, 0.1, 0.0},{ 0.1, -0.1, 0.0 } };
GLfloat lineShape3[2][3] = { { 0.1, -0.1, 0.0},{ -0.1, -0.1, 0.0 } };
GLfloat lineShape4[2][3] = { { -0.1, -0.1, 0.0},{ -0.1, 0.1, 0.0 } };

GLfloat triShape[3][3] = { { -0.1, -0.1, 0.0 }, { 0.0, 0.1, 0.0 }, { 0.1, -0.1, 0.0} };

GLfloat RectShape[6][3] = {
{ -0.1, -0.1, 0.0 }, { -0.1, 0.1, 0.0 }, { 0.1, -0.1, 0.0},
{ -0.1, 0.1, 0.0 }, { 0.1, 0.1, 0.0}, { 0.1, -0.1, 0.0}
};


const GLfloat colors1[6][3] = { { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 } };




const GLfloat Poscolor[3] = { 1.0,0.0,1.0 };
const GLfloat linecolor[2][3] = { {1.0,0.0,0.0},{0.0,1.0,0.0 } };
const GLfloat tricolor[6][3] = { {0.0,1.0,0.0},{0.0,1.0,0.0 } ,{0.0,1.0,0.0 } ,{0.0,1.0,0.0},{0.0,1.0,0.0 } ,{0.0,1.0,0.0 } };
const GLfloat rectcolors[9][3] = {
{ 1.0, 1.0, 0.0 }, { 1.0, 1.0, 0.0 }, { 1.0, 1.0, 0.0 },
{ 1.0, 1.0, 0.0 }, { 1.0, 1.0, 0.0 }, { 1.0, 1.0, 0.0 },
{ 1.0, 1.0, 0.0 }, { 1.0, 1.0, 0.0 }, { 1.0, 1.0, 0.0 } };
const GLfloat PenColors[9][3] = {
{ 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 },
{ 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 },
{ 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 } };



GLfloat PentaPos[5][3] = { {0.5,-0.5,0.0} };
GLfloat Pos[5][3] = { 0, };
GLfloat triPos[5][3] = { {0.5,0.5,0.0} };
GLfloat rectPos[5][3] = { {-0.5,-0.5,0.0} };
GLfloat LinePos[5][3] = { 0, };


GLuint linePosVbo[4], lineColorVbo[4];
GLuint TriPosVbo, TriColorVbo;
GLuint PosVbo, ColorVbo;
GLuint triPosVbo, triColor;
GLuint rectPosVbo, rectColor;
GLuint PenPosVbo, PenColor;


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
	glutMotionFunc(Drag);
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutTimerFunc(100, TimerFunction, 1);
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





	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position"); //	: 0  Shader�� 'layout (location = 0)' �κ�
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color"); //	: 1

	glEnableVertexAttribArray(PosLocation); // Enable �ʼ�! ����ϰڴ� �ǹ�
	glEnableVertexAttribArray(ColorLocation);

	GLuint changePos = glGetUniformLocation(shaderProgramID, "Pos");



	for (int i = 0;i < 4;i++)
	{
		glUniform2f(changePos, LinePos[i][0], LinePos[i][1]);
		glBindBuffer(GL_ARRAY_BUFFER, linePosVbo[i]); // VBO Bind
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		{
			glBindBuffer(GL_ARRAY_BUFFER, lineColorVbo[i]); // VBO Bind
			glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		}
		glDrawArrays(GL_LINES, 0, 3);
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
	case 'q':
		exit(1);
		break;
	}

	
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	srand((unsigned int)time(NULL));

	float Rx, Ry, Wx, Wy;


	convert(x, y, &Wx, &Wy);
	convert(x, y, &Rx, &Ry);



	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (abs(Wx - lineShape1[0][0]) < 0.03 && abs(Wy - lineShape1[0][1]) < 0.03)//c1
		{
			c1 = true;
		}
		if (abs(Wx - lineShape1[1][0]) < 0.03 && abs(Wy - lineShape1[1][1]) < 0.03)//c1
		{
			c2 = true;
		}
		if (abs(Wx - lineShape3[0][0]) < 0.03 && abs(Wy - lineShape3[0][1]) < 0.03)//c1
		{
			c3 = true;
		}
		if (abs(Wx - lineShape3[1][0]) < 0.03 && abs(Wy - lineShape3[1][1]) < 0.03)//c1
		{
			c4 = true;
		}
		if (lineShape1[0][0] <= Wx && lineShape1[1][0] >= Wx)
		{
			if (lineShape2[0][1] >= Wy && lineShape2[1][1] <= Wy)
			{
				if (!c1 || !c2 || !c3 || !c4)
				{
					rect = true;
					
				}				
			}
		}
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		c1 = false;
		c2 = false;
		c3 = false;
		c4 = false;
		rect = false;
	}
}

void Drag(int x, int y)
{
	float Rx, Ry, Wx, Wy;

	convert(x, y, &Wx, &Wy);
	convert(x, y, &Rx, &Ry);

	mx = (lineShape1[0][0] + lineShape1[1][0]) / 2.0;my = (lineShape2[0][1] + lineShape2[1][1]) / 2.0;

	if (c1)
	{
		lineShape1[0][0] = Wx;lineShape1[0][1] = Wy;
		lineShape4[1][0] = Wx;lineShape4[1][1] = Wy;
	}
	if (c2)
	{
		lineShape1[1][0] = Wx;lineShape1[1][1] = Wy;
		lineShape2[0][0] = Wx;lineShape2[0][1] = Wy;
	}
	if (c3)
	{
		lineShape2[1][0] = Wx;lineShape2[1][1] = Wy;
		lineShape3[0][0] = Wx;lineShape3[0][1] = Wy;
	}
	if (c4)
	{
		lineShape3[1][0] = Wx;lineShape3[1][1] = Wy;
		lineShape4[0][0] = Wx;lineShape4[0][1] = Wy;
	}
	if (rect)
	{
		for (int i = 0;i < 2;i++)
		{
			lineShape1[i][0] += (Wx - mx) / 20.0;lineShape1[i][1] += (Wy - my) / 20.0;
			lineShape2[i][0] += (Wx - mx) / 20.0;lineShape2[i][1] += (Wy - my) / 20.0;
			lineShape3[i][0] += (Wx - mx) / 20.0;lineShape3[i][1] += (Wy - my) / 20.0;
			lineShape4[i][0] += (Wx - mx) / 20.0;lineShape4[i][1] += (Wy - my) / 20.0;
		}
	}
	InitBuffer();
	glutPostRedisplay();
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
	glGenBuffers(1, &linePosVbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, linePosVbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineShape1), lineShape1, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &lineColorVbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, lineColorVbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(linecolor), linecolor, GL_STATIC_DRAW);

	

	glGenBuffers(1, &linePosVbo[1]);
	glBindBuffer(GL_ARRAY_BUFFER, linePosVbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineShape2), lineShape2, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &lineColorVbo[1]);
	glBindBuffer(GL_ARRAY_BUFFER, lineColorVbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(linecolor), linecolor, GL_STATIC_DRAW);



	glGenBuffers(1, &linePosVbo[2]);
	glBindBuffer(GL_ARRAY_BUFFER, linePosVbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineShape3), lineShape3, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &lineColorVbo[2]);
	glBindBuffer(GL_ARRAY_BUFFER, lineColorVbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(linecolor), linecolor, GL_STATIC_DRAW);



	glGenBuffers(1, &linePosVbo[3]);
	glBindBuffer(GL_ARRAY_BUFFER, linePosVbo[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineShape4), lineShape4, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &lineColorVbo[3]);
	glBindBuffer(GL_ARRAY_BUFFER, lineColorVbo[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(linecolor), linecolor, GL_STATIC_DRAW);
}

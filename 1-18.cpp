#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include<cstdlib>
#include<ctime>
#include <gl/glew.h> //--- 필요한 헤더파일 include
#include<gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>

using namespace std;



GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Drag(int x, int y);
void TimerFunction(int value);
GLvoid Special(int key, int x, int y);
void convert(int x, int y, float* ox, float* oy);
void InitBuffer();
void make_vertexShaders();
void make_fragmentShaders();
void make_shaderProgram();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
char* filetobuf(const char* file);
void set();


double x1[5], Y1[5], z1[5];
float mx = 0, my = 0;
float r1 = 0, r2 = 0, r3 = 0, r4 = 0, r5 = 0, r6 = 0;
float Y = 0;
bool left_button;
bool h1 = false, h2 = false, h3 = false, h4 = false;
bool t1 = false, t2 = false;
bool anio = false,anir = false;
bool yrot = false;

bool Hex = false;


GLfloat HexahedronShape[36][3];
GLfloat HexahedronColors[36][3];
GLfloat TetrahedronShape[18][3];
GLfloat TetrahedronColors[18][3];



GLuint HexPosVbo, TetPosVbo;
GLuint HexColor, TetColor;


GLint width, height;
GLuint shaderProgramID; //--- 세이더 프로그램 이름
GLuint vertexShader; //--- 버텍스 세이더 객체
GLuint fragmentShader; //--- 프래그먼트 세이더 객체







void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정 
{
	set();
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Example1");
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	glewInit();
	make_shaderProgram();
	InitBuffer();
	glutMouseFunc(Mouse);
	glutMotionFunc(Drag);
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutSpecialFunc(Special);
	glutTimerFunc(100, TimerFunction, 1);

	glutMainLoop();
}

GLUquadricObj* qobj;
GLUquadricObj* qobj2;

GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수
{
	GLfloat rColor, gColor, bColor;
	rColor = gColor = 0.0;
	bColor = 0.0;
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	
	

	glUseProgram(shaderProgramID);



	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); //--- z축으로 -3만큼 이동  카메라를 z축으로 3만큼 이동한 효과
	unsigned int viewLocation = glGetUniformLocation(shaderProgramID, "viewTransform"); //--- 버텍스 세이더에서 viewTransform 변수위치
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);


	glm::mat4 projection = glm::mat4(1.0f);

	projection = glm::ortho(0.0f, 0.0f, -1.0f, 1.0f, -1.0f, 1.0f); //--- 투영 공간 설정: [-100.0, 100.0] 
	

	
	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f); //--- 투영 공간 설정: fovy, aspect, near, far
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, -2.0)); //--- 공간을 z축 이동
	unsigned int projectionLocation = glGetUniformLocation(shaderProgramID, "projectionTransform"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);



	glEnable(GL_DEPTH_TEST);


	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position"); //	: 0  Shader의 'layout (location = 0)' 부분
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color"); //	: 1

	glEnableVertexAttribArray(PosLocation); // Enable 필수! 사용하겠단 의미
	glEnableVertexAttribArray(ColorLocation);




	
	
	glm::mat4 z = glm::mat4(1.0f);
	glm::mat4 xy = glm::mat4(1.0f);
	
	
	glm::mat4 move0 = glm::mat4(1.0f);

	

	glm::mat4 open = glm::mat4(1.0f);
	
	glm::mat4 model3 = glm::mat4(1.0f);
	glm::mat4 model4 = glm::mat4(1.0f);
	glm::mat4 model5 = glm::mat4(1.0f);

	glm::mat4 xrot = glm::mat4(1.0f);
	glm::mat4 yrot = glm::mat4(1.0f);
	glm::mat4 rot = glm::mat4(1.0f);
	glm::mat4 rev = glm::mat4(1.0f);



	

	GLuint changePos = glGetUniformLocation(shaderProgramID, "Pos");




	
	z = glm::rotate(z, glm::radians(-20.0f), glm::vec3(0.0, 1.0, 0.0));



	open = glm::rotate(open, glm::radians(r2), glm::vec3(1.0, 0.0, 0.0));
	
	

	
	
	move0 = glm::translate(move0, glm::vec3(-0.5, -0.5, 0.0f));
	




	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "transform");

	
	

	glBindBuffer(GL_ARRAY_BUFFER, HexPosVbo); // VBO Bind
	glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	{
		glBindBuffer(GL_ARRAY_BUFFER, HexColor); // VBO Bind
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	}


	
	

	{
		glm::mat4 x = glm::mat4(1.0f);
		glm::mat4 y = glm::mat4(1.0f);
		glm::mat4 movex = glm::mat4(1.0f);
		glm::mat4 movey = glm::mat4(1.0f);
		glm::mat4 movez = glm::mat4(1.0f);
		glm::mat4 set = glm::mat4(1.0f);
		glm::mat4 rot = glm::mat4(1.0f);

		x = glm::rotate(x, glm::radians(-20.0f), glm::vec3(1.0, 0.0, 0.0));
		y = glm::rotate(y, glm::radians(-20.0f), glm::vec3(0.0, 1.0, 0.0));
		rot = glm::rotate(rot, glm::radians(Y), glm::vec3(0.0, 1.0, 0.0));
		movex = glm::translate(movex, glm::vec3(-0.25, 0, 0.0f));
		movey = glm::translate(movey, glm::vec3(0.0, -0.25, 0.0f));
		movez = glm::translate(movez, glm::vec3(0.0, 0.0, -0.25));

		set = x * y * movex * movey * movez;

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(x * y *rot* movex * movey * movez* open));
	}
	
	if(Hex)
		glDrawArrays(GL_TRIANGLES, 0, 6);		//정면

	
	{
		glm::mat4 x = glm::mat4(1.0f);
		glm::mat4 y = glm::mat4(1.0f);
		glm::mat4 movex = glm::mat4(1.0f);
		glm::mat4 movey = glm::mat4(1.0f);
		glm::mat4 movez = glm::mat4(1.0f);
		glm::mat4 move = glm::mat4(1.0f);
		glm::mat4 set = glm::mat4(1.0f);
		glm::mat4 rot = glm::mat4(1.0f);

		x = glm::rotate(x, glm::radians(-20.0f), glm::vec3(1.0, 0.0, 0.0));
		y = glm::rotate(y, glm::radians(-20.0f), glm::vec3(0.0, 1.0, 0.0));
		movex = glm::translate(movex, glm::vec3(-0.25, 0, 0.0f));
		movey = glm::translate(movey, glm::vec3(0.0, -0.25, 0.0f));
		movez = glm::translate(movez, glm::vec3(0.0, 0.0, -0.25));
		move = glm::translate(move, glm::vec3(0.0, r3, 0.0f));
		rot = glm::rotate(rot, glm::radians(Y), glm::vec3(0.0, 1.0, 0.0));
		set = x * y * movex * movey * movez;



		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(x * y *rot* movex * movey * movez * move));
	}

	if (Hex)
	{
		glDrawArrays(GL_TRIANGLES, 6, 6);		//왼쪽
		glDrawArrays(GL_TRIANGLES, 18, 6);		//오른쪽
	}
	



	

	{
		glm::mat4 x = glm::mat4(1.0f);
		glm::mat4 y = glm::mat4(1.0f);
		glm::mat4 movex = glm::mat4(1.0f);
		glm::mat4 movey = glm::mat4(1.0f);
		glm::mat4 movey2 = glm::mat4(1.0f);
		glm::mat4 movez = glm::mat4(1.0f);
		glm::mat4 set = glm::mat4(1.0f);
		glm::mat4 spin = glm::mat4(1.0f);
		glm::mat4 rot = glm::mat4(1.0f);

		x = glm::rotate(x, glm::radians(-20.0f), glm::vec3(1.0, 0.0, 0.0));
		y = glm::rotate(y, glm::radians(-20.0f), glm::vec3(0.0, 1.0, 0.0));
		movex = glm::translate(movex, glm::vec3(-0.25, 0, 0.0f));
		movey = glm::translate(movey, glm::vec3(0.0, -0.5, 0.0f));
		movey2 = glm::translate(movey2, glm::vec3(0.0, 0.25, 0.0f));
		movez = glm::translate(movez, glm::vec3(0.0, 0.0, -0.25));
		spin = glm::rotate(spin, glm::radians(r1), glm::vec3(1.0, 0.0, 0.0));
		rot = glm::rotate(rot, glm::radians(Y), glm::vec3(0.0, 1.0, 0.0));

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(x* y*rot* movey2* spin* movex* movey* movez));
	}
	if (Hex)
		glDrawArrays(GL_TRIANGLES, 12 , 6);		//윗면

	{
		glm::mat4 x = glm::mat4(1.0f);
		glm::mat4 y = glm::mat4(1.0f);
		glm::mat4 movex = glm::mat4(1.0f);
		glm::mat4 movey = glm::mat4(1.0f);
		glm::mat4 movez = glm::mat4(1.0f);
		glm::mat4 set = glm::mat4(1.0f);
		glm::mat4 rot = glm::mat4(1.0f);

		x = glm::rotate(x, glm::radians(-20.0f), glm::vec3(1.0, 0.0, 0.0));
		y = glm::rotate(y, glm::radians(-20.0f), glm::vec3(0.0, 1.0, 0.0));
		movex = glm::translate(movex, glm::vec3(-0.25, 0, 0.0f));
		movey = glm::translate(movey, glm::vec3(0.0, -0.25, 0.0f));
		movez = glm::translate(movez, glm::vec3(0.0, 0.0, -0.25));
		rot = glm::rotate(rot, glm::radians(Y), glm::vec3(0.0, 1.0, 0.0));
		set = x * y * movex * movey * movez;



		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(x* y*rot* movex* movey* movez));
	}
	if (Hex)
		glDrawArrays(GL_TRIANGLES, 24 , 6);		//아래

	{
		glm::mat4 x = glm::mat4(1.0f);
		glm::mat4 y = glm::mat4(1.0f);
		glm::mat4 movex = glm::mat4(1.0f);
		glm::mat4 movey = glm::mat4(1.0f);
		glm::mat4 movez = glm::mat4(1.0f);
		glm::mat4 set = glm::mat4(1.0f);
		glm::mat4 s = glm::mat4(1.0f);
		glm::mat4 rot = glm::mat4(1.0f);

		x = glm::rotate(x, glm::radians(-20.0f), glm::vec3(1.0, 0.0, 0.0));
		y = glm::rotate(y, glm::radians(-20.0f), glm::vec3(0.0, 1.0, 0.0));
		movex = glm::translate(movex, glm::vec3(-0.25, 0, 0.0f));
		movey = glm::translate(movey, glm::vec3(0.0, -0.25, 0.0f));
		movez = glm::translate(movez, glm::vec3(0.0, 0.0, -0.25));
		s = glm::scale(s, glm::vec3(1.0 - r4, 1.0 - r4, 1.0));
		rot = glm::rotate(rot, glm::radians(Y), glm::vec3(0.0, 1.0, 0.0));


		set = x * y * movex * movey * movez;



		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(x* y*rot* s* movex* movey* movez));
	}
	if (Hex)
		glDrawArrays(GL_TRIANGLES, 30 , 6);		//뒷면




		

	glBindBuffer(GL_ARRAY_BUFFER, TetPosVbo); // VBO Bind
	glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	{
		glBindBuffer(GL_ARRAY_BUFFER, TetColor); // VBO Bind
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	}
	{
		glm::mat4 x = glm::mat4(1.0f);
		glm::mat4 y = glm::mat4(1.0f);
		glm::mat4 movex = glm::mat4(1.0f);
		glm::mat4 movey = glm::mat4(1.0f);
		glm::mat4 movez = glm::mat4(1.0f);
		glm::mat4 movey2 = glm::mat4(1.0f);
		glm::mat4 movez2 = glm::mat4(1.0f);
		glm::mat4 set = glm::mat4(1.0f);
		glm::mat4 s = glm::mat4(1.0f);
		glm::mat4 spin = glm::mat4(1.0f);
		glm::mat4 rot = glm::mat4(1.0f);

		x = glm::rotate(x, glm::radians(-20.0f), glm::vec3(1.0, 0.0, 0.0));
		y = glm::rotate(y, glm::radians(-20.0f), glm::vec3(0.0, 1.0, 0.0));
		movex = glm::translate(movex, glm::vec3(-0.25, 0, 0.0f));
		movey = glm::translate(movey, glm::vec3(0.0, 0.0, 0.0f));
		movez = glm::translate(movez, glm::vec3(0.0, 0.0, 0.0));
		movey2 = glm::translate(movey2, glm::vec3(0.0, -0.25, 0.0f));
		movez2 = glm::translate(movez2, glm::vec3(0.0, 0.0, -0.25f));
		rot = glm::rotate(rot, glm::radians(Y), glm::vec3(0.0, 1.0, 0.0));

		if(t1 || anio)
			spin = glm::rotate(spin, glm::radians(r5), glm::vec3(1.0, 0.0, 0.0));
		if(t2 || anir)
			spin = glm::rotate(spin, glm::radians(r6), glm::vec3(1.0, 0.0, 0.0));

		set = x * y * movex * movey * movez;



		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(x* y*rot* movey2* movez2* spin* movex* movey* movez));
		
	}
	if (!Hex)
		glDrawArrays(GL_TRIANGLES, 6, 3);//앞



	{
		glm::mat4 x = glm::mat4(1.0f);
		glm::mat4 y = glm::mat4(1.0f);
		glm::mat4 movex = glm::mat4(1.0f);
		glm::mat4 movey = glm::mat4(1.0f);
		glm::mat4 movez = glm::mat4(1.0f);
		glm::mat4 movey2 = glm::mat4(1.0f);
		glm::mat4 movez2 = glm::mat4(1.0f);
		glm::mat4 set = glm::mat4(1.0f);
		glm::mat4 s = glm::mat4(1.0f);
		glm::mat4 spin = glm::mat4(1.0f);
		glm::mat4 rot = glm::mat4(1.0f);

		x = glm::rotate(x, glm::radians(-20.0f), glm::vec3(1.0, 0.0, 0.0));
		y = glm::rotate(y, glm::radians(-20.0f), glm::vec3(0.0, 1.0, 0.0));
		movex = glm::translate(movex, glm::vec3(-0.25, 0, 0.0f));
		movey = glm::translate(movey, glm::vec3(0.0, 0.0, 0.0f));
		movez = glm::translate(movez, glm::vec3(0.0, 0.0, -0.5));
		movey2 = glm::translate(movey2, glm::vec3(0.0, -0.25, 0.0f));
		movez2 = glm::translate(movez2, glm::vec3(0.0, 0.0, 0.25f));
		rot = glm::rotate(rot, glm::radians(Y), glm::vec3(0.0, 1.0, 0.0));
		if(t1 || anio)
			spin = glm::rotate(spin, glm::radians(r5*-1), glm::vec3(1.0, 0.0, 0.0));
		if(t2 || anir)
			spin = glm::rotate(spin, glm::radians(r6 * -1), glm::vec3(1.0, 0.0, 0.0));
		set = x * y * movex * movey * movez;



		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(x* y*rot* movey2* movez2* spin* movex* movey* movez));

	}
	if (!Hex)
		glDrawArrays(GL_TRIANGLES, 15, 3);//뒷면
	

	{
		glm::mat4 x = glm::mat4(1.0f);
		glm::mat4 y = glm::mat4(1.0f);
		glm::mat4 movex = glm::mat4(1.0f);
		glm::mat4 movey = glm::mat4(1.0f);
		glm::mat4 movez = glm::mat4(1.0f);
		glm::mat4 movey2 = glm::mat4(1.0f);
		glm::mat4 movex2 = glm::mat4(1.0f);
		glm::mat4 set = glm::mat4(1.0f);
		glm::mat4 s = glm::mat4(1.0f);
		glm::mat4 spin = glm::mat4(1.0f);
		glm::mat4 rot = glm::mat4(1.0f);

		x = glm::rotate(x, glm::radians(-20.0f), glm::vec3(1.0, 0.0, 0.0));
		y = glm::rotate(y, glm::radians(-20.0f), glm::vec3(0.0, 1.0, 0.0));
		movex = glm::translate(movex, glm::vec3(0.0, 0, 0.0f));
		movey = glm::translate(movey, glm::vec3(0.0, 0.0, 0.0f));
		movez = glm::translate(movez, glm::vec3(0.0, 0.0, -0.25));
		
		movex2 = glm::translate(movey2, glm::vec3(-0.25, 0.0, 0.0f));
		movey2 = glm::translate(movey2, glm::vec3(0.0, -0.25, 0.0f));
		rot = glm::rotate(rot, glm::radians(Y), glm::vec3(0.0, 1.0, 0.0));
		if(t1 || anio)
			spin = glm::rotate(spin, glm::radians(r5 * -1), glm::vec3(0.0, 0.0, 1.0));
		if(t2 || anir)
			spin = glm::rotate(spin, glm::radians(r6 * -1), glm::vec3(0.0, 0.0, 1.0));

		set = x * y * movex * movey * movez;



		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(x * y*rot*movex2*movey2 *spin*  movex * movey * movez));

	}
	if (!Hex)
		glDrawArrays(GL_TRIANGLES, 9, 3);//왼쪽



	{
		glm::mat4 x = glm::mat4(1.0f);
		glm::mat4 y = glm::mat4(1.0f);
		glm::mat4 movex = glm::mat4(1.0f);
		glm::mat4 movey = glm::mat4(1.0f);
		glm::mat4 movez = glm::mat4(1.0f);
		glm::mat4 movey2 = glm::mat4(1.0f);
		glm::mat4 movex2 = glm::mat4(1.0f);
		glm::mat4 set = glm::mat4(1.0f);
		glm::mat4 s = glm::mat4(1.0f);
		glm::mat4 spin = glm::mat4(1.0f);
		glm::mat4 rot = glm::mat4(1.0f);

		x = glm::rotate(x, glm::radians(-20.0f), glm::vec3(1.0, 0.0, 0.0));
		y = glm::rotate(y, glm::radians(-20.0f), glm::vec3(0.0, 1.0, 0.0));
		movex = glm::translate(movex, glm::vec3(-0.5, 0, 0.0f));
		movey = glm::translate(movey, glm::vec3(0.0, 0.0, 0.0f));
		movez = glm::translate(movez, glm::vec3(0.0, 0.0, -0.25));

		movex2 = glm::translate(movey2, glm::vec3(0.25, 0.0, 0.0f));
		movey2 = glm::translate(movey2, glm::vec3(0.0, -0.25, 0.0f));
		rot = glm::rotate(rot, glm::radians(Y), glm::vec3(0.0, 1.0, 0.0));

		if(t1||anio)
			spin = glm::rotate(spin, glm::radians(r5), glm::vec3(0.0, 0.0, 1.0));
		if(t2 || anir)
			spin = glm::rotate(spin, glm::radians(r6), glm::vec3(0.0, 0.0, 1.0));

		set = x * y * movex * movey * movez;



		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(x * y *rot* movex2 * movey2 * spin * movex * movey * movez));

	}
	if (!Hex)
		glDrawArrays(GL_TRIANGLES, 12, 3);//오른쪽





















	{
		glm::mat4 x = glm::mat4(1.0f);
		glm::mat4 y = glm::mat4(1.0f);
		glm::mat4 movex = glm::mat4(1.0f);
		glm::mat4 movey = glm::mat4(1.0f);
		glm::mat4 movez = glm::mat4(1.0f);
		glm::mat4 set = glm::mat4(1.0f);
		glm::mat4 s = glm::mat4(1.0f);
		glm::mat4 rot = glm::mat4(1.0f);
		x = glm::rotate(x, glm::radians(-20.0f), glm::vec3(1.0, 0.0, 0.0));
		y = glm::rotate(y, glm::radians(-20.0f), glm::vec3(0.0, 1.0, 0.0));
		movex = glm::translate(movex, glm::vec3(-0.25, 0, 0.0f));
		movey = glm::translate(movey, glm::vec3(0.0, -0.25, 0.0f));
		movez = glm::translate(movez, glm::vec3(0.0, 0.0, -0.25));
		s = glm::scale(s, glm::vec3(1.0 - r4, 1.0 - r4, 1.0));
		rot = glm::rotate(rot, glm::radians(Y), glm::vec3(0.0, 1.0, 0.0));
		set = x * y * movex * movey * movez;



		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(x * y*rot  * movex * movey * movez));

	}
	if (!Hex)
	{
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 3, 3);//밑면
	}
	




	{
		glm::mat4 x = glm::mat4(1.0f);
		glm::mat4 y = glm::mat4(1.0f);
		glm::mat4 movex = glm::mat4(1.0f);
		glm::mat4 movey = glm::mat4(1.0f);
		glm::mat4 movez = glm::mat4(1.0f);
		glm::mat4 set = glm::mat4(1.0f);
		

		x = glm::rotate(x, glm::radians(-20.0f), glm::vec3(1.0, 0.0, 0.0));
		y = glm::rotate(y, glm::radians(-20.0f), glm::vec3(0.0, 1.0, 0.0));
		movex = glm::translate(movex, glm::vec3(0.0, 0, 0.0f));
		movey = glm::translate(movey, glm::vec3(0.0, 0.0, 0.0f));
		movez = glm::translate(movez, glm::vec3(0.0, 0.0, 0.0));
		


		set = x * y * movex * movey * movez;
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(set));
	}

	glDisableVertexAttribArray(PosLocation); // Disable 필수!
	glDisableVertexAttribArray(ColorLocation);


	glLineWidth(5.0);

	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, -1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, -1.0);
	glVertex3f(0.0, 0.0, 1.0);
	glEnd();
	glFinish();







	glutSwapBuffers();
	glutPostRedisplay();


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
	case 't'://윗면
		if (h1)
			h1 = false;
		else
			h1 = true;

		if (!Hex)
			Hex = true;
		break;
	case 'f'://앞면
		if (h2)
			h2 = false;
		else
			h2 = true;

		if (!Hex)
			Hex = true;
		break;
	case 's'://옆면
		if (h3)
			h3 = false;
		else
			h3 = true;

		if (!Hex)
			Hex = true;
		break;
	case 'b'://뒷면
		if (h4)
			h4 = false;
		else
			h4 = true;

		if (!Hex)
			Hex = true;
		break;
	case 'o'://사각뿔 열기
		if (t1)
			t1 = false;
		else
		{
			t1 = true;
			t2 = false;
		}
			
		anio = true;
		anir = false;
		if (Hex)
			Hex = false;
		break;
	case 'r'://사각뿔 차례로 열기
		if (t2)
		{
			t2 = false;
			t1 = false;
		}
			
		else
		{
			t2 = true;
			t1 = false;
		}
			

		anir = true;
		anio = false;
		if (Hex)
			Hex = false;
		break;
	case'y':
		if (yrot)
			yrot = false;
		else
			yrot = true;

		break;
	case 'q':
		exit(1);
		break;
	}


	glutPostRedisplay();
}
GLvoid Special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
	
		break;
	case GLUT_KEY_RIGHT:
	
		break;
	case GLUT_KEY_UP:
		
		break;
	case GLUT_KEY_DOWN:
		
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

	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{

	}
}

void Drag(int x, int y)
{
	float Rx, Ry, Wx, Wy;

	convert(x, y, &Wx, &Wy);
	convert(x, y, &Rx, &Ry);




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
	if (yrot)
		Y += 3;


	if (h1)
		r1 -= 3;

	if (h2 && r2 > -90)
		r2 -= 3;
	if (!h2 && r2 < 0)
		r2 += 3;

	if (h3 && r3 < 0.5)
	{
		r3 += 0.05;
		if (r3 > 0.5)
			r3 = 0.5;
	}
	if (!h3 && r3 > 0.0)
	{
		r3 -= 0.05;
		if (r3 < 0)
			r3 = 0;
	}
		
	
	if (h4 && r4 < 1)
	{
		r4 += 0.1;
		if (r4 > 1)
			r4 = 1;
	}
	if (!h4 && r4 > 0.0)
	{
		r4 -= 0.1;
		if (r4 < 0)
			r4 = 0;
	}


	if (t1 && r5 > -1 * (360 - 2 * atan(8.0 / 5.0) * 180.0 / 3.141592))
	{
		printf("%f", atan(8.0 / 5.0) * 180.0 / 3.141592);
		r5 -= 6;
		if (r5 < -1 * (360 - 2 * atan(8.0 / 5.0) * 180.0 / 3.141592))
			r5 = -1 * (360 - 2 * atan(8.0 / 5.0) * 180.0 / 3.141592);
	}
	if (!t1 && r5 < 0)
	{
		r5 += 6;
		if (r5 > 0)
			r5 = 0;
	}
		


	if (t2 && r6 > -1 * (180 -  atan(8.0 / 5.0) * 180.0 / 3.141592))
	{
		printf("%f", atan(8.0 / 5.0) * 180.0 / 3.141592);
		r6 -= 6;
		if (r6 < -1 * (180 - atan(8.0 / 5.0) * 180.0 / 3.141592))
			r6 = -1 * (180 - atan(8.0 / 5.0) * 180.0 / 3.141592);
	}
	if (!t2 && r6 < 0)
	{
		r6 += 6;
		if (r6 > 0)
			r6 = 0;
	}




	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정
}


GLchar* vertexSource, * fragmentSource; //--- 소스코드 저장 변수

void make_vertexShaders()
{
	vertexSource = filetobuf("vertex.glsl");
	//--- 버텍스 세이더 객체 만들기
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
	//--- 버텍스 세이더 컴파일하기
	glCompileShader(vertexShader);
	//--- 컴파일이 제대로 되지 않은 경우: 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << endl;
		return;
	}
}

void make_fragmentShaders()
{
	fragmentSource = filetobuf("fragment.glsl");
	//--- 프래그먼트 세이더 객체 만들기
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
	//--- 프래그먼트 세이더 컴파일
	glCompileShader(fragmentShader);
	//--- 컴파일이 제대로 되지 않은 경우: 컴파일 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << endl;
		return;
	}
}


void make_shaderProgram()
{
	make_vertexShaders(); //--- 버텍스 세이더 만들기
	make_fragmentShaders(); //--- 프래그먼트 세이더 만들기
	//-- shader Program
	shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexShader);
	glAttachShader(shaderProgramID, fragmentShader);
	glLinkProgram(shaderProgramID);
	//--- 세이더 삭제하기
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//--- Shader Program 사용하기
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
	glGenBuffers(1, &HexPosVbo);
	glBindBuffer(GL_ARRAY_BUFFER, HexPosVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(HexahedronShape), HexahedronShape, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &HexColor);
	glBindBuffer(GL_ARRAY_BUFFER, HexColor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(HexahedronColors), HexahedronColors, GL_STATIC_DRAW);

	glGenBuffers(1, &TetPosVbo);
	glBindBuffer(GL_ARRAY_BUFFER, TetPosVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TetrahedronShape), TetrahedronShape, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &TetColor);
	glBindBuffer(GL_ARRAY_BUFFER, TetColor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TetrahedronColors), TetrahedronColors, GL_STATIC_DRAW);

}


void set()
{
	for (int i = 0;i < 3;i++)
	{
		TetrahedronColors[i][0] = 1;
		TetrahedronColors[i][1] = 0;
		TetrahedronColors[i][2] = 0;
	}
	for (int i = 3;i < 6;i++)
	{
		TetrahedronColors[i][0] = 0;
		TetrahedronColors[i][1] = 1;
		TetrahedronColors[i][2] = 0;
	}
	for (int i = 6;i < 9;i++)
	{
		TetrahedronColors[i][0] = 0;
		TetrahedronColors[i][1] = 0;
		TetrahedronColors[i][2] = 1;
	}
	for (int i = 9;i < 12;i++)
	{
		TetrahedronColors[i][0] = 1;
		TetrahedronColors[i][1] = 1;
		TetrahedronColors[i][2] = 0;
	}
	for (int i = 12;i < 15;i++)
	{
		TetrahedronColors[i][0] = 1;
		TetrahedronColors[i][1] = 0;
		TetrahedronColors[i][2] = 1;
	}


	for (int i = 0;i < 6;i++)
	{
		HexahedronColors[i][0] = 1;
		HexahedronColors[i][1] = 0;
		HexahedronColors[i][2] = 0;
	}
	for (int i = 6;i < 12;i++)
	{
		HexahedronColors[i][0] = 0;
		HexahedronColors[i][1] = 1;
		HexahedronColors[i][2] = 0;
	}
	for (int i = 12;i < 18;i++)
	{
		HexahedronColors[i][0] = 0;
		HexahedronColors[i][1] = 0;
		HexahedronColors[i][2] = 1;
	}
	for (int i = 18;i < 24;i++)
	{
		HexahedronColors[i][0] = 1;
		HexahedronColors[i][1] = 1;
		HexahedronColors[i][2] = 0;
	}
	for (int i = 24;i < 30;i++)
	{
		HexahedronColors[i][0] = 0;
		HexahedronColors[i][1] = 1;
		HexahedronColors[i][2] = 1;
	}
	for (int i = 30;i < 36;i++)
	{
		HexahedronColors[i][0] = 1;
		HexahedronColors[i][1] = 0;
		HexahedronColors[i][2] = 1;
	}
	HexahedronShape[0][0] = 0.0;HexahedronShape[0][1] = 0.0;HexahedronShape[0][2] = 0.0;
	HexahedronShape[1][0] = 0.5;HexahedronShape[1][1] = 0.5;HexahedronShape[1][2] = 0.0;
	HexahedronShape[2][0] = 0.5;HexahedronShape[2][1] = 0.0;HexahedronShape[2][2] = 0.0;

	HexahedronShape[3][0] = 0.0;HexahedronShape[3][1] = 0.0;HexahedronShape[3][2] = 0.0;
	HexahedronShape[4][0] = 0.0;HexahedronShape[4][1] = 0.5;HexahedronShape[4][2] = 0.0;
	HexahedronShape[5][0] = 0.5;HexahedronShape[5][1] = 0.5;HexahedronShape[5][2] = 0.0;

	HexahedronShape[6][0] = 0.0;HexahedronShape[6][1] = 0.0;HexahedronShape[6][2] = 0.0;
	HexahedronShape[7][0] = 0.0;HexahedronShape[7][1] = 0.5;HexahedronShape[7][2] = 0.5;
	HexahedronShape[8][0] = 0.0;HexahedronShape[8][1] = 0.5;HexahedronShape[8][2] = 0.0;

	HexahedronShape[9][0] = 0.0;HexahedronShape[9][1] = 0.0;HexahedronShape[9][2] = 0.0;
	HexahedronShape[10][0] = 0.0;HexahedronShape[10][1] = 0.0;HexahedronShape[10][2] = 0.5;
	HexahedronShape[11][0] = 0.0;HexahedronShape[11][1] = 0.5;HexahedronShape[11][2] = 0.5;

	HexahedronShape[12][0] = 0.0;HexahedronShape[12][1] = 0.5;HexahedronShape[12][2] = 0.0;
	HexahedronShape[13][0] = 0.5;HexahedronShape[13][1] = 0.5;HexahedronShape[13][2] = 0.5;
	HexahedronShape[14][0] = 0.5;HexahedronShape[14][1] = 0.5;HexahedronShape[14][2] = 0.0;

	HexahedronShape[15][0] = 0.0;HexahedronShape[15][1] = 0.5;HexahedronShape[15][2] = 0.0;
	HexahedronShape[16][0] = 0.0;HexahedronShape[16][1] = 0.5;HexahedronShape[16][2] = 0.5;
	HexahedronShape[17][0] = 0.5;HexahedronShape[17][1] = 0.5;HexahedronShape[17][2] = 0.5;

	HexahedronShape[18][0] = 0.5;HexahedronShape[18][1] = 0.0;HexahedronShape[18][2] = 0.0;
	HexahedronShape[19][0] = 0.5;HexahedronShape[19][1] = 0.5;HexahedronShape[19][2] = 0.0;
	HexahedronShape[20][0] = 0.5;HexahedronShape[20][1] = 0.5;HexahedronShape[20][2] = 0.5;

	HexahedronShape[21][0] = 0.5;HexahedronShape[21][1] = 0.0;HexahedronShape[21][2] = 0.0;
	HexahedronShape[22][0] = 0.5;HexahedronShape[22][1] = 0.5;HexahedronShape[22][2] = 0.5;
	HexahedronShape[23][0] = 0.5;HexahedronShape[23][1] = 0.0;HexahedronShape[23][2] = 0.5;

	HexahedronShape[24][0] = 0.0;HexahedronShape[24][1] = 0.0;HexahedronShape[24][2] = 0.0;
	HexahedronShape[25][0] = 0.5;HexahedronShape[25][1] = 0.0;HexahedronShape[25][2] = 0.0;
	HexahedronShape[26][0] = 0.5;HexahedronShape[26][1] = 0.0;HexahedronShape[26][2] = 0.5;

	HexahedronShape[27][0] = 0.0;HexahedronShape[27][1] = 0.0;HexahedronShape[27][2] = 0.0;
	HexahedronShape[28][0] = 0.5;HexahedronShape[28][1] = 0.0;HexahedronShape[28][2] = 0.5;
	HexahedronShape[29][0] = 0.0;HexahedronShape[29][1] = 0.0;HexahedronShape[29][2] = 0.5;

	HexahedronShape[30][0] = 0.0;HexahedronShape[30][1] = 0.0;HexahedronShape[30][2] = 0.5;
	HexahedronShape[31][0] = 0.5;HexahedronShape[31][1] = 0.0;HexahedronShape[31][2] = 0.5;
	HexahedronShape[32][0] = 0.5;HexahedronShape[32][1] = 0.5;HexahedronShape[32][2] = 0.5;

	HexahedronShape[33][0] = 0.0;HexahedronShape[33][1] = 0.0;HexahedronShape[33][2] = 0.5;
	HexahedronShape[34][0] = 0.5;HexahedronShape[34][1] = 0.5;HexahedronShape[34][2] = 0.5;
	HexahedronShape[35][0] = 0.0;HexahedronShape[35][1] = 0.5;HexahedronShape[35][2] = 0.5;


	TetrahedronShape[0][0] = 0.0;TetrahedronShape[0][1] = 0.0;TetrahedronShape[0][2] = 0.0;
	TetrahedronShape[1][0] = 0.5;TetrahedronShape[1][1] = 0.0;TetrahedronShape[1][2] = 0.0;
	TetrahedronShape[2][0] = 0.0;TetrahedronShape[2][1] = 0.0;TetrahedronShape[2][2] = 0.5;

	TetrahedronShape[3][0] = 0.5;TetrahedronShape[3][1] = 0.0;TetrahedronShape[3][2] = 0.5;
	TetrahedronShape[4][0] = 0.5;TetrahedronShape[4][1] = 0.0;TetrahedronShape[4][2] = 0.0;
	TetrahedronShape[5][0] = 0.0;TetrahedronShape[5][1] = 0.0;TetrahedronShape[5][2] = 0.5;

	TetrahedronShape[6][0] = 0.5;TetrahedronShape[6][1] = 0.0;TetrahedronShape[6][2] = 0.0;
	TetrahedronShape[7][0] = 0.0;TetrahedronShape[7][1] = 0.0;TetrahedronShape[7][2] = 0.0;
	TetrahedronShape[8][0] = 0.25;TetrahedronShape[8][1] = 0.4;TetrahedronShape[8][2] = 0.25;

	TetrahedronShape[9][0] = 0.0;TetrahedronShape[9][1] = 0.0;TetrahedronShape[9][2] = 0.5;
	TetrahedronShape[10][0] = 0.0;TetrahedronShape[10][1] = 0.0;TetrahedronShape[10][2] = 0.0;
	TetrahedronShape[11][0] = 0.25;TetrahedronShape[11][1] = 0.4;TetrahedronShape[11][2] = 0.25;

	TetrahedronShape[12][0] = 0.5;TetrahedronShape[12][1] = 0.0;TetrahedronShape[12][2] = 0.0;
	TetrahedronShape[13][0] = 0.5;TetrahedronShape[13][1] = 0.0;TetrahedronShape[13][2] = 0.5;
	TetrahedronShape[14][0] = 0.25;TetrahedronShape[14][1] = 0.4;TetrahedronShape[14][2] = 0.25;

	TetrahedronShape[15][0] = 0.0;TetrahedronShape[15][1] = 0.0;TetrahedronShape[15][2] = 0.5;
	TetrahedronShape[16][0] = 0.5;TetrahedronShape[16][1] = 0.0;TetrahedronShape[16][2] = 0.5;
	TetrahedronShape[17][0] = 0.25;TetrahedronShape[17][1] = 0.4;TetrahedronShape[17][2] = 0.25;


	
}
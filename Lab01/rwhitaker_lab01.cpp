#include "initShaders.h"
#include "vec.h"
#include <cstdlib>
#include <ctime>
using namespace std;

int counter=0;

const int numPoints = 1500;

//vertexIDs
GLuint vaoID, vboID;// the buffers that are going to be linked too


void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void triangle(){
  glClear(GL_COLOR_BUFFER_BIT);//clears the screen
  
  //vertices
  GLfloat vertexarray[]={0.5f,-0.5f,0.0f,
					   0.0f,0.5f,0.0f,
					   -0.5f,-0.5f,0.0f};// vertices that are drawn x,y,z ...
  //indices of triangle
  GLubyte indices[3]={0,1,2};
  
  glGenVertexArrays(1, &vaoID);//generates object name for Vertex Array Objects
  glBindVertexArray(vaoID);//bind the object to the array

  glGenBuffers(1, &vboID);//generates object name for the Vertex Buffer Object
  glBindBuffer(GL_ARRAY_BUFFER, vboID);//bind the object to the array
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexarray), vertexarray, GL_STATIC_DRAW);//allocates the memory of the vertices

  
  ShaderInfo shaders[]={//create the shader specified by my initshaders 
  { GL_VERTEX_SHADER , "vertexshader1.glsl"} ,
  { GL_FRAGMENT_SHADER , "fragmentshader1.glsl"},
  { GL_NONE , NULL} 
  };
  

  initShaders(shaders);//creates shaders
  
  glEnableVertexAttribArray(0);//enables the vertex attribute index 
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);//specified the start the vertice array used to the draw

  glDrawArrays(GL_TRIANGLES, 0, 3);//draws array
  glFlush();//makes sure the processes finish
}

void points() {
	glClear(GL_COLOR_BUFFER_BIT);

	vec2 points[numPoints];
	float k;
	float j;
	srand(time(0));

	for(int i = 0; i < numPoints; i++) {
		switch(i%4) {
			case 0:
				j = ((float) rand()/RAND_MAX);
				k = ((float) rand()/RAND_MAX - 1);

				points[i] = vec2(j, k);
				break;
			case 1:
				j = ((float) rand()/RAND_MAX - 1);
				k = ((float) rand()/RAND_MAX - 1);

				points[i] = vec2(j, k);
				break;
			case 2:
				j = ((float) rand()/RAND_MAX);
				k = ((float) rand()/RAND_MAX);

				points[i] = vec2(j, k);
				break;
			case 3:
				j = ((float) rand()/RAND_MAX - 1);
				k = ((float) rand()/RAND_MAX);

				points[i] = vec2(j, k);
				break;
		}
	}

	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	
	ShaderInfo shaders[]={//create the shader specified by my initshaders 
	{ GL_VERTEX_SHADER , "vertexshader2.glsl"} ,
	{ GL_FRAGMENT_SHADER , "fragmentshader2.glsl"},
	{ GL_NONE , NULL} 
	};
	

	initShaders(shaders);

	glEnableVertexAttribArray(0);//enables the vertex attribute index 
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,(void*)0);//specified the start the vertice array used to the draw

	glDrawArrays(GL_POINTS, 0, numPoints);
	glFlush();
}

void square() {
	glClear(GL_COLOR_BUFFER_BIT);//clears the screen
  
  //vertices
  GLfloat vertexarray[]={-0.5f,-0.5f,0.0f,
					     -0.5f,0.5f,0.0f,
					      0.5f,0.5f,0.0f,
					      0.5f,-0.5f, 0.0f};// vertices that are drawn x,y,z ...
  //indices of triangle
  GLubyte indices[4]={0,1,2,3};
  
  glGenVertexArrays(1, &vaoID);//generates object name for Vertex Array Objects
  glBindVertexArray(vaoID);//bind the object to the array

  glGenBuffers(1, &vboID);//generates object name for the Vertex Buffer Object
  glBindBuffer(GL_ARRAY_BUFFER, vboID);//bind the object to the array
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexarray), vertexarray, GL_STATIC_DRAW);//allocates the memory of the vertices

  
  ShaderInfo shaders[]={//create the shader specified by my initshaders 
  { GL_VERTEX_SHADER , "vertexshader1.glsl"} ,
  { GL_FRAGMENT_SHADER , "fragmentshader1.glsl"},
  { GL_NONE , NULL} 
  };
  

  initShaders(shaders);//creates shaders
  
  glEnableVertexAttribArray(0);//enables the vertex attribute index 
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);//specified the start the vertice array used to the draw

  glDrawArrays(GL_POLYGON, 0, 4);//draws array
  glFlush();//makes sure the processes finish
}

void drawscene(){
  switch(counter%3){//easy way to switch throw functions
    case 0:
      glutDisplayFunc(triangle);
      glutPostRedisplay();//sets flags for opengl to redraw the display
      break;
	case 1:
      glutDisplayFunc(points);
      glutPostRedisplay();//sets flags for opengl to redraw the display
      break;
	case 2:
      glutDisplayFunc(square);
      glutPostRedisplay();//sets flags for opengl to redraw the display
      break;
  }
}
//this function create the interaction with the mouse
void mousepress(int button, int state, int x, int y){
  if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)//right click closes the screen
    exit(0);
  else if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){//left click changes the shape color
    counter++;
    drawscene();
  }
}

void idle(void){
  glutPostRedisplay();
}

int main(int argc, char **argv){

	//Freeglut window and context management	
  glutInit(&argc, argv);
  glutCreateWindow("Shapes");//creates the window with the specified name

  glutInitWindowSize(500, 500);
  glutInitWindowPosition(500, 500);
  
  //initializes glew
  glewExperimental=GL_TRUE;
  if(glewInit()){
    fprintf(stderr, "Unable to initalize GLEW");
    exit(EXIT_FAILURE);
  }

  //init();

  glutDisplayFunc(drawscene);//displays callback draws the shapes
  glutMouseFunc(mousepress);//control callback specifies the mouse controls
  glutMainLoop();//sets opengl state in a neverending loop
  return 0;
}

/*
	Run the code

	Left Click to draw maze
	Right Click if you drew a wrong piece

	If you are done with your maze, close the app but don't close the console.
	The last array in the console is your required maze array!
	Copy and Paste it in your code.
*/
# include "iGraphics.h"

int maze[23][29];



/*
	function iDraw() is called again and again by the system.
*/
void iDraw()
{
	//place your drawing codes here

	iClear();

	int i, j;
	for (i = 0; i < 23; i++) {
        for (j = 0; j < 29; j++) {
            iSetColor (255, 255, 0);
            if (maze[i][j] == 1) {
                iFilledRectangle (j*30, i*30, 30, 30);
            }
        }
	}
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
	    //printf ("%d %d\n", mx, my);
		//place your codes here
		if (maze[my/30][mx/30] == 0) {
            maze[my/30][mx/30] = 1;
		}

	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
	    //printf ("%d %d\n", mx, my);
		//place your codes here
		if (maze[my/30][mx/30] == 1) {
            maze[my/30][mx/30] = 0;
		}

	}

}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
	if(key == 'x')
	{
		//do something with 'x'
		exit(0);
	}
	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

	if(key == GLUT_KEY_END)
	{
		exit(0);
	}
	//place your codes for other keys here
}

void change () {
    int i, j;
	for (i = 0; i < 23; i++) {
        for (j = 0; j < 29; j++) {
            printf ("%d ", maze[i][j]);
        }
        printf ("\n");
	}

	printf ("\n");
}

int main()
{
	//place your own initialization codes here.

	iSetTimer (1000, change);
	iInitialize(870, 690, "MouseDemo");
	return 0;
}

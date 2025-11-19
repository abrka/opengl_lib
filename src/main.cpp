#include "GLApp/application.h"


int main() {
	GLApp::Application app{ 800,800,OPENGL_VERSION_MAJOR,OPENGL_VERSION_MINOR };
	app.run();
}
#include "window/Window.h"

int main(int argc, char** argv)
{
	Window window{ "SoftRenderer", 1024, 768 };
	window.Run();
	return 0;
}
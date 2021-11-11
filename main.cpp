#include "Application.h"

int main()
{
	constexpr int width = 1500;
	constexpr int height = 900;

	Survive::Application application(width, height, "Survive");

	application.run();

	return 0;
}

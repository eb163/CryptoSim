#include "debug.h"
#include "Controller.h"
#include "Viewer.h"
#include "Model.h"

int main()
{
	Model m;
	Viewer v;
	Controller ctrl(m, v);

	do
	{
		v.loop();
		ctrl.loop();

	} while (ctrl.isRunning() == true);

	return 0;
}
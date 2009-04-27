#include "SoLongSucker.h"

int main()
{
	// Construct new conversation
	try
	{
		SoLongSucker game;

		// Initialize conversation
		game.Initialize();

		// Output state of the conversation
		game.Insert();

		// begin convesation
		game.Simulate();

		// Output state of the conversation
		game.Insert();


		// Output conversation postsimulation report
		game.WrapUp();
	}
	catch ( AppError e )
	{

		cout << "\nSimulation Error Detected!\n------------\n";
		cout << "Description : " << e.getMsg()    << "\n";
		cout << "Origin      : " << e.getOrigin() << "\n\n";
	}

	return 0;

}//main

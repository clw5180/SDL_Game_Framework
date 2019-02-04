#include "game.h"

int main(int argc, char* argv[]) 
{
	return CGame::Instance()->Execute(argc, argv);
}

#include "game.h"

int main(int argc, char* argv[]) 
{
	return CGame::GetInstance()->Execute(argc, argv);
}

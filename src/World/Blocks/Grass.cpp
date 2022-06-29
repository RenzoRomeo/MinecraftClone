#include "Grass.h"

namespace MinecraftClone
{
	Grass::Grass()
	{
		FrontAtlasCoord = { 1,0 };
		BackAtlasCoord = { 1,0 };
		LeftAtlasCoord = { 1,0 };
		RightAtlasCoord = { 1,0 };
		TopAtlasCoord = { 0,0 };
		BottomAtlasCoord = { 2,0 };
		Solid = true;
	}
}
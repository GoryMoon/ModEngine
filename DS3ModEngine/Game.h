#pragma once

typedef enum
{
	GAME_DARKSOULS_REMASTERED,
	GAME_DARKSOULS_3,
	GAME_SEKIRO,
} DSGame;

DSGame GetGameType();
#include "Platform.h"
#include <iostream>

void Platform::Draw(Platform platform) {		//diesgna la piattaforma da disegnare
	if (Platform::ToDraw(platform)) {
		gioco::set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		for (int i = 0; i <= (platform._xfine - platform._xinizio); i++) {
			if (platform._xinizio + i > 0 && platform._xinizio + i < 79) {
				gioco::gotoxy(platform._xinizio + i, platform._height);
				putchar('I');
			}
		}
	}
}
void Platform::Erase(Platform platform) {		//cancella i caratteri della piattaforma
	for (int i = 0; i <= (platform._xfine - platform._xinizio); i++) {
		if (platform._xinizio + i > 0 && platform._xinizio + i < 79) {
			gioco::gotoxy(platform._xinizio + i, platform._height);
			putchar(' ');
		}
	}
}
void Platform::LScrollPlatform(Platform &platform){		//sposta la piattaforma di uno a sinistra
	if (platform._xfine > -1 && platform._xfine < 79) {
		gioco::gotoxy(platform._xfine, platform._height);
		putchar(' ');
	}
	platform._xinizio--;
	platform._xfine--;
	Draw(platform);
}
void Platform::RScrollPlatform(Platform &platform){		//sposta la piattaforma di uno a destra 
	if (platform._xinizio > -1 && platform._xinizio < 79) {
		gioco::gotoxy(platform._xinizio, platform._height);
		putchar(' ');
	}
	platform._xinizio++; 
	platform._xfine++; 
	Draw(platform);
}
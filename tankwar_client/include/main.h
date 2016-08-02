#ifndef __MAIN_H_
#define __MAIN_H_
#include "UGFW++.h"
#include <string>
void DrawFPS() { float FPS = 1 / UG::GetDeltaTime(); UG::DrawString(std::to_string((int)FPS).c_str(), 20, UG::GetScreenSize().y - 20, 1.0f); }

#endif //__MAIN_H_
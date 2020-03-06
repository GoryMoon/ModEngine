#include "stdafx.h"

using namespace ImGui;

namespace Menu
{
	bool isOpen = true;
	float test = 0.f;
	
	void Init()
	{
		static bool noTitlebar = false;
		static bool noResize = false;
		static bool autoResize = false;
		static bool noMove = false;
		static bool noScrollbar = false;
		static bool noCollapse = false;
		static bool noMenu = true;
		static bool startPosSet = false;

		ImGuiWindowFlags windowFlags = 0;
		if (noTitlebar) windowFlags |= ImGuiWindowFlags_NoTitleBar;
		if (noResize) windowFlags |= ImGuiWindowFlags_NoResize;
		if (autoResize) windowFlags |= ImGuiWindowFlags_AlwaysAutoResize;
		if (noMove) windowFlags |= ImGuiWindowFlags_NoMove;
		if (noScrollbar) windowFlags |= ImGuiWindowFlags_NoScrollbar;
		if (noCollapse) windowFlags |= ImGuiWindowFlags_NoCollapse;
		if (!noMenu) windowFlags |= ImGuiWindowFlags_MenuBar;
		SetNextWindowSize(ImVec2(450, 600));
		if (!startPosSet)
		{
			SetNextWindowPos(ImVec2(25, 25));
			startPosSet = true;
		}

		GetIO().MouseDrawCursor = isOpen;

		
		if (isOpen)
		{
			ImGui::ShowDemoWindow(&isOpen);
			/*ImGui::Begin("ImGui Menu", &isOpen, windowFlags);

			ImGui::PushItemWidth(GetWindowWidth() * 0.65f);
			ImGui::PushItemWidth(-140);

			if (ImGui::CollapsingHeader("MENU"))
			{
				if (ImGui::TreeNode("SUB MENU"))
				{
					ImGui::Text("Text Test");
					if (ImGui::Button("Button Test"))
					{
					}
					ImGui::Checkbox("CheckBox Test", &noTitlebar);
					ImGui::SliderFloat("Slider Test", &test, 1.0f, 100.0f);

					ImGui::TreePop();
				}
			}

			ImGui::End();*/
		}
	}
}

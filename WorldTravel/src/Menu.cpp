#include "Menu.h"
#include <spdlog/spdlog.h>

namespace worldtravel
{
	namespace Menu
	{
		std::string statusText;
		DWORD statusTextDrawTicksMax;
		bool statusTextGxtEntry;
		void DrawRect(float A_0, float A_1, float A_2, float A_3, int A_4, int A_5, int A_6, int A_7)
		{
			GRAPHICS::DRAW_RECT((A_0 + (A_2 * 0.5f)), (A_1 + (A_3 * 0.5f)), A_2, A_3, A_4, A_5, A_6, A_7);
		}

		void DrawMenuLine(std::string caption, float lineWidth, float lineHeight, float lineTop, float lineLeft, float textLeft, bool active, bool title, bool rescaleText)
		{
			// default values
			int text_col[4] = { 255, 255, 255, 255 },
				rect_col[4] = { 70, 95, 95, 255 };
			float text_scale = 0.35f;
			int font = 0;

			// correcting values for active line
			if (active)
			{
				text_col[0] = 0;
				text_col[1] = 0;
				text_col[2] = 0;

				rect_col[0] = 218;
				rect_col[1] = 242;
				rect_col[2] = 216;

				if (rescaleText) text_scale = 0.40f;
			}

			if (title)
			{
				rect_col[0] = 0;
				rect_col[1] = 0;
				rect_col[2] = 0;

				if (rescaleText) text_scale = 0.50;
				font = 1;
			}

			int screen_w, screen_h;
			GRAPHICS::GET_SCREEN_RESOLUTION(&screen_w, &screen_h);

			textLeft += lineLeft;

			float lineWidthScaled = lineWidth / (float)screen_w; // line width
			float lineTopScaled = lineTop / (float)screen_h; // line top offset
			float textLeftScaled = textLeft / (float)screen_w; // text left offset
			float lineHeightScaled = lineHeight / (float)screen_h; // line height

			float lineLeftScaled = lineLeft / (float)screen_w;

			// this is how it's done in original scripts

			// text upper part
			UI::SET_TEXT_FONT(font);
			UI::SET_TEXT_SCALE(0.0, text_scale);
			UI::SET_TEXT_COLOUR(text_col[0], text_col[1], text_col[2], text_col[3]);
			UI::SET_TEXT_CENTRE(0);
			UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
			UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
			UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
			UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((LPSTR)caption.c_str());
			UI::END_TEXT_COMMAND_DISPLAY_TEXT(textLeftScaled, (((lineTopScaled + 0.00278f) + lineHeightScaled) - 0.005f));

			// text lower part
			UI::SET_TEXT_FONT(font);
			UI::SET_TEXT_SCALE(0.0, text_scale);
			UI::SET_TEXT_COLOUR(text_col[0], text_col[1], text_col[2], text_col[3]);
			UI::SET_TEXT_CENTRE(0);
			UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
			UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
			UI::BEGIN_TEXT_COMMAND_GET_NUMBER_OF_LINES_FOR_STRING("STRING");
			UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((LPSTR)caption.c_str());
			int num25 = UI::END_TEXT_COMMAND_GET_NUMBER_OF_LINES_FOR_STRING(textLeftScaled, (((lineTopScaled + 0.00278f) + lineHeightScaled) - 0.005f));

			// rect
			DrawRect(lineLeftScaled, lineTopScaled + (0.00278f),
				lineWidthScaled, ((((float)(num25)*UI::GET_RENDERED_CHARACTER_HEIGHT(text_scale, 0)) + (lineHeightScaled * 2.0f)) + 0.005f),
				rect_col[0], rect_col[1], rect_col[2], rect_col[3]);
		}

		void GetButtonState(bool* a, bool* b, bool* up, bool* down, bool* l, bool* r)
		{
			if (a) *a = CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 201);
			if (b) *b = CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 202);
			if (up) *up = CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 188);
			if (down) *down = CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 187);
			if (r) *r = CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 190);
			if (l) *l = CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 189);
		}

		// Beep sounds: SELECT, BACK, NAV_UP_DOWN, NAV_LEFT_RIGHT, ERROR
		void MenuBeep(std::string sound, std::string soundGroup)
		{
			AUDIO::PLAY_SOUND_FRONTEND(-1, (char*)sound.c_str(), (char*)soundGroup.c_str(), 0);
		}
		void UpdateStatusText()
		{
			if (GetTickCount() < statusTextDrawTicksMax)
			{
				UI::SET_TEXT_FONT(0);
				UI::SET_TEXT_SCALE(0.55f, 0.55f);
				UI::SET_TEXT_COLOUR(255, 255, 255, 255);
				UI::SET_TEXT_WRAP(0.0, 1.0);
				UI::SET_TEXT_CENTRE(1);
				UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
				UI::SET_TEXT_EDGE(1, 0, 0, 0, 205);
				if (statusTextGxtEntry)
				{
					UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT((char*)statusText.c_str());
				}
				else
				{
					UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
					UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((char*)statusText.c_str());
				}
				UI::END_TEXT_COMMAND_DISPLAY_TEXT(0.5, 0.5);
			}
		}

		void SetStatusText(std::string str, DWORD time, bool isGxtEntry)
		{
			statusText = str;
			statusTextDrawTicksMax = GetTickCount() + time;
			statusTextGxtEntry = isGxtEntry;
		}

		std::string LineAsStr(std::string text, std::string text2)
		{
			while (text.size() < 18) text += " ";
			return text + text2;
		}

		void DisableControls(bool toggle)
		{
			CONTROLS::DISABLE_CONTROL_ACTION(2, 19, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(2, 20, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(0, 21, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(2, 27, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(0, 57, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(0, 70, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(0, 73, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(2, 85, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(0, 105, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(0, 114, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(0, 120, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(0, 132, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(0, 136, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(0, 137, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(0, 140, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(0, 141, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(0, 154, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(2, 172, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(2, 173, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(2, 174, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(2, 175, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(2, 176, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(2, 177, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(0, 263, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(0, 264, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(2, 288, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(2, 298, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(2, 301, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(2, 307, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(2, 308, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(2, 309, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(2, 311, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(0, 337, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(0, 345, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(0, 353, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(0, 354, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(0, 355, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(0, 356, toggle);
			CONTROLS::DISABLE_CONTROL_ACTION(0, 357, toggle);
		}

		void EnableControls(bool toggle)
		{
			CONTROLS::ENABLE_CONTROL_ACTION(2, 19, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(2, 20, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(0, 21, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(2, 27, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(0, 57, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(0, 70, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(0, 73, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(2, 85, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(0, 105, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(0, 114, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(0, 120, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(0, 132, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(0, 136, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(0, 137, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(0, 140, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(0, 141, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(0, 154, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(2, 172, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(2, 173, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(2, 174, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(2, 175, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(2, 176, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(2, 177, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(0, 263, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(0, 264, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(2, 288, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(2, 298, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(2, 301, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(2, 307, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(2, 308, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(2, 309, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(2, 311, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(0, 337, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(0, 345, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(0, 353, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(0, 354, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(0, 355, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(0, 356, toggle);
			CONTROLS::ENABLE_CONTROL_ACTION(0, 357, toggle);
		}

		int DrawMenu(std::string caption, const std::vector<std::string>& options, const std::vector<bool>& optionAvalible, std::string frontendSoundSet)
		{
			int activeLineIndex = 0;
			int selectedLineIndex = -1;
			const float lineWidth = 250.0;

			worldtravel::Menu::MenuBeep("SELECT", (char*)frontendSoundSet.c_str());

			ULONGLONG waitTime = 150;
			while (true)
			{
				worldtravel::Menu::DisableControls(true);
				// timed menu draw, used for pause after active line switch
				ULONGLONG maxTickCount = GetTickCount64() + waitTime;
				do
				{
					// draw menu
					worldtravel::Menu::DrawMenuLine(caption, lineWidth, 15.0, 18.0, 0.0, 5.0, false, true);
					for (int i = 0; i < options.size(); i++)
						if (i != activeLineIndex)
							worldtravel::Menu::DrawMenuLine(options[i], lineWidth, 9.0f, 60.0f + i * 36.0f, 0.0f, 9.0f, false, false);
					worldtravel::Menu::DrawMenuLine(options[activeLineIndex], lineWidth + 1.0f, 11.0f, 56.0f + activeLineIndex * 36.0f, 0.0f, 7.0f, true, false);

					WAIT(0);
				} while (GetTickCount64() < maxTickCount);
				waitTime = 0;

				// process buttons
				bool bSelect, bBack, bUp, bDown;
				worldtravel::Menu::GetButtonState(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);

				if (bSelect)
				{
					if (optionAvalible[activeLineIndex])
					{
						worldtravel::Menu::MenuBeep("SELECT", (char*)frontendSoundSet.c_str());
						selectedLineIndex = activeLineIndex;
						waitTime = 200;
						break;
					}
					else
					{
						worldtravel::Menu::MenuBeep("ERROR", (char*)frontendSoundSet.c_str());
						waitTime = 200;
					}
				}
				else
				{
					if (bBack)
					{
						worldtravel::Menu::MenuBeep("BACK", (char*)frontendSoundSet.c_str());
						break;
					}
					else
					{
						if (bUp)
						{
							worldtravel::Menu::MenuBeep("NAV_UP_DOWN", (char*)frontendSoundSet.c_str());
							if (activeLineIndex == 0)
								activeLineIndex = static_cast<int>(options.size());
							activeLineIndex--;
							waitTime = 150;
						}
						else
						{
							if (bDown)
							{
								worldtravel::Menu::MenuBeep("NAV_UP_DOWN", (char*)frontendSoundSet.c_str());
								activeLineIndex++;
								if (activeLineIndex == options.size())
									activeLineIndex = 0;
								waitTime = 150;
							}
						}
					}
				}
			}
			return selectedLineIndex;
		}
	}
}
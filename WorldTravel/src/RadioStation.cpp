#include "RadioStation.h"

using namespace std;



std::string RadioStation::GetRadioStationName()
{
	return radioStationName;
}
void RadioStation::SetRadioStationName(const std::string& radioStation)
{
	radioStationName = radioStation;
}
void RadioStation::EnableRadioStation()
{
	AUDIO::LOCK_RADIO_STATION((char*)radioStationName.c_str(), false);
}
void RadioStation::DisableRadioStation()
{
	AUDIO::LOCK_RADIO_STATION((char*)radioStationName.c_str(), true);
}
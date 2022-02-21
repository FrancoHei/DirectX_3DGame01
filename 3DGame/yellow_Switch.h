#ifndef YELLOW_SWITCH_H_
#define YELLOW_SWITCH_H_

#include "switch.h"

class Yellow_Switch : public Switch
{
private:
public:
	Yellow_Switch(D3DXVECTOR3 pos_) :Switch((char*)"data/MODEL/switch.obj", pos_)
	{

	}

};

#endif//YELLOW_SWITCH_H_

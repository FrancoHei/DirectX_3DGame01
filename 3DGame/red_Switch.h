#ifndef RED_SWITCH_H_
#define RED_SWITCH_H_

#include "switch.h"

class Red_Switch : public Switch
{
private:
public:
	Red_Switch(D3DXVECTOR3 pos_):Switch((char*)"data/MODEL/red_switch.obj", pos_)
	{
	}

};

#endif//RED_SWITCH_H_

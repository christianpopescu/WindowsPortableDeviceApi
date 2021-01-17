#pragma once
#include "../stdafx.h"
class CPortableDeviceManager
{

	private:
	CPortableDeviceManager();
	public:
		static CPortableDeviceManager GetCPortableDeviceManager();
	int EnumerateAllDevices() const;
};
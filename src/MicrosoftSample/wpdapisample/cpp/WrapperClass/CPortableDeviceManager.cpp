#include "stdafx.h"
#include "CPortableDeviceManager.h"


CPortableDeviceManager::CPortableDeviceManager()
{
}

CPortableDeviceManager CPortableDeviceManager::GetCPortableDeviceManager()
{
	CPortableDeviceManager aCPortableDeviceManager;

	return aCPortableDeviceManager;
}

int CPortableDeviceManager::EnumerateAllDevices() const
{
	return 0;
}

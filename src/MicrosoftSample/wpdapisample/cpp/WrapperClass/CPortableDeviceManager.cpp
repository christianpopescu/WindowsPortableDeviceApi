#include "stdafx.h"
#include "CPortableDeviceManager.h"


CPortableDeviceManager::CPortableDeviceManager()
{
}


CPortableDeviceManager CPortableDeviceManager::GetCPortableDeviceManager()
{
	CPortableDeviceManager aCPortableDeviceManager;
    // CoCreate the IPortableDeviceManager interface to enumerate
	// portable devices and to get information about them.
	//<SnippetDeviceEnum1>
    HRESULT hr = CoCreateInstance(CLSID_PortableDeviceManager,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&(aCPortableDeviceManager.pPortableDeviceManager)));
    if (FAILED(hr))
    {
        printf("! Failed to CoCreateInstance CLSID_PortableDeviceManager, hr = 0x%lx\n", hr);
    }
	return aCPortableDeviceManager;
}

int CPortableDeviceManager::EnumerateAllDevices() const
{
	return 0;
}

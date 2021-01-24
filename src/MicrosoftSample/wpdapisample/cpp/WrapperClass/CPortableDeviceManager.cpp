#include "stdafx.h"
#include "CPortableDeviceManager.h"

CPortableDeviceManager::CPortableDeviceManager()
{
}


std::unique_ptr<CPortableDeviceManager> CPortableDeviceManager::GetCPortableDeviceManager()
{
    std::unique_ptr<CPortableDeviceManager> pCPortableDeviceManager =
        std::unique_ptr<CPortableDeviceManager>(new CPortableDeviceManager);
    // CoCreate the IPortableDeviceManager interface to enumerate
	// portable devices and to get information about them.
	//<SnippetDeviceEnum1>
    HRESULT hr = CoCreateInstance(CLSID_PortableDeviceManager,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&(pCPortableDeviceManager->pPortableDeviceManager)));
    if (FAILED(hr))
    {
        pCPortableDeviceManager = nullptr;
    }
	return pCPortableDeviceManager;
}

int CPortableDeviceManager::EnumerateAllDevices() const
{
	return 0;
}

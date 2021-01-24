#pragma once
#include "../stdafx.h"
class CPortableDeviceManager
{

	private:
	CPortableDeviceManager();
	CComPtr<IPortableDeviceManager> pPortableDeviceManager;
	
	public:
		CPortableDeviceManager(CPortableDeviceManager& cpdm) = delete;
		CPortableDeviceManager& operator=(CPortableDeviceManager& cpdm) = delete;
//		CPortableDeviceManager(CPortableDeviceManager&& cpdm) = default;
//		CPortableDeviceManager& operator=(CPortableDeviceManager&& cpdm) = default;

		// Factory method
		static std::unique_ptr<CPortableDeviceManager> GetCPortableDeviceManager();
		int EnumerateAllDevices() const;
};
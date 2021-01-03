// WpbApiSandboxConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <PortableDeviceApi.h>
#include <combaseapi.h>
#include <atlbase.h>
#define NUM_OBJECTS_TO_REQUEST  10

// Reads and displays the device friendly name for the specified PnPDeviceID string
void DisplayFriendlyName(
	IPortableDeviceManager* pPortableDeviceManager,
	PCWSTR                  pPnPDeviceID)
{
	DWORD   cchFriendlyName = 0;
	PWSTR   pszFriendlyName = NULL;

	// First, pass NULL as the PWSTR return string parameter to get the total number
	// of characters to allocate for the string value.
	HRESULT hr = pPortableDeviceManager->GetDeviceFriendlyName(pPnPDeviceID, NULL, &cchFriendlyName);
	if (FAILED(hr))
	{
		printf("! Failed to get number of characters for device friendly name, hr = 0x%lx\n", hr);
	}

	// Second allocate the number of characters needed and retrieve the string value.
	if ((hr == S_OK) && (cchFriendlyName > 0))
	{
		pszFriendlyName = new (std::nothrow) WCHAR[cchFriendlyName];
		if (pszFriendlyName != NULL)
		{
			hr = pPortableDeviceManager->GetDeviceFriendlyName(pPnPDeviceID, pszFriendlyName, &cchFriendlyName);
			if (SUCCEEDED(hr))
			{
				printf("Friendly Name: %ws\n", pszFriendlyName);
			}
			else
			{
				printf("! Failed to get device friendly name, hr = 0x%lx\n", hr);
			}

			// Delete the allocated friendly name string
			delete[] pszFriendlyName;
			pszFriendlyName = NULL;
		}
		else
		{
			printf("! Failed to allocate memory for the device friendly name string\n");
		}
	}

	if (SUCCEEDED(hr) && (cchFriendlyName == 0))
	{
		printf("The device did not provide a friendly name.\n");
	}
}


int main()
{
	CComPtr<IPortableDevice> pIPortableDevice;
	CComPtr<IPortableDeviceManager> pPortableDeviceManager;

	CoInitialize(nullptr);
	// 1. Creates the portable device manager object.
	// ----------------------------------------------

	HRESULT hr = S_OK;
	hr = pPortableDeviceManager.CoCreateInstance(CLSID_PortableDeviceManager);
	if (FAILED(hr))
	{
		printf("! Failed to CoCreateInstance CLSID_PortableDeviceManager, hr = 0x%lx\n", hr);
	}

	// 2. Retrieves a count of connected devices.
	// -----------------------------------------------
	DWORD cPnPDeviceIDs = 0;
	PWSTR*  pPnpDeviceIDs = NULL;
	if (SUCCEEDED(hr))
	{
		hr = pPortableDeviceManager->GetDevices(nullptr, &cPnPDeviceIDs);
		if (FAILED(hr))
		{
			printf("! Failed to get number of devices on the system, hr = 0x%lx\n", hr);
		}
	}
	std::cout << "Hello World!\n";
	std::cout << cPnPDeviceIDs << std::endl;;

	// 3. For each device show the device name
	if (SUCCEEDED(hr) && cPnPDeviceIDs)
	{
		pPnpDeviceIDs = new (std::nothrow) PWSTR[cPnPDeviceIDs];
		if (pPnpDeviceIDs != nullptr)
		{
			DWORD dwIndex = 0;

			hr = pPortableDeviceManager->GetDevices(pPnpDeviceIDs, &cPnPDeviceIDs);
			if (SUCCEEDED(hr))
			{
				// For each device found, display the devices friendly name,
				// manufacturer, and description strings.
				for (dwIndex = 0; dwIndex < cPnPDeviceIDs; dwIndex++)
				{
					printf("[%d] ", dwIndex);
					DisplayFriendlyName(pPortableDeviceManager, pPnpDeviceIDs[dwIndex]);
					//printf("    ");
					//DisplayManufacturer(pPortableDeviceManager, pPnpDeviceIDs[dwIndex]);
					//printf("    ");
					//DisplayDescription(pPortableDeviceManager, pPnpDeviceIDs[dwIndex]);

					CComPtr<IPortableDeviceContent> pContent;

					// Get an IPortableDeviceContent interface from the IPortableDevice interface to
					// access the content-specific methods.
					hr = CoCreateInstance(CLSID_PortableDeviceFTM,
						NULL,
						CLSCTX_INPROC_SERVER,
						IID_PPV_ARGS(&pIPortableDevice));
					if (SUCCEEDED(hr))
					{
						hr = pIPortableDevice->Open(pPnpDeviceIDs[dwIndex], nullptr);
						if (FAILED(hr))
						{
							if (hr == E_ACCESSDENIED)
							{
								printf("Failed to Open the device for Read Write access, will open it for Read-only access instead\n");
								//pClientInformation->SetUnsignedIntegerValue(WPD_CLIENT_DESIRED_ACCESS, GENERIC_READ);
							}
							else
							{
								printf("! Failed to Open the device, hr = 0x%lx\n", hr);
								// Release the IPortableDevice interface, because we cannot proceed
								// with an unopen device.
//								(*ppDevice)->Release();
	//							*ppDevice = NULL;
							}
						}
					}
					hr = pIPortableDevice->Content(&pContent);
					if (FAILED(hr))
					{
						printf("! Failed to get IPortableDeviceContent from IPortableDevice, hr = 0x%lx\n", hr);
					}

					// Enumerate content starting from the "DEVICE" object.
					if (SUCCEEDED(hr))
					{
						printf("\n");
//						RecursiveEnumerate(WPD_DEVICE_OBJECT_ID, pContent);
					}
				}
			}
			else
			{
				printf("! Failed to get the device list from the system, hr = 0x%lx\n", hr);
			}

			// Free all returned PnPDeviceID strings by using CoTaskMemFree.
			// NOTE: CoTaskMemFree can handle NULL pointers, so no NULL
			//       check is needed.
			//<SnippetDeviceEnum3>
			for (dwIndex = 0; dwIndex < cPnPDeviceIDs; dwIndex++)
			{
				CoTaskMemFree(pPnpDeviceIDs[dwIndex]);
				pPnpDeviceIDs[dwIndex] = NULL;
			}

			// Delete the array of PWSTR pointers
			delete[] pPnpDeviceIDs;
			pPnpDeviceIDs = NULL;
			//</SnippetDeviceEnum3>
		}
		else
		{
			printf("! Failed to allocate memory for PWSTR array\n");
		}
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

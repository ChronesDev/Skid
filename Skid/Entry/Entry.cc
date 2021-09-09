#include <index>
#include <lib.horion.h>

#include "../Client/Starter.cc"

SlimUtils::SlimMem mem;
const SlimUtils::SlimModule* gameModule;
static bool isRunning = true;

DWORD WINAPI KeyThread(LPVOID lpParam)
{
	logF("Key thread started");

	bool* keyMap = static_cast<bool*>(malloc(0xFF * 4 + 0x4));
	if (keyMap == nullptr)
		throw std::exception("Keymap not allocated");

	auto clickMap = reinterpret_cast<uintptr_t>(malloc(5));
	if (clickMap == 0)
		throw std::exception("Clickmap not allocated");

	bool* keyMapAddr = nullptr;
	uintptr_t sigOffset = FindSignature("48 8D 0D ?? ?? ?? ?? 89 1C B9");
	if (sigOffset != 0x0) {
		int offset = *reinterpret_cast<int*>((sigOffset + 3));                                   // Get Offset from code
		keyMapAddr = reinterpret_cast<bool*>(sigOffset + offset + /*length of instruction*/ 7);  // Offset is relative
	} else {
		logF("!!!KeyMap not located!!!");
		throw std::exception("Keymap not located");
	}

	C_HIDController** hidController = g_Data.getHIDController();

	while (isRunning) {
		if ((GameData::isKeyDown('L') && GameData::isKeyDown(VK_CONTROL)) || GameData::shouldTerminate()) {  // Press L to uninject
			isRunning = false;
			break;
		}

		for (uintptr_t i = 0; i < 0xFF; i++) {
			bool* newKey = keyMapAddr + (4 * i);
			bool newKeyPressed = (*newKey) && GameData::canUseMoveKeys();  // Disable Keybinds when in chat or inventory
			bool* oldKey = keyMap + (4 * i);
			if (newKeyPressed != *oldKey) {
				moduleMgr->onKeyUpdate((int)i, newKeyPressed);
			}
			if (*newKey != *oldKey) {  // Skip Chat or inventory checks
				TabGui::onKeyUpdate((int)i, *newKey);
				ClickGui::onKeyUpdate((int)i, *newKey);
			}
		}

		memcpy_s(keyMap, 0xFF * 4, keyMapAddr, 0xFF * 4);

		Sleep(2);
	}
	logF("Stopping Threads...");
	GameData::terminate();
	Sleep(200);  // Give the threads a bit of time to exit

	FreeLibraryAndExitThread(static_cast<HMODULE>(lpParam), 1);  // Uninject
}

DWORD WINAPI Start(LPVOID lpParam)
{
	// Crash Test
	// *(int*)nullptr = 10;

	logF("Starting up...");
	logF("MSC v%i at %s", _MSC_VER, __TIMESTAMP__);

	Sleep(10);

	init();

	Sleep(10);

	DWORD procId = GetCurrentProcessId();
	if (!mem.Open(procId, SlimUtils::ProcessAccess::Full)) {
		logF("Failed to open process, error-code: %i", GetLastError());
		return 1;
	}
	gameModule = mem.GetModule(L"Minecraft.Windows.exe");  // Get Module for Base Address

	MH_Initialize();
	GameData::initGameData(gameModule, &mem, (HMODULE)lpParam);
	Target::init(g_Data.getPtrLocalPlayer());

	Sleep(10);

	Hooks::Init();

	DWORD keyThreadId;
	CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)KeyThread, lpParam, NULL, &keyThreadId);  // Checking Keypresses
	logF("KeyT: %i", keyThreadId);

	Sleep(10);

	// Start Our Stuff
	Skid::Start();

	std::thread countThread([] {
		while (isRunning) {
			Sleep(1000);
			g_Data.fps = g_Data.frameCount;
			g_Data.frameCount = 0;
			g_Data.cpsLeft = g_Data.leftclickCount;
			g_Data.leftclickCount = 0;
			g_Data.cpsRight = g_Data.rightclickCount;
			g_Data.rightclickCount = 0;
		}
	});
	countThread.detach();

	logF("Count thread started");

	ExitThread(0);
}

DWORD WINAPI DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		{
			CreateThread(0, NULL, (LPTHREAD_START_ROUTINE)Start, hModule, NULL, 0);
			DisableThreadLibraryCalls(hModule);
			break;
		}
		case DLL_PROCESS_DETACH:
		{
			isRunning = false;

			scriptMgr.unloadAllScripts();
			configMgr->saveConfig();
			moduleMgr->disable();
			cmdMgr->disable();
			Hooks::Restore();
			//GameWnd.OnDeactivated();

			logF("Removing logger");
			Logger::Disable();

			MH_Uninitialize();
			delete moduleMgr;
			delete cmdMgr;
			delete configMgr;
			if (g_Data.getLocalPlayer() != nullptr) {
				C_GuiData* guiData = g_Data.getClientInstance()->getGuiData();
				if (guiData != nullptr && !GameData::shouldHide())
					guiData->displayClientMessageF("%sEjected!", RED);
			}
			break;
		}
	}
	return TRUE;
}
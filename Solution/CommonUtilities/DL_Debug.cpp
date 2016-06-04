#include "stdafx.h"
#include "DL_Debug.h"
#include <cassert>
#include <cstdarg>
#include <sstream>
#include <ctime>
#include "DL_StackWalker.h"
#include <sys/types.h>
#include <sys/timeb.h>
#ifdef RELEASE_BUILD
#include <ShlObj.h>
#endif

DL_Debug::Debug* DL_Debug::Debug::ourInstance = nullptr;

DL_Debug::Debug::Debug()
{
	std::pair<bool, CU::String<256>> logSetting;
	logSetting.first = false;

	logSetting.second = "Engine";
	myFilterLogStatus[eFilterLog::ENGINE] = logSetting;

	logSetting.second = "Game";
	myFilterLogStatus[eFilterLog::GAME] = logSetting;

	logSetting.second = "Resource";
	myFilterLogStatus[eFilterLog::RESOURCE] = logSetting;

	logSetting.second = "DirectX";
	myFilterLogStatus[eFilterLog::DIRECTX] = logSetting;

	logSetting.second = "FBX";
	myFilterLogStatus[eFilterLog::FBX] = logSetting;

	logSetting.second = "FunctionTimer";
	myFilterLogStatus[eFilterLog::FUNCTION_TIMER] = logSetting;

	logSetting.second = "Entity";
	myFilterLogStatus[eFilterLog::ENTITY] = logSetting;

	logSetting.second = "PowerUp";
	myFilterLogStatus[eFilterLog::POWERUP_L] = logSetting;

	logSetting.second = "Component";
	myFilterLogStatus[eFilterLog::COMPONENT] = logSetting;
}


DL_Debug::Debug::~Debug()
{
}

bool DL_Debug::Debug::Create(CU::String<256> aFile)
{
	assert(ourInstance == nullptr && "Debugobject already created");
	ourInstance = new Debug();

	time_t now = time(0);
	struct tm tstruct;
	char buf[30];
	localtime_s(&tstruct, &now);

	strftime(buf, sizeof(buf), "%Y-%m-%d_%H_%M_%S", &tstruct);

	CU::String<256> logFolder = "log\\";

	CreateDirectory("log", NULL);

	logFolder += buf;
	logFolder += "_";
	logFolder += aFile;
	ourInstance->myDebugFile.open(logFolder.c_str());
	if (ourInstance == nullptr)
	{
		return(false);
	}
	return(true);
}

bool DL_Debug::Debug::Destroy()
{
	//if (ourInstance->myDebugFile.close() == false)
	//{
	//	return(false);
	//}

	ourInstance->myDebugFile.close();

	delete ourInstance;
	ourInstance = nullptr;
	return(true);
}

DL_Debug::Debug* DL_Debug::Debug::GetInstance()
{
	return(ourInstance);
}

void DL_Debug::Debug::WriteLog(const eFilterLog aFilter, const char* aFormattedString, ...)
{
	if (myFilterLogStatus[aFilter].first == false)
		return;

	CU::String<256> logPrefix = myFilterLogStatus[aFilter].second;


	//Get time and store as string in buf
	time_t now = time(0);
	struct tm tstruct;
	char buf[30];
	localtime_s(&tstruct, &now);

	strftime(buf, sizeof(buf), "%H:%M:%S:", &tstruct);

	//Get Miliseconds and store in tStructMilli
	struct _timeb tstructMilli;
	char bufMilli[128];

	_strtime_s(bufMilli);
	_ftime_s(&tstructMilli);

	//Get VA_ARGS and store as string in buffer
	char buffer[4096];
	va_list args;
	va_start(args, aFormattedString);
	vsprintf_s(buffer, aFormattedString, args);
	perror(buffer);
	va_end(args);


	CU::String<256> output("[");
	output += buf;
	output += tstructMilli.millitm;
	output += "][";
	output += logPrefix;
	output += "]:";
	output += buffer;

	ourInstance->myDebugFile << output.c_str() << std::endl;
	ourInstance->myDebugFile.flush();
}

void DL_Debug::Debug::PrintMessage(const char* aString)
{
	ourInstance->myDebugFile << aString << std::endl;
	ourInstance->myDebugFile.flush();
}

void DL_Debug::Debug::PrintMessageVA(const char *aFormattedString, ...)
{
	char buffer[1024];
	va_list args;
	va_start(args, aFormattedString);
	vsprintf_s(buffer, aFormattedString, args);
	perror(buffer);
	va_end(args);

	ourInstance->myDebugFile << buffer << std::endl;
	ourInstance->myDebugFile.flush();
}

void DL_Debug::Debug::AssertMessageVA(const char *aFileName, int aLine, const char *aFunctionName, const CU::String<256>& aFormattedString, ...)
{
	char buffer[1024];
	va_list args;
	va_start(args, aFormattedString);
	vsprintf_s(buffer, aFormattedString.c_str(), args);
	perror(buffer);
	va_end(args);

	AssertMessage(aFileName, aLine, aFunctionName, buffer);
}

void DL_Debug::Debug::AssertMessage(bool aAssertExpression, const char *aFileName, int aLine, const char *aFunctionName, const CU::String<256>& aString)
{
	if (aAssertExpression == false)
	{
		AssertMessage(aFileName, aLine, aFunctionName, aString);
	}
}

void DL_Debug::Debug::AssertMessage(const char *aFileName, int aLine, const char *aFunctionName, const CU::String<256>& aString)
{
	CU::String<256> output("\nError Message: ");
	output += aString;
	output += "\n\n";
	output += "File: ";
	output += aFileName;
	output += "\n\n";
	output += "Line: ";
	output += aLine;
	output += "\n";
	output += "Function: ";
	output += aFunctionName;
	output += "\n\n";

	ourInstance->myDebugFile << output.c_str();
	ourInstance->myDebugFile << std::endl << std::endl << "Callstack" << std::endl;

	DL_Debug::StackWalker sw;
	sw.ShowCallstack();
	ourInstance->myDebugFile.flush();

	const size_t cSize = strlen(output.c_str()) + 1;
	wchar_t* wc = new wchar_t[cSize];
	size_t tempSize;
	mbstowcs_s(&tempSize, wc, cSize, output.c_str(), cSize);

	//_wassert(wc, 0, aLine);

	_wassert(wc, _CRT_WIDE(__FILE__), __LINE__);
	delete[] wc;
}

void DL_Debug::Debug::DebugMessage(const char *aFileName, int aLine, const char *aFunctionName, const char *aFormattedString, ...)
{
	ourInstance->myDebugFile << std::endl << "File: " << aFileName << std::endl << "Line: " << aLine << std::endl << "Function: " << aFunctionName << std::endl;
	char buffer[1024];
	va_list args;
	va_start(args, aFormattedString);
	vsprintf_s(buffer, aFormattedString, args);
	perror(buffer);
	va_end(args);

	ourInstance->myDebugFile << buffer << std::endl;
	ourInstance->myDebugFile.flush();
}

void DL_Debug::Debug::ShowMessageBox(HWND aHwnd, LPCSTR aText, LPCSTR aTitle, UINT aType)
{
	MessageBox(aHwnd, aText, aTitle, aType);
}

void DL_Debug::Debug::ActivateFilterLog(const eFilterLog aFilter)
{
	if (aFilter == eFilterLog::ALL)
	{
		for (auto it = myFilterLogStatus.begin(); it != myFilterLogStatus.end(); ++it)
		{
			it->second.first = true;
		}
	}
	else
	{
		myFilterLogStatus[aFilter].first = true;
	}
}

void DL_Debug::Debug::DeactiveFilterLog(const eFilterLog aFilter)
{
	if (aFilter == eFilterLog::ALL)
	{
		for (auto it = myFilterLogStatus.begin(); it != myFilterLogStatus.end(); ++it)
		{
			it->second.first = false;
		}
	}
	else
	{
		myFilterLogStatus[aFilter].first = false;
	}
}
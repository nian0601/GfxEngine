#pragma once
#include "CUString.h"
#include "CUMap.h"
#include <functional>
#include <map>
#include <vector>
#include <windows.h>
#include <thread>
#include <mutex>

namespace CU
{
	typedef std::function<void(const CU::String<128>&)> callback_function_file;

	class FileWatcher
	{
	public:
		FileWatcher();
		~FileWatcher();

		/* Will check the file for includes and add them as well*/
		bool WatchFileChangeWithDependencies(const CU::String<128>& aFile, callback_function_file aFunctionToCallOnChange);
		bool WatchFileChange(const CU::String<128>& aFile, callback_function_file aFunctionToCallOnChange);


		void FlushChanges();
	private:
		void UpdateChanges(const CU::String<128>& aDir);
		void OnFolderChange(const CU::String<128>& aDir);
		bool WatchDirectory(const CU::String<128>& aDir);
		void OnFileChange(const CU::String<128>& aFile);
		std::vector<WIN32_FIND_DATA> GetAllFilesInFolder(const CU::String<128>& aDir);

		std::thread* myThread;

		typedef	Map<CU::String<128>, std::vector<WIN32_FIND_DATA>> FolderMap;
		FolderMap myFolders;

		std::vector<CU::String<128>> myFileChangedThreaded;
		std::vector<CU::String<128>> myFileChanged;
		Map<CU::String<128>, std::vector<callback_function_file> > myCallbacks;

		typedef Map<CU::String<128>, std::vector<CU::String<128>>> Dependencies;
		Dependencies myDependencies;

		std::mutex myMutex;
		bool myShouldEndThread;
		bool myThreadIsDone;
	};

}
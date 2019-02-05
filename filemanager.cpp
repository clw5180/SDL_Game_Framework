//=============================================================================
#include "filemanager.h"
#include "log.h"
#include "stringify.h"

#ifdef _WIN32
#include <direct.h>  //clw note:for getcwd()
#include <windows.h>  //clw note:for 自定义的dirent.h，已搬到filemanager.h中
//#include "dirent.h"
#else
#include <sys/param.h>
#include <dirent.h>
#endif

#include <stdio.h>

#define MAXPATHLEN 260 //clw modify 20190131:From microsoft

//=============================================================================
bool CFileManager::SetContents(std::string Filename, std::string Content, bool Relative) 
{
	if(Filename == "") return false;

	if(Relative) Filename = GetCWD() + DIR_SEPARATOR + Filename;

	std::ofstream FileHandle;

    FileHandle.open(Filename.c_str());
	if(!FileHandle.is_open()) return false;

	FileHandle << Content;
	FileHandle.close();

	return true;
}

//-----------------------------------------------------------------------------
std::string CFileManager::GetContents(std::string Filename, bool Relative) {
	if(Filename == "") return "";

	if(Relative) Filename = GetCWD() + DIR_SEPARATOR + Filename;

	std::string Content;
	std::ifstream FileHandle;

    FileHandle.open(Filename.c_str());

	if(FileHandle.is_open()) {
		while(FileHandle.good()) {
			std::string Buffer;
			getline(FileHandle, Buffer);
			if(Buffer == "") continue;

			Content += Buffer + "\n";
		}

		FileHandle.close();
	}

	return Content;
}

//-----------------------------------------------------------------------------
std::vector<std::string> CFileManager::GetFilesInFolder(std::string Folder) 
{
	std::vector<std::string> List;

	std::string Path = GetCWD();

	if(Folder != "") 
		Path += (DIR_SEPARATOR + Folder);

	#ifdef __APPLE__
		NSError* Error;

		NSString* PathNS			= [NSString stringWithUTF8String:Path.c_str()];
		NSArray* DirectoryContents	= [[NSFileManager defaultManager] contentsOfDirectoryAtPath:PathNS error:&Error];

		for(id File in DirectoryContents) {
			std::string Filename = Path + DIR_SEPARATOR + [File cStringUsingEncoding:1];

			List.push_back(Filename);
		}
	#else
        DIR* DirHandle = NULL;
        dirent* FileHandle = NULL;

        // Needs improved
        if((DirHandle = opendir(Folder.c_str())) != NULL) 
		{
            while((FileHandle = readdir(DirHandle)) != NULL) 
			{
				//clw note:在win操作系统，每个文件夹内都有一个看不到的..文件夹
				//         linux下应该同时有.和..文件夹
                if(std::string(FileHandle->d_name) == ".")  continue;
                if(std::string(FileHandle->d_name) == "..") continue;

                std::string Filename = Path + DIR_SEPARATOR + FileHandle->d_name;

                //Log("Found File: %s", Filename.c_str());

                List.push_back(Filename);
            }

            closedir(DirHandle);
        }else{
            Log("Unable to open directory : %s", Path.c_str());
        }
	#endif

	return List;
}

//-----------------------------------------------------------------------------
std::string CFileManager::GetCWD() 
{
	std::string CWD;

	#ifdef __APPLE__
		NSString* ResourcePath = [[NSBundle mainBundle] resourcePath];
		CWD = [ResourcePath cStringUsingEncoding:1];
	#else
		char Buffer[MAXPATHLEN];
		CWD = (_getcwd(Buffer, MAXPATHLEN) ? std::string(Buffer) : std::string(""));
	#endif

	return CWD;
}

//-----------------------------------------------------------------------------
std::string CFileManager::GetFilenameWithoutExt(std::string Filename) {
	std::vector<std::string> Parts = CStringify::Explode(Filename, DIR_SEPARATOR);
	std::string NewFilename = Parts[Parts.size() - 1];

	// To Do: Filename could potentially have one or more dots
	Parts		= CStringify::Explode(NewFilename, ".");
	NewFilename	= Parts[0];

	return NewFilename;
}

//-----------------------------------------------------------------------------
std::string CFileManager::GetFilenameExt(std::string Filename) {
	std::vector<std::string> Parts = CStringify::Explode(Filename, ".");

	return (Parts.size() <= 1 ? "" : Parts[Parts.size() - 1]);
}

//=============================================================================



/************************************************************************/
/*  clw modify 20190131
/************************************************************************/

//dirent.c
static HANDLE hFind;

DIR *opendir(const char *name)
{
	DIR *dir;
	WIN32_FIND_DATA FindData;
	char namebuf[512];

	sprintf_s(namebuf, "%s\\*.*", name);

	hFind = FindFirstFile(namebuf, &FindData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		printf("FindFirstFile failed (%d)\n", GetLastError());
		return 0;
	}

	dir = (DIR *)malloc(sizeof(DIR));
	if (!dir)
	{
		printf("DIR memory allocate fail\n");
		return 0;
	}

	memset(dir, 0, sizeof(DIR));
	dir->dd_fd = 0;   // simulate return  

	return dir;
}

struct dirent *readdir(DIR *d)
{
	int i;
	static struct dirent dirent;
	BOOL bf;
	WIN32_FIND_DATA FileData;
	if (!d)
	{
		return 0;
	}

	bf = FindNextFile(hFind, &FileData);
	//fail or end  
	if (!bf)
	{
		return 0;
	}

	for (i = 0; i < 256; i++)
	{
		dirent.d_name[i] = FileData.cFileName[i];
		if (FileData.cFileName[i] == '\0') break;
	}
	dirent.d_reclen = i;
	dirent.d_reclen = FileData.nFileSizeLow;

	//check there is file or directory  
	if (FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		dirent.d_type = 2;
	}
	else
	{
		dirent.d_type = 1;
	}


	return (&dirent);
}

int closedir(DIR *d)
{
	if (!d) return -1;
	hFind = 0;
	free(d);
	return 0;
}
/************************************************************************/
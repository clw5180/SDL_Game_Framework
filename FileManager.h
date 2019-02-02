#ifndef __FILEMANAGER_H__
#define __FILEMANAGER_H__

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>

#define DIR_SEPARATOR "/"

class CFileManager
{
public:
	static bool SetContents(std::string Filename, std::string Content, bool Relative = true);

	static std::string GetContents(std::string Filename, bool Relative = true);

	static std::vector<std::string> GetFilesInFolder(std::string Folder);

	static std::string GetCWD();

	static std::string GetFilenameWithoutExt(std::string Filename);

	static std::string GetFilenameExt(std::string Filename);
};

/************************************************************************/
/*  clw modify 20190131
/************************************************************************/
// dirent.h
typedef struct _dirdesc 
{
	int     dd_fd;      /** file descriptor associated with directory */
	long    dd_loc;     /** offset in current buffer */
	long    dd_size;    /** amount of data returned by getdirentries */
	char    *dd_buf;    /** data buffer */
	int     dd_len;     /** size of data buffer */
	long    dd_seek;    /** magic cookie returned by getdirentries */
} DIR;

# define __dirfd(dp)    ((dp)->dd_fd)

DIR *opendir(const char *);
struct dirent *readdir(DIR *);
void rewinddir(DIR *);
int closedir(DIR *);

#include <sys/types.h>

struct dirent
{
	long d_ino;              /* inode number*/
	off_t d_off;             /* offset to this dirent*/
	unsigned short d_reclen; /* length of this d_name*/
	unsigned char d_type;    /* the type of d_name*/
	char d_name[1];          /* file name (null-terminated)*/
};
/************************************************************************/


#endif

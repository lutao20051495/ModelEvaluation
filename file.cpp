#ifdef WINDOWS
    #include <windows.h>
#else
    #include <sys/types.h>
    #include <dirent.h>
    #include <sys/stat.h>
#endif 

#include <iostream>
using namespace std;
#include "file.h"

/* Get file name extension */
string getFileNameExt(const string& file_name)
{
	return file_name.substr(file_name.find_last_of('.')+1);
}

/* Returns a list of files in a directory (except the ones that begin with a dot) */
bool GetFileName(std::vector<string> &out, const string &directory, const string& type)
{
#ifdef WINDOWS
	HANDLE dir;
	WIN32_FIND_DATA file_data;

	if ((dir = FindFirstFile((directory + "/*" +).c_str(), &file_data)) == INVALID_HANDLE_VALUE)
	{
		cout << "no file found!" << endl;
		return false; 
	}
	do {
		const string file_name = file_data.cFileName;
		const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

		if (file_name[0] == '.')
			continue;

		if (is_directory)
			continue;
	
		if (getFileNameExt(file_name)==type)
		{
			out.push_back(file_name);
		}
	} while (FindNextFile(dir, &file_data));
	FindClose(dir);
    
#else
    DIR *dir;
    class dirent *ent;
    class stat st;

    dir = opendir(directory.c_str());
    if(!dir)
    {
	    cout << "no files found in " << directory << endl;
	    return false;
    }
    while ((ent = readdir(dir)) != NULL) 
    {
	    const string file_name = ent->d_name;

	    if (file_name[0] == '.')
		continue;
		
	    const string full_file_name = directory + "/" + file_name;
	    if (stat(full_file_name.c_str(), &st) == -1)
		continue;

	    const bool is_directory = (st.st_mode & S_IFDIR) != 0;

	    if (is_directory)
		continue;
	
	    if (getFileNameExt(file_name)==type)
	    {
		    out.push_back(file_name);
	    }
    }
    closedir(dir);
#endif
    return true;
} // GetFilesInDirectory
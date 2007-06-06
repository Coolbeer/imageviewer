#ifndef PWANDIR_H
#define PWANDIR_H

#include <string>
#include <vector>
#include <iostream>
#include <dirent.h>
#include "pwanutils.h"
#include "pwanfileinfo.h"

typedef std::vector<std::string> stringvector;

namespace pwan
{
	class dir;
	
	typedef std::vector<pwan::fileInfo> fileinfovector;
	
	class dir
	{
		public:
			dir(const std::string path = ".");
//  			fileinfovector readdirectory(std::string path, stringvector filter);
			fileinfovector entryInfoList(stringvector filter);

		private:
			std::string currentpath;
	};
	
}

#endif

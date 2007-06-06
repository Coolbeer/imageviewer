#ifndef PWANFILEINFO_H
#define PWANFILEINFO_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

typedef std::vector<std::string> stringvector;

namespace pwan
{
	class fileInfo
	{
		public:
			fileInfo();
			fileInfo(const std::string &file);
			std::string fileName(void);
			std::string path(void);
			unsigned long long int size(void);

		private:
			void setFileName(std::string newFileName);
			void setPath(std::string newPath);
			void setSize(long long int newSize);
			
			std::string absolutePath(std::string path);

			std::string internalfilename;
			std::string internalpath;
			unsigned long long int internalsize;
		friend class dir;
	};
}

#endif

#include "pwanfileinfo.h"
#include "pwanutils.h"
#include "pwanstrings.h"

pwan::fileInfo::fileInfo()
{
	internalfilename = "";
	internalpath = "";
	internalsize = 0;
}

pwan::fileInfo::fileInfo(const std::string &file)
{
	std::ifstream testfile(file.c_str(), std::ios::in);
	if(!testfile)
	{
		std::cout << "fileInfo constructor: " << file << " does not exist\n\n";
		exit(1);
	}
	testfile.close();
	internalpath = file.substr(0, file.find_last_of("/"));
	if(internalpath == file)
		internalpath = ".";
	internalfilename = file.substr(file.find_last_of("/")+1);
	internalpath = absolutePath(internalpath);
}

std::string pwan::fileInfo::fileName(void)
{
	return internalfilename;
}

std::string pwan::fileInfo::path(void)
{
	return internalpath;
}

unsigned long long int pwan::fileInfo::size(void)
{
	return internalsize;
}

void pwan::fileInfo::setFileName(std::string newFileName)
{
	internalfilename = newFileName;
}

void pwan::fileInfo::setPath(std::string newPath)
{
	internalpath = newPath;
}

void pwan::fileInfo::setSize(long long int newSize)
{
	internalsize = newSize;
}

std::string pwan::fileInfo::absolutePath(std::string path)
{
	std::string returnvalue;
	if(path[0] != '/')
	{
		char *tmpcwd = new char[4096];
		std::string cwd;
		if(getcwd(tmpcwd, 4096) == NULL)
		{
			std::cout << "absolutepath failed \n\n";
			exit(1);
		}
		cwd = tmpcwd;
		delete(tmpcwd);
		path = cwd + "/" + path;
	}
	stringvector expath = pwan::strings::explode(path, "/");
	stringvector tmpretvalue;
	for(stringvector::iterator iter = expath.begin(); iter != expath.end(); ++iter)
	{
		if((*iter) == ".")
			iter = iter;
		else if((*iter) == "")
			iter = iter;
		else if((*iter) == "..")
			tmpretvalue.pop_back();
		else
			tmpretvalue.push_back((*iter));
	}
	for(stringvector::iterator iter = tmpretvalue.begin(); iter != tmpretvalue.end(); ++iter)
		returnvalue += "/" + (*iter);
	return returnvalue;
}

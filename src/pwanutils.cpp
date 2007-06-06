#include "pwanutils.h"

std::string pwan::inttostring(long long int number, int padding, int base)
{
	if(base < 2 && base > 36)
	{
		std::cout << "pwan::inttostring: base not in range\n\n";
		exit(1);
	}
	std::string numbers = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string returnvalue = "";
	while(1)
	{
		long long int remainder = number % base;
		returnvalue = numbers.at(remainder) + returnvalue;
		number = number / base;
		if(!number)
			break;
	}
	for (int i = 0; i < (int)(padding - (int)returnvalue.size() )+1; ++i)
		returnvalue = "0" + returnvalue;
	return returnvalue;
}

stringvector pwan::explodestring(std::string inputstring, std::string explodeby)
{
	std::vector<std::string> returnvalue;
	std::string::size_type start = 0;
	std::string::size_type end = 0;

	while(1)
	{
		end = inputstring.find_first_of(explodeby, start);
		if(end == std::string::npos)
		{
			if(start != 0)
				returnvalue.push_back(inputstring.substr(start));
			return returnvalue;
		}
		//std::cout << inputstring.substr(start, end) << "\n";
		returnvalue.push_back(inputstring.substr(start, end-start));
		start = end +1 ;
	}
	return returnvalue;
}

std::string pwan::getextention(std::string filename)
{
	std::vector<std::string> exfilename = pwan::explodestring(filename, ".");
	if(exfilename.size() > 1)
		return *(exfilename.end() -1);
	else
		return "";
}

std::string pwan::stringtolower(std::string inputstring)
{
	for(unsigned int i=0; i!=inputstring.size(); ++i)
	{
		inputstring[i] = std::tolower(inputstring[i]);
	}
	return inputstring;
}

float pwan::calculatezoom(int imagedims[2], int displaydims[2])
{
	float returnvalue;
	float tempzoom1 = (float)displaydims[0]  / (float)imagedims[0];
	float tempzoom2 = (float)displaydims[1] / (float)imagedims[1];
	if (tempzoom1 < tempzoom2)
		returnvalue = tempzoom1;
	else
		returnvalue = tempzoom2;
	
	return returnvalue;
}
pwan::doubleint pwan::calculateoffset(int imagedims[2], int displaydims[2])
{
	pwan::doubleint returnvalue;
	returnvalue.x = ((displaydims[0]/2) - (imagedims[0]/2));
	returnvalue.y = ((displaydims[1]/2) - (imagedims[1]/2));
	
	if(returnvalue.x < 0)
		returnvalue.x = 0;
	if(returnvalue.y < 0)
		returnvalue.y = 0;
	return returnvalue;
}


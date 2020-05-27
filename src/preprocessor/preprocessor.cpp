#include <iostream>
#include <fstream>
#include <algorithm>
#include "preprocessor.hpp"

template<typename T, typename P>
T remove_if(T beg, T end, P pred)
{
    T dest = beg;
    for (T itr = beg;itr != end; ++itr)
        if (!pred(*itr))
            *(dest++) = *itr;
    return dest;
}

std::string Preprocessor::loadFile(std::string filename) {
  std::string line;
  std::string out;
  std::ifstream myfile (filename);
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      std::string::iterator end_pos = std::remove(line.begin(), line.end(), '\n');
      line.erase(end_pos, line.end());
      out.append(line);
    }
    myfile.close();
  }
  else std::cout << "Unable to open file"; 
  return out;
}
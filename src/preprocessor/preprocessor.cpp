#include <iostream>
#include <fstream>
#include <algorithm>
#include "preprocessor/preprocessor.hpp"

template<typename T, typename P>
T remove_if(T beg, T end, P pred)
{
    T dest = beg;
    for (T itr = beg;itr != end; ++itr)
        if (!pred(*itr))
            *(dest++) = *itr;
    return dest;
}

std::string Preprocessor::loadAndCleanFile(std::string filename) {
  std::string line;
  std::string out;
  std::ifstream myfile (filename);
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      out.append(cleanFile(line));
    }
    myfile.close();
  }
  else std::cout << "Unable to open file"; 
  return out;
}
std::string Preprocessor::cleanFile(std::string content) {
  std::string::iterator end_pos = std::remove(content.begin(), content.end(), '\n');
  content.erase(end_pos, content.end());
  return content;
  
} 
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <boost/filesystem.hpp>

using namespace boost::filesystem;

const int MAX = 10;
const std::string NORM_MODE = "\x1b[0m";
const std::string BLUE_BOLD = "\x1b[34;1m";
const std::string RED_BOLD = "\x1b[31;1m";
const std::string GREEN_BOLD = "\x1b[32;1m";

typedef std::vector<path> vec;

class Text_Mode
{
private:
    const std::string mode;
public:
    Text_Mode(const std::string & Mode);
    ~Text_Mode();
};

Text_Mode::Text_Mode(const std::string & Mode) : mode(Mode)
{
    std::cout << "   " + mode;
};

Text_Mode::~Text_Mode()
{
    
    std::cout << NORM_MODE << ' ';
};



void dirwalk(const path & p, vec & arr)
{
     
      if (is_directory(p)) {     
      
          std::cout << p << " is a directory containing:\n";       
 
          std::copy(directory_iterator(p), directory_iterator(), back_inserter(arr));     

          for (vec::const_iterator it(arr.begin()), it_end(arr.end()); it != it_end; ++it) {             
          
              if (!is_directory((*it))) { 
                  if (it->filename().native().find(".txt") != std::string::npos) {
                      Text_Mode red(RED_BOLD);
                      std::cout << it->filename();
                  } 
                  else if (it->filename().native().find(".") == std::string::npos) {
                      Text_Mode red(GREEN_BOLD);
                      std::cout << it->filename();
                  }
                  else {     
                      std::cout << "   " << it->filename();              
                  }    
                  std::cout << file_size((*it)) << '\n';
              }    
              else {
                  Text_Mode blue(BLUE_BOLD);
                  std::cout << (*it).filename() << '\n';                  
              }  
          }
      }   

}

void fsize(const path & p)
{
                       
    vec arr;                
    std::cout  << std::endl;
    if (is_directory(p)) {        
        dirwalk(p, arr);
    }    
    else {        
        std::cout << p.filename() << " " << file_size(p) << std::endl;
    }    
    if (arr.empty()) {
        return;
    }    
      
    else {
        for (int i = 0; i < arr.size(); i++) {
                     
            if (is_directory(arr[i]))
                fsize(arr[i]);
        }        
            
                    
    }    
        
            
}

int main(int argc, char** argv)
{
    path p(std::string("."));
    fsize(p);
    return 0;
}

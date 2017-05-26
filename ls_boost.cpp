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
    std::cout << NORM_MODE;
};



void dirwalk(const path & dir, vec & arr)
{
    std::cout << dir << " is a directory containing:\n";  
    std::copy(directory_iterator(dir), directory_iterator(), back_inserter(arr));
    for (const auto& p : arr) {
        if (!is_directory(p)) { 
            if (p.filename().native().find(".txt") != std::string::npos) {
                Text_Mode red(RED_BOLD);
                std::cout << p.filename() << ' ';
            } else if (p.filename().native().find(".") == std::string::npos) {
                Text_Mode red(GREEN_BOLD);
                std::cout << p.filename() << ' ';
            } else {     
                std::cout << "   " << p.filename() << ' ';              
            }    
            std::cout << file_size(p) << '\n';
        } else {
            Text_Mode blue(BLUE_BOLD);
            std::cout << p.filename() << '\n';   
        }  
    }    
}

void fsize(const path & p)
{
                       
    vec arr;                
    std::cout  << std::endl;
    if (is_directory(p)) {        
        dirwalk(p, arr);
    } else {        
        std::cout << p.filename() << " " << file_size(p) << std::endl;
    }    
    if (arr.empty()) {
        return;
    } else {
        for (int i = 0; i < arr.size(); i++) {                    
            if (is_directory(arr[i]))
                fsize(arr[i]);
        }                        
    }             
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cerr << "usage: " << argv[0] << " file_name" << '\n'; 
        return -1;
    }    
    path p(argv[1]);
    try {
        fsize(p);
    } catch (const filesystem_error& ex) {
        std::cout << ex.what() << '\n';
    } 
    return 0;
}

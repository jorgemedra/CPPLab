
/**********************************************************************
 * 
 * Reference:
 * https://en.cppreference.com/w/cpp/filesystem
 * 
 * IMPORTANT: 
 * 
 * + REQUIERES link option: -lstdc++fs
 * 
 * + For Path and Ubuntu, i had to add to the namespace ::__cxx11 to 
 * find definition of path class.
 * 
 * 
 * For Microsoft:
 * https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/stat-functions?view=msvc-160
 * 
 * For Linux / Unix
 struct stat {
    dev_t     st_dev;     // ID of device containing file 
    ino_t     st_ino;     // inode number 
    mode_t    st_mode;    // protection 
    nlink_t   st_nlink;   // number of hard links 
    uid_t     st_uid;     // user ID of owner 
    gid_t     st_gid;     // group ID of owner 
    dev_t     st_rdev;    // device ID (if special file) 
    off_t     st_size;    // total size, in bytes 
    blksize_t st_blksize; // blocksize for file system I/O 
    blkcnt_t  st_blocks;  // number of 512B blocks allocated 
    time_t    st_atime;   // time of last access 
    time_t    st_mtime;   // time of last modification 
    time_t    st_ctime;   // time of last status change 
};
**********************************************************************/

#include "file.h"

#include <filesystem>
#include <ctime>
#include <sys/stat.h>

#ifndef WIN32
#include <unistd.h>
#endif

#ifdef WIN32
#define stat _stat
#endif


using namespace  jomt::test;
namespace fs = std::filesystem;
namespace fspth = std::filesystem::__cxx11;


void FileTest::doTest()
{
    std::cout << "Getting current path with fs::current_path():\n";
    fspth::path pth = fs::current_path();
    std::cout << "\tCURRENT PATH: [" << pth << "]\n";

    pth /= "README.md"; //Concatenates the path and Filename with separator

    std::cout << "\nChecking if the file [" << pth << "] exits:\n";

    if(!fs::exists(pth))
        std::cout << "\tThe file [" << pth << "] doesn't exist:\n";
    else
    {
        std::cout << "\tThe file [" << pth << "] exists:\n";
        
        std::cout << "\nGetting file size of '" << pth << ":\n";
        std::uintmax_t size = fs::file_size(pth);
        std::cout << "\tFile Size: " << size << " bytes\n";

        std::cout << "\nGetting times of '" << pth << ":\n";
        
        //Getting the information
        struct stat result;
        stat(pth.c_str(), &result);

        time_t mod_time = result.st_mtime;

        struct tm *timeinfo;
        timeinfo = localtime(&mod_time);
        char bufTime[64];
        std::strftime(bufTime, sizeof bufTime, "%F %H:%M:%S", timeinfo);
        std::cout << "\tModif. Time: " << bufTime << "\n"
                  << "\tIt has a size of: " <<  result.st_size << " bytes\n";
    }
}
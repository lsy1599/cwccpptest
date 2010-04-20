//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#include <boost\program_options.hpp>
#include <string>
#include <sstream>
#include <vector>
#pragma hdrstop
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR lpCmdLine, int)
{
    using std::vector;
    using std::string;
    using std::stringstream;
    using std::endl;

    namespace po = boost::program_options;
    po::options_description desc("My Commnad Line");
    desc.add_options()
        ("help,h", "help message")
        ("author,a", "Author")
        ("string,s", po::value<string>(),"run as client and connect to the specified IP")
        ("int,i", po::value<int>(), "the number of concurrent connections")
    ;

    po::variables_map vm;
    vector<string> args = po::split_winmain(lpCmdLine);
    po::store(po::command_line_parser(args).options(desc).allow_unregistered().run(), vm);
    if(vm.size()>0){
        stringstream os;
        if (vm.count("author")) {

          os << "Author: Chui-Wen Chiu" << endl;
          os << "Blog: http://chuiwenchiu.spaces.live.com" << endl;
        }

           // -h or --help
        if (vm.count("help")) {
           os << desc << endl;
           ::MessageBox(0, os.str().c_str(),0, 0);
           return 1;
        }

        // -s "123 456 789" or --string="123 456 789"
        if(vm.count("string")) {
          string sip = vm["string"].as<string>();
          os << "string: " << sip << endl;
          // connect to server...
        }

        // -i 1 or --int=1
        if(vm.count("int")) {
          int t = vm["int"].as<int>();
          os << "int: " << t << endl;
          // connect to server...
        }

        ::MessageBox(0, os.str().c_str(),0, 0);
    }
    return 0;

}
//---------------------------------------------------------------------------

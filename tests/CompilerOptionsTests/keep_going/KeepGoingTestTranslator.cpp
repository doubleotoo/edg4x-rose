#include <string>
#include <boost/lexical_cast.hpp>
#include "rose.h"

//-----------------------------------------------------------------------------
// Method Declarations
//-----------------------------------------------------------------------------
static void
ShowUsage(std::string program_name);

//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
  std::string program_name(argv[0]);

  std::vector<std::string> rose_cmdline;
  rose_cmdline.push_back(program_name);
  rose_cmdline.push_back("-rose:keep_going");

  bool has_expected_status = false;
  int expected_backend_status = 0;

  for (int ii = 1; ii < argc; ++ii)
  {
      std::string arg = argv[ii];
      if ((arg == "-h") || (arg == "--help"))
      {
          ShowUsage(program_name);
          return 0;
      }
      else if (arg.find("--expected-backend-status=") == 0)
      {
          arg.replace(0, 26, "");
          if (arg.empty())
          {
              std::cerr
                  << "[ERROR] "
                  << "[" << program_name << "] "
                  << "--expected_backend_status requires an argument, see --help"
                  << std::endl;
              return 1;
          }
          else
          {
              has_expected_status = true;
              expected_backend_status = boost::lexical_cast<int>(arg);
          }
      }
      else if (arg.find("-") == 0)
      {
          //std::cout
          //    << "[WARN] [" << program_name << "] "
          //    << "Unknown commandline switch: "
          //    << "'" << arg << "' "
          //    << "(passing to ROSE CLI)"
          //    << std::endl;
          rose_cmdline.push_back(arg);
      }
      else
      {
          rose_cmdline.push_back(argv[ii]);
      }
  }

  if (!has_expected_status)
  {
      ShowUsage(program_name);
      return 1;
  }

  SgProject* project = frontend(rose_cmdline);
  int backend_status = backend(project);
  std::cout << "backend_status=" << backend_status << std::endl;
  std::cout << "expected_backend_status=" << expected_backend_status << std::endl;
  if (backend_status == expected_backend_status)
  {
      return 0;
  }
  else
  {
      return backend_status;
  }
}

//-----------------------------------------------------------------------------
// method Definitions
//-----------------------------------------------------------------------------
static void
ShowUsage(std::string program_name)
{
  std::cerr
    << "Usage: " << program_name << " [--help] --expected-backend-status [ROSE Commandline]\n"
    << "Options:\n"
    << "  --expected-backend-status=<#>   Specify the exit status of the ROSE Backend\n"
    << "\n"
    << "  -h,--help                       Show this help message\n"
    << std::endl;
}

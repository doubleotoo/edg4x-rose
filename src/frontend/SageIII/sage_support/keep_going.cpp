/**
 * \file    signal_handling.cpp
 * \author  Justin Too <too1@llnl.gov>
 * \date    November 16, 2013
 */

#include "keep_going.h"

namespace ROSE {
namespace KeepGoing {
bool set_signal_handler(SignalHandlerFunction handler)
{
    SignalAction.sa_flags   = 0;
    SignalAction.sa_handler = handler;

    sigemptyset(&SignalAction.sa_mask);

    sigaction(SIGSEGV, &SignalAction, 0);
    sigaction(SIGABRT, &SignalAction, 0);

    return true;
}

namespace Project {
namespace Parsing {
  void SignalHandler(int sig)
  {
      std::cout
          << "[WARN] "
          << "Caught SgProject Parse signal="
          << "'" << sig << "'"
          << std::endl;

      siglongjmp(Project::Parsing::jmp_target, -1);
  }
} // ::ROSE::KeepGoing::Project::Parsing
} // ::ROSE::KeepGoing::Project

namespace File {
namespace Frontend {
  void SignalHandler(int sig)
  {
      std::cout
          << "[WARN] "
          << "Caught SgFile frontend signal="
          << "'" << sig << "'"
          << std::endl;

      siglongjmp(File::Frontend::jmp_target, -1);
  }
} // ::ROSE::KeepGoing::Frontend::Frontend
} // ::ROSE::KeepGoing::Frontend
} // ::ROSE::KeepGoing
} // ::ROSE


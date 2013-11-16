/**
 * \file    signal_handling.cpp
 * \author  Justin Too <too1@llnl.gov>
 * \date    November 16, 2013
 */

#include <iostream>

#include "keep_going.h"

namespace ROSE {
namespace KeepGoing {
bool g_keep_going = false;
struct sigaction SignalAction;

bool set_signal_handler(SignalHandlerFunction handler)
{
    SignalAction.sa_flags   = 0;
    SignalAction.sa_handler = handler;

    sigemptyset(&SignalAction.sa_mask);

    sigaction(SIGSEGV, &SignalAction, 0);
    sigaction(SIGABRT, &SignalAction, 0);

    return true;
}

namespace File {
namespace Frontend {
  sigjmp_buf jmp_target;
  void SignalHandler(int sig)
  {
      std::cout
          << "[WARN] "
          << "Caught signal="
          << "'" << sig << "' "
          << "during SgFile frontend processing"
          << std::endl;

      siglongjmp(File::Frontend::jmp_target, -1);
  }

  namespace SecondaryPass {
    sigjmp_buf jmp_target;
    void SignalHandler(int sig)
    {
        std::cout
            << "[WARN] "
            << "Caught signal="
            << "'" << sig << "' "
            << "during secondary pass over source file"
            << std::endl;

        siglongjmp(File::Frontend::SecondaryPass::jmp_target, -1);
    }
  } // ::ROSE::KeepGoing::File::Frontend::SecondaryPass
} // ::ROSE::KeepGoing::File::Frontend
} // ::ROSE::KeepGoing::File
} // ::ROSE::KeepGoing
} // ::ROSE


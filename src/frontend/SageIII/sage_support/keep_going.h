#ifndef ROSE_KEEPGOING_H
#define ROSE_KEEPGOING_H

/**
 * \file    signal_handling.h
 * \author  Justin Too <too1@llnl.gov>
 * \date    November 16, 2013
 */

#include <setjmp.h>
#include <signal.h>

#include <iostream>

namespace ROSE {
namespace KeepGoing {
//-----------------------------------------------------------------------------
// Global Data
//-----------------------------------------------------------------------------
bool g_keep_going = false;
struct sigaction SignalAction;
typedef void(*SignalHandlerFunction)(int);

//-----------------------------------------------------------------------------
// Public API
//-----------------------------------------------------------------------------
#define KEEP_GOING_CAUGHT_PARSING_SIGNAL                                \
  (                                                                     \
      ROSE::KeepGoing::g_keep_going &&                                  \
      ROSE::KeepGoing::set_signal_handler(                              \
          &ROSE::KeepGoing::Project::Parsing::SignalHandler) &&         \
      sigsetjmp(ROSE::KeepGoing::Project::Parsing::jmp_target, 0) != 0  \
  )
#define KEEP_GOING_CAUGHT_FILE_FRONTEND_SIGNAL                        \
  (                                                                   \
      ROSE::KeepGoing::g_keep_going &&                                \
      ROSE::KeepGoing::set_signal_handler(                            \
          &ROSE::KeepGoing::File::Frontend::SignalHandler) &&         \
      sigsetjmp(ROSE::KeepGoing::File::Frontend::jmp_target, 0) != 0  \
  )

//-----------------------------------------------------------------------------
// Private API
//-----------------------------------------------------------------------------
bool set_signal_handler(SignalHandlerFunction handler);

namespace Project {
namespace Parsing {
  sigjmp_buf jmp_target;

  void SignalHandler(int sig);
} // ::ROSE::KeepGoing::Project::Parsing
} // ::ROSE::KeepGoing::Project

namespace File {
namespace Frontend {
  sigjmp_buf jmp_target;

  void SignalHandler(int sig);
} // ::ROSE::KeepGoing::Frontend::Frontend
} // ::ROSE::KeepGoing::Frontend
} // ::ROSE::KeepGoing
} // ::ROSE
#endif // ROSE_KEEPGOING_H


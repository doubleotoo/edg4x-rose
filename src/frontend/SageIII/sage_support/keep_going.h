#ifndef ROSE_KEEPGOING_H
#define ROSE_KEEPGOING_H

/**
 * \file    signal_handling.h
 * \author  Justin Too <too1@llnl.gov>
 * \date    November 16, 2013
 */

#include <setjmp.h>
#include <signal.h>

namespace ROSE {
namespace KeepGoing {
//-----------------------------------------------------------------------------
// Global Data
//-----------------------------------------------------------------------------
extern bool g_keep_going;
extern struct sigaction SignalAction;
typedef void(*SignalHandlerFunction)(int);

//-----------------------------------------------------------------------------
// Public API
//-----------------------------------------------------------------------------
#define KEEP_GOING_CAUGHT_FILE_FRONTEND_SIGNAL                        \
  (                                                                   \
      ROSE::KeepGoing::g_keep_going &&                                \
      ROSE::KeepGoing::set_signal_handler(                            \
          &ROSE::KeepGoing::File::Frontend::SignalHandler) &&         \
      sigsetjmp(ROSE::KeepGoing::File::Frontend::jmp_target, 0) != 0  \
  )
#define KEEP_GOING_CAUGHT_FILE_FRONTEND_SECONDARY_PASS_SIGNAL         \
  (                                                                   \
      ROSE::KeepGoing::g_keep_going &&                                \
      ROSE::KeepGoing::set_signal_handler(                            \
          &ROSE::KeepGoing::File::Frontend::SecondaryPass::SignalHandler) &&         \
      sigsetjmp(ROSE::KeepGoing::File::Frontend::SecondaryPass::jmp_target, 0) != 0  \
  )

//-----------------------------------------------------------------------------
// Private API
//-----------------------------------------------------------------------------
bool set_signal_handler(SignalHandlerFunction handler);

namespace File {
namespace Frontend {
  extern sigjmp_buf jmp_target;
  void SignalHandler(int sig);

  namespace SecondaryPass {
    extern sigjmp_buf jmp_target;

    void SignalHandler(int sig);
  } // ::ROSE::KeepGoing::File::Frontend::SecondaryPass
} // ::ROSE::KeepGoing::File::Frontend
} // ::ROSE::KeepGoing::File
} // ::ROSE::KeepGoing
} // ::ROSE
#endif // ROSE_KEEPGOING_H


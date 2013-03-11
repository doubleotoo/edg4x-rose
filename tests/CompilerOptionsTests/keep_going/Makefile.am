include $(top_srcdir)/config/Makefile.for.ROSE.includes.and.libs

noinst_bin_PROGRAMS = KeepGoingTestTranslator
noinst_bindir = $(top_builddir)/tests/CompilerOptionsTests/keep_going

TEST_TRANSLATOR = $(top_builddir)/tests/CompilerOptionsTests/keep_going/KeepGoingTestTranslator
INCLUDES = $(ROSE_INCLUDES)
LDADD    = $(ROSE_LIBS)

KeepGoingTestTranslator_SOURCES = KeepGoingTestTranslator.cpp

check-local:
	$(TEST_TRANSLATOR) $(srcdir)/syntax_error_1.cpp --expected-backend-status=257
	@echo "*****************************************************************************************************************"
	@echo "****** ROSE/tests/CompilerOptionTests/testHeaderFileOutput: make check rule complete (terminated normally) ******"
	@echo "*****************************************************************************************************************"

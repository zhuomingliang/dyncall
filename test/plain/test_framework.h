// 2007-10-11

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

// Statement breaking into debugger (for various platforms). @@@add if defined, etc...
#ifdef _WIN32
# ifdef _MSC_VER
#  define DC_TEST_BREAK				__debugbreak
# else
#  include <windows.h>
#  define DC_TEST_BREAK       DebugBreak
# endif
#else
# define DC_TEST_BREAK
#endif

// Test state - evaluates to false inside a test function if a test fails.
#define DC_TEST_STATE				testFramework_state

// Test functions defined by DC_DEFINE_TEST_FUNC_BEGIN and DC_DEFINE_TEST_FUNC_END pairs do come with
// a default parameter used to pass a path to them specifying where to find external data needed to
// run the tests (if desired). NULL by default. It can be queried by using DC_TEST_PATH.
#define DC_TEST_PATH				testFramework_suitePath

// Test a single expression - the expression must evaluate to true in order to succeed.
// #define DC_TEST(exp)				{ TEST_STATE = TEST_STATE && (exp); if(!TEST_STATE) DC_TEST_BREAK(); }

#include <assert.h>

#define DC_TEST(exp)        assert(exp)
// { if (! (exp) ) DC_TEST_BREAK(); }

// Macros used to define a test functions.
#define DC_DEFINE_TEST_FUNC_BEGIN(name)	/*static */int name(/*const char* DC_TEST_PATH=NULL*/) { /*@@@ add logging*/ int TEST_STATE = TRUE;
#define DC_DEFINE_TEST_FUNC_END			/*@@@ add logging*/ return TEST_STATE; }

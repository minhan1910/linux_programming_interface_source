#ifndef ERROR_FUNCTIONS_H
#define ERROR_FUNCTIONS_H

/*
To diagnose errors from system calls and library functions, we use 
errMsg(),
errExit(),
err_exit(), and errExitEN().
*/


/*
The errMsg() function prints a message on standard error. 
Its argument list is the same as for printf(), except that a terminating newline character is automatically
appended to the output string.
The errMsg() function prints the error text corresponding to the current value of errno 
— this consists of the error name, such as EPERM , plus the error description as returned by strerror() 
— followed by the formatted output specified in the argument list.
*/
void errMsg(const char* format, ...);

#ifdef __GNUC__
/* This macro stops 'gcc -Wall' complaining that "control reaches
end of non-void function" if we use the following functions to
terminate main() or some other non-void function. */

#define NORETURN __attribute__ ((__noreturn__))
#else
#define NORETURN
#endif

/*
The errExit() function operates like errMsg(), but also terminates the program,
either by calling exit() or, if the environment variable EF_DUMPCORE is defined with a
nonempty string value, by calling abort() to produce a core dump file for use with
the debugger.
*/
void errExit(const char* format, ...) NORETURN;


/*
The err_exit() function is similar to errExit(), but differs in two respects:
- It doesn’t flush standard output before printing the error message.
- It terminates the process by calling _exit() instead of exit(). This causes the pro-cess to 
terminate without flushing stdio buffers or invoking exit handlers.

For now, we simply note that err_exit() is especially useful if we write a library function
that creates a child process that needs to terminate because of an error.
*/
void err_exit(const char* format, ...) NORETURN;


/*
The errExitEN() function is the same as errExit(), except that instead of printing
the error text corresponding to the current value of errno, it prints the text corre-
sponding to the error number (thus, the EN suffix) given in the argument errnum.
Mainly, we use errExitEN() in programs that employ the POSIX threads API.
Unlike traditional UNIX system calls, which return –1 on error, the POSIX threads
functions diagnose an error by returning an error number (i.e., a positive number
of the type normally placed in errno) as their function result. (The POSIX threads
functions return 0 on success.)
We could diagnose errors from the POSIX threads functions using code such
as the following:
    errno = pthread_create(&thread, NULL, func, &arg);
    if (errno != 0)
        errExit("pthread_create");
However, this approach is inefficient because errno is defined in threaded pro-
grams as a macro that expands into a function call that returns a modifiable lvalue.
Thus, each use of errno results in a function call. The errExitEN() function allows us
to write a more efficient equivalent of the above code:
    int s;
    s = pthread_create(&thread, NULL, func, &arg);
    if (s != 0)
        errExitEN(s, "pthread_create");

*/
void errExitEN(int errnum, const char* format, ...) NORETURN;


/*
The fatal() function is used to diagnose general errors, including errors from
library functions that don’t set errno. Its argument list is the same as for printf(),
except that a terminating newline character is automatically appended to the out-
put string. It prints the formatted output on standard error and then terminates
the program as with errExit().
*/
void fatal(const char* format, ...) NORETURN;

/*
The usageErr() function is used to diagnose errors in command-line argument
usage. It takes an argument list in the style of printf() and prints the string Usage:
followed by the formatted output on standard error, and then terminates the pro-
gram by calling exit(). (Some of the example programs in this book provide their
own extended version of the usageErr() function, under the name usageError().)
*/
void usageErr(const char* format, ...) NORETURN;

/*
The cmdLineErr() function is similar to usageErr(), but is intended for diagnosing
errors in the command-line arguments specified to a program
*/
void cmdLineErr(const char* format, ...) NORETURN;

#endif
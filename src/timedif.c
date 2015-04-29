/*                                                    B Bunk
                                                      rev    12/2009
    cpudif()  returns the cpu-time (in sec) elapsed since the
        previous call (for the very first call, cpudif()=0. )
    clkdif()  returns the wallclock time (in sec) elapsed since the
        previous call (for the very first call, clkdif()=0. )
*/
/* define Fortran's REAL in C */
typedef float REAL;

#define _INCLUDE_POSIX_SOURCE
#include <sys/times.h>
#include <unistd.h>

REAL cpudif()
{
    static int first = 1;
    static double told, tnew;

    REAL ret_val;

    struct tms usage;

    times(&usage);
    tnew = ((double) usage.tms_utime) / sysconf(_SC_CLK_TCK);

    if (first) {
	told = tnew;
	first = 0;
    }
    ret_val = tnew - told;
    told = tnew;
    return ret_val;
} /* cpudif */

REAL cpudif_()
{
    return cpudif();
} /* cpudif_ */

REAL CPUDIF()
{
    return cpudif();
} /* CPUDIF */

REAL CPUDIF_()
{
    return cpudif();
} /* CPUDIF_ */


REAL clkdif()
{
    static int first = 1;
    static double told, tnew;

    REAL ret_val;

    struct tms usage;

    tnew = ((double) times(&usage)) / sysconf(_SC_CLK_TCK);

    if (first) {
	told = tnew;
	first = 0;
    }
    ret_val = tnew - told;
    told = tnew;
    return ret_val;
} /* clkdif */

REAL clkdif_()
{
    return clkdif();
} /* clkdif_ */

REAL CLKDIF()
{
    return clkdif();
} /* CLKDIF */

REAL CLKDIF_()
{
    return clkdif();
} /* CLKDIF_ */

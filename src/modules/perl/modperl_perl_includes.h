/* Copyright 2001-2004 The Apache Software Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MODPERL_PERL_INCLUDES_H
#define MODPERL_PERL_INCLUDES_H

/* header files for Perl */

#ifndef PERL_NO_GET_CONTEXT
#   define PERL_NO_GET_CONTEXT
#endif

#define PERLIO_NOT_STDIO 0

#include "config.h"

/*
 * sizeof(struct PerlInterpreter) changes #ifdef USE_LARGE_FILES
 * apache-2.0 cannot be compiled with lfs because of sendfile.h
 * the PERL_CORE optimization is a no-no in this case
 */
#if defined(USE_ITHREADS) && !defined(USE_LARGE_FILES)
#   define PERL_CORE
#endif

#ifdef MP_SOURCE_SCAN
/* XXX: C::Scan does not properly remove __attribute__ within
 * function prototypes; so we just rip them all out via cpp
 */
#   undef __attribute__
#   define __attribute__(arg)

#   ifdef MP_SOURCE_SCAN_NEED_ITHREADS
/* just need to have pTHX_ defined for proper prototypes */
#      define USE_ITHREADS
#   endif
#endif

#ifdef WIN32
#   define uid_t perl_uid_t
#   define gid_t perl_gid_t
#   ifdef exit
#      define perl_exit exit
#      undef exit
#   endif
#endif

/* needed starting from 5.8.2 to access the PERL_HASH_INTERNAL macro
 * in hv.h. we use it in modperl_util.c */
#define PERL_HASH_INTERNAL_ACCESS

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#if defined(WIN32) && defined(USE_LARGE_FILES)
#   ifdef malloc
#      define perl_malloc malloc
#      undef malloc
#   endif
#   ifdef free
#      define perl_free free
#      undef free
#   endif
#endif

#if (PERL_REVISION == 5) && (PERL_VERSION == 6)
#   define MP_PERL_5_6_x
#endif

#if defined(MP_PERL_5_6_x) && (PERL_SUBVERSION == 0)
#   define MP_PERL_5_6_0
#endif

#if defined(MP_PERL_5_6_x) && (PERL_SUBVERSION == 1)
#   define MP_PERL_5_6_1
#endif

#include "modperl_perl_unembed.h"

/* avoiding -Wall warning */

#undef dNOOP
#define dNOOP extern int __attribute__ ((unused)) Perl___notused

#ifndef G_METHOD
#   define G_METHOD 64
#endif

#ifndef PERL_MAGIC_tied
#   define PERL_MAGIC_tied 'P'
#endif

#ifndef PERL_MAGIC_tiedscalar
#   define PERL_MAGIC_tiedscalar 'q'
#endif

#ifndef PERL_MAGIC_ext
#   define PERL_MAGIC_ext '~'
#endif

#if defined(__APPLE__) && !defined(PERL_CORE) && !defined(environ)
#   include <crt_externs.h>
#   define environ (*_NSGetEnviron())
#endif

/* sv_copypv was added in perl 5.7.3 */
#ifndef sv_copypv
#  define sv_copypv(dsv, ssv)     \
    STMT_START {                  \
        STRLEN len;               \
        char *s;                  \
        s = SvPV(ssv, len);       \
        sv_setpvn(dsv, s, len);   \
        if (SvUTF8(ssv)) {        \
            SvUTF8_on(dsv);       \
        }                         \
        else {                    \
            SvUTF8_off(dsv);      \
        }                         \
    } STMT_END
#endif

#endif /* MODPERL_PERL_INCLUDES_H */

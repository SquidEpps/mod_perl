#include "mod_perl.h"
#include "modperl_const.h"

typedef SV *(*constants_lookup)(pTHX_ const char *);
typedef const char ** (*constants_group_lookup)(const char *);

static SV *new_constsub(pTHX_ constants_lookup lookup,
                        HV *caller_stash, HV *stash,
                        const char *name)
{
    int name_len = strlen(name);
    GV **gvp = (GV **)hv_fetch(stash, name, name_len, TRUE);
    SV *val;

    /* dont redefine */
    if (!isGV(*gvp) || !GvCV(*gvp)) {
        val = (*lookup)(aTHX_ name);

#if 0
        fprintf(stderr, "newCONSTSUB(%s, %s, %d)\n",
                HvNAME(stash), name, val);
#endif

        newCONSTSUB(stash, (char *)name, val);
#ifdef GvSHARED
        GvSHARED_on(*gvp);
#endif
    }
    
    /* export into callers namespace */
    if (caller_stash) {
        GV *alias = *(GV **)hv_fetch(caller_stash,
                                     (char *)name, name_len, TRUE);

        if (!isGV(alias)) {
            gv_init(alias, caller_stash, name, name_len, TRUE);
        }

        GvCV(alias) = GvCV(*gvp);
    }

    return val;
}

int modperl_const_compile(pTHX_ const char *classname,
                          const char *arg,
                          const char *name)
{
    HV *stash = gv_stashpv(classname, TRUE);
    HV *caller_stash = Nullhv;
    constants_lookup lookup;
    constants_group_lookup group_lookup;

    if (strnEQ(classname, "APR", 3)) {
        lookup       = modperl_constants_lookup_apr;
        group_lookup = modperl_constants_group_lookup_apr;
    }
    else {
        lookup       = modperl_constants_lookup_apache;
        group_lookup = modperl_constants_group_lookup_apache;
    }

    if (*arg != '-') {
        /* only export into callers namespace without -compile arg */
        caller_stash = gv_stashpv(arg, TRUE);
    }

    if (*name == ':') {
        int i;
        const char **group;

        name++;

        group = (*group_lookup)(name);

        for (i=0; group[i]; i++) {
            new_constsub(aTHX_ lookup, caller_stash, stash, group[i]);
        }
    }
    else {
        if (*name == '&') {
            name++;
        }
        new_constsub(aTHX_ lookup, caller_stash, stash, name);
    }

    return 1;
}

XS(XS_modperl_const_compile)
{
    I32 i;
    STRLEN n_a;
    char *stashname = HvNAME(GvSTASH(CvGV(cv)));
    const char *classname, *arg;
    dXSARGS;

    if (items < 2) {
        Perl_croak(aTHX_ "Usage: %s->compile(...)", stashname);
    }

    classname = *(stashname + 1) == 'P' ? "APR" : "Apache";
    arg = SvPV(ST(1),n_a);

    for (i=2; i<items; i++) {
        (void)modperl_const_compile(aTHX_ classname, arg, SvPV(ST(i), n_a));
    }

    XSRETURN_EMPTY;
}
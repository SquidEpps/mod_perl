use strict;
use warnings FATAL => 'all';

use Apache::Test;
use Apache::TestUtil;
use Apache::TestRequest;

use File::Spec::Functions qw(catfile catdir);

my $vars = Apache::Test::config->{vars};
my $dir  = catdir $vars->{documentroot}, "hooks";
my $file = catfile $dir, "cleanup";

plan tests => 2;

{
    # this registers and performs cleanups, but we test whether the
    # cleanup was run only in the next sub-test
    my $location = "/TestHooks::cleanup";
    my $expected = 'ok';
    my $received = GET_BODY $location;
    ok t_cmp($expected, $received, "register req cleanup");
}

{
    # this sub-tests checks that the cleanup stage was run successfully

    # since Apache destroys the request rec after the logging has been
    # finished, we have to give it some time  to get there
    # and fill in the file. (wait 0.25 .. 5 sec)
    my $t = 0;
    select undef, undef, undef, 0.25
        until -e $file && -s _ == 10 || $t++ == 20;

    unless (-e $file) {
        t_debug("can't find $file");
        ok 0;
    }
    else {
        open my $fh, $file or die "Can't open $file: $!";
        my $received = <$fh> || '';
        close $fh;
        my $expected = "cleanup ok";
        ok t_cmp($expected, $received, "verify req cleanup execution");

        # XXX: while Apache::TestUtil fails to cleanup by itself
        unlink $file;
    }

}



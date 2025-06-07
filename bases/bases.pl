#! /usr/bin/perl -w
# Print a digit in any of a number of bases.
# - only takes decimal input
# - binary not tested

my $base = "default";
my $n = shift;

if ($base eq "b") {
    $n = to_string_binary($n);
    printf $n, "\n";
} elsif ($base eq "o") {
    printf "0%o\n", $n;
} elsif ($base eq "d") {
    printf "%d\n", $n;
} elsif ($base eq "h") {
    printf "0x%X\n", $n;
} elsif ($base eq "a") {
    printf "%b 0%o %d 0x%X\n", $n, $n, $n, $n
} else {
    # default is Octal, Decimal, Hex
    printf "0%o %d 0x%X\n", $n, $n, $n;
} 

exit 0;

sub to_string_binary {
    my $n = shift;
    my $c = 8;
    my $s = "";

    if ($n > 0xFF)      { $c += 8; }
    if ($n > 0xFFFF)    { $c += 8; }
    if ($n > 0xFFFFFF)  { $c += 8; }

    for ($i = $c; $i > 0; $i--) {
        if ($n & (1 << $i)) {
            $s .= "1";
        } else {
            $s .= "0";
        }
    }

    return $s;
}

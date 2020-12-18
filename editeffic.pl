#!/usr/bin/perl  

$threshold = $ARGV[0];

foreach $efficfile ( <effic/*> )
{
  open(FH,'>',$efficfile) or die $!;

  print FH "{";

  for ( $i = 1; $i <= 200; $i = $i + 1 )
  {
    if ($i < 2 * $threshold){
      print FH "0.0,";
    }
    elsif ($i < 200){
      print FH "1.0,";
    }
    else {
      print FH "1.0}";
    }
  }
}
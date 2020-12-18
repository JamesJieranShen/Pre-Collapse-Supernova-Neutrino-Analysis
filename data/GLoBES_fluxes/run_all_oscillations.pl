#!/usr/bin/perl  
# Run jobs to create grid of smeared spectra from pinched flux files
# This version sums different channels
use File::Copy;
#use strict;
#use warnings;

$influxdir = $ARGV[0];

if ($influxdir eq "") {
    print "Usage: ./run_all_oscillations.pl influxdir \n"; 
    exit();
}

#delete existing files
foreach $todelete (`ls $influxdir/*normal*`)
{
  print "deleting ".$todelete."\n";
  #unlink($todelete) or die "Can't delete ".$todelete;
  system "rm $todelete";
}
foreach $todelete (`ls $influxdir/*inverted*`)
{
  system "rm $todelete";
}

# Overall loop over fluxes

foreach $fluxfile (`ls $influxdir`)
{
    #print $fluxfile;
    chop($fluxfile);

    

    $fluxfile =~ s/\.dat//;

    $theta12 = 0.588;
    $length = 0;

    $command_normal = "./oscillate_flux $influxdir/$fluxfile 1 $theta12 $length";
    #print $command_normal,"\n";
    system $command_normal;


    $command_inverted = "./oscillate_flux $influxdir/$fluxfile -1 $theta12 $length";
    #print $command_inverted,"\n";
    system $command_inverted
  }

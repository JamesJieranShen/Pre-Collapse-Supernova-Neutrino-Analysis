# README

This README provides basic information to follow my research project on presupernova neutrinos at Duke University in 2017.

## IMPORTANT NOTE!!

- make sure to change the path to SNOwGLoBES in 'analysis.cpp' according to your installation directory. Copy the 'editeffic.pl', and the three 'run_pinched_allflav_*.pl' scripts in the snowglobes directory. The Kato fluxes also need to be copied to the Snowglobes directories.
- This project uses data from the old DUNE detector, whose configuration has been removed from the latest version of SNOWGLOBES. Make sure you are using configurations that are compatible with this detector.

Make sure to read both before starting to work on this project:
kato2017.pdf - The neutrino emisson data used in my analysis is the topic of this paper
presentation.pdf - a summary of the major parts of my analysis

folders:

data - data to be processed by the programs

src - source code folder, containing c++ and ROOT scripts

include - header folder, containing c++ headers

output - output created: histograms, ROOT files, SNOwGLoBES output


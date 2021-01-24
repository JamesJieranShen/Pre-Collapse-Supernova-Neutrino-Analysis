# README

This README provides basic information to follow my research project on presupernova neutrinos at Duke University in 2017.

## IMPORTANT NOTE!!

- make sure to change the path to SNOwGLoBES in 'analysis.cpp' according to your installation directory. Copy the 'editeffic.pl', and the three 'run_pinched_allflav_*.pl' scripts in the snowglobes directory.
- Originally (2017), the project used configurations of the old DUNE/JUNO directories. To replicate the graphs in Mark's original presentation, revert back to an older version of snowglobes, and run via `src/analysis_legacy.sh` after specifying the path to the old snowglobes directory. The commit where this occurs is on Oct 10, 2018; Hash `48b34b9971cae0f324a2e1e694fc7f5610c8f0c6`. All diff from the current version of SNOWGLOBES is listed in
  `snowglobes_diff.txt`

Make sure to read both before starting to work on this project:
kato2017.pdf - The neutrino emisson data used in my analysis is the topic of this paper
presentation.pdf - a summary of the major parts of my analysis

folders:

data - data to be processed by the programs

src - source code folder, containing c++ and ROOT scripts

include - header folder, containing c++ headers

output - output created: histograms, ROOT files, SNOwGLoBES output


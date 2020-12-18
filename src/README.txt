There are two parts of source code files in this folder. The .cpp files and the .C files.

.cpp :

The .cpp files contribute to the creation of ROOT files, which contain the histograms that should be plotted.

The main program is 'analysis.cpp', every other .cpp file is called according to 'analysis.cpp'.

The 'makeHistogram.cpp' is an older version I used for the analysis with outdated data.

.C :

The .C files' job is to create decent looking plots from the ROOT files created by the .cpp files. They are designed to be executed in ROOT by '.x filename.C', and may not be compilable.

To create the histograms with backgrounds use '.x drawBackgrounds.C'

To create the histograms for pre-SN events only use '.x drawHistograms.C'
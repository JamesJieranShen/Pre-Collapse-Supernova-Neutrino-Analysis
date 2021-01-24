./analysis.sh
cd src
./drawEverything.sh
cd ../
make backup
mv histograms_backup histograms_current
./analysis_legacy.sh
cd src
./drawEverything.sh
cd ../
make backup
mv histograms_backup histograms_legacy

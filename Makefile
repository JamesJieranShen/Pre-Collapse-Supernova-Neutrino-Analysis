all:
	$(MAKE) -C src/ analysis

.PHONY:	clean clear
clean:
	(cd src/; $(MAKE) clean)
	(cd output/; $(MAKE) clean)

clear:
	(cd output/; $(MAKE) clean)

backup: 
	rm -rf histograms_backup/*
	mkdir -p histograms_backup
	cp -r output/histograms/* histograms_backup/

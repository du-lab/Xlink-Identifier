# Xlink-Identifier

Xlink-Identifier is a C++ program for identifying chemical crosslinks from tandem mass spectra.

This program requires input tandem mass spectra in dta format. To create spectra in dta format, the following procedure could be followed:

1. Use "msConvert" to extract tandem mass spectra from your raw vendor format data files. The resulting file contains all of the MS/MS spectra.
2. Use "MascotGenericFileToDTA_Installer" (in folder other_programs_needed) to convert the MS/MS spectra in .mgf format to .dta format. All of the MS/MS spectra in .dta format are stored in a text file.
3. Use "ConcatenatedTextFileSplitter_Installer" (in folder other_programs_needed) to split the concatenated text file into individual dta files.

Note: 
1. msConvert can be downloaded at http://proteowizard.sourceforge.net/.
2. MascotGenericFileToDTA_Installer and ConcatenatedTextFileSplitter_Installer were originally downloaded from https://omics.pnl.gov/software. ConcatenatedTextFileSplitter_Installer can still be downloaded from this website.

This program works on Network identifiers. In the input file, each line contains three values:
1) Source Network identifier
2) Destination Network Identifier
3) Bandwidth available (in Mb/s) from source to destination

The identifiers can appear multiple times as both sources and destinations and can contain only letters and are not case sensitive.
This program accepts two command-line arguments: input filename and output filename.

This program outputs:
1) a list of unique identifiers all in uppercase and
2) if an identifier appears both in source and destination, it outputs the ratio of the sum of bandwidth "from" that identifier to the sum of bandwidth "to" that identifier.
3) 

A simple test vector file is added on this folder. More explanation of the code can be found in the actual code file itself. 

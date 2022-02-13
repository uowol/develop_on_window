filename cham "C:\data2021\data\championsData.json" encoding="utf-8";

data champions;
	infile cham;
	input @1 char1 $4000.;
run;
proc print; run;

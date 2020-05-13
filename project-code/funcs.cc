#include <stdio.h>
#include <unistd.h> //for the getopt function
#include <stdlib.h> //for atoi
#include <iostream>
using namespace std;

bool parseParams(int argc, char *argv[ ], int& cache_capacity,
				int& cache_blocksize, int& cache_associativity, bool& split, bool& writehit, bool&writemiss)
{
  //needed for the parsing of command line options
  int c;
  bool c_flag, b_flag, a_flag;
  bool errflg = false;

  c_flag = b_flag = a_flag = errflg = false;

  //the following variables are used by getopt and
  //are defined elsewhere so we just make them
  //extern here
  extern char *optarg;
  extern int optind, optopt;

  //start the parsing of the command line options.
  //end is indicated by getopt returning -1
  //each option has a case statement
  //the corresponding flags are set if the option exists on
  //the command line
  //the : int he getopt indicates that the option preceeding the
  //: requires a argument to be specified
  while ((c = getopt(argc, argv, "c:b:a:w:s")) != -1) {
	switch (c) {
	  case 's':
		split=true;
		break;
	  case 'c':
		cache_capacity = atoi(optarg);
		c_flag = true;
		break;
	  case 'b':
		cache_blocksize = atoi(optarg);
		b_flag = true;
		break;
	  case 'a':
		cache_associativity = atoi(optarg);
		a_flag = true;
		break;
	  case 'w':
		if(optarg){
			if(optarg[0]=='b') writehit=0;
			else if (optarg[0]=='t') writehit=1;
			else if (optarg[0]=='a') writemiss=0;
			else if (optarg[0]=='n') writemiss=1;
			else{
				cout<<"Invalid write option\n";
				errflg=true;
			}
		}
		break;
	  case ':':       /* -c without operand */
		fprintf(stderr,
			"Option -%c requires an operand\n", optopt);
		errflg++;
		break;
	  case '?':
		fprintf(stderr, "Unrecognised option: -%c\n", optopt);
		errflg=true;
	}
  }

  //check if we have all the options and have no illegal options
  if(errflg || !c_flag || !b_flag || !a_flag) {
	fprintf(stderr, "usage: %s -c<capacity> -b<blocksize> -a<associativity>\n", argv[0]);
	return false;
  }

  return true;

}


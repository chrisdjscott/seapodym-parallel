#include <iostream>
#include <cstring>
#include <cstdlib>
using std::cout;

void help(char* argv0);
int OptionToCode(char* Option,int &sub_option);
int seapodym_coupled(const char* parfile, const int cmp_regime, const int sub_option, const bool reset_buffers);
int seapodym_phases(const char* parfile);
bool read_memory_options(int argc, char** argv, const bool grad_calc);

int main(int argc, char** argv) {

	if (argc==1) help(argv[0]);
	int cmp_regime = -1;
	int sub_option = 0;
	bool reset_buffers = false;
 	
	int k=1;
	char *cmdLineOption = argv[k];
	cmp_regime = OptionToCode(cmdLineOption, sub_option);
	if (cmp_regime==-1) k=0;
	if (cmp_regime==-3) help(argv[0]);
	if (argc < k+2) {
		cout << "Parfile can't be omited... \n"; 
		help(argv[0]);
	}
	if ((cmp_regime==-1 && argc>2) || (cmp_regime>=0 && argc>3)){
		bool grad_calc = false;
		if (cmp_regime == -1 || cmp_regime == 2)
			grad_calc = true;
		reset_buffers = read_memory_options(argc, argv, grad_calc);	
	}

	if (cmp_regime!=-11)
		return seapodym_coupled(argv[argc-1],cmp_regime,sub_option,reset_buffers);
	else
		return seapodym_phases(argv[argc-1]);
}

int OptionToCode(char* op, int &sub_option) {

	const int N = 20;
	const char *cmdop[N] = {"-ph","-s","-p","-H","-sa","-t","-h","-v","--phases","--simulation","--likelihood-projection","--hessian","--sensitivity-analysis","--taylor-test","--help","--version","-sa=0","-sa=1","-sa=2","-sa=3"};
	int cmpCode[N] = {-11,0,1,2,3,4,-3,-2,-11,0,1,2,3,4,-3,-2,3,3,3,3};
	for (int i=0; i<N; i++)
		if (strcmp(op,cmdop[i])==0){
			if (i>=N-4) sub_option = 1;
			if (i==N-2) sub_option = 2;
			if (i==N-1) sub_option = 3;
			if (cmpCode[i]==-2) {
				cout << "SEAPODYM with parameter estimation 4.0 \n";
				cout << "Copyright (C) 2022, SPC, CLS, University of Hawaii.\n";
				exit(0);
			}
			return cmpCode[i];
		}
	return -1;//by default - optimization
}

void help(char* argv0) {

	cout << "Usage:" << argv0 << " [option] parfile \n";
	cout << "      IMPORTANT!!! If [option] is omitted, then application will start optimization run! \n"; 
	cout << "Options: \n";
	cout << "  -h, --help \t\t\t Print this message and exit.\n";
	cout << "  -H, --hessian \t\t Compute Hessian matrix.\n";
	cout << "  -p, --projection \t\t Compute 2D-projection of the likelihood on a grid specified in parfile.\n";
	cout << "  -s, --simulation \t\t Run simulation without optimization.\n";
	cout << "  -sa[=FLAG]  \t\t\t Perform sensitivity analysis. By default[=0] local sensitivity with model predictions only.\n";
	cout << "   --sensitivity-analysis[=FLAG] If FLAG=1 the sensitivity function takes both predictions and observations.\n";
	cout << "   --sensitivity-analysis[=FLAG] If FLAG=2 ONE-AT-A-TIME sensitivity analysis.\n";
	cout << "   --sensitivity-analysis[=FLAG] If FLAG=3 ALL-AT-A-TIME sensitivity analysis.\n";
	cout << "  -t, --taylor-test   \t\t Perform Taylor derivative test with central differencing.\n";
	cout << "  -v, --version \t\t Print version number and exit.\n";
	exit(0);
}


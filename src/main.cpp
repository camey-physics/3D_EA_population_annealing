#include <iostream>
#include <vector>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <math.h>
#include <omp.h>
#include <memory>
/*
#include "params.h"
#include "functions.h"
#include "ising_class.h"
*/
#include "pa_class.h"

using namespace std;

int main(int argc, char *argv[]) {
	gsl_rng *r;
	int seed;
	int neighbor_table[LENGTH_3][6];
	double bond_table[LENGTH_3][6];

	omp_set_num_threads(NUM_THREADS);
	try {
		if (argc !=2)
			throw invalid_argument("Invalid RNG seed.");
		seed = stoi(argv[1]);
		if (seed < 1e4)
			throw invalid_argument("RNG seed too small.");
	}
	catch (const char* e) {
		cerr << e << endl;
		return -1;
	}

	printf("%d\n", seed);

	try {
		initialize_rng(&r, seed);
		initialize_NT(neighbor_table);
		read_BT(bond_table);
	}
	catch (const char* e) {
		cerr << e << endl;
		return -1;
	}
	try {
		int pop_size = 1000, num_gs_families;
		spin_conf gs;
		double gs_e, rho_t;
		FILE *fp = fopen("gs.dat", "w");
		PA_simulation find_gs(pop_size, r, neighbor_table, bond_table);
		find_gs.run();
		gs_e = find_gs.get_gs_e();
		gs = find_gs.get_gs();
		num_gs_families = find_gs.num_gs_families();
		rho_t = find_gs.get_rho_t();
		fprintf(fp, "R = %d, seed = %d, GS energy = %15.15f, rho_t = %5.5f, # GS families = %d\n", pop_size, seed, gs_e, rho_t, num_gs_families);
		gs.print();
		fclose(fp);
	}

	catch (const char* e) {
		cerr << e << endl;
		return -1;
	}

	return 0;
}

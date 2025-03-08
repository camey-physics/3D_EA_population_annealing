#include <iostream>
#include <vector>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <math.h>
#include <omp.h>
#include <memory>
#include "params.h"

using namespace std;

class spin_conf {
	private:
		char spin[LENGTH_3];
		double energy;
		int family;
	public:
		void init(gsl_rng *r, int family, int neighbor_table[LENGTH_3][6], double bond_table[LENGTH_3][6]);
		void calc_energy(int neighbor_table[LENGTH_3][6], double bond_table[LENGTH_3][6]);
		double high_T_Met_sweep(double beta, gsl_rng *r, int neighbor_table[LENGTH_3][6], double bond_table[LENGTH_3][6]);
		double Met_sweep(double beta, gsl_rng *r, int neighbor_table[LENGTH_3][6], double bond_table[LENGTH_3][6]);
		int get_family(void);
		double get_energy(void);
		void print(void);
};

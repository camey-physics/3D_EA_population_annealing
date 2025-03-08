#include "ising_class.h"


void spin_conf::calc_energy(int neighbor_table[LENGTH_3][6], double bond_table[LENGTH_3][6]) {
	energy = 0.0;
	for (int s = 0; s < LENGTH_3; s++) {
		double temp_sum = 0;
		for (int n = 0; n < 6; n++) {
			int neighbor = neighbor_table[s][n];
			temp_sum += spin[neighbor] *bond_table[s][n];
		}
		energy += -temp_sum *spin[s];
	}
	energy /= 2.0;
}

void spin_conf::print(void) {
	FILE *fp = fopen("conf.dat", "w");
	for (int i = 0; i < LENGTH_3; i++)
		fprintf(fp, "%d\n", (int) spin[i]);
}
void spin_conf::init(gsl_rng *r, int family, int neighbor_table[LENGTH_3][6], double bond_table[LENGTH_3][6]) {
	for (int s = 0; s < LENGTH_3; s++) {
		if (gsl_rng_uniform(r) < 0.5)
			spin[s] = -1;
		else
			spin[s] = 1;
	}
	spin_conf::family = family;
	calc_energy(neighbor_table, bond_table);
}

double spin_conf::high_T_Met_sweep(double beta, gsl_rng *r, int neighbor_table[LENGTH_3][6], double bond_table[LENGTH_3][6]) {
	double acc_ratio = 0.0;
	for (int i = 0; i < LENGTH_3; i++) {
		int s = gsl_rng_uniform_int(r, LENGTH_3);
		double temp_sum = 0;
		for (int n = 0; n < 6; n++) {
			int neighbor = neighbor_table[s][n];
			temp_sum += spin[neighbor] *bond_table[s][n];
		}
		double weight = exp(-2 *beta *spin[s] *temp_sum);
		if (weight > 1 || gsl_rng_uniform(r) < weight) {
			spin[s] = -spin[s];
			acc_ratio++;
		}
	}
	acc_ratio /= (double) LENGTH_3;
	return acc_ratio;
}

double spin_conf::Met_sweep(double beta, gsl_rng *r, int neighbor_table[LENGTH_3][6], double bond_table[LENGTH_3][6]) {
	double acc_ratio = 0.0;
	for (int i = 0; i < LENGTH_3; i++) {
		int s = i;
		double temp_sum = 0;
		for (int n = 0; n < 6; n++) {
			int neighbor = neighbor_table[s][n];
			temp_sum += spin[neighbor] *bond_table[s][n];
		}
		double weight = exp(-2 *beta *spin[s] *temp_sum);
		if (weight > 1 || gsl_rng_uniform(r) < weight) {
			spin[s] = -spin[s];
			acc_ratio++;
		}
	}
	acc_ratio /= (double) LENGTH_3;
	return acc_ratio;
}

int spin_conf::get_family(void) {
	return family;
}

double spin_conf::get_energy(void) {
	return energy;
}

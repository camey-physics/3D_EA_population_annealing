# 3D_EA_population_annealing
This is code from my PhD work on studying and understanding glassy systems. This code uses population annealing Monte Carlo to find the ground states and ground state energies of 3D Edwards-Anderson glass samples, using refinements that I developed over the course of my PhD.

The bool_pa directory contains a version of this code that uses bit arrays instead of character arrays to store the spin variables. This is computationally a little slower, but much more efficient in terms of RAM usage and should be considered when dealing with extremely large population sizes.

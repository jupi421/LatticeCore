### add library to path
import sys
sys.path.append("../build")

import _lattice_core as lc

import numpy as np
from ase import Atoms, cell
from ase.io import write

### define lattice parameters and create lattice object
a = 3.905
c = 1.12*3.905
rotation_amplitude = 3 

N_row = 4
N_col = 4
N_layers = 4

lattice = lc.STOLattice( a, c, rotation_amplitude, N_row, N_col, N_layers )

### calculate atom positions
lattice.populate()

### get lattice as a numpy array
np_lattice = lattice.lattice

### extract positions for each species
Sr = np_lattice[:,:,:,0,:].reshape((-1, 3))
Ti = np_lattice[:,:,:,1,:].reshape((-1, 3))
O = np_lattice[:,:,:,2:,:].reshape((-1, 3))

### create labels for each atom and create lattice in ase
Sr_symbols = ['Sr']*Sr.shape[0]
Ti_symbols = ['Ti']*Ti.shape[0]
O_symbols = ['O']*O.shape[0]

ase_lattice = Atoms(symbols=Sr_symbols+Ti_symbols+O_symbols, positions=np.concatenate((Sr, Ti, O)))

### calculate lattice vectors for the supercell
min_ = np.min(ase_lattice.positions, axis=0)
max_ = np.max(ase_lattice.positions, axis=0)
lattice_diagonal = max_ - min_
lattice_diagonal[0] += a/2
lattice_diagonal[1] += a/2
lattice_diagonal[2] += c/2
supercell_lattice_matrix = np.diag(lattice_diagonal)

### create supercell
ase_lattice.cell = supercell_lattice_matrix

### write lattice to POSCAR 
ase_lattice.write('POSCAR.vasp', format='vasp', direct=True, sort=False)

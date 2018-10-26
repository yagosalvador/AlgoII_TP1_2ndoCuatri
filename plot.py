#!/usr/bin/env python

import numpy as np
import scipy
from matplotlib import pyplot as plt
from scipy import optimize

n, t_arbol = np.loadtxt('datosArbol.txt', unpack=True)
n, t_orig = np.loadtxt('datosOrig.txt', unpack=True)

def n_(x, c):
    return c * x

def logn(x, c):
    return c * np.log2(x)

arbol_fit, cov = optimize.curve_fit(logn, n, t_arbol)
orig_fit, cov = optimize.curve_fit(n_, n, t_orig)
t_arbol_fit = logn(n, *arbol_fit)
t_orig_fit = n_(n, *orig_fit)

plt.loglog(n, t_arbol, 'o', label='Arbol',
           basex=2, basey=2)
plt.loglog(n, t_orig, 'x', label='Original',
           basex=2, basey=2)
plt.loglog(n, t_arbol_fit,
           basex=2, basey=2)
plt.loglog(n, t_orig_fit,
           basex=2, basey=2)
plt.xlabel('tamaño del vector')
plt.ylabel('tiempo de ejecución (segundos)')
print(arbol_fit, orig_fit)
plt.legend()
plt.savefig('tiempos.png')
plt.show()

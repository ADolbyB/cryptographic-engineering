import math
from os import urandom
from hashlib import sha3_256, sha3_512, shake_256

from sage.rings.polynomial.polynomial_quotient_ring import PolynomialQuotientRing as polynomial
from sage.matrix.constructor import matrix
from sage.misc.prandom import randrange
from sage.rings.finite_rings.finite_field_constructor import FiniteField 
from sage.rings.polynomial.polynomial_ring_constructor import PolynomialRing
from sage.rings.polynomial.polynomial_quotient_ring import PolynomialQuotientRing as polynomial
from sage.rings.integer import Integer

# Kyber Parameters
q = 3329
q_bytes = 16
k = 2
n = 256


rQ = PolynomialRing(FiniteField(q, 'x'), 'x', sparse=True)
x = rQ.gen()
f = x**n + 1
RQ = rQ.quotient(f)

DEBUG = True

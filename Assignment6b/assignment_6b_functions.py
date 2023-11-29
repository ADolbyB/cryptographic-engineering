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

from assignment_6b_parameters import k, n, q, RQ

def RandomList(length, cbd=False):
    out = [randrange(q) for i in range(length)]
    if cbd:
        out = FauxCbd(out)
    return out

def FauxCbd(r: list):
    out = []
    for i in r:
        out.append((i % 5) - 2) # Restrict to -2 <= n <= 2
    return out

def RandPolyUniform(length):
    return RQ(RandomList(length))

def RandPolyCbd(length) -> polynomial:
    return RQ(RandomList(length, cbd=True))

def RandListCbd(length) -> list:
    return RandomList(length, cbd=True)

def BytesNeed4Bits(bits: int) -> int:
    return ((bits+7) & (-8))//8

def RandInt(bits: int) -> int:
    m = Integer(int.from_bytes(urandom(BytesNeed4Bits(bits)), 'big'))
    m &= 2**n-1
    return m

def Poly2Bytes(poly: polynomial) -> bytes:
    out = b''
    p = poly.coefficients()[0].list()
    for c in p:
        c = int(c)
        cb = c.to_bytes(q_bytes, 'big')
        out += cb
    return out

def Bytes2ListBit(b: bytes) -> list:
    out = []
    for byte in b:
        for i in range(0,8):
            bit = (byte >> i) & 1
            out.append(bit)
    return out

def Compress(poly: polynomial):
    q2 = math.ceil(q/2)
    return poly * q2

def Decompress(poly: polynomial) -> int:
    return [(1 if 3*(q/4) > Integer(i) > q/4 else 0) for i in poly]

def dbg(label: str, *args: str):
    if DEBUG:
        s = f'{label}:\n'
        for arg in args:
            s += f'{arg}\n'
        if len(args) == 0:
            s = s[:-2]
        print(s)

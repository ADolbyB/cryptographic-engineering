from sage.rings.polynomial.polynomial_quotient_ring import PolynomialQuotientRing as polynomial
from sage.matrix.constructor import matrix
from sage.misc.prandom import randrange
from sage.rings.finite_rings.finite_field_constructor import FiniteField 
from sage.rings.polynomial.polynomial_ring_constructor import PolynomialRing
from sage.rings.polynomial.polynomial_quotient_ring import PolynomialQuotientRing as polynomial
from sage.rings.integer import Integer


from assignment_6b_parameters import k, n, q, RQ

NTTMUL = 0

#NTT PARAMETERS FOR KYBER
mont_r         = 2285  # 2^16 % q
mont_r2        = 1353  # 2^32 % q
mont_r_inv     = 169   # (1 / 2^16) % q
mont_mask      = 65535 # 2^16 - 1,
q_inv          = 3327  # -1 / 3329 ^ 2^16,
root_of_unity  = 17
f              = 1441  # 2^32 / 128 % q
# zetas      = [(mont_r * pow(root_of_unity,  br(i,7), q)) % q for i in range(128)],
zetas          = [2285, 2571, 2970, 1812, 1493, 1422, 287, 202, 3158, 622, 1577, 182, 962, 2127, 1855, 1468, 
                  573, 2004, 264, 383, 2500, 1458, 1727, 3199, 2648, 1017, 732, 608, 1787, 411, 3124, 1758, 
                  1223, 652, 2777, 1015, 2036, 1491, 3047, 1785, 516, 3321, 3009, 2663, 1711, 2167, 126, 1469, 
                  2476, 3239, 3058, 830, 107, 1908, 3082, 2378, 2931, 961, 1821, 2604, 448, 2264, 677, 2054, 
                  2226, 430, 555, 843, 2078, 871, 1550, 105, 422, 587, 177, 3094, 3038, 2869, 1574, 1653, 3083, 
                  778, 1159, 3182, 2552, 1483, 2727, 1119, 1739, 644, 2457, 349, 418, 329, 3173, 3254, 817, 
                  1097, 603, 610, 1322, 2044, 1864, 384, 2114, 3193, 1218, 1994, 2455, 220, 2142, 1670, 2144, 
                  1799, 2051, 794, 1819, 2475, 2459, 478, 3221, 3021, 996, 991, 958, 1869, 1522, 1628]
# zetas      = [(pow(root_of_unity,  br(i,7), q)) % q for i in range(128)]

def montgomery_reduce(a):
    """
    This is not proper mont. reduction.
    But this is faster than the normal impl
    because python is weird.
    
    Proper impl is commented out at the bot.
    of the file...
    
    a -> R^(-1) a mod q
    """
    return a * mont_r_inv % q

def mont_mul(a, b):
    """
    Multiplication then Montgomery reduction
    
    Ra * Rb -> Rab
    """
    c = a * b
    return montgomery_reduce(c)

def ntt_base_multiplication(a0, a1, b0, b1, zeta):
    global NTTMUL
    r0  = mont_mul(a1, b1)
    r0  = mont_mul(r0, zeta)
    r0 += mont_mul(a0, b0)
    r1  = mont_mul(a0, b1)
    r1 += mont_mul(a1, b0)
    NTTMUL += 5
    return r0, r1
    
def ntt_coefficient_multiplication(f_coeffs, g_coeffs):
    new_coeffs = []
    for i in range(64):
        r0, r1 = ntt_base_multiplication(
                            f_coeffs[4*i+0], f_coeffs[4*i+1],
                            g_coeffs[4*i+0], g_coeffs[4*i+1],
                            zetas[64+i])
        r2, r3 = ntt_base_multiplication(
                            f_coeffs[4*i+2], f_coeffs[4*i+3],
                            g_coeffs[4*i+2], g_coeffs[4*i+3],
                            -zetas[64+i])
        new_coeffs += [r0, r1, r2, r3]
    return RQ(new_coeffs)

def br(i, k):
    """
    bit reversal of an unsigned k-bit integer
    """
    bin_i = bin(i & (2**k - 1))[2:].zfill(k)
    return int(bin_i[::-1], 2)

def to_ntt(a):
    global NTTMUL
    """
    Convert a polynomial to number-theoretic transform (NTT) form in place
    The input is in standard order, the output is in bit-reversed order.
    NTT_ZETAS also has the Montgomery factor 2^16 included, so NTT 
    additionally maps to Montgomery domain.
    
    Only implemented (currently) for n = 256
    """
    k, l = 1, 128
    coeffs = a.list()
    # print(coeffs)
    # print()
    while l >= 2:
        start = 0
        while start < 256:
            zeta = zetas[k]
            k = k + 1
            for j in range(start, start + l):
                t = mont_mul(zeta, coeffs[j+l])
                NTTMUL += 1
                coeffs[j+l] = coeffs[j] - t
                coeffs[j]   = coeffs[j] + t
            start = l + (j + 1)
        l = l >> 1
    # print(coeffs)
    # print()
    return RQ(coeffs)
    
def from_ntt(a):
    global NTTMUL
    """
    Convert a polynomial from number-theoretic transform (NTT) form in place
    and multiplication by Montgomery factor 2^16.
    The input is in bit-reversed order, the output is in standard order.
    
    Because of the montgomery multiplication, we have:
        f != f.to_ntt().from_ntt()
        f = (1/2^16) * f.to_ntt().from_ntt()
    
    To recover f we do
        f == f.to_ntt().from_ntt().from_montgomery()
        
    Only implemented (currently) for n = 256
    """     
    l, l_upper = 2, 128
    k = l_upper - 1
    coeffs = a.list()
    # print(coeffs)
    while l <= 128:
        start = 0
        while start < 256:
            zeta = zetas[k]
            k = k - 1
            for j in range(start, start+l):
                t = coeffs[j]
                coeffs[j]   = t + coeffs[j+l]
                coeffs[j+l] = coeffs[j+l] - t
                coeffs[j+l] = mont_mul(zeta, coeffs[j+l])
                NTTMUL += 1
            start = j + l + 1
        l = l << 1
    for j in range(256):
        coeffs[j] = mont_mul(coeffs[j], f)
        NTTMUL += 1
        
    return RQ(coeffs)

def polymul_ntt_ct_gs(a, b):
    """Compute a polynomial multiplication by computing iNTT(NTT(a) o NTT(b)).

    Works for both the cyclic and the negacyclic case (with the correct twiddles).

    Parameters
    ----------
    a : Poly
        first multiplicand polynomial with n coefficients.
    b : Poly
        second multiplicand polynomial with n coefficients.
    twiddlesNtt : list
        twiddles for the foward NTT as computed by `precomp_ct_cyclic` or `precomp_ct_negacyclic`.
    tiwddlesInvntt : list
        twiddles for the inverse nTT as computed by `precomp_gs_cyclic` or `precmp_gs_negacyclic`.
    Returns
    ----------
    Poly
        product a*b with n coefficients.
    """
    antt = to_ntt(a)
    bntt = to_ntt(b)
    alist = antt.list()
    blist = bntt.list()
    cntt = ntt_coefficient_multiplication(alist,blist)
    return from_ntt(cntt)
    
def nttmul(A, B):
    global NTTMUL
    """
    Denoted A @ B
    """
    NTTMUL = 0
    new_elements = [[sum(polymul_ntt_ct_gs(a, b) for a,b in zip(A_row, B_col)) for B_col in B.transpose().rows()] for A_row in A.rows()]
    return matrix(new_elements), NTTMUL
from fractions import Fraction
from decimal import Decimal, getcontext
getcontext().prec = 250 # set precision
itwo,two,N = Decimal(0.5),Decimal(2),200
def angle(cosT):
  """given cos(theta) in decimal return theta"""
  for i in range(N):
    cosT = ((cosT + 1) / two) ** itwo
  sinT = (1 - cosT * cosT) ** itwo
  return sinT * (2 ** N)
pi = angle(Decimal(-1))

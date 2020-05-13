#!/usr/bin/env python3
#
# gInt.py - Gaussian integer class (numbers of the form a+bi, where a & b are integers)
#
# Python 3.5.2 , on
# 4.13.0-38-generic GNU/Linux
#

class gInt :
	'''Gaussian integer.  Numbers of the form a+bi, where a & b are integers.'''

	def __init__( self, a, b=0 ) :
		'''Creates a gInt of the form a+bi'''

		self.real = a
		self.imag = b
	
	def __eq__( self, other ) :
		if not isinstance( self, other.__class__ ) :
			return False
		return self.real == other.real and self.imag == other.imag
	
	def __str__( self ) :
		'''Return a string representation'''

		op = '+'
		i = self.imag
		if self.imag < 0 :
			op = '-'
			i = -i

		return '(%d%s%di)' % (self.real, op, i)
	
	
	def __add__( self, rhs ) :
		'''Return a new gInt, self + rsh'''

		r = self.real + rhs.real
		i = self.imag + rhs.imag

		return gInt( r, i )
	
	
	def __mul__( self, rhs ) :
		'''Return a new gInt, self * rhs'''

		r = self.real * rhs.real
		i = self.imag * rhs.imag

		return gInt( r, i )
	

	def norm( self ) :
		'''Return real^2 + imag^2 as an int'''

		r = self.real * self.real
		i = self.imag * self.imag

		return int(r + i)


def test() :
	'''A quick example/test function'''
	
	x = gInt( 3, -2 )
	y = gInt( 2, 5 )
	z = gInt( 13 )

	xcopy = gInt( x.real, x.imag )

	if not x == xcopy :
		print( "gInt not equal to new copy" )
	else :
		print( "Equal" )

	print( "x:", str(x) )
	print( "y:", str(y) )
	print( "z:", str(z) )
	print( "" )

	print( "norm(x):", x.norm() )
	print( "norm(y):", y.norm() )
	print( "norm(z):", z.norm() )
	print( "" )

	print( "x + y:", x+y )
	print( "x * y:", x*y )
	print( "" )

	print( "x:", str(x) )
	print( "y:", str(y) )
	print( "z:", str(z) )
	print( "" )

	print( "x + z:", x+z )
	print( "x * z:", x*z )
	print( "" )

	print( "y + z:", y+z )
	print( "y * z:", y*z )
	print( "" )


test()

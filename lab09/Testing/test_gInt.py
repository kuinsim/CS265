#!/usr/bin/env python3
#
#Suin Kim
#CS270-002
#Lab 9

import sys
import unittest

from gInt import gInt 

class gIntTest(unittest.TestCase):
	'''Tests for gInt class'''
	
	def setUp(self):
		self.n1 = gInt(-4,-9)
		self.n1copy = gInt(-4,-9)
		self.p1 = gInt(6,2)
		self.p1copy = gInt(6,2)

	def tearDown(self):
		pass

	def test_add(self):
		r = self.n1.real + self.p1.real

		self.assertEqual( self.n1.real, self.n1copy.real, 'Negative real part changed after addition.' )
		self.assertEqual( self.p1.real, self.p1copy.real, 'Positive real part changed after addition.' )
		self.assertEqual( r, 2, 'Addition of real parts failed.' )
		
		i = self.n1.imag + self.p1.imag

		self.assertEqual( self.n1.imag, self.n1copy.imag, 'Negative imaginary part changed after addition.' )
		self.assertEqual( self.p1.imag, self.p1copy.imag, 'Positive imaginary part changed after addition.' )
		self.assertEqual( i, -7, 'Addition of imaginary parts failed.' )
		
		g_int = gInt( r, i )
      
		self.assertEqual( g_int, gInt( 2, -7 ), 'Addition of Gaussian Integers failed.')

	def test_mul(self):
		r1 = self.n1.real * self.p1.real

		self.assertEqual( self.n1.real, self.n1copy.real, 'Negative real part changed after multiplication.' )
		self.assertEqual( self.p1.real, self.p1copy.real, 'Positive real part changed after multiplication.' )
		self.assertEqual( r1, -24, 'Multiplication of real parts failed.' )

		r2 = self.n1.imag * self.p1.imag

		self.assertEqual( self.n1.imag, self.n1copy.imag, 'Negative imaginary part changed after multiplication.' )
		self.assertEqual( self.p1.imag, self.p1copy.imag, 'Positive imaginary part changed after multiplication.' )
		self.assertEqual( r2, -18, 'Multiplication of imaginary parts failed.' )

		i1 = self.n1.real * self.p1.imag

		self.assertEqual( self.n1.real, self.n1copy.real, 'Negative real part changed after multiplication.' )
		self.assertEqual( self.p1.imag, self.p1copy.imag, 'Positive imaginary part changed after multiplication.' )
		self.assertEqual( i1, -8, 'Multiplication of real and imaginary parts failed.' )

		i2 = self.n1.imag * self.p1.real

		self.assertEqual( self.n1.imag, self.n1copy.imag, 'Negative imaginary part changed after multiplication.' )
		self.assertEqual( self.p1.real, self.p1copy.real, 'Positive real part changed after multiplication.' )
		self.assertEqual( i2, -54, 'Multiplication of real and imaginary parts failed.' )

		r = r1 - r2
		i = i1 + i2

		self.assertEqual( r, -6, 'Combination of real parts failed.' )
		self.assertEqual( i, -62, 'Combination of imaginary parts failed.' )

		g_int = gInt( r, i )

		self.assertEqual( g_int, gInt( -6, -62 ), 'Multiplication of Gaussian Integers failed.' )

	def test_norm(self):
		n1_r_sq = self.n1.real * self.n1.real

		self.assertEqual( self.n1.real, self.n1copy.real, 'Negative real part changed after squaring.' )
		self.assertEqual( n1_r_sq, 16, 'Squaring of negative real part failed.' )

		n1_i_sq = self.n1.imag * self.n1.imag
		self.assertEqual( self.n1.imag, self.n1copy.imag, 'Negative imaginary part changed after squaring.' )
		self.assertEqual( n1_i_sq, 81, 'Squaring of negative imaginary part failed.' )

		p1_r_sq = self.p1.real * self.p1.real

		self.assertEqual( self.p1.real, self.p1copy.real, 'Positive real part changed after squaring.' )
		self.assertEqual( p1_r_sq, 36, 'Squaring of positive real part failed.' )

		p1_i_sq = self.p1.imag * self.p1.imag
		self.assertEqual( self.p1.imag, self.p1copy.imag, 'Positive imaginary part changed after squaring.' )
		self.assertEqual( p1_i_sq, 4, 'Squaring of positive imaginary part failed.' )

		norm_n = n1_r_sq + n1_i_sq
		norm_p = p1_r_sq + p1_i_sq

		self.assertEqual( norm_n, 97, 'Failed to get norm of a negative Gaussian Integer.' )
		self.assertEqual( norm_p, 40, 'Failed to get norm of a positive Gaussian Integer.' )



if __name__ == '__main__':
	sys.argv.append( '-v' )
	unittest.main()


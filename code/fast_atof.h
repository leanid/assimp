// Copyright (C) 2002-2007 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine" and the "irrXML" project.
// For conditions of distribution and use, see copyright notice in irrlicht.h and irrXML.h
// Adapted to the ASSIMP library because the builtin atof indeed takes AGES to parse a
// float inside a large string. Before parsing, it does a strlen on the given point.

#ifndef __FAST_A_TO_F_H_INCLUDED__
#define __FAST_A_TO_F_H_INCLUDED__

#include <math.h>

namespace Assimp
{

const float fast_atof_table[16] =	{  // we write [16] here instead of [] to work around a swig bug
	0.f,
	0.1f,
	0.01f,
	0.001f,
	0.0001f,
	0.00001f,
	0.000001f,
	0.0000001f,
	0.00000001f,
	0.000000001f,
	0.0000000001f,
	0.00000000001f,
	0.000000000001f,
	0.0000000000001f,
	0.00000000000001f,
	0.000000000000001f
};

inline unsigned int strtol10( const char* in, const char** out=0)
{
	unsigned int value = 0;

	while ( 1 )
	{
		if ( *in < '0' || *in > '9' )
			break;

		value = ( value * 10 ) + ( *in - '0' );
		++in;
	}
	if (out)
		*out = in;
	return value;
}


// specal version of the function, providing higher accuracy
inline uint64_t strtol10_64( const char* in, const char** out=0)
{
	uint64_t value = 0;

	while ( 1 )
	{
		if ( *in < '0' || *in > '9' )
			break;

		value = ( value * 10 ) + ( *in - '0' );
		++in;
	}
	if (out)
		*out = in;
	return value;
}

//! Provides a fast function for converting a string into a float,
//! about 6 times faster than atof in win32.
// If you find any bugs, please send them to me, niko (at) irrlicht3d.org.
inline const char* fast_atof_move( const char* c, float& out)
{
	bool inv = false;
	const char *t;
	float f;

	if (*c=='-')
	{
		++c;
		inv = true;
	}

	//f = (float)strtol(c, &t, 10);
	f = (float) strtol10_64 ( c, &c );

	if (*c == '.')
	{
		++c;

		// NOTE: The original implementation is highly unaccurate here
		// The precision of a single IEEE 754 float is not high enough
		// everything behind the 6th digit tends to be more inaccurate
		// than it would need  to be.
		// Casting to double seems to solve the problem.
		// strtol_64 is used to prevent integer overflow.

		//float pl = (float)strtol(c, &t, 10);
		double pl = (double) strtol10_64 ( c, &t );
		pl *= fast_atof_table[t-c];

		f += (float)pl;

		c = t;

		if (*c == 'e')
		{
			++c;
			//float exp = (float)strtol(c, &t, 10);
			bool einv = (*c=='-');
			if (einv)
				++c;

			float exp = (float)strtol10(c, &c);
			if (einv)
				exp *= -1.0f;

			f *= pow(10.0f, exp);
		}
	}

	if (inv)
		f *= -1.0f;
	
	out = f;
	return c;
}

inline float fast_atof(const char* c)
{
	float ret;
	fast_atof_move(c, ret);
	return ret;
}

} // end of namespace Assimp

#endif


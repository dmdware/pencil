



#include "../platform.h"
#include "quaternion.h"

inline void Quaternion::inverse()
{
	m_quat[0] = -m_quat[0];
	m_quat[1] = -m_quat[1];
	m_quat[2] = -m_quat[2];
	m_quat[3] = -m_quat[3];
}

void Quaternion::fromAngles( const float *angles )
{
	float angle;
	double sr, sp, sy, cr, cp, cy;

	angle = angles[2]*0.5f;
	sy = sin( angle );
	cy = cos( angle );
	angle = angles[1]*0.5f;
	sp = sin( angle );
	cp = cos( angle );
	angle = angles[0]*0.5f;
	sr = sin( angle );
	cr = cos( angle );

	double crcp = cr*cp;
	double srsp = sr*sp;

	m_quat[0] = ( float )( sr*cp*cy-cr*sp*sy );
	m_quat[1] = ( float )( cr*sp*cy+sr*cp*sy );
	m_quat[2] = ( float )( crcp*sy-srsp*cy );
	m_quat[3] = ( float )( crcp*cy+srsp*sy );
}

void Quaternion::slerp( const Quaternion& q1, Quaternion& q2, float interp )
{
	// Decide if one of the quaternions is backwards
	int32_t i;
	float a = 0, b = 0;
	for ( i = 0; i < 4; i++ )
	{
		a += ( q1[i]-q2[i] )*( q1[i]-q2[i] );
		b += ( q1[i]+q2[i] )*( q1[i]+q2[i] );
	}
	if ( a > b )
		q2.inverse();

	float cosom = q1[0]*q2[0]+q1[1]*q2[1]+q1[2]*q2[2]+q1[3]*q2[3];
	double sclq1, sclq2;

	if (( 1.0+cosom ) > 0.00000001 )
	{
		if (( 1.0-cosom ) > 0.00000001 )
		{
			double omega = acos( cosom );
			double sinom = sin( omega );
			sclq1 = sin(( 1.0-interp )*omega )/sinom;
			sclq2 = sin( interp*omega )/sinom;
		}
		else
		{
			sclq1 = 1.0-interp;
			sclq2 = interp;
		}
		for ( i = 0; i < 4; i++ )
			m_quat[i] = ( float )( sclq1*q1[i]+sclq2*q2[i] );
	}
	else
	{
		m_quat[0] = -q1[1];
		m_quat[1] = q1[0];
		m_quat[2] = -q1[3];
		m_quat[3] = q1[2];

		sclq1 = sin(( 1.0-interp )*0.5*M_PI );
		sclq2 = sin( interp*0.5*M_PI );
		for ( i = 0; i < 3; i++ )
			m_quat[i] = ( float )( sclq1*q1[i]+sclq2*m_quat[i] );
	}
}

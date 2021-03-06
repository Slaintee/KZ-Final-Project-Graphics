#include <assert.h>
#include <math.h>
#include "Vector3.h"

Vector3::Vector3()
{
	v[0] = 0.0f;
	v[1] = 0.0f;
	v[2] = 0.0f;
	v[3] = 0.0f;
}

Vector3::Vector3(float nw)
{
	v[0] = 0.0f;
	v[1] = 0.0f;
	v[2] = 0.0f;
	v[3] = nw;
}

Vector3::Vector3(float nx, float ny, float nz)
{
	v[0] = nx;
	v[1] = ny;
	v[2] = nz;
	v[3] = 1.0f;
}

Vector3::Vector3(const Vector3& a)
{
	v[0] = a.v[0];
	v[1] = a.v[1];
	v[2] = a.v[2];
	v[3] = 1.0f;
}

void Vector3::set(float x, float y, float z)
{
	v[0] = x; 
	v[1] = y;
	v[2] = z;
}

float Vector3::size() const
{
	return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

Vector3 Vector3::normal() const
{
    float oneOverMag = 1.0f / size();

	return Vector3(v[0]*oneOverMag,v[1]*oneOverMag,v[2]*oneOverMag);
}

Vector3 Vector3::scale(const Vector3& a) const
{
	return Vector3(v[0]*a.v[0], v[1]*a.v[1], v[2]*a.v[2]);
}

Vector3 Vector3::reflect(const Vector3& a) const
{
	Vector3 ref;
	float c1 = -1.0f * (a * (*this));
	ref = (*this) + ((a * c1) * 2.0f);
	return ref;
}

Vector3 Vector3::project(const Vector3& a) const
{
	float s = ((*this) * a) / a.size();
	return a * s;
}

void Vector3::operator=(const Vector3& a)
{
	v[0] = a.v[0];
	v[1] = a.v[1];
	v[2] = a.v[2];
	v[3] = 1.0f;
}

Vector3 Vector3::operator+(const Vector3& a) const
{
	return Vector3(v[0]+a.v[0],v[1]+a.v[1],v[2]+a.v[2]);
}

Vector3 Vector3::operator-(const Vector3& a) const
{
	return Vector3(v[0]-a.v[0],v[1]-a.v[1],v[2]-a.v[2]);
}

Vector3 Vector3::operator*(float s) const
{
	return Vector3(v[0]*s,v[1]*s,v[2]*s);
}

float Vector3::operator*(const Vector3& a) const
{
	return v[0]*a.v[0] + v[1]*a.v[1] + v[2]*a.v[2];
}

Vector3 Vector3::operator*=(float s)
{
	(*this) = (*this) * s;
	return (*this);
}

Vector3 Vector3::operator+=(const Vector3& a)
{
	(*this) = (*this) + a;
	return (*this);
}

bool Vector3::operator==(const Vector3& a)
{
	return (v[0] == a.v[0]) && (v[1] == a.v[1]) && (v[2] == a.v[2]);
}

#ifndef __MATRIX4_H_
#define __MATRIX4_H_
#include "mathLib.h"

class Vector4;

class DLLEXPORT Matrix4
{
	/*
	4x4 Matrix
	x.x, x.y, x.z, 0
	y.x, y.y, y.z, 0
	z.x, z.y, z.z, 0
	t.x, t.y, t.z, 1

	In Memory
	x.x, x.y, x.z, 0, y.x, y.y, y.z, 0, z.x, z.y, z.z, 0, t.x, t.y, t.z, 1
	*/

public:
	union
	{
		float values_[16] = {
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 1 };
		struct
		{
			float
				m_11, m_12, m_13, m_14,
				m_21, m_22, m_23, m_24,
				m_31, m_32, m_33, m_34,
				m_41, m_42, m_43, m_44;
		};
	};

	//\============================================================================
	///	Constructors
	//\============================================================================
	//Default Constructor
	Matrix4();
	//Copy Constructor
	Matrix4(const Matrix4& other);
	//Construct with values
	Matrix4(
		const float& a_xx, const float& a_xy, const float& a_xz,
		const float& a_yx, const float& a_yy, const float& a_yz,
		const float& a_zx, const float& a_zy, const float& a_zz,
		const float& a_tx, const float& a_ty, const float& a_tz);
	//Construct with all 16 values
	Matrix4(
		const float& a_xx, const float& a_xy, const float& a_xz, const float& a_xw,
		const float& a_yx, const float& a_yy, const float& a_yz, const float& a_yw,
		const float& a_zx, const float& a_zy, const float& a_zz, const float& a_zw,
		const float& a_tx, const float& a_ty, const float& a_tz, const float& a_tw);
	Matrix4(const float a_values[16]);
	//Default Destructor
	~Matrix4();

	//\============================================================================
	///	Constants
	//\============================================================================
	//Identity Matrix4
	static Matrix4 IDENTITY;

	//\============================================================================
	///	Operator Overloads
	//\============================================================================
	//Access Individual Elements in the Matrix
	float operator()(unsigned row, unsigned col) const;
	float& operator()(unsigned row, unsigned col);
	//Multiply Matrix4 by a Matrix4
	Matrix4 operator*(Matrix4& other);
	void operator*=(Matrix4& other);

	//\===========================================================================================
	//\ Component Access
	//\===========================================================================================
	//Vector4               x();
	//Vector4               y();
	//Vector4               z();
	//Vector4               t();
	//const Vector4         x() const;
	//const Vector4         y() const;
	//const Vector4         z() const;
	//const Vector4         t() const;

	//\===========================================================================================
	//\ Component Access/ Retreival As Vector4
	//\===========================================================================================
	void					SetX(const Vector4& a_v4);
	void                    SetY(const Vector4& a_v4);
	void                    SetZ(const Vector4& a_v4);
	void                    SetT(const Vector4& a_v4);
	Vector4                 GetX() const;
	Vector4                 GetY() const;
	Vector4                 GetZ() const;
	Vector4                 GetT() const;

	//\===========================================================================================
	//\ Translate the Matrix4
	//\===========================================================================================
	void					Translate(Vector2& a_v2);
	void					Translate(Vector3& a_v3);

	//\===========================================================================================
	//\ Component Row/Column Access Operators
	//\===========================================================================================
	void                    SetCol(int iCol, const Vector3& vCol);
	void                    SetCol(int iCol, const Vector4& vCol);

	void                    GetCol(int iCol, Vector3& vCol) const;
	void                    GetCol(int iCol, Vector4& vCol) const;

	void                    SetRow(int iRow, const Vector3& vRow);
	void                    SetRow(int iRow, const Vector4& vRow);

	void                    GetRow(int iRow, Vector3& vRow) const;
	void                    GetRow(int iRow, Vector4& vRow) const;

	//\===========================================================================================
	//\ Equivalence operators
	//\===========================================================================================
	bool                    operator ==         (const Matrix4& a_m4) const;
	bool                    operator !=         (const Matrix4& a_m4) const;

	//\===========================================================================================
	//\ Operator overloads for Addition
	//\===========================================================================================
	const Matrix4          operator  +         (const Matrix4& a_m4) const;
	const Matrix4&         operator  +=        (const Matrix4& a_m4);

	//\===========================================================================================
	//\ Operator overloads for Subtraction
	//\===========================================================================================
	const Matrix4          operator  -         (const Matrix4& a_m4) const;
	const Matrix4&         operator  -=        (const Matrix4& a_m4);

	//\===========================================================================================
	//\ Operator overloads for multiplication
	//\=========================================================================================== 
	const Matrix4          operator *          (float a_fScalar) const; 
	friend const Matrix4   operator *          (float a_fScalar, const Matrix4& a_m4);
	const Matrix4&         operator *=         (float a_fScalar);

	const Vector3          operator *          (const Vector3& a_v3) const;
	friend const Vector3   operator *          (const Vector3& a_v3, const Matrix4& a_m4);

	const Vector4          operator *          (const Vector4& a_v4) const;
	friend const Vector4   operator *          (const Vector4& a_v4, const Matrix4& a_m4);

	const Matrix4          operator *          (const Matrix4& a_m4) const;
	const Matrix4&         operator *=         (const Matrix4& a_m4);

	//\=========================================================================================== 
	//\ Transpose Matrix
	//\===========================================================================================
	void				Transpose();
	Matrix4				Matrix4::GetTranspose() const;

	//\=========================================================================================== 
	// Inverse Matrix Functions
	//\===========================================================================================
	float               Determinant() const;
	bool                Inverse();

	//\=========================================================================================== 
	// Matrix Rotation functions
	//\===========================================================================================
	void				RotateX(float fAngle);
	void                RotateY(float fAngle);
	void                RotateZ(float fAngle);

	//\=========================================================================================== 
	// Matrix Rotation functions
	//\===========================================================================================
	friend Matrix4		CreateRotateX(float fAngle);
	friend Matrix4      CreateRotateY(float fAngle);
	friend Matrix4      CreateRotateZ(float fAngle);
};

#endif //__MATRIX4_H_
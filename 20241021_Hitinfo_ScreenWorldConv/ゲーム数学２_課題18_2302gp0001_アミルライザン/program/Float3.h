#pragma once

//---------------------------------------------------------------------------------
//	Float3 �N���X�i x y z ������N���X�j
//---------------------------------------------------------------------------------
class Float3
{
public:
	float	x;
	float	y;
	float	z;

	Float3();									//	�R���X�g���N�^
	Float3( float x, float y, float z );
	Float3( VECTOR v );

	void clear();								//	�[��������
	void set( float x, float y, float z );		//	�l�̃Z�b�g
	void set( Float3 &v );

	float GetLength();							//	�����擾
	void normalize();							//	���K��
	void SetLength( float length );				//	�����ݒ�

	Float3& operator = ( const Float3 &v );		//	= ���Z�q�̃I�[�o�[���[�h

	Float3& operator += ( const Float3 &v );	//	+= ���Z�q�̃I�[�o�[���[�h
	Float3& operator -= ( const Float3 &v );	//	-= ���Z�q�̃I�[�o�[���[�h
	Float3& operator *= ( const float f );		//	*= ���Z�q�̃I�[�o�[���[�h
	Float3& operator /= ( const float f );		//	/= ���Z�q�̃I�[�o�[���[�h

	VECTOR VGet();								//	DX���C�u�����Ŏg�� VECTOR ��Ԃ�
	void VSet( VECTOR v );						//	DX���C�u�����Ŏg�� VECTOR �̒l���擾���Đݒ�
};

//	+ ���Z�q�̃I�[�o�[���[�h
Float3 operator + ( const Float3 &v1, const Float3 &v2 );
//	- ���Z�q�̃I�[�o�[���[�h
Float3 operator - ( const Float3 &v1, const Float3 &v2 );
//	* ���Z�q�̃I�[�o�[���[�h
Float3 operator * ( const Float3 &v, const float f );
//	/ ���Z�q�̃I�[�o�[���[�h
Float3 operator / ( const Float3 &v, const float f );

//	�Q�� Float3 �̋��������߂�
float GetFloat3Distance( Float3 &pos1, Float3 &pos2 );
//	�Q�� Float3 �̓��ς����߂�
float GetFloat3Dot( Float3 &v1, Float3 &v2 );
//	�Q�� Float3 �̊O�ς����߂�
Float3 GetFloat3Cross( Float3 &v1, Float3 &v2 );
//	Float3 �� MATRIX �ŕϊ��������̂�Ԃ�
Float3 GetFloat3VTransform( Float3 &v, MATRIX &mat );

#pragma once
#ifndef VECTOR_H_
#define VECTOR_H_

#define ForEach for( size_t i = 0; i < Size; ++i  )

namespace Maths
{
	template<size_t Size> struct Vector
	{
		float m_fData[Size];

		inline Vector()
		{
			ForEach
			{
				m_fData[i] = 0.f;
			}
		}

		inline Vector( float* FloatArray )
		{
			ForEach
			{
				m_fData[i] = 0.f;
			}
			memcpy_s( &m_fData[0], sizeof(m_fData), FloatArray, sizeof(m_fData));
		}

		inline Vector( Vector const & Other )
		{
			memcpy_s( &m_fData[0], sizeof(m_fData), Other.m_fData, sizeof(m_fData));
		}

		//NOT SAFE ON VECTORS GREATER THAN <4>!!!!
		inline Vector( float X, float Y = 0.f, float Z = 0.f, float W = 0.f)
		{
			float MyArray[4]= {X, Y, Z, W};
			memcpy_s( &m_fData[0], sizeof(m_fData), MyArray, sizeof(m_fData));
		}

		static Vector Zero()
		{
			static Vector Zero;
			return Zero;
		}
		inline float & operator[] ( int Pos )
		{
			return m_fData[Pos];
		}

		inline void operator= ( Vector const & Other )
		{
			ForEach
			{
				m_fData[i] = Other.m_fData[i];
			}
		}

		inline bool operator== ( Vector const & Other )
		{
			bool bResult = true;
			ForEach
			{
				bResult &= m_fData[i] == Other.m_fData[i];
			}
			return bResult;
		}

		inline bool operator!= ( Vector const & Other )
		{
			bool bResult = true;
			ForEach
			{
				bResult &= m_fData[i] != Other.m_fData[i];
			}
			return bResult;
		}

		inline Vector operator* ( Vector const & Other )
		{
			Vector result;
			ForEach
			{
				result.m_fData[i] = m_fData[i] * Other.m_fData[i];
			}
			return result;
		}

		inline Vector operator/ ( Vector const & Other )
		{
			Vector result;
			ForEach
			{
				result.m_fData[i] = m_fData[i] / Other.m_fData[i];
			}
			return result;
		}

		inline Vector operator- ( Vector const & Other )
		{
			Vector result;
			ForEach
			{
				result.m_fData[i] = m_fData[i] - Other.m_fData[i];
			}
			return result;
		}

		inline Vector operator+ ( Vector const & Other )
		{
			Vector result;
			ForEach
			{
				result.m_fData[i] = m_fData[i] + Other.m_fData[i];
			}
			return result;
		}

		inline void operator-= ( Vector const & Other )
		{
			ForEach
			{
				m_fData[i] -= Other.m_fData[i];
			}
		}

		inline void operator+= ( Vector const & Other )
		{
			ForEach
			{
				m_fData[i] += Other.m_fData[i];
			}
		}

		inline Vector operator/ ( float  Other )
		{
			Vector result;
			ForEach
			{
				result.m_fData[i] = m_fData[i] / Other;
			}
			return result;
		}

		inline Vector operator* ( float  Other )
		{
			Vector result;
			ForEach
			{
				result.m_fData[i] = m_fData[i] * Other;
			}
			return result;
		}

		inline Vector operator+ ( float  Other )
		{
			Vector result;
			ForEach
			{
				result.m_fData[i] = m_fData[i] + Other;
			}
			return result;
		}

		inline Vector operator- ( float  Other )
		{
			Vector result;
			ForEach
			{
				result.m_fData[i] = m_fData[i] - Other;
			}
			return result;
		}

	};

}

#undef ForEach

#endif//VECTOR_H_
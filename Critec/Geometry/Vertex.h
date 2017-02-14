#ifndef __CRITEC_VERTEX_H__
#define __CRITEC_VERTEX_H__

#include "../Math/Vector.h"

#define BUFFER_OFFSET(x) ((char*)NULL + (x))

class crVertex {
public:
	crVec3		xyz;
	crVec3		normal;
	crVec3		tangent;
	crVec2		st;
	crVec2		_st[4];
	int			color[4];

public:
				crVertex( void );
	explicit	crVertex( const crVertex & vert);
	explicit	crVertex( crVec3 xyz );

	void		Clear( void );
	void		Normalize( void );
	void		CalculateTangent( crVertex a, crVertex b, crVertex c );
	
	void		SetColor( int r, int g, int b );
	void		SetColor( int r, int g, int b, int a );
	int*		GetColor( void ) const;

	float*		ToFloatPtr( void );
};

#endif /* !__CRITEC_VERTEX_H__*/
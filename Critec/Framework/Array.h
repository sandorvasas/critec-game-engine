// Copyright (C) 2007 by Sandor Vasas

#ifndef __CRITEC_ARRAY_H__
#define __CRITEC_ARRAY_H__

#include <windows.h>

enum {
	Bytes = 0,
	kBytes,			MBytes,
	GBytes,			TBytes
};

/*
=========================
 crArray
=========================
*/
template <class T>
class crArray {

public:
						crArray( void ):	
							Count(0) {}
						~crArray( void ) { Free(); }

	void				Allocate( unsigned long Count );
	void				Reallocate( unsigned long newCount, bool keepOld = true );
	void				Free( void );
	void				Append( T element );
	unsigned long		MemoryUsed( int type = Bytes ) const;
	T*					Ptr( void ) const;
	T					LastElement( void );

	//T					operator[](unsigned long index );
	crArray<T>			operator=(const crArray<T>& oArray);

public:
	unsigned long		Count;

protected:
	T*					Array;
};	


/*
=========================
 crArray2D
=========================
*/
template< class T >
class crArray2D {

public:
						crArray2D( void ):
						 Rows(0), Columns(0)
						 {}
						~crArray2D( void )
						{ Free(); }
		
	void				Allocate( unsigned long Rows, unsigned long Columns );
	void				Reallocate( unsigned long nRows, unsigned long nColumns, bool keepOld = true );
	void				Free( void );
	unsigned long		MemoryUsed( int type = Bytes ) const;
	T**					Ptr( void ) const;

//	T					operator[](unsigned long row, unsigned long column );
	crArray2D<T>		operator=(const crArray2D<T>& oArray);

	
protected:
	T**					Array;

public:
	unsigned long		Rows;
	unsigned long		Columns;
};




template< class T >
inline void crArray< T >::Allocate( unsigned long Count ) {
	this->Count = Count;
	Array = new T[Count];
}

template< class T >
inline void crArray< T >::Reallocate( unsigned long newCount, bool keepOld = true ) {
	if (!Count) {
		Allocate( newCount );
		return;
	}

	T* newbuffer = new T[newCount];

	if (keepOld) {
		for (unsigned long i = 0; i<Count; i++) {
			newbuffer[i] = this->Array[i];
		}
	}

	Free();

	Array = newbuffer;
	Count = newCount;
}

template< class T >
inline void crArray< T >::Free( void ) {
	if (Count > 1)
		delete [] Array;
	if (Count == 1)
		delete Array;
	Count = 0;
	Array = NULL;
}

template< class T >
inline unsigned long crArray< T >::MemoryUsed( int type = Bytes) const {
	unsigned long aSize = sizeof(Array);

	for (int i=0; i<type; i++) {
		aSize /= 1024;
	}

	return aSize;
}

template< class T >
inline T crArray< T >::LastElement( void ) {
	return Array[Count-1];
}

/*
template< class T >
inline T crArray< T >::operator[](unsigned long index ) {
	T ef;
	return (index >= 0 && index < Count)? Array[index] : ef;
}
*/

template< class T >
inline crArray< T > crArray< T >::operator=(const crArray<T>& oArray) {
	Free();
	this->Array = oArray.Array;
	this->Count = oArray.Count;

	return *this;
}

template< class T >
inline void crArray< T >::Append( T element ) {
	Reallocate(Count+1);
	Array[Count-1] = element;
}

template< class T >
inline T* crArray< T >::Ptr( void ) const {
	return Array;
}

/*
=========================
	crArray2D
=========================
*/
template< class T >
inline void crArray2D< T >::Allocate( unsigned long Rows, unsigned long Columns ) {
	this->Rows = Rows;
	this->Columns = Columns;


	Array = new T*[Rows];
	for (unsigned int r=0; r<Rows; r++) {
		Array[r] = new T[Columns];
	}
}

template< class T >
inline void crArray2D< T >::Reallocate( unsigned long nRows, unsigned long nColumns, bool keppOld = true ) {
	T** newbuffer = new T*[nRows];
	
	for(unsigned long i=0; i<nRows; i++)
		newbuffer[i] = new T[Columns];

	if (keepOld)
		for(unsigned long i=0; i<Rows; i++)
		for(unsigned long j=0; j<Columns; i++)
			newbuffer[i][j] = Array[i][j];
	
	delete [] Array;
	Array = newbuffer;
	this->Rows = nRows;
	this->Columns = nColumns;
}

template< class T >
inline void crArray2D< T >::Free( void ) {
	for(unsigned long i=0; i<Rows; i++)
		if(Rows>1) delete [] Array[i];
			else delete Array[i];

	Rows = 0;
	Columns = 0;
}

template< class T >
inline unsigned long crArray2D< T >::MemoryUsed(int type = Bytes) const {
	unsigned long nSize = sizeof(Array);

	for(int i=0; i<type; i++) nSize /= 1024;

	return nSize;
}

template< class T >
inline crArray2D< T > crArray2D< T >::operator =(const crArray2D< T > &oArray) {
	Free();
	this->Rows = oArray.Rows;
	this->Columns = oArray.Columns;
	this->Array = oArray.Array;
}

template< class T >
inline T**	crArray2D< T >::Ptr( void ) const {
	return Array;
}

#endif /* !__CRITEC_ARRAY_H__ */

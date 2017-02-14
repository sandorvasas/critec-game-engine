// Copyright 2007 by Sandor Vasas

#ifndef __CRITEC_BLOOM_H__
#define __CRITEC_BLOOM_H__

#include "GL/GLexp.h"
#include "Framebuffer.h"
#include "ShaderManager.h"

const int BLOOM_WIDTH  = 512;
const int BLOOM_HEIGHT = 512;

class crBloomFilter {
protected:
	crFrameBuffer2D		bloomImage;
	crFrameBuffer2D		tempBuf;
	crGLSLShader		Blur;
	crGLSLShader		Bloom;
	
public:
						crBloomFilter( void );
						~crBloomFilter( void );

	void				BloomImage( crFrameBuffer2D frame );
	unsigned int		GetBlurredImage( void );
	unsigned int		GetBloomImage( void );
};


/*
	
	J�rhat� �t:
	1. �tadni a (screen) framebuffer object-et a crBloom oszt�lynak
	2. A crBloom oszt�ly �tm�solja ezt egy HxV m�ret� fbo-ra
	3. Bind()-eli az ideiglenes fbo-t
	4. A horizont�lis blur shader-t aktiv�lva kirajzolja a HxV m�ret� fbo textur�j�t egy quadra
	5. Unbind()-eli az ideiglenes fbo-t
	6. Bind()-eli a m�sodik ideiglenes fbo-t
	7. A vertik�lis blur shadert-t aktiv�lva kirajzolja az els� ideiglenes fbo textur�j�t egy quadra
	8. Unbind()-eli a m�sodik ideiglenes fbo-t
	<ekkor megvan a blurred image>
	9. A bloom shadert aktiv�lva kirajzolja a m�sodik ideiglenes fbo textur�j�t egy quadra.
	10. Blend-eli az eredeti (screen) fbo textur�j�val

	bloomFilter->CreateBlurredImage(&screen);
	  ( =  3-8. l�p�sek  )
    
	bloomFilter->UseBloomShader(true);
	 <k�perny� m�ret� quadra orthogon�lis m�dban kirajzolni>
	 <bloomFilter->BlurredImage textur�t >
    bloomFilter->UseBloomShader(false);
	  ( = 9. l�p�s )

	BlurredImage-nek csak akkor van �rt�ke, ha a CreateBlurredImage() proc lefutott.
	BlurredImage = m�sodik ideiglenes fbo textur�ja
*/

#endif /* !__CRITEC_BLOOM_H__ */
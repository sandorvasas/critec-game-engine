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
	
	Járható út:
	1. Átadni a (screen) framebuffer object-et a crBloom osztálynak
	2. A crBloom osztály átmásolja ezt egy HxV méretû fbo-ra
	3. Bind()-eli az ideiglenes fbo-t
	4. A horizontális blur shader-t aktiválva kirajzolja a HxV méretû fbo texturáját egy quadra
	5. Unbind()-eli az ideiglenes fbo-t
	6. Bind()-eli a második ideiglenes fbo-t
	7. A vertikális blur shadert-t aktiválva kirajzolja az elsõ ideiglenes fbo texturáját egy quadra
	8. Unbind()-eli a második ideiglenes fbo-t
	<ekkor megvan a blurred image>
	9. A bloom shadert aktiválva kirajzolja a második ideiglenes fbo texturáját egy quadra.
	10. Blend-eli az eredeti (screen) fbo texturájával

	bloomFilter->CreateBlurredImage(&screen);
	  ( =  3-8. lépések  )
    
	bloomFilter->UseBloomShader(true);
	 <képernyõ méretû quadra orthogonális módban kirajzolni>
	 <bloomFilter->BlurredImage texturát >
    bloomFilter->UseBloomShader(false);
	  ( = 9. lépés )

	BlurredImage-nek csak akkor van értéke, ha a CreateBlurredImage() proc lefutott.
	BlurredImage = második ideiglenes fbo texturája
*/

#endif /* !__CRITEC_BLOOM_H__ */
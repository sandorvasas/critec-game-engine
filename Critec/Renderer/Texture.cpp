#include "texture.h"


TextureData* LoadBMPFile (char* filename, bool alpha) {
	crRestoreFile	 File;
	BITMAPINFOHEADER bmih;
	BITMAPFILEHEADER bmfh;
	RGBTRIPLE		 rgb;
	TextureData*	 texData = new TextureData;

	if(!File.Open(filename)) return NULL;

	File.Read(&bmfh, sizeof(bmfh));
	File.Read(&bmih, sizeof(bmih));

	if (bmfh.bfType != 'MB') return NULL;

	File.Seek(bmfh.bfOffBits, SEEK_SET);

	texData->width  = bmih.biWidth;
	texData->height = bmih.biHeight;

	texData->texels = new unsigned char [texData->width*texData->height*4];

	unsigned int j=0;
	for(int i=0; i<texData->width*texData->height*4; i++)
	{
		File.Read(&rgb, sizeof(rgb));

		texData->texels[j++] = rgb.rgbtRed;
		texData->texels[j++] = rgb.rgbtGreen;
		texData->texels[j++] = rgb.rgbtBlue;
		texData->texels[j++] = (alpha)? ((rgb.rgbtRed+rgb.rgbtGreen+rgb.rgbtBlue<10)? 0 : 255) : 255;

	}

	File.Close();

	return texData;
}

TextureData* LoadDDSFile(char* filename) {
	DDSURFACEDESC2	ddsd;
	crRestoreFile	File;
	TextureData*	texData = new TextureData;
	char			magicNumber[4];


	if(!File.Open(filename)) return NULL;
	File.Read(&magicNumber, sizeof(char)*4);

	if (!strcmp(magicNumber,"DDS ")) {
		MSGBOX("Invalid DDS file");
		return NULL;
	}

	File.Read(&ddsd, sizeof(ddsd));
	texData->width  = ddsd.dwWidth;
	texData->height = ddsd.dwHeight;
	texData->numMipmaps = ddsd.dwMipMapCount;

	switch(ddsd.ddpfPixelFormat.dwFourCC) {
		case FOURCC_DXT1:
			texData->format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			texData->internalFormat = 3;
		break;

		case FOURCC_DXT3:
			texData->format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
			texData->internalFormat = 4;
		break;

		case FOURCC_DXT5:
			texData->format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			texData->internalFormat = 4;
		break;
	}

	long bufferSize = File.GetSize() - File.Tell();

	texData->texels = new unsigned char [ bufferSize ];
	for(long i=0; i<bufferSize; i++) 
		File.ReadByte(&texData->texels[i]);
	
	File.Close();
	return texData;
}

GLuint LoadDDSTexture(char* filename) {
	TextureData *texData = LoadDDSFile(filename);
	unsigned int tex_id;
	
	if (texData==NULL) return 0;

	glGenTextures(1, &tex_id);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	int ma;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, (float*)&ma );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, ma);

	int offset = 0, mipSize;
	int blockSize = (texData->format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT)? 8 : 16;

	for (int i=0; i<texData->numMipmaps; ++i) {

		mipSize = ((texData->height +3)/4) * ((texData->width +3)/4) * blockSize;

		glCompressedTexImage2D(	GL_TEXTURE_2D, 
								i, 
								texData->format, 
								texData->width, 
								texData->height,
								0, 
								mipSize, 
								texData->texels + offset);
		texData->height /=2;
		texData->width /=2;
		offset += mipSize;
	}

	glBindTexture(GL_TEXTURE_2D, NULL);
	
	delete [] texData->texels;
	delete [] texData;

	return tex_id;
}

GLuint LoadBMPTexture(char* filename, bool alpha) {
	GLuint result;
	TextureData *data = LoadBMPFile(filename, alpha);
	if (!data) return 0;

    glGenTextures(1, &result);
    glBindTexture(GL_TEXTURE_2D, result);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16);
//     gluBuild2DMipmaps(GL_TEXTURE_2D, 3, data->width, data->height, GL_RGBA, GL_UNSIGNED_BYTE, data->texels);
    glBindTexture(GL_TEXTURE_2D, 0);

	delete [] data->texels;
	delete [] data;

  return result;
}


unsigned int CreateEmptyTexture(int width, int height) {
	unsigned int ret;
	unsigned char *data = new unsigned char[width*height*4];

	for (int i=0; i<width*height*4; i++) data[i] = 255;

	glGenTextures(1, &ret);
	glBindTexture(GL_TEXTURE_2D, ret);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, NULL);

	delete [] data;

	return ret;
}
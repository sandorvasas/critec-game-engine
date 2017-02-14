#include "Bloom.h"

const char sBlur[] =
{
	"ßV"
	"uniform float rx, ry;"
	"void main() {"
	" gl_Position = ftransform();"
	" rx = 1.0/rx;"
	" ry = 1.0/ry;"
	" gl_TexCoord[0].st = vec2(gl_MultiTexCoord0.s - rx, gl_MultiTexCoord0.t);"
	" gl_TexCoord[1].st = vec2(gl_MultiTexCoord0.s + rx, gl_MultiTexCoord0.t);"
	" gl_TexCoord[2].st = vec2(gl_MultiTexCoord0.s,		gl_MultiTexCoord0.t - ry);"
	" gl_TexCoord[3].st = vec2(gl_MultiTexCoord0.s,		gl_MultiTexCoord0.t + ry);"
	"}"

	"ßF"
	"uniform sampler2D tex;"
	"void main() {"
	" vec4 s1 = texture2D(tex, gl_TexCoord[0].st);"
	" vec4 s2 = texture2D(tex, gl_TexCoord[1].st);"
	" vec4 s3 = texture2D(tex, gl_TexCoord[2].st);"
	" vec4 s4 = texture2D(tex, gl_TexCoord[3].st);"
	" gl_FragColor = (s1 + s2 + s3 + s4) / 8.0;"
	"}"
};

const char sBloom[] = 
{
	"ßV"
	"void main() {"
	"gl_Position = ftransform();"
	"gl_TexCoord[0].st = gl_MultiTexCoord0.st;"
	"}"

	"ßF"
	"uniform sampler2D tex;"
	"void main() {"
	" vec3 t = texture2D(tex, gl_TexCoord[0].st).rgb;"
	//" t = (pow(t, vec3(2.0)) - vec3(0.0, 0.2, 0.2)) * 3.0;"
	" t = pow(t*1.1, 1.2);"
	" gl_FragColor = vec4(t, 1.0);"
	"}"
};

crBloomFilter::crBloomFilter( void ) {

	Blur.LoadFromSource((char*)sBlur);
	Bloom.LoadFromSource((char*)sBloom);

	tempBuf.Generate(BLOOM_WIDTH, BLOOM_HEIGHT, 0);
	bloomImage.Generate(BLOOM_WIDTH, BLOOM_HEIGHT, 0);
}

crBloomFilter::~crBloomFilter( void ) {
}

void crBloomFilter::BloomImage( crFrameBuffer2D frame ) {

	glViewport(0,0, BLOOM_WIDTH, BLOOM_HEIGHT);
	tempBuf.Bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
				glOrtho(-1, 1, 1, -1, 0, 1);
				glLoadIdentity();

				glPushMatrix();
				glScaled(1.025, 1.025, 1.025);
				Blur.Activate();
				glUniform1f(Blur.UniformLoc("rx"), (float)BLOOM_WIDTH);
				glUniform1f(Blur.UniformLoc("ry"), (float)BLOOM_HEIGHT);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, frame.texture);
					glBegin(GL_QUADS);
						glMultiTexCoord2f(GL_TEXTURE0, 0.f, 0.f);	glVertex3d( -1, -1, 0.0 );
						glMultiTexCoord2f(GL_TEXTURE0, 1.f, 0.f);	glVertex3d(  1, -1, 0.0 );
						glMultiTexCoord2f(GL_TEXTURE0, 1.f, 1.f);	glVertex3d(  1,  1, 0.0 );
						glMultiTexCoord2f(GL_TEXTURE0, 0.f, 1.f);	glVertex3d( -1,  1, 0.0 );
					glEnd();
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, 0);
				Blur.Deactivate();
				glPopMatrix();

			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);

	tempBuf.Unbind();
	
	bloomImage.Bind();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
				glOrtho(-1, 1, 1, -1, 0, 1);
				glLoadIdentity();

				glPushMatrix();
				Bloom.Activate();
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, tempBuf.texture);
					glBegin(GL_QUADS);
						glMultiTexCoord2f(GL_TEXTURE0, 0.f, 0.f);	glVertex3d( -1.0, -1.0, 0.0 );
						glMultiTexCoord2f(GL_TEXTURE0, 1.f, 0.f);	glVertex3d(  1.0, -1.0, 0.0 );
						glMultiTexCoord2f(GL_TEXTURE0, 1.f, 1.f);	glVertex3d(  1.0,  1.0, 0.0 );
						glMultiTexCoord2f(GL_TEXTURE0, 0.f, 1.f);	glVertex3d( -1.0,  1.0, 0.0 );
					glEnd();
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, 0);
				Bloom.Deactivate();
				glPopMatrix();

			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);

	bloomImage.Unbind();
	glViewport(0,0, frame.width, frame.height);
}


unsigned int crBloomFilter::GetBlurredImage( void ) {
	return tempBuf.texture;
}

unsigned int crBloomFilter::GetBloomImage( void ) {
	return bloomImage.texture;
}
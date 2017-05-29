



#ifndef TEXTURE_H
#define TEXTURE_H

#include "platform.h"
#include "math/vec2i.h"

class Texture
{
public:
	unsigned int texname;
	std::string fullpath;
	bool loaded;
	int32_t width, height;
	bool transp;
	bool sky;
	bool breakable;
	bool passthru;
	bool grate;
	bool ladder;
	bool water;
	bool fabric;
	bool clamp;
	bool mipmaps;

	Texture()
	{
		fullpath = '\0';
		loaded = false;
	}
};

//#define TEXTURES	4096
#define TEXTURES 40096
extern Texture g_texture[TEXTURES];

#define TGA_RGB		 2		// This tells us it's a normal RGB (really BGR) file
#define TGA_A		 3		// This tells us it's an ALPHA file
#define TGA_RLE		10		// This tells us that the targa is Run-Length Encoded (RLE)

#ifndef int_p_NULL
#define int_p_NULL (int32_t*)NULL
#endif
#define png_infopp_NULL (png_infopp)NULL
#define png_voidp_NULL	(png_voidp)NULL

#define JPEG_BUFFER_SIZE (8 << 10)

typedef struct
{
	struct jpeg_source_mgr  pub;
} JPEGSource;

class LoadedTex
{
public:
	int32_t channels;			// The channels in the image (3 = RGB : 4 = RGBA)
	int32_t sizex;				// The width of the image in pixels
	int32_t sizey;				// The height of the image in pixels
	unsigned char *data;	// The image pixel data

	void destroy();
	LoadedTex();
	~LoadedTex();
};

struct TextureToLoad
{
	uint32_t* ptexindex;
	uint32_t texindex;
	char relative[DMD_MAX_PATH+1];
	bool clamp;
	bool reload;
	bool mipmaps;
};

extern std::vector<TextureToLoad> g_texload;

extern int32_t g_texwidth;
extern int32_t g_texheight;
//extern int32_t g_texindex;
extern int32_t g_lastLTex;

LoadedTex *LoadBMP(const char *fullpath);
LoadedTex *LoadTGA(const char *fullpath);
void DecodeJPG(jpeg_decompress_struct* cinfo, LoadedTex *pImageData);
LoadedTex *LoadJPG(const char *fullpath);
LoadedTex *LoadPNG(const char *fullpath);
bool FindTexture(uint32_t &texture, const char* relative);
int32_t NewTexture();
bool TextureLoaded(uint32_t texture, const char* relative, bool transp, bool clamp, bool mipmaps, uint32_t& texindex);
void FindTextureExtension(char *relative);
void FreeTextures();
bool Load1Texture();
void QueueTex(uint32_t* texindex, const char* relative, bool clamp, bool mipmaps);
void RequeueTexture(uint32_t texindex, const char* relative, bool clamp, bool mipmaps);
LoadedTex* LoadTexture(const char* full);
bool CreateTex(LoadedTex* pImage, unsigned int* texname, bool clamp, bool mipmaps);
bool CreateTex(uint32_t &texindex, const char* relative, bool clamp, bool mipmaps, bool reload=false);
void ReloadTextures();
void FreeTexture(const char* relative);
void FreeTexture(int32_t i);
void DiffPath(const char* basepath, char* diffpath);
void DiffPathPNG(const char* basepath, char* diffpath);
void SpecPath(const char* basepath, char* specpath);
void NormPath(const char* basepath, char* normpath);
void OwnPath(const char* basepath, char* ownpath);
void AllocTex(LoadedTex* empty, int32_t width, int32_t height, int32_t channels);
void Blit(LoadedTex* src, LoadedTex* dest, Vec2i pos);
void SaveJPEG(const char* fullpath, LoadedTex* image, float quality);
int32_t SavePNG(const char* fullpath, LoadedTex* image);
void FlipImage(LoadedTex* image);
int32_t SaveBMP(const char* fullpath, LoadedTex* image);
bool SaveRAW(const char* fullpath, LoadedTex* image);
void Resample(LoadedTex* original, LoadedTex* empty, Vec2i newdim);
void Extract(LoadedTex* original, LoadedTex* empty, int32_t x1, int32_t y1, int32_t x2, int32_t y2);

#endif

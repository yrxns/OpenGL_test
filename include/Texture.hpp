#ifndef __TEXTURE__
#define __TEXTURE__

#include <string>

class Shader;

class Texture {
public:
	Texture(const std::string& path, unsigned int unit, Shader *shader, const std::string& sampler2D);
	~Texture();

    void bind();

    operator int() {
        return mTexture;
    }

private:
	unsigned int mTexture{ 0 };
	int mWidth{ 0 };
	int mHeight{ 0 };

    // 激活的纹理单元
	unsigned int mUnit{ 0 };
};

#endif
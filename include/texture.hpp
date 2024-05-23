#ifndef __TEXTURE__
#define __TEXTURE__

#include "core.hpp"
#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Texture_load {
public:
	Texture_load(const std::string& path, unsigned int unit,
			int min_filter = GL_LINEAR_MIPMAP_LINEAR, int mag_filter = GL_LINEAR,
			int wrap_s = GL_REPEAT, int wrap_t = GL_REPEAT) {
            mUnit = unit;

            // 生成纹理
            glGenTextures(1, &mTexture);
            //--激活纹理单元--
            glActiveTexture(GL_TEXTURE0 + mUnit);
            //--绑定纹理对象--
            glBindTexture(GL_TEXTURE_2D, mTexture);

            // 设置纹理的过滤方式
            /******************************************************
             * @ GL_NEAREST          : 邻近过滤。OpenGL默认的纹理过滤方式。
             * @ GL_LINEAR           : 线性过滤。它会基于纹理坐标附近的纹理像素，计算出一个插值，近似出这些纹理像素之间的颜色。
             * 
             * 多级渐远纹理
             * @ GL_NEAREST_MIPMAP_NEAREST      : 使用最邻近的多级渐远纹理来匹配像素大小，并使用邻近插值进行纹理采样
             * @ GL_LINEAR_MIPMAP_NEAREST       : 使用最邻近的多级渐远纹理级别，并使用线性插值进行采样
             * @ GL_NEAREST_MIPMAP_LINEAR       : 在两个最匹配像素大小的多级渐远纹理之间进行线性插值，使用邻近插值进行采样
             * @ GL_LINEAR_MIPMAP_LINEAR        : 在两个邻近的多级渐远纹理之间使用线性插值，并使用线性插值进行采样
             *******************************************************/

            /*
            一个常见的错误是，将放大过滤的选项设置为多级渐远纹理过滤选项之一。
            这样没有任何效果，因为多级渐远纹理主要是使用在纹理被缩小的情况下的：纹理放大不会使用多级渐远纹理，
            为放大过滤设置多级渐远纹理的选项会产生一个GL_INVALID_ENUM错误代码。
            */
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);

            // 设置纹理的环绕方式
            /******************************************************
             * @ GL_REPEAT          : 对纹理的默认行为。重复纹理图像。
             * @ GL_MIRRORED_REPEAT ：和GL_REPEAT一样，但每次重复图片是镜像放置的。
             * @ GL_CLAMP_TO_EDGE   ：纹理坐标会被约束在0到1之间，超出的部分会重复纹理坐标的边缘，产生一种边缘被拉伸的效果。
             * @ GL_CLAMP_TO_BORDER : 超出的坐标为用户指定的边缘颜色。
             *******************************************************/
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);//u
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);//v

            // 如果设置了GL_CLAMP_TO_BORDER，指定边缘颜色
            if (wrap_s == GL_CLAMP_TO_BORDER || wrap_t == GL_CLAMP_TO_BORDER) {
                float borderColor[] = { 1.0f, 0.0f, 0.0f, 0.0f };
                glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
            }

            // 加载并生成纹理
            int channels;

            //--反转y轴
            stbi_set_flip_vertically_on_load(true);

            unsigned char* data = stbi_load(path.c_str(), &mWidth, &mHeight, &channels, 0);
            std::cout << "channels: " << channels << std::endl;
            if (data) {
                GLenum format;
                if (channels == 1)
                    format = GL_RED;
                else if (channels == 3)
                    format = GL_RGB;
                else if (channels == 4)
                    format = GL_RGBA;
                // 传输纹理数据,开辟显存
                glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, data);
                // 自动生成所有需要的多级渐远纹理
                glGenerateMipmap(GL_TEXTURE_2D);
            } else {
                std::cout << "Failed to load texture" << std::endl;
            }

            // 释放数据
            stbi_image_free(data);
    }
	~Texture_load() {
        if (mTexture != 0) {
            glDeleteTextures(1, &mTexture);
        }
    }

    void bind() {
        //--激活纹理单元--
        glActiveTexture(GL_TEXTURE0 + mUnit);
        //--绑定纹理对象--
        glBindTexture(GL_TEXTURE_2D, mTexture);
    }

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
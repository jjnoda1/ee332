#include <iostream>
#include <fstream>
#include <vector>
#include "bmp.h"

Color::Color():r(0), g(0), b(0)
{
}

Color::Color(float r, float g, float b): r(r), g(g), b(b)
{
}

Color::~Color()
{
}

Image::Image(): m_width(0), m_height(0), m_colors(std::vector<Color>(0))
{
}

Image::Image(int width, int height): m_width(width), m_height(height), m_colors(std::vector<Color>(width * height))
{
}

Image::~Image()
{
}

Color Image::GetColor(int x, int y) const
{
    return m_colors[y * m_width + x];
}

void Image::SetColor(const Color& color, int x, int y)
{
    m_colors[y*m_width + x].r = color.r;
    m_colors[y*m_width + x].g = color.g;
    m_colors[y*m_width + x].b = color.b;
}

void Image::Read(const char* path)
{
    std::ifstream f;
    f.open(path, std::ios::in | std::ios::binary);

    if (!f.is_open())
    {
        std::cout << "File could not be opened" << std::endl;
        return;
    }

    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;

    unsigned char fileHeader[fileHeaderSize];
    f.read(reinterpret_cast<char*>(fileHeader), fileHeaderSize);

    if (fileHeader[0] != 'B' || fileHeader[1] != 'M')
    {
        std::cout << "The specified path is not a bitmap image" << std::endl;
        f.close();
        return;
    }

    unsigned char infoHeader[informationHeaderSize];
    f.read(reinterpret_cast<char*>(infoHeader), informationHeaderSize);

    // int fileSize = fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4] << 16) + (fileHeader[5] << 24);
    m_width = infoHeader[4] + (infoHeader[5] << 8) + (infoHeader[6] << 16) + (infoHeader[7] << 24);
    m_height = infoHeader[8] + (infoHeader[9] << 8) + (infoHeader[10] << 16) + (infoHeader[11] << 24);
    
    m_colors.resize(m_width * m_height);

    const int paddingAmount = ((4 - (m_width * 3) % 4) % 4);

    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            unsigned char color[3];
            f.read(reinterpret_cast<char*>(color), 3);

            m_colors[y * m_width + x].r = static_cast<float>(color[2]) / 255.0f;
            m_colors[y * m_width + x].g = static_cast<float>(color[2]) / 255.0f;
            m_colors[y * m_width + x].b = static_cast<float>(color[2]) / 255.0f;
        }
        f.ignore(paddingAmount);
    }
    f.close();

    std::cout << "file read" << std::endl;
}

int Image::imageHeight(void)
{
    return m_height;
}

int Image::imageWidth(void)
{
    return m_width;
}
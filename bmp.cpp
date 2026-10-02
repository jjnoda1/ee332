// bmp.cpp: These are the functions that take in information such as color and size from a .bmp file

#include <iostream>
#include <fstream>
#include <vector>
#include "bmp.h"

// Default constructor
Color::Color():r(0), g(0), b(0)
{
}

Color::Color(float r, float g, float b): r(r), g(g), b(b)
{
}

// Destructor
Color::~Color()
{
}

// Default Image class constructor
Image::Image(): m_width(0), m_height(0), m_colors(std::vector<Color>(0))
{
}

Image::Image(int width, int height): m_width(width), m_height(height), m_colors(std::vector<Color>(width * height))
{
}


// Destructor
Image::~Image()
{
}

// GetColor: gets the color of a pixel; returns it as a Color struct
Color Image::GetColor(int x, int y) const
{
    return m_colors[y * m_width + x];
}

// SetColor: sets the color of a pixel (not used in this assignment)
void Image::SetColor(const Color& color, int x, int y)
{
    m_colors[y*m_width + x].r = color.r;
    m_colors[y*m_width + x].g = color.g;
    m_colors[y*m_width + x].b = color.b;
}

// Read: opens and reads the pixels of a .bmp file; stores the colors in a vector of Color structs in the Image class
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

// imageHeight: returns the height of the image
int Image::imageHeight(void)
{
    return m_height;
}

// imageWidth: returns the width of an image
int Image::imageWidth(void)
{
    return m_width;
}

// checkBinary: checks whether the pixel is black or white; returns true if black, false if white
bool Image::checkBinary(int x, int y)
{
    if (x < 0 || y < 0) return false;
    Color blockColor = Image::GetColor(x, y);
    float colorAvg = (blockColor.r + blockColor.g + blockColor.b)/3;
    if (colorAvg >= 0.9) return true; // simple threshold as color should not be above 0.9 or else it would appear grey
    else return false;
}

int Image::checkNeighborLabel(std::vector<std::unordered_set<int>> * labels)
{

}

void Image::putLabel(int x, int y, std::vector<std::unordered_set<int>> * labels)
{
    if (Image::checkBinary(x, y) == true)
    {
        // TODO: check its neighbors sets for a label, then assign it a set.
        // Don't need to check if it is a member of its own set because of raster scanning.
    }
}

// TODO: check the neighbor's sets

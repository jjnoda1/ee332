// bmp.h: This is the header file for the functions in bmp.cpp

#ifndef BMP_H
#define BMP_H

#include<unordered_set>
#include <vector>
#include <unordered_map>

// Color: this is a struct to store the data of the color of each pixel in
struct Color {
    float r, g, b;

    Color();
    Color(float r, float g, float b);
    ~Color();
};

// Image: this is a class that stores all of the functions to take in data from an image
class Image
{
    public:
        Image();
        Image(int width, int height);
        ~Image();

        Color GetColor(int x, int y) const;
        void SetColor(const Color& color, int x, int y);

        void Read(const char* path);
        // void Export(const char* path) const;
        int imageWidth(void);

        int imageHeight(void);

        

        void putLabel(int x, int y);

    private:
        int m_width;
        int m_height;
        std::vector<Color> m_colors;   
        bool checkBinary(int x, int y);
        int checkLabel(int x, int y);
        int Image::findPixel(int pixel);
        std::vector<std::unordered_set<int>> labels;
        std::unordered_map<int, int> m_setOf;
};

#endif
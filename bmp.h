#ifndef BMP_H
#define BMP_H

#include <vector>

struct Color {
    float r, g, b;

    Color();
    Color(float r, float g, float b);
    ~Color();
};

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

    private:
        int m_width;
        int m_height;
        std::vector<Color> m_colors;
};

#endif
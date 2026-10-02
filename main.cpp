#include <iostream>
#include <string>
#include "bmp.h"

int main()
{
    Image new_image;

    const char* image_path = "test.bmp";

    new_image.Read(image_path);
    int h = new_image.imageHeight();
    int w = new_image.imageWidth();

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            Color color1 = new_image.GetColor(i, j);
            std::vector<float> colorVec = {color1.r, color1.g, color1.b};

            for (const auto& element : colorVec) 
            {
                std::cout << element << " ";
            }

            std::cout << "\n";
        }
    }


    return(0);
}

#include <iostream>
#include <string>
#include <vector>
#include "bmp.h"

int main()
{
    Image new_image;

    const char* image_path = "test.bmp";

    new_image.Read(image_path);
    int h = new_image.imageHeight();
    int w = new_image.imageWidth();

    std::vector<std::unordered_set<int>> labels;
    int label_val = 0;
    std::unordered_set<int> label1;
    labels.push_back(label1);

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            new_image.putLabel(i, j, &labels);

        }
    }


    return(0);
}

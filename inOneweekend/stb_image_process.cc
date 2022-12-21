
#define STB_IMAGE_IMPLEMENTATION
#include "stb-master/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb-master/stb_image_write.h"

int main(void)
{
    int width, height, channels;
    unsigned char *img = stbi_load("image.ppm", &width, &height, &channels, 0);
    printf("loaded image");
    stbi_write_jpg("image.jpg", width, height, channels, img, 90);
    stbi_image_free(img);


}
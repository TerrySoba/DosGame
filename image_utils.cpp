#include "image_utils.h"

std::shared_ptr<BITMAP> loadBitmap(const char* filename, RGB* pal)
{
    auto bitmap = load_bitmap(filename, pal);

    if (!bitmap)
    {
        throw std::runtime_error("Could not load image file.");
    }

    auto deleter = [](auto ptr) {destroy_bitmap(ptr);};
    return std::shared_ptr<BITMAP>(bitmap, deleter);
}

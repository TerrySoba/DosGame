#include "image_utils.h"

#include "logging.h"

namespace dos_game
{

std::shared_ptr<BITMAP> loadBitmap(const char* filename, RGB* pal)
{
    auto bitmap = load_bitmap(filename, pal);

    if (!bitmap)
    {
        THROW_EXCEPTION("Could not load image file: " << filename);
    }

    auto deleter = [](auto ptr) {destroy_bitmap(ptr);};
    return std::shared_ptr<BITMAP>(bitmap, deleter);
}


}


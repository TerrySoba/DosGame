#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

#include <allegro.h>
#include <memory>

std::shared_ptr<BITMAP> loadBitmap(const char* filename, RGB* pal = nullptr);

#endif // IMAGE_UTILS_H

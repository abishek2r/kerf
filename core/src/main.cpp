#include <cstdint>
#include <cstring>
#include <utility>
#include <cstddef>
int main()
{
    return 0;
}
class Image{

    std::size_t width;
    std::size_t height;
    std::uint8_t* pixels;
public:
    Image(std::size_t width_,std::size_t height_) : (width(width_),height(height_),pixels(new std::uint_8[width_*height_*3])){}
    ~Image(){
        delete[] pixels;
    }

    Image(const Image& other) : width(other.width),height(other.height),pixels(new std::uint8_t other.pixels){
        std::memcpy(pixels,other.pixels,width*height*3);
    }

    Image& operator=(const Image& other){
        if (this != &other){

            auto* new_pixels = new std::uint8_t[other.width * other.height * 3];
            width = other.width;
            height = other.height;
            std::memcpy(new_pixels,other.pixels,width*height*3);
            pixels = new_pixels;
            delete[] new_pixels;

        }
        return *this;
        
    }
    Image(Image&& other) noexcept : width(other.width),height(other.height),pixels(other.pixels){
        other.width=0;
        other.height = 0;
        other.pixels=nullptr;
    }
    Image& operator=(Image&& other) noexcept
    {
        if (this != &other){
            delete[] pixels;
            pixels = other.pixels;
            width = other.width;
            height = other.height;

            other.pixels=nullptr;
            other.height=0;
            other.width = 0;
        }
    }

}
#include <cstdint>
#include <cstring>
#include <utility>
#include <cstddef>
#include <iostream>
#include <chrono>
template <typename T>
double benchmark(T t,int iterations){
    auto totaltime = 0.0;

    for (int i=0;i<iterations;i++){
        auto start = std::chrono::steady_clock::now();
        t();
        auto end = std::chrono::steady_clock::now();
        auto avgTime = std::chrono::duration<double,std::nano>(end - start);
        totaltime += avgTime.count();
    }
    auto avgTime = totaltime/iterations;
    return avgTime;
};
class Image{
    
    std::size_t width;
    std::size_t height;
    std::uint8_t* pixels;
    public:
    Image(std::size_t width_,std::size_t height_) : width(width_),height(height_),pixels(new std::uint8_t[width_*height_*3]){}
    ~Image(){
        delete[] pixels;
    }
    
    Image(const Image& other) : width(other.width),height(other.height),pixels(new std::uint8_t[other.width * other.height * 3]){
        std::memcpy(pixels,other.pixels,other.width*other.height*3);
    }
    
    Image& operator=(const Image& other){
        if (this != &other){
            
            auto* new_pixels = new std::uint8_t[other.width * other.height * 3];
            std::memcpy(new_pixels,other.pixels,other.width*other.height*3);
            width = other.width;
            height = other.height;
            delete[] pixels;
            pixels = new_pixels;
            
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
        return *this;
    }
    
};
int main()
{   Image a(10000,10000);
    auto copy_time = benchmark([&]{Image copy(a);},1);
    auto moved_time = benchmark([&]{Image moved(std::move(a));},1);
    std::cout << "Copy: " << copy_time << " ns\n";
    std::cout << "Move: " << moved_time << " ns\n";
    return 0;
};
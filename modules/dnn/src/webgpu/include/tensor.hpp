#ifndef OPENCV_DNN_WEBGPU_TENSOR_HPP
#define OPENCV_DNN_WEBGPU_TENSOR_HPP
// #ifdef HAVE_WEBGPU
#include<dawn/webgpu_cpp.h>
// #endif
#include"buffer.hpp"
#include"wgpucom.hpp"
#include<memory>
namespace cv { namespace dnn { namespace webgpu {
// #ifdef HAVE_WEBGPU
class Buffer;
class Tensor{
public:
    Tensor(Format fmt = wFormatFp32);
    Tensor(const char* data, size_t size_in_byte, wgpu::BufferUsage usage, Format fmt = wFormatFp32);  //uniform buffer
    Tensor(const char* data, std::vector<int>& shape, wgpu::BufferUsage usage, Format fmt = wFormatFp32);
    void* map();
    void unMap();
    Shape getShape() const;
    int dimSize(const int dim) const;
    int dimNum() const;
    int count(const int start_axis = 0, const int end_axis = -1) const;
    // Change shape and format to as passed in.
    // Copy data if data != NULL
    // Allocate new internal buffer if new size > old size or alloc flag is true
    Tensor reshape(const void* data, const std::vector<int>& shape, bool alloc = false, Format fmt = wFormatInvalid);
    Tensor setUniform(const void * data, Format fmt = wFormatInt32);
    int getFormat() const;
    size_t size() const { return size_in_byte_; }
    bool isEmpty() { return size_in_byte_ == 0 ? true : false; }
    void copyTo(Tensor& dst);
    std::shared_ptr<Buffer> getBuffer() { return buffer_; }
    void mapReadAsync(void* result);
private:
    std::shared_ptr<wgpu::Device> device_;
    std::vector<int> shape_;
    size_t size_in_byte_;
    std::shared_ptr<Buffer> buffer_;
    Format format_;
    wgpu::BufferUsage usage_;
};

// #endif  //HAVE_WEBGPU

}}}  //namespace cv::dnn:webgpu

#endif  //  OPENCV_DNN_WEBGPU_TENSOR_HPP
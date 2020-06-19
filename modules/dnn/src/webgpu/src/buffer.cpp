#include "../include/buffer.hpp"
#include "../dawn/dawnUtils.hpp"

namespace cv { namespace dnn { namespace webgpu {
// #ifdef HAVE_WEBGPU

Buffer::Buffer(std::shared_ptr<wgpu::Device> device){
    device_ =  device;
    usage_ = wgpu::BufferUsage::Storage;
    bufferMapped_->buffer = nullptr;
    bufferMapped_->dataLength = 0;
    bufferMapped_->data = nullptr;
}

Buffer::Buffer(std::shared_ptr<wgpu::Device> device, const void* data, size_t size, wgpu::BufferUsage usage) {
    device_ = device;
    usage_ = usage;
    bufferMapped_ = std::make_shared<wgpu::CreateBufferMappedResult>(CreateBufferMappedFromData(* device_, data, size, usage_));
}

//steSubdata which is used in tfjs
// Buffer::Buffer(const wgpu::Device& device, const void* data, size_t size, wgpu::BufferUsage usage) {
//     device_ = device;
//     usage_ = usage | wgpu::BufferUsage::CopyDst;
//     buffer_ = CreateBufferFromData(device_, data, size, usage_);
// }

// #endif  //HAVE_WEBGPU

}}}  //namespace cv::dnn::webgpu

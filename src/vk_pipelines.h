#pragma once 
#include <vk_types.h>

namespace vkutil 
{
	bool load_shader_module(const char* filePath, VkDevice device, VkShaderModule* outShaderModule);

};

class PipelineBuilder 
{
public:
	//basically a memeber for each variable of VkGraphicsPipelineCreateInfo
    std::vector<VkPipelineShaderStageCreateInfo> _shaderStages; //use data of this for pStages
    VkPipelineInputAssemblyStateCreateInfo _inputAssembly;
    VkPipelineRasterizationStateCreateInfo _rasterizer;
    VkPipelineColorBlendAttachmentState _colorBlendAttachment;
    VkPipelineMultisampleStateCreateInfo _multisampling;
    VkPipelineLayout _pipelineLayout;
    VkPipelineDepthStencilStateCreateInfo _depthStencil;
    VkPipelineRenderingCreateInfo _renderInfo; //for dynamic rendering
    VkFormat _colorAttachmentformat;

	PipelineBuilder(){ clear(); }

    void clear();
	void set_shaders(VkShaderModule vertexShader, VkShaderModule fragmentShader); //_shaderStages
	void set_input_topology(VkPrimitiveTopology topology); //_inputAssembly
	void set_polygon_mode(VkPolygonMode mode); //_rasterizer
	void set_cull_mode(VkCullModeFlags cullMode, VkFrontFace frontFace); //_rasterizer
	void set_multisampling_none(); //_multisampling
	void disable_blending(); //_colorBlendAttachment
	void set_color_attachment_format(VkFormat format); // _renderInfo, _colorAttachmentformat
	void set_depth_format(VkFormat format); //_renderInfo
	void disable_depthtest(); //_depthStencil

    VkPipeline build_pipeline(VkDevice device);
};
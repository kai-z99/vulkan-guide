#pragma once

#include <vk_types.h>

struct DescriptorLayoutBuilder 
{
    std::vector<VkDescriptorSetLayoutBinding> bindings;

    void add_binding(uint32_t binding, VkDescriptorType type);
    void clear();
    VkDescriptorSetLayout build(VkDevice device, VkShaderStageFlags shaderStages, void* pNext = nullptr, VkDescriptorSetLayoutCreateFlags flags = 0);
};

struct DescriptorAllocator 
{
    struct PoolSizeRatio //one for each type.
    {
		VkDescriptorType type; //eg uniform buffer
		float ratio;	       //How many of that type per set. eg 1.0f means 1 per set
    };

    VkDescriptorPool pool;

    //maxSets is how many descriptor sets we can create from the pool.
    void init_pool(VkDevice device, uint32_t maxSets, std::span<PoolSizeRatio> poolRatios);
    void clear_descriptors(VkDevice device);
    void destroy_pool(VkDevice device);

    VkDescriptorSet allocate(VkDevice device, VkDescriptorSetLayout layout);
};
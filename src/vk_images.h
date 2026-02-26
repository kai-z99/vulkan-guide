
#pragma once 

namespace vkutil {

	//records image memory barrier into command buffer.
	void transition_image(VkCommandBuffer cmd, VkImage image, VkImageLayout currentLayout, VkImageLayout newLayout);
};
#include <vk_images.h>
#include <vk_initializers.h>

void vkutil::transition_image(VkCommandBuffer cmd, VkImage image, VkImageLayout currentLayout, VkImageLayout newLayout)
{
	//set up the barrier object
    VkImageMemoryBarrier2 imageBarrier {.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2};
    imageBarrier.pNext = nullptr;

    //assume any previous command stage could have written memory
    imageBarrier.srcStageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT; //Which earlier gpu work must finish before this barrier? (ANYTHING)
    imageBarrier.srcAccessMask = VK_ACCESS_2_MEMORY_WRITE_BIT; //Specfically WRITES.
    //assume any later command stage may read or write memory
    imageBarrier.dstStageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT; //Whcih later GPU work must wait until after the barrier? (ANYTHING)
    imageBarrier.dstAccessMask = VK_ACCESS_2_MEMORY_WRITE_BIT | VK_ACCESS_2_MEMORY_READ_BIT; //Specifically READs or WRITEs

    //change the layout
    imageBarrier.oldLayout = currentLayout;
    imageBarrier.newLayout = newLayout;

    //Set the range of the image we are transitioning (mips/layers). In this case we say all mips and layers.-----
    //which part of the image are we transitioning? If we are transition to a depth attachment layout,
    //guess that its a depth image. Otherwise assume its a color image. (this is dangerous)
    VkImageAspectFlags aspectMask = (newLayout == VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL) ? VK_IMAGE_ASPECT_DEPTH_BIT : VK_IMAGE_ASPECT_COLOR_BIT;
    imageBarrier.subresourceRange = vkinit::image_subresource_range(aspectMask); //all mips and layers
    imageBarrier.image = image;

    // Insert the barrier into the command buffer
    VkDependencyInfo depInfo {};
    depInfo.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
    depInfo.pNext = nullptr;
    depInfo.imageMemoryBarrierCount = 1;
    depInfo.pImageMemoryBarriers = &imageBarrier;

    vkCmdPipelineBarrier2(cmd, &depInfo);
}


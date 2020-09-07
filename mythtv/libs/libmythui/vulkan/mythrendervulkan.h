#ifndef MYTHRENDERVULKAN_H
#define MYTHRENDERVULKAN_H

// Qt
#include <QVulkanWindowRenderer>
#include <QVulkanDeviceFunctions>

// MythTV
#include "mythuiexp.h"
#include "mythrender_base.h"

class MythImage;
class MythRenderVulkan;
class MythWindowVulkan;
class MythShaderVulkan;
class MythTextureVulkan;

class MythVulkanObject
{
  public:
    static MythVulkanObject* Create(MythRenderVulkan* Render);
    MythVulkanObject(MythRenderVulkan* Render, VkDevice Device, QVulkanDeviceFunctions* Functions);
    MythVulkanObject(MythRenderVulkan* Render, VkDevice Device, QVulkanDeviceFunctions* Functions, MythWindowVulkan* Window);

    bool                    IsValid();
    MythRenderVulkan*       Render ();
    VkDevice                Device ();
    QVulkanDeviceFunctions* Funcs  ();
    MythWindowVulkan*       Window ();

  protected:
    bool                    m_valid    { true    };
    MythRenderVulkan*       m_render   { nullptr };
    VkDevice                m_device   { nullptr };
    QVulkanDeviceFunctions* m_devFuncs { nullptr };
    MythWindowVulkan*       m_window   { nullptr };

  private:
    Q_DISABLE_COPY(MythVulkanObject)
};

class MUI_PUBLIC MythRenderVulkan : public QObject, public QVulkanWindowRenderer, public MythRender
{
    Q_OBJECT

  public:

    static MythRenderVulkan* GetVulkanRender(void);

    MythRenderVulkan();
   ~MythRenderVulkan() override;

    void SetVulkanWindow           (MythWindowVulkan *VulkanWindow);
    MythWindowVulkan* GetVulkanWindow(void);
    void SetFrameExpected          (void);
    bool GetFrameExpected          (void) const;
    bool GetFrameStarted           (void) const;
    void EndFrame                  (void);
    QStringList GetDescription(void) override;

    void preInitResources          (void) override;
    void initResources             (void) override;
    void initSwapChainResources    (void) override;
    void releaseSwapChainResources (void) override;
    void releaseResources          (void) override;
    void startNextFrame            (void) override;
    void physicalDeviceLost        (void) override;
    void logicalDeviceLost         (void) override;

    bool            CreateImage(QSize Size, VkFormat Format, VkImageTiling Tiling,
                                VkImageUsageFlags Usage, VkMemoryPropertyFlags Properties,
                                VkImage& Image, VkDeviceMemory& ImageMemory);
    void            TransitionImageLayout(VkImage &Image, VkImageLayout OldLayout,
                                          VkImageLayout NewLayout, VkCommandBuffer CommandBuffer = nullptr);
    void            CopyBufferToImage(VkBuffer Buffer, VkImage Image,
                                      uint32_t Width, uint32_t Height,
                                      VkCommandBuffer CommandBuffer = nullptr);
    bool            CreateBuffer(VkDeviceSize Size, VkBufferUsageFlags Usage,
                                 VkMemoryPropertyFlags Properties, VkBuffer& Buffer,
                                 VkDeviceMemory& Memory);
    void            CopyBuffer(VkBuffer Src, VkBuffer Dst, VkDeviceSize Size,
                               VkCommandBuffer CommandBuffer = nullptr);
    VkPipeline      CreatePipeline(MythShaderVulkan* Shader, const QRect &Viewport);
    VkCommandBuffer CreateSingleUseCommandBuffer(void);
    void            FinishSingleUseCommandBuffer(VkCommandBuffer &Buffer);
    VkSampler       CreateSampler(VkFilter Min, VkFilter Mag);
    VkPhysicalDeviceFeatures GetPhysicalDeviceFeatures() const;
    VkPhysicalDeviceLimits   GetPhysicalDeviceLimits  () const;

  signals:
    void DoFreeResources    (void);
    void PhysicalDeviceLost (void);
    void LogicalDeviceLost  (void);

  private:
    Q_DISABLE_COPY(MythRenderVulkan)

    std::optional<uint32_t> FindMemoryType(uint32_t Filter, VkMemoryPropertyFlags Properties);

    void BeginFrame                (void);
    void DebugVulkan               (void);

    MythWindowVulkan*  m_window        { nullptr };
    VkDevice           m_device        { nullptr };
    QVulkanFunctions*  m_funcs         { nullptr };
    QVulkanDeviceFunctions *m_devFuncs { nullptr };
    VkPhysicalDeviceFeatures m_phyDevFeatures {  };
    VkPhysicalDeviceLimits   m_phyDevLimits   {  };
    bool               m_frameExpected { false   };
    bool               m_frameStarted  { false   };
    QMap<QString,QString> m_debugInfo;
};

#endif

/*
 * Copyright 2019 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrDawnTexture_DEFINED
#define GrDawnTexture_DEFINED

#include "src/gpu/GrTexture.h"
#include "dawn/webgpu_cpp.h"

class GrDawnGpu;

class GrDawnTexture : public GrTexture {
public:
    static sk_sp<GrDawnTexture> Make(GrDawnGpu*, SkISize dimensions,
                                     wgpu::TextureFormat format, GrRenderable, int sampleCnt,
                                     SkBudgeted, int mipLevels, GrMipmapStatus);

    static sk_sp<GrDawnTexture> MakeWrapped(GrDawnGpu*, SkISize dimensions,
                                            GrRenderable, int sampleCnt,
                                            GrMipmapStatus, GrWrapCacheable, GrIOType,
                                            const GrDawnTextureInfo&);

    ~GrDawnTexture() override;

    GrBackendTexture getBackendTexture() const override;
    GrBackendFormat backendFormat() const override;

    void textureParamsModified() override {}

    void upload(GrColorType, const GrMipLevel texels[], int mipLevels,
                wgpu::CommandEncoder copyEncoder);
    void upload(GrColorType, const GrMipLevel texels[], int mipLevels,
                const SkIRect& dstRect, wgpu::CommandEncoder copyEncoder);

    wgpu::Texture texture() const { return fInfo.fTexture; }
    wgpu::TextureView textureView() const { return fTextureView; }
protected:
    GrDawnTexture(GrDawnGpu*, SkISize dimensions, wgpu::TextureView,
                  const GrDawnTextureInfo&, GrMipmapStatus);

    GrDawnGpu* getDawnGpu() const;

    void onAbandon() override;
    void onRelease() override;

    bool onStealBackendTexture(GrBackendTexture*, SkImage::BackendTextureReleaseProc*) override {
        return false;
    }

private:
    GrDawnTextureInfo        fInfo;
    wgpu::TextureView        fTextureView;

    using INHERITED = GrTexture;
};

#endif

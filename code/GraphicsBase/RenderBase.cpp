//
// Created by caspase on 10/18/2020.
//

#include "RenderBase.h"
#include "Device.h"

RenderBase * RenderBase::get(){
    static RenderBase self = RenderBase();
    return &self;
}
void RenderBase::updateTime(float curTime) {
    currentFrame = curTime;
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void RenderBase::VSYNC(bool on)
{
    Device::VSYNC(on);
}
void RenderBase::MSAA(int msaa) {
    Device::MSAA(msaa);

}
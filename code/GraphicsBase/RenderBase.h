//
// Created by caspase on 10/18/2020.
//

#ifndef EM_RENDERBASE_H
#define EM_RENDERBASE_H


class RenderBase {
public:
    float lastFrame;
    float currentFrame;
    float deltaTime;
public:
    void updateTime(float curTime);
    void VSYNC(bool on);
    void MSAA(int msaa);

    static RenderBase * get();
};


#endif //EM_RENDERBASE_H

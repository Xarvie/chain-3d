#include <iostream>
#include "OpenglHeader.h"
#include <cmath>
#include "Device.h"
#include "RenderBase.h"
#include "Render2D.h"
#include "DeviceResource.h"
#include "PackTool.h"

#include "gui.h"
#if defined(__EMSCRIPTEN__)
#include <GLES3/gl3.h>
#include "emscripten.h"
#include <emscripten/html5.h>
#endif

Render2D r2d;

void main_loop(void*);
#include <iomanip>
#include <iostream>
using namespace std;

/*
 *
 * （ U+0000 – U+007F） 基本拉丁字符
（ U+0000 – U+007F） ASCII 标点符号
（ U+0000 – U+007F） ASCII 数字
（ U+0000 – U+007F） 美元、欧元符号
（ U+0000 – U+007F） 控制符 C0

（ U+0080 – U+00FF） 增补拉丁字符集 1
（ U+0080 – U+00FF） 增补拉丁字符集 1 标点符号
（ U+0080 – U+00FF） 日元、英镑和分币
（ U+0080 – U+00FF） 控制符 C1

（ U+0100 – U+017F） 拉丁字符扩展集 A
（ U+0180 – U+024F） 拉丁字符扩展集 B
（ U+0250 – U+02AF） 国际音标扩展集
（ U+02B0 – U+02FF） 间隔修饰符
（ U+0300 – U+036F） 组合区分标记
（ U+0370 – U+03FF） 希腊文字中的科普特字符
（ U+0370 – U+03FF） 希腊字符
（ U+0400 – U+04FF） 西里尔字符
（ U+0500 – U+052F） 增补西里尔字符
（ U+0530 – U+058F） 亚美尼亚字符
（ U+0590 – U+059F） 希伯来字符
（ U+0600 – U+06FF） 阿拉伯字符
（ U+0700 – U+074F） 叙利亚字符
（ U+0750 – U+077F） 增补阿拉伯字符
（ U+0780 – U+07BF） 塔纳字符
（ U+07C0 – U+07FF） N’Ko
（ U+0900 – U+097F） 梵文字符
（ U+0980 – U+09FF） 孟加拉字符
（ U+0A00 – U+0A7F） 果鲁穆奇字符
（ U+0A80 – U+0AFF） 古吉拉特字符
（ U+0B00 – U+0B7F） 奥里亚字符
（ U+0B80 – U+0BFF） 泰米尔字符
（ U+0C00 – U+0C7F） 泰卢固字符
（ U+0C80 – U+0CFF） 埃纳德字符
（ U+0D00 – U+0D7F） 马拉亚拉姆字符
（ U+0D80 - U+0DFF） 僧伽罗字符
（ U+0E00 – U+0E7F） 泰语字符
（ U+0E80 – U+0EFF） 老挝语字符
（ U+0F00 – U+0FFF） 藏语字符
（ U+1000 – U+109F） 缅甸语字符
（ U+10A0 – U+10FF） 乔治亚风格字母
（ U+1100 – U+11FF） 谚文字母
（ U+1200 – U+137F） 埃塞俄比亚字符
（ U+1380 – U+139F） 增补埃塞俄比亚字符
（ U+1400 – U+167F） 加拿大语字符
（ U+13A0 – U+13FF） 切罗基字符
（ U+1680 – U+169F） 欧甘字符
（ U+16A0 – U+16FF） Runic 字符
（ U+1700 – U+171F） 塔加路字符
（ U+1720 – U+173F） 哈鲁喏字符
（ U+1740 – U+175F） Buhid 字符
（ U+1760 – U+177F） 泰格班瓦字符
（ U+1780 – U+17FF） 高棉字符
（ U+1800 – U+18AF） 蒙古字符
（ U+1900 – U+194F） 林布字符
（ U+1950 – U+197F） 德宏傣文、德傣文，傣讷文字母
（ U+1980 – U+19DF） 新傣泐文字母西双版纳傣文、西傣文，
（ U+19E0 – U+19FF） 高棉符号
（ U+1A00 – U+1A1F） 布吉字符
（ U+1B00 – U+1B7F） 巴厘字符
（ U+1D00 – U+1D7F） 音标扩展集
（ U+1D80 – U+1DBF） 增补音标扩展集
（ U+1DC0 – U+1DFF） 增补组合区分标记
（ U+1E00 – U+1EFF） 附加拉丁字符扩展集
（ U+1F00 – U+1FFF） 希腊字符扩展集

（ U+2000 – U+206F） 通用标点符号
（ U+2000 – U+206F） 排版控制符

（ U+2000 – U+206F） 不可见操作符

（ U+2070 – U+209F） 上标和下标字符
（ U+20A0 – U+20CF） 货币符号
（ U+20A0 – U+20CF） 芬尼
（ U+20D0 – U+20FF） 符号组合区分标记
（ U+2100 – U+214F） 字母类符号
（ U+2100 – U+214F） 马克
（ U+2150 – U+218F） 数字形式字符
（ U+2190 – U+21FF） 箭头符号
（ U+2200 – U+22FF） 数学运算符
（ U+2300 – U+23FF） 综合技术符号
（ U+2400 – U+243F） 控制符图示
（ U+2440 – U+245F） 光学字符识别符号
（ U+2460 – U+24FF） 带圈字母和数字
（ U+2500 – U+257F） 框线绘制符号
（ U+2580 – U+259F） 方形组块图符
（ U+25A0 – U+25FF） 几何图形
（ U+2600 – U+26FF） 综合符号
（ U+2700 - U+27BF） 印刷符号
（ U+27C0 – U+27EF） 综合数学符号集合 A
（ U+27F0 – U+27FF） 增补箭头符号集合 A
（ U+2800 – U+28FF） 盲人点字图符
（ U+2900 – U+297F） 增补箭头符号集合 B
（ U+2980 – U+29FF） 综合数学符号集合 B
（ U+2A00 – U+2AFF） 增补数学运算符
（ U+2B00 – U+2BFF） 综合符号和箭头
（ U+2C00 – U+2C5F） 格拉哥里字符
（ U+2C60 – U+2C7F） 拉丁字符扩展集 C
（ U+2C80 – U+2CFF） 科普特字符
（ U+2D00 – U+2D2F） 增补乔治亚风格字母
（ U+2D30 – U+2D7F） 提非纳字符
（ U+2D80 – U+2DDF） 埃塞俄比亚字符扩展集
（ U+2E00 – U+2E7F） 增补标点符号
（ U+2E80 – U+2EFF） 增补中日韩汉字部首
（ U+2F00 – U+2FDF） 康熙部首
（ U+2FF0 – U+2FFF） 表意文字描述符
（ U+3000 – U+303F） 中日韩标点符号
（ U+3040 – U+309F） 平假名
（ U+30A0 – U+30FF） 片假名
（ U+3100 – U+312F） 汉语拼音字母
（ U+3130 – U+318F） 谚文相容字母
（ U+3190 – U+319F） 汉字注释标记
（ U+31A0 – U+31BF） 汉语拼音字母扩展集
（ U+31C0 – U+31EF） 中日韩汉字笔画
（ U+31F0 – U+31FF） 片假名音标扩展集
（ U+3200 – U+32FF） 带圈中日韩相容表音文字字母和月份符号
（ U+3300 – U+33FF） 中日韩相容符号
（ U+3400 – U+4DBF） 中日韩统一汉字扩展集 A
（ U+4DC0 – U+4DFF） 《易经》六爻符号
（ U+4E00 – U+9FBF） 中日韩统一汉字
（ U+A000 – U+A48F） Yi 音节符号
（ U+A490 – U+A4CF） Yi 字元符号
（ U+A700 – U+A71F） 改进的音标字母
（ U+A720 – U+A7FF） 拉丁字符扩展集 D
（ U+A800 – U+A82F） Syloti Nagri 字符
（ U+A840 – U+A87F） 八思巴字符
（ U+AC00 – U+D7AF） 谚文音节字符
（ U+F900 – U+FAFF） 中日韩相容汉字

（ U+FB00 – U+FB4F） 字母表达形式字符： 拉丁文相关
（ U+FB00 – U+FB4F） 希伯来字母表达形式字符
（ U+FB00 – U+FB4F） 亚美尼亚文字相关

（ U+FB50 – U+FDFF） 阿拉伯表达形式字符集 A
（ U+FB50 – U+FDFF） 里亚尔符号
（ U+FE00 – U+FE0F） 变体选择符
（ U+FE10 – U+FE1F） 竖排标点符号
（ U+FE20 – U+FE2F） 半角组合标记
（ U+FE50 – U+FE6F） 小形式变体字符
（ U+FE70 – U+FEFF） 阿拉伯表达形式字符集 B

（ U+FF00 – U+FFEF） 半角片假名
（ U+FF00 – U+FFEF） 半角谚文字母
（ U+FF00 – U+FFEF） 全角拉丁字母
（ U+FF00 – U+FFEF） 全角 ASCII 标点符号
（ U+FF00 – U+FFEF） 全角 ASCII 数字
（ U+FF00 – U+FFEF） 全角货币符号

（ U+FFF0 – U+FFFF） 专用符号

（ U+10000 – U+1007F） 线状 B 表音字符
（ U+10080 – U+100FF） 线状 B 表意字符
（ U+10100 – U+1013F） 爱琴海数字
（ U+10140 – U+1018F） 古希腊数字
（ U+10300 – U+1032F） 古意大利语字符
（ U+10330 – U+1034F） 哥特字符
（ U+10380 – U+1039F） 乌加里特字符
（ U+103A0 – U+103DF） 古波斯字符
（ U+10400 – U+1044F） 犹他字符
（ U+10450 – U+1047F） 萧伯纳风格字符
（ U+10480 – U+104AF） 奥斯曼字符
（ U+10800 – U+1083F） 塞浦路斯表音字符
（ U+10900 – U+1091F） 腓尼基字符
（ U+10A00 – U+10A5F） Kharoshihi
（ U+12000 – U+123FF） 楔形文字
（ U+12400 – U+1247F） 楔形文字数字和标点符号

（ U+1D000 – U+1D0FF） 拜占庭音乐符号
（ U+1D000 – U+1D0FF） 西方音乐符号

（ U+1D200 – U+1D24F） 古希腊音乐符号
（ U+1D200 – U+1D24F） 古希腊音乐符号
（ U+1D300 – U+1D35F） 《太玄经》符号
（ U+1D360 – U+1D37F） 筹算数字
（ U+1D400 – U+1D4FF） 数学文字符号
（ U+20000 – U+2A6DF） 中日韩统一汉字扩展集 B
（ U+2F800 – U+2FA1F） 增补中日韩相容汉字
（ U+E0000 – U+E007F） 标记符号
（ U+E0100 – U+E01EF） 增补变体选择符
（ U+F0000 – U+FFFFD） 增补私用 A 区
（ U+100000 – U+10FFFD）增补私用 B 区

韩语 AC00-D7AF 1100-11FF 3130-318F
日语 3040-309F 30A0-30FF 31F0-31FF
泰语 0e00-0e7f
越南语 Basic Latin, Latin-1 Supplement, Latin Extended-A, Latin Extended-B, Latin Extended Additional
空格 0020 00A0

 * */
int main(int argc, char** argv) {
//    packResource();


std::cout << __cplusplus << std::endl;
//    int begin = 0x0020;
//    int end = 0x007F;
//    std::vector<char8_t> aaa;
//    aaa.resize(end - begin + 2, 0);
//    for(int i = 0; i < aaa.size()-1; i++)
//    {
//        char8_t vv = i+begin;
//        aaa[i] = vv;
//    }
//    auto fi = fopen("d:\\a.txt", "w+");
//    fwrite(aaa.data(), aaa.size(),1, fi);
//    fclose(fi);
////    //char8_t wcs[] = u8"\U00000000\U00000001\U00000062\U00000063\U0000007F";
//    char8_t wcs2[] = u8"你";
//    printf("%d-%d:[%s][%s]", begin, end, aaa.data(), wcs2);
    DeviceResource::load();

    auto& d = *Device::get();
    auto& r = *RenderBase::get();
    d.init();
    d.createWindow("App",1000, 800, 0, 0);

    r.lastFrame = d.getTime();

    r2d.render2DInit();

    gui::get()->init(d._window->rawPtr);

     r.VSYNC(true);

#ifdef __EMSCRIPTEN__
//    int w = 0, h = 0;
//    emscripten_get_canvas_element_size("#canvas", &w, &h);

    emscripten_set_main_loop_arg(main_loop, NULL, 0, true);
#else
    while(d.running()) main_loop(NULL);
#endif

    return 0;
}

void main_loop(void* arg){
    auto& d = *Device::get();
    auto& r = *RenderBase::get();
    auto& g = *gui::get();
    d.pollEvents();
    const int FPS=1000/60;
    static int _FPS_Timer = 0;
    if(d.getTime()*1000-_FPS_Timer<FPS){
        SDL_Delay(FPS-d.getTime()*1000+_FPS_Timer);
    }
    _FPS_Timer=SDL_GetTicks();
    r.updateTime(d.getTime());

    r2d.render2dDraw();
    g.render();

    d.swapBuffers();
}

#include <iostream>

#include "rtweekend.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

#define MIN(a, b) ((a)<(b) ? (a) : (b))
#define MAX(a, b) ((a)>(b) ? (a) : (b))

color g_predefinedColors[256] = 
{
    color(1.000000, 1.000000, 1.000000), // 0 
    color(0.200000, 0.015686, 0.015686), // 1
    color(0.556863, 0.039216, 0.050980), // 2
    color(0.384314, 0.015686, 0.019608), // 3
    color(0.549020, 0.011765, 0.011765), // 4 
    color(0.368627, 0.000000, 0.015686), // 5
    color(0.537255, 0.000000, 0.015686), // 6
    color(0.862745, 0.058824, 0.062745), // 7 
    color(0.686275, 0.007843, 0.035294), // 8 
    color(0.168627, 0.000000, 0.000000), // 9
    color(0.317647, 0.031373, 0.031373), // 10
    color(0.705882, 0.180392, 0.192157), // 11
    color(0.909804, 0.274510, 0.313726), // 12 
    color(0.141176, 0.003922, 0.000000), // 13
    color(0.207843, 0.003922, 0.000000), // 14
    color(0.317647, 0.000000, 0.000000), // 15
    color(0.576471, 0.019608, 0.007843), // 16
    color(0.952941, 0.113725, 0.149020), // 17
    color(0.254902, 0.062745, 0.043137), // 18 
    color(0.600000, 0.031373, 0.019608), // 19
    color(0.870588, 0.117647, 0.050980), // 20 
    color(0.737255, 0.164706, 0.121569), // 21
    color(0.745098, 0.215686, 0.105882), // 22
    color(0.705882, 0.223529, 0.062745), // 23
    color(0.960784, 0.345098, 0.015686), // 24 
    color(0.764706, 0.313726, 0.105882), // 25
    color(0.729412, 0.141176, 0.007843), // 26
    color(1.000000, 0.215686, 0.000000), // 27
    color(1.000000, 0.254902, 0.000000), // 28 
    color(0.780392, 0.066667, 0.035294), // 29 
    color(0.835294, 0.149020, 0.074510), // 30 
    color(0.901961, 0.368627, 0.188235), // 31 
    color(0.921569, 0.454902, 0.164706), // 32 
    color(0.686275, 0.031373, 0.007843), // 33 
    color(0.600000, 0.117647, 0.007843), // 34 
    color(0.972549, 0.094118, 0.000000), // 35 
    color(0.894118, 0.286275, 0.074510), // 36 
    color(0.588235, 0.062745, 0.015686), // 37 
    color(0.772549, 0.105882, 0.031373), // 38
    color(0.854902, 0.184314, 0.062745), // 39
    color(0.415686, 0.066667, 0.000000), // 40 
    color(0.937255, 0.454902, 0.000000), // 41
    color(1.000000, 0.843137, 0.000000), // 42
    color(0.988235, 0.886275, 0.121569), // 43
    color(0.854902, 0.545098, 0.121569), // 44 
    color(0.854902, 0.325490, 0.007843), // 45
    color(0.988235, 0.576471, 0.184314), // 46
    color(0.929412, 0.525490, 0.003922), // 47 
    color(0.980392, 0.686275, 0.180392), // 48 
    color(0.650980, 0.360784, 0.050980), // 49
    color(0.819608, 0.396078, 0.039216), // 50
    color(0.921569, 0.564706, 0.070588), // 51
    color(0.937255, 0.780392, 0.254902), // 52 
    color(0.615686, 0.325490, 0.003922), // 53
    color(0.686275, 0.380392, 0.019608), // 54
    color(1.000000, 0.705882, 0.070588), // 55
    color(0.796078, 0.819608, 0.176471), // 56 
    color(0.568627, 0.713726, 0.137255), // 57 
    color(0.384314, 0.505882, 0.000000), // 58
    color(0.596078, 0.623529, 0.000000), // 59
    color(0.745098, 0.529412, 0.388235), // 60
    color(0.239216, 0.062745, 0.313726), // 61
    color(0.188235, 0.050980, 0.164706), // 62
    color(0.090196, 0.003922, 0.062745), // 63
    color(0.050980, 0.000000, 0.035294), // 64 
    color(0.090196, 0.043137, 0.090196), // 65
    color(0.039216, 0.007843, 0.101961), // 66
    color(0.364706, 0.223529, 0.364706), // 67 
    color(0.549020, 0.364706, 0.513726), // 68 
    color(0.050980, 0.019608, 0.062745), // 69
    color(0.062745, 0.035294, 0.094118), // 70
    color(0.121569, 0.050980, 0.313726), // 71
    color(0.490196, 0.384314, 0.596078), // 72 
    color(0.105882, 0.039216, 0.121569), // 73
    color(0.121569, 0.062745, 0.184314), // 74
    color(0.200000, 0.101961, 0.294118), // 75
    color(0.400000, 0.243137, 0.505882), // 76 
    color(0.031373, 0.019608, 0.184314), // 77 
    color(0.239216, 0.247059, 0.501961), // 78
    color(0.160784, 0.129412, 0.364706), // 79
    color(0.368627, 0.298039, 0.568627), // 80
    color(0.043137, 0.058824, 0.325490), // 81
    color(0.015686, 0.058824, 0.184314), // 82
    color(0.207843, 0.568627, 0.686275), // 83
    color(0.164706, 0.478431, 0.756863), // 84
    color(0.000000, 0.035294, 0.176471), // 85
    color(0.000000, 0.062745, 0.313726), // 86
    color(0.000000, 0.101961, 0.400000), // 87 
    color(0.188235, 0.670588, 1.000000), // 88 
    color(0.000000, 0.066667, 0.164706), // 89
    color(0.003922, 0.090196, 0.184314), // 90
    color(0.000000, 0.258824, 0.505882), // 91
    color(0.215686, 0.396078, 0.698039), // 92 
    color(0.043137, 0.164706, 0.345098), // 93
    color(0.113725, 0.250980, 0.415686), // 94
    color(0.000000, 0.164706, 0.427451), // 95 
    color(0.000000, 0.368627, 0.513726), // 96
    color(0.207843, 0.513726, 0.368627), // 97
    color(0.000000, 0.141176, 0.101961), // 98 
    color(0.000000, 0.364706, 0.301961), // 99
    color(0.062745, 0.196078, 0.215686), // 100
    color(0.000000, 0.317647, 0.105882), // 101 
    color(0.043137, 0.443137, 0.160784), // 102
    color(0.188235, 0.490196, 0.223529), // 103
    color(0.345098, 0.615686, 0.384314), // 104 
    color(0.031373, 0.215686, 0.023529), // 105
    color(0.050980, 0.231373, 0.105882), // 106
    color(0.058824, 0.384314, 0.215686), // 107 
    color(0.101961, 0.415686, 0.286275), // 108 
    color(0.000000, 0.121569, 0.015686), // 109
    color(0.039216, 0.137255, 0.007843), // 110 
    color(0.043137, 0.184314, 0.035294), // 111
    color(0.078431, 0.215686, 0.172549), // 112
    color(0.094118, 0.121569, 0.015686), // 113 
    color(0.188235, 0.400000, 0.007843), // 114 
    color(0.223529, 0.478431, 0.007843), // 115
    color(0.400000, 0.576471, 0.000000), // 116 
    color(0.184314, 0.239216, 0.019608), // 117
    color(0.031373, 0.090196, 0.007843), // 118 
    color(0.254902, 0.439216, 0.090196), // 119
    color(0.427451, 0.588235, 0.164706), // 120
    color(0.411765, 0.019608, 0.074510), // 121
    color(0.568627, 0.086275, 0.086275), // 122
    color(0.811765, 0.086275, 0.141176), // 123
    color(0.627451, 0.090196, 0.141176), // 124
    color(0.431373, 0.035294, 0.160784), // 125
    color(0.756863, 0.070588, 0.290196), // 126
    color(0.796078, 0.113725, 0.364706), // 127
    color(0.415686, 0.078431, 0.168627), // 128
    color(0.415686, 0.078431, 0.168627), // 129
    color(0.564706, 0.031373, 0.164706), // 130
    color(0.745098, 0.019608, 0.235294), // 131
    color(0.827451, 0.149020, 0.368627), // 132
    color(0.643137, 0.219608, 0.384314), // 133
    color(0.439216, 0.105882, 0.129412), // 134
    color(0.803922, 0.141176, 0.184314), // 135
    color(0.854902, 0.231373, 0.321569), // 136
    color(0.886275, 0.325490, 0.345098), // 137
    color(0.635294, 0.235294, 0.250980), // 138
    color(0.478431, 0.149020, 0.396078), // 139
    color(0.149020, 0.007843, 0.074510), // 140
    color(0.090196, 0.007843, 0.035294), // 141
    color(0.415686, 0.360784, 0.074510), // 142
    color(0.564706, 0.364706, 0.101961), // 143
    color(0.568627, 0.443137, 0.160784), // 144
    color(0.290196, 0.478431, 0.215686), // 145
    color(0.501961, 0.427451, 0.325490), // 146
    color(0.596078, 0.482353, 0.294118), // 147
    color(0.698039, 0.537255, 0.278431), // 148
    color(0.854902, 0.549020, 0.294118), // 149
    color(0.635294, 0.596078, 0.329412), // 150
    color(0.729412, 0.478431, 0.235294), // 151
    color(0.862745, 0.607843, 0.321569), // 152
    color(0.980392, 0.745098, 0.368627), // 153
    color(0.756863, 0.396078, 0.152941), // 154
    color(0.756863, 0.325490, 0.062745), // 155
    color(0.686275, 0.564706, 0.501961), // 156
    color(0.615686, 0.454902, 0.482353), // 157
    color(0.921569, 0.478431, 0.294118), // 158
    color(0.862745, 0.400000, 0.290196), // 159
    color(0.945098, 0.415686, 0.368627), // 160
    color(1.000000, 0.443137, 0.384314), // 161
    color(0.094118, 0.015686, 0.019608), // 162
    color(0.129412, 0.031373, 0.031373), // 163
    color(0.184314, 0.023529, 0.039216), // 164
    color(0.207843, 0.015686, 0.039216), // 165
    color(0.101961, 0.035294, 0.007843), // 166
    color(0.149020, 0.043137, 0.003922), // 167
    color(0.454902, 0.247059, 0.180392), // 168
    color(0.200000, 0.121569, 0.062745), // 169
    color(0.050980, 0.035294, 0.031373), // 170
    color(0.360784, 0.160784, 0.031373), // 171
    color(0.282353, 0.164706, 0.062745), // 172
    color(0.329412, 0.243137, 0.149020), // 173
    color(0.043137, 0.007843, 0.000000), // 174
    color(0.384314, 0.152941, 0.066667), // 175
    color(0.180392, 0.023529, 0.000000), // 176
    color(0.505882, 0.184314, 0.121569), // 177
    color(0.121569, 0.039216, 0.023529), // 178
    color(0.129412, 0.050980, 0.031373), // 179
    color(0.188235, 0.050980, 0.031373), // 180
    color(0.231373, 0.062745, 0.043137), // 181
    color(0.007843, 0.007843, 0.007843), // 182
    color(0.043137, 0.035294, 0.035294), // 183
    color(0.054902, 0.050980, 0.070588), // 184
    color(0.031373, 0.019608, 0.015686), // 185
    color(0.043137, 0.043137, 0.086275), // 186
    color(0.007843, 0.015686, 0.031373), // 187
    color(0.019608, 0.031373, 0.035294), // 188
    color(0.043137, 0.031373, 0.019608), // 189
    color(0.000000, 0.000000, 0.035294), // 190
    color(0.000000, 0.007843, 0.050980), // 191
    color(0.000000, 0.019608, 0.070588), // 192
    color(0.000000, 0.039216, 0.062745), // 193
    color(0.007843, 0.007843, 0.039216), // 194
    color(0.015686, 0.035294, 0.105882), // 195
    color(0.015686, 0.062745, 0.129412), // 196
    color(0.007843, 0.058824, 0.090196), // 197
    color(0.039216, 0.039216, 0.031373), // 198
    color(0.000000, 0.050980, 0.015686), // 199
    color(0.019608, 0.000000, 0.015686), // 200
    color(0.015686, 0.015686, 0.094118), // 201
    color(0.129412, 0.141176, 0.129412), // 202
    color(0.164706, 0.164706, 0.164706), // 203
    color(0.105882, 0.141176, 0.160784), // 204
    color(0.223529, 0.349020, 0.384314), // 205
    color(0.129412, 0.235294, 0.411765), // 206
    color(0.223529, 0.482353, 0.596078), // 207
    color(0.262745, 0.415686, 0.564706), // 208
    color(0.400000, 0.615686, 0.686275), // 209
    color(0.113725, 0.278431, 0.215686), // 210
    color(0.247059, 0.290196, 0.513726), // 211
    color(0.345098, 0.329412, 0.321569), // 212
    color(0.364706, 0.537255, 0.396078), // 213
    color(0.149020, 0.184314, 0.090196), // 214
    color(0.227451, 0.243137, 0.086275), // 215
    color(0.227451, 0.282353, 0.149020), // 216
    color(0.090196, 0.090196, 0.062745), // 217
    color(0.188235, 0.207843, 0.141176), // 218
    color(0.094118, 0.050980, 0.090196), // 219
    color(0.368627, 0.274510, 0.231373), // 220
    color(0.184314, 0.294118, 0.090196), // 221
    color(1.000000, 1.000000, 0.980392), // 222
    color(0.972549, 0.952941, 0.886275), // 223
    color(0.952941, 0.576471, 0.952941), // 224
    color(0.854902, 0.494118, 0.596078), // 225
    color(0.886275, 0.772549, 0.513726), // 226
    color(0.862745, 0.819608, 0.596078), // 227
    color(0.886275, 0.886275, 0.427451), // 228
    color(0.972549, 0.654902, 0.662745), // 229
    color(0.525490, 0.525490, 0.525490), // 230
    color(0.937255, 0.576471, 0.501961), // 231
    color(0.929412, 0.862745, 0.764706), // 232
    color(0.988235, 0.854902, 0.843137), // 233
    color(0.698039, 0.819608, 0.627451), // 234
    color(0.654902, 0.835294, 0.854902), // 235
    color(0.752941, 0.705882, 0.643137), // 236
    color(0.745098, 0.745098, 0.568627), // 237
    color(0.556863, 0.772549, 0.843137), // 238
    color(0.737255, 0.886275, 0.972549), // 239
    color(0.945098, 0.878431, 0.525490), // 240
    color(0.937255, 0.854902, 0.635294), // 241
    color(0.879622, 0.250158, 0.258182), // 242
    color(0.913098, 0.412542, 0.545724), // 243
    color(0.806952, 0.111932, 0.054480), // 244
    color(0.000000, 0.000000, 0.000000), // 245
    color(0.000000, 0.000000, 0.000000), // 246
    color(0.000000, 0.000000, 0.000000), // 247
    color(0.000000, 0.000000, 0.000000), // 248
    color(0.000000, 0.000000, 0.000000), // 249
    color(0.000000, 0.000000, 0.000000), // 250
    color(0.000000, 0.000000, 0.000000), // 251
    color(0.000000, 0.000000, 0.000000), // 252
    color(0.000000, 0.000000, 0.000000), // 253
    color(0.000000, 0.000000, 0.000000), // 254
    color(0.000000, 0.000000, 0.000000)  // 255
};

const int colorAmount = 256;
const int idInterval = 4;
const int stripWidth = image_width / 4;
const int colorAmountPerStrip = image_height / idInterval;

int main() 
{
    
    constexpr int data_size = image_width*image_height*3;
    unsigned char data[data_size];
    int index = 0;
    const int max_depth = 50;

    // Render

    std::cerr << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    //A[I, j] row ith (y), column jth (x)
    auto greyscale = 0;
    // auto gradient  = 0;
    int id = 0;
    auto strip_width = 5;
    
    for (int j = 0; j < image_height; ++j) 
    {
        //(int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines_remaining:" << j << ' ' << std::flush;

        for (int i = 0; i < image_width; ++i)
        {
            color pixel_color(0, 0, 0);

            const int stripID = i / stripWidth;
            const int colorID = MIN(id + stripID * colorAmountPerStrip, colorAmount);

            for (int s = 0; s < samples_per_pixel; ++s)
            {
                auto r = g_predefinedColors[colorID].x();
                auto g = g_predefinedColors[colorID].y();
                auto b = g_predefinedColors[colorID].z();
                pixel_color += color(r, g, b);//a+t*(b−a)
            }

            write_color(std::cout, pixel_color, data, index);
        }

        if (j >= idInterval && (j % idInterval == 0))
        {
            ++id;
        }
    }

    std::cerr << "\nDone.\n";
    stbi_write_png("TST_Pattern_LUT3.png", image_width, image_height, 3, data, image_width * 3);
}
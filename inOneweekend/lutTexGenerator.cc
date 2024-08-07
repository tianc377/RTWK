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
    color(0.764706, 0.035294, 0.035294), // 000
    color(0.886275, 0.196078, 0.000000), // 001
    color(1.000000, 0.580392, 0.066667), // 002
    color(0.623529, 0.588235, 0.074510), // 003
    color(0.396078, 0.517647, 0.050980), // 004
    color(0.019608, 0.301961, 0.031373), // 005
    color(0.000000, 0.364706, 0.301961), // 006
    color(0.007843, 0.184314, 0.478431), // 007
    color(0.027451, 0.380392, 0.827451), // 008
    color(0.062745, 0.137255, 0.705882), // 009
    color(0.149020, 0.105882, 0.654902), // 010
    color(0.505882, 0.290196, 0.909804), // 011
    color(0.654902, 0.078431, 0.247059), // 012
    color(0.239216, 0.007843, 0.007843), // 013
    color(0.090196, 0.015686, 0.015686), // 014
    color(0.200000, 0.015686, 0.015686), // 015
    color(0.274510, 0.062745, 0.062745), // 016
    color(0.415686, 0.164706, 0.164706), // 017
    color(0.141176, 0.003922, 0.000000), // 018
    color(0.403922, 0.121569, 0.054902), // 019
    color(0.415686, 0.168627, 0.117647), // 020
    color(0.490196, 0.192157, 0.090196), // 021
    color(0.352941, 0.109804, 0.027451), // 022
    color(0.282353, 0.070588, 0.007843), // 023
    color(0.403922, 0.235294, 0.101961), // 024
    color(0.403922, 0.215686, 0.050980), // 025
    color(0.231373, 0.105882, 0.019608), // 026
    color(0.431373, 0.184314, 0.011765), // 027
    color(0.517647, 0.388235, 0.227451), // 028
    color(0.537255, 0.262745, 0.031373), // 029
    color(0.415686, 0.360784, 0.227451), // 030
    color(0.380392, 0.231373, 0.031373), // 031
    color(0.282353, 0.145098, 0.000000), // 032
    color(0.341176, 0.262745, 0.113725), // 033
    color(0.301961, 0.301961, 0.058824), // 034
    color(0.231373, 0.250980, 0.086275), // 035
    color(0.133333, 0.152941, 0.058824), // 036
    color(0.050980, 0.062745, 0.015686), // 037
    color(0.156863, 0.219608, 0.090196), // 038
    color(0.031373, 0.090196, 0.007843), // 039
    color(0.050980, 0.109804, 0.023529), // 040
    color(0.031373, 0.070588, 0.027451), // 041
    color(0.000000, 0.043137, 0.003922), // 042
    color(0.027451, 0.094118, 0.050980), // 043
    color(0.000000, 0.015686, 0.003922), // 044
    color(0.000000, 0.043137, 0.031373), // 045
    color(0.031373, 0.090196, 0.098039), // 046
    color(0.000000, 0.015686, 0.019608), // 047
    color(0.007843, 0.035294, 0.050980), // 048
    color(0.007843, 0.054902, 0.094118), // 049
    color(0.015686, 0.062745, 0.129412), // 050
    color(0.058824, 0.113725, 0.219608), // 051
    color(0.027451, 0.062745, 0.145098), // 052
    color(0.007843, 0.019608, 0.043137), // 053
    color(0.003922, 0.003922, 0.027451), // 054
    color(0.000000, 0.007843, 0.050980), // 055
    color(0.015686, 0.011765, 0.062745), // 056
    color(0.031373, 0.007843, 0.039216), // 057
    color(0.074510, 0.019608, 0.066667), // 058
    color(0.043137, 0.003922, 0.035294), // 059
    color(0.094118, 0.007843, 0.047059), // 060
    color(0.082353, 0.003922, 0.023529), // 061
    color(0.239216, 0.054902, 0.094118), // 062
    color(0.168627, 0.023529, 0.043137), // 063
    color(0.282353, 0.086275, 0.101961), // 064
    color(0.070588, 0.015686, 0.015686), // 065
    color(0.062745, 0.031373, 0.031373), // 066
    color(0.023529, 0.003922, 0.003922), // 067
    color(0.031373, 0.011765, 0.011765), // 068
    color(0.105882, 0.023529, 0.011765), // 069
    color(0.086275, 0.027451, 0.019608), // 070
    color(0.039216, 0.015686, 0.011765), // 071
    color(0.058824, 0.035294, 0.031373), // 072
    color(0.023529, 0.015686, 0.015686), // 073
    color(0.239216, 0.121569, 0.082353), // 074
    color(0.050980, 0.019608, 0.011765), // 075
    color(0.094118, 0.023529, 0.003922), // 076
    color(0.129412, 0.050980, 0.023529), // 077
    color(0.219608, 0.090196, 0.039216), // 078
    color(0.062745, 0.019608, 0.007843), // 079
    color(0.109804, 0.050980, 0.027451), // 080
    color(0.121569, 0.086275, 0.062745), // 081
    color(0.011765, 0.003922, 0.000000), // 082
    color(0.070588, 0.023529, 0.000000), // 083
    color(0.027451, 0.007843, 0.000000), // 084
    color(0.094118, 0.058824, 0.031373), // 085
    color(0.094118, 0.074510, 0.062745), // 086
    color(0.168627, 0.125490, 0.078431), // 087
    color(0.160784, 0.101961, 0.047059), // 088
    color(0.129412, 0.109804, 0.086275), // 089
    color(0.015686, 0.011765, 0.003922), // 090
    color(0.043137, 0.039216, 0.015686), // 091
    color(0.066667, 0.062745, 0.039216), // 092
    color(0.019608, 0.019608, 0.007843), // 093
    color(0.039216, 0.039216, 0.023529), // 094
    color(0.015686, 0.015686, 0.011765), // 095
    color(0.035294, 0.039216, 0.019608), // 096
    color(0.019608, 0.027451, 0.019608), // 097
    color(0.015686, 0.031373, 0.023529), // 098
    color(0.027451, 0.043137, 0.035294), // 099
    color(0.003922, 0.019608, 0.011765), // 100
    color(0.015686, 0.027451, 0.027451), // 101
    color(0.039216, 0.058824, 0.070588), // 102
    color(0.003922, 0.011765, 0.031373), // 103
    color(0.019608, 0.027451, 0.039216), // 104
    color(0.011765, 0.011765, 0.031373), // 105
    color(0.023529, 0.023529, 0.050980), // 106
    color(0.019608, 0.019608, 0.035294), // 107
    color(0.035294, 0.035294, 0.043137), // 108
    color(0.019608, 0.019608, 0.023529), // 109
    color(0.047059, 0.035294, 0.058824), // 110
    color(0.031373, 0.015686, 0.039216), // 111
    color(0.019608, 0.011765, 0.019608), // 112
    color(0.035294, 0.015686, 0.027451), // 113
    color(0.070588, 0.050980, 0.058824), // 114
    color(0.066667, 0.054902, 0.058824), // 115
    color(0.145098, 0.066667, 0.090196), // 116
    color(0.098039, 0.066667, 0.078431), // 117
    color(0.250980, 0.121569, 0.152941), // 118
    color(0.015686, 0.015686, 0.015686), // 119
    color(0.058824, 0.058824, 0.058824), // 120
    color(0.121569, 0.121569, 0.121569), // 121
    color(0.164706, 0.164706, 0.164706), // 122
    color(0.341176, 0.341176, 0.341176), // 123
    color(0.525490, 0.525490, 0.525490), // 124
    color(0.705882, 0.705882, 0.705882), // 125
    color(0.870588, 0.870588, 0.870588), // 126
    color(0.549020, 0.388235, 0.352941), // 127
    color(0.568627, 0.478431, 0.427451), // 128
    color(0.505882, 0.364706, 0.274510), // 129
    color(0.368627, 0.274510, 0.231373), // 130
    color(0.431373, 0.368627, 0.286275), // 131
    color(0.431373, 0.364706, 0.247059), // 132
    color(0.549020, 0.501961, 0.372549), // 133
    color(0.458824, 0.439216, 0.290196), // 134
    color(0.580392, 0.556863, 0.447059), // 135
    color(0.568627, 0.568627, 0.427451), // 136
    color(0.458824, 0.517647, 0.419608), // 137
    color(0.419608, 0.525490, 0.537255), // 138
    color(0.415686, 0.372549, 0.458824), // 139
    color(0.400000, 0.298039, 0.403922), // 140
    color(0.317647, 0.231373, 0.286275), // 141
    color(0.403922, 0.266667, 0.305882), // 142
    color(0.317647, 0.250980, 0.262745), // 143
    color(0.415686, 0.149020, 0.149020), // 144
    color(0.258824, 0.078431, 0.070588), // 145
    color(0.443137, 0.196078, 0.164706), // 146
    color(0.600000, 0.294118, 0.262745), // 147
    color(0.454902, 0.247059, 0.180392), // 148
    color(0.568627, 0.290196, 0.215686), // 149
    color(0.580392, 0.294118, 0.160784), // 150
    color(0.580392, 0.329412, 0.215686), // 151
    color(0.600000, 0.329412, 0.141176), // 152
    color(0.439216, 0.317647, 0.207843), // 153
    color(0.729412, 0.478431, 0.235294), // 154
    color(0.564706, 0.364706, 0.101961), // 155
    color(0.623529, 0.458824, 0.160784), // 156
    color(0.568627, 0.443137, 0.160784), // 157
    color(0.403922, 0.360784, 0.101961), // 158
    color(0.223529, 0.239216, 0.086275), // 159
    color(0.321569, 0.431373, 0.129412), // 160
    color(0.184314, 0.294118, 0.090196), // 161
    color(0.149020, 0.184314, 0.090196), // 162
    color(0.227451, 0.282353, 0.149020), // 163
    color(0.196078, 0.317647, 0.145098), // 164
    color(0.113725, 0.184314, 0.086275), // 165
    color(0.176471, 0.352941, 0.200000), // 166
    color(0.062745, 0.160784, 0.074510), // 167
    color(0.364706, 0.537255, 0.396078), // 168
    color(0.207843, 0.403922, 0.313726), // 169
    color(0.113725, 0.294118, 0.223529), // 170
    color(0.125490, 0.274510, 0.274510), // 171
    color(0.066667, 0.176471, 0.215686), // 172
    color(0.223529, 0.349020, 0.384314), // 173
    color(0.180392, 0.368627, 0.443137), // 174
    color(0.345098, 0.501961, 0.549020), // 175
    color(0.141176, 0.298039, 0.431373), // 176
    color(0.254902, 0.415686, 0.564706), // 177
    color(0.074510, 0.168627, 0.258824), // 178
    color(0.137255, 0.254902, 0.403922), // 179
    color(0.262745, 0.380392, 0.549020), // 180
    color(0.078431, 0.164706, 0.301961), // 181
    color(0.129412, 0.231373, 0.411765), // 182
    color(0.247059, 0.290196, 0.513726), // 183
    color(0.231373, 0.235294, 0.380392), // 184
    color(0.133333, 0.113725, 0.250980), // 185
    color(0.247059, 0.211765, 0.352941), // 186
    color(0.113725, 0.086275, 0.152941), // 187
    color(0.345098, 0.250980, 0.403922), // 188
    color(0.364706, 0.223529, 0.364706), // 189
    color(0.152941, 0.090196, 0.215686), // 190
    color(0.090196, 0.058824, 0.121569), // 191
    color(0.035294, 0.023529, 0.050980), // 192
    color(0.094118, 0.050980, 0.090196), // 193
    color(0.282353, 0.164706, 0.254902), // 194
    color(0.388235, 0.141176, 0.239216), // 195
    color(0.490196, 0.196078, 0.243137), // 196
    color(0.478431, 0.219608, 0.231373), // 197
    color(0.478431, 0.305882, 0.321569), // 198
    color(1.000000, 0.549020, 0.094118), // 199
    color(0.431373, 0.250980, 0.062745), // 200
    color(0.909804, 0.364706, 0.250980), // 201
    color(0.431373, 0.176471, 0.117647), // 202
    color(0.549020, 0.568627, 0.580392), // 203
    color(0.364706, 0.341176, 0.317647), // 204
    color(0.215686, 0.215686, 0.239216), // 205
    color(0.670588, 0.490196, 0.215686), // 206
    color(0.490196, 0.341176, 0.098039), // 207
    color(0.003922, 0.003922, 0.003922), // 208
    color(0.015686, 0.015686, 0.015686), // 209
    color(0.062745, 0.062745, 0.062745), // 210
    color(0.215686, 0.215686, 0.215686), // 211
    color(0.294118, 0.294118, 0.294118), // 212
    color(0.380392, 0.380392, 0.380392), // 213
    color(0.203922, 0.117647, 0.113725), // 214
    color(0.203922, 0.149020, 0.113725), // 215
    color(0.203922, 0.164706, 0.113725), // 216
    color(0.203922, 0.192157, 0.113725), // 217
    color(0.184314, 0.203922, 0.113725), // 218
    color(0.105882, 0.152941, 0.098039), // 219
    color(0.129412, 0.203922, 0.172549), // 220
    color(0.129412, 0.168627, 0.203922), // 221
    color(0.113725, 0.156863, 0.203922), // 222
    color(0.113725, 0.121569, 0.203922), // 223
    color(0.156863, 0.141176, 0.203922), // 224
    color(0.149020, 0.101961, 0.160784), // 225
    color(0.160784, 0.101961, 0.125490), // 226
    color(0.039216, 0.000000, 0.000000), // 227
    color(0.031373, 0.000000, 0.007843), // 228
    color(0.015686, 0.000000, 0.019608), // 229
    color(0.003922, 0.000000, 0.031373), // 230
    color(0.000000, 0.003922, 0.015686), // 231
    color(0.000000, 0.015686, 0.015686), // 232
    color(0.000000, 0.015686, 0.003922), // 233
    color(0.003922, 0.015686, 0.000000), // 234
    color(0.015686, 0.019608, 0.000000), // 235
    color(0.019608, 0.011765, 0.000000), // 236
    color(0.015686, 0.003922, 0.000000), // 237
    color(0.058824, 0.043137, 0.043137), // 238
    color(0.050980, 0.058824, 0.050980), // 239
    color(0.050980, 0.050980, 0.058824), // 240
    color(0.086275, 0.070588, 0.070588), // 241
    color(0.086275, 0.090196, 0.086275), // 242
    color(0.078431, 0.078431, 0.082353), // 243
    color(0.141176, 0.117647, 0.117647), // 244
    color(0.129412, 0.141176, 0.129412), // 245
    color(0.129412, 0.137255, 0.141176), // 246

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
    int id = 63;
    auto strip_width = 5;
    
    for (int j = 0; j < image_height; ++j) 
    {
        if (j != 0 && j % idInterval == 0)
        {
            --id;
        }

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
                pixel_color += color(r, g, b);
            }

            write_color(std::cout, pixel_color, data, index);
        }
    }

    std::cerr << "\nDone.\n";
    stbi_write_png("TST_Pattern_LUT4.png", image_width, image_height, 3, data, image_width * 3);
}
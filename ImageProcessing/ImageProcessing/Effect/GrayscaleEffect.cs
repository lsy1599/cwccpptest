using System;
using System.Drawing;

namespace ChuiWenChiu.ImageProcessing {
    public class GrayscaleEffect : Effect {
        protected override void Apply() {
            ForEachPixel(delegate(int x, int y, ref byte A, ref byte R, ref byte G, ref byte B) {                
                R = G = B = (byte)((R + G + B) / 3);                
            });
        }
    }
}

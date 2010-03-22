using System;
using System.Drawing;

namespace ChuiWenChiu.ImageProcessing {
    public class NegativeEffect :Effect {        
        protected override void Apply() {
            ForEachPixel(delegate(int x, int y, ref byte A, ref byte R, ref byte G, ref byte B) {
                R = (byte)(255 - R);
                G = (byte)(255 - G);
                B = (byte)(255 - B);
            });     
        }

    }
}

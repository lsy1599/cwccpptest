using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace ChuiWenChiu.ImageProcessing {
    public class HorizontalFlipEffect :Effect {
        protected override void BeforeApply() {

        }

        protected override void Apply() {
            dstBmp = new Bitmap(m_srcImg);
            dstBmp.RotateFlip(RotateFlipType.RotateNoneFlipX);
        }

        protected override void AfterApply() {

        }
    }
}

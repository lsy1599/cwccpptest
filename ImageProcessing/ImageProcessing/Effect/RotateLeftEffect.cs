﻿using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace ChuiWenChiu.ImageProcessing {
    public class RotateLeftEffect : Effect {
        protected override void BeforeApply() {
            
        }

        protected override void Apply() {
            dstBmp = new Bitmap(m_srcImg);
            dstBmp.RotateFlip(RotateFlipType.Rotate270FlipNone);            
        }

        protected override void AfterApply() {
            
        }
    }
}

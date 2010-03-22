using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Drawing.Imaging;

namespace ChuiWenChiu.ImageProcessing {
    public class Effect {
        protected Image m_srcImg;
        protected Bitmap srcBmp;
        protected Bitmap dstBmp;
        protected BitmapData srcData;
        protected BitmapData dstData;
        protected IntPtr dstptr;
        protected byte[] rgbValues;
        protected int dataLen;

        protected virtual void BeforeApply() {
            srcBmp = new Bitmap(m_srcImg);
            dstBmp = new Bitmap(m_srcImg);
            Rectangle srcArea = new Rectangle(0, 0, srcBmp.Width, srcBmp.Height);
            Rectangle dstArea = new Rectangle(0, 0, srcBmp.Width, srcBmp.Height);
            srcData = srcBmp.LockBits(srcArea, ImageLockMode.ReadOnly, srcBmp.PixelFormat);
            dstData = dstBmp.LockBits(dstArea, ImageLockMode.WriteOnly, dstBmp.PixelFormat);
            IntPtr srcptr = srcData.Scan0;
            dstptr = dstData.Scan0;

            dataLen = srcBmp.Width * srcBmp.Height * 4;
            rgbValues = new byte[dataLen];

            Marshal.Copy(srcptr, rgbValues, 0, dataLen);
            srcBmp.UnlockBits(srcData);
        }

        protected virtual void AfterApply() {
            Marshal.Copy(rgbValues, 0, dstptr, dataLen);
            dstBmp.UnlockBits(dstData);
        }

        protected virtual void Apply() {

        }

        public Bitmap DoIt(Image src) {
            m_srcImg = src;

            BeforeApply();
            Apply();
            AfterApply();

            return dstBmp;
        }

        protected delegate void ForEachCallback(int x, int y, ref byte A, ref byte R, ref byte G, ref byte B);
        protected void ForEachPixel(ForEachCallback callback) {
            for (int y = 0; y < srcBmp.Height; ++y) {
                for (int x = 0; x < srcBmp.Width * 4; x += 4) {
                    int pos = x + y * srcBmp.Width * 4;
                    callback(x, y, ref rgbValues[pos + 3], ref rgbValues[pos], ref rgbValues[pos + 1], ref rgbValues[pos + 2]);
                }
            }
        }
    }
}

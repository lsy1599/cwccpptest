using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Drawing.Imaging;

using ChuiWenChiu.ImageProcessing;

namespace ImageProcessing {
    public partial class Form1 : Form {
        private Effect e1;

        public Form1() {
            InitializeComponent();
        }

        private OpenFileDialog dlg = new OpenFileDialog(); 
        private void mnuFileOpen_Click(object sender, EventArgs e) {
            dlg.Filter = "*.jpg|*.jpg";
            
            if (dlg.ShowDialog() == DialogResult.OK) {                
                Image bmp = Image.FromFile(dlg.FileName);
                //if (bmp.PixelFormat != PixelFormat.Format32bppArgb) {
                //    MessageBox.Show("Only support 32bits ARGB Format");  
                //    return;
                //}
                imgSrc.Image = bmp;
                
                sbFilename.Text = dlg.FileName; 
            }
        }

        private void mnuImageGrayscale_Click(object sender, EventArgs e) {
            e1 = new GrayscaleEffect();
            imgDst.Image = e1.DoIt(imgSrc.Image); 
        }

        private void mnuSrcToDest_Click(object sender, EventArgs e) {
            imgDst.Image = imgSrc.Image;  
        }

        private void mnuDestToSrc_Click(object sender, EventArgs e) {
            imgSrc.Image = imgDst.Image;  
        }

        private void mnuImageNegative_Click(object sender, EventArgs e) {
            e1 = new NegativeEffect();
            imgDst.Image = e1.DoIt(imgSrc.Image); 
        }

        private void mnuFileExit_Click(object sender, EventArgs e) {
            Close();
        }

        private void mnuViewDestWin_Click(object sender, EventArgs e) {
            mnuViewDestWin.Checked = !mnuViewDestWin.Checked;
            splitContainer1.Panel2Collapsed = !mnuViewDestWin.Checked;
        }

        private void Form1_Load(object sender, EventArgs e) {
            splitContainer1.SplitterDistance = splitContainer1.Width / 2;  
        }

        private void mnuImageRotateLeft_Click(object sender, EventArgs e) {
            e1 = new RotateLeftEffect();
            imgDst.Image = e1.DoIt(imgSrc.Image); 
        }

        private void mnuImageRotateRight_Click(object sender, EventArgs e) {
            e1 = new RotateRightEffect();
            imgDst.Image = e1.DoIt(imgSrc.Image); 
        }

        private void mnuImageVerticalFlip_Click(object sender, EventArgs e) {
            e1 = new VerticalFlipEffect();
            imgDst.Image = e1.DoIt(imgSrc.Image); 
        }

        private void mnuImageHorizontalFlip_Click(object sender, EventArgs e) {
            e1 = new HorizontalFlipEffect();
            imgDst.Image = e1.DoIt(imgSrc.Image); 
        }

        private void toolStripButton1_Click(object sender, EventArgs e) {
            Bitmap b = new Bitmap(100, 100, PixelFormat.Format32bppArgb);
            
            for (int y = 0; y < b.Height; ++y) {
                for (int x = 0; x < b.Width; ++x) {
                    b.SetPixel(x, y, Color.Red);  
                }
            }
            imgSrc.Image = b; 
        }
    }



}
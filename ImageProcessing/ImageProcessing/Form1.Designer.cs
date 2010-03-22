namespace ImageProcessing {
    partial class Form1 {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.imgSrc = new System.Windows.Forms.PictureBox();
            this.imgDst = new System.Windows.Forms.PictureBox();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.toolStripButton1 = new System.Windows.Forms.ToolStripButton();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFileOpen = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFileExit = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuViewDestWin = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuImage = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuImageRotateLeft = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuImageRotateRight = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuImageVerticalFlip = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuImageHorizontalFlip = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuImageGrayscale = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuImageNegative = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuSrcToDest = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuDestToSrc = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.sbFilename = new System.Windows.Forms.ToolStripStatusLabel();
            this.tableLayoutPanel1.SuspendLayout();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.imgSrc)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.imgDst)).BeginInit();
            this.toolStrip1.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.splitContainer1, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.toolStrip1, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.menuStrip1, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.statusStrip1, 0, 3);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 4;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(430, 243);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(3, 43);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.imgSrc);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.imgDst);
            this.splitContainer1.Size = new System.Drawing.Size(424, 177);
            this.splitContainer1.SplitterDistance = 150;
            this.splitContainer1.SplitterWidth = 5;
            this.splitContainer1.TabIndex = 0;
            // 
            // imgSrc
            // 
            this.imgSrc.Dock = System.Windows.Forms.DockStyle.Fill;
            this.imgSrc.Location = new System.Drawing.Point(0, 0);
            this.imgSrc.Name = "imgSrc";
            this.imgSrc.Size = new System.Drawing.Size(150, 177);
            this.imgSrc.TabIndex = 0;
            this.imgSrc.TabStop = false;
            // 
            // imgDst
            // 
            this.imgDst.Dock = System.Windows.Forms.DockStyle.Fill;
            this.imgDst.Location = new System.Drawing.Point(0, 0);
            this.imgDst.Name = "imgDst";
            this.imgDst.Size = new System.Drawing.Size(269, 177);
            this.imgDst.TabIndex = 0;
            this.imgDst.TabStop = false;
            // 
            // toolStrip1
            // 
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton1});
            this.toolStrip1.Location = new System.Drawing.Point(0, 20);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(430, 20);
            this.toolStrip1.TabIndex = 1;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // toolStripButton1
            // 
            this.toolStripButton1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton1.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton1.Image")));
            this.toolStripButton1.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton1.Name = "toolStripButton1";
            this.toolStripButton1.Size = new System.Drawing.Size(23, 17);
            this.toolStripButton1.Text = "toolStripButton1";
            this.toolStripButton1.Click += new System.EventHandler(this.toolStripButton1_Click);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.toolStripMenuItem1,
            this.mnuImage,
            this.helpToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(430, 20);
            this.menuStrip1.TabIndex = 3;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuFileOpen,
            this.mnuFileExit});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(34, 16);
            this.fileToolStripMenuItem.Text = "&File";
            // 
            // mnuFileOpen
            // 
            this.mnuFileOpen.Name = "mnuFileOpen";
            this.mnuFileOpen.Size = new System.Drawing.Size(95, 22);
            this.mnuFileOpen.Text = "&Open";
            this.mnuFileOpen.Click += new System.EventHandler(this.mnuFileOpen_Click);
            // 
            // mnuFileExit
            // 
            this.mnuFileExit.Name = "mnuFileExit";
            this.mnuFileExit.Size = new System.Drawing.Size(95, 22);
            this.mnuFileExit.Text = "E&xit";
            this.mnuFileExit.Click += new System.EventHandler(this.mnuFileExit_Click);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuViewDestWin});
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(41, 16);
            this.toolStripMenuItem1.Text = "&View";
            // 
            // mnuViewDestWin
            // 
            this.mnuViewDestWin.Checked = true;
            this.mnuViewDestWin.CheckState = System.Windows.Forms.CheckState.Checked;
            this.mnuViewDestWin.Name = "mnuViewDestWin";
            this.mnuViewDestWin.Size = new System.Drawing.Size(165, 22);
            this.mnuViewDestWin.Text = "Destination Window";
            this.mnuViewDestWin.Click += new System.EventHandler(this.mnuViewDestWin_Click);
            // 
            // mnuImage
            // 
            this.mnuImage.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuImageRotateLeft,
            this.mnuImageRotateRight,
            this.mnuImageVerticalFlip,
            this.mnuImageHorizontalFlip,
            this.toolStripSeparator2,
            this.mnuImageGrayscale,
            this.mnuImageNegative,
            this.toolStripSeparator1,
            this.mnuSrcToDest,
            this.mnuDestToSrc});
            this.mnuImage.Name = "mnuImage";
            this.mnuImage.Size = new System.Drawing.Size(46, 16);
            this.mnuImage.Text = "&Image";
            // 
            // mnuImageRotateLeft
            // 
            this.mnuImageRotateLeft.Name = "mnuImageRotateLeft";
            this.mnuImageRotateLeft.Size = new System.Drawing.Size(170, 22);
            this.mnuImageRotateLeft.Text = "Rotate Left";
            this.mnuImageRotateLeft.Click += new System.EventHandler(this.mnuImageRotateLeft_Click);
            // 
            // mnuImageRotateRight
            // 
            this.mnuImageRotateRight.Name = "mnuImageRotateRight";
            this.mnuImageRotateRight.Size = new System.Drawing.Size(170, 22);
            this.mnuImageRotateRight.Text = "Rotate Right";
            this.mnuImageRotateRight.Click += new System.EventHandler(this.mnuImageRotateRight_Click);
            // 
            // mnuImageVerticalFlip
            // 
            this.mnuImageVerticalFlip.Name = "mnuImageVerticalFlip";
            this.mnuImageVerticalFlip.Size = new System.Drawing.Size(170, 22);
            this.mnuImageVerticalFlip.Text = "Vertical Flip";
            this.mnuImageVerticalFlip.Click += new System.EventHandler(this.mnuImageVerticalFlip_Click);
            // 
            // mnuImageHorizontalFlip
            // 
            this.mnuImageHorizontalFlip.Name = "mnuImageHorizontalFlip";
            this.mnuImageHorizontalFlip.Size = new System.Drawing.Size(170, 22);
            this.mnuImageHorizontalFlip.Text = "Horizotal Flip";
            this.mnuImageHorizontalFlip.Click += new System.EventHandler(this.mnuImageHorizontalFlip_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(167, 6);
            // 
            // mnuImageGrayscale
            // 
            this.mnuImageGrayscale.Name = "mnuImageGrayscale";
            this.mnuImageGrayscale.Size = new System.Drawing.Size(170, 22);
            this.mnuImageGrayscale.Text = "Grayscale";
            this.mnuImageGrayscale.Click += new System.EventHandler(this.mnuImageGrayscale_Click);
            // 
            // mnuImageNegative
            // 
            this.mnuImageNegative.Name = "mnuImageNegative";
            this.mnuImageNegative.Size = new System.Drawing.Size(170, 22);
            this.mnuImageNegative.Text = "Negative";
            this.mnuImageNegative.Click += new System.EventHandler(this.mnuImageNegative_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(167, 6);
            // 
            // mnuSrcToDest
            // 
            this.mnuSrcToDest.Name = "mnuSrcToDest";
            this.mnuSrcToDest.Size = new System.Drawing.Size(170, 22);
            this.mnuSrcToDest.Text = "Source -> Destination";
            this.mnuSrcToDest.Click += new System.EventHandler(this.mnuSrcToDest_Click);
            // 
            // mnuDestToSrc
            // 
            this.mnuDestToSrc.Name = "mnuDestToSrc";
            this.mnuDestToSrc.Size = new System.Drawing.Size(170, 22);
            this.mnuDestToSrc.Text = "Desination -> Source";
            this.mnuDestToSrc.Click += new System.EventHandler(this.mnuDestToSrc_Click);
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aboutToolStripMenuItem});
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(39, 16);
            this.helpToolStripMenuItem.Text = "&Help";
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(99, 22);
            this.aboutToolStripMenuItem.Text = "&About";
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.sbFilename});
            this.statusStrip1.Location = new System.Drawing.Point(0, 223);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(430, 20);
            this.statusStrip1.TabIndex = 2;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // sbFilename
            // 
            this.sbFilename.Name = "sbFilename";
            this.sbFilename.Size = new System.Drawing.Size(104, 15);
            this.sbFilename.Text = "toolStripStatusLabel1";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(430, 243);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Name = "Form1";
            this.Text = "Digital Image Processing";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.Load += new System.EventHandler(this.Form1_Load);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.imgSrc)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.imgDst)).EndInit();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.PictureBox imgSrc;
        private System.Windows.Forms.PictureBox imgDst;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton toolStripButton1;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem mnuFileOpen;
        private System.Windows.Forms.ToolStripMenuItem mnuFileExit;
        private System.Windows.Forms.ToolStripMenuItem mnuImage;
        private System.Windows.Forms.ToolStripMenuItem mnuImageGrayscale;
        private System.Windows.Forms.ToolStripMenuItem mnuSrcToDest;
        private System.Windows.Forms.ToolStripMenuItem mnuDestToSrc;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem mnuImageNegative;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripStatusLabel sbFilename;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem mnuViewDestWin;
        private System.Windows.Forms.ToolStripMenuItem mnuImageRotateLeft;
        private System.Windows.Forms.ToolStripMenuItem mnuImageRotateRight;
        private System.Windows.Forms.ToolStripMenuItem mnuImageVerticalFlip;
        private System.Windows.Forms.ToolStripMenuItem mnuImageHorizontalFlip;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;

    }
}


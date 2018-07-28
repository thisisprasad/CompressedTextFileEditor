namespace GUI
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
			this.components = new System.ComponentModel.Container();
			this.btn = new System.Windows.Forms.Button();
			this.txtbox = new System.Windows.Forms.TextBox();
			this.namelbl = new System.Windows.Forms.Label();
			this.txtEditor = new System.Windows.Forms.RichTextBox();
			this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
			this.fileChoosebtn = new System.Windows.Forms.Button();
			this.msglbl = new System.Windows.Forms.Label();
			this.notifyIcon1 = new System.Windows.Forms.NotifyIcon(this.components);
			this.savebtn = new System.Windows.Forms.Button();
			this.savasbtn = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// btn
			// 
			this.btn.Location = new System.Drawing.Point(278, 9);
			this.btn.Name = "btn";
			this.btn.Size = new System.Drawing.Size(75, 23);
			this.btn.TabIndex = 0;
			this.btn.Text = "Compress";
			this.btn.UseVisualStyleBackColor = true;
			this.btn.Click += new System.EventHandler(this.button1_Click);
			// 
			// txtbox
			// 
			this.txtbox.Location = new System.Drawing.Point(153, 12);
			this.txtbox.Name = "txtbox";
			this.txtbox.Size = new System.Drawing.Size(119, 20);
			this.txtbox.TabIndex = 1;
			this.txtbox.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
			// 
			// namelbl
			// 
			this.namelbl.AutoSize = true;
			this.namelbl.Location = new System.Drawing.Point(81, 15);
			this.namelbl.Name = "namelbl";
			this.namelbl.Size = new System.Drawing.Size(55, 13);
			this.namelbl.TabIndex = 2;
			this.namelbl.Text = "Filename";
			this.namelbl.Click += new System.EventHandler(this.label1_Click);
			// 
			// txtEditor
			// 
			this.txtEditor.BackColor = System.Drawing.SystemColors.Info;
			this.txtEditor.Font = new System.Drawing.Font("Consolas", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.txtEditor.ForeColor = System.Drawing.SystemColors.MenuText;
			this.txtEditor.Location = new System.Drawing.Point(12, 63);
			this.txtEditor.Name = "txtEditor";
			this.txtEditor.Size = new System.Drawing.Size(1033, 577);
			this.txtEditor.TabIndex = 3;
			this.txtEditor.Text = "";
			this.txtEditor.TextChanged += new System.EventHandler(this.richTextBox1_TextChanged);
			this.txtEditor.KeyDown += new System.Windows.Forms.KeyEventHandler(this.txtEditorClick);
			this.txtEditor.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtEditorClick);
			this.txtEditor.KeyUp += new System.Windows.Forms.KeyEventHandler(this.txtEditorClick);
			// 
			// openFileDialog1
			// 
			this.openFileDialog1.FileName = "openFileDialog1";
			this.openFileDialog1.FileOk += new System.ComponentModel.CancelEventHandler(this.openFileDialog1_FileOk);
			// 
			// fileChoosebtn
			// 
			this.fileChoosebtn.Location = new System.Drawing.Point(53, 34);
			this.fileChoosebtn.Name = "fileChoosebtn";
			this.fileChoosebtn.Size = new System.Drawing.Size(83, 23);
			this.fileChoosebtn.TabIndex = 4;
			this.fileChoosebtn.Text = "Choose file";
			this.fileChoosebtn.UseVisualStyleBackColor = true;
			this.fileChoosebtn.Click += new System.EventHandler(this.button1_Click_2);
			// 
			// msglbl
			// 
			this.msglbl.AutoSize = true;
			this.msglbl.Location = new System.Drawing.Point(406, 14);
			this.msglbl.Name = "msglbl";
			this.msglbl.Size = new System.Drawing.Size(49, 13);
			this.msglbl.TabIndex = 5;
			this.msglbl.Text = "Message";
			this.msglbl.Click += new System.EventHandler(this.label1_Click_1);
			// 
			// notifyIcon1
			// 
			this.notifyIcon1.Text = "notifyIcon1";
			this.notifyIcon1.Visible = true;
			// 
			// savebtn
			// 
			this.savebtn.Location = new System.Drawing.Point(363, 34);
			this.savebtn.Name = "savebtn";
			this.savebtn.Size = new System.Drawing.Size(39, 23);
			this.savebtn.TabIndex = 9;
			this.savebtn.Text = "Save";
			this.savebtn.UseVisualStyleBackColor = true;
			this.savebtn.Click += new System.EventHandler(this.button1_Click_3);
			// 
			// savasbtn
			// 
			this.savasbtn.Location = new System.Drawing.Point(430, 34);
			this.savasbtn.Name = "savasbtn";
			this.savasbtn.Size = new System.Drawing.Size(58, 23);
			this.savasbtn.TabIndex = 10;
			this.savasbtn.Text = "Save as";
			this.savasbtn.UseVisualStyleBackColor = true;
			this.savasbtn.Click += new System.EventHandler(this.button1_Click_4);
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(913, 512);
			this.Controls.Add(this.savasbtn);
			this.Controls.Add(this.savebtn);
			this.Controls.Add(this.msglbl);
			this.Controls.Add(this.fileChoosebtn);
			this.Controls.Add(this.txtEditor);
			this.Controls.Add(this.namelbl);
			this.Controls.Add(this.txtbox);
			this.Controls.Add(this.btn);
			this.Font = new System.Drawing.Font("Consolas", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.Name = "Form1";
			this.Text = "Form1";
			this.Load += new System.EventHandler(this.Form1_Load);
			this.ResumeLayout(false);
			this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btn;
        private System.Windows.Forms.TextBox txtbox;
        private System.Windows.Forms.Label namelbl;
        private System.Windows.Forms.RichTextBox txtEditor;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.Button fileChoosebtn;
        private System.Windows.Forms.Label msglbl;
        private System.Windows.Forms.NotifyIcon notifyIcon1;
        private System.Windows.Forms.Button savebtn;
        private System.Windows.Forms.Button savasbtn;
	}
}


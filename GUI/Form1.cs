using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Windows;
using Microsoft.Win32;

namespace GUI
{
    public partial class Form1 : Form
    {
        //[DllImport("kernel32.dll", SetLastError = true)]
        //[return: MarshalAs(UnmanagedType.Bool)]
        //static extern bool AllocConsole();

        string fileName = "";
        bool flag = false;

        [DllImport("CompressionInC#.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "_Z9solveNamePcii")]
        //  [DllImport("CompressionInC#.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "_Z5solvev")]
        //  public static extern int solve();
        public static extern int solveName(string s, int len, int parity);
        [DllImport("StringPassing.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "_Z10strPassingPci")]
        public static extern void strPassing(string a, int len);
        public Form1()
        {
            InitializeComponent();
            FontFamily ff = new FontFamily("Consolas"); 
            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Calling the native method");
            //  int res = solveName();
            //  Console.WriteLine(res);
            if(fileName == "")
            {
                msglbl.Text = "Please select a valid file";
                return;
            }
            int res = solveName(fileName, fileName.Length, 1);
            Console.WriteLine(res);
            Console.WriteLine("Completed solve()");
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            //  AllocConsole();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {
			//  If the text in the editor was changed then enable the save button
			msglbl.Text = "From the richTextBox1_TextChanged";
			flag = true;
			//	while (flag) msglbl.Text = "*" + fileName;
			//	while (flag)
			{
				if (fileName != "" && flag) msglbl.Text = "*" + fileName;
				else msglbl.Text = "Untitled Document";
			}
		}

        private void folderBrowserDialog1_HelpRequest(object sender, EventArgs e)
        {

        }

        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {

        }

        private void button1_Click_1(object sender, EventArgs e)
        {

        }

        private void button1_Click_2(object sender, EventArgs e)
        {
            int i;
			bool dec = false;
			OpenFileDialog ofd = new OpenFileDialog();
			//  Nullable<bool> res = (Nullable<bool>) ofd.ShowDialog();
			if (ofd.ShowDialog() == DialogResult.OK)
			{
				fileName = ofd.FileName;
				msglbl.Text = fileName;
				txtbox.Text = fileName; //  Text set in the TextField
										//  Now Read the whole File contents and display it in RichTextBox
				FileStream fin;
				try
				{
					//  fin = new FileStream(fileName, FileMode.Open, FileAccess.Read);
					fin = new FileStream(fileName, FileMode.Open);
					txtEditor.Text = "";
					//	If it is .en file we need to decompress it.
					int n = fileName.Length;
					if (fileName[n - 1] == 'n' && fileName[n - 2] == 'e' && fileName[n - 3] == '.')
					{
						Console.WriteLine("Yes it is .en"); dec = true;
						int res = solveName(fileName, fileName.Length, 0);  //	We want ot decompresss the file
																			//	Now a .dec file is created. Read the contents of that file into textEditor and delete that file
						string dfile = fileName;
						fileName += ".dec";
						fin.Close();	//	I think this would work!!
						fin = new FileStream(fileName, FileMode.Open);
						//	dfile[n - 2] = 'd'; dfile[n - 1] = 'e'; dfile += 'c';
					}

					//  Read the bytes until end of file is encountered
					do
					{
						try
						{
							i = fin.ReadByte();
						}
						catch (IOException ioe)
						{
							Console.WriteLine("Error reading file\n " + ioe);
							break;
						}
						if (i != -1)
						{
							Console.Write((char)i);
							txtEditor.Text += (char)i;
						}
					} while (i != -1);
					fin.Close();
				}
				catch (FileNotFoundException fnfe)
				{
					Console.WriteLine("line 90, FileNotFoundException\n" + fnfe);
				}
				catch (IOException ioe)
				{
					Console.WriteLine("line:94, IOException caught\n" + ioe);
				}
				catch (Exception ex)
				{
					Console.WriteLine("line:98, Excception caught\n" + ex);
				}
				flag = false;
			}
			if (dec) File.Delete(fileName);
            //  if (ofd.ShowDialog() == true)
            //  txtEditor.Text = File.ReadAllText(ofd.FileName);
        }

        private void label1_Click_1(object sender, EventArgs e)
        {

        }

        private void strbtn_Click(object sender, EventArgs e)
        {
            string s = "Prasad";
            int l = s.Length;
            strPassing(s, l);
        }

        private void textBox1_TextChanged_1(object sender, EventArgs e)
        {
            //	if (fonttxt.Text == "") return;
            //	double sz = double.Parse(fonttxt.Text);
            //  Code to change the size of text of txteditor
            //  txtEditor.Font.Size = new System.Drawing.Font((System.Drawing.Font))txtEditor.Font.Name, (System.Drawing.FontStyle)sz);
            //	sz = txtEditor.Font.Size;   
        }

		private void button1_Click_3(object sender, EventArgs e)
		{
			SaveFileDialog sfd = new SaveFileDialog();
			if (fileName == "" && txtEditor.Text == "")
			{
				msglbl.Text = "Nothing to be saved";
				flag = false;
				return;
			}
			else if (fileName == "" && txtEditor.Text != "")
			{
				if (sfd.ShowDialog() == DialogResult.OK)
				{
					File.WriteAllText(sfd.FileName, txtEditor.Text);
					msglbl.Text = sfd.FileName;
					fileName = sfd.FileName;
					int res = solveName(fileName, fileName.Length, 1);  //	Compress the file
					checkRes(res);
					flag = false;
					string en = fileName; en += ".en";
					if (File.Exists(en)) File.Delete(fileName);
				}
				//	File.Delete(fileName);
			}
			else
			{
				try
				{
					FileStream fout = new FileStream(fileName, FileMode.OpenOrCreate, FileAccess.ReadWrite);
					string str = txtEditor.Text;
					for (int i = 0; i < str.Length; i++)
					{
						fout.WriteByte((byte)str[i]);
					}
					int res = solveName(fileName, fileName.Length, 1);  //	Compress the file and save it
					checkRes(res);
					flag = false;
					fout.Close();
				}
				catch (AccessViolationException ave)
				{
					Console.WriteLine("line:201, AccessViolationException generated");
				}
				catch (IOException ioe)
				{
					Console.WriteLine("line:191, Exception while saving the file");
				}
			}

			if (!flag)
			{
				msglbl.Text = fileName;
			}
		}

		private void txtEditorClick(object sender, EventArgs e)
		{

		}

		void checkRes(int res)
		{
			Console.WriteLine(res);
			switch (res)
			{
				case 1:
					Console.WriteLine("Trying to open a compressed file\nInvaid operation");
					break;
				case 2:
					Console.WriteLine("Cannot open file for compression");
					break;

				case 4:
					Console.WriteLine("Cannot decompress the file as the file extension is different");
					break;

				case 5:
					Console.WriteLine("Cannot open file for decompression");
					break;

				case 100:
					Console.WriteLine("Compression routine executed successfully");
					break;

				case 200:
					Console.WriteLine("Decompression routine executed successfully");
					break;

				default:
					Console.WriteLine("Something else is returned");
					break;
			}
		}

		private void button2_Click(object sender, EventArgs e)
		{
			msglbl.Text = "";
			txtEditor.Text = "";
			//	msglbl.Text = "this is a new file";
			//	txtEdi
		}

		private void txtEditorClick(object sender, KeyPressEventArgs e)
		{
			//	msglbl.Text = "KeyPressEventArgs";
		}

		private void txtEditorClick(object sender, KeyEventArgs e)
		{
			///	msglbl.Text = "From the keyEventArgs";
		}

		private void button1_Click_4(object sender, EventArgs e)
		{
			SaveFileDialog sfd = new SaveFileDialog();
			if (sfd.ShowDialog() == DialogResult.OK)
			{
				File.WriteAllText(sfd.FileName, txtEditor.Text);
				msglbl.Text = sfd.FileName;
				fileName = sfd.FileName;
				int res = solveName(fileName, fileName.Length, 1);  //	Compress the file
				checkRes(res);
				flag = false;
			}
		}
	}
}

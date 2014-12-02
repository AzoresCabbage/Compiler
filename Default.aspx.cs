using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Diagnostics;
using System.IO;

public partial class _Default : System.Web.UI.Page
{
    static string rootpath = @"C:\Users\coolwyj\Documents\Visual Studio 2012\WebSites\WebSite1\";

    protected void Page_Load(object sender, EventArgs e)
    {

        if (Request.Form["s"] == "1")
        {
            string code = Request.Form["code"].ToString();
            //code = Server.UrlDecode(code);

            FileStream fs = new FileStream(rootpath+"code.txt", FileMode.Create, FileAccess.Write);
            //初始化写入流对象，指定要写入的流，编码方式
            StreamWriter sw = new StreamWriter(fs, System.Text.Encoding.Default);
            //向文件写入内容
            sw.WriteLine(code);
            //关闭流
            sw.Close();
            fs.Close();
           
            string res = Solve();

            Response.Write(res);
            Response.End();
        }
    }

    protected void Call_c()
    {
        string cmdtext0 = "cd "+rootpath;
        string cmdtext1 = @"main.exe";
        
        Process MyProcess = new Process();
        //设定程序名 
        MyProcess.StartInfo.FileName = "cmd.exe";
        //关闭Shell的使用 
        MyProcess.StartInfo.UseShellExecute = false;
        //重定向标准输入 
        MyProcess.StartInfo.RedirectStandardInput = true;
        //重定向标准输出 
        MyProcess.StartInfo.RedirectStandardOutput = true;
        //重定向错误输出 
        MyProcess.StartInfo.RedirectStandardError = true;
        //设置不显示窗口 
        MyProcess.StartInfo.CreateNoWindow = true;
        //执行VER命令 
        MyProcess.Start();
        MyProcess.StandardInput.WriteLine(cmdtext0);
        MyProcess.StandardInput.WriteLine(cmdtext1);
        MyProcess.StandardInput.WriteLine("exit");
        //从输出流获取命令执行结果
        MyProcess.WaitForExit();
    }
    protected string Solve()
    {
        Call_c();
        StreamReader sr = new StreamReader(rootpath+"syntax_analyze.txt",System.Text.Encoding.Default); 
        String txtStr = sr.ReadToEnd();
        sr.Close();
        return txtStr;
    }

    protected void Button1_Click(object sender, EventArgs e)
    {
        Response.Redirect("syntax.aspx");
    }
    protected void Button2_Click(object sender, EventArgs e)
    {
        Response.Redirect("lex.aspx");
    }
}